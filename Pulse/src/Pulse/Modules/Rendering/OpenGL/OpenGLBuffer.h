#pragma once

#include "Pulse/Modules/Rendering/Buffer.h"

#include <glad/glad.h>

namespace Pulse::Modules::Rendering {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) { // function to convert ShaderDataType to OpenGL base type
		switch (type) {
			case ShaderDataType::Float:		return GL_FLOAT;
			case ShaderDataType::Float2:	return GL_FLOAT;
			case ShaderDataType::Float3:	return GL_FLOAT;
			case ShaderDataType::Float4:	return GL_FLOAT;
			case ShaderDataType::Mat3:		return GL_FLOAT;
			case ShaderDataType::Mat4:		return GL_FLOAT;
			case ShaderDataType::Int:		return GL_INT;
			case ShaderDataType::Int2:		return GL_INT;
			case ShaderDataType::Int3:		return GL_INT;
			case ShaderDataType::Int4:		return GL_INT;
			case ShaderDataType::Bool:		return GL_BOOL;
		}

		PLS_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	// Implementation of VertexBuffer for OpenGL
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size); // constructor to create vertex buffer
		~OpenGLVertexBuffer(); // destructor to ensure derived classes are destructed properly

		void Bind() const override; // bind the vertex buffer
		void Unbind() const override; // unbind the vertex buffer

		const BufferLayout& GetLayout() const override; // get the buffer layout of the vertex buffer
		void SetLayout(const BufferLayout& layout) override; // set the buffer layout of the vertex buffer
	private:
		uint32_t rendererID_ = 0; // ID of the vertex buffer in the renderer
		BufferLayout layout_; // buffer layout of the vertex buffer
	}; // class OpenGLVertexBuffer

	// Implementation of IndexBuffer for OpenGL
	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count); // constructor to create index buffer
		~OpenGLIndexBuffer(); // destructor to ensure derived classes are destructed properly

		void Bind() const override; // bind the index buffer
		void Unbind() const override; // unbind the index buffer

		uint32_t GetCount() const override; // get the number of indices in the index buffer
	private:
		uint32_t rendererID_ = 0; // ID of the vertex buffer in the renderer
		uint32_t count_ = 0; // number of indices in the index buffer
	}; // class OpenGLIndexBuffer

} // namespace Pulse::Modules::Rendering