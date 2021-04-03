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
	std::vector<circle> circles; /// On every selected point derivate except end there must be a turn
	std::vector<decimal_n> angles; /// Selected angles that local coordinates systems will start with
	std::vector<coordinates> selected_derivate = selected;
	std::vector<std::pair<step*, decimal_n>> crosses; /// cross that'll be constructed on selected point
	std::vector<std::pair<step, step>> paralels; /// paralels to check how close we are to an obstacle
	//~ if( selected)
	for(unsigned_b i = 1; i < selected.size(); i++){
		 steps.push_back(step(selected[i-1], selected[i]));
		 /// steps that do connect these points, these are definitely lines
		}
	
	
	crosses.push_back(std::make_pair(&steps[0], initial_rotation));
	line cross;
	for(unsigned_b i = 0; i < steps.size()-1; i++){ 
		/// fills all the local angles according to the straight lines between selected
		cross = line::make_axis(std::get<line>(steps[i].formula), std::get<line>(steps[i+1].formula));
		crosses.push_back(std::make_pair(&steps[i+1], suiting_angle({cross, cross.make_perpendicular(steps[i].start)},\
																	&steps[i+1].end, &steps[i].start, &steps[i].end)));
		}
	
	for(std::pair<step*, decimal_n>& pair: crosses){
		/// alters location of every coordinates that are close to an obstacle
		}
		
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
		/// cross is turned by -pi/4, making it more valuable to use y axis to compare
		ret = (l_next.y <= 0 ^ l_previous.y <= 0) ? (ret) : (angle);
		/// literally first time I've ever used xor
		}
		
	return ret;
	}


decimal_n planner::evaluate_radius(coordinates previous, coordinates current){
	decimal_n d = previous.get_distance(current);
	/// this gives us circle radius that is allowed for such distance
	if((d - limits::minimal::circle) <= -1e-5){
		return 0; /// a rotation on place must be held
		}
		
	if((d - limits::maximal::circle) > 0){
		return limits::maximal::circle; /// a maximum is only possible
		}
	return d;
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
	if(distance > limits::maximal::circle){ 
		/// distance is bigger than the radius of maximal circle, thus making it inefficient to drive on circular path.
		/// radius is given by halving the one that's on the correct side of coordinates
		wall closest_w = m.closest_wall(start);
		//~ if()
		/// checks if the trace doesn't collide with any object within range 
		/// checks if the trace doesn't collide with any object
		}
		
	if(distance < limits::maximal::circle){ 
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

bool planner::collides_nowhere(map &m, coordinates start, coordinates end){
	line lin(start, end);
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
