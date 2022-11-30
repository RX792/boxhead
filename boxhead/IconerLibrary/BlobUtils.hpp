#pragma once
#include "Blobs.hpp"

namespace ogl
{
	namespace blob
	{
		namespace edge
		{
			[[nodiscard]]
			inline constexpr blob::Edge Create
			(
				const float x1, const float y1, const float z1, // ù��° ��
				const float x2, const float y2, const float z2  // �ι�° ��
			)
			{
				return { x1, y1, z1, x2, y2, z2 };
			}

			[[nodiscard]]
			inline constexpr blob::Edge Create
			(
				const Quad& from, // ù��° ��
				const Quad& to    // �ι�° ��
			)
			{
				return { from.x, from.y, from.z, to.x, to.y, to.z };
			}

			[[nodiscard]]
			inline constexpr blob::Edge Create
			(
				const Vertex& from, // ù��° ��
				const Vertex& to    // �ι�° ��
			)
			{
				return { from, to };
			}
		}

		namespace plane
		{
			[[nodiscard]]
			inline constexpr blob::ColoredPlane Create
			(
				const float& x1, const float& y1, const float& z1, const Colour& c1, // ù��° ��
				const float& x2, const float& y2, const float& z2, const Colour& c2, // �ι�° ��
				const float& x3, const float& y3, const float& z3, const Colour& c3, // ����° ��
				const float& x4, const float& y4, const float& z4, const Colour& c4  // �׹�° ��
			)
			{
				return
				{
					x1, y1, z1, c1.r, c1.g, c1.b, c1.a,
					x2, y2, z2, c2.r, c2.g, c2.b, c2.a,
					x3, y3, z3, c3.r, c3.g, c3.b, c3.a,
					x4, y4, z4, c4.r, c4.g, c4.b, c4.a
				};
			}

			[[nodiscard]]
			inline constexpr blob::ColoredPlane Create
			(
				const Quad& point1, const Colour& c1, // ù��° ��
				const Quad& point2, const Colour& c2, // �ι�° ��
				const Quad& point3, const Colour& c3, // ����° ��
				const Quad& point4, const Colour& c4  // �׹�° ��
			)
			{
				return
				{
					point1.x, point1.y, point1.z, c1.r, c1.g, c1.b, c1.a,
					point2.x, point2.y, point2.z, c2.r, c2.g, c2.b, c2.a,
					point3.x, point3.y, point3.z, c3.r, c3.g, c3.b, c3.a,
					point4.x, point4.y, point4.z, c4.r, c4.g, c4.b, c4.a
				};
			}

			[[nodiscard]]
			inline constexpr blob::ColoredPlane Create
			(
				const float& x1, const float& y1, const float& z1, // ù��° ��
				const float& x2, const float& y2, const float& z2, // �ι�° ��
				const float& x3, const float& y3, const float& z3, // ����° ��
				const float& x4, const float& y4, const float& z4, // �׹�° ��
				const Colour& color
			)
			{
				return Create(x1, y1, z1, color, x2, y2, z2, color, x3, y3, z3, color, x4, y4, z4, color);
			}

			[[nodiscard]]
			inline constexpr blob::ColoredPlane Create
			(
				const Quad& point1, // ù��° ��
				const Quad& point2, // �ι�° ��
				const Quad& point3, // ����° ��
				const Quad& point4, // �׹�° ��
				const Colour& color
			)
			{
				return Create(point1, color, point2, color, point3, color, point4, color);
			}

			[[nodiscard]]
			inline constexpr blob::ColoredPlane Create
			(
				const Vertex& pt1, // ù��° ��
				const Vertex& pt2, // �ι�° ��
				const Vertex& pt3, // ����° ��
				const Vertex& pt4  // �׹�° ��
			)
			{
				return
				{
					pt1.x, pt1.y, pt1.z, pt1.r, pt1.g, pt1.b, pt1.a,
					pt2.x, pt2.y, pt2.z, pt2.r, pt2.g, pt2.b, pt2.a,
					pt3.x, pt3.y, pt3.z, pt3.r, pt3.g, pt3.b, pt3.a,
					pt4.x, pt4.y, pt4.z, pt4.r, pt4.g, pt4.b, pt4.a
				};
			}
		}

