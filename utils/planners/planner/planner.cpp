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
	std::vector<circle> circles; /// TODO: Description
	
	line l(initial_rotation, selected[0]);
	std::vector<std::pair<step*, std::array<line, 2>>> crosses; /// cross that'll be constructed on Dijkstra point
	//~ if( selected)
	for(unsigned_b i = 1; i < selected.size(); i++){
		 steps.push_back(step(selected[i-1], selected[i]));
		 /// steps that do connect these points, these are definitely lines
		}
		
	line cross(initial_rotation, steps[0].start);
	crosses.push_back(std::make_pair(&steps[0], std::array<line, 2>({line(initial_rotation, steps[0].start), cross.make_perpendicular(steps[0].start)})));
	for(unsigned_b i = 0; i < steps.size()-1; i++){
		cross = line().make_axis(std::get<line>(steps[i].formula), std::get<line>(steps[i+1].formula));
		
		crosses.push_back(std::make_pair(&steps[i+1], std::array<line, 2>({cross, cross.make_perpendicular(steps[i].start)})));
		//~ steps[i]
		//~ std::cout << 
		}
	return steps;
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
