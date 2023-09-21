#include "pch.h"

#include "Pulse/Modules/Rendering/OpenGL/OpenGLVertexArray.h"
#include "Pulse/Modules/Rendering/OpenGL/OpenGLBuffer.h"

#include <glad/glad.h>

namespace Pulse::Modules::Rendering {

	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &rendererID_);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &rendererID_);
	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(rendererID_);
	}

	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}
	
	void OpenGLVertexArray::AddVertexBuffer(const VertexBuffer* vertexBuffer) {
		glBindVertexArray(rendererID_);
		vertexBuffer->Bind();

		PLS_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");

		BufferLayout layout = vertexBuffer->GetLayout();
		uint32_t index = 0;
		for (auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

		vertexBuffers_.push_back((VertexBuffer*)vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const IndexBuffer* indexBuffer) {
		glBindVertexArray(rendererID_);
		indexBuffer->Bind();

		indexBuffer_ = (IndexBuffer*)indexBuffer;
	}

	const std::vector<VertexBuffer*> OpenGLVertexArray::GetVertexBuffers() const {
		return vertexBuffers_;
	}

	const IndexBuffer* OpenGLVertexArray::GetIndexBuffer() const {
		return indexBuffer_;
	}

} // namespace Pulse::Modules::Rendering