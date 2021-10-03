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


#include "../../data_containers/angles/angles/angles.hpp"
#include "../../data_containers/speeds/speeds.hpp"
#include "../../data_containers/coordinates/coordinates.hpp"
#include "../../data_containers/map/map.hpp"

#include "../../../elements/radius/radius.h"
#include "../avoidance_planner/avoider.hpp"

#include "dijkstra.hpp"
#include "travel_node.cpp"
//~ #include "./optimization/ant_colony.cpp"
//~ #include "step.hpp"
#include "step.hpp"
#include "path.hpp"
#include "movement_utils.cpp"
#include <vector>
#include <stdexcept>

#ifndef PLANNER_HPP
#define PLANNER_HPP

class planner {
	public:
		angles * sight;
		planner();
		std::vector<step> plan;
		std::vector<circle> perimeters;
		circle create_perimeter(coordinates, decimal_n radius = robot_radius * 2.0);
		
		std::vector<circle> circle_generate(coordinates goal, coordinates start, map &, uint8_t it = 0, decimal_n multiplier = 1); // function to create all circles with goal coordinate on it
		std::vector<circle> perimeter_generate(map &m);
		
		std::vector<step> plan_make(std::vector<coordinates> selected, map &m, decimal_n initial_rotation = 0); 
		std::vector<coordinates> coincidental_points_generate(std::vector<circle>& circles);
		static std::vector<path> list_options(std::vector<circle> selected, coordinates end, coordinates start, decimal_n initial_rotation = 0);
		/// line segment implementation
		// deprecated, see step::on_segment, step::intersection etc.
		bool collides(wall w, coordinates start, coordinates end);
		bool collides_nowhere(map& m, coordinates start, coordinates end);
		
		/// circle arc implementation
		// deprecated, see step::on_segment, step::intersection etc.
		bool collides(wall w, coordinates start, coordinates end, circle c, bool side);
		bool collides_nowhere(map &m, coordinates start, coordinates end, circle c, bool side);
		
		void alter_selected(std::vector<step>& selected, map& m, decimal_n initial_rotation);
		static std::vector<step> avoid(std::vector<step> altered, map& m);
		std::vector<travel_node> expand(std::vector<travel_node> nodes, std::vector<travel_node> prev_nodes, unsigned_b id_curr);
		std::vector<step> make_first_move(map& m, coordinates start, coordinates next, decimal_n initial_rotation, speeds v);
		static wall get_closest_wall(step s, map &m);
		
		/// makes plan geometrically, does not assign speeds or something exact
		std::vector<coordinates> make_path(std::vector<coordinates> &c, coordinates start, coordinates end, map &m);
		std::vector<step> plan_calculate(std::vector<step> s); 
		std::vector<step> extend(std::vector<step>& future_steps, std::vector<step>& branch, circle future, map& m); 
		// makes speeds assigned, new coordinates, angle and steps calculated
		decimal_n evaluate_radius(coordinates previous, coordinates current);
		decimal_n suiting_angle(std::array<line, 2> cross, coordinates *p_next, coordinates *p_previous = nullptr, coordinates *p_current = nullptr);
		decimal_n get_distance_to_walls(step s, map &m);
		travel_node search_by_id(unsigned_b id, std::vector<travel_node> &nodes);
		
	private:
		/* add your private declarations */
};

#endif /* PLANNER_HPP */ 
