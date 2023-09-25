#pragma once

#include <string>

#include "Pulse/Core/Core.h"

namespace Pulse::Modules::Rendering {

	// Interface class for all textures
	class Texture {
	public: 
		virtual ~Texture() = default; // Virtual destructor for proper cleanup

		virtual void Bind(uint32_t slot = 0) const = 0; // Bind texture

		virtual uint32_t GetWidth() const = 0; // Get texture width
		virtual uint32_t GetHeight() const = 0; // Get texture height

	}; // class Texture

	// 2D texture
	class Texture2D : public Texture {
	public:
		virtual ~Texture2D() = default; // Virtual destructor for proper cleanup

		static Ref<Texture2D> Create(const std::string& path); // Create texture from file

	}; // class Texture2D

} // namespace Pulse::Modules::Rendering