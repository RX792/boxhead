#pragma once

class SideCubeModelView : public ModelView
{
public:
	constexpr SideCubeModelView()
		: ModelView(ReferenceIndex)
	{}

	constexpr SideCubeModelView(const size_t& id)
		: ModelView(id)
	{}

	virtual void Render() override
	{
		for (GLint i = 0; i < 6; i++)
		{
			ogl::Render(ogl::PRIMITIVE_TYPES::TRIANGLE_FAN, 4, i * 4);
		}
	}

	constinit inline static size_t ReferenceIndex = 0;
};
