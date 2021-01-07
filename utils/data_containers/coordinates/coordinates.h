/*
 * coordinates.h
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


#ifndef UTILS_DATA_CONTAINERS_COORDINATES_COORDINATES_H
#define UTILS_DATA_CONTAINERS_COORDINATES_COORDINATES_H


#include "../../../defines/typedefines.h"

class coordinates
{
	public:
		coordinates();
		coordinates(decimal_n, decimal_n);
		decimal_n x;
		decimal_n y;
		coordinates make_local(coordinates, coordinates, decimal_n ang);
		coordinates make_local(coordinates, decimal_n, decimal_n);
		decimal_n get_gamma(decimal_n x_rel, decimal_n y_rel);
		decimal_n get_distance(decimal_n x_rel, decimal_n y_rel);
		decimal_n get_distance(coordinates c);
		uint8_t get_dec(decimal_n x_rel, decimal_n y_rel);
		uint8_t get_dec(decimal_n rads);
		decimal_n get_rel_x(decimal_n alpha, decimal_n gamma, decimal_n radius, uint8_t dec);
		decimal_n get_rel_y(decimal_n alpha, decimal_n gamma, decimal_n radius, uint8_t dec);
		
		
	private:
		/* add your private declarations */
};

#endif /* COORDINATES_H */ 
