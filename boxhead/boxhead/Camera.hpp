#pragma once
#include "GameObject.hpp"

namespace camera
{
	enum class CameraLookOption
	{
		POSITION,
		LOCKED_POSITION,
		DIRECTION,
	};

	class Camera
	{
	public:
		constexpr Camera(const glm::vec3& up)
			: lookOption(CameraLookOption::DIRECTION)
			, lookPosition(), lookDirection(ogl::forward)
			, viewMatrix()
			, worldUp(up), worldTransform(ogl::identity)
			, cameraRight(), cameraUp(), cameraLook()
		{}

		constexpr void SetLookAt(const glm::vec3& local_position)
		{
			SetOption(CameraLookOption::POSITION);
			lookPosition = local_position;
		}

		constexpr void SetLockViewAt(const glm::vec3& world_position)
		{
			SetOption(CameraLookOption::LOCKED_POSITION);
			lookPosition = world_position;
		}

		constexpr void SetLookDirection(const glm::vec3& direction)
		{
			SetOption(CameraLookOption::DIRECTION);
			lookDirection = direction;
		}

		constexpr void SetOption(const CameraLookOption& option)
		{
			lookOption = option;
		}

		/// <summary>
		/// ��ǥ�� �����մϴ�.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="z"></param>
		void MoveTo(const float& x, const float& y, const float& z)
		{
			worldTransform.MoveTo(x, y, z);

			UpdateCamera();
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
			worldTransform.Translate(ax, ay, az);

			UpdateCamera();
		}

		/// <summary>
		/// ��ǥ�� ���մϴ�.
		/// </summary>
		/// <param name="vector"></param>
		void Translate(const glm::vec3& vector)
		{
			worldTransform.Translate(vector);

			UpdateCamera();
		}

		/// <summary>
		/// ȸ�� ������ ���մϴ�.
		/// </summary>
		/// <param name="pitch">X ����</param>
		/// <param name="yaw">Y ����</param>
		/// <param name="roll">Z ����</param>
		void Tilt(const float& pitch, const float& yaw, const float& roll)
		{
			worldTransform.Tilt(pitch, -yaw, roll);

			UpdateCamera();
		}

		/// <summary>
		/// ȸ�� ������ �����մϴ�.
		/// </summary>
		/// <param name="pitch">X ����</param>
		/// <param name="yaw">Y ����</param>
		/// <param name="roll">Z ����</param>
		void Rotate(const float& pitch, const float& yaw, const float& roll)
		{
			worldTransform.Rotate(pitch, -yaw, roll);

			UpdateCamera();
		}

		void UpdateCamera()
		{
			const glm::vec3 camera_position = GetPosition();

			glm::vec3 camera_lookat;

			switch (lookOption)
			{
				case CameraLookOption::POSITION:
				{
					camera_lookat = worldTransform.myMatrix * glm::vec4{ lookPosition, 1.0f };
				}
				break;

				case CameraLookOption::LOCKED_POSITION:
				{
					camera_lookat = lookPosition;
				}
				break;

				case CameraLookOption::DIRECTION:
				{
					camera_lookat = worldTransform.myMatrix * glm::vec4{ lookDirection, 1.0f };
				}
				break;
			}

			cameraLook = glm::normalize(camera_lookat - camera_position);
			cameraRight = glm::normalize(glm::cross(worldUp, cameraLook));
			cameraUp = glm::normalize(glm::cross(cameraLook, cameraRight));

			viewMatrix = glm::lookAt(camera_position, camera_lookat, cameraUp);
		}

		/// <summary>
		/// ī�޶� ��ȯ ����� ��ȯ�մϴ�.
		/// </summary>
		/// <returns></returns>
		glm::mat4& GetMatrix()
		{
			return viewMatrix;
		}

		/// <summary>
		/// ī�޶� ��ȯ ����� ��ȯ�մϴ�.
		/// </summary>
		/// <returns></returns>
		const glm::mat4& GetMatrix() const
		{
			return viewMatrix;
		}

		/// <summary>
		/// ���� ��ġ�� ��ȯ�մϴ�.
		/// </summary>
		/// <returns>��ġ ���� x, y, z</returns>
		glm::vec3 GetPosition() const
		{
			return worldTransform.GetPosition();
		}

		/// <summary>
		/// ���� ȸ���� ��ȯ�մϴ�.
		/// </summary>
		/// <returns>����� ȸ��</returns>
		glm::quat GetRotation() const
		{
			return worldTransform.GetRotation();
		}

		CameraLookOption lookOption;
		glm::vec3 lookPosition;
		glm::vec3 lookDirection;

	private:
		glm::vec3 worldUp;
		Transform worldTransform;

		glm::vec3 cameraRight, cameraLook, cameraUp;
		glm::mat4 viewMatrix;
	};
}
