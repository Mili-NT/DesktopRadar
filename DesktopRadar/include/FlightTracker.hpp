#pragma once
#include <vector>

/// Each plane represents a state vector containing the tracking info for that flight, derived from ADS-B and Mode S messages
/// OpenSky returns these state vectors as JSON, from which we can pull the relvant properties. Currently, I'm just focusing the position and direction of the plane.
/// I will go ahead and add other relevant state vectors in case I want to add additional information to the UI.

/// OpenSky Network API 
/// Rate Limits: 
///		Anonymous -		400	 credits per day
///		OpenSky Users - 4000 credits per day
///		Active Users -	8000 credits per day 
///
///		Active Users are required to have an ADS-B Reciever with >30% monthly uptime.
/// 
///		Credits remaining are indicated by the X-Rate-Limit-Remaining.
///		If exceeded, the API returns a status code 429 and indicates the time until availability with the X-Rate-Limit-Retry-After-Seconds header.
/// 
/// API can be queried by time and ICAO24 transponder address:
///		https://opensky-network.org/api/states/all?time=1458564121&icao24=3c6444
/// or by providing a bounding box for a specific area, defined by upper and lower bounds for latitude and longtitude:
///		https://opensky-network.org/api/states/all?lamin=45.8389&lomin=5.9962&lamax=47.8229&lomax=10.5226
/// The price per bounded request is dependendent on the area of the box:
///		0 - 25 (<500x500km) -				1 credit per request
///		25 - 100 (<1000x1000km) -			2 credits per request
///		100 - 400 (<2000x2000km) -			3 credits per request
///		over 400 or all (>2000x2000km) -	4 credits per request



struct Plane {
	// Position
	float latitude;				// CAN BE NULL
	float longitude;			// CAN BE NULL
	bool is_grounded;			// If the plane is grounded, we won't render it.
	// Direction
	float track;				// Direction measured in degrees clockwise from north. CAN BE NULL
	float velocity;				// Ground speed in m/s. CAN BE NULL
	// Altitude
	float barometric_altitude;	// Altitude relative to sea level based on air pressure.
	float geometric_altitude;	// Altitude based on GPS. CAN BE NULL
	float vertical_rate;		// Climb/descend rate in m/s. CAN BE NULL
	// Category
	int category;				// Which type of aircraft, i.e 12 = ultralight, 15 = space, etc. 0 means theres no information.
};	

class FlightTracker {
public:
	FlightTracker();


private:
	std::vector<Plane> planes;
};