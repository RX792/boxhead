#pragma once
#include "Blobs.hpp"

namespace ogl
{
	class VertexStream
	{
	public:
		class Buffer
		{
		public:
			Buffer(const GLenum type = GL_ARRAY_BUFFER)
				: myID(), myType(type)
			{
				glGenBuffers(1, &myID);
			}

			~Buffer()
			{}

			inline void Bind(const void* blob, const GLsizeiptr size, const GLenum usage = GL_STATIC_DRAW)
			{
				glBindBuffer(myType, myID);
				glBufferData(myType, size, blob, usage);
			}

			template<typename Ty, size_t Size>
			inline void Bind(const Ty(&blob)[Size], const GLenum usage = GL_STATIC_DRAW)
			{
				Bind(blob, sizeof(blob), usage);
			}

			template<typename Ty, size_t Size>
			inline void Bind(const std::array<Ty, Size>& blob, const GLenum usage = GL_STATIC_DRAW)
			{
				Bind(blob.data(), sizeof(Ty) * Size, usage);
			}

			inline void PrepareRendering()
			{
				glBindBuffer(myType, myID);
			}

			inline constexpr const GLuint& GetID() const noexcept
			{
				return myID;
			}

			inline constexpr const GLuint& GetType() const noexcept
			{
				return myType;
			}

		private:
			GLuint myID;
			const GLenum myType;
		};

		constexpr VertexStream()
			: myBuffers()
		{}

		constexpr VertexStream(const std::size_t& reserved_length)
			: myBuffers()
		{
			myBuffers.reserve(reserved_length);
		}

		constexpr VertexStream(std::initializer_list<Buffer> buffers)
			: myBuffers(buffers)
		{}

		~VertexStream()
		{}

		inline VertexStream& operator<<(Buffer&& buffer)
		{
			myBuffers.push_back(std::forward<Buffer>(buffer));

			return *this;
		}

		inline VertexStream& operator<<(const Buffer& buffer)
		{
			myBuffers.push_back(buffer);

			return *this;
		}

		inline VertexStream& operator<<(std::tuple<GLenum, const void*, GLsizeiptr, GLenum> params)
		{
			auto& buffer = myBuffers.emplace_back(std::get<0>(params));

			buffer.Bind(std::get<1>(params), std::get<2>(params), std::get<3>(params));

			return *this;
		}

		template<typename Ty, size_t Size>
		inline VertexStream& operator<<(std::tuple<GLenum, const Ty(&)[Size], GLenum> params)
		{
			auto& buffer = myBuffers.emplace_back(std::get<0>(params));

			auto& blob = std::get<1>(params);
			auto& usage = std::get<2>(params);

			buffer.Bind(blob, sizeof(Ty) * Size, usage);

			return *this;
		}

		template<typename Ty, size_t Size>
		inline VertexStream& operator<<(const Ty(&blob)[Size])
		{
			auto& buffer = myBuffers.emplace_back(GL_ARRAY_BUFFER);

			buffer.Bind(blob, sizeof(blob), GL_STATIC_DRAW);

			return *this;
		}

		template<typename Ty, size_t Length, size_t Stride_length>
		inline VertexStream& operator<<(const blob::meta::BlobInterface<Ty, Length, Stride_length>& data)
		{
			using BlobType = blob::meta::BlobInterface<Ty, Length, Stride_length>;

			Buffer result{};
			result.Bind(data.data(), BlobType::alloc_size(), GL_STATIC_DRAW);
			Push(result);

			return *this;
		}

		/// <summary>
		/// 원본 버퍼를 삽입하고 반환합니다.
		/// </summary>
		/// <param name="buffer"></param>
		/// <returns>정점 스트림에 삽입된 원본 버퍼</returns>
		inline Buffer&
			Push(Buffer&& buffer)
		{
			return myBuffers.emplace_back(std::forward<Buffer>(buffer));
		}

		/// <summary>
		/// 복사본 버퍼를 삽입하고 반환합니다.
		/// </summary>
		/// <param name="buffer"></param>
		/// <returns>정점 스트림에 삽입된 원본 버퍼</returns>
		inline Buffer&
			Push(const Buffer& buffer)
		{
			return myBuffers.emplace_back(buffer);
		}

		/// <summary>
		/// 지정한 핸들로부터 버퍼를 바로 만들고 삽입한 후 반환합니다.
		/// </summary>
		/// <param name="blob"></param>
		/// <param name="size"></param>
		/// <param name="usage"></param>
		/// <returns>정점 스트림에 삽입된 원본 버퍼</returns>
		inline Buffer&
			Push(const void* blob, const GLsizeiptr& size, const GLenum& usage = GL_STATIC_DRAW)
		{
			Buffer result{};
			result.Bind(blob, size, usage);

			return Push(result);
		}

		/// <summary>
		/// 미리 만들어진 정점 객체들의 묶음을 삽입합니다.
		/// </summary>
		/// <param name="blobs"></param>
		template<size_t Count>
		inline Buffer&
			PushRaw(const ogl::blob::Vertex (&vertices)[Count])
		{
			constexpr size_t count_max = Count * 7;
			float refined[count_max]{};

			size_t index = 0;
			for (size_t i = 0; i < Count; i++)
			{
				const ogl::blob::Vertex& vertex = vertices[i];
				refined[index++] = vertex.x;
				refined[index++] = vertex.y;
				refined[index++] = vertex.z;
				refined[index++] = vertex.r;
				refined[index++] = vertex.g;
				refined[index++] = vertex.b;
				refined[index++] = vertex.a;
			}

			return Push(refined);
		}

