/*
 * step.cpp
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

#include "../../../elements/circle/circle.cpp"
#include "../../../elements/line/line.cpp"
#include "../../data_containers/speeds/speeds.cpp"
#include "../../../defines/constants.h"
#include <string>
#include <limits>
#include <variant>

#include "step.hpp"


step::step()
{
	
}

	
step::step(coordinates start, coordinates end, coordinates center){
	this -> start = start;
	this -> end = end;
	this -> _type = circle_e;
	this -> formula = circle(center, start.get_distance(center));
	}
	
	
step::step(coordinates start, coordinates end){
	this -> start = start;
	this -> end = end;	
	this -> _type = line_e;
	this -> formula = line(start, end);
	
	}

std::string step::inkscape_print(){
	switch(_type){
		case line_e:
			return " <path id=\"path853\" d=\"M "+ std::to_string(start.x)+","+ std::to_string(start.y)+","+ \
				std::to_string(end.x)+","+ std::to_string(end.y)+"style=\"fill:none;stroke:#000000;stroke-width:0.564583px;\
				stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\" />";
			
			
		case circle_e:
			return "<path style=\"opacity:1;fill:none;stroke:#008080;stroke-width:0.564999;stroke-linecap:round;stroke-linejoin:round;paint-order:stroke fill markers\"\
			\tid=\"path833\"\n\
			\tsodipodi:type=\"arc\" \n\
			\tsodipodi:cx=\"" + std::to_string(std::get<circle>(formula).center.x) +"\"\n\
			\tsodipodi:cy=\"" + std::to_string(std::get<circle>(formula).center.y) +"\"\n\
			\tsodipodi:rx=\"" + std::to_string(std::get<circle>(formula).radius) +"\"\n\
			\tsodipodi:ry=\"" + std::to_string(std::get<circle>(formula).radius) +"\"\n\
			\tsodipodi:start=\"" + std::to_string(std::get<circle>(formula).center.get_gamma(start)) +"\"\n\
			\tsodipodi:end=\"" + std::to_string(std::get<circle>(formula).center.get_gamma(end)) +"\"\n\
			\tsodipodi:arc-type=\"arc\"\n\
			\tsodipodi:open=\"false\" />\n";
		}
	return "";
	}

std::pair<step, step> step::get_perimeters(step s, decimal_n perimeter){
	switch(s._type){
		case line_e: {
			circle c = circle(s.start, perimeter);
			line trace = line(s.start, s.end);
			line perp = trace.make_perpendicular(s.start);
			std::vector<coordinates> starts = circle::intersection(perp, c);
			perp = perp.make_parallel(s.end);
			return std::make_pair(step(starts[0], perp.intersection(trace.make_parallel(starts[0]))), 
								step(starts[1], perp.intersection(trace.make_parallel(starts[1]))));
			}
		case equation_type::circle_e: {
			circle c = std::get<circle>(s.formula);
			circle bigger = c + perimeter;
			circle smaller = c - perimeter;
			line control_start(c.center, s.start);
			line control_end(c.center, s.end);
			return std::make_pair(step(s.start.get_closest(bigger.intersection(control_start)), s.end.get_closest(bigger.intersection(control_end)), c.center),
									step(s.start.get_closest(smaller.intersection(control_start)), s.end.get_closest(smaller.intersection(control_end)), c.center));
			}
		}
	}
