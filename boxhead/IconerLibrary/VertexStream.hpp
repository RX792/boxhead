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
		/// ���� ���۸� �����ϰ� ��ȯ�մϴ�.
		/// </summary>
		/// <param name="buffer"></param>
		/// <returns>���� ��Ʈ���� ���Ե� ���� ����</returns>
		inline Buffer&
			Push(Buffer&& buffer)
		{
			return myBuffers.emplace_back(std::forward<Buffer>(buffer));
		}

		/// <summary>
		/// ���纻 ���۸� �����ϰ� ��ȯ�մϴ�.
		/// </summary>
		/// <param name="buffer"></param>
		/// <returns>���� ��Ʈ���� ���Ե� ���� ����</returns>
		inline Buffer&
			Push(const Buffer& buffer)
		{
			return myBuffers.emplace_back(buffer);
		}

		/// <summary>
		/// ������ �ڵ�κ��� ���۸� �ٷ� ����� ������ �� ��ȯ�մϴ�.
		/// </summary>
		/// <param name="blob"></param>
		/// <param name="size"></param>
		/// <param name="usage"></param>
		/// <returns>���� ��Ʈ���� ���Ե� ���� ����</returns>
		inline Buffer&
			Push(const void* blob, const GLsizeiptr& size, const GLenum& usage = GL_STATIC_DRAW)
		{
			Buffer result{};
			result.Bind(blob, size, usage);

			return Push(result);
		}

		/// <summary>
		/// �̸� ������� ���� ��ü���� ������ �����մϴ�.
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
		/// �迭�κ��� ���۸� �ٷ� ����� ������ �� ��ȯ�մϴ�.
		/// </summary>
		/// <param name="blob"></param>
		/// <param name="usage"></param>
		/// <returns>���� ��Ʈ���� ���Ե� ���� ����</returns>
		template<typename Ty, size_t Count>
		inline Buffer&
			Push(const Ty(&blob)[Count], const GLenum& usage = GL_STATIC_DRAW)
		{
			Buffer result{};
			result.Bind(blob, usage);

			return Push(result);
		}

		/// <summary>
		/// ������ �迭�� �����Ϳ� ���̷� ���۸� �ٷ� ����� ������ �� ��ȯ�մϴ�.
		/// </summary>
		/// <param name="blob"></param>
		/// <param name="count"></param>
		/// <param name="[usage]"></param>
		/// <returns>���� ��Ʈ���� ���Ե� ���� ����</returns>
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
		/// �̸� ������� ��� ��ü�� ���� ���۸� ����� ������ �� ��ȯ�մϴ�.
		/// </summary>
		/// <param name="data"></param>
		/// <param name="usage"></param>
		/// <returns>���� ��Ʈ���� ���Ե� ���� ����</returns>
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
		/// ������ ���� �迭�� ���۸� ����� ������ �� ��ȯ�մϴ�.
		/// </summary>
		/// <param name="blob"></param>
		/// <param name="usage"></param>
		/// <returns>���� ��Ʈ���� ���Ե� ���� ����</returns>
		inline Buffer&
			Push(const blob::TriangleWithIndex& blob, const GLenum& usage = GL_STATIC_DRAW)
		{
			return Push(blob.first);
		}

		/// <summary>
		/// ���� ������ �����մϴ�.
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
		/// Ư�� ���� ���ۿ� ���Ͽ� �����͸� �Ҵ��մϴ�.
		/// </summary>
		/// <param name="index">������ ��ġ �ε���</param>
		/// <param name="blob"></param>
		/// <param name="size"></param>
		/// <param name="usage"></param>
		inline void Bind(const std::size_t& index, const void* blob, const GLsizeiptr& size, const GLenum& usage = GL_STATIC_DRAW)
		{
			myBuffers.at(index).Bind(blob, size, usage);
		}

		/// <summary>
		/// ��� ���� ���ۿ� ���Ͽ� ���� �����͸� �Ҵ��մϴ�.
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
		/// ��� ���� ���ۿ� ���Ͽ� ���� �����͸� �Ҵ��մϴ�.
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
