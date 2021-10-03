/*
 * obsolete.hpp
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

#include "./../defines/typedefines.h"
#include "./../defines/variables.hpp"
#include "./../utils/data_containers/coordinates/coordinates.hpp"
#include <cmath>

#ifndef OBSOLETE_HPP
#define OBSOLETE_HPP

decimal_n calculate_omega(decimal_n T_avg = 0);
decimal_n calculate_T_avg(decimal_n T_left = 0, decimal_n T_right = 0);
decimal_n calculate_distance_wheel(decimal_n period, decimal_n time);
decimal_n c_f(char * input);
signed_n c_i(char * input);
decimal_n get_gamma(signed_n x_rel, signed_n y_rel);
decimal_n get_radius(decimal_n x_rel, decimal_n y_rel);
decimal_n coords_x(decimal_n alpha, decimal_n gamma, decimal_n radius, uint8_t dec);
decimal_n coords_y(decimal_n alpha, decimal_n gamma, decimal_n radius, uint8_t dec);
coordinates coords_n(decimal_n alpha, coordinates rel);

#endif /* OBSOLETE_HPP */ 
