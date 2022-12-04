#pragma once
#include "Framework.hpp"

class Model
{
public:
	Model(const size_t& id)
		: myID(id)
		, modelBuffer(Framework::Instance->myVertexBuffer)
	{}

	virtual ~Model()
	{}

	virtual void PrepareRendering()
	{
		if (myID == size_t(-1))
			return;

		auto& buffer = modelBuffer.At(myID);
		buffer.PrepareRendering();
	}

	virtual void Render() = 0;

	const size_t myID;
	ogl::VertexStream& modelBuffer;
};
