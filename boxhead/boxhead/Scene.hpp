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
