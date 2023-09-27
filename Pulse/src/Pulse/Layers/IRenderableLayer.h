#pragma once

#include "Pulse/Layers/ILayer.h"
#include <Pulse/TimeData.h>

namespace Pulse::Layers {

    // Interface for layers that need to be rendered
    class IRenderableLayer : public virtual ILayer {
    public:
        IRenderableLayer(const IRenderableLayer&) = delete; // Copy constructor deleted as we don't want to copy layers
        IRenderableLayer& operator=(const IRenderableLayer&) = delete;  // Copy assignment operator deleted as we don't want to copy layers
        IRenderableLayer(IRenderableLayer&&) = delete; // Move constructor deleted as we don't want to move layers
        IRenderableLayer& operator=(IRenderableLayer&&) = delete; // Move assignment operator deleted as we don't want to move layers

        virtual void Render(const TimeData& timeData) = 0;  // Pure virtual function gets called by the layer manager every frame after module processing

    protected:
        IRenderableLayer() = default; // Default constructor is protected as layers should only be created by the layer manager
        virtual ~IRenderableLayer() = default; // Default destructor is protected as layers should only be destroyed by the layer manager

        friend class LayerManager; // The layer manager is befriended with the layer to allow it to call the OnAttach, Render and OnDetach functions
    }; // class IRenderableLayer

} // namespace Pulse::Layer