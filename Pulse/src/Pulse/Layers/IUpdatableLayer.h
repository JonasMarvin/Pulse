#pragma once

#include "Pulse/Layers/ILayer.h"
#include "Pulse/Core/TimeData.h"

namespace Pulse::Layers {

    // Interface for layers that need to be updated every frame
    class IUpdatableLayer: public virtual ILayer {
    public:
        IUpdatableLayer(const IUpdatableLayer&) = delete; // Copy constructor deleted as we don't want to copy layers
        IUpdatableLayer& operator=(const IUpdatableLayer&) = delete;  // Copy assignment operator deleted as we don't want to copy layers
        IUpdatableLayer(IUpdatableLayer&&) = delete; // Move constructor deleted as we don't want to move layers
        IUpdatableLayer& operator=(IUpdatableLayer&&) = delete; // Move assignment operator deleted as we don't want to move layers

        virtual void Update(const TimeData& timeData) = 0;  // Pure virtual function gets called by the layer manager every frame after module processing

    protected:
        IUpdatableLayer() = default; // Default constructor is protected as layers should only be created by the layer manager
        virtual ~IUpdatableLayer() = default; // Default destructor is protected as layers should only be destroyed by the layer manager

        friend class LayerManager; // The layer manager is befriended with the layer to allow it to call the OnAttach, Update and OnDetach functions
    }; // class IUpdatableLayer

} // namespace Pulse::Layer