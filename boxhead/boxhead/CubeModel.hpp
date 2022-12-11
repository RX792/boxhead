#pragma once

class CubeModel : public Model
{
public:
	constexpr CubeModel(std::string_view name, ogl::VertexStream::Buffer& buffer)
		: Model(name, buffer)
	{}

	virtual void Render() const override
	{
		ogl::Render(ogl::PRIMITIVE_TYPES::TRIANGLE_FAN, 24, 0);
	}

	static constexpr size_t GetID()
	{
		return ReferenceIndex;
	}

	constinit inline static size_t ReferenceIndex = 0;
};
