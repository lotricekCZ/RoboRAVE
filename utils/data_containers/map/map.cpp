/*
 * map.cpp
 * 
 * Copyright 2020 Jakub Ramašeuski <jakub@jakub-ThinkPad-X250>
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


#include "map.hpp"


map::map()
{
	
}
std::vector<location> map::grid(int s_height, int s_width, int height, int width){
	//~ std::cout << s_height << "  " << height << std::endl;
	//~ std::cout << s_width << "  " << width << std::endl;
	int h = (s_height < height)? s_height : height, he = (s_height > height)? s_height : height, \
		w = (s_width < width)? s_width : width, we = (s_width > width)? s_width : width, \
		ht = h, wt = w;
	std::vector<location> b;
	//~ std::cout << h << " <= " << he << std::endl;
	//~ std::cout << w << " <= " << we << std::endl;
	
	while(ht <= he){
		while(wt <= we){
			b.push_back(location(ht, wt));
			wt += map_raster;
			//~ std::cout << ht << "  op made  " << he << std::endl;
			}
		wt = w;
		ht += map_raster;
		}
	return b;
	}
	
void map::append(location in){
	_map.push_back(in);
	}
