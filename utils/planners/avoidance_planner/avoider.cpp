/*
 * avoider.cpp
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


#include "avoider.hpp"


avoider::avoider(){
	
	}




std::vector<step> avoider::avoid(std::vector<step> steps, wall w){
	assert(steps.size() >= 4);
	assert((steps.at(0)._type == steps.at(2)._type) && (steps.at(2)._type == step::line_e)); 
	assert((steps.at(1)._type == steps.at(3)._type) && (steps.at(1)._type == step::circle_e)); 
	/* 1 linear path to which it should move 
	 * 1 circular path to which it should continue
	 * 1 linear path that needs to be changed
	 * 1 circular path from which it should continue
	 *  */
	std::vector<vector> vectors_a = steps.at(2).get_point_vectors(w);
	//~ std::vector<vector> * vectors_b = new std::vector<vector>(steps.at(2).get_vectors(w));
	//~ vectors_a.insert(vectors_a.end(), vectors_b -> begin(), vectors_b -> end());
	//~ delete vectors_b;
	//~ vectors_a.insert(vectors_a.end(), steps.at(2).get_vectors(w));
	
	for(std::vector<vector>::iterator a = vectors_a.begin(); a != vectors_a.end(); a++){
		if(a -> length() > (robot_radius * safe_constant)){
			vectors_a.erase(a--);
			} /* else {
				*a = a -> extend(robot_radius * 2 * safe_constant);
				} */
		}
	
	std::vector<circle> middle_circles;
	middle_circles.push_back(std::get<circle>(steps.at(1).formula));
	
	for(auto &a: vectors_a){
		middle_circles.emplace_back(a.get_origin(), robot_radius * std::pow(safe_constant, 1 + robot_radius * safe_constant - a.length()));
		std::cout << middle_circles.back().print() << std::endl;
		//~ std::cout << a.length() << " < " << (robot_radius * safe_constant) << std::endl;
		}
	std::sort(middle_circles.begin() + 1, middle_circles.end(), 
				[middle_circles](circle a, circle b){return (a.center.get_distance(middle_circles.front().center) < b.center.get_distance(middle_circles.front().center));});
	for(unsigned_n i = 1; i < middle_circles.size(); i++){
		auto tangents = to_steps(circle::circle_tangents(middle_circles.at(i - 1), middle_circles.at(i)), middle_circles.at(i - 1), middle_circles.at(i));
		eliminate_tangents(tangents, std::vector<circle>({middle_circles.at(i - 1), middle_circles.at(i)}), 
							std::vector<coordinates>({middle_circles.at(i - 1).center, middle_circles.at(i).center, steps.at(0).end}), 
							steps.at(1).angle_end);
		for(auto stp: tangents)
			std::cout << stp.print_geogebra() << std::endl;
		}
	std::cout << vectors_a.size() << std::endl;
	
	//~ std::vector<vector> vectors_b = steps.at(1).get_vector(w);
	return std::vector<step> ();
	}



path avoider::avoid(path p, std::vector<wall> w){
	assert(p.size() <= 4);
	path ret = p;
	//~ std::vector<vector> vectors_b = steps.at(1).get_vector(w);
	return std::vector<step> ();
	}




