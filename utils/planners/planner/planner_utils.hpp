/*
 * planner_utils.hpp
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


#include "../../data_containers/angles/angles/angles.hpp"
#include "../../data_containers/speeds/speeds.hpp"
#include "../../data_containers/coordinates/coordinates.hpp"
#include "../../data_containers/map/map.hpp"

#include "../../../elements/radius/radius.h"
#include "../avoidance_planner/avoider.hpp"

#include "dijkstra.hpp"
#include "travel_node.cpp"
#include "step.hpp"
#include "path.hpp"
#include "movement_utils.cpp"
#include <iostream>
#include <utility>
#include <vector>
#include <array>
#include <cmath>
#include <stdexcept>

#ifndef PLAN_UTILS_HPP
#define PLAN_UTILS_HPP

class plan_utils {
	public:
		static std::vector<coordinates> closest_points(coordinates measured_point, std::vector<std::vector<coordinates>> source); // selects only the closest points from the vectors

	
};

#endif // PLAN_UTILS_HPP
