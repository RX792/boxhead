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
				throw "쉐이더 파일의 경로가 정해지지 않음!";
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
				error << " 쉐이더 파일 " << path.filename() << "을(를) 불러오는데 실패!\n";

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
					throw std::runtime_error(std::format("쉐이더 유형 {}을 만들 수 없습니다!", Type));
				}

				const auto& blob = shaderCode.c_str();
				const auto length = GLint(shaderCode.length());

				// 쉐이더 코드를 쉐이더 오브젝트에 할당
				glShaderSource(myID, 1, &blob, &length);

				// 할당된 쉐이더 코드를 컴파일
				glCompileShader(myID);

				// 성공적으로 컴파일 되었는지 확인
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

					// OpenGL의 결과를 가져옴
					glGetShaderInfoLog(myID, 1024, NULL, InfoLog);

					std::stringstream error{};
					error << " 쉐이더 " << std::hex << this << "(타입: " << Type << ") 에서 " << std::dec << " 컴파일 실패!\n로그: " << InfoLog << "\n쉐이더 코드: " << blob << '\n';

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
