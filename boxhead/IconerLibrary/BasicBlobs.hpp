#pragma once
#include "Prototypes.hpp"

namespace ogl
{
	namespace blob
	{
		struct Vertex2D
		{
			constexpr Vertex2D()
				: myPositions(), myColour()
				, x(myPositions.x), y(myPositions.y)
				, r(myColour.r), g(myColour.g), b(myColour.b), a(myColour.a)
			{}

			constexpr Vertex2D(float x, float y, float r, float g, float b, float a)
				: myPositions{ x, y }, myColour{ r, g, b, a }
				, x(myPositions.x), y(myPositions.y)
				, r(myColour.r), g(myColour.g), b(myColour.b), a(myColour.a)
			{}

			constexpr Vertex2D(glm::vec2&& position)
				: myPositions(std::forward<glm::vec2>(position)), myColour()
				, x(myPositions.x), y(myPositions.y)
				, r(myColour.r), g(myColour.g), b(myColour.b), a(myColour.a)
			{}

			constexpr Vertex2D(const glm::vec2& position)
				: myPositions(position), myColour()
				, x(myPositions.x), y(myPositions.y)
				, r(myColour.r), g(myColour.g), b(myColour.b), a(myColour.a)
			{}

			constexpr Vertex2D(glm::vec2&& position, Colour&& color)
				: myPositions(std::forward<glm::vec2>(position)), myColour(std::forward<Colour>(color))
				, x(myPositions.x), y(myPositions.y)
				, r(myColour.r), g(myColour.g), b(myColour.b), a(myColour.a)
			{}

			constexpr Vertex2D(glm::vec2&& position, const Colour& color)
				: myPositions(std::forward<glm::vec2>(position)), myColour(color)
				, x(myPositions.x), y(myPositions.y)
				, r(myColour.r), g(myColour.g), b(myColour.b), a(myColour.a)
			{}

			constexpr Vertex2D(float x, float y, Colour&& color)
				: myPositions{ x, y }, myColour(std::forward<Colour>(color))
				, x(myPositions.x), y(myPositions.y)
				, r(myColour.r), g(myColour.g), b(myColour.b), a(myColour.a)
			{}

			constexpr Vertex2D(float x, float y, const Colour& color)
				: myPositions{ x, y }, myColour(color)
				, x(myPositions.x), y(myPositions.y)
				, r(myColour.r), g(myColour.g), b(myColour.b), a(myColour.a)
			{}

			ogl::Point myPositions;
			ogl::Colour myColour;

			float& x, & y;
			float& r, & g, & b, & a;
		};

		struct Vertex
		{
			constexpr Vertex()
				: myPositions(), myColour()
				, x(myPositions.x), y(myPositions.y), z(myPositions.z)
				, r(myColour.r), g(myColour.g), b(myColour.b), a(myColour.a)
			{}

			constexpr Vertex(float x, float y, float z, float r, float g, float b, float a)
				: myPositions{ x, y, z }, myColour{ r, g, b, a }
				, x(myPositions.x), y(myPositions.y), z(myPositions.z)
				, r(myColour.r), g(myColour.g), b(myColour.b), a(myColour.a)
			{}

			constexpr Vertex(ogl::Quad&& position)
				: myPositions(std::forward<ogl::Quad>(position)), myColour()
				, x(myPositions.x), y(myPositions.y), z(myPositions.z)
				, r(myColour.r), g(myColour.g), b(myColour.b), a(myColour.a)
			{}

			constexpr Vertex(const ogl::Quad& position)
				: myPositions(position), myColour()
				, x(myPositions.x), y(myPositions.y), z(myPositions.z)
				, r(myColour.r), g(myColour.g), b(myColour.b), a(myColour.a)
			{}

			constexpr Vertex(const ogl::Quad& position, Colour&& color)
				: myPositions(position), myColour(std::forward<Colour>(color))
				, x(myPositions.x), y(myPositions.y), z(myPositions.z)
				, r(myColour.r), g(myColour.g), b(myColour.b), a(myColour.a)
			{}

			constexpr Vertex(const ogl::Quad& position, const Colour& color)
				: myPositions(position), myColour(color)
				, x(myPositions.x), y(myPositions.y), z(myPositions.z)
				, r(myColour.r), g(myColour.g), b(myColour.b), a(myColour.a)
			{}