		namespace cube
		{
			[[deprecated("asdf"), nodiscard]]
			inline constexpr blob::Cube Create
			(
				const float& x1, const float& y1, const float& z1, // ���� ù��° ��
				const float& x2, const float& y2, const float& z2, // ���� �ι�° ��
				const float& x3, const float& y3, const float& z3, // ���� ����° ��
				const float& x4, const float& y4, const float& z4, // ���� �׹�° ��
				const float& x5, const float& y5, const float& z5, // �Ʒ��� ù��° ��
				const float& x6, const float& y6, const float& z6, // �Ʒ��� �ι�° ��
				const float& x7, const float& y7, const float& z7, // �Ʒ��� ����° ��
				const float& x8, const float& y8, const float& z8  // �Ʒ��� �׹�° ��
			)
			{
				return
				{
					x1, y1, z1,
					x2, y2, z2,
					x3, y3, z3,
					x4, y4, z4,
					x5, y5, z5,
					x6, y6, z6,
					x7, y7, z7,
					x8, y8, z8,
				};
			}

			[[nodiscard]]
			inline constexpr blob::Cube Create
			(
				const Plane(&planes)[6] // �� 6��
			)
			{
				blob::Cube result{};

				size_t index = 0;
				size_t seek = 0;
				for (size_t i = 0; i < 6; i++)
				{
					for (size_t verts = 0; verts < 4; verts++)
					{
						result.at(index++) = planes[i].at(seek++); // x
						result.at(index++) = planes[i].at(seek++); // y
						result.at(index++) = planes[i].at(seek++); // z
					}
					seek = 0;
				}

				return result;
			}

			[[nodiscard]]
			inline constexpr blob::Cube Create
			(
				const Plane& pn1, // ù��° ��
				const Plane& pn2, // �ι�° ��
				const Plane& pn3, // ����° ��
				const Plane& pn4, // �׹�° ��
				const Plane& pn5, // �ټ���° ��
				const Plane& pn6  // ������° ��
			)
			{
				return Create({ pn1, pn2, pn3, pn4, pn5, pn6 });
			}

			[[nodiscard]]
			inline constexpr blob::ColoredCube Create
			(
				const ColoredPlane(&planes)[6] // �� 6��
			)
			{
				blob::ColoredCube result{};

				size_t index = 0;
				size_t seek = 0;
				for (size_t i = 0; i < 6; i++)
				{
					for (size_t verts = 0; verts < 4; verts++)
					{
						result.at(index++) = planes[i].at(seek++); // x
						result.at(index++) = planes[i].at(seek++); // y
						result.at(index++) = planes[i].at(seek++); // z
						result.at(index++) = planes[i].at(seek++); // r
						result.at(index++) = planes[i].at(seek++); // g
						result.at(index++) = planes[i].at(seek++); // b
						result.at(index++) = planes[i].at(seek++); // a
					}
					seek = 0;
				}

				return result;
			}

			[[nodiscard]]
			inline constexpr blob::ColoredCube Create
			(
				const ColoredPlane& pn1, // ù��° ��
				const ColoredPlane& pn2, // �ι�° ��
				const ColoredPlane& pn3, // ����° ��
				const ColoredPlane& pn4, // �׹�° ��
				const ColoredPlane& pn5, // �ټ���° ��
				const ColoredPlane& pn6  // ������° ��
			)
			{
				return Create({ pn1, pn2, pn3, pn4, pn5, pn6 });
			}

