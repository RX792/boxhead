#pragma once

namespace ogl
{
	class Shader
	{
	public:
		constexpr Shader()
			: Shader(0, "")
		{}

		constexpr Shader(GLenum type)
			: Shader(type, "")
		{}

		constexpr Shader(GLenum type, const Path& path)
			: myID(0) ,Type(type)
			, shaderFile(path), blobStatus(), codeStatus()
			, programID(NULL)
		{}

		Shader(const Shader& other) = delete;
		Shader& operator=(const Shader& other) = delete;

		~Shader()
		{
			if (NULL != Detach())
			{
				glDeleteShader(myID);
			}
		}

		inline void Load()
		{
			if (!IsLoaded() && shaderFile.empty())
			{
				throw "���̴� ������ ��ΰ� �������� ����!";
			}

			return Load(shaderFile);
		}

		inline void Load(const Path& path)
		{
			std::ifstream file{ path };

			if (file.fail())
			{
				blobStatus = BLOB_STATES::UNLOADED;
				file.close();

				std::stringstream error{};
				error << " ���̴� ���� " << path.filename() << "��(��) �ҷ����µ� ����!\n";

				throw std::runtime_error(error.str());
			}

			std::string line{};
			while (std::getline(file, line))
			{
				shaderCode.append(line.c_str());
				shaderCode.append("\n");
			}

			blobStatus = BLOB_STATES::LOADED;

			file.close();
		}

		inline bool Compile()
		{
			codeStatus = CODE_STATES::FAILED;

			if (IsLoaded())
			{
				myID = glCreateShader(Type);
				if (NULL == myID)
				{
					throw std::runtime_error(std::format("���̴� ���� {}�� ���� �� �����ϴ�!", Type));
				}

				const auto& blob = shaderCode.c_str();
				const auto length = GLint(shaderCode.length());

				// ���̴� �ڵ带 ���̴� ������Ʈ�� �Ҵ�
				glShaderSource(myID, 1, &blob, &length);

				// �Ҵ�� ���̴� �ڵ带 ������
				glCompileShader(myID);

				// ���������� ������ �Ǿ����� Ȯ��
				GLint success{};
				glGetShaderiv(myID, GL_COMPILE_STATUS, &success);

				if (success)
				{
					codeStatus = CODE_STATES::SUCCEED;
					return true;
				}
				else
				{
					GLchar InfoLog[1024]{};

					// OpenGL�� ����� ������
					glGetShaderInfoLog(myID, 1024, NULL, InfoLog);

					std::stringstream error{};
					error << " ���̴� " << std::hex << this << "(Ÿ��: " << Type << ") ���� " << std::dec << " ������ ����!\n�α�: " << InfoLog << "\n���̴� �ڵ�: " << blob << '\n';

					throw std::runtime_error(error.str());
				}
			}

			return false;
		}

		inline void Attach(const GLuint pipeline)
		{
			programID = pipeline;
			glAttachShader(programID, myID);
		}

		inline GLint SafeAttach(const GLuint pipeline)
		{
			if (pipeline != programID)
			{
				auto result = Detach();
				Attach(pipeline);
				return pipeline;
			}

			return NULL;
		}

		inline GLint Detach()
		{
			auto result = programID;
			if (NULL != programID)
			{
				glDetachShader(programID, myID);
			}

			return result;
		}

		inline constexpr bool IsUnloaded() const noexcept
		{
			return BLOB_STATES::UNLOADED == blobStatus;
		}

		inline constexpr bool IsLoaded() const noexcept
		{
			return BLOB_STATES::LOADED == blobStatus;
		}

		inline constexpr bool IsCompiled() const noexcept
		{
			return IsLoaded() && IsSucceed();
		}

		inline constexpr bool IsSucceed() const noexcept
		{
			return CODE_STATES::SUCCEED == codeStatus;
		}

		inline constexpr bool IsFailed() const noexcept
		{
			return !IsCompiled();
		}

		enum class BLOB_STATES : unsigned char
		{
			UNLOADED, LOADED
		};

		enum class CODE_STATES : unsigned char
		{
			NONE, SUCCEED, FAILED
		};

		GLuint programID;
		Path shaderFile;
		std::string shaderCode;

		GLuint myID;
		GLenum Type;
		BLOB_STATES blobStatus;
		CODE_STATES codeStatus;
	};
}
