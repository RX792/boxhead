#pragma once
#include <OpenGL.hpp>

#include "Scene.hpp"
#include "Entity.hpp"
#include "Camera.hpp"

class Framework
{
private:

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
		if (currentScene)
		{
			sceneProcessFinished = false;

			currentScene->Start();
		}
	}

	void Update(const float& delta_time)
	{
		if (currentScene)
		{
			sceneProcessFinished = false;

			currentScene->Update(delta_time);
		}
	}

	void PrepareRendering()
	{
		if (currentScene)
		{
			currentScene->PrepareRendering();
		}
	}

	void Render()
	{
		if (currentScene)
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
		requires SceneType<Ty, ArgTy...>
	Ty* AddScene(ArgTy&&... arg)
	{
		Ty* scene = new Ty{ std::forward<ArgTy>(arg)... };

		myScenes.push_back(scene);

		return scene;
	}

	void ChangeScene(Scene* scene)
	{
		if (currentScene)
		{
			currentScene->Cleanup();
		}
		else
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

	static Framework* Instance;

private:
	std::vector<Scene*> myScenes;
	Scene* currentScene;
	Scene* reservatedScene;
	bool sceneProcessFinished;

	void ChangeSceneNow(Scene* scene)
	{
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
