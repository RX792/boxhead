#pragma once

class WorldManagers
{
public:
	void Awake(Scene* scene)
	{}
};

class Block
{
public:
	constexpr Block(size_t ix, size_t iy, const float& height = 1.0f)
		: x(ix), y(iy), myHeight(height)
	{}

	constexpr Block& operator=(const float& height)
	{
		myHeight = height;

		return *this;
	}

	explicit operator float() const
	{
		return myHeight;
	}

	size_t x, y;
	float myHeight;
};
