#pragma once
#include <OpenGL.hpp>
#include <Pipeline.hpp>
#include <VertexStream.hpp>
#include <Blobs.hpp>
#include <Utils.hpp>
#include <BlobUtils.hpp>

#include "Scene.hpp"
#include "ModelView.hpp"
#include "Entity.hpp"
#include "Camera.hpp"

class Framework
{
public:
	Framework()
		: myVertexBuffer(10)
		, myScenes()
		, currentScene(nullptr), reservatedScene(nullptr)
		, sceneProcessFinished(false)
	{
		myScenes.reserve(10);

		Instance = this;
	}

	void Awake()
	{
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

		constexpr ogl::Quad pt1 = { -0.5f, +0.5f, -0.5f };
		constexpr ogl::Quad pt2 = { -0.5f, +0.5f, +0.5f };
		constexpr ogl::Quad pt3 = { +0.5f, +0.5f, +0.5f };
		constexpr ogl::Quad pt4 = { +0.5f, +0.5f, -0.5f };
		constexpr ogl::Quad pt5 = { -0.5f, -0.5f, -0.5f };
		constexpr ogl::Quad pt6 = { -0.5f, -0.5f, +0.5f };
		constexpr ogl::Quad pt7 = { +0.5f, -0.5f, +0.5f };
		constexpr ogl::Quad pt8 = { +0.5f, -0.5f, -0.5f };

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

		// 0: Å¥ºê
		myVertexBuffer.Push(raw_cube);

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

		// 1: ÁÂÇ¥Ãà
		myVertexBuffer.PushRaw(axis_lines);

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

		// 2: ¹Ù´Ú
		myVertexBuffer.Push(floor);

		if (0 < myScenes.size())
		{
			auto first_scene = myScenes.at(0);

			ChangeScene(first_scene);
		}
	}

	void Start()
	{
		if (currentScene && !currentScene->IsEnded())
		{
			sceneProcessFinished = false;
		}
	}

	void Update()
	{
		if (reservatedScene && sceneProcessFinished)
		{
			ChangeScene(reservatedScene);
		}

		if (currentScene)
		{
			sceneProcessFinished = false;

			if (currentScene->IsEnded())
			{
				Scene* next_scene;
				try
				{
					next_scene = myScenes.at(currentScene->GetID() + 1);

					ChangeScene(next_scene);
				}
				catch (...)
				{
					currentScene = nullptr;
				}

				return;
			}

			currentScene->Update();
		}
	}

	void OnUpdateView(const int& w, const int h)
	{
		if (currentScene && !currentScene->IsEnded())
		{
			currentScene->OnUpdateView(w, h);
		}
	}

	void OnUpdateKeyboard(const unsigned char& key, const int& x, const int& y)
	{
		if (currentScene && !currentScene->IsEnded())
		{
			currentScene->OnUpdateKeyboard(key, x, y);
		}
	}

	void OnUpdateSpecialKey(const int& key, const int& x, const int& y)
	{
		if (currentScene && !currentScene->IsEnded())
		{
			currentScene->OnUpdateSpecialKey(key, x, y);
		}
	}

	void OnUpdateMouse(const int& button, const int& state, const int& x, const int& y)
	{
		if (currentScene && !currentScene->IsEnded())
		{
			currentScene->OnUpdateMouse(button, state, x, y);
		}
	}

	void OnUpdateMouseMotion(const int& x, const int& y)
	{
		if (currentScene && !currentScene->IsEnded())
		{
			currentScene->OnUpdateMouseMotion(x, y);
		}
	}

	void PrepareRendering()
	{
		if (currentScene && currentScene->IsStarted())
		{
			sceneProcessFinished = false;

			currentScene->PrepareRendering();
		}
	}

	void Render()
	{
		if (currentScene && currentScene->IsStarted())
		{
			currentScene->Render();

			sceneProcessFinished = true;
		}
	}

	Scene* AddScene(Scene* const scene)
	{
		myScenes.push_back(scene);

		return scene;
	}

	template<typename Ty, typename ...ArgTy>
		requires SceneType<Ty, size_t, ArgTy...>
	Ty* AddScene(ArgTy&&... arg)
	{
		const size_t count = myScenes.size();

		Ty* scene = new Ty{ count, std::forward<ArgTy>(arg)... };

		myScenes.push_back(scene);

		return scene;
	}

	Scene* const GetScene(const size_t& index) const
	{
		return myScenes.at(index);
	}

	void ChangeScene(Scene* scene)
	{
		if (!currentScene)
		{
			sceneProcessFinished = true;
		}

		if (sceneProcessFinished)
		{
			ChangeSceneNow(scene);

			reservatedScene = nullptr;
		}
		else
		{
			reservatedScene = scene;
		}
	}

	void ChangeScene(const size_t& index)
	{
		auto target = GetScene(index);

		if (target)
		{
			ChangeScene(target);
		}
	}

	static Framework* Instance;

private:
	std::vector<Scene*> myScenes;
	Scene* currentScene;
	Scene* reservatedScene;
	bool sceneProcessFinished;

	ogl::VertexStream myVertexBuffer;

	friend class ModelView;

	void ChangeSceneNow(Scene* scene)
	{
		if (currentScene)
		{
			currentScene->Cleanup();
		}

		currentScene = scene;
		sceneProcessFinished = false;

		if (!currentScene->IsAwaken())
		{
			currentScene->Awake();
		}

		if (!currentScene->IsStarted())
		{
			currentScene->Start();
		}
	}
};
