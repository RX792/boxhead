#pragma once
#include <VertexStream.hpp>

class Model
{
public:
	template<typename Ty, typename ...ArgTy>
		requires ModelType<Ty, ArgTy...>
	static Ty Get(ArgTy&& ...args)
	{
		return Ty{ std::forward<ArgTy>(args)... };
	}

	Model(const size_t& id);

	virtual ~Model();
	
	void SetID(const size_t& id);

	static ogl::VertexStream::Buffer& GetRawBuffer(const size_t& id);
	
	virtual void PrepareRendering();

	virtual void Render() = 0;

	size_t myID;
};

template<typename Ty, typename ...ArgTy>
concept ModelType = std::derived_from<Ty, Model> && std::constructible_from<Ty, ArgTy...>;

template<typename Ty, typename ...ArgTy>
concept RefModelType = std::derived_from<Ty, Model> && std::constructible_from<Ty, size_t, std::remove_cv_t<ArgTy>...>;