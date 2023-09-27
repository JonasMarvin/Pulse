#pragma once

#include "Pulse/Core/Core.h"

namespace Pulse::Layers {

	// Base Interface for layers that can be registered with the layer manager.
	// Dervied class should follow the friend Pattern with LayerManager to only allow LayerManager to create and destroy the layers.
	class ILayer {
	public:
		ILayer(const ILayer&) = delete; // Copy constructor deleted as we don't want to copy layers
		ILayer& operator=(const ILayer&) = delete; // Copy assignment operator deleted as we don't want to copy layers
		ILayer(ILayer&&) = delete; // Move constructor deleted as we don't want to move layers
		ILayer& operator=(ILayer&&) = delete; // Move assignment operator deleted as we don't want to move layers

		virtual void OnAttach() = 0; // Pure virtual function gets called by the layer manager when the layer is attached
		virtual void OnDetach() = 0; // Pure virtual function gets called by the layer manager when the layer is detached

	protected:
		ILayer() = default; // Default constructor is protected as layers should only be created by the layer manager
		virtual ~ILayer() = default; // Default destructor is protected as layers should only be destroyed by the layer manager

		friend class LayerManager; // The layer manager is befriended with the layers to allow it to call the OnAttach and OnDetach functions
	}; // class ILayer

} // namespace Pulse::Layers