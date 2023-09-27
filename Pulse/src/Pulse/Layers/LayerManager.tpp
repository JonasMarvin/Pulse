#include "Pulse/Layers/LayerManager.h"
namespace Pulse::Layers {

    template<typename T>
    void LayerManager::AttachLayer() {
        std::type_index typeIndex(typeid(T));
        T* existingLayer = _GetLayer<T>(typeIndex);
        if (existingLayer) {
            PLS_CORE_ERROR("Layer {0} already attached!", typeIndex.name());
            return;
        }

        T* layer = new T();
        _AddLayerToSpecificMaps<T>(layer, typeIndex);
        layer->OnAttach();
        PLS_CORE_INFO("Layer {0} has been attached.", typeIndex.name());
    }

    template <typename Base, typename Derived>
    void LayerManager::AttachLayer() {
        std::type_index typeIndex(typeid(Base));
        Base* existingLayer = _GetLayer<Base>(typeIndex);
        if (existingLayer) {
            PLS_CORE_ERROR("Layer {0} already attached!", typeIndex.name());
            return;
        }

        Derived* layer = new Derived();
        _AddLayerToSpecificMaps<Base>(layer, typeIndex);
        layer->OnAttach();
        PLS_CORE_INFO("Layer {0} has been attached.", typeIndex.name());
    }

    template<typename Base>
    void LayerManager::AttachLayerByPointer(Base* layer) {
    std::type_index typeIndex(typeid(Base));
		Base* existingLayer = _GetLayer<Base>(typeIndex);
		if (existingLayer) {
			PLS_CORE_ERROR("Layer {0} already attached!", typeIndex.name());
			return;
		}

		_AddLayerToSpecificMaps<Base>(layer, typeIndex);
		layer->OnAttach();
		PLS_CORE_INFO("User defined Layer {0} has been attached.", typeIndex.name());
    }

    template<typename T>
    T* LayerManager ::GetLayer() {
        std::type_index typeIndex(typeid(T));
        T* layer = _GetLayer<T>(typeIndex);
        if (layer == nullptr) {
            PLS_CORE_ERROR("Layer {0} is not attached! Maybe you tried using a base layer. Don't do that and use the parent layer!", typeIndex.name());
        }
        return layer;
    }

    template<typename T>
    bool LayerManager::ContainsLayer()
    {
        std::type_index typeIndex(typeid(T));
        T* layer = _GetLayer<T>(typeIndex);
        if (layer) {
            return true;
        }
        return false;
    }

    template<typename T>
    void LayerManager::DetachLayer() {
        std::type_index typeIndex(typeid(T));
        T* layer = _GetLayer<T>(typeIndex);
        if (!layer) {
            PLS_CORE_ERROR("Layer {0} is not attached!", typeIndex.name());
            return;
        }

        _RemoveLayerFromSpecificMaps<T>(layer, typeIndex);
        layer->OnDetach();
        delete layer;
        layer = nullptr;
        PLS_CORE_INFO("Layer {0} has been detached.", typeIndex.name());
    }

    template <typename T>
    void LayerManager::_AddLayerToSpecificMaps(T* layer, std::type_index& typeIndex) {
        if constexpr (std::is_base_of_v<IUpdatableLayer, T>) {
            updatableLayers_.push_back(layer);
            updatableLayersMap_[typeIndex] = layer;
        }
        if constexpr (std::is_base_of_v<IImGuiRenderableLayer, T>) {
            imGuiRenderableLayers_.push_back(layer);
            imGuiRenderableLayersMap_[typeIndex] = layer;
        }
        if constexpr (std::is_base_of_v<IRenderableLayer, T>) {
            renderableLayers_.push_back(layer);
            renderableLayersMap_[typeIndex] = layer;
        }
        layers_.push_back(layer);
        layersMap_[typeIndex] = layer;
    }

    template<typename T>
    T* LayerManager::_GetLayer(std::type_index& typeIndex) {

        if constexpr (std::is_base_of_v<IUpdatableLayer, T>) {
            if (updatableLayersMap_.find(typeIndex) != updatableLayersMap_.end()) {
                return static_cast<T*>(updatableLayersMap_.at(typeIndex));
            }
        }
        if constexpr (std::is_base_of_v<IImGuiRenderableLayer, T>) {
            if (imGuiRenderableLayersMap_.find(typeIndex) != imGuiRenderableLayersMap_.end()) {
                return static_cast<T*>(imGuiRenderableLayersMap_.at(typeIndex));
            }
        }
        if constexpr (std::is_base_of_v<IRenderableLayer, T>) {
            if (renderableLayersMap_.find(typeIndex) != renderableLayersMap_.end()) {
                return static_cast<T*>(renderableLayersMap_.at(typeIndex));
            }
        }
        if constexpr (!std::is_base_of_v<IUpdatableLayer, T> && !std::is_base_of_v<IImGuiRenderableLayer, T> && !std::is_base_of_v<IRenderableLayer, T>) {
            if (layersMap_.find(typeIndex) != layersMap_.end()) {
                return static_cast<T*>(layersMap_.at(typeIndex));
            }
        }
        return nullptr;
    }

    template <typename T>
    void LayerManager::_RemoveLayerFromSpecificMaps(T* layer, std::type_index& typeIndex) {
        if constexpr (std::is_base_of_v<IUpdatableLayer, T>) {
            updatableLayers_.erase(std::remove(updatableLayers_.begin(), updatableLayers_.end(), layer), updatableLayers_.end());
            updatableLayersMap_.erase(typeIndex);
        }
        if constexpr (std::is_base_of_v<IImGuiRenderableLayer, T>) {
            imGuiRenderableLayers_.erase(std::remove(imGuiRenderableLayers_.begin(), imGuiRenderableLayers_.end(), layer), imGuiRenderableLayers_.end());
            imGuiRenderableLayersMap_.erase(typeIndex);
        }
        if constexpr (std::is_base_of_v<IRenderableLayer, T>) {
			renderableLayers_.erase(std::remove(renderableLayers_.begin(), renderableLayers_.end(), layer), renderableLayers_.end());
			renderableLayersMap_.erase(typeIndex);
		}
        layers_.erase(std::remove(layers_.begin(), layers_.end(), layer), layers_.end());
        layersMap_.erase(typeIndex);
    }
} // namespace Pulse::Layers