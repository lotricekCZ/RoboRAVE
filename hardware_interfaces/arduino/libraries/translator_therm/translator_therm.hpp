/*
 * translator_therm.hpp
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
#include "../driver_thermo/driver_thermo.cpp"

#ifndef TRANSLATOR_THERM_HPP
#define TRANSLATOR_THERM_HPP

class translator_therm {
	public:
		struct {
			unsigned first_index:	2;
			unsigned last_index:	2;
			unsigned current_index:	2;
		} presets;
		translator_therm();
		uint8_t data[16];
		thermo_driver *main_th_dr;
		void decompose(uint8_t in[16]);
		bool compose();
		bool is_longer();
			
	private:
		/* add your private declarations */
};

#endif /* TRANSLATOR_THERM_HPP */ 
