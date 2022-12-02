#pragma once
#include "Transform.hpp"

class GameObject
{
public:
	template<typename Ty, typename ...ArgTy>
		requires GameObjectType<Ty, ArgTy...>
	static Ty* Instantiate(ArgTy&& ...args)
	{
		return new Ty{ std::forward<ArgTy>(args)... };
	}

	constexpr GameObject()
		: localTransform(), worldTransform()
		, prevSibling(nullptr), nextSibling(nullptr)
		, myParent(nullptr), myChild(nullptr)
	{}

	virtual ~GameObject()
	{
		DestroyChildren();
		GiveInheritance();

		if (prevSibling)
		{
			prevSibling->nextSibling = nextSibling;
		}
	}

	virtual void Start()
	{}

	virtual void Update(const float& delta_time)
	{}

	virtual void PrepareRendering()
	{
		EnumerateTransform();
	}

	virtual void Render(ogl::Uniform& world_uniform)
	{}

	/// <summary>
	/// �ڽ��� �߰��մϴ�.
	/// </summary>
	/// <param name="child"></param>
	void AddChild(Entity* child)
	{
		if (!child) return;

		if (!myChild)
		{
			myChild = child;
		}
		else
		{
			myChild->AddSibling(child);
		}

		child->myParent = this;
	}

	/// <summary>
	/// ������ �߰��մϴ�.
	/// </summary>
	/// <param name="other">���� �ν��Ͻ�</param>
	void AddSibling(Entity* other)
	{
		if (!other) return;

		if (!nextSibling)
		{
			nextSibling = other;

			other->prevSibling = this;
		}
		else
		{
			nextSibling->AddSibling(other);
		}
	}

	/// <summary>
	/// ���� �������� �θ��� ���踦 �Ѱ��ݴϴ�.
	/// </summary>
	void GiveInheritance()
	{
		if (myParent)
		{
			if (myParent->myChild == this)
			{
				myParent->myChild = nextSibling;
			}
		}
	}

	/// <summary>
	/// ��� �ڽ� ��ü�� �ı��մϴ�.
	/// </summary>
	void DestroyChildren()
	{
		if (myChild)
		{
			myChild->DestroyChildren();

			delete myChild;
			myChild = nullptr;
		}
	}

	/// <summary>
	/// ��� ���� ���� ��ü�� �ı��մϴ�.
	/// </summary>
	void DestroySiblings()
	{
		if (nextSibling)
		{
			nextSibling->DestroySiblings();

			delete nextSibling;
			nextSibling = nullptr;
		}
	}

	Transform localTransform;
	Transform worldTransform;

	GameObject* prevSibling;
	GameObject* nextSibling;
	GameObject* myParent;
	GameObject* myChild;

protected:
	void EnumerateTransform()
	{
		if (nextSibling)
		{
			nextSibling->EnumerateTransform();
		}

		if (myChild)
		{
			myChild->UpdateTransform(worldTransform);
		}
	}

	void UpdateTransform(const glm::Transform& parent_transform)
	{
		worldMatrix = parent_matrix * localMatrix;

		if (nextSibling)
		{
			nextSibling->UpdateTransform(parent_transform);
		}

		if (myChild)
		{
			myChild->UpdateTransform(worldTransform);
		}
	}
};

template<typename Ty, typename ...ArgTy>
concept GameObjectType = std::derived_from<Ty, GameObject> && std::constructible_from<Ty, ArgTy...>;
