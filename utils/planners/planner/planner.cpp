/*
 * planner.cpp
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


#include "dijkstra.cpp"
#include "travel_node.cpp"
#include "movement_utils.cpp"
#include "planner.hpp"



planner::planner()
{
	
}

circle planner::create_perimeter(coordinates c, decimal_n radius){
	//~ std::cout << c.print() << std::endl;
	return circle(c, radius);
	}

/**
 * 
 * name: planner::plan_make
 * planner::plan_make takes in the road 
 * designed by planner::make_path and creates 
 * a path that does have lines and turns.
 * 
 * Main idea behind it is that all the points noted are 
 * actually 
 * 
 * @param selected: coordinates that create the possible path
 * @param m: current map object
 * @param initial_rotation: rotation robot is currently headed
 * @return
 * 
 */


std::vector<step> planner::plan_make(std::vector<coordinates> selected, map &m, decimal_n initial_rotation){
	// There must be at least two points - start and end
	std::vector<step> steps; /// steps based on coordinates selected by Dijkstra
	std::vector<std::vector<step>> pre_steps; /// steps based on coordinates selected by Dijkstra
	std::vector<circle> pre_circles; /// circles based on coordinates selected by Dijkstra
	std::vector<std::vector<line>> pre_lines; /// lines tangent to any of pre_circles
	/// TODO: First move!
	for(unsigned_b i = 1; i < selected.size()-1; i++){
		if(i >= selected.size())
			break;
		pre_circles.push_back(circle(selected.at(i), evaluate_radius(selected.at(i-1), selected.at(i))));
		std::cout << pre_circles.back().print() << std::endl;
		}
	coordinates start = selected.at(0);
	/// first circle generation block start
	decimal_n radius_initial = evaluate_radius(selected.at(1), start);
	coordinates next_local = selected.at(1).make_local(start, -pi_const/2 - initial_rotation);
	bool is_right = (next_local.y < 0);
	bool is_behind = (next_local.x < 0);
	
	coordinates center_local(0, ((is_right)? -1: 1) * radius_initial);
	circle first_circle(start.make_global(center_local, initial_rotation - pi_const/2), radius_initial);
	coordinates center_next_local = pre_circles.back().center.make_local(first_circle.center, -pi_const/2 - initial_rotation);
	/// first circle generation block end
	pre_circles.insert(pre_circles.begin(), first_circle);
	std::cout << first_circle.print() << std::endl;
	for(unsigned_b i = 0; i < pre_circles.size() - 1; i++){
		std::cout << std::to_string(i) << std::endl;
		std::vector<line> temp_lines = circle::circle_tangents(pre_circles.at(i+1), pre_circles.at(i));
		pre_steps.push_back(std::vector<step>());
		for(line l: temp_lines){
			step t_step(pre_circles.at(i).intersection(l)[0], pre_circles.at(i+1).intersection(l)[0]);
			decimal_n step_distance = get_distance_to_walls(t_step, m);
			if(step_distance > (robot_radius * 0.5)){
				pre_steps.back().push_back(t_step);
				}
			}
		}
	std::cout << "Bordel se deje" << std::endl;
	std::vector<coordinates> temp_points = circle::tangent_points(pre_circles.back(), selected.back());
	pre_steps.push_back(std::vector<step>());
	for(coordinates l: temp_points){
		std::cout << l.print() << std::endl;
		step t_step(l, selected.back());
		decimal_n step_distance = get_distance_to_walls(t_step, m);
		if(step_distance > (robot_radius * 0.5)){
			pre_steps.back().push_back(t_step);
			}
		}
	for(auto vs: pre_steps){
		for(auto s: vs)
			std::cout << s.print_geogebra() << std::endl;
		}
	//~ std::cout << next_local.print() << std::endl;
	//~ std::cout << first_circle.print() << std::endl;
	
	/// TODO: THIS SECTION
	
	std::cout << std::endl;
		
	
	return steps;
	}

/**
 * 
 * name: planner::suiting_angle
 * @param cross: those two ange options that are possible to choose
 * @param p_previous: 
 * @param p_next: next coordinates
 * @param p_current: current coordinates, optional
 * @return out of two lines it selects the angle that has previous and next point on the same side
 * 
 */

decimal_n planner::suiting_angle(std::array<line, 2> cross, coordinates *p_next, coordinates *p_previous, coordinates *p_current){
	decimal_n ret = std::numeric_limits<decimal_n>::infinity();
	coordinates local = (p_current != nullptr)? (*p_current) : (cross[0].intersection(cross[1]));
	/// It's literally a cross, tell me one case when it won't have any intersection
	
	for(line l: cross){
		decimal_n angle = l.get_angle();
		coordinates l_next = local.make_local(*p_next, angle);
		coordinates l_previous = (p_previous != nullptr) ? (coordinates(-l_next.x, l_next.y)) : (local.make_local(*p_previous, angle));
		/// cross is turned by -pi/2, making it more valuable to use y axis to compare
		ret = (l_next.y <= 0 ^ l_previous.y <= 0) ? (ret) : (angle);
		/// literally first time I've ever used xor
		}
		
	return ret;
	}


