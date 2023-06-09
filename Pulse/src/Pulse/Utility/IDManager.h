#pragma once

#include <stack>

#include "Pulse/Utility/NumberConstraints.h"

namespace Pulse::Utility {
	template<typename IntergralIDType>
	class IDManager : private EnsureIntergralType<IDType> {
	public:
		IDManager() : counter_(0) {}

		inline IntergralIDType GenerateID() {
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
		}

	private:
		std::stack<IDType> freeIDs_;
		IntergralIDType counter_;

	}; // class IDManager

} // namespace Pulse::Utility