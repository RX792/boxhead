#pragma once
#include "Model.hpp"

class AxisModel : public Model
{
public:
	AxisModel(const size_t& id)
		: Model(id)
	{}

	virtual void Render()
	{
		ogl::Render(ogl::PRIMITIVE_TYPES::LINES, 6);
	}
};