			namespace indexed
			{
				[[nodiscard]]
				inline constexpr blob::IndexedColoredCube Create
				(
					const float x1, const float y1, const float z1, const Colour& c1, // ù��° ��
					const float x2, const float y2, const float z2, const Colour& c2, // �ι�° ��
					const float x3, const float y3, const float z3, const Colour& c3, // ����° ��
					const float x4, const float y4, const float z4, const Colour& c4, // �׹�° ��
					const float x5, const float y5, const float z5, const Colour& c5, // �ټ���° ��
					const float x6, const float y6, const float z6, const Colour& c6, // ������° ��
					const float x7, const float y7, const float z7, const Colour& c7, // �ϰ���° ��
					const float x8, const float y8, const float z8, const Colour& c8  // ������° ��
				)
				{
					return
					{
						x1, y1, z1, c1.r, c1.g, c1.b, c1.a,
						x2, y2, z2, c2.r, c2.g, c2.b, c2.a,
						x3, y3, z3, c3.r, c3.g, c3.b, c3.a,
						x4, y4, z4, c4.r, c4.g, c4.b, c4.a,
						x5, y5, z5, c5.r, c5.g, c5.b, c5.a,
						x6, y6, z6, c6.r, c6.g, c6.b, c6.a,
						x7, y7, z7, c7.r, c7.g, c7.b, c7.a,
						x8, y8, z8, c8.r, c8.g, c8.b, c8.a
					};
				}

				[[nodiscard]]
				inline constexpr blob::IndexedColoredCube Create
				(
					const Vertex& pt1, // ù��° ��
					const Vertex& pt2, // �ι�° ��
					const Vertex& pt3, // ����° ��
					const Vertex& pt4, // �׹�° ��
					const Vertex& pt5, // �ټ���° ��
					const Vertex& pt6, // ������° ��
					const Vertex& pt7, // �ϰ���° ��
					const Vertex& pt8  // ������° ��
				)
				{
					return
					{
						pt1.x, pt1.y, pt1.z, pt1.r, pt1.g, pt1.b, pt1.a,
						pt2.x, pt2.y, pt2.z, pt2.r, pt2.g, pt2.b, pt2.a,
						pt3.x, pt3.y, pt3.z, pt3.r, pt3.g, pt3.b, pt3.a,
						pt4.x, pt4.y, pt4.z, pt4.r, pt4.g, pt4.b, pt4.a,
						pt5.x, pt5.y, pt5.z, pt5.r, pt5.g, pt5.b, pt5.a,
						pt6.x, pt6.y, pt6.z, pt6.r, pt6.g, pt6.b, pt6.a,
						pt7.x, pt7.y, pt7.z, pt7.r, pt7.g, pt7.b, pt7.a,
						pt8.x, pt8.y, pt8.z, pt8.r, pt8.g, pt8.b, pt8.a,
					};
				}

				[[nodiscard]]
				inline constexpr blob::IndexedColoredCube Create
				(
					const float& width,
					const float& height,
					const float& depth,
					const Colour& color
				)
				{
					const float hw = width / 2;
					const float hh = height / 2;
					const float hd = depth / 2;

					return
					{
						-hw, +hh, -hd, color.r, color.g, color.b, color.a,
						-hw, +hh, +hd, color.r, color.g, color.b, color.a,
						+hw, +hh, +hd, color.r, color.g, color.b, color.a,
						+hw, +hh, -hd, color.r, color.g, color.b, color.a,
						-hw, -hh, -hd, color.r, color.g, color.b, color.a,
						-hw, -hh, +hd, color.r, color.g, color.b, color.a,
						+hw, -hh, +hd, color.r, color.g, color.b, color.a,
						+hw, -hh, -hd, color.r, color.g, color.b, color.a,
					};
				}

