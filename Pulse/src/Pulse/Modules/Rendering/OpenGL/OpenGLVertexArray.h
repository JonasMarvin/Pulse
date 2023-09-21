#pragma once

#include "Pulse/Modules/Rendering/VertexArray.h"

namespace Pulse::Modules::Rendering {

	// class to represent the OpenGL vertex array
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray(); // Constructor to create the OpenGL vertex array
		~OpenGLVertexArray(); // Destructor to destroy the OpenGL vertex array

		void Bind() const override; // Bind the OpenGL vertex array
		void Unbind() const override; // Unbind the OpenGL vertex array

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override; // Add a vertex buffer to the OpenGL vertex array
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override; // Set the index buffer of the OpenGL vertex array

		const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override; // Get the vertex buffers of the OpenGL vertex array
		const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override; // Get the index buffer of the OpenGL vertex array

	private:
		uint32_t rendererID_ = 0; // The ID of the OpenGL vertex array
		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers_; // The vertex buffers of the OpenGL vertex array
		std::shared_ptr<IndexBuffer> indexBuffer_ = nullptr; // The index buffer of the OpenGL vertex array
	}; // class OpenGLVertexArray

} // namespace Pulse::Modules::Rendering