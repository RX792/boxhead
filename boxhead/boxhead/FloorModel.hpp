#pragma once
#include "Model.hpp"

class FloorModel : public Model
{
public:
	FloorModel(const size_t& id)
		: Model(id)
	{}

	virtual void Render()
	{
		ogl::Render(ogl::PRIMITIVE_TYPES::TRIANGLE_FAN, 4);
	}
};
