#pragma once

class CubeModelView : public ModelView
{
public:
	constexpr CubeModelView()
		: ModelView(ReferenceIndex)
	{}

	virtual void Render() override
	{
		ogl::Render(ogl::PRIMITIVE_TYPES::TRIANGLE_FAN, 24, 0);
	}

	constinit inline static size_t ReferenceIndex = 0;
};