		/// <summary>
		/// 배열로부터 버퍼를 바로 만들고 삽입한 후 반환합니다.
		/// </summary>
		/// <param name="blob"></param>
		/// <param name="usage"></param>
		/// <returns>정점 스트림에 삽입된 원본 버퍼</returns>
		template<typename Ty, size_t Count>
		inline Buffer&
			Push(const Ty(&blob)[Count], const GLenum& usage = GL_STATIC_DRAW)
		{
			Buffer result{};
			result.Bind(blob, usage);

			return Push(result);
		}

		/// <summary>
		/// 지정한 배열의 포인터와 길이로 버퍼를 바로 만들고 삽입한 후 반환합니다.
		/// </summary>
		/// <param name="blob"></param>
		/// <param name="count"></param>
		/// <param name="[usage]"></param>
		/// <returns>정점 스트림에 삽입된 원본 버퍼</returns>
		template<typename Ty>
		inline Buffer&
			Push(const Ty blob[], size_t count, const GLenum& usage = GL_STATIC_DRAW)
		{
			//static_assert(false);
			std::vector<Ty> refined{};

			Buffer result{};
			result.Bind(blob, usage);

			return Push(result);
		}

		/// <summary>
		/// 미리 만들어진 블롭 객체로 정점 버퍼를 만들고 삽입한 후 반환합니다.
		/// </summary>
		/// <param name="data"></param>
		/// <param name="usage"></param>
		/// <returns>정점 스트림에 삽입된 원본 버퍼</returns>
		template<typename Ty, size_t Length, size_t Stride_length>
		inline Buffer&
			Push(const blob::meta::BlobInterface<Ty, Length, Stride_length>& data, const GLenum& usage = GL_STATIC_DRAW)
		{
			using BlobType = blob::meta::BlobInterface<Ty, Length, Stride_length>;

			Buffer result{};
			result.Bind(data.data(), BlobType::alloc_size(), usage);
			return Push(result);
		}

		/// <summary>
		/// 정점의 정보 배열로 버퍼를 만들고 삽입한 후 반환합니다.
		/// </summary>
		/// <param name="blob"></param>
		/// <param name="usage"></param>
		/// <returns>정점 스트림에 삽입된 원본 버퍼</returns>
		inline Buffer&
			Push(const blob::TriangleWithIndex& blob, const GLenum& usage = GL_STATIC_DRAW)
		{
			return Push(blob.first);
		}

		/// <summary>
		/// 버퍼 묶음을 삽입합니다.
		/// </summary>
		/// <param name="buffers"></param>
		inline void
			Push(std::initializer_list<Buffer> buffers)
		{
			for (auto it = buffers.begin(); buffers.end() != it; it++)
			{
				Push(*it);
			}
		}

		inline void Swap(VertexStream& other)
		{
			myBuffers.swap(other.myBuffers);
		}

		/// <summary>
		/// 특정 정점 버퍼에 대하여 데이터를 할당합니다.
		/// </summary>
		/// <param name="index">버퍼의 위치 인덱스</param>
		/// <param name="blob"></param>
		/// <param name="size"></param>
		/// <param name="usage"></param>
		inline void Bind(const std::size_t& index, const void* blob, const GLsizeiptr& size, const GLenum& usage = GL_STATIC_DRAW)
		{
			myBuffers.at(index).Bind(blob, size, usage);
		}

		/// <summary>
		/// 모든 정점 버퍼에 대하여 같은 데이터를 할당합니다.
		/// </summary>
		/// <param name="blob"></param>
		/// <param name="size"></param>
		/// <param name="usage"></param>
		inline void Bind(const void* blob, const GLsizeiptr size, const GLenum usage = GL_STATIC_DRAW)
		{
			std::for_each(myBuffers.begin(), myBuffers.end(), [&](Buffer& vbo) {
				vbo.Bind(blob, size, usage);
			});
		}

		/// <summary>
		/// 모든 정점 버퍼에 대하여 같은 데이터를 할당합니다.
		/// </summary>
		template<typename Ty, size_t Size>
		inline void Bind(const Ty(&blob)[Size], const GLenum usage = GL_STATIC_DRAW)
		{
			std::for_each(myBuffers.begin(), myBuffers.end(), [&](Buffer& vbo) {
				vbo.Bind(blob, sizeof(Ty) * Size, usage);
			});
		}

		inline constexpr Buffer& At(const size_t& index)
		{
			return myBuffers.at(index);
		}

		inline constexpr const Buffer& At(const size_t& index) const
		{
			return myBuffers.at(index);
		}

		inline constexpr const size_t Size() const noexcept
		{
			return myBuffers.size();
		}

		inline void PrepareRendering()
		{
			std::for_each(myBuffers.begin(), myBuffers.end(), [&](Buffer& vbo) {
				vbo.PrepareRendering();
			});
		}

	private:
		std::vector<Buffer> myBuffers;
	};

	static inline
		VertexStream
		CreateVertex()
	{
		return VertexStream{};
	}

	static inline
		VertexStream::Buffer
		CreateBuffer(const GLenum type = GL_ARRAY_BUFFER)
	{
		return VertexStream::Buffer{ type };
	}
}
