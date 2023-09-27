#pragma once

#include <memory>
#include <vector>
#include <typeindex>

#include "Pulse/Layers/IImGuiRenderableLayer.h"
#include "Pulse/Layers/IUpdatableLayer.h"
#include "Pulse/Layers/IRenderableLayer.h"
#include "Pulse/Core/Logging/Log.h"

namespace Pulse::Layers {

	// Singleton class that manages all layers as pointers
	// Due to private destructors of layers, the layer manager is responsible for deleting the layers.
	// Setup happens in Application.
	class LayerManager {
	public:
		LayerManager(const LayerManager&) = delete; // Delete copy constructor because singleton
		LayerManager(LayerManager&&) = delete; // Delete move constructor because singleton
		LayerManager& operator=(const LayerManager&) = delete; // Delete copy assignment operator because singleton
		LayerManager& operator=(LayerManager&&) = delete; // Delete move assignment operator because singleton

		static LayerManager& GetInstance(); // Singleton instance getter

		// Registers a layer to the layer manager and initializes it by calling the layers OnAttach() function
		template <typename T>
		void AttachLayer();

		// Registers a interface layer Base to the layer manager by using the implementation in Derived and initializes it by calling the layers OnAttach() function
		template <typename Base, typename Derived>
		void AttachLayer();

		// Registers a interface layer Base to the layer manager by using the passed downcasted pointer and initializes it by calling the layers OnAttach() function
		// This is used for layers which are defined by the user and not by the engine dont use this for engine defined layers.
		// If you still do that he Log message will state that a user defined layer is added.
		template <typename Base>
		void AttachLayerByPointer(Base* layer);

		// Returns a layer of type T if it exists, otherwise returns nullptr
		template <typename T>
		T* GetLayer();

		// Returns a boolean based on the existence of a layer of type T
		template <typename T>
		bool ContainsLayer();

		// Updates all updatable layer by calling the layers Update(TimeData timeData) function. Gets called in Application::Run()
		void UpdateLayers(const TimeData& timeData);

		// Updates all ImGuiRenderable layers by calling the layers ImGuiRender(TimeData timeData) function. Gets called in Application::Run()
		void RenderImGuiLayers(const TimeData& timeData);

		// Updates all Renderable layers by calling the layers Render(TimeData timeData) function. Gets called in Application::Run()
		void RenderLayers(const TimeData& timeData);

		// Shuts down a layer of type T by calling the layers OnDetach() function and removes it from the layer manager
		template <typename T>
		void DetachLayer();

		// Detaches all layers by calling the layers OnDetach() function and removes them from the layer manager. Gets called before the Application shuts down
		void DetachAllLayers();

	private:
		LayerManager(); // Private constructor for singleton
		~LayerManager() = default; // Private destructor for singleton

		// Adds a layer to the according layers maps
		template <typename T>
		void _AddLayerToSpecificMaps(T* layer, std::type_index& typeIndex);

		// Checks if a layer of type T exists and returns it if it does, otherwise returns nullptr
		template <typename T>
		T* _GetLayer(std::type_index& typeIndex);

		// Removes a layer from the according layers maps
		template <typename T>
		void _RemoveLayerFromSpecificMaps(T* layer, std::type_index& typeIndex);

		std::vector<ILayer*> layers_; // Vector of active layers safed as pointers
		std::vector<IUpdatableLayer*> updatableLayers_; // Vector for layers that are updatable
		std::vector<IRenderableLayer*> renderableLayers_; // Vector for layers that are renderable
		std::vector<IImGuiRenderableLayer*> imGuiRenderableLayers_; // Vector for layers that are ImGui renderable
		std::unordered_map<std::type_index, ILayer*> layersMap_; // Map of active layers safed as pointers
		std::unordered_map<std::type_index, IUpdatableLayer*> updatableLayersMap_; // Map of active updatable layers safed as pointers
		std::unordered_map<std::type_index, IRenderableLayer*> renderableLayersMap_; // Map of active renderable layers safed as pointers
		std::unordered_map<std::type_index, IImGuiRenderableLayer*> imGuiRenderableLayersMap_; // Map of active imgui renderable layers safed as pointers
	}; // class LayerManager

} // namespace Pulse::Layers

#include "Pulse/Layers/LayerManager.tpp"