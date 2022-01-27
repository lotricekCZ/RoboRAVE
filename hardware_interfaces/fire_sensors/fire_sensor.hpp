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


class fire_sensor{
	public:
		std::vector<node> sensors;
		decimal_n spread;
		decimal_n range;
		chat *_conn;
		
		fire_sensor(uint8_t sensors = 8, 
					decimal_n spread = 45 /*degrees*/, 
					decimal_n range = 70 /*cm*/);
		bool update();
		std::vector<node> get_data(bool update);
	private:
		/* add your private declarations */
};

#endif /* FIRE_SENSOR_HPP */ 
