#pragma once

class FloorModel : public Model
{
public:
	constexpr FloorModel(std::string_view name, ogl::VertexStream::Buffer& buffer)
		: Model(name, buffer)
	{}

	virtual void Render() const override
	{
		ogl::Render(ogl::PRIMITIVE_TYPES::TRIANGLE_FAN, 4);
	}

	static constexpr size_t GetID()
	{
		return ReferenceIndex;
	}

	constinit inline static size_t ReferenceIndex = 2;
};
