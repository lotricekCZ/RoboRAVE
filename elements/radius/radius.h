/*
 * radius.h
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

#ifndef ELEMENTS_RADIUS_H
#define ELEMENTS_RADIUS_H

#include "../../defines/typedefines.h"
#include "../triangle/triangle.cpp"

#include <pthread.h>
#include <cmath>
#include <iostream>
#include <future>
#include <thread>
#include <vector>


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

class radius{
	public:		
		static decimal_n from_speeds(decimal_n speed_left, decimal_n speed_right){
			return ((speed_left + speed_right) / (speed_left - speed_right)) * (dist_wheel / 2);
			}
			
		static decimal_n from_speeds(speeds sp){
			return from_speeds(sp.left, sp.right);
			}
			
			
		static decimal_n from_3_points(coordinates a, coordinates b, coordinates c){
			triangle abc(a, b, c);
			//~ std::cout << abc.length() << "\t" << abc.herone_s() << std::endl;
			return (abc.len_a * abc.len_b * abc.len_c) / (4.0 * abc.herone_s());
			
			
			}
			
		static coordinates coords(coordinates a, coordinates b, coordinates c){
			decimal_n ma = (b.y - a.y) / (b.x - a.x);
			decimal_n mb = (c.y - b.y) / (c.x - b.x);
			coordinates center;
			decimal_n r = from_3_points(a, b, c);
			decimal_n x_delta = a.x - center.x;
			
			center.x = (ma * mb * (a.y - c.y) + mb * (a.x + b.x) - ma * (b.x + c.x)) / (2 * (mb - ma));
			center.y = (1 / (2 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)))) * (\
						(pow(a.x, 2) + pow(a.y, 2)) * (c.x - b.x) + \
						(pow(b.x, 2) + pow(b.y, 2)) * (a.x - c.x) + \
						(pow(c.x, 2) + pow(c.y, 2)) * (b.x - a.x));
			//~ std::cout << "\n: " << round(pow(r, 2) * 100) << "y:" << round(pow(x_delta, 2) * 100) <<"";
			//~ std::cout << "\nbod A: " << "[" << a.x << "; " << a.y <<"]";
			//~ std::cout << "\nbod B: " << "[" << b.x << "; " << b.y <<"]";
			//~ std::cout << "\nbod C: " << "[" << c.x << "; " << c.y <<"]";
			//~ std::cout << "\npolomer: " << r <<"";
			//~ std::cout << "\nstred: x: " << center.x << " y: " << center.y <<"\n";
			return center;
			}
		
		static coordinates coords(decimal_n in_radius, decimal_n hypotenuse, decimal_n x_rel, decimal_n y_rel){
			decimal_n height = sqrt(pow((in_radius * 100.0), 2) - pow((hypotenuse / 2.0), 2));
			decimal_n rho = acos(hypotenuse / (in_radius * 200.0)); // angle between hypotenuse and radius
			decimal_n phi = atan(y_rel / x_rel);
			decimal_n alpha = phi - rho;
			coordinates ret;
			ret.x = in_radius * 100 * cos(alpha);
			ret.y = in_radius * 100 * sin(alpha);
			return ret;
			}
		
		static coordinates coords(decimal_n in_radius, decimal_n hypotenuse, coordinates rel){
			return coords(in_radius, hypotenuse, rel.x, rel.y);
		}
		
		// tecny z bodu
		static std::vector<coordinates> tangent_points(coordinates center, decimal_n radius_c, coordinates point){
			decimal_n diff_x = point.x - center.x;
			decimal_n diff_y = point.y - center.y;
			decimal_n dxr = -diff_y; 
			decimal_n dyr = diff_x;
			decimal_n distance = center.get_distance(point);
			std::vector<coordinates> ret;
			if (distance >= radius_c){
				decimal_n rho = radius_c / distance;
				decimal_n ad = pow(rho, 2);
				decimal_n bd = rho * sqrt(1-pow(rho, 2));
				ret.push_back(coordinates(center.x + ad * diff_x + bd*dxr, center.y + ad*diff_y + bd*dyr));
				ret.push_back(coordinates(center.x + ad * diff_x - bd*dxr, center.y + ad*diff_y - bd*dyr));
				}
			return ret;
			}

		
	};

#endif // ELEMENTS_RADIUS_H