void planner::alter_selected(std::vector<step>& selected, map& m, decimal_n initial_rotation){
	std::vector<bool> safe_distance(selected.size(), false);
	
	decimal_n first = evaluate_radius(selected[0].start, selected[0].end);
	decimal_n safe = 0.6;
	std::pair<step, step> perimeters = step::get_perimeters(selected[0], variables::properties::widths::robot * safe);
	coordinates local_next = selected[0].start.make_local(selected[0].end, initial_rotation);
	if(std::abs(local_next.y) >= 1e-1 && local_next.x > 0){
		coordinates local_center(0, (local_next.y > 0)?-1 : 1 * first);
		circle turn(selected[0].start.make_global(local_center, initial_rotation), first); /// TODO: WARNING, might be incorrect
		//~ while(!(collides_nowhere(m, std::get<0>(perimeters).start, std::get<0>(perimeters).end, /** TODO */) & \
	      //~ collides_nowhere(m, std::get<1>(perimeters).start, std::get<1>(perimeters).end, /** TODO */)){
			  //~ /// both of them must be true to proceed
			  //~ }
	}
	
	/// gives us a bitmap of which segments are not close
	for(unsigned_b i = 0; i < selected.size(); i++){ 
		perimeters = step::get_perimeters(selected[i], variables::properties::widths::robot * 0.65);
		/// 0.65 is given because it is demanded to have 1.3 of a width in total
		safe_distance[i] = (collides_nowhere(m, std::get<0>(perimeters).start, std::get<0>(perimeters).end) & \
							collides_nowhere(m, std::get<1>(perimeters).start, std::get<1>(perimeters).end));
		}
	/// 
	}


decimal_n planner::evaluate_radius(coordinates previous, coordinates current){
	decimal_n d = previous.get_distance(current);
	/// this gives us circle radius that is allowed for such distance
	if((d - 2*variables::limits::minimal::circle) <= -1e-5){
		return 0; /// a rotation on place must be held
		}
		
	if((d - variables::limits::maximal::circle) > 0){
		return variables::limits::maximal::circle; /// a maximum is only possible
		}
	return d/2;
	}

std::vector<step> planner::make_first_move(map& m, coordinates start, coordinates next, decimal_n initial_rotation, speeds v){
	std::vector<step> ret;
	coordinates next_local = start.make_local(next, initial_rotation);
	decimal_n distance = start.get_distance(next);
	next_local.x = 0;
	if(std::abs(next_local.y) <= 1e-1 && next_local.x > 0){ /// means next is right in front of us -> don't create any circle
		ret.push_back(step(start, next));
		return ret;
	}
	
	if(std::abs(next_local.y) <= 1e-1 && next_local.x < 0){ /// means next is right behind us -> this has specific conditions
		/// in case there are more interesting points on the right and is it possible to look there, no obstacles on the left turn slowly left, 
		/// if that's on the other side... You got the point
		std::array<std::vector<location *>, 4> interestings = m.subdivide(start, initial_rotation);	
	}
	if(distance > variables::limits::maximal::circle){ 
		/// distance is bigger than the radius of maximal circle, thus making it inefficient to drive on circular path.
		/// radius is given by halving the one that's on the correct side of coordinates
		wall closest_w = m.closest_wall(start);
		//~ if()
		/// checks if the trace doesn't collide with any object within range 
		/// checks if the trace doesn't collide with any object
		}
		
	if(distance < variables::limits::maximal::circle){ 
		/// distance is bigger than the radius of maximal circle, thus making it inefficient to drive on circular path.
		}
	return ret;
	}

bool planner::collides(wall w, coordinates start, coordinates end){
	line lin(start, end);
	for(auto l: w.properties.walls){
		coordinates inters = lin.intersection(l, lin);
		if((lin.on_segment(inters, start, end) && w.inside(inters)) || w.inside(start) || w.inside(end)){
			return true;
		}
	}
	return false;
}

bool planner::collides(wall w, coordinates start, coordinates end, circle c, bool side){
	std::vector<coordinates> collidors;
	for(auto l: w.properties.walls){
		auto n = c.intersection(l);
		collidors.insert(collidors.end(), n.begin(), n.end());
		}
	for(auto co: collidors){
		if(c.on_segment(start, end, co, side)){
			return true;
			}
		}
	return false;
}

bool planner::collides_nowhere(map &m, coordinates start, coordinates end, circle c, bool side){
	for(auto w: m._map_walls){
		if(collides(w, start, end, c, side))
			return false;
		}
	return true;
}

