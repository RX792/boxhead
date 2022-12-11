#pragma once
#include "Model.hpp"

class ModelView
{
public:
	template<typename Ty> requires std::derived_from<std::decay_t<Ty>, Model>
	static inline ModelView GetReference()
	{
		return ModelView{ Ty::GetID() };
	}

	static inline ModelView GetReference(const size_t& id)
	{
		return ModelView{ id };
	}

	static inline ModelView GetReference(std::string_view name)
	{
		return ModelView{ name };
	}
	
	constexpr ModelView()
		: myModel(nullptr)
	{}

	constexpr ModelView(Model* const model)
		: myModel(model)
	{}

	ModelView(const size_t& id);

	ModelView(std::string_view name);

	constexpr ~ModelView() = default;

	constexpr bool IsAvailable() const noexcept
	{
		return nullptr != myModel;
	}
	
	void PrepareRendering() const
	{
		if (myModel)
		{
			myModel->PrepareRendering();
		}
	}

	void Render() const
	{
		if (myModel)
		{
			myModel->Render();
		}
	}

	Model* myModel;
};
