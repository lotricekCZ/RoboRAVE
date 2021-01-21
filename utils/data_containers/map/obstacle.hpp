/*
 * obstacle.hpp
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


#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

class obstacle
{
	public:
		obstacle();
		virtual bool inside(coordinates a){return false;}
		virtual bool inside(decimal_n x, decimal_n y){return false;}
		virtual std::vector<coordinates> points(){return std::vector<coordinates> ();}
		virtual bool is_collision_course(){return false;}
	private:
		/* add your private declarations */
};

#endif /* OBSTACLE_HPP */ 
