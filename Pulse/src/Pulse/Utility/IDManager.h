#pragma once

#include <stack>
#include <stdexcept>

#include "Pulse/Utility/Constraints.h"

namespace Pulse::Utility {
	template<UnsignedIntegralWithNumericLimits IDType>
	class IDManager {
	public:
		IDManager() : counter_(0) {}

		IDManager(const IDManager&) = delete;
		IDManager& operator=(const IDManager&) = delete;

		inline IDType GenerateID() {
			if (!freeIDs_.empty()) {
				IDType id = freeIDs_.top();
				freeIDs_.pop();
				return id;
			}
			else {
				if (counter_ == std::numeric_limits<IDType>::max()) {
					throw std::runtime_error("ID limit reached!");
				}
				return ++counter_;
			}
		}

		inline void FreeID(IDType id) {
			freeIDs_.push(id);
			if (IDsInUsage() == 0) {
				std::stack<IDType>().swap(freeIDs_);
				counter_ = 0;
			}
		}

	private:
		std::stack<IDType> freeIDs_;
		IDType counter_;

		inline size_t StackMemoryUsage() const {
			return freeIDs_.size() * sizeof(IDType);
		}

		inline IDType IDsInUsage() const {
			return static_cast<IDType>(counter_ - freeIDs_.size());
		}

	}; // class IDManager

} // namespace Pulse::Utility