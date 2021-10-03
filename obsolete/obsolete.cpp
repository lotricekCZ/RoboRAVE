/*
 * obsolete.cpp
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


#include "obsolete.hpp"

decimal_n calculate_omega(decimal_n T_avg){
	//~ printf("omega con %f\nTavg %f\n %.20Lf\n", omega_wheel_const, T_avg, pi);
	return (variables::omega_wheel_const * T_avg);
	}




decimal_n calculate_T_avg(decimal_n T_left, decimal_n T_right){
	return ((T_right - T_left) / (decimal_n)(T_right * T_left));
	}




decimal_n calculate_distance_wheel(decimal_n period, decimal_n time){
	return abs((time * variables::wheel_step_length_const)/(decimal_n)period);
	}




decimal_n c_f(char * input){
	return (decimal_n)atof(input);
	}




signed_n c_i(char * input){
	return atoi(input);
	}




decimal_n get_gamma(signed_n x_rel, signed_n y_rel){
	return atan((decimal_n)y_rel / (decimal_n)x_rel);
	}



	
decimal_n get_radius(decimal_n x_rel, decimal_n y_rel){
	return sqrt(pow(x_rel, 2) + pow(y_rel, 2));
	}





decimal_n coords_x(decimal_n alpha, decimal_n gamma, decimal_n radius, uint8_t dec){
	return (((dec >> 1) & 1? 1 : -1))*cos((alpha) + ((dec & 1)? (1) : (-1))* gamma)*radius;
	}




decimal_n coords_y(decimal_n alpha, decimal_n gamma, decimal_n radius, uint8_t dec){
	return (((dec >> 1) & 1? 1 : -1))*sin((alpha) + ((dec & 1)? (1) : (-1))* gamma)*radius;
	}


/*
 * 
 * name: coords_n
 * @param alpha - aktualni natoceni v prostoru
 * @param rel - relative coordinates / vector
 * @return delta souradnic v realnem prostoru
 * 
 */

coordinates coords_n(decimal_n alpha, coordinates rel){
	return coordinates(rel.x * cos(alpha) - (rel.y * sin(alpha)), rel.x * sin(alpha) + (rel.y * cos(alpha)));
	}
