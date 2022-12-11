#pragma once

class AxisModel : public Model
{
public:
	constexpr AxisModel(std::string_view name, ogl::VertexStream::Buffer& buffer)
		: Model(name, buffer)
	{}

	virtual void Render() const override
	{
		ogl::Render(ogl::PRIMITIVE_TYPES::LINES, 6);
	}

	static constexpr size_t GetID()
	{
		return ReferenceIndex;
	}

	constinit inline static size_t ReferenceIndex = 1;
};
