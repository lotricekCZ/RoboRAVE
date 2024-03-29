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


#include "planner.hpp"
#include <chrono>
#include <thread>
#include <memory>

#define msg(indice, value){std::cout << indice << ": " << value << std::endl;}

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
	std::vector<std::vector<step>> post_steps; /// driveable steps built based on the avoider functions, those that build the entire path
	std::vector<circle> pre_circles; /// circles based on coordinates selected by Dijkstra
	std::vector<std::vector<line>> pre_lines; /// lines tangent to any of pre_circles
	/// TODO: First move!
	for(unsigned_b i = 1; i < selected.size()-1; i++){
		if(i >= selected.size()){
			break;
		}
		pre_circles.emplace_back(selected.at(i), evaluate_radius(selected.at(i-1), selected.at(i)));
		//~ std::cout << pre_circles.back().print() << std::endl;
		}
	
	//~ pre_circles.push_back(circle(selected.back(), 0));
	coordinates start = selected.at(0);
	/// first circle generation block start; this is where the first circle is generated
	decimal_n radius_initial = evaluate_radius(selected.at(1), start);
	coordinates next_local = selected.at(1).make_local(start, -pi_const/2 - initial_rotation);
	bool is_right = (next_local.y < 0);
	bool is_behind = (next_local.x < 0);
	
	coordinates center_local(0, ((is_right)? -1: 1) * radius_initial);
	circle first_circle(start.make_global(center_local, initial_rotation - pi_const/2), radius_initial);
	//~ coordinates center_next_local = pre_circles.back().center.make_local(first_circle.center, -pi_const/2 - initial_rotation);
	pre_circles.insert(pre_circles.begin(), first_circle);
	/// first circle generation block end
	//~ pre_steps.push_back(avoider::to_steps(circle::tangents(pre_circles.back(), selected.back()), circle(selected.back(), 0), pre_circles.back()));
	std::vector<path> options = list_options(pre_circles, selected.back(), start);
	//~ for(auto o: options)
		//~ std::cout << o.print() << std::endl;
	
	/// TODO: THIS SECTION
	
	//~ std::cout << std::endl;
	//~ std::cout << options.size() << std::endl;
		
	
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
		ret.emplace_back(start, next);
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
	out.emplace_back(start, start.get_distance(goal));
	decimal_n goal_start_distance = goal.get_distance(start);
	for(wall w: m._map_walls) /// generation of circles between the walls and goal
		for(coordinates c: w.properties.edges)
			out.emplace_back(c, c.get_distance(goal));
			
	for(wall w: m._map_walls) /// generation of circles between the walls and start
		for(coordinates c: w.properties.edges)
			if(c.get_distance(goal) < goal_start_distance)
				out.emplace_back(c, c.get_distance(start));
			
			
	for(wall w: m._map_walls) /// generation of perimeter circles between of the wall edges
		for(coordinates c: w.properties.edges)
			out.push_back(create_perimeter(c));
	
	
	
	for(uint8_t i = 1; i < it; i++){ /// generation of circles between start and end
		out.emplace_back(start, (goal_start_distance * multiplier * (decimal_n)i) /  (decimal_n)it);
		out.emplace_back(goal, (goal_start_distance * multiplier * (decimal_n)i) /  (decimal_n)it);
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



wall planner::get_closest_wall(step s, map &m){
	wall wret;
	decimal_n ret = std::numeric_limits<decimal_n>::infinity();
	for(auto w: m._map_walls){
		decimal_n retc = step::get_distance(s, w);
		if(ret > retc){
			ret = retc;
			wret = w;
			}
		}
	return wret;
	}



wall planner::get_closest_wall(coordinates c, map &m){
	wall wret;
	decimal_n ret = std::numeric_limits<decimal_n>::infinity();
	for(auto w: m._map_walls){
		for(uint8_t i = 0; i < 4; i++){
			decimal_n retc = step::get_distance(step(w.properties.edges[i], w.properties.edges[(i+1)%4]), c);
			if(ret > retc){
				ret = retc;
				wret = w;
				}
			}
		}
	return wret;
	}



std::vector<step> planner::extend(std::vector<step>& future_steps, std::vector<step>& branch, circle future, map& m){
	wall closest = get_closest_wall(future_steps.back(), m);
	std::cout << closest.print_geogebra() << std::endl;
	
	return future_steps;
	}


std::vector<step> planner::avoid(std::vector<step> altered, map& m){
	wall closest = get_closest_wall(altered.at(1), m);
	std::cout << closest.print_geogebra() << std::endl;
	avoider l;
	return l.avoid(altered, closest);
	}



std::vector<path> planner::list_options(std::vector<circle> selected, coordinates end, coordinates start, decimal_n initial_rotation, decimal_n terminal_rotation){
	std::vector<path> ret;
	//~ msg("START", start.print())
	//~ msg("END", end.print())
	assert(selected.front().is_on(start));
	uint8_t is_on_zero_r = 0;
	if(!selected.back().is_on(end, 8e-2)){
		for(auto coord: selected.back().tangent_points(end)) // all the variants of connecting to an end
			ret.emplace_back(step(coord, end));
		} else {
			for(uint8_t i = 0; i < 2; i++){
				ret.emplace_back(step(end, end));
				ret.back().angle_end = ret.back().back().angle_end = 
				ret.back().back().angle_start = selected.back().center.get_gamma(end) + (-1 + (i * 2)) * pi_const/2;
				}
			if(selected.back().radius <= 1e-3){
				is_on_zero_r = 1;
				for(auto coord: selected.at(selected.size() - 2).tangent_points(end)) // all the variants of connecting to an end
					ret.emplace_back(step(coord, end));
				}
				
			}
	for(unsigned_b circ = 1 + is_on_zero_r; circ < selected.size(); circ++){ // every circle...
		for(unsigned_b pth = ret.size(); pth-- > 0;){ // every current option
			//~ std::cout << "CIRCS / LINES, INTS\n\t" << selected.at(selected.size() - (circ)).print() << "\n\t" << 
				//~ selected.at(selected.size() - (circ + 1)).print() << std::endl;
			for(line tr: circle::circle_tangents(selected.at(selected.size() - (circ)), selected.at(selected.size() - (circ + 1)))){
				//~ std::cout << "\t" << tr.make_perpendicular(selected.at(selected.size() - (circ)).center).print() << std::endl;
				//~ std::cout << "\t" << tr.make_perpendicular(selected.at(selected.size() - (circ + 1)).center).print() << std::endl;
				//~ std::cout << "\toriginal\n\t" << tr.print() << std::endl;
				coordinates end = vector(selected.at(selected.size() - (circ)).center,
					selected.at(selected.size() - (circ)).radius,
					selected.at(selected.size() - (circ)).
						center.get_gamma(tr.intersection
							(tr.make_perpendicular(selected.at(selected.size() - (circ)).center))), 1).get_point();
				coordinates start = vector(selected.at(selected.size() - (circ + 1)).center,
					selected.at(selected.size() - (circ + 1)).radius,
					selected.at(selected.size() - (circ + 1)).
						center.get_gamma(tr.intersection
							(tr.make_perpendicular(selected.at(selected.size() - (circ + 1)).center))), 1).get_point();
				//~ coordinates start = tr.intersection(tr.make_perpendicular(selected.at(selected.size() - (circ + 1)).center));
				coordinates center_local = coordinates::make_local(selected.at(selected.size() - (circ)).center, 
																	ret.at(pth).back().start, 
																	-ret.at(pth).back().angle_start);
				// local center by start of the step before and angle of that step
				//~ std::cout << "\tSTART / END\n\t\t" << start.print() << "\n\t\t" << end.print() << std::endl;
				decimal_n vector_angle = end.get_gamma(start);
				decimal_n tangent_angle = selected.at(selected.size() - (circ)).center.get_gamma(end);
				decimal_n difference_angle = vector_angle - (tangent_angle + ((center_local.x < 0)?1:-1) * pi_const/2);

				if((std::abs(difference_angle) <= 1e-3 || (std::abs(difference_angle + ((center_local.x < 0)?2:-2)*pi_const) <= 1e-3))){
					ret.push_back(ret.at(pth));
					ret.back().emplace_back(end, ret.at(pth).back().start, 
											selected.at(selected.size() - (circ)).center, 
											center_local.x < 0);
					ret.back().emplace_back(start, end);
					}
				}
			ret.erase(ret.begin() + pth);
			}
		}
		
	// part to finish the last, circular, step.
	for(path &p: ret){
		coordinates end_c = p.back().start;
		coordinates center_local = coordinates::make_local(selected.front().center,
															end_c, -p.back().angle_start);
		p.emplace_back(start, end_c, selected.front().center, center_local.x < 0);
		p.reorder(); // reorder them properly
		p.assemble(); // reorder them properly
		}
	/*
	for(auto paths: ret)
		std::cout << "trasa" << std::endl << paths.print() << std::endl;
	std::cout << ret.size() << std::endl;
	*/
	//~ std::cout << "trasa" << std::endl << ret.at(0).print() << std::endl;
	return ret;
	}



std::vector<path> planner::suppress_by_sensibility(std::vector<path> selected){
	std::vector<path> ret = selected;
	for(unsigned_b p = 0; p < ret.size(); p++){
		for(unsigned_b i = 2; i < ret.at(p).size(); i++){
			for(unsigned_b j = i - 2; j < ret.at(p).size(); j++){
				if((std::abs(((signed_b)i - (signed_b)j))) >= (unsigned_b)2){
					if(ret.at(p).at(i).get_distance(ret.at(p).at(j)) == 0){
						// by this this path is useless - deletion of this path occurs 
						// and all the parameters are resetted.
						i = 2; j = 0;
						ret.erase(ret.begin() + p);
						p = ((!p)? 0: p - 1);
						}
					}
				}
			}
		}
	return ret;
	}




path planner::avoid(path p, map &m, unsigned_b pit){
	assert(p.size() != 0 && p.back()._type == step::line_e);
	//~ std::system("figlet \"AVOID\"");
	constexpr decimal_n safe_dist = robot_radius * safe_constant;
	// there must be only one step in order to give the 
	// idea which step should be modified with which parameters
	/// 0(): acknowledge if there are any close_points available
	path ret_pth = p;
	unsigned_b index = (p.size() <= pit)? p.size() - 1: pit;
	unsigned_b lui = 0; // lui = last used index
	bool is_last = true;
	
	do {
		is_last = (index == 0);
		//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
		std::vector<planner::wall_container> 
		close_points = planner::avoid_phase_0(ret_pth, m);
		line original(ret_pth.at(index).start, ret_pth.at(index).end);
		//~ std::cout << "This " << __FILE__ << " " << __LINE__ << "\n\n\n\n\n\n\n\n\n\n\n\n" << std::endl;
		switch(ret_pth.at(index)._type){
			case step::line_e: {
				//~ std::system("figlet \"Linear start\"");
				//~ std::system(std::string("figlet \"INDEX\t" + std::to_string(index) + " z " + std::to_string(ret_pth.size() - 1) + "\"").c_str());
				//~ std::cout << ret_pth.at(index).print_geogebra() << std::endl << std::endl;
				//~ std::cout << ret_pth.print() << std::endl << std::endl;
				//~ std::cout << "linear start" << std::endl;
				/// selected all where it either collides or comes close
				// selects the closest wall
				planner::wall_container closest;
				std::array<std::deque<vector>, 2> sides({std::deque<vector>(), 
													std::deque<vector>()}); 
				// and here we'll try a little bit of insert_sort
				//~ line original = std::get<line>(ret_pth.at(index).formula); 
				// this must be outside, otherwise it would've been overwritten every time
				std::vector<wall> closest_wall;
				std::vector<std::vector<coordinates>> temporary;
				bool condition = true;
				
				/// OUTSIDE OF WHILE IS ABOVE
				while(condition){
					closest = planner::avoid_linear_wall_select(close_points.at(index));
					// finding the closest wall
					//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
					//~ msg("INDEX", index)
					//~ msg("SIZE", closest.second.size())
					//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
					if(!closest.second.size()) {index --; std::cout << "this ran" << std::endl; condition ^= condition; break;} // means that no wall violated rule
					closest_wall.assign({*std::get<wall *>(closest.second.front())});
					//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;

					planner::avoid_get_close_walls(m, closest_wall);
					planner::avoid_get_points(temporary, closest_wall);
					
					
					
					coordinates blob_mid(0, 0);
					for(wall w: closest_wall)
						blob_mid = blob_mid + w.estimate_center();
					blob_mid = blob_mid / closest_wall.size();
					//~ wall closest_wall;
					//~ std::cout << "\nBLOB\n" << blob_mid.print() << std::endl;
					//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
					/// 1(): lead point vectors from edges to line
					//~ std::cout << "ZDI" << std::endl;
					//~ for(auto i: temporary)
						//~ for(auto o: i)
							//~ std::cout << o.print() << std::endl;
					//~ for(auto o: closest_wall)
						//~ std::cout << o.print_geogebra() << std::endl;
					// we have the closest relevant wall, time to generate point vectors.
					{
						//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
						std::unique_ptr<std::vector<coordinates>> tmp(new std::vector<coordinates>());
						for(auto o: temporary)
							tmp -> insert(tmp -> end(), o.begin(), o.end());
						auto point_vectors = step::get_point_vectors(original, *tmp);
						//~ for(auto v: point_vectors)
							//~ std::cout << v.print() << std::endl;
						tmp.reset();
						//~ point_vectors = step::get_point_vectors(original, closest_wall.front());
						//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
						// sort them by length
						std::sort(point_vectors.begin(), point_vectors.end(), [](vector a, vector b){return a.length() < b.length();});
						/// 1-alpha(): start
						bool has_intersection = closest_wall.front().is_collision_course(original).size() != 0; 
						/// 1-alpha(): end
						// check if there are any intersections with original line
						// insert them into vectors by angle
						for(auto &o: point_vectors){
							//~ std::cout << std::sin(o.angle() - (original.get_angle())) << "\n" << original.print() << "\n" << o.print() << std::endl;
							bool b_index = (std::sin(o.angle() - (original.get_angle())) >= 0);
							//~ if((sides.at(b_index).at(i).length() < o.length())/* | has_intersection*/){
							sides.at(b_index).insert(sides.at(b_index).end(), o);
								//~ break;
								//~ }
							}
						//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
						//~ for(auto p: sides.at(0)){
							//~ std::cout << p.get_origin().print() << std::endl;
							//~ std::cout << p.print() << std::endl;
							//~ }
						//~ return ret_pth;
						//~ std::cout << "perpendiculars" << std::endl;
						//~ for(auto &o: sides){
							//~ std::cout << "strana" << std::endl;
							//~ for(auto &v: o)
								//~ std::cout << v.print() << std::endl;
							//~ }
					}
					/**
					/// 1-beta(): start
					bool negate_result = false;
					
					if(index != 0){ // index is non-zero
						system("figlet \"1-beta peek\"");
						if(ret_pth.at(index - 1)._type == step::circle_e){ // type at the previous index is circular
							coordinates center = std::get<circle>(ret_pth.at(index - 1).formula).center;
							vector circ(center, original.make_perpendicular(center).intersection(original));
							negate_result = std::abs(sides.at(0).front().angle() - circ.angle()) <= 2e-3; 
								// means that they're the same angle
							system("figlet \"1-beta intervence\"");
							
							}
						}
					/// 1-beta(): end
					*/
					decimal_n decision = /*(1 + -2 * negate_result) * */ ((std::accumulate(sides.at(0).begin(), sides.at(0).end(), vector(0, 0))/(sides.at(0).size())).length() 
					/*   from the line above*/ - (std::accumulate(sides.at(1).begin(), sides.at(1).end(), vector(0, 0))/(sides.at(1).size())).length());
					
					/// 2(): sort 
					auto extract_origins = [](std::deque<vector> a) -> std::vector<coordinates>{
						std::vector<coordinates> ret;
						for(auto v: a)
							ret.push_back(v.get_origin());
						return ret;
						};
					
					auto is_visible = [](coordinates c_o, std::vector<wall> w, coordinates a) -> bool{
						step s(a, c_o);
						for(auto v: w){
							//~ std::cout << s.print_geogebra() << std::endl;
							for(auto c: step::intersection(s, v)){
								//~ std::cout << "\t" << c.print() << std::endl;
								if(!(c == c_o))
									return false;
								}
							}
						return true;
						};
					
					auto filter_by_visibility = [&is_visible, closest_wall](std::shared_ptr<std::vector<coordinates>> e, coordinates end){
						std::vector<coordinates> ret;
						for(unsigned_b i = 0; i < e -> size(); i++)
							if(is_visible(e -> at(i), closest_wall, end))
								ret.push_back(e -> at(i));
						//~ std::cout << "\nATAK\n" << std::endl;
						for(auto c: ret)
							std::cout << c.print() << std::endl;
						return ret;
						};
					std::shared_ptr<std::vector<coordinates>> tmp_a(new std::vector<coordinates>(extract_origins(sides.at(decision > 0))));
					std::unique_ptr<std::vector<coordinates>> tmp_b(new std::vector<coordinates>(extract_origins(sides.at(decision <= 0))));
					tmp_a -> insert(tmp_a -> end(), tmp_b -> begin(), tmp_b -> end());
					*tmp_a = filter_by_visibility(tmp_a, ret_pth.at(index).end);
					//~ for(auto o: *tmp_a)
					tmp_b.reset();
					
					
					//~ std::cout << "\nRAZENI\n" << std::endl;
					//~ for(auto c: *tmp_a)
						//~ std::cout << c.print() << std::endl;
						
					for(auto sel_point: *tmp_a){
						//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
						//~ if(tmp -> size() != 1){ // must have only one point selected, if none are selected...
							//~ std::cout << tmp -> size() << "\tIDK, but " << __FILE__ << " " << __LINE__ << std::endl;
							//~ tmp.reset();
							//~ continue;
							//~ }
						auto onlytwo = [](step s, map m){
							std::vector<coordinates> inters;
							for(auto i: m._map_walls){
								auto ic = s.intersection(i);
								inters.insert(inters.end(), ic.begin(), ic.end());
								}
							for(coordinates c: inters)
								if(!(c == s.start) & !(c == s.end)) return false;
							return true;
							};
						/// 3(): ((index)) ? std::get<circle>(ret_pth.at(index - 1).formula): 
						unsigned_b suitable_circle = 0;
						/*
						for(unsigned_b i = ret_pth.size() - 1; i > index; i--){
							if(ret_pth.at(i)._type == step::circle_e)
								if(onlytwo(step(ret_pth.at(i).get_center(), sel_point), m)){
									suitable_circle = i - index - 1;
									std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
									}
							}
						*/
						std::vector<circle> curve({(circle(ret_pth.front().start, 0)), 
													circle(sel_point, safe_dist)});
						if((index + 1) < ret_pth.size())
							curve.push_back(std::get<circle>(ret_pth.at(index + 1 + suitable_circle).formula));
						//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
						//~ for(auto a: curve)
							//~ std::cout << "selected\n" << a.print() << std::endl;
						//~ std::cout << "selected\n" << curve.at(1).print() << std::endl;
						//~ tmp.reset();
						
						/// 4():
						std::vector<path> replacement = planner::list_options(curve, ret_pth.at(index + (curve.size() == 3)).end, ret_pth.front().start, 
								ret_pth.at(index + 2 * (curve.size() == 3)).angle_start);
						//~ std::cout << "size: " << replacement.size() << std::endl;
						for(auto r: replacement){
							auto r_zero = r;
							r_zero.delete_zero_length();
							//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
							if(!r_zero.at(r_zero.size() - (1 + (curve.size() == 3))).intersection(closest_wall.front()).size()){
								//~ std::cout << "cesta\n" << r_zero.print() << std::endl;
								close_points = planner::avoid_phase_0(r_zero, m);
								//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
								bool has_substitute = false;
								auto sub = r_zero;
								if(r_zero.at(r_zero.size() - 1)._type == step::circle_e){
									if((r_zero.at(r_zero.size() - 1).length() / (std::get<circle>
											(r_zero.at(r_zero.size() - 1).formula).radius * 2 * pi_const)) > 0.5f){
										has_substitute = true;
										coordinates halfway = step(r_zero.at(r_zero.size() - 1).start, r_zero.at(r_zero.size() - 1).end).get_center();
										vector to_sector = vector(r_zero.at(r_zero.size() - 1).get_center(), halfway) >> halfway;
										sub.at(sub.size() - 1) = step(sub.at(sub.size() - 1).start, sub.at(sub.size() - 1).end, to_sector.get_point());
										//~ msg("RESULT\n", sub.at(sub.size() - 1).print_geogebra())
										}
									}
								//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
								//~ std::cout << "Krok:\n" << close_points.at(r_zero.size() - (1 + (curve.size() == 3))).first -> print_geogebra() << std::endl;
								//~ std::cout << "VIOLATORI\n" << planner::avoid_violation_number(close_points.at(close_points.size() - (1 + index))) << std::endl;
								//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
								//~ if((r_zero.size() - ret_pth.size() + index - 1) < r_zero.size())
									//~ std::cout << "- 1\n" << r_zero.at(r_zero.size() - ret_pth.size() + index - 1).print_geogebra() << std::endl;
								//~ if((r_zero.size() - ret_pth.size() + index + 1) < r_zero.size())
									//~ std::cout << "+ 1\n" << r_zero.at(r_zero.size() - ret_pth.size() + index + 1).print_geogebra() << std::endl;
								//~ auto round = r_zero.at(((r_zero.size() - ret_pth.size() + index + 1) < r_zero.size())?
									//~ (r_zero.size() - ret_pth.size() + index + 1) : (r_zero.size() - ret_pth.size() + index - 1));
								//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
								auto round = r_zero.back();
								//~ std::cout << "LOCAL BLOBS\n" << 
									//~ round.start.make_local(blob_mid, -round.angle_start).print() << "\n" <<
									//~ round.end.make_local(blob_mid, -round.angle_end).print() << "\n" <<
									//~ round.start.print() << "\n" <<
									//~ round.end.print() << "\n" <<
								//~ std::endl;
								//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
								auto is_closer_int = [round, blob_mid](){	
										coordinates inter = line(round.angle_start, round.start).intersection(line(round.angle_end, round.end));
										step axis(inter, step::get_center(round));
										return axis.intersection(std::get<line>(axis.formula).make_perpendicular(blob_mid)).size() > 0;
										};
										
								bool same = ((round.start.make_local(blob_mid, -round.angle_start).x * round.end.make_local(blob_mid, -round.angle_end).x)
											* (1 + -2 * (!is_closer_int() & (round.angle() > pi_const)))) > 0;
								//~ std::cout << "SAME\n" << same << std::endl;
								//~ msg("ANGLE", (round.angle() / pi_const)*180.0)
								if((same | (curve.size() < 3)) && !planner::avoid_violation_number(close_points.at(close_points.size() - (1 + index)))){ // if the size at the index is equal zero
									//~ replacement.assign({r_zero});
									//~ if(std::abs(r_zero.back().angle_start - r_zero.at(r_zero.size() - 2).angle_end) <= 1e-3){
										if(((curve.size() >= 3)? 
											(r_zero.at(r_zero.size() - 1).direction_curve == ret_pth.at(index + 1).direction_curve) : 1)){
											unsigned_b tmp_size = ret_pth.size();
											ret_pth.erase(ret_pth.begin(), ret_pth.begin() + index + 1 + (curve.size() >= 3));
											ret_pth.insert(ret_pth.begin(), r_zero.begin(), r_zero.end());
											index = ret_pth.size() - (tmp_size - index + 1) + (curve.size() >= 3);
											//~ std::cout << "cesta\n" << r_zero.print() << "\nr_zero " << r_zero.size() << "\nret_pth " << ret_pth.size() << "\nindex " << std::to_string(index) << std::endl;
											//~ std::cout << "This " << __FILE__ << " " << __LINE__ << "\n\n\n\n\n\n\n\n\n\n\n\n" << std::endl;
											//~ std::cout << "EVEN This " << __FILE__ << " " << __LINE__ << std::endl;
											is_last = (index == 0);
											condition = false;
											}
										//~ }
									//~ break;
									}
									
								if(has_substitute & condition){
									close_points = planner::avoid_phase_0(sub, m);
									if(same && !planner::avoid_violation_number(close_points.at(close_points.size() - (1 + index)))){ // if the size at the index is equal zero
										//~ replacement.assign({r_zero});
										unsigned_b tmp_size = ret_pth.size();
										ret_pth.erase(ret_pth.begin(), ret_pth.begin() + index + 1 + (curve.size() >= 3));
										ret_pth.insert(ret_pth.begin(), sub.begin(), sub.end());
										index = ret_pth.size() - (tmp_size - index + 1) + (curve.size() >= 3);
										//~ std::cout << "cesta\n" << r_zero.print() << "\nr_zero " << r_zero.size() << "\nret_pth " << ret_pth.size() << "\nindex " << std::to_string(index) << std::endl;
										//~ std::cout << "This " << __FILE__ << " " << __LINE__ << "\n\n\n\n\n\n\n\n\n\n\n\n" << std::endl;
										//~ std::cout << "EVEN This " << __FILE__ << " " << __LINE__ << std::endl;
										is_last = (index == 0);
										condition = false;
										//~ break;
										}
									}
								if(!condition) break;
								}
							}
							//~ std::cout << "this was from linear" << std::endl;
							//~ std::this_thread::sleep_for(std::chrono::seconds(2));
						if(!condition) break;
						}
					}
				break;
				}
				
			case step::circle_e: {
				//~ std::system("figlet \"Circular start\"");
				//~ std::system(std::string("figlet \"INDEX\t" + std::to_string(index) + " z " + std::to_string(ret_pth.size() - 1) + "\"").c_str());
				//~ std::cout << ret_pth.at(index).print_geogebra() << std::endl << std::endl;
				//~ std::cout << ret_pth.print() << std::endl << std::endl;
				//~ std::cout << "circular start" << std::endl;
				/// selected all where it either collides or comes close
				/// 0(): selects the closest wall
				planner::wall_container closest;
				std::array<std::deque<vector>, 2> sides({std::deque<vector>({vector(), vector()}), 
													std::deque<vector>({vector(), vector()})}); 
				// and here we'll try a little bit of insert_sort
				circle original = std::get<circle>(ret_pth.at(index).formula); 
				// this must be outside, otherwise it would've been overwritten every time
				wall closest_wall;
				bool condition = true;
				
				while(condition){
					//~ std::cout << "circular loop" << std::endl;
					//~ std::cout << "index odecten: " << (index) << "\t" << ret_pth.size() << std::endl;
					//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
					std::vector<wall> closest_wall = planner::avoid_circular_phase_0(close_points.at(index));
					std::vector<std::vector<coordinates>> temporary;
					
					planner::avoid_get_close_walls(m, closest_wall);
					//~ planner::avoid_get_points(temporary, closest_wall);
					
					/*
					for(auto o: closest_wall){
						temporary.emplace_back(&o.properties.edges[0], &o.properties.edges[4]);
						//~ temporary.emplace_back();
						//~ for(uint8_t i = 0; i < 4; i++)
							//~ temporary.back().push_back(o.properties.edges[i]);
						}
					
					// erasing them for being too close
					for(unsigned_b i = 0; i < temporary.size(); i++){
						for(unsigned_b j = 0; j < temporary.at(i).size(); j++){
							bool erase = false;
							for(unsigned_b k = i + 1; k < temporary.size(); k++){
								for(unsigned_b l = 0; l < temporary.at(k).size(); l++){
									if(temporary.at(i).at(j).get_distance(temporary.at(k).at(l)) < (5e-2)){
										//~ std::cout << "ERASING - DISTANCE\n" << temporary.at(i).at(j).print() << std::endl;
										temporary.at(k).erase(temporary.at(k).begin() + l--);
										erase = true;
										}
									}
								}
							if(erase) temporary.at(i).erase(temporary.at(i).begin() + j--);
							}
						}
					
					// erasing them for touching other walls
					for(unsigned_b i = 0; i < temporary.size(); i++){
						for(unsigned_b j = 0; j < temporary.size(); j++){
							if(i != j){
								for(unsigned_b k = 0; k < temporary.at(j).size(); k++){
									if(step::get_distance(temporary.at(j).at(k), closest_wall.at(i)) < (2.5e-1)){
										//~ std::cout << "ERASING - WALL\n" << temporary.at(j).at(k).print() << std::endl;
										temporary.at(j).erase(temporary.at(j).begin() + k--);
										}
									}
								}
							}
						}
					*/
					coordinates blob_mid(0, 0);
					for(wall w: closest_wall)
						blob_mid = blob_mid + w.estimate_center();
					//~ std::cout << "BLOB MID\n" << (blob_mid / closest_wall.size()).print() << std::endl;
					/*
					if(index != 0)
						if(ret_pth.at(index - 1)._type == step::line_e)
							for(wall w: m._map_walls){
								std::cout << "THIS OCCURRED" << std::endl;
								std::cout << w.print_geogebra() << std::endl;
								line l = std::get<line>(ret_pth.at(index - 1).formula);
								auto c = w.is_collision_course(l);
								step s = ret_pth.at(index - 1);
								std::cout << l.print() << std::endl;
								for(auto a: c){
									std::cout << a.print() << std::endl;
									if(s.on_segment(a) | s.end.get_distance(a) > s.start.get_distance(a)){
										// push_back if that wall is somewhere before end
										closest_wall.push_back(w);
										break;
										}
									}
								}*/
					//~ std::cout << "CLOSE" << std::endl;
					//~ for(auto cw: closest_wall)
						//~ std::cout << cw.print_geogebra() << std::endl;
					//~ std::cout << "CLOSE" << std::endl;
					
					//~ for(auto v: temporary)
						//~ for(auto c: v)
							//~ std::cout << c.print() << std::endl;
						
					if(!closest_wall.size()){index--; /* std::system("figlet \"ESCAPE VIA CONTINUE 700\""); */condition = false; continue;}
					//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
					//~ for(auto o: closest_wall)
						//~ std::cout << "CANDIDATE\n" << o.print_geogebra() << std::endl;
					std::vector<coordinates> candidates;
					//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
					
					//~ std::cout << "circle candidate\n" << std::endl;
					//~ for(auto t: temporary)
						//~ for(auto c: t)
							//~ std::cout << c.print() << std::endl;
					
					
					candidates = planner::avoid_circular_phase_1(*close_points.at(index).first, closest_wall);
					temporary.clear();
					//~ std::unique();
					for(coordinates cand: candidates){
						//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
						//~ std::cout << "circle candidate\n" << cand.print() << std::endl;
						//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
						if(!candidates.size()){/*std::system("figlet \"ESCAPE VIA CONTINUE 707\"");*/ continue;}
						//~ std::cout << 
						std::vector<circle> curve = {(((index - 1)) ? std::get<circle>(ret_pth.at(index - 2).formula): circle(ret_pth.front().start, 0)), 
										circle(cand, safe_dist), original};
						//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
						//~ for(auto c: curve){
							//~ std::cout << c.center.print() << std::endl;
							//~ std::cout << c.print() << std::endl;
							//~ }
						//~ std::cout << "Possible source " << __FILE__ << " " << __LINE__ << std::endl;
						//~ std::cout << "konec/zacatek/kruhy" << std::endl;
						//~ std::cout << ret_pth.at(index).end.print() << std::endl;
						//~ std::cout << ret_pth.front().start.print() << std::endl;
						//~ for(auto c: curve) 
							//~ std::cout << (c.print()) << std::endl;
						/// 4():
						std::vector<path> replacement = planner::list_options(curve, ret_pth.at(index).end, ret_pth.front().start, 
							(((index - 1)) ? (ret_pth.at(index - 2)).angle_start: (ret_pth.front().angle_start)));
						//~ for(auto o: replacement) std::cout << o.print() << std::endl;
						//~ std::cout << "pocet cest" << replacement.size() << std::endl;
						for(auto r: replacement){
							auto r_zero = r;
							r_zero.delete_zero_length();
							close_points = planner::avoid_phase_0(r_zero, m);
							if(close_points.at(r_zero.size() - 1).first -> direction_curve == ret_pth.at(index).direction_curve){
								if(!(close_points.at(r_zero.size() - 1).first -> intersection(closest_wall.front()).size() 
									+ planner::avoid_violation_number(close_points.at(r_zero.size() - 2)))){ // if the size at the index is equal zero
									//~ replacement.assign({r_zero});
									//~ msg("THAT INDEX\n", r_zero.at(r_zero.size() - 2).print_geogebra())
									unsigned_b tmp_size = ret_pth.size();
									ret_pth.erase(ret_pth.begin(), ret_pth.begin() + index + 1);
									ret_pth.insert(ret_pth.begin(), r_zero.begin(), r_zero.end());
									index = ret_pth.size() - (tmp_size - index + 1);
									//~ std::cout << "cesta\n" << r_zero.print() << "\nr_zero " << r_zero.size() << "\nret_pth " << ret_pth.size() << "\nindex " << r_zero.size() - (2 + index) << std::endl;
									//~ std::cout << "This " << __FILE__ << " " << __LINE__ << "\n\n\n\n\n\n\n\n\n\n\n\n" << std::endl;
									//~ std::cout << "EVEN This " << __FILE__ << " " << __LINE__ << std::endl;
									condition = false;
									//~ index = r_zero.size() - (2 + index);
									//~ break;
									//~ std::cout << "cesta_cela\n" << ret_pth.print() << std::endl << std::endl;
									//~ std::this_thread::sleep_for(std::chrono::seconds(1));
									//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
									is_last = (index == 0);
									break;
									}
								}
							//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
							}
						//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
						if(!condition) break;
						}
					}
				//~ std::cout << "this was from circular" << std::endl;
				if(!condition) break;
				//~ std::this_thread::sleep_for(std::chrono::seconds(1));
				}
			//~ std::cout << "from circular" << std::endl;
			break;
			}
		//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
		//~ for(auto [stp, w]: close_points){
			//~ std::cout << "step\n"  << stp -> print_geogebra() << "\nvelikost " << w.size() << std::endl;
			//~ for(unsigned_b i = 0; i < w.size(); i++){
				//~ for(auto c: std::get<1>(w.at(i))){
					//~ std::cout << c.print() << std::endl;
					//~ }
				
				//~ for(auto v: std::get<2>(w.at(i))){
					//~ std::cout << v.print() << std::endl;
					//~ }
				//~ }
			
			//~ }
		} while(((index - 1) < index ^ is_last) | !is_last);
	
	std::cout << ret_pth.print() << std::endl;
	
	return ret_pth;
	}




std::vector<std::pair<std::vector<coordinates>, wall>> planner::intersecting_walls(step s, map &m){
	std::vector<std::pair<std::vector<coordinates>, wall>> ret;
	std::vector<coordinates> ret_c;
	for(auto w: m._map_walls){
		ret_c = s.intersection(w);
		if(ret_c.size())
			ret.emplace_back(ret_c, w);
		}
	//~ std::cout << "this runned " << ret.size() << std::endl;
	return ret;
	}




std::vector<planner::wall_container> 
	planner::avoid_phase_0(path &p, map &m){
	constexpr decimal_n safe_dist = robot_radius * safe_constant - 1e-3;
	std::vector<planner::wall_container> close_points;
	for(auto &s: p){
		close_points.emplace_back(&s, std::vector<std::tuple<wall *,
												std::vector<coordinates>, 
												std::vector<vector>>>());
		for(auto &w: m._map_walls){
			close_points.back().second.emplace_back(&w, 
								close_points.back().first -> intersection(w),
								close_points.back().first -> get_vectors(w));
			//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
			}
		}
	//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
	for(auto &[stp, w]: close_points){
		//~ std::cout << "step\n"  << stp -> print_geogebra() << "\nvelikost " << w.size() << std::endl;
		for(unsigned_b i = 0; i < w.size(); i++){
			bool toggled = false;
			for(std::vector<vector>::iterator v = std::get<2>(w.at(i)).begin();
				v != std::get<2>(w.at(i)).end(); v++){
					toggled = toggled | v -> length() < (safe_dist);
					if(toggled) break;
				}
			
			if(toggled | (std::get<1>(w.at(i)).size() != 0)) continue;
			w.erase(w.begin() + i--);
			}
		}
	return close_points;
	}
	
	

	
planner::wall_container planner::avoid_linear_wall_select(planner::wall_container a){
	planner::wall_container w;
	/* this system should act followingly:
	 * 		1) pick all vectors where the rule violation occurs
	 * 		2) compare distances of them with intersection points
	 * */
	constexpr decimal_n safe_dist = robot_radius * safe_constant;
	decimal_n dist = std::numeric_limits<decimal_n>::infinity();
	
	for(auto o: a.second){
		for(auto v: std::get<std::vector<vector>>(o))
			if(v.length() > 0 && v.length() <= safe_dist){
				decimal_n dist_c = a.first -> end.get_distance(v.get_point()) - std::sqrt(std::pow(safe_dist, 2) - std::pow(v.length(), 2));
				if(dist_c < dist){
					dist = dist_c;
					w = wall_container(a.first, {o});
					}
				}
				
		for(auto c: std::get<std::vector<coordinates>>(o)){
			line p = a.first -> perpendicular_bisector();
			line l(a.first -> end, a.first -> start); // same for std::get<line>(step::formula), but even for circle formulas
			//~ std::cout << l.intersection(p.make_parallel(c)).print() << std::endl;
			decimal_n dist_c = a.first -> end.get_distance(l.intersection(p.make_parallel(c))) - safe_dist;
			if(dist_c < dist){
				dist = dist_c;
				w = wall_container(a.first, {o});
				}
			}
		}
	return w;
	}
	
	

		
auto planner::avoid_linear_phase_1(wall w){
	constexpr decimal_n safe_dist = robot_radius * safe_constant;
	
	return 1.0f;
	}
	
	

	
std::vector<coordinates> planner::avoid_linear_phase_2(wall &w, std::deque<vector> v, step s){
	std::vector<coordinates> ret;
	decimal_n min = std::numeric_limits<decimal_n>::infinity();
	unsigned_b min_i = std::numeric_limits<unsigned_b>::infinity();
	for(auto o: v){
		//~ std::cout << step(o.get_origin(), s.end).intersection(w).size() << std::endl;
		//~ for(auto i: step(o.get_origin(), s.end).intersection(w)){
			//~ std::cout << i.print() << std::endl;
			//~ }
		auto cand = [&](std::vector<coordinates> inter, coordinates c){
			decimal_n ret = 0;
			std::vector<coordinates> st = inter;
			st.push_back(c);
			
			for(uint8_t i = 0; i < st.size(); i++){
				//~ std::cout << st.at(i).print() << std::endl;
				ret += st.at(i).get_distance(st.at((i + 1) % st.size()));
				}
			return ret;
			};
		auto l = step(o.get_origin(), s.end).intersection(w);
		unsigned_b ass_ic = l.size();
		decimal_n ass_c = cand(l, o.get_origin());
		if(ass_c <= min && ass_c < 1e-2 && ass_ic <= 2 /*&& ass_ic > 0*/){
			min = ass_c;
			min_i = ass_ic;
			ret.assign({o.get_origin()}); // only like 1-2 intersections as this is the corner are possible
			}
		}
	return ret;
	}
	
	

	
auto planner::avoid_linear_phase_3(){
	constexpr decimal_n safe_dist = robot_radius * safe_constant;
	
	return 1.0f;
	}
	
	

	
auto planner::avoid_linear_phase_4(){
	constexpr decimal_n safe_dist = robot_radius * safe_constant;
	
	return 1.0f;
	}
	
	

	
auto planner::avoid_linear_phase_5(){
	constexpr decimal_n safe_dist = robot_radius * safe_constant;
	
	return 1.0f;
	}
	
	


std::vector<wall> planner::avoid_circular_phase_0(planner::wall_container w){ // sorts walls based on which violation was the first
	constexpr decimal_n safe_dist = robot_radius * safe_constant - 1e-3;
	std::vector<wall> ret;
	auto wv = w.second;
	std::sort(wv.begin(), wv.end(), [&, w](auto a, auto b){
		decimal_n shortest_a = std::numeric_limits<decimal_n>::infinity(), shortest_b = shortest_a;
		bool ret = false;
		coordinates center = w.first -> get_center();
		for(auto i: std::get<2>(a)){
			decimal_n ret_c = step(i.get_point(), w.first -> end, center).length();
			shortest_a = (ret_c < shortest_a)? ret_c: shortest_a;
			}
			
		for(auto i: std::get<2>(b)){
			decimal_n ret_c = step(i.get_point(), w.first -> end, center).length();
			shortest_b = (ret_c < shortest_b)? ret_c: shortest_b;
			}
			
		for(auto i: std::get<1>(a)){
			decimal_n ret_c = step(i, w.first -> end, center).length();
			shortest_a = (ret_c < shortest_a)? ret_c: shortest_a;
			}
			
		for(auto i: std::get<1>(b)){
			decimal_n ret_c = step(i, w.first -> end, center).length();
			shortest_b = (ret_c < shortest_b)? ret_c: shortest_b;
			}
		return shortest_a < shortest_b;});
	for(auto o: wv)
		ret.push_back(*std::get<wall *>(o));
	//~ std::cin.ignore(100);
	//~ char wait;
	//~ std::this_thread::sleep_for(std::chrono::seconds(3));
	return ret;
	}




std::vector<coordinates> planner::avoid_circular_phase_1(step s, std::vector<wall> w){ // the acknowledging phase: to know if any points may be used on the current side
	//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
	constexpr decimal_n safe_dist = robot_radius * safe_constant;
	decimal_n length = std::numeric_limits<decimal_n>::infinity();
	unsigned_b ret_c = std::numeric_limits<unsigned_b>::infinity();
	//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
	// fundamental return point selectors
	//~ for(auto u: w)
		//~ std::cout << u.print_geogebra() << std::endl;
	std::vector<coordinates> ret; 
	std::vector<coordinates> ret_h;
	
	// point selectors for mirrored 
	std::vector<coordinates> ret_m; 
	std::vector<coordinates> ret_hm;
	
	// formula of original step 
	circle form = std::get<circle>(s.formula);
	//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;

	// generating temporary point vector which contains all non-duplicate condition-matching points
	std::unique_ptr<std::vector<std::vector<coordinates>>> temporary(new std::vector<std::vector<coordinates>>());
	std::vector<wall> w_temp = w;
	
	auto is_duplicate = [&](auto a, auto b){
		unsigned_n coincidences = 0;
		for(uint8_t i = 0; i < 4; i++){
			for(uint8_t j = 0; j < 4; j++){
				coincidences += (a.properties.edges[i] == b.properties.edges[j]);
				}
			}
		return (a.estimate_center() == b.estimate_center()) && coincidences >= 2;
		};
	
	// erasing duplicates from temporary wall selection
	//~ std::cout << "WALL SIZE\t" << w.size() << std::endl;
	for(unsigned_b i = 0; i < w_temp.size(); i++)
		for(unsigned_b j = i + 1; j < w_temp.size(); j++)
			if(is_duplicate(w_temp.at(i), w_temp.at(j)))
				w_temp.erase(w_temp.begin() + j--);
	
	// emplacing edges of remaining walls into structured selection
	//~ std::cout << "WALL_TEMP SIZE\t" << w_temp.size() << std::endl;
	for(auto o: w_temp){
		temporary -> emplace_back();
		for(uint8_t i = 0; i < 4; i++)
			temporary -> back().push_back(o.properties.edges[i]);
			}
	
	// printing them
	//~ for(auto o: temporary){
		//~ for(auto r: o)
			//~ std::cout << r.print() << std::endl;
		//~ }
	
	// erasure cycles - by distance to one each other or to walls they represent
	for(unsigned_b i = 0; i < temporary -> size(); i++){
		for(unsigned_b j = 0; j < temporary -> at(i).size(); j++){
			bool erase = false;
			for(unsigned_b k = i + 1; k < temporary -> size(); k++){
				for(unsigned_b l = 0; l < temporary -> at(k).size(); l++){
					if(temporary -> at(i).at(j).get_distance(temporary -> at(k).at(l)) < (5e-2)){
						//~ std::cout << "ERASING - DISTANCE\n" << temporary -> at(i).at(j).print() << std::endl;
						temporary -> at(k).erase(temporary -> at(k).begin() + l--);
						erase = true;
						}
					}
				}
			if(erase) temporary -> at(i).erase(temporary -> at(i).begin() + j--);
			}
		}
		
	for(unsigned_b i = 0; i < temporary -> size(); i++){
		for(unsigned_b j = 0; j < temporary -> size(); j++){
			if(i != j){
				for(unsigned_b k = 0; k < temporary -> at(j).size(); k++){
					if(step::get_distance(temporary -> at(j).at(k), w_temp.at(i)) < (2.5e-1)){
						//~ std::cout << "ERASING - WALL\n" << temporary -> at(j).at(k).print() << std::endl;
						temporary -> at(j).erase(temporary -> at(j).begin() + k--);
						}
					}
				}
			}
		}
	// erasure end
	// point selection algorithm end
	for(auto s: *temporary)
		ret.insert(ret.end(), s.begin(), s.end());
	
	// printing them
	//~ std::cout << "\nFILTERED\n" << std::endl;
	for(auto o: *temporary){
		for(auto r: o)
			std::cout << r.print() << std::endl;
		}
		
	temporary.reset();
	// creating mirrored and extended version of searching steps
	//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
	circle form_mirror((vector(form.center, s.end) >> s.end).get_point(), form.radius);
	step s_mirrored((vector(s.start, form.center) >> form_mirror.center).get_point(),
					s.end, form_mirror.center, !s.direction_curve);
	step s_extended((vector(s.end, form.center) >> form.center).get_point(),
					s.end, form.center, s.direction_curve);
	/* line::intersection(line((s.angle_end - pi_const/2), s.end), line((s.angle_end), s.end))) >> s.end).get_point()
	 * - this made an exactly mirrored copy of step s, but it was rather unusable as it
	 * 		was prone to select the exact point where the step from which it is 
	 * 		derived from has the rotation center.
	 * 
	 * */
	//~ std::cout << form_mirror.print() << std::endl;
	//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
	//~ std::cout << s_mirrored.print_geogebra() << std::endl;
	//~ std::cout << s_extended.print_geogebra() << std::endl;
	//~ std::cout << s.print_geogebra() << std::endl;
	//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
	//~ for(auto w: m._map_walls)
	//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
	//~ temporary = new std::vector<std::vector<coordinates>>());
	//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
	unsigned_b redundant = ret.size();
	for(unsigned_b e = 0; e < redundant; e++){
		//~ std::cout << ret.at(e).print() << std::endl;
		//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
		for(auto c: circle::tangent_points(form, ret.at(e))){
			//~ std::cout << c.get_gamma(e)* 180/pi_const << "° and " << (form.center.get_gamma(c) + (const decimal_n)(pi_const / 2) *
					//~ (1 + s.direction_curve * -2)) << "°" << std::endl;
			// pushing 
			//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
			if((s.on_segment(c) | s_extended.on_segment(c)) && 
				std::abs(std::sin(c.get_gamma(ret.at(e))) - std::sin(form.center.get_gamma(c) + (const decimal_n)(pi_const / 2) *
					(1 + !s.direction_curve * -2))) <= 1e-3){
				//~ std::cout << "BOD CIRKULARU" << std::endl;
				//~ std::cout << c.print() << std::endl;
				//~ std::cout << e.print() << std::endl;
				//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
				//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
				unsigned_b index = 0;
				while(ret_h.size() > index){
					//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
					//~ std::cout << std::to_string(index) << std::endl;
					if(step(s.end, ret_h.at(index), form.center, s.direction_curve).length() < step(s.end, c, form.center, s.direction_curve).length()){
						break;
						}
					//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
					index ++;
					}
				ret.insert(ret.begin() + index + redundant, ret.at(e));
				ret_h.push_back(c);
				break;
				}
			}
		//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
		//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
		for(auto c: circle::tangent_points(form_mirror, ret.at(e))){
			//~ std::cout << c.get_gamma(e)* 180/pi_const << "° and " << (form.center.get_gamma(c) + (const decimal_n)(pi_const / 2) *
					//~ (1 + s.direction_curve * -2)) << "°" << std::endl;
			if(s_mirrored.on_segment(c) && 
				std::abs(std::sin(c.get_gamma(ret.at(e))) - std::sin(form_mirror.center.get_gamma(c) + (const decimal_n)(pi_const / 2) *
					(1 + s.direction_curve * -2))) <= 1e-3){
				//~ std::cout << "BOD CIRKULARU 2" << std::endl;
				//~ std::cout << c.print() << std::endl;
				//~ std::cout << ret.at(e).print() << std::endl;
				//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
				unsigned_b index = 0;
				while(ret_hm.size() > index){
					//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
					//~ std::cout << std::to_string(index) << std::endl;
					if(step(s.end, ret_hm.at(index), form_mirror.center, !s.direction_curve).length() < step(s.end, c, form_mirror.center, !s.direction_curve).length()){
						//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
						break;
						}
					//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
					index ++;
					}
				//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
				ret_m.insert(ret_m.begin() + index, ret.at(e));
				ret_hm.push_back(c);
				break;
				}
			}
		//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;

		}
	//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
	ret.erase(ret.begin(), std::min(ret.begin() + ret.size() - 1, ret.begin() + (redundant)));
	//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
	//~ std::cout << "RET" << std::endl;
	//~ for(auto o: ret)
		//~ std::cout << o.print() << std::endl;
	//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
	//~ std::cout << "SIZE " << ret.size() << std::endl;
	//~ if(ret.size()) std::cout << "STEP\n" << std::endl;
	//~ if(ret.size()) std::cout << "STEP\n" << step(s.end, ret_h.front(), 
								//~ (s.on_segment(ret_h.front()))? form.center: form_mirror.center, 
								//~ s.on_segment(ret_h.front()) ^ s.direction_curve).print_geogebra() << std::endl;
	/*
	 * for(unsigned_b i = 0; i < ret.size(); i++){
		bool segment_sel = s.on_segment(ret_h.at(i)) | s_extended.on_segment(ret_h.at(i));
		decimal_n len_c = step(s.end, ret_h.at(i), 
								(segment_sel)? form.center: form_mirror.center, 
								segment_sel ^ s.direction_curve).length();
		std::cout << step(s.end, ret_h.at(i), 
								(segment_sel)? form.center: form_mirror.center, 
								segment_sel ^ s.direction_curve).print_geogebra() << std::endl;
		bool not_through = true;
		bool not_inside = true;
		for(auto wc: w_temp){
			for(auto c: step(ret_h.at(i), ret.at(i)).intersection(wc)){
				if(!(c == ret.at(i))){
					not_through = false;
					break;
					}
				if(wc.inside(((segment_sel)? form.center: form_mirror.center)))
					if(step(ret_h.at(i), ret.at(i)).on_segment(c) && !(ret.at(i) == c)){
						std::cout << "THROUGH\n" << step(ret_h.at(i), ret.at(i)).print_geogebra() << std::endl;
						not_through = false;
						break;
						}
					}
			not_inside &= !wc.inside(ret_h.at(i));
			}
		
		if(len_c < length && not_inside && not_through){
			length = len_c;
			ret_c = i;
			}
		}
		*/
	//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
	//~ if (ret.size()) ret.assign({ret.at(ret_c)});
	//~ for(auto p: ret)
		//~ std::cout << "BOD\n" << p.print() << std::endl;
	//~ for(auto p: ret_m)
		//~ std::cout << "BOD2\n" << p.print() << std::endl;
	//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
	return ret;
	}





unsigned_b planner::avoid_violation_number(planner::wall_container w){
	constexpr decimal_n safe_dist = robot_radius * safe_constant - 1e-3;
	unsigned_b ret = 0;
	for(auto o: w.second){
		ret += (std::get<std::vector<coordinates>>(o)).size();
		for(auto v: std::get<std::vector<vector>>(o)) 
			if(v.length() < safe_dist){ ret ++; /* std::cout << "This ruins my sleep" << v.print() << std::endl;*/}
		}	
	return ret;
	}





std::vector<wall> planner::avoid_get_close_walls(map &m, std::vector<wall>& closest_wall){
	constexpr decimal_n safe_dist = robot_radius * safe_constant;
	// confirm duplicates
	auto is_duplicate = [&](auto a, auto b){
		unsigned_n coincidences = 0;
		for(uint8_t i = 0; i < 4; i++){
			for(uint8_t j = 0; j < 4; j++){
				coincidences += (a.properties.edges[i] == b.properties.edges[j]);
				}
			}
		return (a.estimate_center() == b.estimate_center()) && coincidences >= 2;
		};
	
	
	// confirm being close
	auto is_close = [&](auto a, auto b, decimal_n predicate){
		decimal_n shortest_dist = std::numeric_limits<decimal_n>::infinity();
		for(uint8_t i = 0; i < 4; i++){
			shortest_dist = std::min(shortest_dist, step::get_distance(step(a.properties.edges[i], a.properties.edges[(i+1)%4]), b));
			}
		return shortest_dist <= predicate;
		};
	
	// adds close walls
	{
	bool close = false;
		do {
			close = false;
			for(unsigned_b i = 0; i < m._map_walls.size(); i++){
				for(auto cls: closest_wall){
					if((is_close(m._map_walls.at(i), cls, 2 * safe_dist))){
						bool non_duplicate = true;
						for(auto chk: closest_wall)
							non_duplicate &= !is_duplicate(m._map_walls.at(i), chk);
						
						if(non_duplicate){
							closest_wall.push_back(m._map_walls.at(i)); close = true;}
						}
					}
				}
			} while(close);
	}
	// remove duplicates
	for(unsigned_b i = 0; i < closest_wall.size(); i++)
		for(unsigned_b j = 0; j < closest_wall.size(); j++)
			if(is_duplicate(closest_wall.at(i), closest_wall.at(j)) && i != j){
				closest_wall.erase(closest_wall.begin() + j);
				j = 0;
				}
	return closest_wall;
	}





void planner::avoid_get_points(std::vector<std::vector<coordinates>>& temporary, std::vector<wall>& closest_wall){
	constexpr decimal_n safe_dist = robot_radius * safe_constant;
	for(auto o: closest_wall){
		temporary.emplace_back(&o.properties.edges[0], &o.properties.edges[4]);
		}
	// erasing them for being too close
	//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
	for(unsigned_b i = 0; i < temporary.size(); i++){
		for(unsigned_b j = 0; j < temporary.at(i).size(); j++){
			bool erase = false;
			for(unsigned_b k = i + 1; k < temporary.size(); k++){
				for(unsigned_b l = 0; l < temporary.at(k).size(); l++){
					if(temporary.at(i).at(j).get_distance(temporary.at(k).at(l)) < (5e-2)){
						//~ std::cout << "ERASING - DISTANCE\n" << temporary.at(i).at(j).print() << std::endl;
						temporary.at(k).erase(temporary.at(k).begin() + l--);
						erase = true;
						}
					}
				}
			if(erase) temporary.at(i).erase(temporary.at(i).begin() + j--);
			}
		}
	//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
	// erasing them for touching other walls
	for(unsigned_b i = 0; i < closest_wall.size(); i++){
		//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
		//~ msg("i", std::to_string(i))
		for(unsigned_b j = 0; j < temporary.size(); j++){
			if(i != j){
				//~ msg("j", std::to_string(j))
				for(unsigned_b k = 0; k < temporary.at(j).size(); k++){
					//~ msg("k", std::to_string(k))
					if(step::get_distance(temporary.at(j).at(k), closest_wall.at(i)) < (2.5e-1)){
						//~ std::cout << "ERASING - WALL\n" << temporary.at(j).at(k).print() << std::endl;
						temporary.at(j).erase(temporary.at(j).begin() + k--);
						}
					}
				}
			}
		}
	//~ std::cout << "This " << __FILE__ << " " << __LINE__ << std::endl;
	/*
	// erasing them for being close to other walls
	for(unsigned_b i = 0; i < temporary.size(); i++){
		for(unsigned_b j = 0; j < temporary.size(); j++){
			if(i != j){
				for(unsigned_b k = 0; k < temporary.at(j).size(); k++){
					if(step::get_distance(temporary.at(j).at(k), closest_wall.at(i)) < 2 * safe_dist){
						//~ std::cout << "ERASING - WALL\n" << temporary.at(j).at(k).print() << std::endl;
						temporary.at(j).erase(temporary.at(j).begin() + k--);
						}
					}
				}
			}
		}*/
	}
