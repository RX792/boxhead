#pragma once

class FloorModelView : public ModelView
{
public:
	constexpr FloorModelView()
		: ModelView(ReferenceIndex)
	{}

	virtual void Render() override
	{
		ogl::Render(ogl::PRIMITIVE_TYPES::TRIANGLE_FAN, 4);
	}

	constinit inline static size_t ReferenceIndex = 2;
};
