#pragma once
#include <OpenGL.hpp>

#include "Scene.hpp"
#include "Entity.hpp"
#include "Camera.hpp"

class Framework
{
public:
	Framework()
		: myScenes()
		, currentScene(nullptr), reservatedScene(nullptr)
		, sceneProcessFinished(false)
	{
		myScenes.reserve(10);

		Instance = this;
	}

	void Awake()
	{
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

	void Update(const float& delta_time)
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

			currentScene->Update(delta_time);
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
