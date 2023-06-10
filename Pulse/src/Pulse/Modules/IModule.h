#pragma once

#include <memory>

namespace Pulse::Modules {
	
	class IModule : public std::enable_shared_from_this<IModule> {
	public:
		// Declarations
		IModule() = default;
		virtual ~IModule() = default;

		IModule(const IModule&) = delete;
		IModule& operator=(const IModule&) = delete;
		IModule(IModule&&) = delete;
		IModule& operator=(IModule&&) = delete;

		virtual void Initialize() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Shutdown() = 0;

	}; // class IModule

} // namespace Pulse::Modules