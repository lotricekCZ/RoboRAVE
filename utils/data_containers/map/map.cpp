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

std::vector<location> map::grid(int s_height = 0, int s_width = 0, int height = 1000, int width = 1000){
	
	int h = (s_height < height)? s_height : height, he = (s_height > height)? s_height : height, \
		w = (s_width < width)? s_width : width, we = (s_width > width)? s_width : width, \
		ht = h, wt = w;
	std::vector<location> b;
	
	while(ht <= he){
		while(wt <= we){
			b.push_back(location(ht, wt));
			wt += map_raster;
			}
		wt = w;
		ht += map_raster;
		}
	return b;
	}
	
	
coordinates map::interest_calculate(){
	std::vector<location> _map_priority = _map;
	for (auto point: _map_priority){
		point.set_interest(calculate_location(point));
		}
	_map = _map_priority;
	return interest_maximal(_map)._coordinates;
	}
	
signed_b map::calculate_location(location lo){
	coordinates c = lo._coordinates;
	decimal_n x = c.x, y = c.y, distance = 0, interest = 0;
	
	using namespace tresholds::explo;
	// scaled down part of map based on maximal range
	for (auto o: _map){
		if(abs(o._coordinates.x - x) < (influence::interesting * map_raster) || \
			abs(o._coordinates.y - y) < (influence::interesting * map_raster)){
			distance = o.get_distance(c);
			if(distance < (influence::interesting * map_raster)){
				switch(lo.get_point()){
					case location::_unknown:
						interest += (distance < (influence::unknown * map_raster)? \
										(1.0f - distance / influence::unknown) * objects::unknown : 0);
						break;
						
					case location::_candle:
						interest += (distance < (influence::candle * map_raster)? \
										(1.0f - distance / influence::candle) * objects::candle : 0);
						break;
						
					case location::_interesting:
						interest += (distance < (influence::interesting * map_raster)? \
										(1.0f - distance / influence::interesting) * objects::interesting : 0);
						break;
						
					case location::_barrier:
						interest += (distance < (influence::barrier * map_raster)? \
										(1.0f - distance / influence::barrier) * objects::barrier : 0);
						break;
						
					case location::_discovered:
						interest += (distance < (influence::discovered * map_raster)? \
										(1.0f - distance / influence::discovered) * objects::discovered : 0);
						break;
						
					case location::_boring:
						interest += (distance < (influence::boring * map_raster)? \
										(1.0f - distance / influence::boring) * objects::boring : 0);
						break;
					}
				//~ interest += 
				}			
			}
		}
		return interest;
	}

location map::interest_maximal(std::vector<location> inmap){
	
	location max;
	
	max.set_interest( -1*(1<<22));
	for (auto o: inmap){
		if(o.get_interest() > max.get_interest()){
			max.set_interest(o.get_interest());
			}
		}
	return max;
	}
	
	
coordinates map::interest_scale(signed_b max){
	
	}
	
		
void map::append(location in){
	_map.push_back(in);
	}
