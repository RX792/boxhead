#pragma once

class Model
{
protected:
	Model(ogl::VertexStream::Buffer&);

public:
	Model(const size_t& id);

	Model(std::string_view name);

	void PrepareRendering(ogl::Pipeline& renderer);

	void PrepareRendering();

	void Render();

	ogl::VertexStream::Buffer& bufferHandle;

	friend class Framework;
};
