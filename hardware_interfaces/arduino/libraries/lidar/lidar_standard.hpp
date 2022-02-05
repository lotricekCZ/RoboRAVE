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
/*
<0x55><0xAA><0x03><0x08>
<speedL><speedH>
<startAngleL><startAngleH>
<distance0L><distance0H><quality0>
<distance1L><distance1H><quality1>
<distance2L><distance2H><quality2>
<distance3L><distance3H><quality3>
<distance4L><distance4H><quality4>
<distance5L><distance5H><quality5>
<distance6L><distance6H><quality6>
<distance7L><distance7H><quality7>
<endAngleL><endAngleH>
<unknown><unknown> could be a CRC

A package always starts with <0x55><0xAA><0x03><0x08>

Calculate rotation speed in hz:

float Hz = ((uint16_t) (speedH << 8) | speedL) / 3840.0; // 3840.0 = (64 * 60)

Calculate start and end Angle in degrees:

 float startAngle = (startAngleH << 8 | startAngleL) / 64.0 - 640.0;
 float endAngle   = (endAngleH   << 8 | endAngleL)   / 64.0 - 640.0;
*/

#endif // lidar_standard_hpp

