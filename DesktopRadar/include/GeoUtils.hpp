#pragma once

#include "Constants.hpp"
#include <cmath>
#include <string>
#include <optional>
	

namespace GeoUtils {
	struct Coordinate {
		double lat;
		double lon;

		// Normal constructor
		constexpr Coordinate(double lat = 0.0, double lon = 0.0)
			: lat(lat), lon(lon) {
		}
		// Constructor for passing in DMS coordinate strings
		Coordinate(const std::string& str);

		static std::optional<Coordinate> from_dms(const std::string& dms_string);
		std::string to_string() const;
	};

	struct BoundedBox {
		double lat_min;
		double lat_max;
		double lon_min;
		double lon_max;
		double area_deg_sq;
	};

	double dist_per_deg_lat(double deg, Constants::Units unit);
	double dist_per_deg_lon(double lat_deg, Constants::Units unit);
	double dist_between_points(Coordinate point1, Coordinate point2, Constants::Units unit);
}
