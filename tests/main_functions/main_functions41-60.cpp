/*
 * main_functions21-40.cpp
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


#include "main_functions21-40.hpp"

namespace mf {
	void function41(int argc, char *argv[]){
		#ifndef dont_comp
		std::cout << step(coordinates(3, 5), coordinates(-5, 1), coordinates(0, 1)).print_geogebra() << std::endl;
		return;
		#endif 
		}
		
	void function42(int argc, char *argv[]){
		#ifndef dont_comp
		std::cout << step(coordinates(3, 5), coordinates(-5, 1)).print_geogebra() << std::endl;
		return;
		#endif 
		}
		
	void function43(int argc, char *argv[]){
		#ifndef dont_comp
		std::cout << step(coordinates(c_f(argv[3]), c_f(argv[4])), coordinates(c_f(argv[5]), c_f(argv[6])), coordinates(0, 1), c_i(argv[2])).print_geogebra() << std::endl;
		std::vector<coordinates> out = step::intersection(step(coordinates(c_f(argv[3]), c_f(argv[4])), coordinates(c_f(argv[5]), c_f(argv[6])), coordinates(0, 1), c_i(argv[2])), circle(coordinates(4, -7), 6));
		std::cout << "velikost: " << out.size() << std::endl;
		for(auto a: out)
			std::cout << a.print_geogebra() << std::endl;
		return;
		#endif 
		}
		
	void function44(int argc, char *argv[]){
		#ifndef dont_comp
		std::cout << step(coordinates(c_f(argv[3]), c_f(argv[4])), coordinates(c_f(argv[5]), c_f(argv[6])), coordinates(0, 1), c_i(argv[2])).print_geogebra() << std::endl;
		std::cout << line(-3, 8, -4).print() << std::endl;
		std::vector<coordinates> out = step::intersection(step(coordinates(c_f(argv[3]), c_f(argv[4])), coordinates(c_f(argv[5]), c_f(argv[6])), coordinates(0, 1), c_i(argv[2])), line(-3, 8, -4));
		std::cout << "velikost: " << out.size() << std::endl;
		for(auto a: out)
			std::cout << a.print_geogebra() << std::endl;
		return;
		#endif 
		}
		
	void function45(int argc, char *argv[]){
		#ifndef dont_comp
		std::cout << step(coordinates(c_f(argv[3]), c_f(argv[4])), coordinates(c_f(argv[5]), c_f(argv[6])), coordinates(0, 1), c_i(argv[2])).print_geogebra() << std::endl;
		std::cout << step(coordinates(c_f(argv[7]), c_f(argv[8])), coordinates(c_f(argv[9]), c_f(argv[10])), coordinates(4, -7), c_i(argv[11])).print_geogebra() << std::endl;
		std::vector<coordinates> out = step::intersection(
										step(coordinates(c_f(argv[3]), c_f(argv[4])), coordinates(c_f(argv[5]), c_f(argv[6])), coordinates(0, 1), c_i(argv[2])), 
										step(coordinates(c_f(argv[7]), c_f(argv[8])), coordinates(c_f(argv[9]), c_f(argv[10])), coordinates(4, -7), c_i(argv[11])));
		std::cout << "velikost: " << out.size() << std::endl;
		for(auto a: out)
			std::cout << a.print_geogebra() << std::endl;
		return;
		#endif 
		}
		
	void function46(int argc, char *argv[]){
		#ifndef dont_comp
		std::cout << step(coordinates(c_f(argv[3]), c_f(argv[4])), coordinates(c_f(argv[5]), c_f(argv[6])), coordinates(0, 1), c_i(argv[2])).print_geogebra() << std::endl;
		std::cout << step(coordinates(c_f(argv[7]), c_f(argv[8])), coordinates(c_f(argv[9]), c_f(argv[10]))).print_geogebra() << std::endl;
		std::vector<coordinates> out = step::intersection(
										step(coordinates(c_f(argv[3]), c_f(argv[4])), coordinates(c_f(argv[5]), c_f(argv[6])), coordinates(0, 1), c_i(argv[2])), 
										step(coordinates(c_f(argv[7]), c_f(argv[8])), coordinates(c_f(argv[9]), c_f(argv[10]))));
		std::cout << "velikost: " << out.size() << std::endl;
		for(auto a: out)
			std::cout << a.print_geogebra() << std::endl;
		return;
		#endif 
		}

	void function47(int argc, char *argv[]){
		#ifndef dont_comp
		std::cout << step(coordinates(c_f(argv[3]), c_f(argv[4])), coordinates(c_f(argv[5]), c_f(argv[6])), coordinates(0, 1), c_i(argv[2])).print_geogebra() << std::endl;
		std::cout << step(coordinates(c_f(argv[7]), c_f(argv[8])), coordinates(c_f(argv[9]), c_f(argv[10]))).print_geogebra() << std::endl;
		std::vector<coordinates> out = step::intersection(
										step(coordinates(c_f(argv[3]), c_f(argv[4])), coordinates(c_f(argv[5]), c_f(argv[6])), coordinates(0, 1), c_i(argv[2])), 
										step(coordinates(c_f(argv[7]), c_f(argv[8])), coordinates(c_f(argv[9]), c_f(argv[10]))));
		std::cout << "velikost: " << out.size() << std::endl;
		for(auto a: out)
			std::cout << a.print_geogebra() << std::endl;
		return;
		#endif 
		}

	void function48(int argc, char *argv[]){
		#ifndef dont_comp
		step s = step(coordinates(c_f(argv[3]), c_f(argv[4])), coordinates(c_f(argv[5]), c_f(argv[6])), coordinates(0, 1), c_i(argv[2]));
		coordinates c = coordinates(c_f(argv[7]), c_f(argv[8]));
		std::cout << s.print_geogebra() << std::endl;
		std::cout << c.print_geogebra() << std::endl;
		std::cout << step::get_distance(s, c, c_i(argv[9])) << std::endl;
		return;
		#endif 
		}

	void function49(int argc, char *argv[]){
		#ifndef dont_comp
		step s = step(coordinates(c_f(argv[3]), c_f(argv[4])), coordinates(c_f(argv[5]), c_f(argv[6])));
		coordinates c = coordinates(c_f(argv[7]), c_f(argv[8]));
		std::cout << s.print_geogebra() << std::endl;
		std::cout << c.print_geogebra() << std::endl;
		std::cout << step::get_distance(s, c, c_i(argv[2])) << std::endl;
		return;
		#endif 
		}
		
	void function50(int argc, char *argv[]){
		#ifndef dont_comp // distance of two linear steps ./roborave 50  0   0 3 2 1  6 5 2 -5 1
		step s = step(coordinates(c_f(argv[3]), c_f(argv[4])), coordinates(c_f(argv[5]), c_f(argv[6])), coordinates(0, 1), c_i(argv[2]));
		step c = step(coordinates(c_f(argv[7]), c_f(argv[8])), coordinates(c_f(argv[9]), c_f(argv[10])));
		std::cout << s.print_geogebra() << std::endl;
		std::cout << c.print_geogebra() << std::endl;
		for(uint16_t i = 0; i < 65000; i++){
			step::get_distance(s, c);
			}
		std::cout << step::get_distance(s, c, 0) << std::endl;
		return;
		#endif 
		}
		
	void function51(int argc, char *argv[]){
		#ifndef dont_comp // distance of two linear steps ./roborave 51  0   0 3 2 1  6 5 2 -5 1
		step s = step(coordinates(c_f(argv[2]), c_f(argv[3])), coordinates(c_f(argv[4]), c_f(argv[5])));
		step c = step(coordinates(c_f(argv[6]), c_f(argv[7])), coordinates(c_f(argv[8]), c_f(argv[9])));
		std::cout << s.print_geogebra() << std::endl;
		std::cout << c.print_geogebra() << std::endl;
		for(uint16_t i = 0; i < 65000; i++){
			step::get_distance(s, c);
			}
		std::cout << step::get_distance(s, c) << std::endl;
		return;
		#endif 
		}
		
	void function52(int argc, char *argv[]){
		#ifndef dont_comp // distance of two circular steps ./roborave 52  0   -2 1 2 1  0 1 4 1 2 1 1 1
		step s = step(coordinates(c_f(argv[3]), c_f(argv[4])), coordinates(c_f(argv[5]), c_f(argv[6])), coordinates(0, 1), c_i(argv[2]));
		step c = step(coordinates(c_f(argv[7]), c_f(argv[8])), coordinates(c_f(argv[9]), c_f(argv[10])), coordinates(c_f(argv[11]), c_f(argv[12])), c_i(argv[13]));
		std::cout << s.print_geogebra() << std::endl;
		std::cout << c.print_geogebra() << std::endl;
		for(uint16_t i = 0; i < 65000; i++){
			step::get_distance(s, c);
			}
		std::cout << step::get_distance(s, c, c_i(argv[14])) << std::endl;
		return;
		#endif 
		}
		
	void function53(int argc, char *argv[]){
		#ifndef dont_comp
		coordinates x[] = {coordinates(1, 1), coordinates(0, 2), coordinates(4, 6), coordinates(5, 5)};
		step s(coordinates(c_f(argv[2]), c_f(argv[3])), coordinates(c_f(argv[4]), c_f(argv[5])));
		std::cout << s.print_geogebra() << std::endl;
		std::cout << step::get_distance(s, wall(x)) << std::endl;
		return;
		#endif 
		}
		
	void function54(int argc, char *argv[]){
		#ifndef dont_comp
		coordinates x[] = {coordinates(1, 1), coordinates(0, 2), coordinates(4, 6), coordinates(5, 5)};
		step s(coordinates(c_f(argv[2]), c_f(argv[3])), coordinates(c_f(argv[4]), c_f(argv[5])), coordinates(c_f(argv[6]), c_f(argv[7])), c_i(argv[8]));
		std::cout << s.print_geogebra() << std::endl;
		std::cout << step::get_distance(s, wall(x)) << std::endl;
		return;
		#endif 
		}
		
	void function55(int argc, char *argv[]){
		#ifndef dont_comp // show map as opencv mat
		map m;
		uint8_t c = 8;
		std::vector<std::future < std::vector<location> > > o;
		for (uint8_t t = 0; t < c; t ++){
			o.push_back(std::move(std::async(&map::grid, m, t * c_i(argv[2]) / c, 0, ((t+1) * c_i(argv[2]) / c), c_i(argv[3]))));
			
			}
		for (auto &i: o){
			std::vector<location> out = i.get();
			
			m._map.insert(m._map.begin(), out.begin(), out.end());
			
		}
		if(argc >= 5){
			m.append(candle(coordinates(300,450)));
			m.append(candle(coordinates(600,600)));
			m.edit_map(m._map_candles.at(0));
			m.edit_map(m._map_candles.at(1));
		}
		//~ m.edit_map(candle(coordinates(600,600)));
		//~ m.edit_map(candle(coordinates(310,450)));
		//~ m.edit_map(candle(coordinates(320,450)));
		//~ m.edit_map(candle(coordinates(321,450)));
		std::cout << "pocet " << m._map.size() << std::endl;
		location loo = m.interest_calculate();
		m.show_map();
		return;
		#endif 
		}
	
	void function56(int argc, char *argv[]){
		#ifndef dont_comp
		map m;
		coordinates x[] = {coordinates(1, 1), coordinates(0, 2), coordinates(4, 6), coordinates(5, 5)};
		//~ m.append(candle(coordinates(4,3)));
		m.append(wall(x));
		//~ for(wall w: m._map_walls)
			//~ std::cout << w.print_geogebra() << std::endl;
		
		planner p;
		step s(coordinates(-5, 2), coordinates(c_f(argv[2]), c_f(argv[3])));
		step circular_first(s.start.make_global(coordinates(0, 0), s.start.get_gamma(s.end) - pi_const/2), 
							s.start.make_global(coordinates(-3, -3), s.start.get_gamma(s.end) - pi_const/2),
							s.start.make_global(coordinates(0, -3), s.start.get_gamma(s.end) - pi_const/2), 0);
							
		step circular_second(s.end.make_global(coordinates(0, 0), s.start.get_gamma(s.end) - pi_const/2), 
							s.end.make_global(coordinates(3, 3), s.start.get_gamma(s.end) - pi_const/2),
							s.end.make_global(coordinates(0, 3), s.start.get_gamma(s.end) - pi_const/2), 0);

		std::cout << circular_first.print_geogebra() << std::endl;
		std::cout << circular_second.print_geogebra() << std::endl;
		
		std::vector<step> previous({circular_first, s, circular_second});
		std::vector<step> next({s});
		
		for (auto a: p.extend(next, previous, std::get<circle>(circular_second.formula), m))
			std::cout << a.print_geogebra() << std::endl;
		
		return;
		#endif 
		}
		
	void function57(int argc, char *argv[]){
		#ifndef dont_comp
		map m;

		coordinates c[] = {coordinates(-10, 3), coordinates(-11, 4), coordinates(-7, 8), coordinates(-6, 7)};
		coordinates x[] = {coordinates(1, 1), coordinates(0, 2), coordinates(4, 6), coordinates(5, 5)};
		coordinates y[] = {coordinates(-1, 1), coordinates(0, 2), coordinates(4, -2), coordinates(3, -3)};
		coordinates z[] = {coordinates(4, 6), coordinates(5, 7), coordinates(9, 3), coordinates(8, 2)};
		//~ m.append(candle(coordinates(4,3)));
		m.append(wall(c));
		m.append(wall(x));
		m.append(wall(y));
		for(wall w: m._map_walls)
			std::cout << w.print_geogebra() << std::endl;
		return;
		#endif 
		}
		
	void function58(int argc, char *argv[]){
		#ifndef dont_comp
		map m;

		//~ coordinates c[] = {coordinates(-10, 3), coordinates(-11, 4), coordinates(-7, 8), coordinates(-6, 7)};
		coordinates x[] = {coordinates(1, 1), coordinates(0, 2), coordinates(4, 6), coordinates(5, 5)};
		//~ coordinates y[] = {coordinates(-1, 1), coordinates(0, 2), coordinates(4, -2), coordinates(3, -3)};
		//~ coordinates z[] = {coordinates(4, 6), coordinates(5, 7), coordinates(9, 3), coordinates(8, 2)};
		//~ m.append(candle(coordinates(4,3)));
		//~ m.append(wall(c));
		step s(coordinates(-5, 2), coordinates(c_f(argv[2]), c_f(argv[3])));
		m.append(wall(x));
		//~ m.append(wall(y));
		for(auto w: step::get_distances(s, m._map_walls.at(0)))
			std::cout << w << std::endl;
		return;
		#endif 
		}
		
	void function59(int argc, char *argv[]){
		#ifndef dont_comp
		//~ std::cout << vector(coordinates(4, 0), coordinates(12, 5), c_i(argv[2]), c_i(argv[3])).print() << std::endl;
		//~ std::cout << vector(coordinates(4, 0), 9.433981, 0.558599, c_i(argv[2])).print() << std::endl;
		//~ std::cout << vector(9.43398113, -0.558599315, c_i(argv[2])).print() << std::endl;
		std::cout << vector(coordinates(4, 0), coordinates(12, 5)).print() << std::endl;
		std::cout << vector(coordinates(6, 4), coordinates(9, -5)).print() << std::endl;
		std::cout << (vector(coordinates(4, 0), coordinates(12, 5)) << vector(coordinates(6, 4), coordinates(9, -5))).print() << std::endl;
		return;
		#endif 
		}
		
	void function60(int argc, char *argv[]){
		#ifndef dont_comp
		//~ std::cout << vector(coordinates(4, 0), coordinates(12, 5)).print() << std::endl;
		//~ std::cout << vector(coordinates(6, 4), coordinates(9, -5)).print() << std::endl;
		//~ std::cout << (vector(coordinates(4, 0), coordinates(12, 5)) + vector(coordinates(6, 4), coordinates(9, -5))).print() << std::endl;
		std::cout << (vector(coordinates(-4, 0), coordinates(12, 5)) * 2.0f).print() << std::endl;
		std::cout << vector(coordinates(4, 0), coordinates(12, 5)).print() << std::endl;
		std::cout << vector(coordinates(4, 0), coordinates(-4, 5)).print() << std::endl;
		std::cout << (vector(coordinates(4, 0), coordinates(12, 5)) + vector(coordinates(4, 0), coordinates(-4, 5))).print() << std::endl;
		return;
		#endif 
		}
};
