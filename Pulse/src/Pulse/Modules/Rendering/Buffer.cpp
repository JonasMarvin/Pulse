#include "pch.h"

#include "Pulse/Modules/Rendering/Buffer.h"
#include "Pulse/Modules/ModuleManager.h"
#include "Pulse/Modules/Rendering/RendererModule.h"
#include "Pulse/Modules/Rendering/OpenGL/OpenGLBuffer.h"

namespace Pulse::Modules::Rendering {

	// Implementation of BufferElement
	uint32_t BufferElement::GetComponentCount() const {
		switch (Type) {
			case ShaderDataType::Float:		return 1;
			case ShaderDataType::Float2:	return 2;
			case ShaderDataType::Float3:	return 3;
			case ShaderDataType::Float4:	return 4;
			case ShaderDataType::Mat3:		return 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4;
			case ShaderDataType::Int:		return 1;
			case ShaderDataType::Int2:		return 2;
			case ShaderDataType::Int3:		return 3;
			case ShaderDataType::Int4:		return 4;
			case ShaderDataType::Bool:		return 1;
		}

		PLS_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	// Implementation of BufferLayout
	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements) : elements_(elements) {
		CalculateOffsetsAndStride();
	}

	const std::vector<BufferElement>& BufferLayout::GetElements() const {
		return elements_;
	}

	const uint32_t BufferLayout::GetStride() const {
		return stride_;
	}

	std::vector<BufferElement>::iterator BufferLayout::begin() {
		return elements_.begin();
	}

	std::vector<BufferElement>::iterator BufferLayout::end() {
		return elements_.end();
	}

	std::vector<BufferElement>::const_iterator BufferLayout::begin() const {
		return elements_.begin();
	}

	std::vector<BufferElement>::const_iterator BufferLayout::end() const {
		return elements_.end();
	}

	void BufferLayout::CalculateOffsetsAndStride() {
		uint32_t offset = 0;
		stride_ = 0;
		for (auto& element : elements_) {
			element.Offset = offset;
			offset += element.Size;
			stride_ += element.Size;
		}
	}

	// Implementation of VertexBuffer
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (ModuleManager::GetInstance().GetModule<RendererModule>()->GetRendererAPIType()) {
			case RendererAPI::Type::None:		PLS_CORE_ASSERT(false, "RendererAPI::None is currently not supported by VertexBuffer!");	return nullptr;
			case RendererAPI::Type::OpenGL:																									return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		PLS_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}

	// Implementation of IndexBuffer
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size) {
		switch (ModuleManager::GetInstance().GetModule<RendererModule>()->GetRendererAPIType()) {
			case RendererAPI::Type::None:		PLS_CORE_ASSERT(false, "RendererAPI::None is currently not supported by IndexBuffer!");	return nullptr;
			case RendererAPI::Type::OpenGL:																								return CreateRef<OpenGLIndexBuffer>(indices, size);
		}

		PLS_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}

} // namespace Pulse::Modules::Rendering