				[[nodiscard]]
				inline constexpr blob::IndexedColoredCube Create
				(
					const float& width,
					const float& height,
					const float& depth,
					const Colour(&colors)[8]
				)
				{
					const float hw = width / 2;
					const float hh = height / 2;
					const float hd = depth / 2;

					return
					{
						-hw, +hh, -hd, colors[0].r, colors[0].g, colors[0].b, colors[0].a,
						-hw, +hh, +hd, colors[1].r, colors[1].g, colors[1].b, colors[1].a,
						+hw, +hh, +hd, colors[2].r, colors[2].g, colors[2].b, colors[2].a,
						+hw, +hh, -hd, colors[3].r, colors[3].g, colors[3].b, colors[3].a,
						-hw, -hh, -hd, colors[4].r, colors[4].g, colors[4].b, colors[4].a,
						-hw, -hh, +hd, colors[5].r, colors[5].g, colors[5].b, colors[5].a,
						+hw, -hh, +hd, colors[6].r, colors[6].g, colors[6].b, colors[6].a,
						+hw, -hh, -hd, colors[7].r, colors[7].g, colors[7].b, colors[7].a,
					};
				}
			}
		}

		namespace tedra
		{

		}

		namespace line
		{
			[[nodiscard]]
			inline constexpr blob::Line Create
			(
				const float x1, const float y1, // ù��° ��
				const float x2, const float y2  // �ι�° ��
			)
			{
				return { x1, y1, x2, y2 };
			}

			[[nodiscard]]
			inline constexpr blob::Line Create
			(
				const Point& from, // ù��° ��
				const Point& to    // �ι�° ��
			)
			{
				return { from.x, from.y, to.x, to.y };
			}
		}

		namespace triangle
		{
			[[nodiscard]]
			inline constexpr blob::Triangle Create
			(
				const float x1, const float y1, // ù��° ��
				const float x2, const float y2, // �ι�° ��
				const float x3, const float y3  // ����° ��
			)
			{
				return { x1, y1, x2, y2, x3, y3 };
			}

			[[nodiscard]]
			inline constexpr blob::Triangle Create
			(
				const Point& pt1, // ù��° ��
				const Point& pt2, // �ι�° ��
				const Point& pt3  // ����° ��
			)
			{
				return { pt1, pt2, pt3 };
			}

			[[nodiscard]]
			inline constexpr blob::ColoredTriangle Create
			(
				const float x1, const float y1, // ù��° ��
				const Colour& color1,           // ù��° ���� ����
				const float x2, const float y2, // �ι�° ��
				const Colour& color2,           // �ι�° ���� ����
				const float x3, const float y3, // ����° ��
				const Colour& color3            // ����° ���� ����
			)
			{
				return
				{
					x1, y1, color1.r, color1.g, color1.b, color1.a,
					x2, y2, color2.r, color2.g, color2.b, color2.a,
					x3, y3, color3.r, color3.g, color3.b, color3.a
				};
			}

			[[nodiscard]]
			inline constexpr blob::ColoredTriangle Create
			(
				const Vertex2D& pt1, // ù��° ����
				const Vertex2D& pt2, // �ι�° ����
				const Vertex2D& pt3  // ����° ����
			)
			{
				return
				{
					pt1, pt2, pt3
				};
			}

			[[nodiscard]]
			inline constexpr blob::ColoredTriangle Create
			(
				const float x1, const float y1, // ù��° ��
				const float x2, const float y2, // �ι�° ��
				const float x3, const float y3, // ����° ��
				const Colour& color             // �ﰢ���� ����
			)
			{
				return Create(x1, y1, color, x2, y2, color, x3, y3, color);
			}

			namespace indexed
			{
				[[nodiscard]]
				inline constexpr blob::TriangleWithIndex Create
				(
					const float x1, const float y1, // ù��° ��
					const unsigned int index1,      // ù��° ���� ��ȣ
					const float x2, const float y2, // �ι�° ��
					const unsigned int index2,      // �ι�° ���� ��ȣ
					const float x3, const float y3, // ����° ��
					const unsigned int index3       // ����° ���� ��ȣ
				)
				{
					return std::make_pair
					(
						blob::triangle::Create(x1, y1, x2, y2, x3, y3),
						index::Triangles{ index1, index2, index3 }
					);
				}

