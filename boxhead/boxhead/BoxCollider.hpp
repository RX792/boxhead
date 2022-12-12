#pragma once
#include "Collider.hpp"
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include <DirectXMathVector.inl>
#include <DirectXMathMatrix.inl>
#include <DirectXCollision.inl>
#include <DirectXMathMisc.inl>

constexpr glm::vec4 BoxOffsets[] =
{
	{ -1.0f, -1.0f,  1.0f, 0.0f },
	{  1.0f, -1.0f,  1.0f, 0.0f },
	{  1.0f,  1.0f,  1.0f, 0.0f },
	{ -1.0f,  1.0f,  1.0f, 0.0f },
	{ -1.0f, -1.0f, -1.0f, 0.0f },
	{  1.0f, -1.0f, -1.0f, 0.0f },
	{  1.0f,  1.0f, -1.0f, 0.0f },
	{ -1.0f,  1.0f, -1.0f, 0.0f },
};

constexpr DirectX::XMVECTORF32 g_RayEpsilon = { { { 1e-20f, 1e-20f, 1e-20f, 1e-20f } } };
constexpr DirectX::XMVECTORF32 g_RayNegEpsilon = { { { -1e-20f, -1e-20f, -1e-20f, -1e-20f } } };
constexpr DirectX::XMVECTORF32 g_FltMin = { { { -FLT_MAX, -FLT_MAX, -FLT_MAX, -FLT_MAX } } };
constexpr DirectX::XMVECTORF32 g_FltMax = { { { FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX } } };

class OrientedBoxCollider;

class BoxCollider : public Collider
{
public:
	explicit constexpr BoxCollider() noexcept
		: Collider()
	{}

	explicit constexpr BoxCollider(const glm::vec3& extents) noexcept
		: Collider(extents)
	{}

	explicit constexpr BoxCollider(const glm::mat4& world_matrix) noexcept
		: Collider(world_matrix)
	{}

	explicit constexpr BoxCollider(const glm::mat4& world_matrix, const glm::vec3& extents) noexcept
		: Collider(world_matrix, extents)
	{}

	constexpr BoxCollider(const Transform& transform, const glm::vec3& extents) noexcept
		: Collider(transform, extents)
	{}

	constexpr BoxCollider(Transform&& transform, const glm::vec3& extents) noexcept
		: Collider(std::move(transform), extents)
	{}

	constexpr ~BoxCollider() = default;

	constexpr bool Check(const BoxCollider& other) const
	{
		const auto& this_pos = worldTransform.GetPosition();
		const auto& other_pos = other.worldTransform.GetPosition();

		const auto& other_ext = other.colliderExtent;

		// 왼쪽 아래 꼭지점
		const auto lb_point = this_pos - colliderExtent;
		// 오른쪽 위 꼭지점
		const auto rt_point = this_pos + colliderExtent;

		// 왼쪽 아래 꼭지점
		const auto other_lb_point = other_pos - other_ext;
		// 오른쪽 위 꼭지점
		const auto other_rt_point = other_pos + other_ext;

		if (rt_point.x < other_lb_point.x || other_rt_point.x <= lb_point.x)
			return false;

		if (rt_point.y < other_lb_point.y || other_rt_point.y <= lb_point.y)
			return false;

		if (rt_point.z < other_lb_point.z || other_rt_point.z <= lb_point.z)
			return false;

		return true;
	}

	bool Check(const OrientedBoxCollider& other) const
	{
		return false;
	}

	static inline constexpr glm::vec3 BoxBounds[] =
	{
		glm::vec3{ -1, -1, -1 },
		glm::vec3{ +1, +1, +1 },
	};
};

class OrientedBoxCollider : public Collider
{
public:
	constexpr OrientedBoxCollider() = default;

	constexpr ~OrientedBoxCollider() = default;

	bool Check(const BoxCollider& other) const
	{
		return false;
	}

	bool Check(const OrientedBoxCollider& other) const
	{
		return false;
	}
};

