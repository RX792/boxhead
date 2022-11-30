#pragma once
#include "BasicBlobs.hpp"

namespace ogl
{
	/// <summary>
	/// 정점 자료 구조
	/// </summary>
	namespace blob
	{
		template<size_t Vertices>
		/// <summary>
		/// 다양체들의 꼭지점 개수는 1 이상이어야 한다.
		/// </summary>
		concept PolygonVerticeCount = 0 < Vertices;

		/* 3D */
		struct Edge;
		struct Cube;
		struct IndexedCube;
		struct ColoredCube;
		struct IndexedColoredCube;
		struct Tetrahedron;
		struct ColoredTetrahedron;
		struct Sphere;
		struct ColoredSphere;

		/* 2D */
		struct Line;
		struct Triangle;
		struct ColoredTriangle;
		struct Rectangle;
		struct ColoredRectangle;
		template<size_t Vertices> requires PolygonVerticeCount<Vertices> struct Polygon;
		template<size_t Vertices> requires PolygonVerticeCount<Vertices> struct ColoredPolygon;

#define MAKE_BLOB_OPENED(NAME, VERTEX_TYPE, SINGLE_POINT_TYPE, ARRAY_LENGTH, STRIDE_LENGTH, COLORED)\
	struct NAME : public blob::meta::BlobInterface<float, (ARRAY_LENGTH), (STRIDE_LENGTH)>\
	{\
		using BaseType = blob::meta::BlobInterface<float, (ARRAY_LENGTH), (STRIDE_LENGTH)>;\
		using BaseType::data;\
		using BaseType::size;\
		using BaseType::at;\
		using BaseType::operator[];\
		using BaseType::cbegin;\
		using BaseType::cend;\
		using BaseType::begin;\
		using BaseType::end;\
		\
		constexpr NAME()\
			: BaseType()\
		{}\
		\
		template<std::forward_iterator It, std::sentinel_for<It> Guard>\
		constexpr NAME(It itbegin, const Guard itend)\
			: BaseType(itbegin, itend)\
		{}\
		\
		constexpr NAME(std::initializer_list<float> list)\
			: BaseType(list)\
		{}\
		\
		constexpr NAME(std::initializer_list<VERTEX_TYPE> list)\
			: BaseType(list, COLORED)\
		{}\
		\
		constexpr NAME(std::initializer_list<SINGLE_POINT_TYPE> list)\
			: BaseType(list)\
		{}
		;
#define MAKE_BLOB_CLOSE }

#define MAKE_BLOB(NAME, VERTEX_TYPE, SINGLE_POINT_TYPE, ARRAY_LENGTH, STRIDE_LENGTH, COLORED) MAKE_BLOB_OPENED(NAME, VERTEX_TYPE, SINGLE_POINT_TYPE, (ARRAY_LENGTH), (STRIDE_LENGTH), (COLORED)) }
		;

#define MAKE_LINE_BLOB(NAME, VERTEX_TYPE, SINGLE_POINT_TYPE, ARRAY_LENGTH, STRIDE_LENGTH) \
	MAKE_BLOB_OPENED(NAME, VERTEX_TYPE, SINGLE_POINT_TYPE, (ARRAY_LENGTH), (STRIDE_LENGTH), false)\
	constexpr NAME(std::pair<VERTEX_TYPE, VERTEX_TYPE> paired_coords)\
		: BaseType({ paired_coords.first, paired_coords.second })\
	{}\
	\
	constexpr NAME(std::pair<SINGLE_POINT_TYPE, SINGLE_POINT_TYPE> paired_coords)\
		: BaseType({ paired_coords.first, paired_coords.second })\
	{}\
	}
#define MAKE_2D_LINE(NAME, ARRAY_LENGTH, STRIDE_LENGTH) MAKE_LINE_BLOB(NAME, Vertex2D, Point, (ARRAY_LENGTH), (STRIDE_LENGTH))
#define MAKE_3D_LINE(NAME, ARRAY_LENGTH, STRIDE_LENGTH) MAKE_LINE_BLOB(NAME, Vertex, Quad, (ARRAY_LENGTH), (STRIDE_LENGTH))

#define MAKE_2D_BLOB_OPENED(NAME, ARRAY_LENGTH, STRIDE_LENGTH, COLORED) MAKE_BLOB_OPENED(NAME, Vertex2D, Point, (ARRAY_LENGTH), (STRIDE_LENGTH), (COLORED))
#define MAKE_2D_BLOB(NAME, ARRAY_LENGTH, STRIDE_LENGTH) MAKE_2D_BLOB_OPENED(NAME, (ARRAY_LENGTH), (STRIDE_LENGTH), false) }
#define MAKE_2D_COLORED_BLOB(NAME, ARRAY_LENGTH, STRIDE_LENGTH) MAKE_2D_BLOB_OPENED(NAME, (ARRAY_LENGTH), (STRIDE_LENGTH), true) }

#define MAKE_3D_BLOB_OPENED(NAME, ARRAY_LENGTH, STRIDE_LENGTH, COLORED) MAKE_BLOB_OPENED(NAME, Vertex, Quad, (ARRAY_LENGTH), (STRIDE_LENGTH), (COLORED))
#define MAKE_3D_BLOB(NAME, ARRAY_LENGTH, STRIDE_LENGTH) MAKE_3D_BLOB_OPENED(NAME, (ARRAY_LENGTH), (STRIDE_LENGTH), false) }
#define MAKE_3D_COLORED_BLOB(NAME, ARRAY_LENGTH, STRIDE_LENGTH) MAKE_3D_BLOB_OPENED(NAME, (ARRAY_LENGTH), (STRIDE_LENGTH), true) }

