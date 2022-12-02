#pragma once
#include <OpenGL.hpp>
#include <Uniform.hpp>

class Entity
{
public:
	Entity()
		: myName()
		, myHealth(), maxHealth()
		, localMatrix(ogl::identity), worldMatrix(ogl::identity)
		, mySibling(nullptr), myChild(nullptr)
	{}

	Entity(const Entity& other) = default;
	Entity(Entity&& other) = default;
	Entity& operator=(const Entity& other) = default;
	Entity& operator=(Entity&& other) = default;

	virtual ~Entity()
	{}

	virtual void PrepareRendering(ogl::Uniform& world_uniform)
	{
		EnumerateTransform();

		world_uniform.AssignMatrix4x4(worldMatrix);
	}

	virtual void Render()
	{
		ogl::Render(ogl::PRIMITIVE_TYPES::TRIANGLE_FAN, 24, 0);
	}

	void EnumerateTransform()
	{
		if (mySibling)
		{
			mySibling->EnumerateTransform();
		}

		if (myChild)
		{
			myChild->UpdateTransform(worldMatrix);
		}
	}

	void UpdateTransform(const glm::mat4& parent_matrix)
	{
		worldMatrix = parent_matrix * localMatrix;

		if (mySibling)
		{
			mySibling->UpdateTransform(parent_matrix);
		}

		if (myChild)
		{
			myChild->UpdateTransform(worldMatrix);
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
		//localMatrix = glm::translate(localMatrix, x, y, z);
		localMatrix[3][0] = x;
		localMatrix[3][1] = y;
		localMatrix[3][2] = z;

		UpdateTransform(localMatrix);
	}

	/// <summary>
	/// 좌표를 더합니다.
	/// </summary>
	/// <param name="ax"></param>
	/// <param name="ay"></param>
	/// <param name="az"></param>
	void Translate(const float& ax, const float& ay, const float& az)
	{
		localMatrix[3][0] += ax;
		localMatrix[3][1] += ay;
		localMatrix[3][2] += az;

		UpdateTransform(localMatrix);
	}

	/// <summary>
	/// 좌표를 더합니다.
	/// </summary>
	/// <param name="vector"></param>
	void Translate(const glm::vec3& vector)
	{
		//localMatrix[3] += vector;

		UpdateTransform(localMatrix);
	}

	/// <summary>
	/// 회전 각도를 더합니다.
	/// </summary>
	/// <param name="pitch"></param>
	/// <param name="yaw"></param>
	/// <param name="roll"></param>
	void Tilt(const float& pitch, const float& yaw, const float& roll)
	{
		localMatrix = glm::rotate(localMatrix, yaw, ogl::up);
		localMatrix = glm::rotate(localMatrix, pitch, ogl::right);
		localMatrix = glm::rotate(localMatrix, roll, ogl::look);

		UpdateTransform(localMatrix);
	}

	/// <summary>
	/// 회전 각도를 지정합니다.
	/// </summary>
	/// <param name="pitch"></param>
	/// <param name="yaw"></param>
	/// <param name="roll"></param>
	void Rotate(const float& pitch, const float& yaw, const float& roll)
	{
		const glm::vec4 origin = localMatrix[3];
		const glm::vec3 translation = { origin[0], origin[1], origin[2] };

		localMatrix = ogl::identity;

		localMatrix = glm::rotate(localMatrix, yaw, ogl::up);
		localMatrix = glm::rotate(localMatrix, pitch, ogl::right);
		localMatrix = glm::rotate(localMatrix, roll, ogl::look);
		localMatrix = glm::translate(localMatrix, translation);

		UpdateTransform(localMatrix);
	}

	std::string myName;
	float myHealth;
	float maxHealth;

	glm::mat4 localMatrix;
	glm::mat4 worldMatrix;

	Entity* mySibling;
	Entity* myChild;
};
