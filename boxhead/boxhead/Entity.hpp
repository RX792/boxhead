#pragma once
#include "GameObject.hpp"
#include "Model.hpp"
#include "SideCubeModel.hpp"

class Entity : public GameObject
{
public:
	template<typename Ty, typename ...ArgTy>
		requires EntityType<Ty, ArgTy...>
	static Ty* Instantiate(ArgTy&& ...args)
	{
		return new Ty{ std::forward<ArgTy>(args)... };
	}

	constexpr Entity(Model* const model_view = nullptr)
		: GameObject()
		, myName(), myHealth(), maxHealth()
		, myModel(model_view)
	{}

	Entity(Model* const model_view, const glm::vec3& position)
		: Entity(model_view)
	{
		MoveTo(position);
	}

	Entity(Model* const model_view, const float& x, const float& y, const float& z)
		: Entity(model_view)
	{
		MoveTo(x, y, z);
	}

	Entity(const glm::vec3& position)
		: Entity()
	{
		MoveTo(position);
	}

	Entity(const float& x, const float& y, const float& z)
		: Entity()
	{
		MoveTo(x, y, z);
	}

	virtual ~Entity()
	{}

	virtual void Start()
	{}

	virtual void Update(const float& delta_time)
	{}

	virtual void PrepareRendering()
	{
		GameObject::PrepareRendering();

		myModel->PrepareRendering();
	}

	virtual void Render(ogl::Uniform& world_uniform)
	{
		if (myChild)
		{
			myChild->Render(world_uniform);
		}

		if (nextSibling)
		{
			nextSibling->Render(world_uniform);
		}

		world_uniform.AssignMatrix4x4(worldTransform.myMatrix);
		myModel->Render();
	}

	Entity(const Entity& other) = default;
	Entity(Entity&& other) = default;
	Entity& operator=(const Entity& other) = default;
	Entity& operator=(Entity&& other) = default;

	std::string myName;
	float myHealth;
	float maxHealth;
	Model* myModel;
};

template<typename Ty, typename ...ArgTy>
concept EntityType = std::derived_from<Ty, Entity> && std::constructible_from<Ty, ArgTy...>;
