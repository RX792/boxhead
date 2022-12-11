#pragma once

class AxisModelView : public ModelView
{
public:
	constexpr AxisModelView()
		: ModelView(ReferenceIndex)
	{}

	virtual void Render() override
	{
		ogl::Render(ogl::PRIMITIVE_TYPES::LINES, 6);
	}

	constinit inline static size_t ReferenceIndex = 1;
};

