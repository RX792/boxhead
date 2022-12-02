#pragma once
#include <OpenGL.hpp>
#include <Pipeline.hpp>
#include <VertexStream.hpp>
#include <Blobs.hpp>
#include <Utils.hpp>
#include <BlobUtils.hpp>

#include "Scene.hpp"

class GameScene : public Scene
{
public:
	GameScene()
		: Scene()
		, myRenderer(), myVertexBuffer(ogl::CreateVertex())
		, cameraMatrix()
		, cameraRight(), cameraUp(), cameraLook()
		, perspectiveMatrix(), orthodoxMatrix()
	{}

	void Awake() override
	{
		Scene::Awake();

		myRenderer.Awake();
		myRenderer.LoadVertexShader("..\\Shaders\\PlainV.glsl");
		myRenderer.LoadFragmentShader("..\\Shaders\\PlainP.glsl");
		myRenderer.Ready();

		ResetCamera();

		constexpr float proj_fov = glm::radians(60.0f);
		const float proj_ratio = ogl::GetAspectRatio();

		perspectiveMatrix = glm::perspective(proj_fov, proj_ratio, 0.1f, 10000.0f);

		orthodoxMatrix = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f);

		constexpr auto axis_color = ogl::Colour{ 0.0f, 0.0f, 0.0f, 1.0f };
		const ogl::Vertex axis_lines[] =
		{
			{ +400.0f, 0.0f, 0.0f, axis_color },
			{ -400.0f, 0.0f, 0.0f, axis_color },
			{ 0.0f, +300.0f, 0.0f, axis_color },
			{ 0.0f, -300.0f, 0.0f, axis_color },
			{ 0.0f, 0.0f, -400.0f, axis_color },
			{ 0.0f, 0.0f, -400.0f, axis_color }
		};

		// 0: 좌표축
		myVertexBuffer.PushRaw(axis_lines);

		constexpr auto spatial_c1 = ogl::Colour{ 0.0f, 1.0f, 1.0f, 1.0f };
		constexpr auto spatial_c2 = ogl::Colour{ 1.0f, 0.0f, 1.0f, 1.0f };
		constexpr auto spatial_c3 = ogl::Colour{ 1.0f, 1.0f, 0.0f, 1.0f };
		constexpr auto spatial_c4 = ogl::Colour{ 1.0f, 0.0f, 0.0f, 1.0f };
		constexpr auto spatial_c5 = ogl::Colour{ 0.0f, 1.0f, 0.0f, 1.0f };
		constexpr auto spatial_c6 = ogl::Colour{ 0.0f, 0.0f, 1.0f, 1.0f };
		// 검은색
		constexpr auto spatial_c7 = ogl::Colour{ 0.0f, 0.0f, 0.0f, 1.0f };
		// 흰색
		constexpr auto spatial_c8 = ogl::Colour{ 1.0f, 1.0f, 1.0f, 1.0f };
		// 금색
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

		// 1
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

		// 2
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

		// 3
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

		// 4
		myVertexBuffer.Push(floor);
	}
	
	void Start() override
	{
		Scene::Start();

		auto aa = Scene::CreateObject<Entity>();
		aa->MoveTo(1.0f, 0.0f, 1.0f);

		auto bb = Scene::CreateObject<Entity>();
		bb->MoveTo(0.0f, 00.0f, 0.0f);

		auto cc = Scene::CreateObject<Entity>(3.0f, 0.0f, -1.0f);
		cc->MoveTo(3.0f, 0.0f, -1.0f);

		auto dd = Scene::CreateObject<Entity>();
		dd->MoveTo(4.0f, 0.0f, -2.0f);

		auto ee = Scene::CreateObject<Entity>();
		ee->MoveTo(5.0f, 0.0f, -3.0f);

		myRenderer.Start();
	}

	void Update(const float& delta_time) override
	{
		Scene::Update(delta_time);
	}

	void PrepareRendering() override
	{
		myRenderer.PrepareRendering();
	}

	void Render() override
	{
		auto uniform_mat_world = myRenderer.GetUniform("a_WorldMatrix");
		auto uniform_mat_camera = myRenderer.GetUniform("a_CameraMatrix");
		auto uniform_mat_proj = myRenderer.GetUniform("a_ProjMatrix");

		uniform_mat_world.AssignMatrix4x4(ogl::identity);
		uniform_mat_camera.AssignMatrix4x4(cameraMatrix);
		uniform_mat_proj.AssignMatrix4x4(perspectiveMatrix);

		// x, y, z, r, g, b, a
		constexpr GLsizei shade_stride = sizeof(float) * 7;

		// x, y, z, r, g, b, a, nx, ny, nz
		constexpr GLsizei normal_stride = sizeof(float) * 10;

		auto attr_pos = myRenderer.BeginAttribute("a_Position", shade_stride);
		auto attr_col = myRenderer.BeginAttribute("a_Colour", shade_stride);

		// 0: 좌표축 그리기
		auto& buffer_axis = myVertexBuffer.At(0);
		buffer_axis.PrepareRendering();
		{
			myRenderer.ReadBuffer(attr_pos, 3);
			myRenderer.ReadBuffer(attr_col, 4);
			ogl::Render(ogl::PRIMITIVE_TYPES::LINES, 4);
			myRenderer.ResetSeekBuffer();
		}

		// 4: 바닥 그리기
		auto& buffer_floor = myVertexBuffer.At(4);
		buffer_floor.PrepareRendering();
		myRenderer.ReadBuffer(attr_pos, 3);
		myRenderer.ReadBuffer(attr_col, 4);
		ogl::Render(ogl::PRIMITIVE_TYPES::TRIANGLE_FAN, 4);
		myRenderer.ResetSeekBuffer();

		// 1: 큐브
		auto& buffer_cube = myVertexBuffer.At(1);
		buffer_cube.PrepareRendering();

		myRenderer.ReadBuffer(attr_pos, 3);
		myRenderer.ReadBuffer(attr_col, 4);

		for (auto& instance : myInstances)
		{
			instance->PrepareRendering(uniform_mat_world);
			instance->Render();
		}

		myRenderer.ResetSeekBuffer();

		attr_pos.DisableVertexArray();
		attr_col.DisableVertexArray();
	}

private:
	void ResetCamera()
	{
		ResetCamera({ 0.0f, 15.0f, 8.0f }, {});
	}

	void ResetCamera(const glm::vec3& camera_position, const glm::vec3& camera_lookat)
	{
		constexpr glm::vec3 world_up = { 0.0f, 1.0f, 0.0f };

		cameraLook = glm::normalize(camera_lookat - camera_position);
		cameraRight = glm::normalize(glm::cross(world_up, cameraLook));
		cameraUp = glm::normalize(glm::cross(cameraLook, cameraRight));

		cameraMatrix = glm::lookAt(camera_position, camera_lookat, cameraUp);
	}
	
	void CameraMove(const float& x, const float& y, const float& z)
	{
		cameraMatrix = ogl::Translate(cameraMatrix, { x, y, z });
	}

	void CameraRotate(const float& pitch, const float& yaw, const float& roll)
	{
		cameraMatrix = ogl::Rotate(cameraMatrix, pitch, yaw, roll);
	}

private:
	ogl::Pipeline myRenderer;
	ogl::VertexStream myVertexBuffer;

	glm::mat4 cameraMatrix;
	glm::vec3 cameraRight, cameraLook, cameraUp;
	glm::mat4 perspectiveMatrix;
	glm::mat4 perspectiveTopMatrix;
	glm::mat4 orthodoxMatrix;
};
