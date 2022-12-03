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
		, isEnded(false)
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

	virtual void OnUpdateView(const int& w, const int& h)
	{}

	virtual void OnUpdateKeyboard(const unsigned char& key, const int& x, const int& y)
	{}

	virtual void OnUpdateSpecialKey(const int& key, const int& x, const int& y)
	{}

	virtual void OnUpdateMouse(const int& button, const int& state, const int& x, const int& y)
	{}

	virtual void OnUpdateMouseMotion(const int& x, const int& y)
	{}

	virtual void PrepareRendering() = 0;

	virtual void Render() = 0;

	virtual void Cleanup()
	{
		isStarted = false;
		isEnded = false;

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

	void End()
	{
		isEnded = true;
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

	bool IsEnded() const
	{
		return isEnded;
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

	std::vector<Entity*>::iterator FindEntity(Entity* const instance)
	{
		return std::ranges::find(myInstances, instance);
	}

	std::vector<Entity*>::iterator FindEntity(std::string_view name)
	{
		return std::ranges::find_if(myInstances, [&](const Entity* instance) -> bool {
			return (instance->myName == name);
		});
	}

	std::vector<Entity*>::iterator RemoveEntity(Entity* const instance)
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

	bool IsEntityExists(const Entity* instance) const
	{
		return myInstances.end() != std::ranges::find(myInstances, instance);
	}

	bool IsEntityExists(const std::vector<Entity*>::iterator& it) const
	{
		return myInstances.end() != it;
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
	bool isEnded;
};

template<typename Ty, typename ...ArgTy>
concept SceneType = std::derived_from<Ty, Scene> && std::constructible_from<Ty, ArgTy...>;
