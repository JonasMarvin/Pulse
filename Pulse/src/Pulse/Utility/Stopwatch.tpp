namespace Pulse::Utility {

    template <typename Precision>
    double Stopwatch::GetTime() const {
        auto now = isPaused_ ? lastPausedTime_ : Clock::now();
        return std::chrono::duration<double, typename Precision::period>(now - startTime_ - totalPausedTime_).count();
    }

    template <typename Precision>
    void Stopwatch::PrintTime(const char* message) const {
        if (message == nullptr) {
            PLS_CORE_INFO("Time: {0}", GetTime<Precision>());
        } else {
            PLS_CORE_INFO("{0} {1}", message, GetTime<Precision>());
		}
        
    }

} // namespace Pulse::Utility