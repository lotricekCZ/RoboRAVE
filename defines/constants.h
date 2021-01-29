#ifndef defines_constants_h
#define defines_constants_h
#include "typedefines.h"
//~ #include <fstream>
//~ #include "yaml-cpp/yaml.h"

/// robot parameters
#define N_wheel 	200.0f
#define r_wheel 	0.044f // in meters
#define pi 			3.141592653589793238462643383279502884L
#define dist_wheel 	0.125f // in meters
#define fric_wheel 	0.5097f // static friction coeficient against wood I measured using kitchen scale

#define map_raster 	15 // in milimeters, x and y difference of unknown points
#define map_unit 	30 // distance to be multiplied by influence
#define map_l 		1500 // in milimeters, x and y difference of unknown points
#define map_h 		map_l // in milimeters, x and y difference of unknown points

/// obstacles parameters
/// 	wall
#define barrier_w 	0.3f 	// m barrier width
#define barrier_d	0.04f  	// m barrier depth
/// 	surround_circle
#define outer_r		0.2f //	m radius of circle	
#define outer_w		0.025f //	m width of line	
/// 	candle
#define candle_r	0.03f //	m radius of circle	

#define MAX_DISTANCE 170 //maximum distance to have 3 cm difference between lines that are 1 degree apart
const decimal_n omega_wheel_const = (pi * r_wheel) / (N_wheel * dist_wheel);
const decimal_n wheel_step_lenght_const = (2 * pi * r_wheel) / (N_wheel);

/// tresholds
/// TODO: config file, do it through config file using YAML, since it's human readable

namespace tresholds {
	namespace mAP { 
		// ammount of confidence image recognition needs to have
		decimal_n candle = 			0.2f;
		decimal_n line_border = 	0.3f;
		decimal_n line_surround = 	0.3f;
		decimal_n fire = 			0.6f;
		decimal_n barrier = 		0.6f;
		}
		
	namespace explo {
		
		namespace objects {
			decimal_n candle = 			8192;
			decimal_n candle_blown = 	0;
			decimal_n unknown = 		128;
			decimal_n barrier = 		2;
			decimal_n discovered =		-640;
			decimal_n interesting =		1024;
			decimal_n boring =			-128;
			}
			
		namespace influence {
			decimal_n candle = 			6;
			decimal_n candle_blown = 	4;
			decimal_n unknown = 		4;
			decimal_n barrier = 		8;
			decimal_n discovered = 		9;
			decimal_n boring = 			7;
			decimal_n interesting = 	18;
			
			//~ decimal_n candle = 			1;
			//~ decimal_n candle_blown = 	2;
			//~ decimal_n unknown = 		2.5;
			//~ decimal_n barrier = 		4;
			//~ decimal_n discovered = 		4;
			//~ decimal_n boring = 			3;
			//~ decimal_n interesting = 	9;
			}
			 
		}
		
	}

#endif
