#pragma once
#include <OpenGL.hpp>

#include "box.h"

class Entity
{
public:
	Entity()
		: myName()
		, myHealth(), maxHealth()
		, localMatrix(ogl::identity), worldMatrix(ogl::identity)
		, mySibling(nullptr), myChild(nullptr)
		, testBox(0, 0, 0)
	{}

	virtual ~Entity() = default;

	virtual void PrepareRendering()
	{
		EnumerateTransform();

		testBox.x = localMatrix[3][0];
		testBox.y = localMatrix[3][1];
		testBox.z = localMatrix[3][2];
	}

	virtual void Render()
	{
		PrepareRendering();

		testBox.draw();
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

	void MoveTo(const float& x, const float& y, const float& z)
	{
		//localMatrix = glm::translate(localMatrix, x, y, z);
		localMatrix[3][0] = x;
		localMatrix[3][1] = y;
		localMatrix[3][2] = z;
		
		UpdateTransform(localMatrix);
	}

	void Translate(const float& ax, const float& ay, const float& az)
	{
		localMatrix[3][0] += ax;
		localMatrix[3][1] += ay;
		localMatrix[3][2] += az;

		UpdateTransform(localMatrix);
	}

	void Translate(const glm::vec3& vector)
	{
		localMatrix[3] += vector;

		UpdateTransform(localMatrix);
	}

	void Tilt(const float& pitch, const float& yaw, const float& roll)
	{
		localMatrix = glm::rotate(localMatrix, yaw, ogl::up);
		localMatrix = glm::rotate(localMatrix, pitch, ogl::right);
		localMatrix = glm::rotate(localMatrix, roll, ogl::look);

		UpdateTransform(localMatrix);
	}

	void Rotate(const float& pitch, const float& yaw, const float& roll)
	{
		const auto translation = localMatrix[3];

		localMatrix = ogl::identity;
		localMatrix[3] = translation;

		localMatrix = glm::rotate(localMatrix, yaw, ogl::up);
		localMatrix = glm::rotate(localMatrix, pitch, ogl::right);
		localMatrix = glm::rotate(localMatrix, roll, ogl::look);

		UpdateTransform(localMatrix);
	}

	std::string myName;
	float myHealth;
	float maxHealth;

	glm::mat4 localMatrix;
	glm::mat4 worldMatrix;

	Entity* mySibling;
	Entity* myChild;
	
	Box testBox;
};