	/// <summary>
	/// 3D 직선
	/// </summary>
	MAKE_3D_LINE(Edge, 6, 3);

	/// <summary>
	/// 육면체
	/// </summary>
	MAKE_3D_BLOB(Cube, 72, 3);

	/// <summary>
	/// 색인된 육면체 (EBO 사용 필수)
	/// </summary>
	MAKE_3D_BLOB(IndexedCube, 24, 3);

	/// <summary>
	/// 면
	/// </summary>
	MAKE_3D_BLOB(Plane, 12, 3);

	/// <summary>
	/// 색깔 있는 면
	/// </summary>
	MAKE_3D_BLOB(ColoredPlane, 28, 7);

	/// <summary>
	/// 면 마다 색깔 있는 육면체
	/// </summary>
	MAKE_3D_BLOB(ColoredCube, 168, 7);

	/// <summary>
	/// 색인된 색깔 있는 육면체 (EBO 사용 필수)
	/// </summary>
	MAKE_3D_BLOB(IndexedColoredCube, 56, 7);

	/// <summary>
	/// 2D 직선
	/// </summary>
	MAKE_2D_LINE(Line, 6, 3);

	/// <summary>
	/// 2D 삼각형
	/// </summary>
	MAKE_2D_BLOB_OPENED(Triangle, 6, 2, false)
		constexpr operator ColoredTriangle() const noexcept;
	MAKE_BLOB_CLOSE;

	/// <summary>
	/// 색깔 있는 2D 삼각형
	/// </summary>
	MAKE_2D_BLOB_OPENED(ColoredTriangle, 18, 2, true)
		constexpr operator Triangle() const noexcept;
	MAKE_BLOB_CLOSE;

	constexpr Triangle::operator ColoredTriangle() const noexcept
	{
		return ColoredTriangle
		{
			x(0), y(0), 1.0f, 1.0f, 1.0f, 1.0f,
			x(1), y(1), 1.0f, 1.0f, 1.0f, 1.0f,
			x(2), y(2), 1.0f, 1.0f, 1.0f, 1.0f
		};
	}

	constexpr ColoredTriangle::operator Triangle() const noexcept
	{
		return Triangle
		{
			x(0), y(0),
			x(1), y(1),
			x(2), y(2)
		};
	}

