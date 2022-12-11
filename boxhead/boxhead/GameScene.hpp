#pragma once
#define NOMINMAX
#include <windows.h>

#include "Player.hpp"
#include "WorldManager.hpp"
#include "AxisModel.hpp"
#include "FloorModel.hpp"
#include "SideCubeModel.hpp"

using namespace camera;

class WorldManager
{
public:
	constexpr WorldManager()
		: heightMap()
		, stageFilepath("Stage.txt")
	{
		heightMap.reserve(boardSizeW * boardSizeH + 1);
	}

	~WorldManager()
	{}

	void Awake()
	{
		// 딱 한번만 높이 맵 생성
		std::fstream stage_file{ stageFilepath, std::ios::in };

		if (stage_file)
		{
			terrainMap = new int* [boardSizeH];
			for (size_t y = 0; y < boardSizeW; y++)
			{
				terrainMap[y] = new int[boardSizeW];
			}

			char piece{};
			size_t x = 0, y = 0;

			while (stage_file >> piece)
			{
				if (' ' == piece) continue;

				SetTerrainAt(x, y, int(piece - '0'));

				x++;
				if (boardSizeW <= x)
				{
					x = 0;
					y++;
				}
			}

			for (size_t i = 0; i < boardSizeW; i++)
			{
				for (size_t j = 0; j < boardSizeH; j++)
				{
					// 열 우선으로 삽입
					auto& terrain_cell = GetTerrainAt(i, j);

					if (0 < terrain_cell)
					{
						float cell_height = 1.0f * float(terrain_cell);
						heightMap.emplace_back(i, j, cell_height);
					}
				}
			}
		}
	}

	void Start(Scene* scene)
	{
		// 모델 가져오기
		auto wall_model_view = ModelView::GetReference<SideCubeModel>();

		// 높이 맵의 내용대로 벽 생성
		for (auto& height_block : heightMap)
		{
			const float cx = boardScaleW * static_cast<float>(height_block.x);
			const float cy = -(1 - height_block.myHeight) * 0.5f;
			const float cz = boardScaleD * static_cast<float>(height_block.y);

			Entity* wall = scene->CreateEntity<Entity>(wall_model_view, cx, cy, cz);
			wall->Scale(boardScaleW, height_block.myHeight, boardScaleD);
		}
	}

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

	constexpr int& SetTerrainAt(const size_t& x, const size_t& y, const int& value)
	{
		auto& cell = GetTerrainAt(x, y);
		cell = value;

		return cell;
	}

	constexpr int& GetTerrainAt(const size_t& x, const size_t& y)
	{
		//return terrainMap.at(y).at(x);
		return terrainMap[y][x];
	}

	constexpr const int& GetTerrainAt(const size_t& x, const size_t& y) const
	{
		//return terrainMap.at(y).at(x);
		return terrainMap[y][x];
	}

	static inline constexpr size_t boardSizeW = 40;
	static inline constexpr size_t boardSizeH = 40;

private:
	static inline constexpr float boardScaleW = 1.0f;
	static inline constexpr float boardScaleD = 1.0f;

	std::vector<Block> heightMap;
	std::string stageFilepath;

	//int terrainMap[boardSizeH][boardSizeW];
	int** terrainMap;
};

class GameScene : public Scene
{
public:
	constexpr GameScene(const size_t& id)
		: Scene(id)
		, myRenderer()
		, worldManager()
		, windowFocused(false), cursorClicked(false), cursorPosition(), clientRect()
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

		worldManager.Awake();
		worldManager.Start(this);
	}

	void Start() override
	{
		Scene::Start();

		UpdateClientRect();
		ResetCamera();
		ResetCursorPosNow();
		FocusCursor();

		windowFocused = true;
		myRenderer.Start();
	}

	void Update() override
	{
		const auto delta_time = Timer::GetDeltaTime();

		Scene::Update();

		mainCamera->MoveTo(playerCharacter->GetPosition());

		const auto focus = GetFocus();
		const auto capture = GetCapture();

		if (focus == WindowManager::windowHandle)
		{
			if (windowFocused)
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
		else
		{
			const auto capture = GetCapture();

			if (capture == WindowManager::windowHandle)
			{
				windowFocused = false;
				ReleaseCapture();
			}
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
		}
		else if (ogl::IsMouseReleased(state))
		{
			cursorClicked = false;

			const auto capture = GetCapture();

			if (capture != WindowManager::windowHandle)
			{
				windowFocused = true;
				SetCapture(WindowManager::windowHandle);
			}
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

	bool windowFocused;
	bool cursorClicked;
	POINT cursorPosition;
	RECT clientRect;

	Camera* mainCamera;
	float cameraPitch, cameraYaw;

	Player* playerCharacter;
	const glm::vec3 playerSpawnPosition;

	WorldManager worldManager;
};
