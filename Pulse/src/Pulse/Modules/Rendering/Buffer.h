#pragma once

#include <string>

namespace Pulse::Modules::Rendering {

	// enum class to represent the data type of a shader element
	enum class ShaderDataType {
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	}; // enum class ShaderDataType

	static uint32_t ShaderDataTypeSize(ShaderDataType type) { // get the size of the shader data type
		switch (type) {
			case ShaderDataType::Float:		return 4;
			case ShaderDataType::Float2:	return 4 * 2;
			case ShaderDataType::Float3:	return 4 * 3;
			case ShaderDataType::Float4:	return 4 * 4;
			case ShaderDataType::Mat3:		return 4 * 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4 * 4;
			case ShaderDataType::Int:		return 4;
			case ShaderDataType::Int2:		return 4 * 2;
			case ShaderDataType::Int3:		return 4 * 3;
			case ShaderDataType::Int4:		return 4 * 4;
		case ShaderDataType::Bool:		return 1;
		}

		PLS_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	} 

	// structure to represent a single element of the buffer layout
	struct BufferElement {
		ShaderDataType Type; // data type of the element
		std::string Name; // name of the element
		uint32_t Size; // size of the element
		uint32_t Offset; // offset of the element
		bool Normalized; // whether the element is normalized

		BufferElement() = default; // default constructor to create an empty buffer element
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false) : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {}; // constructor to create a buffer element from a data type and a name

		uint32_t GetComponentCount() const; // get the number of components of the buffer type
	}; // struct BufferElement

	// class to represent the buffer layout of a vertex buffer
	class BufferLayout {
	public:
		BufferLayout() = default; // default constructor to create an empty buffer layout
		BufferLayout(const std::initializer_list<BufferElement>& elements); // constructor to create the buffer layout from a list of buffer elements

		const std::vector<BufferElement>& GetElements() const;// get the elements of the buffer layout
		const uint32_t GetStride() const; // get the stride of the buffer layout

		std::vector<BufferElement>::iterator begin(); // get the begin iterator of the buffer layout
		std::vector<BufferElement>::iterator end(); // get the end iterator of the buffer layout
		std::vector<BufferElement>::const_iterator begin() const; // get the begin iterator of the buffer layout (const)
		std::vector<BufferElement>::const_iterator end() const; // get the end iterator of the buffer layout (const)
	private:
		void CalculateOffsetsAndStride(); // calculate the offsets and stride of the buffer layout

		std::vector<BufferElement> elements_; // elements of the buffer layout
		uint32_t stride_ = 0; // stride of the buffer layout
	}; // class BufferLayout

	// interface class for vertex buffer. Implementation is API specific
	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default; // virtual destructor to ensure derived classes are destructed properly
		
		virtual void Bind() const = 0; // bind the vertex buffer
		virtual void Unbind() const = 0; // unbind the vertex buffer

		virtual const BufferLayout& GetLayout() const = 0; // get the buffer layout of the vertex buffer
		virtual void SetLayout(const BufferLayout& layout) = 0; // set the buffer layout of the vertex buffer

		static std::shared_ptr<VertexBuffer> Create(float* vertices, uint32_t size); // factory method to create vertex buffer of the current API
	}; // class VertexBuffer

	// interface class for index buffer. Implementation is API specific
	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default; // virtual destructor to ensure derived classes are destructed properly

		virtual void Bind() const = 0; // bind the index buffer
		virtual void Unbind() const = 0; // unbind the index buffer
		
		virtual uint32_t GetCount() const = 0; // get the number of indices in the index buffer

		static std::shared_ptr<IndexBuffer> Create(uint32_t* indices, uint32_t size); // factory method to create index buffer of the current API
	}; // class IndexBuffer

} // namespace Pulse::Modules::Rendering