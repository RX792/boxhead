#pragma once
#define NOMINMAX
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
#include "Camera.hpp"
#include "Player.hpp"
#include "Map.hpp"

class GameScene : public Scene
{
public:
	constexpr GameScene(const size_t& id)
		: Scene(id)
		, myRenderer()
		, perspectiveMatrix(), orthodoxMatrix()
		, cursorClicked(false), cursorPosition(), clientRect()
		, mainCamera(nullptr), cameraYaw(), cameraPitch()
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

		constexpr float proj_fov = glm::radians(60.0f);
		const float proj_ratio = ogl::GetAspectRatio();

		perspectiveMatrix = glm::perspective(proj_fov, proj_ratio, 0.1f, 10000.0f);

		orthodoxMatrix = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f);

		mainCamera = new Camera{ ogl::up };
		mainCamera->MoveTo({ 0.0f, 15.0f, -8.0f });
		mainCamera->SetLookDirection(ogl::forward);

		playerCharacter = new Player{};

		map_manager = new MapManager{};
		map_manager->Awake(this);
	}

	void Start() override
	{
		Scene::Start();

		UpdateClientRect();
		ResetCamera();
		ResetCursorPosNow();
		FocusCursor();

		myRenderer.Start();
	}

	void Update() override
	{
		const auto delta_time = Timer::GetDeltaTime();

		Scene::Update();

		const auto capture = GetCapture();

		if (capture == WindowManager::windowHandle)
		{
			HideCursor();

			POINT mouse{};
			GetCursorPos(&mouse);

			const int dx = mouse.x - cursorPosition.x;
			const int dy = mouse.y - cursorPosition.y;

			if (0 != dx)
			{
				const float addition = dx * 0.3f * delta_time;
				cameraYaw += addition;
				//mainCamera->Tilt(0.0f, addition, 0.0f);
			}

			if (0 != dy)
			{
				const float addition = dy * 0.3f * delta_time;
				cameraPitch += addition;
				//mainCamera->Tilt(addition, 0.0f, 0.0f);
			}

			mainCamera->Rotate(cameraPitch, cameraYaw, 0.0f);

			const int tx = clientRect.left + int(clientRect.right - clientRect.left) / 2;
			const int ty = clientRect.top + int(clientRect.bottom - clientRect.top) / 2;

			SetCursorPos(tx, ty);
			cursorPosition = { tx, ty };
		}
	}

	virtual void OnUpdateView(const int& w, const int& h)
	{
		UpdateClientRect();

		FocusCursor();
	}

	virtual void OnUpdateMouse(const int& button, const int& state, const int& x, const int& y)
	{
		if (ogl::IsMouseClicked(state))
		{
			if (!cursorClicked)
			{
				ResetCursorPosNow();

				cursorClicked = true;
			}

			const auto capture = GetCapture();

			if (capture != WindowManager::windowHandle)
			{
				SetCapture(WindowManager::windowHandle);
			}
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
		uniform_mat_camera.AssignMatrix4x4(mainCamera->GetMatrix());
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
		ShowCursor();

		const auto capture = GetCapture();
		if (capture == WindowManager::windowHandle)
		{
			ReleaseCapture();
		}

		ClipCursor(NULL);
	}

	GameScene* getThis()
	{
		return this;
	}

private:
	void UpdateClientRect()
	{
		GetClientRect(WindowManager::windowHandle, &clientRect);
	}

	void ResetCamera()
	{
		ResetCamera({ 0.0f, 15.0f, -8.0f }, {});
	}

	void ResetCamera(const glm::vec3& camera_position, const glm::vec3& camera_lookat)
	{
		mainCamera->MoveTo(camera_position);
		mainCamera->Rotate(0.0f, 0.0f, 0.0f);

		cameraYaw = 0.0f;
		cameraPitch = 0.0f;
	}

	void ShowCursor()
	{
		::ShowCursor(TRUE);
	}

	void HideCursor()
	{
		::ShowCursor(FALSE);
	}

	void FocusCursor()
	{
		RECT temp_rect{};
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

	void ResetCursorPosNow()
	{
		POINT mouse{};
		GetCursorPos(&mouse);

		cursorPosition = { mouse.x, mouse.y };
	}

	ogl::Pipeline myRenderer;

	glm::mat4 perspectiveMatrix;
	glm::mat4 perspectiveTopMatrix;
	glm::mat4 orthodoxMatrix;

	float cameraPitch, cameraYaw;

	bool cursorClicked;
	POINT cursorPosition;
	RECT clientRect;

	Camera* mainCamera;
	Player* playerCharacter;
	MapManager* map_manager;
};
