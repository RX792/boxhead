#include "pch.hpp"
#include "Model.hpp"
#include "Framework.hpp"

Model::Model(std::string_view name, const size_t& id)
	: myName(name)
	, bufferHandle(Framework::Instance->GetVertexBuffer(id))
{}

