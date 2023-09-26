#pragma once

#include "Pulse/Modules/Rendering/Texture.h"

namespace Pulse::Modules::Rendering {

	// Class for OpenGL 2D textures
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(const std::string& path); // constructor
		virtual ~OpenGLTexture2D(); // virtual destructor for proper cleanup

		uint32_t GetWidth() const override; // get width of texture
		uint32_t GetHeight() const override; // get height of texture

		void Bind(uint32_t slot) const override; // bind texture

	private:
		std::string path_ = "";
		uint32_t width_ = 0;
		uint32_t height_ = 0;

		uint32_t rendererID_ = 0;

	}; // class OpenGLTexture2D

} // namespace Pulse::Modules::Rendering