void avoider::eliminate_tangents(std::vector<step>& steps, std::vector<circle> circles, std::vector<coordinates> selected, decimal_n escape_angle){
	assert(circles.size() == 2); // only two there are - first and second
	
	circle first_circle = circles.at(1);
	circle second_circle = circles.at(0);
	bool direction = std::sin(vector(selected.at(0), selected.at(1)).angle() - vector(selected.at(1), selected.at(2)).angle()) > 0;
	coordinates center_local(0, (direction * 2 - 1));
	for(auto b = steps.begin(); b != steps.end(); b++) {
			// in_first: bod prvni kruznice, ktera se musi projet
			coordinates in_first = b -> start;
			// in_next: bod kruznice, na kterou se musi najet z prvni
			coordinates in_next = b -> end;
			// vector_angle: uhel tecny na kterou se musi najet
			decimal_n vector_angle = in_first.get_gamma(in_next);
			// tangent_angle: uhel bodu in_first vuci stredu kruznice, na ktere lezi
			decimal_n tangent_angle = first_circle.center.get_gamma(in_first);
			// difference_angle: rozdil uhlu tecny a uhlu vuci bodu dotyku
			decimal_n difference_angle = vector_angle - (tangent_angle + ((center_local.y < 0)?-0.5:0.5) * pi_const);
			std::cout << std::sin(vector(selected.at(0), selected.at(1)).angle() - vector(selected.at(1), selected.at(2)).angle()) << std::endl;
			if((std::abs(difference_angle) <= 1e-3 || (std::abs(difference_angle + ((center_local.y < 0)?-2:2) * pi_const) <= 1e-3))){
				decimal_n next_angle = selected.at(0).get_gamma(selected.at(1));
				//~ std::cout << selected.at(1).make_local(b.intersection(std::get<line>(pre_steps.at(1).formula)), -next_angle).print() << std::endl;
				//~ std::cout << step(selected.at(0), selected.at(1)).print_geogebra() << std::endl;
				if(selected.at(0).make_local(std::get<line>(b -> formula).intersection(std::get<line>(step(selected.at(0), selected.at(1)).formula)), -next_angle).x < 0){
					
					std::cout << "eliminace" << std::endl;
					steps.erase(b--);
					//~ std::cout << steps.at(0).print_geogebra() << std::endl;
					//~ break;
					} else {
						std::cout << "neeliminace 1. rad\t" << first_circle.center.print() << "\t" << in_first.print() << std::endl;
						}
				} else {
					std::cout << "neeliminace 2. rad\t" << first_circle.center.print() << "\t" << in_first.print() << std::endl;
					}
			}
	
	
	//~ return std::vector<step> ();
	}




void avoider::eliminate_tangents(std::vector<step>& steps, std::vector<step> circular_steps){
	assert(circular_steps.size() == 2); // only two there are - first and second
	assert(circular_steps.at(0)._type == step::circle_e && circular_steps.at(1)._type == step::circle_e);
	
	circle first_circle = std::get<circle>(circular_steps.at(0).formula);
	circle second_circle = std::get<circle>(circular_steps.at(1).formula);
	
	std::vector<coordinates> selected({});
	std::vector<line> tangents = circle::circle_tangents(first_circle, second_circle);
	
	for(line &b: tangents) {
			//~ coordinates first = b.intersection(b.make_perpendicular(c.center));
			//~ coordinates second = b.intersection(b.make_perpendicular(a.center));
			// in_first: bod prvni kruznice, ktera se musi projet
			coordinates in_first = b.intersection(b.make_perpendicular(first_circle.center));
			// in_next: bod kruznice, na kterou se musi najet z prvni
			coordinates in_next = b.intersection(b.make_perpendicular(second_circle.center));
			// vector_angle: uhel tecny na kterou se musi najet
			decimal_n vector_angle = in_first.get_gamma(in_next);
			// tangent_angle: uhel bodu in_first vuci stredu kruznice, na ktere lezi
			decimal_n tangent_angle = first_circle.center.get_gamma(in_first);
			// difference_angle: rozdil uhlu tecny a uhlu vuci bodu dotyku
			decimal_n difference_angle = vector_angle - (tangent_angle + ((circular_steps.at(1).direction_curve)?-0.5:0.5) * pi_const);
			if((std::abs(difference_angle) <= 1e-3 || (std::abs(difference_angle + ((circular_steps.at(1).direction_curve)?-2:2) * pi_const) <= 1e-3))){
				//~ decimal_n next_angle = selected.at(1).get_gamma(selected.at(2));
				decimal_n next_angle = circular_steps.at(1).angle_end;
				//~ std::cout << selected.at(1).make_local(b.intersection(std::get<line>(pre_steps.at(1).formula)), -next_angle).print() << std::endl;
				//~ if(selected.at(0).make_local(b.intersection(std::get<line>(step(selected.at(0), selected.at(1)).formula)), -next_angle).x < 0){
				if(first_circle.center.make_local(b.intersection(std::get<line>(step(first_circle.center, second_circle.center).formula)), -next_angle).x < 0){
					//~ pre_steps.push_back(step(start, in_first, first_circle.center, is_right));
					//~ pre_steps.push_back(step(in_first, in_next));
					std::cout << vector(in_first, in_next).print() << std::endl;
					//~ std::cout << pre_steps.at(0).print_geogebra() << std::endl;
					//~ std::cout << pre_steps.at(1).print_geogebra() << std::endl;
					break;
					}
				}
			}
	
	
	//~ return std::vector<step> ();
	}



std::vector<step> avoider::to_steps(std::vector<line> tangents, circle future, circle current){
	std::vector<step> ret;
	for(auto o: tangents)
		ret.emplace_back(o.intersection(o.make_perpendicular(current.center)), o.intersection(o.make_perpendicular(future.center)));
	return ret;
	}

