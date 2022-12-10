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

	Entity* Raycast(GameObject obj_list[], const size_t& count, const float& distance, const glm::vec3& direction) const
	{

	}

	GameObject* Raycast(const GameObject& target, const float& distance, const glm::vec3& direction) const
	{


		return nullptr;
	}
};
