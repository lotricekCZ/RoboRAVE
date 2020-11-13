#ifndef defines_constants_h
#define defines_constants_h
#include "typedefines.h"
//~ #include <fstream>
//~ #include "yaml-cpp/yaml.h"

/// robot parameters
#define N_wheel 200.0f
#define r_wheel 0.044f // in meters
#define pi 3.141592653589793238462643383279502884L
#define dist_wheel 0.125f // in meters

#define map_raster 15 // in milimeters, x and y difference of unknown points
#define map_l 3000 // in milimeters, x and y difference of unknown points
#define map_h 4000 // in milimeters, x and y difference of unknown points


const decimal_n omega_wheel_const = (pi * r_wheel) / (N_wheel * dist_wheel);
const decimal_n wheel_step_lenght_const = (2 * pi * r_wheel) / (N_wheel);

/// tresholds
/// TODO: config file, do it through config file
namespace tresholds{
	namespace mAP{
		decimal_n candle = 0.2f;
		decimal_n line_border = 0.3f;
		decimal_n line_surround = 0.3f;
		decimal_n fire = 0.6f;
		decimal_n barrier = 0.6f;
		}
	}

#endif
