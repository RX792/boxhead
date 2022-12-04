#pragma once
#include "Model.hpp"

class SideCubeModel : public Model
{
public:
	SideCubeModel(const size_t& id)
		: Model(id)
	{}

	virtual void Render()
	{
		for (GLint i = 0; i < 6; i++)
		{
			ogl::Render(ogl::PRIMITIVE_TYPES::TRIANGLE_FAN, 4, i * 4);
		}
	}
};
