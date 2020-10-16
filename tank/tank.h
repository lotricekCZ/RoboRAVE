/*
 * tank.h
 * 
 * Copyright 2020 Jakub Ramašeuski <jakub@skaryna.net>
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

#ifndef TANK_TANK_H
#define TANK_TANK_H

#ifndef decimal_n
	#define decimal_n float
#endif

#ifndef signed_n
	#include <inttypes.h>
	#define signed_n int16_t
#endif

#ifndef unsigned_n
	#include <inttypes.h>
	#define unsigned_n uint16_t
#endif

class tank{
	public:
		unsigned_n joystick_range = 100; // default joystick range
		
	
	
	};

#endif // TANK_TANK_H