bool planner::collides_nowhere(map &m, coordinates start, coordinates end){
	for(auto w: m._map_walls){
		if(collides(w, start, end))
			return false;
		}
	return true;
}	

std::vector<circle> planner::circle_generate(coordinates goal, coordinates start, map &m, uint8_t it, decimal_n multiplier){
	std::vector<circle> out;
	out.push_back(circle(start, start.get_distance(goal)));
	decimal_n goal_start_distance = goal.get_distance(start);
	for(wall w: m._map_walls) /// generation of circles between the walls and goal
		for(coordinates c: w.properties.edges)
			out.push_back(circle(c, c.get_distance(goal)));
			
	for(wall w: m._map_walls) /// generation of circles between the walls and start
		for(coordinates c: w.properties.edges)
			if(c.get_distance(goal) < goal_start_distance)
				out.push_back(circle(c, c.get_distance(start)));
			
			
	for(wall w: m._map_walls) /// generation of perimeter circles between of the wall edges
		for(coordinates c: w.properties.edges)
			out.push_back(create_perimeter(c));
	
	
	
	for(uint8_t i = 1; i < it; i++){ /// generation of circles between start and end
		out.push_back(circle(start, (goal_start_distance * multiplier * (decimal_n)i) /  (decimal_n)it));
		out.push_back(circle(goal, (goal_start_distance * multiplier * (decimal_n)i) /  (decimal_n)it));
		}
	
	return out;	
}

std::vector<circle> planner::perimeter_generate(map &m){
	std::vector<circle> out;
	
	for(wall w: m._map_walls)
		for(coordinates c: w.properties.edges)
			out.push_back(create_perimeter(c));
	return out;	
}

std::vector<coordinates> planner::coincidental_points_generate(std::vector<circle>& circles){
	std::vector<coordinates> out;
	for(std::vector<circle>::iterator a = circles.begin(); a != circles.end(); ++a){
		for(std::vector<circle>::iterator b = a; b != circles.end(); ++b){
			if(*a != *b){
				std::vector<coordinates> n = b -> intersection(*a, *b);
				out.insert(out.end(), n.begin(), n.end());
				
				}
					
			}
		}
		
	for(std::vector<coordinates>::iterator a = out.begin(); a != out.end(); ++a){
		for(std::vector<coordinates>::iterator b = a; b != out.end(); ++b){
			if(a != b){
				if(*a == *b){
					out.erase(b);
					--b;
					}				
				}
					
			}
		}
	return out;	
	}

	
std::vector<step> planner::plan_calculate(std::vector<step> in){
	std::vector<step> out = in;
	
	return out;
	}
	

std::vector<travel_node> planner::expand(std::vector<travel_node> nodes, std::vector<travel_node> prev_nodes,  unsigned_b id_curr){
	std::vector<travel_node> curr_nodes;
	travel_node i = search_by_id(id_curr, nodes);
	for(auto o: i.connected){
		bool inside = false;
		for(auto u: prev_nodes){
			if(o.second -> id == u.id){
				inside = true;
				}
			if(!inside){
				curr_nodes.push_back(*o.second);
				}
			}
		}
			
	return curr_nodes;	
	}


travel_node planner::search_by_id(unsigned_b id, std::vector<travel_node> &nodes){
	for(auto i: nodes){
		if(i.id == id)
			return i;
		}
	return travel_node(-1, coordinates());
	}


std::vector<coordinates> planner::make_path(std::vector<coordinates> &c, coordinates start, coordinates end, map &m){
	std::vector<coordinates> temp = c;
	std::vector<coordinates> out;
	for(unsigned_b i = 0; i < temp.size(); i++){
		for(auto b: m._map_walls){
			if(b.inside(temp[i])){
				temp.erase(temp.begin() + i--);				
				}
		}
	}
	dijkstra d(m);
	//~ temp.push_back(start);
	d.nodes = d.generate_nodes(temp, start);
	d.p_nodes = d.generate_node_pointers(d.nodes);

	d.edges = d.generate_edges(d.nodes, m);
	d.p_edges = d.generate_edge_pointers(d.edges);
	
	std::vector<dijk_node> nodes = d.dijkstras(d.p_nodes, d.p_edges);
	std::cout << nodes.size() << std::endl;

	std::cout << std::endl << d.nodes.size() << std::endl;
	for(auto &o: nodes){
		if(*o.coords == end){
			out = d.print_shortest_route(&o);
			break;
		}
	}
	
	out.push_back(start);
	std::reverse(out.begin(), out.end());
	for(auto o: out){
		std::cout << o.print() << std::endl;
		}
	return out;
	}

decimal_n planner::get_distance_to_walls(step s, map &m){
	decimal_n ret = std::numeric_limits<decimal_n>::infinity();
	for(auto w: m._map_walls){
		decimal_n retc = step::get_distance(s, w);
		ret = (ret < retc)? ret: retc;
		}
	return ret;
	}
