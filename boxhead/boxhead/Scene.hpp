#pragma once
#include "Entity.hpp"

class Scene
{
public:
	constexpr Scene(const size_t& id)
		: myID(id)
		, myName()
		, myInstances()
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

	Scene& SetName(std::string_view name)
	{
		myName = name;

		return *this;
	}

	std::string_view GetName() const
	{
		return myName;
	}

	size_t GetID() const
	{
		return myID;
	}

	bool IsAwaken() const
	{
		return isAwaken;
	}

	bool IsStarted() const
	{
		return isStarted;
	}

	template<typename Ty, typename ...ArgTy>
		requires EntityType<Ty, ArgTy...>
	Ty* CreateEntity(ArgTy&& ...args)
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

	void AddEntity(Entity* instance)
	{
		myInstances.push_back(instance);
	}

	std::vector<Entity*>::iterator FindEntity(Entity* instance)
	{
		return std::ranges::find(myInstances, instance);
	}

	std::vector<Entity*>::iterator FindEntity(std::string_view name)
	{
		return std::ranges::find_if(myInstances, [&](const Entity* instance) -> bool {
			return (instance->myName == name);
		});
	}

	std::vector<Entity*>::iterator RemoveEntity(Entity* instance)
	{
		auto it = FindEntity(instance);
		if (it != myInstances.end())
		{
			myInstances.erase(it);
		}

		return it;
	}

	std::vector<Entity*>::iterator RemoveEntity(std::vector<Entity*>::iterator& it)
	{
		return myInstances.erase(it);
	}

	size_t GetInstanceCount() const
	{
		return myInstances.size();
	}

	std::vector<Entity*> myInstances;

private:
	std::string myName;
	const size_t myID;

	bool isAwaken;
	bool isStarted;
};

template<typename Ty, typename ...ArgTy>
concept SceneType = std::derived_from<Ty, Scene> && std::constructible_from<Ty, ArgTy...>;
