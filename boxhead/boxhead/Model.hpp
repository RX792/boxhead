#pragma once
#include <VertexStream.hpp>

class Model
{
protected:
	constexpr Model(std::string_view name, ogl::VertexStream::Buffer& buffer)
		: myName(name)
		, bufferHandle(buffer)
	{}

public:
	Model(std::string_view name, const size_t& id);

	virtual ~Model() = default;

	void PrepareRendering() const
	{
		bufferHandle.PrepareRendering();
	}

	virtual void Render() const = 0;

	static constexpr size_t GetID()
	{
		return -1;
	}

	std::string myName;
	ogl::VertexStream::Buffer& bufferHandle;

	friend class Framework;
};

template<typename Ty>
concept ModelType = std::derived_from<std::decay_t<Ty>, Model>;
