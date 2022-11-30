#pragma once

namespace ogl
{
	class Attribute
	{
	public:
		constexpr Attribute(const GLint id, const GLsizei stride = 0, const GLenum type = GL_FLOAT)
			: myID(id)
			, writeType(type), writeStride(stride)
		{}

		/// <summary>
		/// glVertexAttribPointer(myID, length, type, GL_FALSE, stride, begin);
		/// </summary>
		/// <param name="type">버퍼 유형</param>
		/// <param name="length">정점 버퍼를 읽어들일 바이트 길이</param>
		/// <param name="stride">정점 버퍼 내ㄴ의 구분 간격</param>
		/// <param name="begin">정점 버퍼를 읽기 시작하는 위치</param>
		inline void Assign(const GLenum type
			, const GLint length
			, const GLsizei stride = 0
			, const GLvoid* begin = nullptr) const
		{
			glVertexAttribPointer(myID, length, type, GL_FALSE, stride, begin);
		}

		/// <summary>
		/// glVertexAttribPointer(myID, length, writeType, GL_FALSE, writeStride, begin);
		/// </summary>
		/// <param name="length">정점 버퍼를 읽어들일 바이트 길이</param>
		/// <param name="begin">정점 버퍼를 읽기 시작하는 위치</param>
		inline void Assign(const GLint length, const size_t begin = 0) const
		{
			Assign(writeType, length, writeStride, (GLvoid*) (begin));
		}

		inline void EnableVertexArray() const
		{
			glEnableVertexAttribArray(myID);
		}

		inline void DisableVertexArray() const
		{
			glDisableVertexAttribArray(myID);
		}

		friend class Pipeline;

	private:
		const GLint myID;

		GLenum writeType;
		GLsizei writeStride;
	};
}
