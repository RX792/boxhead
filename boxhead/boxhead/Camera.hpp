#pragma once

namespace camera
{
	enum class CameraLookOption
	{
		POSITION,
		LOCKED_POSITION,
		DIRECTION,
	};

	struct PerspectiveCameraSetting
	{
		float projectionFieldOfView;
		float projectionRatio;
		float projectionNear;
		float projectionFar;
	};

	struct OrthodoxCameraSetting
	{
		float projectionLeft;
		float projectionRight;
		float projectionBottom;
		float projectionTop;
	};

	class Camera
	{
	public:
		constexpr Camera(const glm::vec3& up)
			: lookOption(CameraLookOption::DIRECTION)
			, lookPosition(), lookDirection(ogl::forward)
			, viewMatrix()
			, perspectiveMatrix(), orthodoxMatrix()
			, worldUp(up), worldTransform(ogl::identity)
			, cameraRight(), cameraUp(), cameraLook()
		{}

		void Setup(PerspectiveCameraSetting setting)
		{
			perspectiveSetting = setting;
		}

		void Setup(OrthodoxCameraSetting setting)
		{
			orthodoxSetting = setting;
		}

		void Awake()
		{
			float proj_fov = glm::radians(perspectiveSetting.projectionFieldOfView);
			float proj_ratio = perspectiveSetting.projectionRatio;

			perspectiveMatrix = glm::perspective(proj_fov, proj_ratio, perspectiveSetting.projectionNear, perspectiveSetting.projectionFar);

			orthodoxMatrix = glm::ortho(orthodoxSetting.projectionLeft, orthodoxSetting.projectionRight, orthodoxSetting.projectionBottom, orthodoxSetting.projectionTop);
		}

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
		/// 좌표를 지정합니다.
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
			worldTransform.Translate(ax, ay, az);

			UpdateCamera();
		}

		/// <summary>
		/// 좌표를 더합니다.
		/// </summary>
		/// <param name="vector"></param>
		void Translate(const glm::vec3& vector)
		{
			worldTransform.Translate(vector);

			UpdateCamera();
		}

		/// <summary>
		/// 회전 각도를 더합니다.
		/// </summary>
		/// <param name="pitch">X 각도</param>
		/// <param name="yaw">Y 각도</param>
		/// <param name="roll">Z 각도</param>
		void Tilt(const float& pitch, const float& yaw, const float& roll)
		{
			worldTransform.Tilt(pitch, -yaw, roll);

			UpdateCamera();
		}

		/// <summary>
		/// 회전 각도를 지정합니다.
		/// </summary>
		/// <param name="pitch">X 각도</param>
		/// <param name="yaw">Y 각도</param>
		/// <param name="roll">Z 각도</param>
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
		/// 카메라 변환 행렬을 반환합니다.
		/// </summary>
		/// <returns></returns>
		constexpr glm::mat4& GetCameraMatrix()
		{
			return viewMatrix;
		}

		/// <summary>
		/// 카메라 변환 행렬을 반환합니다.
		/// </summary>
		/// <returns></returns>
		constexpr const glm::mat4& GetCameraMatrix() const
		{
			return viewMatrix;
		}

		/// <summary>
		/// 원근 투영 변환 행렬을 반환합니다.
		/// </summary>
		/// <returns></returns>
		constexpr const glm::mat4& GetPerspectiveViewMatrix() const
		{
			return perspectiveMatrix;
		}

		/// <summary>
		/// 직교 투영 변환 행렬을 반환합니다.
		/// </summary>
		/// <returns></returns>
		constexpr const glm::mat4& GetOrthodoxViewMatrix() const
		{
			return orthodoxMatrix;
		}

		/// <summary>
		/// 현재 위치를 반환합니다.
		/// </summary>
		/// <returns>위치 벡터 x, y, z</returns>
		constexpr glm::vec3 GetPosition() const
		{
			return worldTransform.GetPosition();
		}

		/// <summary>
		/// 현재 회전을 반환합니다.
		/// </summary>
		/// <returns>사원수 회전</returns>
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

		glm::mat4 perspectiveMatrix;
		glm::mat4 orthodoxMatrix;

		PerspectiveCameraSetting perspectiveSetting;
		OrthodoxCameraSetting orthodoxSetting;
	};
}
