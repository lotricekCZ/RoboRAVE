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
		
		std::vector<step> plan_make(location goal, location start, decimal_n current_angle); 
		// makes plan geometrically, does not assign speeds or something exact
		
		std::vector<step> plan_calculate(std::vector<step>); 
		// makes speeds assigned, new coordinates, angle and steps calculated
	private:
		/* add your private declarations */
};

#endif /* PLANNER_HPP */ 
