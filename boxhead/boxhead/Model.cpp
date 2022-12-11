#include "pch.hpp"
#include "Model.hpp"
#include "Framework.hpp"

ModelView::ModelView(const size_t& id)
	: myID(id)
{}

ModelView::~ModelView()
{}

void ModelView::SetID(const size_t & id)
{
	myID = id;
}

ogl::VertexStream::Buffer& ModelView::GetRawBuffer(const size_t& id)
{
	return Framework::Instance->myVertexBuffer.At(id);
}

void ModelView::PrepareRendering(ogl::Pipeline& renderer)
{}

void ModelView::PrepareRendering()
{
	if (myID == size_t(-1))
		return;

	auto& buffer = GetRawBuffer(myID);
	buffer.PrepareRendering();
}
