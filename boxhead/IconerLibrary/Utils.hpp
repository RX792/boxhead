#pragma once

namespace ogl
{
	/// <summary>
	/// ������ ȭ�� ���� X ��ǥ�� -1 ~ +1 ������ OpenGL ���� ��ǥ�� ��ȯ�մϴ�.
	/// </summary>
	/// <param name="view_size">ȭ�� �ʺ�</param>
	/// <param name="position">ȭ�� ���� X ��ǥ</param>
	/// <returns>���� ��ǥ</returns>
	inline constexpr float
		CalcProjectedX
		(const int view_size, const int position)
	{
		return float(position) / float(view_size) * 2.0f - 1.0f;
	}
	/// <summary>
	/// ������ ȭ�� ���� Y ��ǥ�� -1 ~ +1 ������ OpenGL ���� ��ǥ�� ��ȯ�մϴ�.
	/// </summary>
	/// <param name="view_size">ȭ�� ����</param>
	/// <param name="position">ȭ�� ���� Y ��ǥ</param>
	/// <returns>���� ��ǥ</returns>
	inline constexpr float
		CalcProjectedY
		(const int view_size, const int position)
	{
		return -CalcProjectedX(view_size, position);
	}

	float CalcProjectedX(const int, const std::floating_point auto position) = delete;
	float CalcProjectedY(const int, const std::floating_point auto position) = delete;

	/// <summary>
	/// OpenGL�� ���� ��ǥ�� ������ ȭ�� ���� ��ǥ�� ��ȯ�մϴ�.
	/// </summary>
	/// <param name="view_size">ȭ�� �ʺ� �Ǵ� ����</param>
	/// <param name="position">���� ��ǥ</param>
	/// <returns>ȭ�� ��ǥ</returns>
	inline constexpr int
		CalcOnScreen
		(const int view_size, const float position)
	{
		return static_cast<int>(((position + 1.0f) * 0.5f) * view_size);
	}
	int CalcOnScreen(const int, const std::integral auto position) = delete;

	/// <summary>
	/// ȭ�� ��ǥ �� ���� -1 ~ +1 ������ OpenGL ���� ��ǥ�� ��ȯ�մϴ�.
	/// </summary>
	/// <param name="view_w">ȭ�� �ʺ�</param>
	/// <param name="view_h">ȭ�� ����</param>
	/// <param name="screen_x">ȭ�� ���� X ��ǥ</param>
	/// <param name="screen_y">ȭ�� ���� Y ��ǥ</param>
	/// <returns>���� ��ǥ</returns>
	inline constexpr const std::pair<float, float>
		CalcProjectedCoords
		(
			const int view_w,
			const int view_h,
			const int screen_x,
			const int screen_y
		)
	{
		return std::make_pair
		(
			CalcProjectedX(view_w, screen_x),
			CalcProjectedY(view_h, screen_y)
		);
	}

	/// <summary>
	/// ȭ�� ��ǥ �� ���� -1 ~ +1 ������ OpenGL ���� ��ǥ�� ��ȯ�մϴ�.
	/// </summary>
	/// <param name="view_w">ȭ�� �ʺ�</param>
	/// <param name="view_h">ȭ�� ����</param>
	/// <param name="screen_coords">ȭ�� ���� ��ǥ ��</param>
	/// <returns>���� ��ǥ</returns>
	inline constexpr const std::pair<float, float>
		CalcProjectedCoords
		(
			const int view_w,
			const int view_h,
			const std::pair<int, int> screen_coords
		)
	{
		return CalcProjectedCoords(view_w, view_h, screen_coords.first, screen_coords.second);
	}

	inline constexpr const std::pair<int, int>
		CalcScreenCoords
		(
			const int view_w,
			const int view_h,
			const float proj_x,
			const float proj_y
		)
	{
		return std::make_pair
		(
			CalcOnScreen(view_w, proj_x),
			CalcOnScreen(view_h, proj_y)
		);
	}

	inline constexpr void CutExtensions(std::string& filename) noexcept
	{
		const std::vector<std::string> extensions{ ".glsl", ".vs", ".fs" };
		for (auto& ext : extensions)
		{
			auto fn_span = std::search(filename.begin(), filename.end(), ext.cbegin(), ext.cend());

			if (filename.end() != fn_span)
			{
				filename.erase(fn_span, filename.end());
				break;
			}
		}
	}

	inline constexpr std::string CutExtensions(const std::string& filename) noexcept
	{
		std::string result{};

		const std::vector<std::string> extensions{ ".glsl", ".vs", ".fs" };
		for (auto& ext : extensions)
		{
			auto fn_span = std::search(filename.cbegin(), filename.cend(), ext.cbegin(), ext.cend());

			if (filename.end() != fn_span)
			{
				result.assign(filename.cbegin(), fn_span);
				break;
			}
		}

		return result;
	}
}

namespace
{
	inline constexpr float degtorad(float angle)
	{
		return angle * std::numbers::pi_v<float> / 180.0f;
	}

	inline constexpr float radtodeg(float angle)
	{
		return angle * 180.0f / std::numbers::pi_v<float>;
	}

	inline float lengthdir_x(float distance, float degree)
	{
		return std::cos(degtorad(degree)) * distance;
	}

	inline float lengthdir_y(float distance, float degree)
	{
		return std::sin(degtorad(degree)) * distance;
	}

	inline constexpr float Dot(float x1, float y1, float z1, float x2, float y2, float z2)
	{
		return x1 * x2 + y1 * y2 + z1 * z2;
	}

	inline constexpr float Dot(float x1, float y1, float x2, float y2)
	{
		return x1 * x2 + y1 * y2;
	}

	inline constexpr std::array<float, 3> Cross(float x1, float y1, float z1, float x2, float y2, float z2)
	{
		return { y1 * z2 - z1 * y2, z1 * x2 - x1 * z2, x1 * y2 - y1 * x2 };
	}

	inline constexpr std::array<float, 2> Cross(float x1, float y1, float x2, float y2)
	{
		return { x1 * y2 - y1 * x2 };
	}

	inline constexpr float Square(float x1, float y1, float x2, float y2)
	{
		return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
	}

	inline float Distance(float x1, float y1, float x2, float y2)
	{
		return std::sqrt(Square(x1, y1, x2, y2));
	}
}
