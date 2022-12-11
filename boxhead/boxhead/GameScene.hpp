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
		, test_model(nullptr)
	{
		heightMap.reserve(boardSizeW * boardSizeH + 1);
	}

	virtual ~MapManager()
	{}

	void Awake(Scene* scene)
	{
		// 딱 한번만 높이 맵 생성
		for (size_t i = 0; i < boardSizeW; i++)
		{
			for (size_t j = 0; j < boardSizeH; j++)
			{
				// 열 우선으로 삽입
				auto& terrain_cell = GetTerrainAt(i, j);

				if (terrain_cell == 1 || terrain_cell == 2)
				{
					float cell_height = 1.0f;
					heightMap.emplace_back(i, j, cell_height);
				}
			}
		}

		test_model = new SideCubeModelView{ 0 };

		// 높이 맵의 내용대로 벽 생성
		for (auto& height_block : heightMap)
		{
			const float cx = boardScaleW * static_cast<float>(height_block.x);
			const float cz = boardScaleH * static_cast<float>(height_block.y);

			Entity* wall = scene->CreateEntity<Entity>(test_model, cx, 0.5f, cz);
		}
	}

	void Start(Scene* scene)
	{}

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

	ModelView* test_model;

	static inline constexpr size_t boardSizeW = 40;
	static inline constexpr size_t boardSizeH = 40;

private:
	static inline constexpr float boardScaleW = 1.0f;
	static inline constexpr float boardScaleH = 1.0f;

	std::vector<Block> heightMap;

	TerrainItem terrainMap[boardSizeH][boardSizeW] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
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
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
		auto model_axis = ModelView::GetReference<AxisModelView>();
		model_axis.PrepareRendering();
		myRenderer.ReadBuffer(attr_pos, 3);
		myRenderer.ReadBuffer(attr_col, 4);

		model_axis.Render();
		myRenderer.ResetSeekBuffer();

		// 2: 바닥 그리기
		auto model_floor = ModelView::GetReference<FloorModelView>();
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
