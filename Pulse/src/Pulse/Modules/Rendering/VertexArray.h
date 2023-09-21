#pragma once

#include <vector>

#include "Pulse/Modules/Rendering/Buffer.h"

namespace Pulse::Modules::Rendering {

	// interface class for vertex array. Implementation is API specific
	class VertexArray {
	public:
		virtual ~VertexArray() = default; // virtual destructor to ensure derived classes are destructed properly

		virtual void Bind() const = 0; // bind the vertex array
		virtual void Unbind() const = 0; // unbind the vertex array

		virtual void AddVertexBuffer(const VertexBuffer* vertexBuffer) = 0; // add a vertex buffer to the vertex array
		virtual void SetIndexBuffer(const IndexBuffer* indexBuffer) = 0; // set the index buffer of the vertex array

		virtual const std::vector<VertexBuffer*> GetVertexBuffers() const = 0; // get the vertex buffers of the vertex array
		virtual const IndexBuffer* GetIndexBuffer() const = 0; // get the index buffer of the vertex array

		static VertexArray* Create(); // factory method to create vertex array of the current API
	}; // class VertexArray

} // namespace Pulse::Modules::Rendering