#pragma once

class Transform
{
public:
	constexpr Transform()
		: myMatrix(ogl::identity)
	{}

	explicit constexpr Transform(const glm::mat4& mat)
		: myMatrix(mat)
	{}

	constexpr void Set(const glm::mat4& mat)
	{
		myMatrix = mat;
	}

	constexpr void Set(const Transform& other)
	{
		myMatrix = other.myMatrix;
	}

	Transform& Multiply(const glm::mat4& mat)
	{
		const auto result = mat * myMatrix;
		myMatrix = result;

		return *this;
		;
	}

	Transform& Multiply(const Transform& other)
	{
		const auto result = other.myMatrix * myMatrix;
		myMatrix = result;

		return *this;
	}

	Transform operator+(const glm::mat4& mat) const
	{
		return Transform{ myMatrix + mat };
	}

	Transform operator+(const Transform& other) const
	{
		return Transform{ myMatrix + other.myMatrix };
	}

	Transform operator-(const glm::mat4& mat) const
	{
		return Transform{ myMatrix - mat };
	}

	Transform operator-(const Transform& other) const
	{
		return Transform{ myMatrix - other.myMatrix };
	}

	Transform operator*(const glm::mat4& mat) const
	{
		return Transform{ myMatrix * mat };
	}

	Transform operator*(const Transform& other) const
	{
		return Transform{ myMatrix * other.myMatrix };
	}

	Transform& operator=(const glm::mat4& mat)
	{
		myMatrix = mat;

		return *this;
	}

	Transform& operator=(const Transform& other)
	{
		myMatrix = other.myMatrix;

		return *this;
	}

	Transform& operator+=(const glm::mat4& mat)
	{
		myMatrix += mat;

		return *this;
	}

	Transform& operator+=(const Transform& other)
	{
		myMatrix += other.myMatrix;

		return *this;
	}

	Transform& operator-=(const glm::mat4& mat)
	{
		myMatrix -= mat;

		return *this;
	}

	Transform& operator-=(const Transform& other)
	{
		myMatrix -= other.myMatrix;

		return *this;
	}

	Transform& operator*=(const glm::mat4& mat)
	{
		myMatrix *= mat;

		return *this;
	}

	Transform& operator*=(const Transform& other)
	{
		myMatrix *= other.myMatrix;

		return *this;
	}

	/// <summary>
	/// 좌표를 지정합니다.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	void MoveTo(const float& x, const float& y, const float& z)
	{
		myMatrix[3][0] = x;
		myMatrix[3][1] = y;
		myMatrix[3][2] = z;
	}

	/// <summary>
	/// 좌표를 지정합니다.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
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
		myMatrix[3][0] += ax;
		myMatrix[3][1] += ay;
		myMatrix[3][2] += az;
	}

	/// <summary>
	/// 좌표를 더합니다.
	/// </summary>
	/// <param name="vector"></param>
	void Translate(const glm::vec3& vector)
	{
		myMatrix[3] += glm::vec4{ vector, 0.0f };
	}

	void RotateX(const float& pitch)
	{
		myMatrix = glm::rotate(myMatrix, pitch, ogl::right);
	}

	void RotateY(const float& yaw)
	{
		myMatrix = glm::rotate(myMatrix, yaw, ogl::up);
	}

	void RotateZ(const float& roll)
	{
		myMatrix = glm::rotate(myMatrix, roll, ogl::forward);
	}

	/// <summary>
	/// 회전 각도를 더합니다.
	/// </summary>
	/// <param name="pitch"></param>
	/// <param name="yaw"></param>
	/// <param name="roll"></param>
	void Tilt(const float& pitch, const float& yaw, const float& roll)
	{
		RotateY(yaw);
		RotateX(pitch);
		RotateZ(roll);
	}

	/// <summary>
	/// 회전 각도를 지정합니다.
	/// </summary>
	/// <param name="pitch"></param>
	/// <param name="yaw"></param>
	/// <param name="roll"></param>
	void Rotate(const float& pitch, const float& yaw, const float& roll)
	{
		const glm::vec4& origin = myMatrix[3];
		const glm::vec3 position = { origin[0], origin[1], origin[2] };

		myMatrix = ogl::identity;

		// T R S
		RotateY(yaw);
		RotateX(pitch);
		RotateZ(roll);
		MoveTo(position);
	}

	/// <summary>
	/// X 축으로 비율을 조정합니다.
	/// </summary>
	/// <param name="scale"></param>
	void ScaleX(const float& scale)
	{
		myMatrix = glm::scale(myMatrix, glm::vec3{ scale, 1.0f, 1.0f });
	}

	/// <summary>
	/// Y 축으로 비율을 조정합니다.
	/// </summary>
	/// <param name="scale"></param>
	void ScaleY(const float& scale)
	{
		myMatrix = glm::scale(myMatrix, glm::vec3{ 1.0f, scale, 1.0f });
	}

	/// <summary>
	/// Z 축으로 비율을 조정합니다.
	/// </summary>
	/// <param name="scale"></param>
	void ScaleZ(const float& scale)
	{
		myMatrix = glm::scale(myMatrix, glm::vec3{ 1.0f, 1.0f, scale });
	}

	/// <summary>
	/// 모든 축으로 비율을 조정합니다.
	/// </summary>
	/// <param name="scale"></param>
	void Scale(const float& scale)
	{
		myMatrix = glm::scale(myMatrix, glm::vec3{ scale });
	}

	/// <summary>
	/// 모든 축으로 비율을 조정합니다.
	/// </summary>
	/// <param name="scale"></param>
	void Scale(const float& xscale, const float& yscale, const float& zscale)
	{
		myMatrix = glm::scale(myMatrix, glm::vec3{ xscale, yscale, zscale });
	}

	glm::mat4 myMatrix;
};
