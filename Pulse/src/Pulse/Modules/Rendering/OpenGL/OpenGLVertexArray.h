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

		void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override; // Add a vertex buffer to the OpenGL vertex array
		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override; // Set the index buffer of the OpenGL vertex array

		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override; // Get the vertex buffers of the OpenGL vertex array
		const Ref<IndexBuffer>& GetIndexBuffer() const override; // Get the index buffer of the OpenGL vertex array

	private:
		uint32_t rendererID_ = 0; // The ID of the OpenGL vertex array
		std::vector<Ref<VertexBuffer>> vertexBuffers_; // The vertex buffers of the OpenGL vertex array
		Ref<IndexBuffer> indexBuffer_ = nullptr; // The index buffer of the OpenGL vertex array
	}; // class OpenGLVertexArray

} // namespace Pulse::Modules::Rendering