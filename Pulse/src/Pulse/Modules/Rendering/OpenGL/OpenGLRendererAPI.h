#pragma once

#include "Pulse/Modules/Rendering/RendererAPI.h"

namespace Pulse::Modules::Rendering {

	// class for OpenGL rendering API calls
	class OpenGLRendererAPI : public RendererAPI {
	public:
		virtual ~OpenGLRendererAPI() = default; // virtual destructor for proper cleanup

		void SetClearColor(const glm::vec4& color) override; // set clear color
		void Clear() override; // clear screen

		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override; // draw indexed vertex array

		const Type GetAPIType() const override; // get API type
	private:
		RendererAPI::Type api_ = RendererAPI::Type::OpenGL; // API type
	}; // class OpenGLRendererAPI

} // namespace Pulse::Modules::Rendering