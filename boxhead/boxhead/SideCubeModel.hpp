#pragma once

class SideCubeModel : public Model
{
public:
	constexpr SideCubeModel(std::string_view name, ogl::VertexStream::Buffer& buffer)
		: Model(name, buffer)
	{}

	virtual void Render() const override
	{
		for (GLint i = 0; i < 6; i++)
		{
			ogl::Render(ogl::PRIMITIVE_TYPES::TRIANGLE_FAN, 4, i * 4);
		}
	}

	static constexpr size_t GetID()
	{
		return ReferenceIndex;
	}

	constinit inline static size_t ReferenceIndex = 0;
};
