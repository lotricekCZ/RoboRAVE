/*
 * driver_thermo.hpp
 * 
 * Copyright 2022 Jakub Ramašeuski <jakub@skaryna.net>
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

#include <AMG88xx.h>
#include <cinttypes>

#ifndef DRIVER_THERMO_HPP
#define DRIVER_THERMO_HPP

class thermo_driver {
	public:
		uint16_t refresh =		75;
		unsigned frame_lock:	1; // To lock frame in order to have still picture
		uint32_t last_refresh = 0;
		thermo_driver();
		Adafruit_AMG88xx * main_thermocam;
		float grid[AMG88xx_PIXEL_ARRAY_SIZE];
		void handle_in_background();
		void capture();
	private:
		/* add your private declarations */
};

#endif /* DRIVER_THERMO_HPP */ 
