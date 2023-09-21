#include "pch.h"

#include "Pulse/Modules/Rendering/OpenGL/OpenGLBuffer.h"

namespace Pulse::Modules::Rendering {

	// Vertex buffer implementation
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
		glCreateBuffers(1, &rendererID_);
		glBindBuffer(GL_ARRAY_BUFFER, rendererID_);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		glDeleteBuffers(1, &rendererID_);
	}

	void OpenGLVertexBuffer::Bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, rendererID_);
	}

	void OpenGLVertexBuffer::Unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	const BufferLayout& OpenGLVertexBuffer::GetLayout() const {
		return layout_;
	}

	void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout) {
		layout_ = layout;
	}

	// Index buffer implementation
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : count_(count) {
		;
		glCreateBuffers(1, &rendererID_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count_ * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		glDeleteBuffers(1, &rendererID_);
	}

	void OpenGLIndexBuffer::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID_);
	}

	void OpenGLIndexBuffer::Unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	uint32_t OpenGLIndexBuffer::GetCount() const {
		return count_;
	}

} // namespace Pulse::Modules::Rendering