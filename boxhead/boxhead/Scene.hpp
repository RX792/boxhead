#pragma once
#include "Entity.hpp"

class Scene
{
public:
	constexpr Scene()
		: myInstances()
	{
		myInstances.reserve(10);
	}

	virtual ~Scene()
	{}

	virtual void Awake()
	{
		
	}
	
	virtual void Start()
	{
		auto& aa = myInstances.emplace_back();
		aa->MoveTo(1.0f, 0.0f, 1.0f);

		auto& bb = myInstances.emplace_back();
		bb->MoveTo(0.0f, 00.0f, 0.0f);

		auto& cc = myInstances.emplace_back();
		cc->MoveTo(3.0f, 0.0f, -1.0f);

		auto& dd = myInstances.emplace_back();
		dd->MoveTo(4.0f, 0.0f, -2.0f);

		auto& ee = myInstances.emplace_back();
		ee->MoveTo(5.0f, 0.0f, -3.0f);
	}

	virtual void Update(const float& delta_time)
	{
		
	}
	
	virtual void PrepareRendering()
	{
		
	}

	virtual void Render()
	{
		for (auto& instance : myInstances)
		{
			instance->PrepareRendering(uniform_mat_world);
			instance->Render();
		}
	}

	std::vector<Entity*> myInstances;
};
