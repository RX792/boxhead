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
		: GameObject("GameObject")
	{}

	constexpr GameObject(std::string_view name)
		: myName(name)
		, localTransform(), worldTransform()
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

#pragma region 파이프라인
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
#pragma endregion

#pragma region 계층 구조
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

	GameObject* FindChild(std::string_view name) const
	{
		if (myChild)
		{
			if (myChild->myName == name)
				return myChild;

			if (GameObject* sibling = myChild->FindSibling(name))
				return sibling;

			if (GameObject* child = myChild->FindChild(name))
				return child;
		}

		return nullptr;
	}

	GameObject* FindSibling(std::string_view name) const
	{
		if (nextSibling)
		{
			if (nextSibling->myName == name)
				return nextSibling;

			if (GameObject* sibling = nextSibling->FindSibling(name))
				return sibling;
		}

		return nullptr;
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
#pragma endregion

#pragma region 변환
	/// <summary>
	/// 특정한 회전 축을 따라 거리만큼 이동합니다.
	/// </summary>
	/// <param name="axis">이동 축</param>
	/// <param name="rotation">회전</param>
	/// <param name="distance">이동 거리</param>
	inline void MoveTo(const glm::vec3& axis, const glm::mat4& rotation, const float& distance)
	{
		localTransform.MoveTo(axis, rotation, distance);

		EnumerateTransform();
	}

	/// <summary>
	/// z축을 따라 이동합니다.
	/// </summary>
	/// <param name="rotation">회전</param>
	/// <param name="distance">이동 거리</param>
	inline void MoveForward(const glm::mat4& rotation, const float& distance)
	{
		MoveTo(ogl::forward, rotation, distance);
	}

	/// <summary>
	/// y축을 따라 이동합니다.
	/// </summary>
	/// <param name="rotation">회전</param>
	/// <param name="distance">이동 거리</param>
	inline void MoveUp(const glm::mat4& rotation, const float& distance)
	{
		MoveTo(ogl::up, rotation, distance);
	}

	/// <summary>
	/// x축을 따라 이동합니다.
	/// </summary>
	/// <param name="rotation">회전</param>
	/// <param name="distance"></param>
	inline void MoveStrife(const glm::mat4& rotation, const float& distance)
	{
		MoveTo(ogl::right, rotation, distance);
	}

	/// <summary>
	/// 특정한 축을 따라 거리만큼 이동합니다.
	/// </summary>
	/// <param name="axis">이동 축</param>
	/// <param name="distance">이동 거리</param>
	inline void MoveTo(const glm::vec3& axis, const float& distance)
	{
		localTransform.MoveTo(axis, distance);

		EnumerateTransform();
	}

	/// <summary>
	/// z축을 따라 이동합니다.
	/// </summary>
	/// <param name="distance">이동 거리</param>
	inline void MoveForward(const float& distance)
	{
		MoveTo(ogl::forward, distance);
	}

	/// <summary>
	/// y축을 따라 이동합니다.
	/// </summary>
	/// <param name="distance">이동 거리</param>
	inline void MoveUp(const float& distance)
	{
		MoveTo(ogl::up, distance);
	}

	/// <summary>
	/// x축을 따라 이동합니다.
	/// </summary>
	/// <param name="distance"></param>
	inline void MoveStrife(const float& distance)
	{
		MoveTo(ogl::right, distance);
	}

	/// <summary>
	/// 좌표를 지정합니다.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	void SetPosition(const float& x, const float& y, const float& z)
	{
		localTransform.SetPosition(x, y, z);

		EnumerateTransform();
	}

	/// <summary>
	/// 좌표를 지정합니다.
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const glm::vec3& position)
	{
		SetPosition(position.x, position.y, position.z);
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
	void Rotate(const float& pitch, const float& yaw, const float& roll)
	{
		localTransform.Rotate(pitch, yaw, roll);

		EnumerateTransform();
	}

	/// <summary>
	/// 회전 각도를 지정합니다.
	/// </summary>
	/// <param name="pitch">X 각도</param>
	/// <param name="yaw">Y 각도</param>
	/// <param name="roll">Z 각도</param>
	void SetRotation(const float& pitch, const float& yaw, const float& roll)
	{
		localTransform.SetRotation(pitch, yaw, roll);

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
	constexpr glm::vec3 GetPosition() const
	{
		return localTransform.GetPosition();
	}

	/// <summary>
	/// 현재 회전을 반환합니다.
	/// </summary>
	/// <returns>사원수 회전</returns>
	glm::quat GetQuaternion() const
	{
		return localTransform.GetQuaternion();
	}
#pragma endregion

	Transform localTransform;
	Transform worldTransform;

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

	std::string myName;
	GameObject* prevSibling;
	GameObject* nextSibling;
	GameObject* myParent;
	GameObject* myChild;

	static inline constexpr glm::vec3 wrongCollisionCoord = glm::vec3{ std::numeric_limits<float>::min() };
};

template<typename Ty, typename ...ArgTy>
concept GameObjectType = std::derived_from<Ty, GameObject> && std::constructible_from<Ty, ArgTy...>;
