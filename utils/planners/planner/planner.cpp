/*
 * planner.cpp
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


#include "planner.hpp"


planner::planner()
{
	
}

circle planner::create_perimeter(coordinates c){
	std::cout << c.print() << std::endl;
	return circle(c, robot_radius*2.0);
	}

std::vector<coordinates> planner::plan_make(coordinates goal, coordinates start, map &m){
	std::cout << "start: " << start.print() << "  goal: " << goal.print() << std::endl;
	std::vector<coordinates> out;
	std::vector<circle> circles;
	if(start == goal) return out;
	out.push_back(start);
	angles local_sight = angles().load_virtual(start, m);
	
	decimal_n distance = start.get_distance(goal);
	//~ decimal_n angle = start.get_gamma(goal);
	//~ decimal_n start_index = (angle / pi) * 180; // get this thing from radians
	circle range(start, distance);
	circles.push_back(range);
	
	for(auto w: m._map_walls){
		for(auto poi: w.properties.edges){
			if(range.inside(poi) && (poi.get_distance(start) < distance)){
				std::cout << circle(poi, poi.get_distance(goal)).print() << std::endl;
				//~ std::cout << range.inside(poi) << std::endl;
				circles.push_back(circle(poi, poi.get_distance(goal)));
				}
			}
		}
	
	for(uint16_t i = 0; i < circles.size(); i++){
		for(uint16_t e = 0; i < circles.size(); i++){
			if(!(circles[e] == circles[i])){
				std::vector<coordinates> tangs = circle().intersection(circles[e], circles[i]);
				out.insert(out.end(), tangs.begin(), tangs.end());
				}
			}
		}
	
	//~ std::sort( out.begin(), out.end() );
	std::sort(out.begin(), out.end(), [](coordinates a, coordinates b){return (a.x < b.x) || (a.y < b.y);});
	out.erase( unique( out.begin(), out.end() ), out.end() );
	
	
	return out;
	}

bool planner::collides(wall w, coordinates start, coordinates end){
	line lin(start, end);
	for(auto l: w.properties.walls){
		coordinates inters = lin.intersection(l, lin);
		if(lin.on_segment(inters, start, end) && w.inside(inters)){
			return true;
		}
	}
	return false;
}

std::vector<line> planner::plan_trace(std::vector<coordinates> c, coordinates goal, coordinates start, map &m){
	std::vector<coordinates> temp = c;
	std::vector<line> sketch;
	coordinates curr = start;
	coordinates next = goal;
	
	while(temp.size() != 0){
		for(size_t a = 0; a < temp.size(); a++){
			std::cout << curr.print() << "   " << next.print() << std::endl;
			bool possible = true;
			bool possible_goal = true;
			for(auto w: m._map_walls){
				if(possible_goal){
					possible_goal = !collides(w, curr, goal);
					}
				if(possible){
					possible = !collides(w, curr, next);
					}
				}
				
			if(possible_goal){
				sketch.push_back(line(curr, goal));
				return sketch;
				}
				
			if(possible){
				sketch.push_back(line(curr, next));
				curr = next;
				}
			next = temp[a];
			temp.erase(temp.begin() + a);
			//~ if(possible){
				//~ sketch.push_back(curr_l);
				//~ if(next == goal){
					//~ return sketch;
				//~ }
				//~ curr = temp[a];
				//~ temp.erase(temp.begin() + a);
				//~ curr_l = line()
				//~ }
			}
		}
	return sketch;
	}
	
std::vector<step> planner::plan_calculate(std::vector<step> in){
	std::vector<step> out = in;
	
	return out;
	}
