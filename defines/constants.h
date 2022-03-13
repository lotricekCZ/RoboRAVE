#ifndef defines_constants_h
#define defines_constants_h
#include "typedefines.h"
#include <string>
//~ #include <fstream>
//~ #include "yaml-cpp/yaml.h"

/// robot parameters
#define N_wheel 	200.0f
#define r_wheel 	0.044f // in meters
#define pi_const 	3.141592653589793238462643383279502884L
#define sqrt2_const 1.41421356237309504880
#define dist_wheel 	0.125f // in meters
#define fric_wheel 	0.5097f // static friction coeficient against wood I measured using kitchen scale
//~ #define robot_radius 0.10f // in meters
#define robot_radius 0.75 // in meters
#define safe_constant 1.1 // odchylka kolik musi byt pocitano robot_radiusu, aby se nebouralo

#define map_unit 	30 // distance to be multiplied by influence
#define map_l 		1500 // in milimeters, x and y difference of unknown points
#define map_h 		map_l // in milimeters, x and y difference of unknown points

#define meters		1000 // 1000mm == 1m, for conversion from standard unit

/// obstacles parameters
/// 	wall
#define barrier_w 	0.3f 	// m barrier width
#define barrier_d	0.04f  	// m barrier depth
/// 	surround_circle
#define outer_r		0.2f //	m radius of circle	
#define outer_w		0.025f //	m width of line	
/// 	candle
#define candle_r	0.03f //	m radius of circle	

#define MAX_DISTANCE 170 // in cm, maximum distance to have 3 cm difference between lines that are 1 degree apart



#include "variables.hpp"
#endif
