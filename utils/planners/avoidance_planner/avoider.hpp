/*
 * avoider.hpp
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
#include "../../../elements/circle/circle.hpp"
#include "../../../elements/vector/vector.hpp"
#include "../planner/step.hpp"
//~ #include "movement_utils.cpp"
#include <vector>
#include <stdexcept>
#include <cassert>

#ifndef AVOIDER_HPP
#define AVOIDER_HPP

class avoider {
	public:
		avoider();
		static std::vector<step> avoid(std::vector<step> steps, wall w);
		static void eliminate_tangents(std::vector<step>& steps, std::vector<step> circular_steps);
		static void eliminate_tangents(std::vector<step>& steps, std::vector<circle> circles, std::vector<coordinates> selected, decimal_n escape_angle);
		static std::vector<step> to_steps(std::vector<line> tangents, circle future, circle current);
	private:
		/* add your private declarations */
};

#endif /* AVOIDER_HPP */ 
