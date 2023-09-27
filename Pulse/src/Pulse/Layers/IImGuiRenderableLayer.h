#pragma once

#include "Pulse/Layers/ILayer.h"
#include "Pulse/Core/TimeData.h"

namespace Pulse::Layers {

    // Interface for layers that need to be rendered to ImGui
    class IImGuiRenderableLayer : public virtual ILayer {
    public:
        IImGuiRenderableLayer(const IImGuiRenderableLayer&) = delete; // Copy constructor deleted as we don't want to copy layers
        IImGuiRenderableLayer& operator=(const IImGuiRenderableLayer&) = delete;  // Copy assignment operator deleted as we don't want to copy layers
        IImGuiRenderableLayer(IImGuiRenderableLayer&&) = delete; // Move constructor deleted as we don't want to move layers
        IImGuiRenderableLayer& operator=(IImGuiRenderableLayer&&) = delete; // Move assignment operator deleted as we don't want to move layers

        virtual void RenderImGui(const TimeData& timeData) = 0;  // Pure virtual function gets called by the layer manager every frame after module processing

    protected:
        IImGuiRenderableLayer() = default; // Default constructor is protected as layers should only be created by the layer manager
        virtual ~IImGuiRenderableLayer() = default; // Default destructor is protected as layers should only be destroyed by the layer manager

        friend class LayerManager; // The layer manager is befriended with the layer to allow it to call the OnAttach, Render and OnDetach functions
    }; // class IImGuiRenderableLayer

} // namespace Pulse::Layer