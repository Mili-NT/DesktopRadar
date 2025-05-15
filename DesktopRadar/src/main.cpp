// main.cpp : Defines the entry point for the application.
//
#pragma comment(linker, "/verbose:lib")

#include <iostream>
#include <GeoUtils.hpp>
#include <Constants.hpp>
using namespace std;

int main()
{
	// Test GeoUtils using Haversine example from
	// https://en.wikipedia.org/wiki/Haversine_formula#Example
	GeoUtils::Coordinate a{ 38.898, -77.037 }; // D.C.
	GeoUtils::Coordinate b{ 48.858, 2.294 };  // Paris
	double d = GeoUtils::dist_between_points(a, b, Constants::Units::Kilometers);
	std::cout << "Distance: " << d << " mi\n";
	return 0;
}
