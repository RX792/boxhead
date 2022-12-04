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

	Entity()
		: GameObject()
		, myName(), myHealth(), maxHealth()
		, myModel(nullptr)
	{}

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
	{
		myModel = new SideCubeModel{ 1 };
	}

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
