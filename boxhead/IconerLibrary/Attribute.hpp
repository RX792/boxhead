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
		/// <param name="type">���� ����</param>
		/// <param name="length">���� ���۸� �о���� ����Ʈ ����</param>
		/// <param name="stride">���� ���� ������ ���� ����</param>
		/// <param name="begin">���� ���۸� �б� �����ϴ� ��ġ</param>
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
		/// <param name="length">���� ���۸� �о���� ����Ʈ ����</param>
		/// <param name="begin">���� ���۸� �б� �����ϴ� ��ġ</param>
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
