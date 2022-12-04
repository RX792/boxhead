#include "pch.hpp"
#include "Model.hpp"
#include "Framework.hpp"

Model::Model(const size_t& id)
	: myID(id)
{}

Model::~Model()
{}

void Model::SetID(const size_t & id)
{
	myID = id;
}

ogl::VertexStream::Buffer& Model::GetRawBuffer(const size_t& id)
{
	return Framework::Instance->myVertexBuffer.At(id);
}

void Model::PrepareRendering()
{
	if (myID == size_t(-1))
		return;

	auto& buffer = GetRawBuffer(myID);
	buffer.PrepareRendering();
}
