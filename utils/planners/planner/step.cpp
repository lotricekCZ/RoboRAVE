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
			//~ std::cout << "opt 1" << std::endl;
			this -> phi = (((2*pi_const) - this -> angle_end) + this -> angle_start);
			}
		else if(!is_right && (this -> angle_end < this -> angle_start)){ // means that it overflew
			//~ std::cout << "opt 2" << std::endl;
			this -> phi = (this -> angle_end + ((2*pi_const) - this -> angle_start));
			} else {
				//~ std::cout << "opt 3" << std::endl;
				this -> phi = (this -> angle_end - this -> angle_start);
			}
		//~ this -> phi = (is_right? (this -> angle_end - this -> angle_start) :(2*pi_const - (this -> angle_end - this -> angle_start)));

		/// diagnostics
		//~ std::cout << "zacatek " << start.print_geogebra() + "\t" << this -> angle_start / pi_const * 180 << std::endl;
		//~ std::cout << "konec " << end.print_geogebra() + "\t" << this -> angle_end / pi_const * 180 << std::endl;
		//~ std::cout << "phi  " << this -> phi / pi_const * 180 << std::endl;
		}
	}
	
	
step::step(coordinates start, coordinates end, bool compute_angle){
	this -> start = start;
	this -> end = end;	
	this -> _type = line_e;
	this -> formula = line(start, end);
	this -> phi = 0; // does not change
	this -> omega = 0; // does not change
	
	//~ std::cout << "zacatek " << start.print_geogebra() + "\t" << this -> angle_start / pi_const * 180 << std::endl;
	//~ std::cout << "konec " << end.print_geogebra() + "\t" << this -> angle_end / pi_const * 180 << std::endl;
	
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

std::vector<coordinates> step::intersection(circle c){
	return step::intersection(*this, c);
	}


std::vector<coordinates> step::intersection(step b){
	return step::intersection(*this, b);
	}

std::vector<coordinates> step::intersection(line l){
	return step::intersection(*this, l);
	}


std::vector<coordinates> step::intersection(step s, circle c){
	std::vector<coordinates> ret;
	switch(s._type){
		case line_e: {
			ret = c.intersection(std::get<line>(s.formula));
			for(std::vector<coordinates>::iterator i = ret.begin(); i < ret.end(); i++){
				if(!s.on_segment_linear(*i)){
					ret.erase(i--);
					}
				}
			break;
			}
		case circle_e: {
			ret = c.intersection(std::get<circle>(s.formula));
			for(std::vector<coordinates>::iterator i = ret.begin(); i < ret.end(); i++){
				if(!s.on_segment_circular(*i)){
					ret.erase(i--);
					}
				}
			return ret;
			}
		}
	return ret;
	}


std::vector<coordinates> step::intersection(step a, step b){
	std::vector<coordinates> ret;
	switch(a._type){
		case line_e: {
			ret = step::intersection(b, std::get<line>(a.formula));
			for(std::vector<coordinates>::iterator i = ret.begin(); i < ret.end(); i++){
				if(!a.on_segment_linear(*i)){
					ret.erase(i--);
					}
				}
			break;
			}
		case circle_e: {
			ret = step::intersection(b, std::get<circle>(a.formula));
			for(std::vector<coordinates>::iterator i = ret.begin(); i < ret.end(); i++){
				if(!a.on_segment_circular(*i)){
					ret.erase(i--);
					}
				}
			break;
			}
		}
	return ret;
	}

std::vector<coordinates> step::intersection(step s, line l){
	std::vector<coordinates> ret;
	switch(s._type){
		case line_e: {
			coordinates intersect = l.intersection(std::get<line>(s.formula));
			if(s.on_segment_linear(intersect)){
					ret.push_back(intersect);
					}
			break;
			}
		case circle_e: {
			ret = std::get<circle>(s.formula).intersection(l);
			for(std::vector<coordinates>::iterator i = ret.begin(); i < ret.end(); i++){
				if(!s.on_segment_circular(*i)){
					ret.erase(i--);
					}
				}
			}
		}
	return ret;
	}


bool step::on_segment_circular(coordinates point){
	if(std::abs(std::abs(phi) - pi_const) >= 1e-4){ 
		// means that the angle isn't exactly 180 degrees and so the circle::on_segment method can be used 
		if(!(std::get<circle>(formula).on_segment(start, end, point, std::abs(phi) > pi_const))){
			return false;
			}
		} else {
			//~ circle track = std::get<circle>(formula);
			decimal_n sta_end = start.get_gamma(end);
			decimal_n sta_point = start.get_gamma(point);
			if((std::sin(sta_point - sta_end) > 0) ^ direction_curve){
				return false;
				}
			}
	return true;
	}

bool step::on_segment_linear(coordinates point){
	return line::on_segment(point, start, end);
	}


decimal_n step::get_distance(step s, coordinates c, bool carry_caps){
	decimal_n ret = std::numeric_limits<decimal_n>::infinity();
	bool cap = false;
	switch(s._type){
		case line_e: {
			coordinates p = line::intersection(std::get<line>(s.formula), 
							std::get<line>(s.formula).make_perpendicular(c)); /// always exactly one point
			if(s.on_segment_linear(p)){
				ret = p.get_distance(c);
				} else {
					/// toggles bool cap
					cap = true;
					decimal_n d_start = c.get_distance(s.start);
					decimal_n d_end = c.get_distance(s.end);
					ret = (d_end < d_start)? d_end: d_start;
					}
			break;
			}

		case circle_e: {
			bool passed = false;
			std::vector<coordinates> p = circle::intersection(line(c, std::get<circle>(s.formula).center),
															std::get<circle>(s.formula)); /// always exactly two points
			for(auto i: p){
				if(((c.get_distance(i) < std::get<circle>(s.formula).radius) | 
						line::on_segment(i, std::get<circle>(s.formula).center, c))){
					if(s.on_segment_circular(i)){
						/** 
						 * 	this means that the point is closer to intersection than center 
						 * 	or the intersection is between center and point and intersection is on segment 
						 * 	- by that it is sure that the closest distance to circular segment is from that intersection
						 **/
						 passed = true;
						 decimal_n comp_ret = c.get_distance(i);
						 ret = (comp_ret < ret)? comp_ret: ret;
						} else {
							/// toggles bool cap
							cap = true ^ passed;
							decimal_n d_start = c.get_distance(s.start);
							decimal_n d_end = c.get_distance(s.end);
							ret = (d_end < d_start)? ((d_end < ret)? d_end: ret): ((d_start < ret)? d_start: ret);
							}
						}
				}
			break;
			}
		}
	return ((carry_caps | (!carry_caps ^ cap))? ret: std::numeric_limits<decimal_n>::infinity());
	}

decimal_n step::get_distance(step s, line l, bool carry_caps){
	decimal_n ret = std::numeric_limits<decimal_n>::infinity();
	std::vector<coordinates> inter;
	switch(s._type){
		case line_e: {
			decimal_n d_start = l.get_distance(s.start);
			decimal_n d_end = l.get_distance(s.end);
			if(std::abs(d_start + d_end - s.start.get_distance(s.end)) <= 1e-4){
				return 0; // it is definite that it cuts the segment, no need to calculate
				}
			ret = (d_start < d_end)? d_start: d_end; // no caps here, sorry
			break;
			}
		
		case circle_e: {
			inter = circle::intersection(l, std::get<circle>(s.formula));
			if(inter.size() != 0){
				for(auto i: inter){
					if(s.on_segment_circular(i)){
						return 0; /* intersection that lies on segment -> 0 distance to curve, 
									no need to compute any further */
						}
					}
				}
			line perp = l.make_perpendicular(std::get<circle>(s.formula).center);
			inter = step::intersection(s, perp);
			for(auto i: inter){
				decimal_n retc = line::get_distance(l, i); // return candidate
				ret = (ret < retc)? ret: retc;
				} // this gives us the lowest
				
			if (carry_caps){
				decimal_n d_min = l.get_distance(s.start);
				decimal_n d_end = l.get_distance(s.end);
				d_min = (d_min < d_end)? d_min: d_end;
				ret = (ret < d_min)? ret: d_min;
			}
			break;
			}
		}
		return ret;
	}

bool step::on_segment(coordinates point){
	return (_type == line_e)? (on_segment_linear(point)): (on_segment_circular(point));
	}

decimal_n step::get_distance(step s, circle c){
	decimal_n ret = step::get_distance(s, c.center) - c.radius;
	return (ret > 0)? ret: 0; /* If less than zero to that point, 
				it means that it has at least one intersection */
	}

decimal_n step::get_distance(step a, step b, bool carry_caps){
	switch(a._type) {
		case line_e: {
			switch(b._type) {
				case line_e: { // both are linear segments
					return get_distance_linears(a, b, carry_caps);
					}
					
				case circle_e: { // combined
					return get_distance_combined(a, b, carry_caps);
					}
				}
			}
			
		case circle_e:{
			switch(b._type) {
				case line_e: { // combined
					return get_distance_combined(a, b, carry_caps);
					}
					
				case circle_e: { // both are circular
					return get_distance_circulars(a, b, carry_caps);
					}
				}
			break;
			}
		}
	}

decimal_n step::get_distance_linears(step a, step b, bool carry_caps){
	if(a._type != b._type | (a._type & b._type)){
		// that's just fucked, this is the linears section
		std::cerr << "You garbage tried to put in there some circular steps\nPROOF:\t" << a.print_geogebra() 
			<< "\t" << b.print_geogebra() << std::endl;
		if((a._type == circle_e) && (b._type == circle_e)){
			return step::get_distance_linears(a, b, carry_caps);
			} else {
				return step::get_distance_combined(a, b, carry_caps);
				}
		return 666;
		}

	if(step::intersection(a, b).size() != 0){
		return 0;
	}
		
	std::vector<line> intersections;
	decimal_n ret = std::numeric_limits<decimal_n>::infinity();
	line a_start 	= std::get<line>(b.formula).make_perpendicular(a.start);
	line a_end 		= std::get<line>(b.formula).make_perpendicular(a.end);
	line b_start 	= std::get<line>(a.formula).make_perpendicular(b.start);
	line b_end 		= std::get<line>(a.formula).make_perpendicular(b.end);
	
	std::vector<coordinates> int_a_start_b 	= step::intersection(b, a_start);
	std::vector<coordinates> int_a_end_b 	= step::intersection(b, a_end);
	std::vector<coordinates> int_b_start_a 	= step::intersection(a, b_start);
	std::vector<coordinates> int_b_end_a 	= step::intersection(a, b_end);
	
	std::array<std::vector<coordinates>, 4> inters = {int_a_start_b, int_a_end_b, int_b_start_a, int_b_end_a};
	std::vector<coordinates> origins = {a.start, a.end, b.start, b.end};
	
	for(uint8_t i = 0; i < inters.size(); i++)
		if(inters[i].size() != 0){
			//~ std::cout << inters[i][0].print_geogebra() << std::endl;
			decimal_n retc = origins[i].get_distance(inters[i][0]);
			ret = (ret < retc)? ret: retc;
			}
	decimal_n start_start = a.start.get_distance(b.start);
	decimal_n start_end = a.start.get_distance(b.end);
	decimal_n end_start = a.end.get_distance(b.start);
	decimal_n end_end = a.end.get_distance(b.end);
	
	decimal_n shortest = std::numeric_limits<decimal_n>::infinity();
	for(auto o: {start_start, start_end, end_start, end_end}){
		shortest = (shortest < o)? shortest: o;
		}
	ret = (ret < shortest)? ret: shortest;
	
	return ret;
	}



decimal_n step::get_distance_circulars(step a, step b, bool carry_caps){
	if(a._type != b._type | !(a._type & b._type)){
		// that's just fucked, this is the circulars section
		std::cerr << "You garbage tried to put in there some linear steps\nPROOF:\t" << a.print_geogebra() 
			<< "\t" << b.print_geogebra() << std::endl;
		// that's just fucked, this is the combined section
		if((a._type == line_e) && (b._type == line_e)){
			return step::get_distance_linears(a, b, carry_caps);
			} else {
				return step::get_distance_combined(a, b, carry_caps);
				}
		return 666;
		}
	if(step::intersection(a, b).size() != 0){
		return 0;
	}
	decimal_n ret = std::numeric_limits<decimal_n>::infinity();
	circle a_formula = std::get<circle>(a.formula);
	circle b_formula = std::get<circle>(b.formula);
	
	// make line from each center to each start/end/center (estimated count: 5)
	line start_center	(a.start, b_formula.center);
	line end_center		(a.end, b_formula.center);
	line center_center	(a_formula.center, b_formula.center);
	line center_start	(a_formula.center, b.start);
	line center_end		(a_formula.center, b.end);
	
	std::vector<coordinates> int_start_center 	= step::intersection(b, start_center);
	std::vector<coordinates> int_end_center	 	= step::intersection(b, end_center);
	/// TODO: Horrendous glitch that considers ANY point on center_center line on the segment
	std::vector<coordinates> int_center_center_b= step::intersection(b, center_center); ///THIS ONE DOES THAT
	std::vector<coordinates> int_center_center_a= step::intersection(a, center_center);
	std::vector<coordinates> int_center_start	= step::intersection(a, center_start);
	std::vector<coordinates> int_center_end		= step::intersection(a, center_end);
	
	std::array<std::vector<coordinates>, 4> it_1 = {int_start_center, int_end_center, 
													int_center_start, int_center_end};
	std::array<coordinates, 4> it_2 = {a.start, a.end, b.start, b.end};
	for(uint8_t i = 0; i < 4; i++){
		for(auto o: it_1[i]){
			//~ std::cout << o.print_geogebra() << std::endl;
			decimal_n retc = o.get_distance(it_2[i]);
			ret = (ret < retc)? ret: retc;
			}
		}
	for(uint8_t i = 0; i < int_center_center_b.size(); i++){
		//~ if(b.on_segment(int_center_center_b[i])){
			//~ std::cout << int_center_center_b[i].print_geogebra() << std::endl;
			for(uint8_t o = 0; o < int_center_center_a.size(); o++){
				//~ if(a.on_segment(int_center_center_a[o])){
					//~ std::cout << int_center_center_a[o].print_geogebra() << std::endl;
					//~ std::cout << "Tam" << std::endl;
					decimal_n retc = int_center_center_b[i].get_distance(int_center_center_a[o]);
					ret = (ret < retc)? ret: retc;
					//~ }
				}
			//~ }
		}
		
	if(carry_caps){
		// get distances between starts and ends
		decimal_n start_start = a.start.get_distance(b.start);
		decimal_n start_end	  = a.start.get_distance(b.end);
		decimal_n end_start	  = a.end.get_distance(b.start);
		decimal_n end_end	  = a.end.get_distance(b.end);
		decimal_n shortest = std::numeric_limits<decimal_n>::infinity();
			for(auto o: {start_start, start_end, end_start, end_end}){
				shortest = (shortest < o)? shortest: o;
				}
		ret = (ret < shortest)? ret: shortest;	
		}
	return ret;
	}



decimal_n step::get_distance_combined(step a, step b, bool carry_caps){
	if(a._type == b._type){
		std::cerr << "You garbage tried to put in two same steps\nPROOF:\t" << a.print_geogebra() 
			<< "\t" << b.print_geogebra() << std::endl;
		// that's just fucked, this is the combined section
		if((a._type == circle_e) && (b._type == circle_e)){
			return step::get_distance_circulars(a, b, carry_caps);
			} else {
				return step::get_distance_linears(a, b, carry_caps);
				}
		/// TODO: exception to match the needs
		return 666;
		}
		
	if(step::intersection(a, b).size() != 0){
		return 0;
	}
	
	decimal_n ret = std::numeric_limits<decimal_n>::infinity();
	step linear 	= (a._type == line_e)?	a: b;
	step circular 	= (a._type != line_e)?	a: b;
	
	line n_line		= std::get<line>(linear.formula);
	circle n_circ	= std::get<circle>(circular.formula);
	
	line perp_center 	= n_line.make_perpendicular(n_circ.center);
	line perp_start 	= n_line.make_perpendicular(circular.start);
	line perp_end 		= n_line.make_perpendicular(circular.end);
	
	coordinates e_center= line::intersection(perp_center, n_line);
	coordinates e_start = line::intersection(perp_start, n_line);
	coordinates e_end 	= line::intersection(perp_end, n_line);
	
	std::vector<coordinates> int_center = step::intersection(circular, perp_center);
	std::vector<coordinates> int_start 	= step::intersection(circular, perp_start);
	std::vector<coordinates> int_end 	= step::intersection(circular, perp_end);
	
	//~ for(auto a: {int_center, int_start, int_end})
		//~ for(auto b: a)
			//~ std::cout << b.print() << std::endl;
	//~ std::cout << e_center.print() << std::endl;
	//~ std::cout << e_start.print() << std::endl;
	//~ std::cout << e_end.print() << std::endl;
	
	//~ std::cout << perp_center.print() << std::endl;
	//~ std::cout << perp_start.print() << std::endl;
	//~ std::cout << perp_end.print() << std::endl;
	
	//~ std::cout << .print_geogebra() << std::endl;
	
	
	if(linear.on_segment(e_center)){
		for(auto i: int_center){
			// they already are on circular segment, so no worries I suppose
			decimal_n retc = i.get_distance(e_center); // return candidate
			//~ std::cout << i.print_geogebra() << std::endl;
			ret = (ret < retc)? ret: retc;
			}
		}
		
	if(linear.on_segment(e_start)){
		decimal_n retc = circular.start.get_distance(e_start); // return candidate
		ret = (ret < retc)? ret: retc;
		for(auto i: int_start){
			// they already are on circular segment, so no worries I suppose
			retc = i.get_distance(e_start); // return candidate
			//~ std::cout << i.print_geogebra() << std::endl;
			ret = (ret < retc)? ret: retc;
			}
			
		}
		
	if(linear.on_segment(e_end)){
		decimal_n retc = circular.end.get_distance(e_end); // return candidate
		ret = (ret < retc)? ret: retc;
		for(auto i: int_end){
			// they already are on circular segment, so no worries I suppose
			//~ std::cout << i.print_geogebra() << std::endl;
			decimal_n retc = i.get_distance(e_end); // return candidate
			ret = (ret < retc)? ret: retc;
			}
		}
	
	if(carry_caps){ 
		// cares about every other possibilities
		line start_center_variant 	= line(linear.start, n_circ.center);
		line end_center_variant 	= line(linear.end, n_circ.center);
		
		line start_start_variant 	= line(linear.start, circular.start);
		line end_start_variant 		= line(linear.end, circular.start);
		line start_end_variant 		= line(linear.start, circular.end);
		line end_end_variant 		= line(linear.end, circular.end);
		
		// all the possible variants of intersection of circular segment with the lines above
		std::vector<coordinates> start_center_intersections = circular.intersection(start_center_variant);
		std::vector<coordinates> end_center_intersections 	= circular.intersection(end_center_variant);
		
		std::vector<coordinates> start_start_intersections 	= circular.intersection(start_start_variant);
		std::vector<coordinates> end_start_intersections 	= circular.intersection(end_start_variant);
		std::vector<coordinates> start_end_intersections 	= circular.intersection(start_end_variant);
		std::vector<coordinates> end_end_intersections 		= circular.intersection(end_end_variant);
		std::array<std::vector<coordinates>, 6> it_1 = {start_center_intersections, end_center_intersections, start_start_intersections, 
					end_start_intersections, start_end_intersections, end_end_intersections};
		std::array<coordinates, 2> it_2 = {linear.start, linear.end};
		for(uint8_t i = 0; i < 6; i++){
			for(auto o: it_1[i]){
				//~ std::cout << o.print_geogebra() << std::endl;
				decimal_n retc = o.get_distance(it_2[i%2]);
				ret = (ret < retc)? ret: retc;
				}
			}
		
		decimal_n start_start = linear.start.get_distance(circular.start);
		decimal_n start_end = linear.start.get_distance(circular.end);
		decimal_n end_start = linear.end.get_distance(circular.start);
		decimal_n end_end = linear.end.get_distance(circular.end);
		
		decimal_n shortest = std::numeric_limits<decimal_n>::infinity();
		for(auto o: {start_start, start_end, end_start, end_end}){
			shortest = (shortest < o)? shortest: o;
			}
		ret = (ret < shortest)? ret: shortest;
		}
		
	return ret;
	}


decimal_n step::get_distance(coordinates c, bool carry_caps){
	return step::get_distance(*this, c, carry_caps);
	}
	
	
decimal_n step::get_distance(line l, bool carry_caps){
	return step::get_distance(*this, l, carry_caps);
	}
	
decimal_n step::get_distance(circle c){
	return step::get_distance(*this, c);
	}
	
decimal_n step::get_distance(step b, bool carry_caps){
	return step::get_distance(*this, b, carry_caps);
	}
	
decimal_n step::get_distance(step s, candle c){
	// just a redirection to step::get_distance(step, circle)
	return step::get_distance(s, c.tube);
	}

decimal_n step::get_distance(step s, wall w){
	// converts a wall into independent steps
	decimal_n ret = std::numeric_limits<decimal_n>::infinity();
	for(uint8_t i = 0; i < 4; i++){
		decimal_n retc = s.get_distance(s, step(w.properties.edges[i], w.properties.edges[(i + 1) % 4], false));
		ret = (ret < retc)? ret: retc;
		}
	return ret;
	}

std::vector<decimal_n> step::get_distances(step s, std::vector<coordinates> points){
	std::vector<decimal_n> ret;
	for(auto o: points){
		ret.push_back(step::get_distance(s, o));
		}
	return ret;
	}

std::vector<decimal_n> step::get_distances(step s, wall w){
	std::vector<decimal_n> ret;
	for(uint8_t i = 0; i < 4; i++){
		ret.push_back(step::get_distance(s, w.properties.edges[i]));
		}
	return ret;
	}

std::vector<decimal_n> step::get_distances(std::vector<coordinates> points){
	return get_distances(*this, points);
	}

std::vector<decimal_n> step::get_distances(wall w){
	return get_distances(*this, w);
	}
