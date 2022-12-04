#pragma once
#include <OpenGL.hpp>
#include <Pipeline.hpp>
#include <VertexStream.hpp>
#include <Blobs.hpp>
#include <Utils.hpp>
#include <BlobUtils.hpp>
#include <windows.h>

#include "WindowManager.hpp"
#include "Transform.hpp"
#include "Scene.hpp"
#include "Model.hpp"
#include "AxisModel.hpp"
#include "FloorModel.hpp"
#include "SideCubeModel.hpp"
#include "Player.hpp"

class GameScene : public Scene
{
public:
	GameScene(const size_t& id)
		: Scene(id)
		, myRenderer()
		, cameraPitch(), cameraYaw()
		, cameraMatrix()
		, cameraRight(), cameraUp(), cameraLook()
		, perspectiveMatrix(), orthodoxMatrix()
		, cursorClicked(false), cursorPosition(), clientRect()
		, playerCharacter(nullptr)
	{
		SetName("GameScene");
	}

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
	}

	void Start() override
	{
		Scene::Start();

		auto aa = Scene::CreateEntity<Entity>();
		aa->MoveTo(1.0f, 0.0f, 1.0f);

		auto bb = Scene::CreateEntity<Entity>();
		bb->MoveTo(0.0f, 0.0f, 10.0f);

		auto cc = Scene::CreateEntity<Entity>(3.0f, 0.0f, -1.0f);
		cc->MoveTo(3.0f, 0.0f, -1.0f);

		auto dd = Scene::CreateEntity<Entity>();
		dd->MoveTo(4.0f, 0.0f, -2.0f);

		auto ee = Scene::CreateEntity<Entity>();
		ee->MoveTo(5.0f, 0.0f, -3.0f);

		FocusCursor();

		myRenderer.Start();
	}

	void Update() override
	{
		Scene::Update();

		const auto capture = GetCapture();

		if (capture == WindowManager::windowHandle)
		{
			ShowCursor(FALSE);

			POINT mouse{};
			GetCursorPos(&mouse);

			const int dx = mouse.x - cursorPosition.x;
			const int dy = mouse.y - cursorPosition.y;

			if (0 != dx)
			{
				cameraYaw += dx * 0.001f;
			}
			if (0 != dy)
			{
				cameraPitch += dy * 0.001f;
			}

			CameraRotate(cameraPitch, cameraYaw, 0);
			const int tx = int(clientRect.right - clientRect.left) / 2;
			const int ty = int(clientRect.bottom - clientRect.top) / 2;

			SetCursorPos(tx, ty);
			cursorPosition = { tx, ty };
		}
	}

	virtual void OnUpdateView(const int& w, const int& h)
	{
		FocusCursor();
	}

	virtual void OnUpdateMouse(const int& button, const int& state, const int& x, const int& y)
	{
		if (ogl::IsMouseClicked(state))
		{
			const auto capture = GetCapture();

			if (capture != WindowManager::windowHandle)
			{
				SetCapture(WindowManager::windowHandle);
			}

			cursorClicked = true;
		}
		else if (ogl::IsMouseReleased(state))
		{
			const auto capture = GetCapture();

			if (capture == WindowManager::windowHandle)
			{
				ReleaseCapture();
			}

			cursorClicked = false;
		}
	}

	virtual void OnUpdateMouseMotion(const int& x, const int& y)
	{
		if (cursorClicked)
		{
			//SetCapture(WindowManager::windowHandle);
		}
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
		uniform_mat_camera.AssignMatrix4x4(cameraMatrix.myMatrix);
		uniform_mat_proj.AssignMatrix4x4(perspectiveMatrix);

		// x, y, z, r, g, b, a
		constexpr GLsizei shade_stride = sizeof(float) * 7;

		// x, y, z, r, g, b, a, nx, ny, nz
		constexpr GLsizei normal_stride = sizeof(float) * 10;

		auto attr_pos = myRenderer.BeginAttribute("a_Position", shade_stride);
		auto attr_col = myRenderer.BeginAttribute("a_Colour", shade_stride);

		// 0: 좌표축 그리기
		auto model_axis = Model::GetReference<AxisModel>(0);
		model_axis.PrepareRendering();
		myRenderer.ReadBuffer(attr_pos, 3);
		myRenderer.ReadBuffer(attr_col, 4);

		model_axis.Render();
		myRenderer.ResetSeekBuffer();

		// 2: 바닥 그리기
		auto model_floor = Model::GetReference<FloorModel>(2);
		model_floor.PrepareRendering();
		myRenderer.ReadBuffer(attr_pos, 3);
		myRenderer.ReadBuffer(attr_col, 4);

		model_floor.Render();
		myRenderer.ResetSeekBuffer();

		for (auto& instance : myInstances)
		{
			// 1: 큐브
			instance->PrepareRendering();

			myRenderer.ReadBuffer(attr_pos, 3);
			myRenderer.ReadBuffer(attr_col, 4);

			instance->Render(uniform_mat_world);
			myRenderer.ResetSeekBuffer();
		}

		attr_pos.DisableVertexArray();
		attr_col.DisableVertexArray();
	}

	void Cleanup() override
	{
		ShowCursor(TRUE);

		const auto capture = GetCapture();
		if (capture == WindowManager::windowHandle)
		{
			ReleaseCapture();
		}

		ClipCursor(NULL);
	}

private:
	void ResetCamera()
	{
		ResetCamera({ 0.0f, 15.0f, -8.0f }, {});
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
		cameraMatrix.Translate(x, y, z);
	}

	void CameraRotate(const float& pitch, const float& yaw, const float& roll)
	{
		cameraMatrix.Rotate(pitch, 0, 0);
		cameraMatrix.Tilt(0, 0, roll);
		cameraMatrix.Tilt(0, yaw, 0);
	}

private:
	void FocusCursor()
	{
		GetClientRect(WindowManager::windowHandle, &clientRect);

		POINT pt1{}, pt2{};
		pt1.x = clientRect.left;
		pt1.y = clientRect.top;
		pt2.x = clientRect.right;
		pt2.y = clientRect.bottom;

		ClientToScreen(WindowManager::windowHandle, &pt1);
		ClientToScreen(WindowManager::windowHandle, &pt2);
		clientRect.left = pt1.x;
		clientRect.top = pt1.y;
		clientRect.right = pt2.x;
		clientRect.bottom = pt2.y;

		ClipCursor(&clientRect);
	}

	ogl::Pipeline myRenderer;

	float cameraPitch, cameraYaw;
	Transform cameraMatrix;
	glm::vec3 cameraRight, cameraLook, cameraUp;

	glm::mat4 perspectiveMatrix;
	glm::mat4 perspectiveTopMatrix;
	glm::mat4 orthodoxMatrix;

	bool cursorClicked;
	POINT cursorPosition;
	RECT clientRect;

	Player* playerCharacter;
	Camera* camera;
};
