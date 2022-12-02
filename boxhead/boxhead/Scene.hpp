#pragma once
#include "Entity.hpp"

class Scene
{
public:
	constexpr Scene()
		: myInstances()
		, isAwaken(false), isStarted(false)
	{
		myInstances.reserve(10);
	}

	virtual ~Scene()
	{
		Cleanup();
	}

	virtual void Awake()
	{
		if (!isAwaken)
		{
			isAwaken = true;
		}
	}
	
	virtual void Start()
	{
		if (!isStarted)
		{
			isStarted = true;
		}
	}

	virtual void Update(const float& delta_time)
	{
		for (auto& instance : myInstances)
		{
			instance->Update(delta_time);
		}
	}
	
	virtual void PrepareRendering() = 0;

	virtual void Render() = 0;

	virtual void Cleanup()
	{
		isStarted = false;
		
		if (0 < myInstances.size())
		{
			myInstances.clear();
		}
	}

	template<typename Ty, typename ...ArgTy>
		requires EntityType<Ty, ArgTy...>
	Ty* CreateObject(ArgTy&& ...args)
	{
		Ty* obj = Entity::Instantiate<Ty>(std::forward<ArgTy>(args)...);
		if (!obj)
		{
			throw std::bad_alloc{};

			return nullptr;
		}

		obj->Start();
		myInstances.push_back(obj);

		return obj;
	}

	bool IsAwaken() const
	{
		return isAwaken;
	}

	bool IsStarted() const
	{
		return isStarted;
	}

	std::vector<Entity*> myInstances;

private:
	bool isAwaken;
	bool isStarted;
};

template<typename Ty, typename ...ArgTy>
concept SceneType = std::derived_from<Ty, Scene> && std::constructible_from<Ty, ArgTy...>;
