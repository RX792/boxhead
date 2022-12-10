#pragma once
#include "Entity.hpp"

class Player : public Entity
{
public:
	constexpr Player()
		: Entity()
	{}

	virtual ~Player()
	{}

	void Awake()
	{

	}

	void Start() override
	{

	}

	void Update(const float& delta_time) override
	{


	}
};
