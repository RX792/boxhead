#pragma once
#include <OpenGL.hpp>
#include <Pipeline.hpp>
#include <VertexStream.hpp>
#include <Blobs.hpp>
#include <Utils.hpp>
#include <BlobUtils.hpp>

GLvoid Render(GLvoid);
GLvoid UpdateView(const int w, const int h);
GLvoid UpdateKeyboard(const unsigned char key, const int x, const int y);
GLvoid UpdateSpecialKeyboard(const int key, const int x, const int y);
GLvoid UpdateMouse(const int button, const int state, const int x, const int y);
GLvoid UpdateMouseMotion(const int x, const int y);
GLvoid UpdateFrames(const int delta_time);

float RandomizeColour();

class TankShow
{
public:
	TankShow()
		: myRenderer(), myVertexBuffer(ogl::CreateVertex())
		, myX(), myY(), myZ()
		, myPitch(), myYaw(), myRoll()
	{}

	void Awake()
	{
		myRenderer.Awake();

		myRenderer.LoadVertexShader("..\\Shaders\\PlainV.glsl");
		myRenderer.LoadFragmentShader("..\\Shaders\\PlainP.glsl");

		ResetCamera();
		
		constexpr float proj_fov = glm::radians(60.0f);
		const float proj_ratio = ogl::GetAspectRatio();

		perspectiveMatrix = glm::perspective(proj_fov, proj_ratio, 0.1f, 10000.0f);
		
		orthodoxMatrix = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f);
	}

	void Start()
	{
		constexpr auto axis_color = ogl::Colour{ 0.0f, 0.0f, 0.0f, 1.0f };
		const ogl::Vertex axis_lines[] =
		{
			{ +400.0f, 0.0f, 0.0f, axis_color },
			{ -400.0f, 0.0f, 0.0f, axis_color },
			{ 0.0f, +300.0f, 0.0f, axis_color },
			{ 0.0f, -300.0f, 0.0f, axis_color }
		};
		myVertexBuffer.PushRaw(axis_lines);

		constexpr auto spatial_c1 = ogl::Colour{ 0.0f, 1.0f, 1.0f, 1.0f };
		constexpr auto spatial_c2 = ogl::Colour{ 1.0f, 0.0f, 1.0f, 1.0f };
		constexpr auto spatial_c3 = ogl::Colour{ 1.0f, 1.0f, 0.0f, 1.0f };
		constexpr auto spatial_c4 = ogl::Colour{ 1.0f, 0.0f, 0.0f, 1.0f };
		constexpr auto spatial_c5 = ogl::Colour{ 0.0f, 1.0f, 0.0f, 1.0f };
		constexpr auto spatial_c6 = ogl::Colour{ 0.0f, 0.0f, 1.0f, 1.0f };
		// °ËÀº»ö
		constexpr auto spatial_c7 = ogl::Colour{ 0.0f, 0.0f, 0.0f, 1.0f };
		// Èò»ö
		constexpr auto spatial_c8 = ogl::Colour{ 1.0f, 1.0f, 1.0f, 1.0f };
		// ±Ý»ö
		constexpr auto spatial_c9 = ogl::Colour{ 1.0f, 0.8f, 0.1f, 1.0f };

		constexpr ogl::Quad pt1 = { -0.8f, +0.5f, -0.7f };
		constexpr ogl::Quad pt2 = { -0.8f, +0.5f, +0.7f };
		constexpr ogl::Quad pt3 = { +0.8f, +0.5f, +0.7f };
		constexpr ogl::Quad pt4 = { +0.8f, +0.5f, -0.7f };
		constexpr ogl::Quad pt5 = { -0.8f, -0.5f, -0.7f };
		constexpr ogl::Quad pt6 = { -0.8f, -0.5f, +0.7f };
		constexpr ogl::Quad pt7 = { +0.8f, -0.5f, +0.7f };
		constexpr ogl::Quad pt8 = { +0.8f, -0.5f, -0.7f };

		constexpr ogl::blob::ColoredPlane each_sides[] =
		{
			ogl::blob::plane::Create(pt1, pt2, pt3, pt4, spatial_c1),
			ogl::blob::plane::Create(pt1, pt5, pt6, pt2, spatial_c2),
			ogl::blob::plane::Create(pt2, pt6, pt7, pt3, spatial_c3),
			ogl::blob::plane::Create(pt1, pt4, pt8, pt5, spatial_c9),
			ogl::blob::plane::Create(pt3, pt7, pt8, pt4, spatial_c5),

			ogl::blob::plane::Create(pt5, pt8, pt7, pt6, spatial_c6)
		};
		const auto raw_cube = ogl::blob::cube::Create(each_sides);
		myVertexBuffer.Push(raw_cube);

		constexpr ogl::Quad head_pt1 = { -0.45f, +0.2f, -0.3f };
		constexpr ogl::Quad head_pt2 = { -0.45f, +0.2f, +0.3f };
		constexpr ogl::Quad head_pt3 = { +0.45f, +0.2f, +0.3f };
		constexpr ogl::Quad head_pt4 = { +0.45f, +0.2f, -0.3f };
		constexpr ogl::Quad head_pt5 = { -0.45f, -0.2f, -0.3f };
		constexpr ogl::Quad head_pt6 = { -0.45f, -0.2f, +0.3f };
		constexpr ogl::Quad head_pt7 = { +0.45f, -0.2f, +0.3f };
		constexpr ogl::Quad head_pt8 = { +0.45f, -0.2f, -0.3f };

		constexpr ogl::blob::ColoredPlane head_sides[] =
		{
			ogl::blob::plane::Create(head_pt1, head_pt2, head_pt3, head_pt4, spatial_c7),
			ogl::blob::plane::Create(head_pt1, head_pt5, head_pt6, head_pt2, spatial_c7),
			ogl::blob::plane::Create(head_pt2, head_pt6, head_pt7, head_pt3, spatial_c7),
			ogl::blob::plane::Create(head_pt1, head_pt4, head_pt8, head_pt5, spatial_c8),
			ogl::blob::plane::Create(head_pt3, head_pt7, head_pt8, head_pt4, spatial_c7),
			ogl::blob::plane::Create(head_pt5, head_pt8, head_pt7, head_pt6, spatial_c7)
		};
		const auto head_cube = ogl::blob::cube::Create(head_sides);
		myVertexBuffer.Push(head_cube);

		constexpr ogl::Quad arm_pt1 = { -0.1f, +0.7f, -0.1f };
		constexpr ogl::Quad arm_pt2 = { -0.1f, +0.7f, +0.1f };
		constexpr ogl::Quad arm_pt3 = { +0.1f, +0.7f, +0.1f };
		constexpr ogl::Quad arm_pt4 = { +0.1f, +0.7f, -0.1f };
		constexpr ogl::Quad arm_pt5 = { -0.1f, -0.7f, -0.1f };
		constexpr ogl::Quad arm_pt6 = { -0.1f, -0.7f, +0.1f };
		constexpr ogl::Quad arm_pt7 = { +0.1f, -0.7f, +0.1f };
		constexpr ogl::Quad arm_pt8 = { +0.1f, -0.7f, -0.1f };

		constexpr ogl::blob::ColoredPlane arms_sides[] =
		{
			ogl::blob::plane::Create(arm_pt1, arm_pt2, arm_pt3, arm_pt4, spatial_c9),
			ogl::blob::plane::Create(arm_pt1, arm_pt5, arm_pt6, arm_pt2, spatial_c9),
			ogl::blob::plane::Create(arm_pt2, arm_pt6, arm_pt7, arm_pt3, spatial_c9),
			ogl::blob::plane::Create(arm_pt1, arm_pt4, arm_pt8, arm_pt5, spatial_c8),
			ogl::blob::plane::Create(arm_pt3, arm_pt7, arm_pt8, arm_pt4, spatial_c9),
			ogl::blob::plane::Create(arm_pt5, arm_pt8, arm_pt7, arm_pt6, spatial_c9)
		};
		const auto arms_cube = ogl::blob::cube::Create(arms_sides);
		myVertexBuffer.Push(arms_cube);

		constexpr auto floor_c1 = ogl::Colour{ 0.15f, 0.4f, 0.1f, 1.0f };
		constexpr auto floor_c2 = ogl::Colour{ 0.6f, 0.2f, 0.0f, 1.0f };
		constexpr auto floor_c3 = ogl::Colour{ 0.0f, 0.6f, 0.0f, 1.0f };
		constexpr ogl::blob::ColoredPlane floor = ogl::blob::plane::Create
		(
			{ -10.0f, -2.0f, -10.0f, floor_c1 },
			{ -10.0f, -2.0f, +10.0f, floor_c2 },
			{ +10.0f, -2.0f, +10.0f, floor_c3 },
			{ +10.0f, -2.0f, -10.0f, floor_c2 }
		);
		myVertexBuffer.Push(floor);

		myRenderer.Start();
	}

	void Move(const float& x, const float& y, const float& z)
	{
		const glm::vec4 direction{ x, y, z, 1.0f };
		const auto my_mat = ogl::Rotate(ogl::identity, myPitch, myYaw, myRoll);

		Translate(my_mat * direction);
	}

	void JumpTo(const float& x, const float& y, const float& z)
	{
		myX = x;
		myY = y;
		myZ = z;
	}

	void Translate(const float& ax, const float& ay, const float& az)
	{
		myX += ax;
		myY += ay;
		myZ += az;
	}

	void Translate(const glm::vec3& vector)
	{
		myX += vector.x;
		myY += vector.y;
		myZ += vector.z;
	}

	void Tilt(const float& pitch, const float& yaw, const float& roll)
	{
		myRoll += roll;
		myPitch += pitch;
		myYaw += yaw;
	}

	void Rotate(const float& pitch, const float& yaw, const float& roll)
	{
		myRoll = roll;
		myPitch = pitch;
		myYaw = yaw;
	}

	void HeadRotate(const float& yaw)
	{
		myHeadYaw = yaw;
	}

	void ArmsRotate(const float& roll)
	{
		myArmsPitch = roll;
	}

	void CameraMove(const float& x, const float& y, const float& z)
	{
		myCameraMatrix = ogl::Translate(myCameraMatrix, { x, y, z });
	}

	void CameraRotate(const float& pitch, const float& yaw, const float& roll)
	{
		myCameraMatrix = ogl::Rotate(myCameraMatrix, pitch, yaw, roll);
	}

	void ResetCamera()
	{
		constexpr glm::vec3 world_up = { 0.0f, 1.0f, 0.0f };
		constexpr glm::vec3 cam_coords = { 0.0f, 8.0f, 15.0f };
		constexpr glm::vec3 cam_target = { 0.0f, 0.0f, 0.0f };

		cameraLook = glm::normalize(cam_target - cam_coords);
		cameraRight = glm::normalize(glm::cross(world_up, cameraLook));
		cameraUp = glm::normalize(glm::cross(cameraLook, cameraRight));

		myCameraMatrix = glm::lookAt(cam_coords, cam_target, cameraUp);
	}

	void PrepareRendering()
	{
		myRenderer.PrepareRendering();
	}

	void DrawScreens()
	{
		const auto halfw = ogl::gl_width / 2;
		const auto halfh = ogl::gl_height / 2;
		const auto cy = std::max(ogl::gl_width, ogl::gl_height);
		
		ogl::DrawSetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		glPushMatrix();
		glViewport(0, halfh * 2 / 3, halfw, halfh);
		Draw();
		glPopMatrix();
		
		glPushMatrix();
		//gluLookAt(0, cy, 0, 0, 0, 0, 0, 1, 0);
		glViewport(halfw, 0, halfw, halfh);
		Draw();
		glPopMatrix();

		glPushMatrix();
		//gluLookAt(cy, 0, 0, 0, 0, 0, 0, 1, 0);
		glViewport(halfw, halfh, halfw, halfh);
		Draw();
		glPopMatrix();
		
		glLoadIdentity();
		
		ogl::DrawSetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		glLineWidth(3);
		ogl::PrimitivesBegin(ogl::PRIMITIVE_TYPES::LINES);
		glVertex3f(halfw, 0, 0);
		glVertex3f(halfw, ogl::gl_height, 0);
		ogl::PrimitivesEnd();
		ogl::PrimitivesBegin(ogl::PRIMITIVE_TYPES::LINES);
		glVertex3f(0, halfh, 0);
		glVertex3f(ogl::gl_width, halfh, 0);
		ogl::PrimitivesEnd();
		
		ogl::DrawSetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		glLineWidth(1);
	}
	
	void Draw()
	{
		auto uniform_mat_world = myRenderer.GetUniform("a_WorldMatrix");
		auto uniform_mat_camera = myRenderer.GetUniform("a_CameraMatrix");
		auto uniform_mat_proj = myRenderer.GetUniform("a_ProjMatrix");

		// x, y, z, r, g, b, a
		constexpr GLsizei stride = sizeof(float) * 7;

		uniform_mat_world.AssignMatrix4x4(ogl::identity);
		uniform_mat_camera.AssignMatrix4x4(myCameraMatrix);
		uniform_mat_proj.AssignMatrix4x4(perspectiveMatrix);
		//perspectiveMatrix

		auto attr_pos = myRenderer.BeginAttribute("a_Position", stride);
		auto attr_col = myRenderer.BeginAttribute("a_Colour", stride);

		auto& buffer_axis = myVertexBuffer.At(0);
		buffer_axis.PrepareRendering();
		{
			myRenderer.ReadBuffer(attr_pos, 3);
			myRenderer.ReadBuffer(attr_col, 4);
			ogl::Render(ogl::PRIMITIVE_TYPES::LINES, 4);
			myRenderer.ResetSeekBuffer();
		}

		auto& buffer_floor = myVertexBuffer.At(4);
		buffer_floor.PrepareRendering();
		myRenderer.ReadBuffer(attr_pos, 3);
		myRenderer.ReadBuffer(attr_col, 4);
		ogl::Render(ogl::PRIMITIVE_TYPES::TRIANGLE_FAN, 4);
		myRenderer.ResetSeekBuffer();

		const auto translation_x = ogl::right * myX;//cameraRight * myX;
		const auto translation_y = ogl::up * myY;
		const auto translation_z = ogl::forward * myZ;

		// T R S
		auto my_mat = ogl::Translate(ogl::identity, translation_x);
		my_mat = ogl::Translate(my_mat, translation_y);
		my_mat = ogl::Translate(my_mat, translation_z);
		my_mat = ogl::Rotate(my_mat, myPitch, myYaw, myRoll);

		uniform_mat_world.AssignMatrix4x4(my_mat);

		auto& buffer_cube = myVertexBuffer.At(1);
		buffer_cube.PrepareRendering();
		{
			myRenderer.ReadBuffer(attr_pos, 3);
			myRenderer.ReadBuffer(attr_col, 4);
			for (GLint i = 0; i < 6; i++)
			{
				ogl::Render(ogl::PRIMITIVE_TYPES::TRIANGLE_FAN, 4, i * 4);
			}
			myRenderer.ResetSeekBuffer();
		}

		my_mat = ogl::Translate(my_mat, { 0.0f, 0.5f, 0.0f });
		my_mat = ogl::Rotate(my_mat, 0.0f, myHeadYaw, 0.0f);
		uniform_mat_world.AssignMatrix4x4(my_mat);

		auto& buffer_head = myVertexBuffer.At(2);
		buffer_head.PrepareRendering();
		{
			myRenderer.ReadBuffer(attr_pos, 3);
			myRenderer.ReadBuffer(attr_col, 4);
			for (GLint i = 0; i < 6; i++)
			{
				ogl::Render(ogl::PRIMITIVE_TYPES::TRIANGLE_FAN, 4, i * 4);
			}
			myRenderer.ResetSeekBuffer();
		}

		const auto my_head_mat = my_mat;

		auto& buffer_arm = myVertexBuffer.At(3);
		buffer_arm.PrepareRendering();
		// ¿ÞÂÊ ±Í
		{
			my_mat = ogl::Rotate(my_mat, myArmsPitch, 0.0f, 0.0f);
			my_mat = ogl::Translate(my_mat, { -0.22f, 0.35f, 0.0f });
			uniform_mat_world.AssignMatrix4x4(my_mat);

			myRenderer.ReadBuffer(attr_pos, 3);
			myRenderer.ReadBuffer(attr_col, 4);
			for (GLint i = 0; i < 6; i++)
			{
				ogl::Render(ogl::PRIMITIVE_TYPES::TRIANGLE_FAN, 4, i * 4);
			}
			myRenderer.ResetSeekBuffer();
			my_mat = my_head_mat;
		}
		// ¿À¸¥ÂÊ ±Í
		{
			my_mat = ogl::Rotate(my_mat, -myArmsPitch, 0.0f, 0.0f);
			my_mat = ogl::Translate(my_mat, { +0.22f, 0.35f, 0.0f });
			uniform_mat_world.AssignMatrix4x4(my_mat);

			myRenderer.ReadBuffer(attr_pos, 3);
			myRenderer.ReadBuffer(attr_col, 4);
			for (GLint i = 0; i < 6; i++)
			{
				ogl::Render(ogl::PRIMITIVE_TYPES::TRIANGLE_FAN, 4, i * 4);
			}
			myRenderer.ResetSeekBuffer();
		}

		attr_pos.DisableVertexArray();
		attr_col.DisableVertexArray();
	}

	ogl::Pipeline myRenderer;
	ogl::VertexStream myVertexBuffer;

	//glm::mat4 myWorldMatrix;
	glm::mat4 myCameraMatrix;
	glm::vec3 cameraRight, cameraLook, cameraUp;
	glm::mat4 perspectiveMatrix;
	glm::mat4 perspectiveTopMatrix;
	glm::mat4 orthodoxMatrix;

	float myX, myY, myZ;
	float myPitch, myYaw, myRoll;
	float myHeadYaw;
	float myArmsPitch;
	float mySpeed;
	glm::vec3 myDirection;
};
