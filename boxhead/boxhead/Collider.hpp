#pragma once
#include "Transform.hpp"

class Collider
{
public:
	constexpr Collider() = default;

	bool Check(const ColliderType auto& other) const = 0;

	constexpr virtual ~Collider() = default;

	Transform worldTransform;
	glm::vec3 colliderExtent;
	/*
	ContainmentType check(const BoundingOrientedBox& other)
	{
		if (!mybox.Intersects(other))
			return DISJOINT;

		// Load the boxes

		// position
		XMVECTOR aCenter = XMLoadFloat3(&mybox.Center);
		// radius
		XMVECTOR aExtents = XMLoadFloat3(&mybox.Extents);
		// normalize(matrix.get_rotation())
		XMVECTOR aOrientation = XMLoadFloat4(&mybox.Orientation);

		::assert(DirectX::Internal::XMQuaternionIsUnit(aOrientation));

		// other.position
		XMVECTOR bCenter = XMLoadFloat3(&other.Center);
		// radius
		XMVECTOR bExtents = XMLoadFloat3(&other.Extents);
		// normalize(other.matrix.get_rotation())
		XMVECTOR bOrientation = XMLoadFloat4(&other.Orientation);

		::assert(DirectX::Internal::XMQuaternionIsUnit(bOrientation));

		// other.position - position
		XMVECTOR offset = DirectX::XMVectorSubtract(bCenter, aCenter);
		
		// 육면체 모서리 꼭지점 수만큼, 8번 반복
		for (size_t i = 0; i < mybox.CORNER_COUNT; ++i)
		{
			auto Cb = rotate(bExtents * corneroffset[i], bOrientation) + bcenter;

			glm::affineInverse(matrix);
			auto Ca = invrotate(Cb - aCenter, aOrientation);

			// other.position - position + other.rotation * ...
			XMVECTOR C = XMVectorAdd
			(
				// other.rotation * ...
				DirectX::XMVector3Rotate
				(
					// other.radius * glm::vec4{ box_corrds[i], 0.0f }
					DirectX::XMVectorMultiply
					(
						bExtents, ::g_BoxOffset[i]
					),
					bOrientation
				),
				offset
			);

			// C * (this.rotation)(-1)
			C = DirectX::XMVector3InverseRotate(C, aOrientation);
			
			return
			(
				!(
					(
						C.x <= radius.x &&
						C.x >= -radius.x
					) &&
					(
						C.y <= radius.y &&
						C.y >= -radius.y
					) &&
					(
						C.z <= radius.z &&
						C.z >= -radius.z
					)
				)
				//!= 0
			);
			if (!DirectX::XMVector3InBounds(C, aExtents))
				return INTERSECTS;
		}

		return CONTAINS;
	}
	glm::vec3 position;
	glm::mat4 matrix;
	glm::vec3 radius;
	DirectX::BoundingOrientedBox mybox;
	*/
};

template<typename Ty>
concept ColliderType = std::derived_from<std::decay_t<Ty>, Collider>;
