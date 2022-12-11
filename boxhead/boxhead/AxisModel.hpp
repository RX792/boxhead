#pragma once
#include "Model.hpp"

class AxisModelView : public ModelView
{
public:
	AxisModelView(const size_t& id)
		: ModelView(id)
	{}

	virtual void Render() override
	{
		ogl::Render(ogl::PRIMITIVE_TYPES::LINES, 6);
	}
};

