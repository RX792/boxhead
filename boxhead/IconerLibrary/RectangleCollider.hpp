#pragma once
#include "Collider.hpp"
#include "Utils.hpp"
#include "Prototypes.hpp"

class RectangleCollider : public Collider
{
public:
	constexpr RectangleCollider()
		: RectangleCollider(0.0f, 0.0f)
	{}

	constexpr RectangleCollider(const float proj_x, const float proj_y, const float size = 0.1f)
		: RectangleCollider(proj_x - size, proj_x + size, proj_y + size, proj_y - size)
	{}

	constexpr RectangleCollider(float left, float right, float top, float bottom)
		:  Collider()
		, myPosition{ left, top, right, bottom }
		, myWidth(right - left), myHeight(top - bottom)
	{}

	constexpr ~RectangleCollider()
	{}

	inline constexpr
		std::pair<bool, bool>
		MoveBounds(const int view_w, const int view_h, float ax, float ay)
	{
		bool collide_h = false;
		bool collide_v = false;

		MoveToward(ax, ay);

		float bound_l = GetLeft();
		float bound_r = GetRight();
		float bound_b = GetBottom();
		float bound_t = GetTop();

		float addr_h = 0, addr_v = 0;
		if (bound_l < -1.0f)
		{
			collide_h = true;

			addr_h = -(bound_l + 1.0f);
		}
		else if (1.0f <= bound_r)
		{
			collide_h = true;

			addr_h = 1.0f - bound_r;
		}

		if (bound_b < -1.0f)
		{
			collide_v = true;

			addr_v = -(bound_b + 1.0f);
		}
		else if (1.0f <= bound_t)
		{
			collide_v = true;

			addr_v = 1.0f - bound_t;
		}

		if (0 != addr_h || 0 != addr_v)
		{
			MoveToward(addr_h, addr_v);
		}

		return std::make_pair(collide_h, collide_v);
	}

	inline constexpr void JumpTo(const float tx, const float ty)
	{
		const auto cx = GetCenterX();
		const auto cy = GetCenterY();

		const auto gx = (tx - cx);
		const auto gy = (ty - cy);
		MoveToward(gx, gy);
	}

	inline constexpr void JumpTo(const Positions& pos)
	{
		myPosition = pos;
	}

	inline constexpr void MoveToward(float ax, float ay)
	{
		myPosition.left += ax;
		myPosition.right += ax;

		myPosition.top += ay;
		myPosition.bottom += ay;
	}

	inline constexpr void JumpToScreen(const int view_w, const int view_h, const int tx, const int ty)
	{
		const auto [px, py] = ogl::CalcProjectedCoords(view_w, view_h, tx, ty);

		JumpTo(px, py);
	}

	inline constexpr void MoveTowardOnScreen(const int view_w, const int view_h, const int ax, const int ay)
	{
		const auto [px, py] = ogl::CalcProjectedCoords(view_w, view_h, ax, ay);

		MoveToward(px, py);
	}

	inline constexpr float GetCenterX() const noexcept
	{
		return (myPosition.right + myPosition.left) * 0.5f;
	}

	inline constexpr float GetCenterY() const noexcept
	{
		return (myPosition.bottom + myPosition.top) * 0.5f;
	}

	inline constexpr const float& GetWidth() const noexcept
	{
		return myWidth;
	}

	inline constexpr const float& GetHeight() const noexcept
	{
		return myHeight;
	}

	inline constexpr float GetLeft() const noexcept
	{
		return myPosition.left;
	}

	inline constexpr float GetRight() const noexcept
	{
		return myPosition.right;
	}

	inline constexpr float GetTop() const noexcept
	{
		return myPosition.top;
	}

	inline constexpr float GetBottom() const noexcept
	{
		return myPosition.bottom;
	}

	inline constexpr int GetLeftOnScreen(const int view_w) const noexcept
	{
		return ogl::CalcOnScreen(view_w, myPosition.left);
	}

	inline constexpr int GetRightOnScreen(const int view_w) const noexcept
	{
		return ogl::CalcOnScreen(view_w, myPosition.right);
	}

	inline constexpr int GetTopOnScreen(const int view_h) const noexcept
	{
		return ogl::CalcOnScreen(view_h, myPosition.top);
	}

	inline constexpr int GetBottomOnScreen(const int view_h) const noexcept
	{
		return ogl::CalcOnScreen(view_h, myPosition.bottom);
	}

	inline constexpr bool IsCollided(const RectangleCollider& other) const noexcept
	{
		return !(GetRight() <= other.GetLeft()
			|| GetTop() <= other.GetBottom()
			|| other.GetRight() < GetLeft()
			|| other.GetTop() < GetBottom());
	}

	inline constexpr bool IsCollided(const Positions& other) const noexcept
	{
		return !(GetRight() <= other.left
			|| GetTop() <= other.bottom
			|| other.right < GetLeft()
			|| other.top < GetBottom());
	}

	inline constexpr bool IsCollided(const ogl::Point& projected_point) const noexcept
	{
		return GetLeft() <= projected_point.x
			&& projected_point.x < GetRight()
			&& GetBottom() <= projected_point.y
			&& projected_point.y < GetTop();
	}

	inline constexpr bool IsCollided(const int view_w, const int view_h, const POINT& screen_point) const noexcept
	{
		return GetLeftOnScreen(view_w) <= screen_point.x
			&& screen_point.x < GetRightOnScreen(view_w)
			&& GetBottomOnScreen(view_h) <= screen_point.y
			&& screen_point.y < GetTopOnScreen(view_h);
	}

	inline constexpr bool IsHover(const int view_w, const int view_h, const int mx, const int my) const noexcept
	{
		return GetLeftOnScreen(view_w) <= mx
			&& view_h - GetTopOnScreen(view_h) <= my
			&& mx < GetRightOnScreen(view_w)
			&& my < view_h - GetBottomOnScreen(view_h);
	}

	inline constexpr void SetWidth(const float w)
	{
		const auto cx = GetCenterX();
		myPosition.left = cx - w * 0.5f;
		myPosition.right = cx + w * 0.5f;

		myWidth = w;
	}

	inline constexpr void SetHeight(const float h)
	{
		const auto cy = GetCenterY();
		myPosition.bottom = cy - h * 0.5f;
		myPosition.top = cy + h * 0.5f;

		myHeight = h;
	}

	inline constexpr void Resize(const float w, const float h)
	{
		SetWidth(w);
		SetHeight(h);
	}

	float myWidth, myHeight;
	Positions myPosition;
};
