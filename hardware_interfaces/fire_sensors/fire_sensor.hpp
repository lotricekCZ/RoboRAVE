/*
 * fire_sensor.hpp
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


#ifndef FIRE_SENSOR_HPP
#define FIRE_SENSOR_HPP

#include <vector>
#include <map>

class fire_sensor: public virtual serial_peripheral{
	public:
		enum kinds: uint8_t{
			SND_DAT = 0,	/* Send data */
			SND_CON = 1,	/* Send data continuously */
			SET_ALL = 2 	/* Set preferences */
			};
		const static std::map<uint8_t, std::vector<uint8_t>> table;
		//~ using serial_peripheral::comp_kinds;
		unsigned reference:		10;
		std::vector<node> sensors;
		
		// these are the settings
		unsigned_n period		:16;
		unsigned_n oversampling	:5;
		unsigned_n expo_time	:16;
		
		decimal_n spread;
		decimal_n range;

		chat *_conn;
		fire_sensor(uint8_t sensors = 8, 
					decimal_n spread = 45, /*degrees*/ 
					decimal_n range = 70 /*cm*/);
					
		fire_sensor(chat &c,
					uint8_t sensors = 8, 
					decimal_n spread = 45, /*degrees*/ 
					decimal_n range = 70 /*cm*/);
					
		fire_sensor(chat *c, 
					uint8_t sensors = 8, 
					decimal_n spread = 45, /*degrees*/ 
					decimal_n range = 70 /*cm*/);
		
		//~ bool update();
		//~ std::vector<node> get_data(bool update);
		void run();
		void question();
		void answer();
		void decode();
		void encode();
		void update();
	private:
		/* add your private declarations */
};

const std::map<uint8_t, std::vector<uint8_t>> fire_sensor::table = {{fire_sensor::SND_DAT, {fire_sensor::SND_DAT}}, 
																	{fire_sensor::SND_CON, {fire_sensor::SND_CON}},
																	{fire_sensor::SET_ALL, {fire_sensor::SET_ALL}},};

#endif /* FIRE_SENSOR_HPP */ 
