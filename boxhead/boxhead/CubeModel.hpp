#pragma once
#include "Model.hpp"

class CubeModelView : public ModelView
{
public:
	CubeModelView(const size_t& id)
		: ModelView(id)
	{}

	virtual void Render() override
	{
		ogl::Render(ogl::PRIMITIVE_TYPES::TRIANGLE_FAN, 24, 0);
	}
};
