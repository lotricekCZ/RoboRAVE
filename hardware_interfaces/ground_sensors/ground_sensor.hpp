/*
 * ground_sensor.hpp
 * 
 * Copyright 2021 Jakub Ramašeuski <jakub@skaryna.net>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#ifndef GROUND_SENSOR_HPP
#define GROUND_SENSOR_HPP

#include <vector>
#include <cmath>
#include <map>

class ground_sensor: public serial_peripheral{
	public:
		unsigned_b queue = 0;
		enum kinds: uint8_t{
			SND_DAT = 0,	/* Send data */
			SND_CON = 1,	/* Send data continuously */
			SET_ALL = 2 	/* Set preferences */
			};
		const static std::map<uint8_t, std::vector<uint8_t>> table;
		const static std::vector<uint16_t> angles;
		//~ using serial_peripheral::comp_kinds;
		std::vector<node> sensors;
		
		struct {
			unsigned reference:		10;
			// these are the settings
			unsigned_n period		:16;
			unsigned_n oversampling	:5;
			unsigned_n expo_time	:16;
			} presets;

		chat *_conn;
		//~ using serial_peripheral::_conn;
		ground_sensor();
		ground_sensor(chat *c);
		ground_sensor(chat &c);

		/*degrees 
		* 0, 
		* atan(64.96/ 55.53), 
		* 90 - atan(8.67/ 88.66), 
		* 180 - atan(64.96/ 55.53), 
		* 180
		* 180 + atan(64.96/ 55.53),
		* 270 + atan(8.67/ 88.66),
		* 360 - atan(64.96/ 55.53),
		* */
		

		~ground_sensor();

		//~ bool update();
		//~ std::vector<node> get_data(bool update);
		void run() override;
		void question() override;
		void answer() override;
		void decode() override;
		void encode() override;
		void update() override;
		
		//~ ground_sensor& operator=(const ground_sensor& rhs);
	private:
		/* add your private declarations */
};

const std::map<uint8_t, std::vector<uint8_t>> ground_sensor::table = {{ground_sensor::SND_DAT, {ground_sensor::SND_DAT}}, 
																	{ground_sensor::SND_CON, {ground_sensor::SND_CON}},
																	{ground_sensor::SET_ALL, {ground_sensor::SET_ALL}},};

const std::vector<uint16_t> ground_sensor::angles = {0, (uint16_t)(std::round((atan(64.96/55.53) * 180) / pi_const)), 
					(uint16_t)(90 - std::round((atan(8.67/88.66) * 180) / pi_const)), 
					(uint16_t)(180 - std::round((atan(64.96/55.53) * 180) / pi_const)), 
					180, 
					(uint16_t)(180 + std::round((atan(64.96/55.53) * 180) / pi_const)), 
					(uint16_t)(270 + std::round((atan(8.67/88.66) * 180) / pi_const)), 
					(uint16_t)(360 - std::round((atan(64.96/55.53) * 180) / pi_const))};
#endif /* GROUND_SENSOR_HPP */ 
