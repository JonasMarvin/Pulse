#include "pch.h"

#include "OpenGLTexture.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Pulse::Modules::Rendering {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : path_(path) {
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		PLS_CORE_ASSERT(data, "Failed to load image!");
		width_ = width;
		height_ = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4) {
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		} else if (channels == 3) {
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		PLS_CORE_ASSERT(internalFormat && dataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &rendererID_);
		glTextureStorage2D(rendererID_, 1, internalFormat, width_, height_);

		glTextureParameteri(rendererID_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(rendererID_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(rendererID_, 0, 0, 0, width_, height_, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1, &rendererID_);
	}

	uint32_t OpenGLTexture2D::GetWidth() const {
		return width_;
	}

	uint32_t OpenGLTexture2D::GetHeight() const {
		return height_;
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const {
		glBindTextureUnit(slot, rendererID_);
	}

} // namespace Pulse::Modules::Rendering