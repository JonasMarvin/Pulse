#pragma once

#include <vector>
#include <memory>

#include "Pulse/Modules/Rendering/Buffer.h"

namespace Pulse::Modules::Rendering {

	// interface class for vertex array. Implementation is API specific
	class VertexArray {
	public:
		virtual ~VertexArray() = default; // virtual destructor to ensure derived classes are destructed properly

		virtual void Bind() const = 0; // bind the vertex array
		virtual void Unbind() const = 0; // unbind the vertex array

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0; // add a vertex buffer to the vertex array
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0; // set the index buffer of the vertex array

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0; // get the vertex buffers of the vertex array
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0; // get the index buffer of the vertex array

		static Ref<VertexArray> Create(); // factory method to create vertex array of the current API
	}; // class VertexArray

} // namespace Pulse::Modules::Rendering