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

class BoxCollider : public Collider
{
public:
	constexpr BoxCollider() = default;

	constexpr ~BoxCollider() = default;

	bool Check(const BoxCollider& other) const
	{
		return false;
	}

	bool Check(const OrientedBoxCollider& other) const
	{
		return false;
	}
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

