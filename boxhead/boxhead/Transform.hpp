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

	constexpr Transform& operator=(const glm::mat4& mat)
	{
		myMatrix = mat;

		return *this;
	}

	constexpr Transform& operator=(const Transform& other)
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
	/// Ư���� ȸ�� ���� ���� �Ÿ���ŭ �̵��մϴ�.
	/// </summary>
	/// <param name="axis">�̵� ��</param>
	/// <param name="quaternion">����� ȸ��</param>
	/// <param name="distance">�̵� �Ÿ�</param>
	inline void MoveTo(const glm::vec3& axis, const glm::mat4& rotation, const float& distance)
	{
		const auto vector = glm::vec4{ axis * distance, 1.0f };
		//const auto my_mat = ogl::Rotate(ogl::identity, myPitch, myYaw, myRoll);
		const auto direction = GetRotation();

		Translate(direction * vector);
		//auto toward = myMatrix * glm::vec4{ axis, 1.0f };
		//auto toward = glm::mat4{ quaternion } * glm::vec4{ axis, 1.0f };
		//auto toward = rotation * glm::vec4{ axis, 0.0f };

		//Translate(glm::normalize(toward) * distance);
		//Translate(glm::normalize(quaternion * distance * axis));
	}

	/// <summary>
	/// Ư���� ���� ���� �Ÿ���ŭ �̵��մϴ�.
	/// </summary>
	/// <param name="axis">�̵� ��</param>
	/// <param name="distance">�̵� �Ÿ�</param>
	inline void MoveTo(const glm::vec3& axis, const float& distance)
	{
		MoveTo(axis, GetRotation(), distance);
	}

	/// <summary>
	/// z���� ���� �̵��մϴ�.
	/// </summary>
	/// <param name="distance">�̵� �Ÿ�</param>
	inline void MoveForward(const float& distance)
	{
		MoveTo(ogl::forward, distance);
	}

	/// <summary>
	/// y���� ���� �̵��մϴ�.
	/// </summary>
	/// <param name="distance">�̵� �Ÿ�</param>
	inline void MoveUp(const float& distance)
	{
		MoveTo(ogl::up, distance);
	}

	/// <summary>
	/// x���� ���� �̵��մϴ�.
	/// </summary>
	/// <param name="distance"></param>
	inline void MoveStrife(const float& distance)
	{
		MoveTo(ogl::right, distance);
	}

	/// <summary>
	/// ��ǥ�� �����մϴ�.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	constexpr void SetPosition(const float& x, const float& y, const float& z)
	{
		myMatrix[3][0] = x;
		myMatrix[3][1] = y;
		myMatrix[3][2] = z;
	}

	/// <summary>
	/// ��ǥ�� �����մϴ�.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	constexpr void SetPosition(const glm::vec3& position)
	{
		SetPosition(position.x, position.y, position.z);
	}

	/// <summary>
	/// ��ǥ�� ���մϴ�.
	/// </summary>
	/// <param name="ax"></param>
	/// <param name="ay"></param>
	/// <param name="az"></param>
	constexpr void Translate(const float& ax, const float& ay, const float& az)
	{
		myMatrix[3][0] += ax;
		myMatrix[3][1] += ay;
		myMatrix[3][2] += az;
	}

	/// <summary>
	/// ��ǥ�� ���մϴ�.
	/// </summary>
	/// <param name="vector"></param>
	constexpr void Translate(const glm::vec3& vector)
	{
		myMatrix[3] += glm::vec4{ vector, 0.0f };
	}

	void RotateX(const float& pitch)
	{
		myMatrix = glm::rotate(myMatrix, glm::radians(pitch), ogl::right);
	}

	void RotateY(const float& yaw)
	{
		myMatrix = glm::rotate(myMatrix, glm::radians(yaw), ogl::up);
	}

	void RotateZ(const float& roll)
	{
		myMatrix = glm::rotate(myMatrix, glm::radians(roll), ogl::forward);
	}

	/// <summary>
	/// ȸ�� ������ ���մϴ�.
	/// </summary>
	/// <param name="pitch"></param>
	/// <param name="yaw"></param>
	/// <param name="roll"></param>
	void Rotate(const float& pitch, const float& yaw, const float& roll)
	{
		RotateY(yaw);
		RotateX(pitch);
		RotateZ(roll);
	}

	/// <summary>
	/// ȸ�� ������ �����մϴ�.
	/// </summary>
	/// <param name="pitch"></param>
	/// <param name="yaw"></param>
	/// <param name="roll"></param>
	void SetRotation(const float& pitch, const float& yaw, const float& roll)
	{
		const glm::vec4& origin = myMatrix[3];
		const glm::vec3 position = { origin[0], origin[1], origin[2] };

		myMatrix = ogl::identity;

		// T R S
		RotateY(yaw);
		RotateX(pitch);
		RotateZ(roll);
		SetPosition(position);
	}

	/// <summary>
	/// X ������ ������ �����մϴ�.
	/// </summary>
	/// <param name="scale"></param>
	void ScaleX(const float& scale)
	{
		myMatrix = glm::scale(myMatrix, glm::vec3{ scale, 1.0f, 1.0f });
	}

	/// <summary>
	/// Y ������ ������ �����մϴ�.
	/// </summary>
	/// <param name="scale"></param>
	void ScaleY(const float& scale)
	{
		myMatrix = glm::scale(myMatrix, glm::vec3{ 1.0f, scale, 1.0f });
	}

	/// <summary>
	/// Z ������ ������ �����մϴ�.
	/// </summary>
	/// <param name="scale"></param>
	void ScaleZ(const float& scale)
	{
		myMatrix = glm::scale(myMatrix, glm::vec3{ 1.0f, 1.0f, scale });
	}

	/// <summary>
	/// ��� ������ ������ �����մϴ�.
	/// </summary>
	/// <param name="scale"></param>
	void Scale(const float& scale)
	{
		myMatrix = glm::scale(myMatrix, glm::vec3{ scale });
	}

	/// <summary>
	/// ��� ������ ������ �����մϴ�.
	/// </summary>
	/// <param name="scale"></param>
	void Scale(const float& xscale, const float& yscale, const float& zscale)
	{
		myMatrix = glm::scale(myMatrix, glm::vec3{ xscale, yscale, zscale });
	}

	/// <summary>
	/// ���� ��ġ�� ��ȯ�մϴ�.
	/// </summary>
	/// <returns>��ġ ���� x, y, z</returns>
	constexpr glm::vec3 GetPosition() const
	{
		return glm::vec3{ myMatrix[3] };
	}

	/// <summary>
	/// ���� ȸ���� ��ȯ�մϴ�.
	/// </summary>
	/// <returns></returns>
	glm::mat4 GetRotation() const
	{
		glm::mat4 result = myMatrix;
		result[3] = glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f };

		return result;
	}

	/// <summary>
	/// ���� ����� ȸ������ ��ȯ�մϴ�.
	/// </summary>
	/// <returns>����� ȸ��</returns>
	glm::quat GetQuaternion() const
	{
		return glm::quat_cast(myMatrix);
	}

	glm::mat4 myMatrix;
};
