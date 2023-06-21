#include "Stopwatch.h"

#include <chrono>

namespace Pulse::Utility {

	Stopwatch::Stopwatch() {
		Reset();
	}

	void Stopwatch::Reset() {
		startTime_ = Clock::now();
		totalPausedTime_ = std::chrono::duration<double>::zero();
		isPaused_ = false;
	}

	void Stopwatch::Pause() {
		if (!isPaused_) {
			lastPausedTime_ = Clock::now();
			isPaused_ = true;
		}
	}

	void Stopwatch::Resume() {
		if (isPaused_) {
			totalPausedTime_ += Clock::now() - lastPausedTime_;
			isPaused_ = false;
		}
	}

} // namespace Pulse::Utility