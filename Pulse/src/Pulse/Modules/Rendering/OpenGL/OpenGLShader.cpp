#include "pch.h"

#include <filesystem>
#include <fstream>

#include "Pulse/Modules/Rendering/OpenGL/OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Pulse::Modules::Rendering {

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource) : name_(name) {
		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSource;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSource;
		Compile(shaderSources);
	}

	OpenGLShader::OpenGLShader(const std::string& filepath) {
		std::filesystem::path canonicalPath = std::filesystem::canonical(filepath);

		std::string shaderSource = ReadFile(canonicalPath.string());
		auto shaderSources = ProcessShaderSource(shaderSource);
		Compile(shaderSources);

		name_ = canonicalPath.stem().string();
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& filepath) : name_(name) {
		std::filesystem::path canonicalPath = std::filesystem::canonical(filepath);

		std::string shaderSource = ReadFile(canonicalPath.string());
		auto shaderSources = ProcessShaderSource(shaderSource);
		Compile(shaderSources);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(rendererID_);
	}

	void OpenGLShader::Bind() const {
		glUseProgram(rendererID_);
	}

	void OpenGLShader::Unbind() const {
		glUseProgram(0);
	}

	const std::string& OpenGLShader::GetName() const {
		return name_;
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value) {
		GLint location = glGetUniformLocation(rendererID_, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value) {
		GLint location = glGetUniformLocation(rendererID_, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values) {
		GLint location = glGetUniformLocation(rendererID_, name.c_str());
		glUniform2f(location, values.x, values.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values) {
		GLint location = glGetUniformLocation(rendererID_, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values) {
		GLint location = glGetUniformLocation(rendererID_, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix) {
		GLint location = glGetUniformLocation(rendererID_, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) {
		GLint location = glGetUniformLocation(rendererID_, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath) {
		std::filesystem::path canonicalPath = std::filesystem::canonical(filepath);

		std::ifstream in(canonicalPath, std::ios::in | std::ios::binary);
		
		if (!in) {
			PLS_CORE_ERROR("Could not open file '{0}'", canonicalPath.string());
			PLS_CORE_ASSERT(false, "Could not open file!");
			return "";
		}

		std::string result;
		result.resize(std::filesystem::file_size(canonicalPath));
		in.read(&result[0], result.size());
		in.close();

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::ProcessShaderSource(const std::string& shaderSource) {
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = shaderSource.find(typeToken, 0);
		while (pos != std::string::npos) {
			size_t eol = shaderSource.find_first_of("\r\n", pos);
			PLS_CORE_ASSERT(eol != std::string::npos, "Syntax error!");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = shaderSource.substr(begin, eol - begin);
			PLS_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified!");

			size_t nextLinePos = shaderSource.find_first_not_of("\r\n", eol);
			PLS_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error!");
			pos = shaderSource.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = shaderSource.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? shaderSource.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	GLenum OpenGLShader::ShaderTypeFromString(const std::string& type) {
		if(type == "vertex")						return GL_VERTEX_SHADER;
		if(type == "fragment" || type == "pixel")	return GL_FRAGMENT_SHADER;

		PLS_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources) {
		GLuint program = glCreateProgram();
		PLS_CORE_ASSERT(shaderSources.size() <= 2, "Only two shaders are supported for now!");
		std::array<GLenum, 2> glShaderIDs = { 0, 0 };
		int glShaderIDIndex = 0;
		for (auto& keyValue : shaderSources) {
			GLenum shaderType = keyValue.first;
			const std::string& shaderSource = keyValue.second;

			GLuint shader = glCreateShader(shaderType);

			const GLchar* source = shaderSource.c_str();
			glShaderSource(shader, 1, &source, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE) {
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				PLS_CORE_ERROR("Shader compilation failed! Log: {0}", infoLog.data());
				PLS_CORE_ASSERT(false, "Shader compilation failed!");
				break;
			}
			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}
		
		glLinkProgram(program);
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			for (auto id : glShaderIDs) {
				glDeleteShader(id);
			}

			PLS_CORE_ERROR("Shader linking failed! Log: {0}", infoLog.data());
			PLS_CORE_ASSERT(false, "Shader linking failed!");
			return;
		}

		for (auto id : glShaderIDs) {
			glDetachShader(program, id);
		}

		rendererID_ = program;
	}

} // namespace Pulse::Modules::Rendering