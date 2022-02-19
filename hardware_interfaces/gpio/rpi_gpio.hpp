/*
 * rpi_gpio.hpp
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


#ifndef RPI_GPIO_HPP
#define RPI_GPIO_HPP

class rpi_gpio {
	public:
		const uint8_t serial_pin = 4; // Using the WiringPi numbering
		#ifndef __arm__
		bool placeholder = false;
		#endif
		
		rpi_gpio();
		void init();
		steady last_toggled;
		void enable_serial();
		void disable_serial();
		bool get_state();
		bool run();
			
	private:
		/* add your private declarations */
};

#endif /* RPI_GPIO_HPP */ 
