#pragma once
#include "GameObject.hpp"
#include "ModelView.hpp"
#include "BoxCollider.hpp"

class Entity : public GameObject
{
public:
	template<typename Ty, typename ...ArgTy>
		requires EntityType<Ty, ArgTy...>
	static decltype(auto) Instantiate(ArgTy&& ...args)
	{
		return new Ty{ std::forward<ArgTy>(args)... };
	}

	constexpr Entity()
		: GameObject()
		, myName(), myHealth(), maxHealth()
		, myModel(-1)
		, myCollider(nullptr)
	{}
	
	constexpr Entity(const ModelView& model_view)
		: GameObject()
		, myName(), myHealth(), maxHealth()
		, myModel(model_view)
		, myCollider(nullptr)
	{}

	Entity(const ModelView& model_view, const glm::vec3& position)
		: Entity(model_view)
	{
		MoveTo(position);
	}

	Entity(const ModelView& model_view, const float& x, const float& y, const float& z)
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

		if (myModel.IsAvailable())
		{
			myModel.PrepareRendering();
		}
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
		if (myModel.IsAvailable())
		{
			myModel.Render();
		}
	}

#pragma region �浹
	/// <summary>
	/// �浹ü�� �����մϴ�.
	/// </summary>
	/// <param name="collider">�浹ü</param>
	constexpr void SetCollider(BoxCollider* const collider)
	{
		if (!collider) return;

		myCollider = collider;
	}

	/// <summary>
	/// �浹ü�� �����մϴ�.
	/// </summary>
	constexpr void DetachCollider()
	{
		if (myCollider)
		{
			myCollider = nullptr;
		}
	}

	/// <summary>
	/// �浹ü�� ��ȯ�մϴ�.
	/// </summary>
	/// <returns></returns>
	constexpr BoxCollider* GetCollider()
	{
		return myCollider;
	}

	/// <summary>
	/// �浹ü�� ��ȯ�մϴ�.
	/// </summary>
	/// <returns></returns>
	constexpr const BoxCollider* GetCollider() const
	{
		return myCollider;
	}

	/// <summary>
	/// �浹 �˻縦 �����մϴ�.
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	bool IsCollideWith(const Collider* const other) const
	{
		const auto place = WhereCollideWith(other);

		if (wrongCollisionCoord == place)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	/// <summary>
	/// �浹�� ��ġ�� ��ȯ�մϴ�.
	/// </summary>
	/// <param name="other">�ٸ� �浹ü</param>
	/// <returns>���� ��ǥ���� �浹 ����</returns>
	glm::vec3 WhereCollideWith(const Collider* const other) const
	{
		return wrongCollisionCoord;
	}
#pragma endregion

	Entity(const Entity& other) = default;
	Entity(Entity&& other) = default;
	Entity& operator=(const Entity& other) = default;
	Entity& operator=(Entity&& other) = default;

	std::string myName;
	float myHealth;
	float maxHealth;
	ModelView myModel;

	BoxCollider* myCollider;
};

template<typename Ty, typename ...ArgTy>
concept EntityType = std::derived_from<std::decay_t<Ty>, Entity> && std::constructible_from<std::decay_t<Ty>, ArgTy...>;
