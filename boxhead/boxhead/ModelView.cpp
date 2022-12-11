#include "pch.hpp"
#include "ModelView.hpp"
#include "Framework.hpp"

ModelView::ModelView(const size_t& id)
	: myModel(Framework::Instance->GetModel(id))
{}

ModelView::ModelView(std::string_view name)
	: myModel(Framework::Instance->GetModel(name))
{}