				[[nodiscard]]
				inline constexpr blob::ColoredTriangleWithIndex Create
				(
					const float x1, const float y1, // ù��° ��
					const Colour& color1,           // ù��° ���� ����
					const unsigned int index1,      // ù��° ���� ��ȣ
					const float x2, const float y2, // �ι�° ��
					const Colour& color2,           // �ι�° ���� ����
					const unsigned int index2,      // �ι�° ���� ��ȣ
					const float x3, const float y3, // ����° ��
					const Colour& color3,           // ����° ���� ����
					const unsigned int index3       // ����° ���� ��ȣ
				)
				{
					return std::make_pair
					(
						blob::triangle::Create
						(
							x1, y1, color1,
							x2, y2, color2,
							x3, y3, color3
						),
						index::Triangles
						{
							index1, index2, index3
						}
					);
				}

				[[nodiscard]]
				inline constexpr blob::ColoredTriangleWithIndex Create
				(
					const float x1, const float y1, // ù��° ��
					const unsigned int index1,      // ù��° ���� ��ȣ
					const float x2, const float y2, // �ι�° ��
					const unsigned int index2,      // �ι�° ���� ��ȣ
					const float x3, const float y3, // ����° ��
					const unsigned int index3,      // ����° ���� ��ȣ
					const Colour& color             // �ﰢ���� ����
				)
				{
					return Create
					(
						x1, y1, color, index1,
						x2, y2, color, index2,
						x3, y3, color, index3
					);
				}
			}
		}

		namespace rectangle
		{
			[[nodiscard]]
			inline constexpr blob::Rectangle Create
			(
				const float x1, const float y1, // ù��° ��
				const float x2, const float y2, // �ι�° ��
				const float x3, const float y3, // ����° ��
				const float x4, const float y4  // ����° ��
			)
			{
				return { x1, y1, x2, y2, x3, y3, x4, y4 };
			}

			[[nodiscard]]
			inline constexpr blob::Rectangle Create
			(
				const float l, // ����
				const float t, // ����
				const float r, // ������
				const float b  // �Ʒ���
			)
			{
				return Create(l, t, l, b, r, b, r, t);
			}

			[[nodiscard]]
			inline constexpr blob::Rectangle Create
			(
				const Point& pt1, // ù��° ��
				const Point& pt2, // �ι�° ��
				const Point& pt3, // ����° ��
				const Point& pt4  // ����° ��
			)
			{
				return { pt1, pt2, pt3, pt4 };
			}

			[[nodiscard]]
			inline constexpr blob::Rectangle CreateFrom
			(
				const float x, const float y, // ���� �� ��
				const float width, // �ʺ�
				const float height // ����
			)
			{
				return Create
				(
					x, y,
					x + width, y,
					x + width, y + height,
					x, y + height
				);
			}

			[[nodiscard]]
			inline constexpr blob::Rectangle CreateFrom
			(
				const Point& pt, // ���� �� ��
				const float width, // �ʺ�
				const float height // ����
			)
			{
				return CreateFrom(pt.x, pt.y, width, height);
			}

			[[nodiscard]]
			inline constexpr blob::Rectangle CreateAt
			(
				const float x, const float y, // �߽���
				const float width, // �ʺ�
				const float height // ����
			)
			{
				return Create
				(
					x - width / 2, y + height / 2,
					x - width / 2, y - height / 2,
					x + width / 2, y - height / 2,
					x + width / 2, y + height / 2
				);
			}

			[[nodiscard]]
			inline constexpr blob::Rectangle CreateAt
			(
				const Point& centre, // �߽���
				const float width,   // �ʺ�
				const float height   // ����
			)
			{
				return CreateAt(centre.x, centre.y, width, height);
			}

			[[nodiscard]]
			inline constexpr blob::Rectangle CreateBy
			(
				const float width, // �ʺ�
				const float height // ����
			)
			{
				return CreateAt(0.0f, 0.0f, width, height);
			}

			[[nodiscard]]
			inline constexpr blob::ColoredRectangle Create
			(
				const Vertex2D& pt1, // ù��° ����
				const Vertex2D& pt2, // �ι�° ����
				const Vertex2D& pt3, // ����° ����
				const Vertex2D& pt4  // �׹�° ����
			)
			{
				return
				{
					pt1, pt2, pt3, pt4
				};
			}

