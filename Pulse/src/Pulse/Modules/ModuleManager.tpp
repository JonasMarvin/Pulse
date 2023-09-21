#include "ModuleManager.h"
namespace Pulse::Modules {

    template<typename T>
    void ModuleManager::RegisterModule() {
        std::type_index typeIndex(typeid(T));
        T* existingModule = _GetModule<T>(typeIndex);
        if (existingModule) {
            PLS_CORE_ERROR("Module {0} already registered!", typeIndex.name());
            return;
        }

        T* module = new T();
        _AddModuleToSpecificMaps<T>(module, typeIndex);
        module->Initialize();
        PLS_CORE_INFO("Module {0} has been registered.", typeIndex.name());
    }

    template<typename T>
    T* ModuleManager::GetModule() {
        std::type_index typeIndex(typeid(T));
        T* module = _GetModule<T>(typeIndex);
        if (module == nullptr) {
            PLS_CORE_ERROR("Module {0} is not registered!", typeIndex.name());
        }
        return module;
    }

    template<typename T>
    bool ModuleManager::HasModule()
    {
        std::type_index typeIndex(typeid(T));
        T* module = _GetModule<T>(typeIndex);
        if (module) {
			return true;
		}
        return false;
    }

    template<typename T>
    void ModuleManager::UnregisterModule() {
        std::type_index typeIndex(typeid(T));
        T* module = _GetModule<T>(typeIndex);
        if (!module) {
            PLS_CORE_ERROR("Module {0} is not registered!", typeIndex.name());
            return;
        }

        _RemoveModuleFromSpecificMaps<T>(module, typeIndex);
        module->Shutdown();
        delete module;
        module = nullptr;
        PLS_CORE_INFO("Module {0} has been unregistered.", typeIndex.name());
    }

    template <typename T>
    void ModuleManager::_AddModuleToSpecificMaps(T* module, std::type_index& typeIndex) {
        if constexpr (std::is_base_of_v<IUpdatableModule, T>) {
            updatableModules_.push_back(module);
            updatableModulesMap_[typeIndex] = module;
        }
        if constexpr (std::is_base_of_v<IRenderImGuiModule, T>) {
            imGuiRenderableModules_.push_back(module);
            imGuiRenderableModulesMap_[typeIndex] = module;
        }
        modules_.push_back(module);
    }

    template<typename T>
    T* ModuleManager::_GetModule(std::type_index& typeIndex) {

        if constexpr (std::is_base_of_v<IUpdatableModule, T>) {
            if (updatableModulesMap_.find(typeIndex) != updatableModulesMap_.end()) {
                return static_cast<T*>(updatableModulesMap_.at(typeIndex));
            }
        }
        if constexpr (std::is_base_of_v<IRenderImGuiModule, T>) {
            if (imGuiRenderableModulesMap_.find(typeIndex) != imGuiRenderableModulesMap_.end()) {
                return static_cast<T*>(imGuiRenderableModulesMap_.at(typeIndex));
            }
        }
        if constexpr (!std::is_base_of_v<IUpdatableModule, T> && !std::is_base_of_v<IRenderImGuiModule, T>) {
            if (modulesMap_.find(typeIndex) != modulesMap_.end()) {
                return static_cast<T*>(modulesMap_.at(typeIndex));
            }
        }
        return nullptr;
    }

    template <typename T>
    void ModuleManager::_RemoveModuleFromSpecificMaps(T* module, std::type_index& typeIndex) {
        if constexpr (std::is_base_of_v<IUpdatableModule, T>) {
            updatableModules_.erase(std::remove(updatableModules_.begin(), updatableModules_.end(), module), updatableModules_.end());
            updatableModulesMap_.erase(typeIndex);
        }
        if constexpr (std::is_base_of_v<IRenderImGuiModule, T>) {
            imGuiRenderableModules_.erase(std::remove(imGuiRenderableModules_.begin(), imGuiRenderableModules_.end(), module), imGuiRenderableModules_.end());
            imGuiRenderableModulesMap_.erase(typeIndex);
        }
        modules_.erase(std::remove(modules_.begin(), modules_.end(), module), modules_.end());
    }
} // namespace Pulse::Modules