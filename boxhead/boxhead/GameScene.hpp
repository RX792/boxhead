#pragma once
#define NOMINMAX
#include <OpenGL.hpp>
#include <Pipeline.hpp>
#include <VertexStream.hpp>
#include <Blobs.hpp>
#include <Utils.hpp>
#include <BlobUtils.hpp>
#include <windows.h>

#include "AxisModel.hpp"
#include "FloorModel.hpp"
#include "SideCubeModel.hpp"
#include "Player.hpp"
#include "Map"

using namespace camera;

class MapManager
{
private:
	using TerrainItem = int;

public:
	class Block
	{
	public:
		constexpr Block(size_t ix, size_t iy, const float& height = 1.0f)
			: x(ix), y(iy), myHeight(height)
		{}

		constexpr Block& operator=(const float& height)
		{
			myHeight = height;

			return *this;
		}

		explicit operator float() const
		{
			return myHeight;
		}

		size_t x, y;
		float myHeight;
	};

	constexpr MapManager()
		: heightMap()
	{
		heightMap.reserve(boardSizeW * boardSizeH + 1);
	}

	virtual ~MapManager() = default;

	void Awake(Scene* scene);

	void Start(Scene* scene);

	constexpr Block& CellAt(const size_t& x, const size_t& y)
	{
		const auto pos = x * boardSizeH + y;

		return heightMap.at(pos);
	}

	constexpr const Block& CellAt(const size_t& x, const size_t& y) const
	{
		const auto pos = x * boardSizeH + y;

		return heightMap.at(pos);
	}

	constexpr TerrainItem& SetTerrainAt(const size_t& x, const size_t& y, const int& value)
	{
		auto& cell = GetTerrainAt(x, y);
		cell = value;

		return cell;
	}

	constexpr TerrainItem& GetTerrainAt(const size_t& x, const size_t& y)
	{
		//return terrainMap.at(y).at(x);
		return terrainMap[y][x];
	}

	constexpr const TerrainItem& GetTerrainAt(const size_t& x, const size_t& y) const
	{
		//return terrainMap.at(y).at(x);
		return terrainMap[y][x];
	}

	static inline constexpr size_t boardSizeW = 40;
	static inline constexpr size_t boardSizeH = 40;

private:
	static inline constexpr float boardScaleW = 1.0f;
	static inline constexpr float boardScaleH = 1.0f;

	std::vector<Block> heightMap;

	TerrainItem terrainMap[boardSizeH][boardSizeW] =
	{
		// 이쪽이 시작점!
		{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},

		{1,0,0,0,0,0,0,0,0,0,0,2,1,1,1,1,1,1,2,0,0,0,2,1,1,1,1,1,1,2,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2,1,2,0,0,0,0,0,2,1,2,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2,1,2,0,0,0,0,0,2,1,2,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},

		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2,1,2,0,0,0,0,0,2,1,2,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2,1,2,0,0,0,0,0,2,1,2,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,2,1,1,1,1,1,1,2,0,0,0,2,1,1,1,1,1,1,2,0,0,0,0,0,0,0,0,0,1},

		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
};

class WorldManagers
{
public:
	void Awake(Scene* scene)
	{}
};

class GameScene : public Scene
{
public:
	constexpr GameScene(const size_t& id)
		: Scene(id)
		, myRenderer()
		, map_manager()
		, cursorClicked(false), cursorPosition(), clientRect()
		, mainCamera(nullptr), cameraYaw(), cameraPitch()
		, playerCharacter(nullptr), playerSpawnPosition(1.0f, 1.0f, 1.0f)
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

		mainCamera = new Camera{ ogl::up };

		auto pr_setting = camera::PerspectiveCameraSetting{ 40.0f, 16.0f / 9.0f, 0.1f, 1000.0f };
		mainCamera->Setup(pr_setting);

		auto ox_setting = camera::OrthodoxCameraSetting{ -400.0f, 400.0f, -300.0f, 300.0f };
		mainCamera->Setup(ox_setting);

		mainCamera->Awake();
		mainCamera->MoveTo({ 0.0f, 15.0f, -8.0f });
		mainCamera->SetLookDirection(ogl::forward);

		playerCharacter = new Player{ playerSpawnPosition };

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

		const auto focus = GetFocus();

		if (focus == WindowManager::windowHandle)
		{
			HideCursor();

			POINT mouse{};
			GetCursorPos(&mouse);

			const int dx = mouse.x - cursorPosition.x;
			const int dy = mouse.y - cursorPosition.y;

			if (0 != dx)
			{
				const float addition = dx * 10.0f * delta_time;
				cameraYaw += addition;
			}

			if (0 != dy)
			{
				const float addition = dy * 6.0f * delta_time;
				
				cameraPitch = std::max(std::min(cameraPitch + addition, 89.0f), -89.0f);
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

	virtual void OnUpdateKeyboard(const unsigned char& key, const int& x, const int& y)
	{
		playerCharacter->OnKeyboard(key, x, y);
	}

	virtual void OnUpdateSpecialKey(const int& key, const int& x, const int& y)
	{
		playerCharacter->OnSpecialKey(key, x, y);
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

		playerCharacter->OnMouse(button, state, x, y);
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
		uniform_mat_camera.AssignMatrix4x4(mainCamera->GetCameraMatrix());
		uniform_mat_proj.AssignMatrix4x4(mainCamera->GetPerspectiveViewMatrix());

		// x, y, z, r, g, b, a
		constexpr GLsizei shade_stride = sizeof(float) * 7;

		// x, y, z, r, g, b, a, nx, ny, nz
		constexpr GLsizei normal_stride = sizeof(float) * 10;

		auto attr_pos = myRenderer.BeginAttribute("a_Position", shade_stride);
		auto attr_col = myRenderer.BeginAttribute("a_Colour", shade_stride);

		// 1: 좌표축
		auto model_axis = ModelView::GetReference(1);
		model_axis.PrepareRendering();
		myRenderer.ReadBuffer(attr_pos, 3);
		myRenderer.ReadBuffer(attr_col, 4);

		model_axis.Render();
		myRenderer.ResetSeekBuffer();

		// 2: 바닥
		auto model_floor = ModelView::GetReference(2);
		model_floor.PrepareRendering();
		myRenderer.ReadBuffer(attr_pos, 3);
		myRenderer.ReadBuffer(attr_col, 4);

		model_floor.Render();
		myRenderer.ResetSeekBuffer();

		for (auto& instance : myInstances)
		{
			//  0: 큐브
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

	float cameraPitch, cameraYaw;

	bool cursorClicked;
	POINT cursorPosition;
	RECT clientRect;

	Camera* mainCamera;

	Player* playerCharacter;
	const glm::vec3 playerSpawnPosition;

	MapManager* map_manager;
};
