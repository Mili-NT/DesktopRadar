// main.cpp : Defines the entry point for the application.
//
#pragma comment(linker, "/verbose:lib")

#include <iostream>
#include <GeoUtils.hpp>
#include <Constants.hpp>
using namespace std;

int main()
{
	GeoUtils::Coordinate a{ 38.898, -77.037 }; // D.C.
	GeoUtils::Coordinate b{ 48.858, 2.294 };  // Paris
	auto box = GeoUtils::calc_bounded_box(a, 100, Constants::Units::Miles);
	std::cout << box.to_string() << '\n';
	return 0;
}