	/// <summary>
	/// 2D 사각형
	/// </summary>
	MAKE_2D_BLOB_OPENED(Rectangle, 8, 2, false)
		constexpr operator ColoredRectangle() const noexcept;
	MAKE_BLOB_CLOSE;

	/// <summary>
	/// 색깔 있는 2D 사각형
	/// </summary>
	MAKE_2D_BLOB_OPENED(ColoredRectangle, 24, 6, true)
		constexpr operator Rectangle() const noexcept;
	MAKE_BLOB_CLOSE;

	constexpr Rectangle::operator ColoredRectangle() const noexcept
	{
		return ColoredRectangle
		{
			x(0), y(0), 1.0f, 1.0f, 1.0f, 1.0f,
			x(1), y(1), 1.0f, 1.0f, 1.0f, 1.0f,
			x(2), y(2), 1.0f, 1.0f, 1.0f, 1.0f,
			x(3), y(3), 1.0f, 1.0f, 1.0f, 1.0f
		};
	}

	constexpr ColoredRectangle::operator Rectangle() const noexcept
	{
		return Rectangle
		{
			x(0), y(0),
			x(1), y(1),
			x(2), y(2),
			x(3), y(3)
		};
	}

	template<size_t Vertices> requires PolygonVerticeCount<Vertices>
	/// <summary>
	/// 일반화 된 2D 도형
	/// </summary>
	MAKE_2D_BLOB_OPENED(Polygon, Vertices * 2, 2, false)
		constexpr operator ColoredPolygon<Vertices>() const noexcept;
	MAKE_BLOB_CLOSE;

	template<size_t Vertices> requires PolygonVerticeCount<Vertices>
	/// <summary>
	/// 일반화 된 색깔 있는 2D 도형
	/// </summary>
	MAKE_2D_BLOB_OPENED(ColoredPolygon, Vertices * 6, 6, true)
		constexpr operator Polygon<Vertices>() const noexcept;
	MAKE_BLOB_CLOSE;

	template<size_t Vertices> requires PolygonVerticeCount<Vertices>
	constexpr Polygon<Vertices>::operator ColoredPolygon<Vertices>() const noexcept
	{
		using BaseType = blob::meta::BlobInterface<float, Vertices * 2, 2>;

		std::vector<float> result{};
		result.reserve(Vertices * 2);

		for (size_t i = 0; i < Vertices; i++)
		{
			result.push_back(BaseType::x(i));
			result.push_back(BaseType::y(i));
			result.emplace_back({ 1.0f, 1.0f, 1.0f, 1.0f });
		}

		return ColoredPolygon<Vertices>{result.cbegin(), result.cend()};
	}

	template<size_t Vertices> requires PolygonVerticeCount<Vertices>
	constexpr ColoredPolygon<Vertices>::operator Polygon<Vertices>() const noexcept
	{
		using BaseType = blob::meta::BlobInterface<float, Vertices * 6, 6>;

		std::vector<float> result{};
		result.reserve(Vertices * 6);

		for (size_t i = 0; i < Vertices; i++)
		{
			result.push_back(BaseType::x(i));
			result.push_back(BaseType::y(i));
		}

		return Polygon<Vertices>{result.cbegin(), result.cend()};
	}

	using CubeWithIndex = std::pair<const Cube, const index::Cubes>;
	using ColoredCubeWithIndex = std::pair<const ColoredCube, const index::Cubes>;
	using TetrahedronWithIndex = std::pair<const Tetrahedron, const index::Tetrahedra>;
	using ColoredTetrahedronWithIndex = std::pair<const ColoredTetrahedron, const index::Tetrahedra>;

	using TriangleWithIndex = std::pair<const Triangle, const index::Triangles>;
	using ColoredTriangleWithIndex = std::pair<const ColoredTriangle, const index::Triangles>;
	using RectangleWithIndex = std::pair<const Rectangle, const index::Triangles>;
	using ColoredRectangleWithIndex = std::pair<const ColoredRectangle, const index::Rectangles>;
	}
}