			[[nodiscard]]
			inline constexpr blob::ColoredRectangle Create
			(
				const float x1, const float y1, // ù��° ��
				const Colour& color1,           // ù��° ���� ����
				const float x2, const float y2, // �ι�° ��
				const Colour& color2,           // �ι�° ���� ����
				const float x3, const float y3, // ����° ��
				const Colour& color3,           // ����° ���� ����
				const float x4, const float y4, // �׹�° ��
				const Colour& color4            // �׹�° ���� ����
			)
			{
				return
				{
					x1, y1, color1.r, color1.g, color1.b, color1.a,
					x2, y2, color2.r, color2.g, color2.b, color2.a,
					x3, y3, color3.r, color3.g, color3.b, color3.a,
					x4, y4, color4.r, color4.g, color4.b, color4.a
				};
			}

			[[nodiscard]]
			inline constexpr blob::ColoredRectangle Create
			(
				const float x1, const float y1, // ù��° ��
				const float x2, const float y2, // �ι�° ��
				const float x3, const float y3, // ����° ��
				const float x4, const float y4, // �׹�° ��
				const Colour& color             // �簢���� ����
			)
			{
				return Create
				(
					x1, y1, color,
					x2, y2, color,
					x3, y3, color,
					x4, y4, color
				);
			}

			[[nodiscard]]
			inline constexpr blob::ColoredRectangle Create
			(
				const float l,      // ����
				const float t,      // ����
				const float r,      // ������
				const float b,      // �Ʒ���
				const Colour& color // �簢���� ����
			)
			{
				return Create(l, t, l, b, r, b, r, t, color);
			}

			[[nodiscard]]
			inline constexpr blob::ColoredRectangle CreateFrom
			(
				const float x, const float y, // ���� �� ��
				const float width,  // �ʺ�
				const float height, // ����
				const Colour& color // �簢���� ����
			)
			{
				return Create
				(
					x, y, color,
					x + width, y, color,
					x + width, y + height, color,
					x, y + height, color
				);
			}

			[[nodiscard]]
			inline constexpr blob::ColoredRectangle CreateAt
			(
				const float x, const float y, // �߽���
				const float width,  // �ʺ�
				const float height, // ����
				const Colour& color // �簢���� ����
			)
			{
				return Create
				(
					x - width / 2, y - height / 2, color,
					x - width / 2, y + height / 2, color,
					x + width / 2, y + height / 2, color,
					x + width / 2, y - height / 2, color
				);
			}

			[[nodiscard]]
			inline constexpr blob::ColoredRectangle CreateBy
			(
				const float width,  // �ʺ�
				const float height, // ����
				const Colour& color // �簢���� ����
			)
			{
				return CreateAt(0.0f, 0.0f, width, height, color);
			}
		}

		namespace poly
		{
			template<size_t Vertices>
			[[nodiscard]]
			inline constexpr blob::Polygon<Vertices> Create
			(
				std::initializer_list<float> coords
			)
			{
				return { coords };
			}

			template<size_t Vertices>
			[[nodiscard]]
			inline constexpr blob::Polygon<Vertices> Create
			(
				std::initializer_list<Point> points
			)
			{
				return { points };
			}

			template<size_t Vertices>
			[[nodiscard]]
			inline constexpr blob::Polygon<Vertices> Create
			(
				std::initializer_list<Vertex2D> vertices
			)
			{
				return { vertices };
			}

			template<size_t Vertices>
			[[nodiscard]]
			inline constexpr blob::Polygon<Vertices> Create
			(
				std::span<Vertex2D, Vertices> vertices
			)
			{
				return { vertices.begin(), vertices.end() };
			}

			template<size_t Vertices>
			[[nodiscard]]
			inline constexpr blob::ColoredPolygon<Vertices> CreateWithColour
			(
				std::initializer_list<Vertex2D> vertices
			)
			{
				return { vertices };
			}
		}
	}
}
