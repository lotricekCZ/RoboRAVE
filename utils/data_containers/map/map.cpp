/*
 * map.cpp
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


#include <algorithm>
#include <vector>
#include <array>
#include <iostream>
#include <stdexcept>
#include <opencv2/opencv.hpp>

#include "include.hpp"
#include "map.hpp"

#ifndef MAP_CPP
#define MAP_CPP

map::map(){
	//~ _map_obstacles.push_back(circle());
}

std::vector<location> map::grid(int s_height = 0, int s_width = 0, int height = 1000, int width = 1000) {
	
	int h = (s_height < height)? s_height : height, he = (s_height > height)? s_height : height, \
		w = (s_width < width)? s_width : width, we = (s_width > width)? s_width : width, \
		ht = h, wt = w;
	std::vector<location> b;
	
	while(ht <= he){
		while(wt <= we){
			b.push_back(location(ht, wt, location::_unknown));
			wt += map_raster;
			}
		wt = w;
		ht += map_raster;
		}
	return b;
	}
	
	
location map::interest_calculate(){
	std::vector<location> _map_priority;
	//~ _map_priority.assign(_map.begin(), _map.end());
	//~ int points = 0;
	for (auto& point: _map){
		point.set_interest(calculate_location(point));
		}
	//~ _map.assign(_map_priority.begin(), _map_priority.end());
	return interest_maximal(_map)._coordinates;
	}
	
	
decimal_n map::calculate_location(location lo){
	coordinates c = lo._coordinates;
	decimal_n x = c.x, y = c.y, distance = 0, interest = 0;
	
	//~ using variables::thresholds::explo;
	// scaled down part of map based on maximal range
	//~ std::cout << "\ncoords:\nx: " << c.x << "\ty: " << c.y << std::endl;
	for (auto o: _map){
		distance = lo.get_distance(o);
		if(distance <= (variables::thresholds::explo::influence::interesting * map_unit)){
			switch(o.get_point()){
				case location::_unknown:
					interest += (distance <= (variables::thresholds::explo::influence::unknown * map_unit)? \
									(1.0f - (distance / (variables::thresholds::explo::influence::unknown * map_unit))) * variables::thresholds::explo::objects::unknown : 0);
					break;
					
				case location::_candle:
					interest += (distance <= (variables::thresholds::explo::influence::candle * map_unit)? \
									(1.0f - distance / (variables::thresholds::explo::influence::candle * map_unit)) * variables::thresholds::explo::objects::candle : 0);
					break;
					
				case location::_interesting:
					interest += (distance <= (variables::thresholds::explo::influence::interesting * map_unit)? \
									(1.0f - distance / (variables::thresholds::explo::influence::interesting * map_unit)) * variables::thresholds::explo::objects::interesting : 0);
					break;
					
				case location::_barrier:
					interest += (distance <= (variables::thresholds::explo::influence::barrier * map_unit)? \
									(1.0f - distance / (variables::thresholds::explo::influence::barrier * map_unit)) * variables::thresholds::explo::objects::barrier : 0);
					break;
					
				case location::_discovered:
					interest += (distance <= (variables::thresholds::explo::influence::discovered * map_unit)? \
									(1.0f - distance / (variables::thresholds::explo::influence::discovered * map_unit)) * variables::thresholds::explo::objects::discovered : 0);
					break;
					
				case location::_boring:
					interest += (distance <= (variables::thresholds::explo::influence::boring * map_unit)? \
									(1.0f - distance / (variables::thresholds::explo::influence::boring * map_unit)) * variables::thresholds::explo::objects::boring : 0);
					break;
				}
				//~ interest += 			
			}
		switch(lo.get_point()){
				case location::_unknown:
					interest += variables::thresholds::explo::objects::unknown;
					break;
					
				case location::_candle:
					interest += variables::thresholds::explo::objects::candle;
					break;
					
				case location::_interesting:
					interest += variables::thresholds::explo::objects::interesting;
					break;
					
				case location::_barrier:
					interest +=  variables::thresholds::explo::objects::barrier;
					break;
					
				case location::_discovered:
					interest += variables::thresholds::explo::objects::discovered;
					break;
					
				case location::_boring:
					interest += variables::thresholds::explo::objects::boring;
					break;
				}
		}
		//~ interest ;
		return interest;
	}

location map::interest_maximal(std::vector<location> inmap){
	
	location max;
	
	max.set_interest( -1*(1<<21));
	for (auto o: inmap){
		//~ std::cout << "interest: " << o.get_interest() << std::endl;
		//~ std::cout << "x: " << o._coordinates.x << "  y: " << o._coordinates.y << std::endl;
		if(o.get_interest() > max.get_interest()){
			max = o;
			}
		}
	
	std::cout << "interest max: " << max.get_interest() << std::endl;
	return max;
	}
	
location map::interest_minimal(std::vector<location> inmap){
	
	location min;
	
	min.set_interest((1 << 22) - 1);
	for (auto o: inmap){
		//~ std::cout << "interest: " << o.get_interest() << std::endl;
		//~ std::cout << "x: " << o._coordinates.x << "  y: " << o._coordinates.y << std::endl;
		if(o.get_interest() < min.get_interest()){
			min = o;
			}
		}
	
	std::cout << "interest min: " << min.get_interest() << std::endl;
	return min;
	}
	
// function to show a map of interest

void map::interest_map(){
	
	std::sort(_map.begin(), _map.end(), [](location a, location b){return (a._coordinates.y < b._coordinates.y);});
	std::vector<location> same_y;
	decimal_n y = _map[0]._coordinates.y;
	
	for(auto i: _map){
		if(y == i._coordinates.y){
			same_y.push_back(i);
			}
		else {
			y = i._coordinates.y;
			std::sort(same_y.begin(), same_y.end(), [](location a, location b){return (a._coordinates.x < b._coordinates.x);});
			
			//~ for(auto o: same_y){
				//~ std::cout << "x:" << o._coordinates.x <<  "y: "<< o._coordinates.y << "\t";
				//~ }
			std::cout << "\n";
			for(auto o: same_y){
				std::cout << "" << o.get_interest() <<  "\t";
				}
				
			std::cout << "\n";
			same_y.clear();
			}
		}
	}
	
		
void map::append(location in){
	_map.push_back(in);
	if(in.classification.point_type == location::type::_interesting){
		_map_interesting.push_back(&_map.back());
		}
	}
	
void map::append(surround_circle in){
	_map_surround_circles.push_back(in);
	}
	
void map::append(candle in){
	_map_candles.push_back(in);
	}

void map::append(wall in){
	_map_walls.push_back(in);
	}

std::vector<location *> map::strip(std::array<coordinates, 2> limits){
	std::vector<location *> ret;
	coordinates ed[4] = {limits[0], coordinates(limits[0].x, limits[1].y), limits[1], coordinates(limits[1].x, limits[0].y)};
	wall r(ed);
	for(auto &i: _map){
		if(r.inside(i._coordinates)){
			std::cout << i._coordinates.print() << std::endl;
			ret.push_back(&i);
		}
	}
	return ret;
}

void map::edit_map(wall w){
	std::array<coordinates, 2> limits = w.get_box();
	std::vector<location *> edit_box = strip(w.get_box());
	for(auto a: edit_box){
		if(w.inside(a -> _coordinates)){
			a -> set_point(location::_barrier); // alterovani existujicixh bodu
			}
		}
	/// doplneni polovicnim rastrem
	for(decimal_n x = limits[1].x; x < limits[0].x; x += (map_raster/2)){
		for(decimal_n y = limits[1].y; y < limits[0].y; y += (map_raster/2)){
			coordinates c(x, y);
			if(w.inside(c)){
				std::cout << c.print() << std::endl;
				append(location(c, location::_barrier));
			}
		}		
	}
}

void map::edit_map(surround_circle w){
	std::array<coordinates, 2> limits = w.get_box();
	std::vector<location *> edit_box = strip(w.get_box());
	for(auto a: edit_box){
		if(w.inside(a -> _coordinates)){
			a -> set_point(location::_barrier); // alterovani existujicich bodu
			}
		}
	//~ std::cout << "\n\nrastr\n" << std::endl;
	//~ std::cout << limits[0].print() << std::endl;
	//~ std::cout << limits[1].print() << std::endl;
	/// doplneni polovicnim rastrem
	for(decimal_n x = limits[1].x; x < limits[0].x; x += (map_raster/2)){
		for(decimal_n y = limits[1].y; y < limits[0].y; y += (map_raster/2)){
			coordinates c(x, y);
			if(w.inside(c)){
				std::cout << c.print() << std::endl;
				append(location(c, location::_barrier));
			}
		}		
	}
}

void map::edit_map(candle w){
	std::array<coordinates, 2> limits = w.get_box();
	std::vector<location *> edit_box = strip(w.get_box());
	for(auto a: edit_box){
		if(w.inside(a -> _coordinates)){
			a -> set_point(location::_barrier); // alterovani existujicich bodu
			}
		}
	//~ std::cout << "\n\nrastr\n" << std::endl;
	//~ std::cout << limits[0].print() << std::endl;
	//~ std::cout << limits[1].print() << std::endl;
	/// doplneni polovicnim rastrem
	for(decimal_n x = limits[1].x; x < limits[0].x; x += (map_raster/2)){
		for(decimal_n y = limits[1].y; y < limits[0].y; y += (map_raster/2)){
			coordinates c(x, y);
			if(w.inside(c)){
				std::cout << c.print() << std::endl;
				append(location(c, location::_barrier));
			}
		}		
	}
}


wall map::closest_wall(coordinates c){
	decimal_n minimal_distance = std::numeric_limits<decimal_n>::infinity();
	wall *ret;
	for(auto &w: _map_walls){
		for(coordinates edges: w.properties.edges){
			decimal_n current = c.get_distance(edges);
			if(minimal_distance > current){
				minimal_distance = current;
				ret = &w;
				}
			}
		}
	return *ret;
	}


candle map::closest_candle(coordinates c){
	decimal_n minimal_distance = std::numeric_limits<decimal_n>::infinity();
	candle *ret;
	for(auto &cn: _map_candles){
		decimal_n current = c.get_distance(cn.tube.center);
		if(minimal_distance > current){
			minimal_distance = current;
			ret = &cn;
			}
		}
	
	return *ret;
	}

std::vector<coordinates> map::collidors(circle c, collidor_types cols){
	std::vector<coordinates> ret;
	if((cols & collidor_types::walls) == collidor_types::walls){
		for(wall w: _map_walls){
			if(w.closest_point(c.center).get_distance(c.center) <= c.radius){
				std::vector<coordinates> curr = w.is_collision_course(c);
				ret.insert(ret.end(), curr.begin(), curr.end());
				}
			}
		}
	if((cols & collidor_types::candles) == collidor_types::candles){
		for(candle ca: _map_candles){
			if(ca.tube.radius + c.radius < c.center.get_distance(ca.tube.center)){
				std::vector<coordinates> curr = ca.is_collision_course(c);
				ret.insert(ret.end(), curr.begin(), curr.end());
				}
			}
		}
		
	if((cols & collidor_types::surround_circles) == collidor_types::surround_circles){
		for(surround_circle su: _map_surround_circles){
			if(su.outer.radius + c.radius < c.center.get_distance(su.outer.center)){
				std::vector<coordinates> curr = su.is_collision_course(c);
				ret.insert(ret.end(), curr.begin(), curr.end());
				}
			}
		}
		
	/// TODO: Other objects 
	return ret;
	}
	
std::vector<coordinates> map::collidors(line l, collidor_types cols){
	std::vector<coordinates> ret;
	if((cols & collidor_types::walls) == collidor_types::walls){
		for(wall w: _map_walls){
			std::vector<coordinates> curr = w.is_collision_course(l);
			ret.insert(ret.end(), curr.begin(), curr.end());
			}
		}
	if((cols & collidor_types::candles) == collidor_types::candles){
		for(candle ca: _map_candles){
			std::vector<coordinates> curr = ca.is_collision_course(l);
			ret.insert(ret.end(), curr.begin(), curr.end());
			}
		}
		
	if((cols & collidor_types::surround_circles) == collidor_types::surround_circles){
		for(surround_circle su: _map_surround_circles){
			std::vector<coordinates> curr = su.is_collision_course(l);
			ret.insert(ret.end(), curr.begin(), curr.end());
			}
		}
		
	/// TODO: Other objects 
	return ret;
	}

std::array<std::vector<location*>, 4> map::subdivide(coordinates c, decimal_n angle, location::type selected_type){
	std::array<std::vector<location*>, 4> ret;
	coordinates local;
	if(selected_type == location::type::_interesting){
		for(location* l: _map_interesting){
			local = c.make_local(l -> _coordinates, angle);
			ret[((local.x > 0) << 1) | ((local.y > 0))].push_back(l);
			}
	} else {
		for(location &l: _map){
			if(l.classification.point_type == selected_type){
				local = c.make_local(l._coordinates, angle);
				ret[((local.x > 0) << 1) | ((local.y > 0))].push_back(&l);
				}
			}
		}
	return ret;	
	}

void map::show_map(){
	std::sort(_map.begin(), _map.end(), [](location a, location b){return (a._coordinates.y < b._coordinates.y);});
	cv::namedWindow("map preview", cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO | cv::WINDOW_GUI_EXPANDED);
	cv::Mat map_view(map_h/15+1, map_l/15+1, CV_8UC3, cv::Scalar(40, 40, 0));
	std::cout << "posledni:\t" << _map.back()._coordinates.print() << std::endl;
	signed_b maximum = interest_maximal(_map).get_interest();
	signed_b minimum = interest_minimal(_map).get_interest();
	std::cout << "passed" << std::endl;
	for(auto element: _map){
		try{
			//~ std::cout << 255.0f - (((decimal_n)element.get_interest())/((decimal_n)(maximum - minimum))) << std::endl;
			signed_b interest = element.get_interest();
			signed_b color = (255 * (1 -(((decimal_n)interest)/((decimal_n)(maximum - minimum)))));
			map_view.at<cv::Vec3b>(cvRound(element._coordinates.y/15), cvRound(element._coordinates.x/15)) = cv::Vec3b((interest < 0? color: 0), 0, (interest >= 0? color: 0));
			//~ cv::putText(map_view, "[" + std::to_string(cvRound(element._coordinates.y)) + "; " + std::to_string(cvRound(element._coordinates.x))+"]", cv::Point(element._coordinates.y*5 + 1, element._coordinates.x*5 + 1), cv::FONT_HERSHEY_PLAIN, 0.75, cv::Scalar(0, 0, color, 40));
			} catch(std::exception e) {
				std::cout << "uh oh..." << std::endl;
				}
		}
	cv::imshow("map preview", map_view);
	while(cv::waitKey() != 27){};
	}

#endif
