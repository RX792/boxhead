#pragma once

class GameViewManger
{
public:
	constexpr GameViewManger()
		: mainCamera(ogl::up)
		, cameraPitch(), cameraYaw()
		, isFollow(false), cameraFollower(nullptr)
		, followTransform()
		, followSmooth(false), followSpeed(8.0f)
	{}

	~GameViewManger()
	{}

	void Awake()
	{
		camera::PerspectiveCameraSetting pr_setting{};
		pr_setting.projectionFieldOfView = 40.0f;
		pr_setting.projectionRatio = 16.0f / 9.0f;
		pr_setting.projectionNear = 0.1f;
		pr_setting.projectionFar = 10000.0f;

		camera::OrthodoxCameraSetting ox_setting{};
		ox_setting.projectionLeft = 480.0f;
		ox_setting.projectionRight = 480.0f;
		ox_setting.projectionBottom = -270.0f;
		ox_setting.projectionTop = 270.0f;

		mainCamera.Setup(pr_setting);
		mainCamera.Setup(ox_setting);
		mainCamera.Awake();
	}

	void Start()
	{
		Reset();
	}

	void Update(const float& delta_time)
	{
		if (isFollow)
		{
			if (cameraFollower)
			{
				switch (mainCamera.lookOption)
				{
					case camera::CameraLookOption::POSITION:
					{
						mainCamera.SetPosition(cameraFollower->GetPosition());
					}
					break;

					case camera::CameraLookOption::LOCKED_POSITION:
					{
						mainCamera.SetPosition(cameraFollower->GetPosition());
					}
					break;

					case camera::CameraLookOption::DIRECTION:
					{
						mainCamera.SetPosition(cameraFollower->GetPosition());
					}
					break;
				}
			}
		}
	}

	void Reset()
	{
		mainCamera.SetPosition({ 0.0f, 15.0f, -8.0f });
		mainCamera.SetRotation(0.0f, 0.0f, 0.0f);
		mainCamera.SetLookDirection(ogl::forward);

		cameraYaw = 0.0f;
		cameraPitch = 0.0f;
	}

	void MouseTrack(const int& dx, const int& dy, const float& delta_time)
	{
		if (0 != dx)
		{
			const float addition = dx * 10.0f * delta_time;
			cameraYaw += addition;
		}

		if (0 != dy)
		{
			const float addition = dy * 6.0f * delta_time;

			cameraPitch = std::max(std::min(cameraPitch + addition, 89.0f), -89.0f);
		}

		mainCamera.SetRotation(cameraPitch, cameraYaw, 0.0f);
	}

	constexpr void SetLookAt(const glm::vec3& local_position)
	{
		mainCamera.SetLookAt(local_position);
	}

	constexpr void SetLockViewAt(const glm::vec3& world_position)
	{
		mainCamera.SetLockViewAt(world_position);
	}

	constexpr void SetLookDirection(const glm::vec3& direction)
	{
		mainCamera.SetLookDirection(direction);
	}

	constexpr void SetOption(const camera::CameraLookOption& option)
	{
		mainCamera.SetOption(option);
	}

	constexpr void SetFollower(GameObject* target, bool flag = true)
	{
		isFollow = flag;
		cameraFollower = target;
	}

	constexpr void SetRotationX(const float& rotation)
	{
		cameraPitch = rotation;
	}

	constexpr void RotateX(const float& rotation)
	{
		cameraPitch += rotation;
	}

	constexpr void SetRotationY(const float& rotation)
	{
		cameraYaw = rotation;
	}

	constexpr void RotateY(const float& rotation)
	{
		cameraYaw += rotation;
	}

	constexpr camera::Camera& GetCamera()
	{
		return mainCamera;
	}

	constexpr const camera::Camera& GetCamera() const
	{
		return mainCamera;
	}

	constexpr const glm::mat4& GetCameraMatrix() const
	{
		return mainCamera.GetCameraMatrix();
	}

	constexpr const glm::mat4& GetPerspectiveViewMatrix() const
	{
		return mainCamera.GetPerspectiveViewMatrix();
	}

	constexpr const glm::mat4& GetOrthodoxViewMatrix() const
	{
		return mainCamera.GetOrthodoxViewMatrix();
	}

	camera::Camera mainCamera;
	float cameraPitch, cameraYaw;

	bool isFollow;
	GameObject* cameraFollower;
	Transform followTransform;
	bool followSmooth;
	float followSpeed;
};
