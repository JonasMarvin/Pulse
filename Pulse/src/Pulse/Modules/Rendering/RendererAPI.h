#pragma once

#include <glm/glm.hpp>
#include "Pulse/Modules/Rendering/VertexArray.h"

namespace Pulse::Modules::Rendering {

	// virtual class for render API commands
	class RendererAPI {
	public:
		// enum class for render API
		enum class Type {
			None = 0,
			OpenGL = 1
		}; // enum class API

		virtual ~RendererAPI() = default; // virtual destructor for inheritance

		virtual void SetClearColor(const glm::vec4& color) = 0; // virtual function for setting the clear color
		virtual void Clear() = 0; // virtual function for clearing the screen

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0; // virtual function for drawing the indexed vertex array

		virtual const Type GetAPIType() const = 0; // virtual function for getting the render API

		static RendererAPI* Create(Type api); // static function for creating the render API
	}; // class RendererAPI

} // namespace Pulse::Modules::Rendering