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
	/// 자식을 추가합니다.
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
	/// 형제를 추가합니다.
	/// </summary>
	/// <param name="other">게임 인스턴스</param>
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
	/// 다음 형제에게 부모의 관계를 넘겨줍니다.
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
	/// 모든 자식 개체를 파괴합니다.
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
	/// 모든 다음 형제 개체를 파괴합니다.
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
	/// 좌표를 지정합니다.
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
	/// 좌표를 지정합니다.
	/// </summary>
	/// <param name="position"></param>
	void MoveTo(const glm::vec3& position)
	{
		MoveTo(position.x, position.y, position.z);
	}

	/// <summary>
	/// 좌표를 더합니다.
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
	/// 좌표를 더합니다.
	/// </summary>
	/// <param name="vector"></param>
	void Translate(const glm::vec3& vector)
	{
		localTransform.Translate(vector);

		EnumerateTransform();
	}

	/// <summary>
	/// 회전 각도를 더합니다.
	/// </summary>
	/// <param name="pitch">X 각도</param>
	/// <param name="yaw">Y 각도</param>
	/// <param name="roll">Z 각도</param>
	void Tilt(const float& pitch, const float& yaw, const float& roll)
	{
		localTransform.Tilt(pitch, yaw, roll);

		EnumerateTransform();
	}

	/// <summary>
	/// 회전 각도를 지정합니다.
	/// </summary>
	/// <param name="pitch">X 각도</param>
	/// <param name="yaw">Y 각도</param>
	/// <param name="roll">Z 각도</param>
	void Rotate(const float& pitch, const float& yaw, const float& roll)
	{
		localTransform.Rotate(pitch, yaw, roll);

		EnumerateTransform();
	}

	/// <summary>
	/// 모든 축으로 비율을 조정합니다.
	/// </summary>
	/// <param name="scale"></param>
	void Scale(const float& scale)
	{
		localTransform.Scale(scale);
	}

	/// <summary>
	/// 특정한 축으로 비율을 조정합니다.
	/// </summary>
	/// <param name="scale"></param>
	void Scale(const float& xscale, const float& yscale, const float& zscale)
	{
		localTransform.Scale(xscale, yscale, zscale);
	}

	/// <summary>
	/// 현재 위치를 반환합니다.
	/// </summary>
	/// <returns>위치 벡터 x, y, z</returns>
	glm::vec3 GetPosition() const
	{
		return localTransform.GetPosition();
	}

	/// <summary>
	/// 현재 회전을 반환합니다.
	/// </summary>
	/// <returns>사원수 회전</returns>
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
