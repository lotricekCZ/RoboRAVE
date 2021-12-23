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
	for(auto o: options)
		std::cout << o.print() << std::endl;
	
	/// TODO: THIS SECTION
	
	std::cout << std::endl;
	std::cout << options.size() << std::endl;
		
	
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



std::vector<path> planner::list_options(std::vector<circle> selected, coordinates end, coordinates start, decimal_n initial_rotation){
	assert(selected.front().is_on(start));
	
	std::vector<path> ret;
	for(auto coord: selected.back().tangent_points(end)) // all the variants of connecting to an end
		ret.emplace_back(step(coord, end));
	for(unsigned_b circ = 1; circ < selected.size(); circ++){ // every circle...
		for(unsigned_b pth = ret.size(); pth-- > 0;){ // every current option
			for(line tr: circle::circle_tangents(selected.at(selected.size() - (circ)), selected.at(selected.size() - (circ + 1)))){
				coordinates end = tr.intersection(tr.make_perpendicular(selected.at(selected.size() - (circ)).center));
				coordinates start = tr.intersection(tr.make_perpendicular(selected.at(selected.size() - (circ + 1)).center));
				coordinates center_local = coordinates::make_local(selected.at(selected.size() - (circ)).center, 
																	ret.at(pth).back().start, 
																	-ret.at(pth).back().angle_start);
				// local center by start of the step before and angle of that step
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




path planner::avoid(path p, map &m){
	assert(p.size() <= 2 && p.back()._type == step::line_e); 
	constexpr decimal_n safe_dist = robot_radius * safe_constant;
	// there must be only one step in order to give the 
	// idea which step should be modified with which parameters
	/// 0(): acknowledge if there are any close_points available
	
	std::vector<planner::wall_container> 
	close_points = planner::avoid_linear_phase_0(p, m);
	
	/// selected all where it either collides or comes close
	// selects the closest wall
	
	auto closest = planner::avoid_linear_wall_select(close_points.at(0));
	if(!closest.second.size()) return p;
	wall closest_wall = *std::get<wall *>(closest.second.at(0));
	//~ wall closest_wall;
	
	/// 1(): lead point vectors from edges to line
	std::array<std::deque<vector>, 2> sides({std::deque<vector>({vector(), vector()}), 
											std::deque<vector>({vector(), vector()})}); // and here we'll try a little bit of insert_sort
	std::cout << closest_wall.print_geogebra() << std::endl;
	line original = std::get<line>(p.back().formula);
	// we have the closest relevant wall, time to generate point vectors.
	{
		auto point_vectors = step::get_point_vectors(original, closest_wall);
		for(auto &o: point_vectors){
			bool index = (std::sin(o.angle() - (closest.first -> angle_start)) >= 0);
			for(uint8_t i = 0; i < 2; i++){
				if(sides.at(index).at(i).length() < o.length()){
					sides.at(index).insert(sides.at(index).begin() + i, o);
					break;
					}
				}
			if(sides.at(index).size() > 2) sides.at(index).pop_back();
			}
	}
	
	decimal_n decision = ((std::accumulate(sides.at(0).begin(), sides.at(0).end(), vector(0, 0))/(2)).length() - (std::accumulate(sides.at(1).begin(), sides.at(1).end(), vector(0, 0))/(2)).length());
	
	/// 2():
	std::vector<coordinates> *tmp = new std::vector<coordinates>(planner::avoid_linear_phase_2(closest_wall, sides.at(decision > 0), p.back()));
	if(tmp -> size() != 1){
		delete tmp;
		return p;
		}
	
	/// 3():
	std::vector<circle> curve({circle(p.back().start, 0), circle(tmp -> at(0), safe_dist)});
	
	std::cout << "selected\n" << curve.at(0).print() << std::endl;
	for(auto i: sides.at(decision > 0)){
		std::cout << i.print() << std::endl;
		}
	delete tmp;
	/// 4():
	std::vector<path> replacement = planner::list_options(curve, p.back().end, p.back().start, p.back().angle_start);
	for(auto r: replacement){
		if(!r.back().intersection(closest_wall).size())
		std::cout << "cesta\n" << r.print() << std::endl;
		}
		
	for(auto [stp, w]: close_points){
		std::cout << "step\n"  << stp -> print_geogebra() << "\nvelikost " << w.size() << std::endl;
		for(unsigned_b i = 0; i < w.size(); i++){
			for(auto c: std::get<1>(w.at(i))){
				std::cout << c.print() << std::endl;
				}
			
			for(auto v: std::get<2>(w.at(i))){
				std::cout << v.print() << std::endl;
				}
			}
		
		}
	return p;
	}




std::vector<std::pair<std::vector<coordinates>, wall>> planner::intersecting_walls(step s, map &m){
	std::vector<std::pair<std::vector<coordinates>, wall>> ret;
	std::vector<coordinates> ret_c;
	for(auto w: m._map_walls){
		ret_c = s.intersection(w);
		if(ret_c.size())
			ret.emplace_back(ret_c, w);
		}
	std::cout << "this runned " << ret.size() << std::endl;
	return ret;
	}




std::vector<planner::wall_container> 
	planner::avoid_linear_phase_0(path &p, map &m){
	constexpr decimal_n safe_dist = robot_radius * safe_constant;
	std::vector<planner::wall_container> close_points;
	for(auto &s: p){
		close_points.emplace_back(&s, std::vector<std::tuple<wall *,
												std::vector<coordinates>, 
												std::vector<vector>>>());
		for(auto &w: m._map_walls){
			close_points.back().second.emplace_back(&w, 
								close_points.back().first -> intersection(w),
								close_points.back().first -> get_vectors(w));
			}
		}
		
	for(auto &[stp, w]: close_points){
		std::cout << "step\n"  << stp -> print_geogebra() << "\nvelikost " << w.size() << std::endl;
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
			std::cout << l.intersection(p.make_parallel(c)).print() << std::endl;
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
		std::cout << step(o.get_origin(), s.end).intersection(w).size() << std::endl;
		for(auto i: step(o.get_origin(), s.end).intersection(w)){
			std::cout << i.print() << std::endl;
			}
		auto cand = [&](std::vector<coordinates> inter, coordinates c){
			decimal_n ret = 0;
			std::vector<coordinates> st = inter;
			st.push_back(c);
			
			for(uint8_t i = 0; i < st.size(); i++){
				std::cout << st.at(i).print() << std::endl;
				ret += st.at(i).get_distance(st.at((i + 1) % st.size()));
				}
			return ret;
			};
		auto l = step(o.get_origin(), s.end).intersection(w);
		unsigned_b ass_ic = l.size();
		decimal_n ass_c = cand(l, o.get_origin());
		if(ass_c <= min && ass_c < 1e-2 && ass_ic <= 2 && ass_ic > 0){
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
	
	
/*
auto planner::avoid_circular_phase_0(){
	constexpr decimal_n safe_dist = robot_radius * safe_constant;
	
	return 1.0f;
	}
	
	
	
auto planner::avoid_circular_phase_1(){
	constexpr decimal_n safe_dist = robot_radius * safe_constant;
	
	return 1.0f;
	}
*/
