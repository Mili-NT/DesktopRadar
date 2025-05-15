#pragma once

namespace Constants {
	constexpr double PI = 3.14159265358979323846;
	constexpr double DEG_TO_RAD = PI / 180.0;
	constexpr double RAD_TO_DEG = 180.0 / PI;
	constexpr double EARTH_RADIUS_MILES = 3959.0;

	constexpr double EARTH_RADIUS_KM = 6371.0;
	enum class Units {
		Miles,
		Kilometers
	};
}