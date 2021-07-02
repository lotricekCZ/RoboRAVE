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

	
step::step(coordinates start, coordinates end, coordinates center, bool is_right, bool compute_angle){
	this -> start = start;
	this -> end = end;
	this -> _type = circle_e;
	this -> direction_curve = is_right;
	this -> formula = circle(center, center.get_distance(start));
	
	/// block for optional activities
	if(compute_angle){
		decimal_n raw_start = start.get_gamma(center);
		decimal_n raw_end = end.get_gamma(center);
		this -> angle_start = (raw_start + (is_right? 0.5f: -0.5f) * pi_const);
		this -> angle_start = angle_start + ((angle_start >= 2*pi_const)? - 2*pi_const: (angle_start < 0)? 2*pi_const: 0);
		this -> angle_end = (raw_end + (is_right? 0.5f: -0.5f) * pi_const);
		this -> angle_end = angle_end + ((angle_end >= 2*pi_const)? - 2*pi_const: (angle_end < 0)? 2*pi_const: 0);
		if(is_right && (this -> angle_end > this -> angle_start)){ // means that it underflew
			std::cout << "opt 1" << std::endl;
			this -> phi = (((2*pi_const) - this -> angle_end) + this -> angle_start);
			}
		else if(!is_right && (this -> angle_end < this -> angle_start)){ // means that it overflew
			std::cout << "opt 2" << std::endl;
			this -> phi = (this -> angle_end + ((2*pi_const) - this -> angle_start));
			} else {
				std::cout << "opt 3" << std::endl;
				this -> phi = (this -> angle_end - this -> angle_start);
			}
		//~ this -> phi = (is_right? (this -> angle_end - this -> angle_start) :(2*pi_const - (this -> angle_end - this -> angle_start)));

		/// diagnostics
		std::cout << "zacatek " << start.print_geogebra() + "\t" << this -> angle_start / pi_const * 180 << std::endl;
		std::cout << "konec " << end.print_geogebra() + "\t" << this -> angle_end / pi_const * 180 << std::endl;
		std::cout << "phi  " << this -> phi / pi_const * 180 << std::endl;
		}
	}
	
	
step::step(coordinates start, coordinates end, bool compute_angle){
	this -> start = start;
	this -> end = end;	
	this -> _type = line_e;
	this -> formula = line(start, end);
	this -> phi = 0; // does not change
	this -> omega = 0; // does not change
	
	/// block for optional activities
	if(compute_angle){
		this -> angle_start = this -> angle_end = start.get_gamma(end);
		}
	}

std::string step::print_inkscape(){
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
	
std::string step::print(){
	switch(_type){
		case line_e: {
			return std::get<line>(this -> formula).print();
			}
		case equation_type::circle_e: {
			return std::get<circle>(this -> formula).print();
			}
		}
	}
	
std::string step::print_geogebra(){
	switch(_type){
		case line_e: {
			return "=Segment[" + start.print_geogebra() + "," + end.print_geogebra() + "]";
			}
		case equation_type::circle_e: {
			return "=CircularArc[" + std::get<circle>(this -> formula).center.print_geogebra() + 
						"," + ((direction_curve)? end.print_geogebra(): start.print_geogebra()) +
						"," + ((direction_curve)? start.print_geogebra(): end.print_geogebra()) + "]";
			}
		}
	}

std::vector<coordinates> step::intersection(step s, circle c){
	std::vector<coordinates> ret;
	switch(s._type){
		case line_e: {
			ret = c.intersection(std::get<line>(s.formula));
			for(std::vector<coordinates>::iterator i = ret.begin(); i < ret.end(); i++){
				if(!line::on_segment(*i, s.start, s.end)){
					ret.erase(i--);
					}
				}
			break;
			}
		case circle_e: {
			ret = c.intersection(std::get<circle>(s.formula));
			for(std::vector<coordinates>::iterator i = ret.begin(); i < ret.end(); i++){
				if(std::abs(std::abs(s.phi) - pi_const) >= 1e-4){ 
					// means that the angle isn't exactly 180 degrees and so the circle::on_segment method can be used 
					if(!(std::get<circle>(s.formula).on_segment(s.start, s.end, *i, std::abs(s.phi) > pi_const))){
						ret.erase(i--);
						}
					} else {
						//~ circle track = std::get<circle>(s.formula);
						decimal_n sta_end = s.start.get_gamma(s.end);
						decimal_n sta_point = s.start.get_gamma(*i);
						if(std::sin(sta_point - sta_end) > 0 ^ s.direction_curve){
							ret.erase(i--);
							}
						}
				}
			return ret;
			}
		}
	return ret;
	}
	
std::vector<coordinates> step::intersection(step s, line l){
	std::vector<coordinates> ret;
	switch(s._type){
		case line_e: {
			coordinates intersect = l.intersection(std::get<line>(s.formula));
			if(!line::on_segment(intersect, s.start, s.end)){
					ret.push_back(intersect);
					}
			break;
			}
		case circle_e: {
			ret = std::get<circle>(s.formula).intersection(l);
			for(std::vector<coordinates>::iterator i = ret.begin(); i < ret.end(); i++){
				if(!(std::get<circle>(s.formula).on_segment(s.start, s.end, *i, std::abs(s.phi) > pi_const))){
					ret.erase(i--);
					}
				}
			}
		}
	return ret;
	}
