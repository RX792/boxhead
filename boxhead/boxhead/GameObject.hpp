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
	void AddChild(GameObject* child)
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
	void AddSibling(GameObject* other)
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

	/// <summary>
	/// ��ǥ�� �����մϴ�.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	void MoveTo(const float& x, const float& y, const float& z)
	{
		localTransform.MoveTo(x, y, z);

		EnumerateTransform();
	}

	/// <summary>
	/// ��ǥ�� �����մϴ�.
	/// </summary>
	/// <param name="position"></param>
	void MoveTo(const glm::vec3& position)
	{
		MoveTo(position.x, position.y, position.z);
	}

	/// <summary>
	/// ��ǥ�� ���մϴ�.
	/// </summary>
	/// <param name="ax"></param>
	/// <param name="ay"></param>
	/// <param name="az"></param>
	void Translate(const float& ax, const float& ay, const float& az)
	{
		localTransform.Translate(ax, ay, az);

		EnumerateTransform();
	}

	/// <summary>
	/// ��ǥ�� ���մϴ�.
	/// </summary>
	/// <param name="vector"></param>
	void Translate(const glm::vec3& vector)
	{
		localTransform.Translate(vector);

		EnumerateTransform();
	}

	/// <summary>
	/// ȸ�� ������ ���մϴ�.
	/// </summary>
	/// <param name="pitch">X ����</param>
	/// <param name="yaw">Y ����</param>
	/// <param name="roll">Z ����</param>
	void Tilt(const float& pitch, const float& yaw, const float& roll)
	{
		localTransform.Tilt(pitch, yaw, roll);

		EnumerateTransform();
	}

	/// <summary>
	/// ȸ�� ������ �����մϴ�.
	/// </summary>
	/// <param name="pitch">X ����</param>
	/// <param name="yaw">Y ����</param>
	/// <param name="roll">Z ����</param>
	void Rotate(const float& pitch, const float& yaw, const float& roll)
	{
		localTransform.Rotate(pitch, yaw, roll);

		EnumerateTransform();
	}

	/// <summary>
	/// ��� ������ ������ �����մϴ�.
	/// </summary>
	/// <param name="scale"></param>
	void Scale(const float& scale)
	{
		localTransform.Scale(scale);
	}

	/// <summary>
	/// Ư���� ������ ������ �����մϴ�.
	/// </summary>
	/// <param name="scale"></param>
	void Scale(const float& xscale, const float& yscale, const float& zscale)
	{
		localTransform.Scale(xscale, yscale, zscale);
	}

	/// <summary>
	/// ���� ��ġ�� ��ȯ�մϴ�.
	/// </summary>
	/// <returns>��ġ ���� x, y, z</returns>
	glm::vec3 GetPosition() const
	{
		return localTransform.GetPosition();
	}

	/// <summary>
	/// ���� ȸ���� ��ȯ�մϴ�.
	/// </summary>
	/// <returns>����� ȸ��</returns>
	glm::quat GetRotation() const
	{
		return localTransform.GetRotation();
	}

	Transform localTransform;
	Transform worldTransform;

	GameObject* prevSibling;
	GameObject* nextSibling;
	GameObject* myParent;
	GameObject* myChild;

protected:
	virtual void EnumerateTransform()
	{
		worldTransform.Set(localTransform);

		if (nextSibling)
		{
			nextSibling->EnumerateTransform();
		}

		if (myChild)
		{
			myChild->UpdateTransform(worldTransform);
		}
	}

	void UpdateTransform(const Transform& parent_transform)
	{
		worldTransform.Set(parent_transform * localTransform);

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