			constexpr Vertex(ogl::Quad&& position, Colour&& color)
				: myPositions(std::forward<ogl::Quad>(position)), myColour(std::forward<Colour>(color))
				, x(myPositions.x), y(myPositions.y), z(myPositions.z)
				, r(myColour.r), g(myColour.g), b(myColour.b), a(myColour.a)
			{}

			constexpr Vertex(ogl::Quad&& position, const Colour& color)
				: myPositions(std::forward<ogl::Quad>(position)), myColour(color)
				, x(myPositions.x), y(myPositions.y), z(myPositions.z)
				, r(myColour.r), g(myColour.g), b(myColour.b), a(myColour.a)
			{}

			constexpr Vertex(float x, float y, float z, Colour&& color)
				: myPositions{ x, y, z }, myColour(std::forward<Colour>(color))
				, x(myPositions.x), y(myPositions.y), z(myPositions.z)
				, r(myColour.r), g(myColour.g), b(myColour.b), a(myColour.a)
			{}

			constexpr Vertex(float x, float y, float z, const Colour& color)
				: myPositions{ x, y, z }, myColour(color)
				, x(myPositions.x), y(myPositions.y), z(myPositions.z)
				, r(myColour.r), g(myColour.g), b(myColour.b), a(myColour.a)
			{}

			ogl::Quad myPositions;
			ogl::Colour myColour;

			float& x, & y, & z;
			float& r, & g, & b, & a;
		};

		namespace meta
		{
			template<typename Ty, size_t Length, size_t Stride_length = 1>
			struct BlobInterface : public std::array<Ty, Length>
			{
				using BaseType = std::array<Ty, Length>;
				using BaseType::data;
				using BaseType::size;
				using BaseType::at;
				using BaseType::operator[];
				using BaseType::cbegin;
				using BaseType::cend;
				using BaseType::begin;
				using BaseType::end;

				constexpr BlobInterface()
					: BaseType()
				{};

				template<std::forward_iterator It, std::sentinel_for<It> Guard>
				constexpr BlobInterface(It itbegin, const Guard itend)
					: BaseType()
				{
					std::copy(itbegin, itend, begin());
				}

				constexpr BlobInterface(std::initializer_list<Ty> list) requires std::convertible_to < Ty, float>
					: BaseType()
				{
					std::copy(list.begin(), list.end(), BaseType::begin());
				}

				constexpr BlobInterface(std::initializer_list<Point> list)
					: BaseType()
				{
					size_t index = 0;
					for (auto& point : list)
					{
						at(index) = point.x;
						at(index + 1) = point.y;

						index += 2;
					}
				}

				constexpr BlobInterface(std::initializer_list<Quad> list)
					: BaseType()
				{
					size_t index = 0;
					for (auto& quad : list)
					{
						at(index) = quad.x;
						at(index + 1) = quad.y;
						at(index + 2) = quad.z;

						index += 3;
					}
				}

				constexpr BlobInterface(std::initializer_list<Vertex2D> list, bool colored = false)
					: BaseType()
				{
					size_t index = 0;
					for (auto& vertex : list)
					{
						at(index) = vertex.x;
						at(index + 1) = vertex.y;
						if (colored)
						{
							at(index + 2) = vertex.r;
							at(index + 3) = vertex.g;
							at(index + 4) = vertex.b;
							at(index + 5) = vertex.a;
							index += 4;
						}

						index += 2;
					}
				}

				constexpr BlobInterface(std::initializer_list<Vertex> list, bool colored = false)
					: BaseType()
				{
					size_t index = 0;
					for (auto& vertex : list)
					{
						at(index) = vertex.x;
						at(index + 1) = vertex.y;
						at(index + 2) = vertex.z;
						if (colored)
						{
							at(index + 3) = vertex.r;
							at(index + 4) = vertex.g;
							at(index + 5) = vertex.b;
							at(index + 6) = vertex.a;
							index += 4;
						}

						index += 3;
					}
				}

				[[nodiscard]]
				inline constexpr Ty& x(const size_t& index) noexcept
				{
					return at(index * Stride_length);
				}

