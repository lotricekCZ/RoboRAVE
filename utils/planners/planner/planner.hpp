/*
 * planner.hpp
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
#include "../../data_containers/map/map.cpp"
#include "../../../elements/radius/radius.h"
//~ #include "./optimization/ant_colony.cpp"
#include "step.cpp"
#include <vector>

#ifndef PLANNER_HPP
#define PLANNER_HPP

class planner
{
	public:
		angles * sight;
		planner();
		std::vector<step> plan;
		std::vector<circle> perimeters;
		circle create_perimeter(coordinates);
		
		std::vector<circle> circle_generate(coordinates goal, coordinates start, map &); // function to create all circles with goal coordinate on it
		std::vector<circle> perimeter_generate(map &m);
		
		std::vector<coordinates> plan_make(coordinates goal, coordinates start, map &); 
		std::vector<coordinates> coincidental_points_generate(std::vector<circle>& circles);
		//~ std::vector<step> plan_trace(std::vector<coordinates>, coordinates goal, coordinates start, map &); // traces the path in lines, perhaps it'll sort the stuff
		bool collides(wall w, coordinates start, coordinates end);
		bool collides_nowhere(map& m, coordinates start, coordinates end);
		//~ void plan_make(coordinates goal, coordinates start, std::vector<coordinates>&, map &); // useless
		std::vector<travel_node> expand(std::vector<travel_node> nodes, std::vector<travel_node> prev_nodes,  unsigned_b id_curr);
		//~ std::vector<step> plan_make(location goal, location start, decimal_n current_angle, map &); 
		//~ void plan_make(location goal, location start, decimal_n current_angle, std::vector<step>&, map &); 
		// makes plan geometrically, does not assign speeds or something exact
		std::vector<step> make_path(std::vector<coordinates> &c, coordinates start, coordinates end, map &m);
		std::vector<step> plan_calculate(std::vector<step>); 
		// makes speeds assigned, new coordinates, angle and steps calculated
		
		
		travel_node search_by_id(unsigned_b id, std::vector<travel_node> &nodes);
		
	private:
		/* add your private declarations */
};

#endif /* PLANNER_HPP */ 
