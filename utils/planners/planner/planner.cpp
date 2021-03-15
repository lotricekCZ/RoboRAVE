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
#include "planner.hpp"



planner::planner()
{
	
}

circle planner::create_perimeter(coordinates c){
	std::cout << c.print() << std::endl;
	return circle(c, robot_radius*2.0);
	}

std::vector<coordinates> planner::plan_make(coordinates goal, coordinates start, map &m){
	std::cout << "start: " << start.print() << "  goal: " << goal.print() << std::endl;
	std::vector<coordinates> out;
	std::vector<circle> circles;
	if(start == goal) return out;
	out.push_back(start);
	angles local_sight = angles().load_virtual(start, m);
	
	decimal_n distance = start.get_distance(goal);
	circle range(start, distance);
	circles.push_back(range);
	
	for(auto w: m._map_walls){
		for(auto poi: w.properties.edges){
			if(range.inside(poi) && (poi.get_distance(start) < distance)){
				std::cout << circle(poi, poi.get_distance(goal)).print() << std::endl;
				circles.push_back(circle(poi, poi.get_distance(goal)));
				}
			}
		}
	
	for(uint32_t i = 0; i < circles.size(); i++){
		for(uint32_t e = 0; i < circles.size(); i++){
			if(!(circles[e] == circles[i])){
				std::vector<coordinates> tangs = circle().intersection(circles[e], circles[i]);
				out.insert(out.end(), tangs.begin(), tangs.end());
				}
			}
		}
	
	std::sort(out.begin(), out.end(), [](coordinates a, coordinates b){return (a.x < b.x) || (a.y < b.y);});
	out.erase( unique( out.begin(), out.end() ), out.end() );
	
	
	return out;
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


std::vector<step> planner::make_path(std::vector<coordinates> &c, coordinates start, coordinates end, map &m){
	std::vector<coordinates> temp = c;
	for(unsigned_b i = 0; i < temp.size(); i++){
		for(auto b: m._map_walls){
			if(b.inside(temp[i])){
				temp.erase(temp.begin() + i--);				
				}
		}
	}
	dijkstra d(m);
	d.nodes = d.generate_nodes(temp, start);
	d.p_nodes = d.generate_node_pointers(d.nodes);

	d.edges = d.generate_edges(d.nodes, m);
	d.p_edges = d.generate_edge_pointers(d.edges);
	
	std::vector<dijk_node> nodes = d.dijkstras(d.p_nodes, d.p_edges);
	std::cout << nodes.size() << std::endl;

	std::cout << std::endl << d.nodes.size() << std::endl;
	for(auto &o: nodes)
		if(*o.coords == end){
			d.print_shortest_route(&o);
			break;
			}
	
	return std::vector<step>();
	}