				[[nodiscard]]
				inline constexpr Ty& y(const size_t& index) noexcept
				{
					return at(index * Stride_length + 1);
				}

				[[nodiscard]]
				inline constexpr Ty& z(const size_t& index) noexcept
				{
					return at(index * Stride_length + 2);
				}

				[[nodiscard]]
				inline constexpr Ty& w(const size_t& index) noexcept
				{
					return at(index * Stride_length + 3);
				}

				[[nodiscard]]
				inline constexpr const Ty& x(const size_t& index) const noexcept
				{
					return at(index * Stride_length);
				}

				[[nodiscard]]
				inline constexpr const Ty& y(const size_t& index) const noexcept
				{
					return at(index * Stride_length + 1);
				}

				[[nodiscard]]
				inline constexpr const Ty& z(const size_t& index) const noexcept
				{
					return at(index * Stride_length + 2);
				}

				[[nodiscard]]
				inline constexpr const Ty& w(const size_t& index) const noexcept
				{
					return at(index * Stride_length + 3);
				}

				[[nodiscard]]
				static inline constexpr size_t alloc_size() noexcept
				{
					return Length * sizeof(Ty);
				}

				[[nodiscard]]
				static inline constexpr size_t element_size() noexcept
				{
					return Stride_length * sizeof(Ty);
				}

				static inline constexpr size_t stride = sizeof(Ty) * Stride_length;
			};
		}
	}

	template<typename Ty, typename ContainTy, size_t Length, size_t StrideLen>
	concept blobs = std::convertible_to<std::remove_cvref_t<Ty>, blob::meta::BlobInterface<ContainTy, Length, StrideLen>>;

	namespace index
	{
		using Triangles = std::array<unsigned int, 3>;
		using Rectangles = std::array<unsigned int, 6>;
		using Tetrahedra = std::array<unsigned int, 12>;
		using Cubes = std::array<unsigned int, 36>;
	}
}

template<typename Ty, size_t Length, size_t StrideLen, ogl::blobs<Ty, Length, StrideLen> BlobTy>
inline constexpr
bool
operator==(const BlobTy& lhs, const BlobTy& rhs)
{
	const auto result = std::mismatch(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());

	return (result.first == lhs.cend());
}

template<typename Ty, size_t Length, size_t StrideLen, ogl::blobs<Ty, Length, StrideLen> BlobTy>
inline constexpr
BlobTy
operator+(const BlobTy& lhs, const BlobTy& rhs)
{
	BlobTy result{};
	auto it = result.begin();

	for (auto ait = lhs.cbegin(), bit = rhs.cbegin(); ait != lhs.cend(), bit != rhs.cend(); ait++, bit++)
	{
		*(it++) = *ait + *bit;
	}

	return result;
}

template<typename Ty, size_t Length, size_t StrideLen, ogl::blobs<Ty, Length, StrideLen> BlobTy>
inline constexpr
BlobTy
operator-(const BlobTy& lhs, const BlobTy& rhs)
{
	BlobTy result{};
	auto it = result.begin();

	for (auto ait = lhs.cbegin(), bit = rhs.cbegin(); ait != lhs.cend(), bit != rhs.cend(); ait++, bit++)
	{
		*(it++) = *ait - *bit;
	}

	return result;
}

template<typename Ty, size_t Length, size_t StrideLen, ogl::blobs<Ty, Length, StrideLen> BlobTy>
inline constexpr
BlobTy&
operator+=(BlobTy& lhs, BlobTy& rhs)
{
	for (auto ait = lhs.begin(), bit = rhs.cbegin(); ait != lhs.end(), bit != rhs.cend(); ait++, bit++)
	{
		*ait = *ait + *bit;
	}

	return lhs;
}

template<typename Ty, size_t Length, size_t StrideLen, ogl::blobs<Ty, Length, StrideLen> BlobTy>
inline constexpr
BlobTy&
operator-=(BlobTy& lhs, const BlobTy& rhs)
{
	for (auto ait = lhs.begin(), bit = rhs.cbegin(); ait != lhs.end(), bit != rhs.cend(); ait++, bit++)
	{
		*ait = *ait - *bit;
	}

	return lhs;
}
