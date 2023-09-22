#include "pch.h"

#include "Pulse/TimeData.h"

namespace Pulse {

	TimeData::operator float() const {
		return static_cast<float>(deltaTime_ / 1e9);
	}

	float TimeData::GetDeltaTimeNanoSeconds() const {
		return static_cast<float>(deltaTime_);
	}

	float TimeData::GetDeltaTimeMicroSeconds() const {
		return static_cast<float>(deltaTime_ / 1000.0);
	}

	float TimeData::GetDeltaTimeMilliSeconds() const {
		return static_cast<float>(deltaTime_ / 1e6);
	}

	float TimeData::GetDeltaTimeSeconds() const {
		return static_cast<float>(deltaTime_ / 1e9);
	}

	float TimeData::GetDeltaTimeMinutes() const {
		return static_cast<float>(deltaTime_ / 6e10);
	}

	void TimeData::Initialize() {
		lastFrameTime_ = stopwatch_.GetTime<std::chrono::nanoseconds>();
	}

	void TimeData::Update() {
		currentFrameTime_ = stopwatch_.GetTime<std::chrono::nanoseconds>();
		deltaTime_ = currentFrameTime_ - lastFrameTime_;
		lastFrameTime_ = currentFrameTime_;
	}

} // namespace Pulse