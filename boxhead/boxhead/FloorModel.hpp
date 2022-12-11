#pragma once
#include "Model.hpp"

class FloorModelView : public ModelView
{
public:
	FloorModelView(const size_t& id)
		: ModelView(id)
	{}

	virtual void Render() override
	{
		ogl::Render(ogl::PRIMITIVE_TYPES::TRIANGLE_FAN, 4);
	}
};
