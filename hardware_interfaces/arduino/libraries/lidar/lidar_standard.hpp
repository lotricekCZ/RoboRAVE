#ifndef lidar_standard_hpp
#define lidar_standard_hpp
#include <cinttypes>

namespace ldr_std {
	const uint32_t baudrate = 		115200;
	const uint8_t length_packet = 	36;
	const uint8_t length_header = 	4;
	const float rotation_div = 		3840.0f;
	const float angle_div = 		64.0f;
	const float angle_sub = 		640.0f;
	const uint8_t dist_num = 		8; // number of distances
	const uint8_t dist_size = 		2;
	const uint8_t ang_size = 		2;
	const uint8_t spd_size = 		2;
	const uint8_t qual_size = 		1;
	const uint8_t ang_first = 		length_header + spd_size - 1; // offset for first distance
	const uint8_t dist_first = 		length_header + ang_size + spd_size - 1; // offset for first distance
	const uint8_t header[length_header] = 		{0x55, 0xAA, 0x03, 0x08};
	
	};
	
#endif // lidar_standard_hpp

