/*
 * map.cpp
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


#include "map.hpp"
#include <algorithm>
#ifndef MAP_CPP
#define MAP_CPP

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
			b.push_back(location(ht, wt, location::_unknown));
			wt += map_raster;
			}
		wt = w;
		ht += map_raster;
		}
	return b;
	}
	
	
location map::interest_calculate(){
	std::vector<location> _map_priority;
	//~ _map_priority.assign(_map.begin(), _map.end());
	//~ int points = 0;
	for (auto& point: _map){
		point.classification.interest_level = calculate_location(point);
		}
	//~ _map.assign(_map_priority.begin(), _map_priority.end());
	return interest_maximal(_map)._coordinates;
	}
	
	
decimal_n map::calculate_location(location lo){
	coordinates c = lo._coordinates;
	decimal_n x = c.x, y = c.y, distance = 0, interest = 0;
	
	using namespace tresholds::explo;
	// scaled down part of map based on maximal range
	//~ std::cout << "\ncoords:\nx: " << c.x << "\ty: " << c.y << std::endl;
	for (auto o: _map){
		if(abs(o._coordinates.x - x) < (influence::interesting * map_unit) || \
			abs(o._coordinates.y - y) < (influence::interesting * map_unit)){
			distance = lo.get_distance(o);
			switch(o.get_point()){
				case location::_unknown:
					interest += (distance < (influence::unknown * map_unit)? \
									(1.0f - distance / (influence::unknown * map_unit)) * objects::unknown : 0);
					break;
					
				case location::_candle:
					interest += (distance < (influence::candle * map_unit)? \
									(1.0f - distance / (influence::candle * map_unit)) * objects::candle : 0);
					break;
					
				case location::_interesting:
					interest += (distance < (influence::interesting * map_unit)? \
									(1.0f - distance / (influence::interesting * map_unit)) * objects::interesting : 0);
					break;
					
				case location::_barrier:
					interest += (distance < (influence::barrier * map_unit)? \
									(1.0f - distance / (influence::barrier * map_unit)) * objects::barrier : 0);
					break;
					
				case location::_discovered:
					interest += (distance < (influence::discovered * map_unit)? \
									(1.0f - distance / (influence::discovered * map_unit)) * objects::discovered : 0);
					break;
					
				case location::_boring:
					interest += (distance < (influence::boring * map_unit)? \
									(1.0f - distance / (influence::boring * map_unit)) * objects::boring : 0);
					break;
				}
				//~ interest += 			
			}
		}
		return interest;
	}

location map::interest_maximal(std::vector<location> inmap){
	
	location max;
	
	max.set_interest( -1*(1<<22));
	for (auto o: inmap){
		//~ std::cout << "interest: " << o.get_interest() << std::endl;
		//~ std::cout << "x: " << o._coordinates.x << "  y: " << o._coordinates.y << std::endl;
		if(o.get_interest() > max.get_interest()){
			max = o;
			}
		}
	
	std::cout << "interest max: " << max.get_interest() << std::endl;
	return max;
	}
	
	
void map::interest_map(){
	
	std::sort(_map.begin(), _map.end(), [](location a, location b){return (a._coordinates.y < b._coordinates.y);});
	std::vector<location> same_y;
	decimal_n y = _map[0]._coordinates.y;
	
	for(auto i: _map){
		if(y == i._coordinates.y){
			same_y.push_back(i);
			}
		else {
			y = i._coordinates.y;
			std::sort(same_y.begin(), same_y.end(), [](location a, location b){return (a._coordinates.x < b._coordinates.x);});
			
			//~ for(auto o: same_y){
				//~ std::cout << "x:" << o._coordinates.x <<  "y: "<< o._coordinates.y << "\t";
				//~ }
			std::cout << "\n";
			for(auto o: same_y){
				std::cout << "" << o.get_interest() <<  "\t";
				}
				
			std::cout << "\n";
			same_y.clear();
			}
		}
	}
	
		
void map::append(location in){
	_map.push_back(in);
	}
	
#endif
