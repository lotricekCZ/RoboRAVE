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
