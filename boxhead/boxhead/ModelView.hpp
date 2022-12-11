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

	constexpr ModelView(const size_t& id);

	constexpr virtual ~ModelView();
	
	constexpr void SetID(const size_t& id);

	static ogl::VertexStream::Buffer& GetRawBuffer(const size_t& id);
	
	virtual void PrepareRendering(ogl::Pipeline& renderer);

	virtual void PrepareRendering();

	virtual void Render() = 0;

	size_t myID;
};

constexpr ModelView::ModelView(const size_t& id)
	: myID(id)
{}

constexpr ModelView::~ModelView()
{}

constexpr void ModelView::SetID(const size_t& id)
{
	myID = id;
}
