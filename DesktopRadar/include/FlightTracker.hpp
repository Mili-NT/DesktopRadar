#pragma once
#include <vector>

// Planes are associated with a specific flight state messages from ADS - B & Mode S, consisting of the tracking info.
// OpenSky returns these state vectors as JSON. For now, we just need to know where the aircraft is (lat and long), if it's on the ground, and its heading.
// I will go ahead and add other relevant state vectors just in case.

struct Plane {
	// Position
	float latitude; // CAN BE NULL
	float longitude; // CAN BE NULL
	bool is_grounded; // Indicates if the position was retrieved from a surface position. We don't need to render these currently.
	// Direction
	float track; // The plane's direction in decimal degrees clockwise from north. CAN BE NULL.
	float velocity; // Velocity over ground in m/s. CAN BE NULL.
	// Altitude
	float barometric_altitude; // Altitude based on air pressure, relative to sea level. CAN BE NULL
	float geometric_altitude; // Altitude based on GPS. CAN BE NULL
	float vertical_rate; // Plane's climb rate in m/s, positive indicates climbing and negative is desending. CAN BE NULL
};

class FlightTracker {
public:
	FlightTracker();

private:
	std::vector<Plane> planes;
};