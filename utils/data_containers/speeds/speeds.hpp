/*
 * speeds.hpp
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

#include "../../../defines/constants.h"
#include "../setters/setters.tpp"

#ifndef UTILS_DATA_CONTAINERS_SPEEDS_SPEEDS_HPP
#define UTILS_DATA_CONTAINERS_SPEEDS_SPEEDS_HPP


class speeds: public setters<decimal_n>
{
	public:
		decimal_n left;
		decimal_n right;
		speeds();
		speeds(decimal_n, decimal_n);
		virtual ~speeds();
		signed_n to_hw_speed(decimal_n);
		decimal_n from_hw_speed(decimal_n);
	private:
		/* add your private declarations */
};

#endif /* UTILS_DATA_CONTAINERS_SPEEDS_SPEEDS_HPP */ 
