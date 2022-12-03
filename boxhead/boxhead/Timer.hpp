#pragma once

class Timer
{
public:
	constexpr Timer() = default;
	Timer(const Timer& other) = delete;
	Timer(Timer&& other) = delete;
	Timer& operator=(const Timer& other) = delete;
	Timer& operator=(Timer&& other) = delete;

	static inline std::chrono::system_clock::time_point BeginInspection()
	{
		using namespace std::chrono;

		if (was_inspected)
		{
			const auto time_now = performance_clock.now();
			const auto time_between = time_now - elapsed_timer;
			const auto mill = duration_cast<milliseconds>(time_between);

			delta_time = static_cast<float>(mill.count()) / 1000.0f;

			return time_now;
		}
		else
		{
			delta_time = 0.0f;
			was_inspected = true;

			return Now();
		}
	}

	static inline void EndInspection(const std::chrono::system_clock::time_point& before)
	{
		using namespace std::chrono;

		elapsed_timer = before;
	}

	static inline constexpr float GetDeltaTime() noexcept
	{
		return delta_time;
	}

	static inline std::chrono::system_clock::time_point Now() noexcept
	{
		return performance_clock.now();
	}
	
private:
	static inline constexpr std::chrono::system_clock performance_clock{};
	static inline std::chrono::system_clock::time_point elapsed_timer{};

	static inline float delta_time{};
	static inline bool was_inspected = false;
};
