#pragma once

#include <glm/glm.hpp>

namespace Pulse::Modules::Rendering {

	// virtual class for RendererAPI calls
	class RendererAPI {
	public:
		enum class API {
			None = 0,
			OpenGL = 1
		}; // enum class API

		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;

		virtual void DrawIndexed() = 0;

	}; // class RendererAPI

} // namespace Pulse::Modules::Rendering