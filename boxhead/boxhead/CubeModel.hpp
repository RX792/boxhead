#pragma once
#include "Model.hpp"

class CubeModel : public Model
{
public:
	CubeModel(const size_t& id)
		: Model(id)
	{}

	virtual void Render()
	{
		ogl::Render(ogl::PRIMITIVE_TYPES::TRIANGLE_FAN, 24, 0);
	}
};
