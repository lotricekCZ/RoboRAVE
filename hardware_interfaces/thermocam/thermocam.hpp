/*
 * thermocam.hpp
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


#ifndef THERMOCAM_HPP
#define THERMOCAM_HPP

#include <array>
#include <cmath>
#include <map>

class thermocam: public serial_peripheral{
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
		std::array<std::array<int8_t, 8>, 8> sensor;
		
		struct {
			unsigned first_index:	2;
			unsigned last_index:	2;
			unsigned current_index:	2;
		} presets;


		chat *_conn;
		//~ using serial_peripheral::_conn;
		thermocam();
		thermocam(chat *c);
		thermocam(chat &c);

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
		

		~thermocam();

		//~ bool update();
		//~ std::vector<node> get_data(bool update);
		void run() override;
		void question() override;
		void answer() override;
		void decode() override;
		void encode() override;
		void update() override;
		
		//~ thermocam& operator=(const thermocam& rhs);
	private:
		/* add your private declarations */
};

const std::map<uint8_t, std::vector<uint8_t>> thermocam::table = {{thermocam::SND_DAT, {thermocam::SND_DAT}}, 
																	{thermocam::SND_CON, {thermocam::SND_CON}},
																	{thermocam::SET_ALL, {thermocam::SET_ALL}},};

#endif /* thermocam_HPP */ 
