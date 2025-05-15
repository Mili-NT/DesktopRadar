//
// Various functions for calculating distance, handling coordinates, etc.
//
#include "GeoUtils.hpp"
#include "Constants.hpp"
#include <cmath>
#include <regex>
#include <sstream>


namespace GeoUtils {
	double dist_between_points(Coordinate point1, Coordinate point2, Constants::Units unit) {
		// θ = d / r
		// Where:
		//	d = distance between two points (what we want to solve for)
		//	r = radius of the sphere, in this case earth
		// havθ = hav(Δ_φ) + cos(φ_1)cos(φ_2)hav(Δλ)		hav\Theta = hav(\Delta\varphi) + \cos(\varphi_{1})\cos(\varphi_{2})hav(\Delta\lambda)
		// Where:
		//	φ_1, φ_2 = latitude of points 1 and 2 respectively
		//	λ_1, λ_2 = longitudes of points 1 and 2 respectively
		//	Δ_φ = φ_2 - φ_1 (difference in latitudes)
		//	Δ_λ = λ_2 - λ_1 (difference in longitudes)
		//	hav() = sin^2(x/2)								hav(\Theta) = \sin^{2}(\frac{\Theta }{2}) = \frac{1 - \cos(\Theta) }{2}
		// To solve for distance:
		// d = 2r arcsine(√havθ)							d = r *archav(hav\Theta) = 2r \arcsin(\sqrt{hav\Theta})
		double lat1 = point1.lat * Constants::DEG_TO_RAD;
		double lon1 = point1.lon * Constants::DEG_TO_RAD;
		double lat2 = point2.lat * Constants::DEG_TO_RAD;
		double lon2 = point2.lon * Constants::DEG_TO_RAD;
		double radius = (unit == Constants::Units::Miles) ? Constants::EARTH_RADIUS_MILES : Constants::EARTH_RADIUS_KM;

		double delta_phi = lat2 - lat1;
		double delta_lambda = lon2 - lon1;

		auto hav = [](double x) {
			return std::pow(std::sin(x / 2), 2);
			};

		double hav_theta = hav(delta_phi) + std::cos(lat1) * std::cos(lat2) * hav(delta_lambda);
		double dist = (2 * radius) * std::asin(std::sqrt(hav_theta));
		return dist;
	}
	static double dms_to_dd(double deg, double min, double sec, char dir) {
		double decimal = deg + (min / 60) + (sec / 3600);
		if (dir == 'S' || dir == 'W')
		{
			decimal *= -1.0;
		}
		return std::round(decimal * 10000.0) / 10000.0;
	}
	double dist_per_deg_lat(double deg, Constants::Units unit) {
		// Meridian distance per degree of latitude:
		// m(θ) = (π / 180)Rθ_degrees = Rθ_radians           m(\Theta) = \frac{\pi }{180^{\circ }}R_{degrees} = R\Theta_{radians}
		// Where:
		//	R = the mean radius of the earth
		double radius = (unit == Constants::Units::Miles)
			? Constants::EARTH_RADIUS_MILES
			: Constants::EARTH_RADIUS_KM;

		return radius * Constants::DEG_TO_RAD * deg;
	}
	double dist_per_deg_lon(double lat_deg, Constants::Units unit) {
		// Distance per degree of longitude:
		// Δ1_long = (π / 180)acos?                          (\Delta^{1}_{long} = \frac{\pi }{180}\alpha\cos\Theta)
		// Where:
		//	a = radius of sphere
		//	φ = latitude in radians
		double radius = (unit == Constants::Units::Miles) ? Constants::EARTH_RADIUS_MILES : Constants::EARTH_RADIUS_KM;
		double theta_rad = lat_deg * Constants::DEG_TO_RAD;
		return Constants::DEG_TO_RAD * radius * std::cos(theta_rad);
	}
	
	std::optional<GeoUtils::Coordinate> GeoUtils::Coordinate::from_dms(const std::string& dms_string)
	{
		// This regex is simple: it consists of three capture groups for each value and a fourth for direction. The rest is accounting for formatting.
		// It should be fairly robust, handling spaces, primes, and other formatting quirks. All of these match:
		// 48°51'30"N 2°17'40"E
		// 48° 51′ 30.24″ N, 2° 17′ 40.2″ E
		// 48d51m30.24sN 2d17m40.2sE
		std::regex pattern(R"((\d{1,3})°?[dD]? ?(\d{1,2})[\'′]?[mM]? ?(\d{1,2}\.?\d*)["″]?[sS]? ?([nsewNSEW]))");
		std::sregex_iterator iter(dms_string.begin(), dms_string.end(), pattern);
		std::sregex_iterator end;

		auto parse = [](const std::smatch& match) {
			int deg = std::stoi(match[1]);
			int min = std::stoi(match[2]);
			double sec = std::stod(match[3]);
			char dir = match[4].str()[0];
			return dms_to_dd(deg, min, sec, dir);
			};

		double lat = parse(*iter++);
		double lon = parse(*iter++);

		return Coordinate{ lat, lon };
	}
	Coordinate::Coordinate(const std::string & coord_str) {
		auto coord = from_dms(coord_str);
		if (coord) {
			lat = coord->lat;
			lon = coord->lon;
		}
		else {
			throw std::invalid_argument("Invalid DMS format: " + coord_str);
		}
	}
	std::string GeoUtils::Coordinate::to_string() const {
		std::ostringstream oss;
		oss.precision(6);
		oss << std::fixed << lat << ", " << lon;
		return oss.str();
	}
}


