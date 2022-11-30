#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace ogl
{
#pragma pack(push, 1)
	using Point = glm::vec2;
	using Quad = glm::vec3;

	struct Colour
	{
		constexpr Colour(float r, float g, float b, float a) noexcept
			: r(r), g(g), b(b), a(a)
		{}

		constexpr Colour() noexcept
			: Colour(1.0f, 1.0f, 1.0f, 1.0f)
		{}

		constexpr Colour(float r, float g, float b) noexcept
			: Colour(r, g, b, 1.0f)
		{}

		constexpr Colour(Colour&& other) noexcept
			: Colour(std::forward<float>(other.r), std::forward<float>(other.g), std::forward<float>(other.b), std::forward<float>(other.a))
		{}

		constexpr Colour(const Colour& other) noexcept
			: Colour(other.r, other.g, other.b, other.a)
		{}

		constexpr Colour(const std::span<float> color) noexcept
			: Colour(color.begin(), color.end())
		{}

		template<std::forward_iterator It, std::sentinel_for<It> Guard>
		constexpr Colour(It begin, const Guard end)
			: Colour
			(
				*(begin++),
				(begin != end) ? *(begin++) : 1.0f,
				(begin != end) ? *(begin++) : 1.0f,
				(begin != end) ? *(begin++) : 1.0f
			)
		{
			std::cout << "!!\n";
		}

		inline constexpr Colour& operator=(Colour&& other) noexcept
		{
			r = std::forward<float>(other.r);
			g = std::forward<float>(other.g);
			b = std::forward<float>(other.b);
			a = std::forward<float>(other.a);

			return *this;
		}

		inline constexpr Colour& operator=(const Colour& other) noexcept
		{
			r = other.r;
			g = other.g;
			b = other.b;
			a = other.a;

			return *this;
		}

		float r, g, b, a;
	};
}
#pragma pack(pop)
