#include "pch.h"

#include "Pulse/Layers/LayerManager.h"

namespace Pulse::Layers {

	LayerManager::LayerManager() {
		PLS_CORE_INFO("Layer manager loaded.");
	}

	LayerManager& LayerManager::GetInstance() {
		static LayerManager instance;
		return instance;
	}

	void LayerManager::UpdateLayers(const TimeData& timeData) {
		for (auto it = updatableLayers_.rbegin(); it != updatableLayers_.rend(); ++it) {
			(*it)->Update(timeData);
		}
	}

	void LayerManager::RenderImGuiLayers(const TimeData& timeData) {
		for (auto it = imGuiRenderableLayers_.rbegin(); it != imGuiRenderableLayers_.rend(); ++it) {
			(*it)->RenderImGui(timeData);
		}
	}

	void LayerManager::RenderLayers(const TimeData& timeData) {
		for (auto it = renderableLayers_.rbegin(); it != renderableLayers_.rend(); ++it) {
			(*it)->Render(timeData);
		}
	}

	void LayerManager::DetachAllLayers() {
		for (auto layer = layers_.rbegin(); layer != layers_.rend(); ++layer) {
			(*layer)->OnDetach();
			delete (*layer);
			(*layer) = nullptr;
		}
		layers_.clear();
		imGuiRenderableLayersMap_.clear();
		imGuiRenderableLayers_.clear();
		updatableLayersMap_.clear();
		updatableLayers_.clear();
		renderableLayersMap_.clear();
		renderableLayers_.clear();
		PLS_CORE_INFO("All layers have been detached!");
	}

} // namespace Pulse::Layers