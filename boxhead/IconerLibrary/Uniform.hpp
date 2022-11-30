#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "BasicBlobs.hpp"

namespace ogl
{
	class Uniform
	{
	public:
		constexpr Uniform(const GLint id)
			: myID(id)
		{}

		inline void AssignMatrix4x4(const glm::mat4& matrix)
		{
			glUniformMatrix4fv(myID, 1, GL_FALSE, glm::value_ptr(matrix));
		}

		inline void AssignMatrix3x3(const glm::mat3& matrix)
		{
			glUniformMatrix3fv(myID, 1, GL_FALSE, glm::value_ptr(matrix));
		}

		inline void Assign(const int arg0)
		{
			glUniform1i(myID, arg0);
		}

		inline void Assign(const int arg0, const int arg1)
		{
			glUniform2i(myID, arg0, arg1);
		}

		inline void Assign(const int arg0, const int arg1, const int arg2)
		{
			glUniform3i(myID, arg0, arg1, arg2);
		}

		inline void Assign(const int arg0, const int arg1, const int arg2, const int arg3)
		{
			glUniform4i(myID, arg0, arg1, arg2, arg3);
		}

		template<size_t Length>
		inline void Assign(const int(&datas)[Length])
		{
			glUniform1iv(myID, Length, datas);
		}

		inline void Assign(const float arg0)
		{
			glUniform1f(myID, arg0);
		}

		inline void Assign(const float arg0, const float arg1)
		{
			glUniform2f(myID, arg0, arg1);
		}

		inline void Assign(const float arg0, const float arg1, const float arg2)
		{
			glUniform3f(myID, arg0, arg1, arg2);
		}

		inline void Assign(const float arg0, const float arg1, const float arg2, const float arg3)
		{
			glUniform4f(myID, arg0, arg1, arg2, arg3);
		}

		inline void AssignArray4(const float* datas, GLsizei count)
		{
			glUniform4fv(myID, count, datas);
		}

		inline void AssignArray3(const float* datas, GLsizei count)
		{
			glUniform3fv(myID, count, datas);
		}

		inline void AssignArray2(const float* datas, GLsizei count)
		{
			glUniform2fv(myID, count, datas);
		}

		inline void AssignArray1(const float* datas, GLsizei count)
		{
			glUniform1fv(myID, count, datas);
		}

		inline void AssignArray(const float(&datas)[4])
		{
			glUniform4fv(myID, 4, datas);
		}

		inline void AssignArray(const float(&datas)[3])
		{
			glUniform3fv(myID, 3, datas);
		}

		inline void AssignArray(const float(&datas)[2])
		{
			glUniform2fv(myID, 2, datas);
		}

		inline void AssignArray(const float(&datas)[1])
		{
			glUniform1fv(myID, 1, datas);
		}

		inline void Assign(const ogl::Colour& color)
		{
			glUniform4f(myID, color.r, color.g, color.b, color.a);
		}

		inline void Assign(const float(&datas)[4])
		{
			glUniform4f(myID, datas[0], datas[1], datas[2], datas[3]);
		}

		inline void Assign(const float(&datas)[3])
		{
			glUniform3f(myID, datas[0], datas[1], datas[2]);
		}

		inline void Assign(const float(&datas)[2])
		{
			glUniform2f(myID, datas[0], datas[1]);
		}

		inline void Assign(const float(&datas)[1])
		{
			glUniform1f(myID, datas[0]);
		}

		inline void Assign(const int(&datas)[4])
		{
			glUniform4i(myID, datas[0], datas[1], datas[2], datas[3]);
		}

		inline void Assign(const int(&datas)[3])
		{
			glUniform3i(myID, datas[0], datas[1], datas[2]);
		}

		inline void Assign(const int(&datas)[2])
		{
			glUniform2i(myID, datas[0], datas[1]);
		}

		inline void Assign(const int(&datas)[1])
		{
			glUniform1i(myID, datas[0]);
		}

		inline void Assign(const bool arg0)
		{
			glUniform1i(myID, arg0);
		}

	private:
		const GLint myID;
	};
}
