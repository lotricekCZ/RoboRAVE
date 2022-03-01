/*
 * speeds.cpp
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



#include "speeds.hpp"

#ifndef SPEEDS_CPP
#define SPEEDS_CPP

speeds::speeds(): setters()
{
	
}

speeds::speeds(decimal_n left, decimal_n right)
	: setters(), left(left), right(right)
{
	
}


signed_n speeds::to_hw_speed(decimal_n speed){ // 2^15 - 1 = overflow
	//~ std::cout << (2.0 * pi_const * r_wheel)/(N_wheel * speed) << std::endl;
	signed_n ret = (decimal_n)(2.0 * pi_const * r_wheel)/(N_wheel * speed) * 1000000;
	return (ret >= (1 << 14) || ret < -(1 << 14))? 1 << 14: ret;
}

decimal_n speeds::from_hw_speed(decimal_n time){ // 2^15 - 1 = overflow
	//~ std::cout << (2.0 * pi * r_wheel)/(N_wheel * speed) << std::endl;
	decimal_n ret = (decimal_n)(2000000.0 * pi_const * r_wheel)/(N_wheel * (decimal_n)time);
	return ret;
}

#endif
