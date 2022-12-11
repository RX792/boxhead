#pragma once
#include <Pipeline.hpp>
#include <VertexStream.hpp>

class ModelView
{
public:
	template<typename Ty, typename ...ArgTy>
		requires std::derived_from<Ty, ModelView>&& std::constructible_from<Ty, ArgTy...>
	static inline constexpr Ty CreateView(ArgTy&& ...args)
	{
		return Ty{ std::forward<ArgTy>(args)... };
	}

	template<typename Ty> requires std::derived_from<std::decay_t<Ty>, ModelView>
	static inline constexpr Ty GetReference()
	{
		return Ty{};
	}

	ModelView(const size_t& id);

	ModelView(std::string_view name);

	constexpr virtual ~ModelView() = default;

	constexpr bool IsAvailable() const noexcept;
	
	virtual void PrepareRendering(ogl::Pipeline& renderer);

	virtual void PrepareRendering();

	virtual void Render();

	static ogl::VertexStream::Buffer& GetRawBuffer(const size_t& id);

	Model* myModel;
};

inline constexpr bool ModelView::IsAvailable() const noexcept
{
	return nullptr != myModel;
}
