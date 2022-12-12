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
	/// 특정한 회전 축을 따라 거리만큼 이동합니다.
	/// </summary>
	/// <param name="axis">이동 축</param>
	/// <param name="quaternion">사원수 회전</param>
	/// <param name="distance">이동 거리</param>
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
	/// 특정한 축을 따라 거리만큼 이동합니다.
	/// </summary>
	/// <param name="axis">이동 축</param>
	/// <param name="distance">이동 거리</param>
	inline void MoveTo(const glm::vec3& axis, const float& distance)
	{
		MoveTo(axis, GetRotation(), distance);
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
	constexpr void SetPosition(const float& x, const float& y, const float& z)
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
	constexpr void SetPosition(const glm::vec3& position)
	{
		SetPosition(position.x, position.y, position.z);
	}

	/// <summary>
	/// 좌표를 더합니다.
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
	/// 좌표를 더합니다.
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
	/// 회전 각도를 더합니다.
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
	/// 회전 각도를 지정합니다.
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

	/// <summary>
	/// 현재 위치를 반환합니다.
	/// </summary>
	/// <returns>위치 벡터 x, y, z</returns>
	constexpr glm::vec3 GetPosition() const
	{
		return glm::vec3{ myMatrix[3] };
	}

	/// <summary>
	/// 현재 회전을 반환합니다.
	/// </summary>
	/// <returns></returns>
	glm::mat4 GetRotation() const
	{
		glm::mat4 result = myMatrix;
		result[3] = glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f };

		return result;
	}

	/// <summary>
	/// 현재 사원수 회전각을 반환합니다.
	/// </summary>
	/// <returns>사원수 회전</returns>
	glm::quat GetQuaternion() const
	{
		return glm::quat_cast(myMatrix);
	}

	glm::mat4 myMatrix;
};
