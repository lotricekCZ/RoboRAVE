/*
 * angles.cpp
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


#include "angles.hpp"


angles::angles()
	: std::vector<node>()
{
	for(unsigned_n i = 0; i < 360; i ++){
		emplace_back(0.0f, (decimal_n)i);
		}
	std::sort(this -> begin(), this -> end(), [](node a, node b){return (a.angle < b.angle);});
}

node angles::get_angle(unsigned_n angle){
	//~ std::cout << angle << std::endl;
	for(unsigned_n i = 0; i < (this -> size() -1); i++){
		if(at(i).angle == angle){
			//~ std::cout << at(i).get_angle() << at(i).position._coordinates.print() << std::endl;
			//~ std::cout << "podminka splnena " << i << std::endl;
			return at(i);
			}
		}
	return node(-1);
	}
	
angles::~angles()
{
	
}

angles angles::load_virtual_circular(coordinates c, map &m, decimal_n min, decimal_n max, decimal_n step = 10){
	angles ret;
	std::vector<bool> crossed; 
	crossed.resize(360);
	std::vector<coordinates> intersects_an;
	
	for(decimal_n i = min; i < max; i += step){
		//~ std::cout << i << std::endl;
		circle k(c, i);
		for(auto a: m._map_walls){ // to get all possible intersections with walls
			std::vector<coordinates> in = a.is_collision_course(k);
			intersects_an.insert(std::end(intersects_an), std::begin(in), std::end(in));
			}
	} // nasbirani vsech bodu dotyku
	
	//~ coordinates nx(c.x+1, c.y);
	//~ coordinates ny(c.x, c.y+1);
	
	for(auto a: intersects_an){
		// potrebuju jejich lokalni souradnice
		coordinates d = a-c;
		decimal_n to_a = c.get_distance(a);
		//~ std::cout << d.x << "\t" << d.y << "\t" << (d.y < 0) << "\t" << ((d.y < 0)? 360:0) + ((atan2f(d.y, d.x)*180)/pi) <<"\t";
		signed_n ang = ((d.y < 0)? 360:0) + atan2f(d.y, d.x)*180/pi_const;
		//~ std::cout << ang << std::endl;
		if(ret[ang].distance > to_a || ret[ang].distance == 0){
			crossed[ang] = 1;
			ret[ang] = node(ang, a);
			ret[ang].distance = to_a;
			ret[ang].position.classification.point_type = location::_barrier;
		}
		//
	} // filtrovani vsech bodu dotyku
	
	for(signed_n i = 359; i >= 0; i--){
		//~ std::cout << ret[i].angle << "\t" << ret[i].distance << "\t" << ret[i].position._coordinates.print() << std::endl;
		if(ret[i].distance == 0 || ret[i].distance >= MAX_DISTANCE || \
			ret[i].position._coordinates.get_distance(c) >= MAX_DISTANCE || \
			ret[i].position._coordinates == coordinates(0, 0) || !crossed[i]){
			ret.erase(ret.begin() + i);
			
			}
		}
		//~ std::cout << "outcome end" << std::endl;
	
	std::sort(ret.begin(), ret.end(), [](node a, node b){return (a.angle < b.angle);});
	return ret;
}

// loads the virtual angles on any coordinate on the map... Well at least this is what it should do and partially does
angles angles::load_virtual(coordinates a, map &m){
	angles ret;
	std::vector<bool> crossed; 
	crossed.resize(360);
	for(unsigned_n i = 0; i < 180; i ++){
		std::vector<coordinates> intersects_an; // all the places that are intersected on map
		
		coordinates n = a+a.make_local(1, (decimal_n)i / 180.0 * pi_const);
		line l(a, n);
		
		for(auto k: m._map_walls){ // to get all possible intersections with walls
			std::vector<coordinates> in = k.is_collision_course(l);
			intersects_an.insert(std::end(intersects_an), std::begin(in), std::end(in));
			}
		/// TODO: optimize this war crime
		for(auto k: intersects_an){
			if(k.x != std::numeric_limits<float>::infinity()){
				decimal_n to_a = a.get_distance(k);
				decimal_n to_n = n.get_distance(k);
				if(to_a < to_n){ // to znamena, ze je na opacne strane, nez co beha iterator
					if(ret[i+180].distance > to_a || ret[i+180].distance == 0){
						ret[i+180] = node(i+180, k);
						ret[i+180].distance = to_a;
						ret[i+180].position.classification.point_type = location::_barrier;
						crossed[i+180] = 1;
						}
					} else {
						if(ret[i].distance > to_a || ret[i].distance == 0){
							crossed[i] = 1;
							ret[i] = node(i, k);
							ret[i].distance = to_a;
							ret[i].position.classification.point_type = location::_barrier;
							}
						}
				
				}
			}
			
		}
		//~ std::cout << "outcome" << std::endl;
	for(signed_n i = 359; i >= 0; i--){
		//~ std::cout << ret[i].angle << "\t" << ret[i].distance << "\t" << ret[i].position._coordinates.print() << std::endl;
		if(ret[i].distance == 0 || ret[i].distance >= MAX_DISTANCE || \
			ret[i].position._coordinates.get_distance(a) >= MAX_DISTANCE/* || \
			ret[i].position._coordinates == coordinates(0, 0)*/){
			//~ std::cout << ret[i].angle << "\t" << ret[i].distance << "\t" << ret[i].position._coordinates.print() << std::endl;
			ret.erase(ret.begin() + i);
			}
		}
		//~ std::cout << "outcome end" << std::endl;
	
	std::sort(ret.begin(), ret.end(), [](node a, node b){return (a.angle < b.angle);});
	return ret;
	}

