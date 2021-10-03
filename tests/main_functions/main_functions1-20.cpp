/*
 * main_functions1-20.cpp
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


#include "main_functions1-20.hpp"

namespace mf {
	
	
	
	void function1(){
		#ifndef dont_comp
		log_writer("dear Odin, fuck you", "general.txt");
		#endif
		}
		
		
	void function2(int argc, char *argv[]){
		#ifndef dont_comp
		printf("result %.10f\n", calculate_T_avg(c_f(argv[2]), c_f(argv[3])));
		#endif
		}
		
		
	void function3(int argc, char *argv[]){
		#ifndef dont_comp
		printf("result %.10f\n", get_radius(c_f(argv[2]), c_f(argv[3])));
		#endif
		}
		
		
	void function4(int argc, char *argv[]){
		#ifndef dont_comp
		coordinates a(-1, -2);
			coordinates b(1, -1);
			// ocekavane - 3, 4
			decimal_n ang = -pi_const/2;
			switch(c_i(argv[2])){
				case 0:
					ang = pi_const/4;
					break;
				case 1:
					ang = 3*pi_const/4;
					break;
				case 2:
					ang = 5*pi_const/4;
					break;
				case 3:
					ang = 7*pi_const/4;
					break;
				case 4:
					ang = pi_const;
					break;
				case 5:
					ang = pi_const/2.0;
					break;
				case 6:
					ang = -pi_const/2.0;
					break;
				default:
					ang = 0;
					break;
				
				}
			coordinates c = c.make_global(a, b, -3*pi_const/4);
			std::cout << c.print() << std::endl;
			c = c.make_local(c, a, 3*pi_const/4);
			std::cout << c.print() << std::endl;
			
			c = c.make_local(sqrt(5), -atan(1.0/2.0));
			std::cout << c.print() << std::endl;
			//~ c = c.make_global(a, sqrt(5), pi/2 + atan(2));
			//~ std::cout << c.x << "; " << c.y << std::endl;
			//~ std::fstream f("t_1.svg", std::ios_base::app);
			//~ for(uint8_t i = 0; i < 60; i++){
				//~ c = c.make_global(a, coordinates(0, 4), -pi/2 + (decimal_n)i*1.6*(pi/180.0));
				//~ f << "<circle r=\"0.7080836\" cy=\""<< std::to_string(80.240021 + c.y*13) \
					//~ <<"\" cx=\"" << std::to_string(93.624962 + c.x*13) << "\"style=\"fill:#000000;stroke:none;stroke-width:22.1243;stroke-miterlimit:4;stroke-dasharray:none\"id=\"path2"<< std::to_string(i)<<"\" />" << std::endl;
				
				//~ c = c.make_global(a, coordinates(4, 2), +pi/2+(decimal_n)i*(pi/180.0));
				//~ f << "<circle r=\"1.080836\" cy=\""<< std::to_string(80.240021 + c.y*10) \
					//~ <<"\" cx=\"" << std::to_string(93.624962 + c.x*10) << "\"style=\"fill:#000000;stroke:none;stroke-width:22.1243;stroke-miterlimit:4;stroke-dasharray:none\"id=\"path3"<< std::to_string(i)<<"\" />" << std::endl;
				
				//~ c = c.make_global(a, coordinates(3, 0), +pi/2+(decimal_n)i*(pi/180.0));
				//~ f << "<circle r=\"0.580836\" cy=\""<< std::to_string(80.240021 + c.y*10) \
					//~ <<"\" cx=\"" << std::to_string(93.624962 + c.x*10) << "\"style=\"fill:#000000;stroke:none;stroke-width:22.1243;stroke-miterlimit:4;stroke-dasharray:none\"id=\"path3"<< std::to_string(i)<<"\" />" << std::endl;
				//~ std::cout << c.x << "; "<< c.y << std::endl;
				//~ /// tenci je 3; 0
				//~ }
			//~ c = c.make_global(a, coordinates(4, 2), -pi/2);
			//~ f << "<circle r=\"2.7080836\" cy=\""<< std::to_string(80.240021 - c.y*10) \
					//~ <<"\" cx=\"" << std::to_string(93.624962 - c.x*10) << "\"style=\"fill:#ff0000;stroke:#ff0000;stroke-width:22.1243;stroke-miterlimit:4;stroke-dasharray:none\"id=\"path5"<< std::to_string(46)<<"\" />" << std::endl;
			
			//~ c = c.make_global(a, coordinates(4, 2), +pi/2);
			//~ f << "<circle r=\"2.7080836\" cy=\""<< std::to_string(80.240021 + c.y*10) \
					//~ <<"\" cx=\"" << std::to_string(93.624962 + c.x*10) << "\"style=\"fill:#ff0000;stroke:#ff0000;stroke-width:22.1243;stroke-miterlimit:4;stroke-dasharray:none\"id=\"path5"<< std::to_string(46)<<"\" />" << std::endl;
			
			//~ c = c.make_global(a, coordinates(3, 0), +pi/2);
			//~ f << "<circle r=\"2.7080836\" cy=\""<< std::to_string(80.240021 + c.y*10) \
					//~ <<"\" cx=\"" << std::to_string(93.624962 + c.x*10) << "\"style=\"fill:#ff0000;stroke:#ff0000;stroke-width:22.1243;stroke-miterlimit:4;stroke-dasharray:none\"id=\"path5"<< std::to_string(55)<<"\" />" << std::endl;
			//~ f << "\n</g>\n</svg>\n";
			#endif
		}
		
		
	void function5(int argc, char *argv[]){
		#ifndef dont_comp
		auto var = std::async(c_f, argv[2]);
		auto var1 = std::async(c_f, argv[3]);
		tank t;
		t.assign_speeds(var.get(), var1.get());
		#endif
		}
		
		
	void function6(int argc, char *argv[]){
		#ifndef dont_comp
		auto var = std::async(c_f, argv[2]);
		auto var1 = std::async(c_f, argv[3]);
		
		float x = var.get();
		float y = var1.get();
		
		decimal_n rad = radius::from_speeds(x, y);
		std::cout << "poloměr: " << rad+dist_wheel/2 << " m" << std::endl;
		#endif
		}
		
		
	void function7(int argc, char *argv[]){
		#ifndef dont_comp
		auto var = std::async(c_f, argv[2]);
		auto var1 = std::async(c_f, argv[3]);
		
		float x = var.get();
		float y = var1.get();
		tank t;
		t.assign_speeds(x, y);
		decimal_n rad = radius::from_speeds(t.velocities.left, t.velocities.right);
		coordinates r = radius::coords(rad, get_radius(x, y), x, y);
		std::cout << r.x << " "<< r.y << std::endl;
		#endif
		}
		
		
	void function8(int argc, char *argv[]){
		#ifndef dont_comp
		uint8_t c = std::thread::hardware_concurrency();
		
		map m;
		for (uint16_t g = 0; g < 32; g++){
			std::vector<std::future< std::vector<location> > > o;
			for (uint8_t t = 0; t < c; t ++){
				o.push_back(std::move(std::async(&map::grid, m, t * map_h / c, 0, ((t+1) * map_h / c), map_l)));
				
				}
			for (auto &i: o){
				std::vector<location> out = i.get();
				
				m._map.insert(m._map.begin(), out.begin(), out.end());
				
				}
			//~ std::cout << "size " << m._map.size() << std::endl;
			m._map.clear();
			//~ for (auto d: m._map){
				
				//~ std::cout << d._coordinates.x << std::endl;
				//~ }
			
			}
		#endif
		}
		
		
		
	void function9(int argc, char *argv[]){
		#ifndef dont_comp
		uint8_t c = std::thread::hardware_concurrency();
		
		map m;
		std::vector<std::future < std::vector<location> > > o;
		for (uint8_t t = 0; t < c; t ++){
			o.push_back(std::move(std::async(&map::grid, m, t * map_h / c, 0, ((t+1) * map_h / c), map_l)));
			
			}
		for (auto &i: o){
			std::vector<location> out = i.get();
			
			m._map.insert(m._map.begin(), out.begin(), out.end());
			
			}
	
	
		m._map[0].set_point(location::_discovered);
		m._map[30].set_point(location::_candle);
		std::cout << "x: " << m._map[0]._coordinates.x << "  y: " << m._map[0]._coordinates.y << std::endl;
		location loo = m.interest_calculate();
		std::cout << "x: " << loo._coordinates.x << "  y: " << loo._coordinates.y << std::endl;
		m.interest_map();
		decimal_n loc = m.calculate_location(location(10, 10));
		std::cout << "interest: " << loc << "\n";
		std::cout << radius::from_3_points(coordinates(4, 4), coordinates(-1, 1), coordinates(2, 4));
		coordinates d = radius::coords(coordinates(0, 0), coordinates(2, 2), coordinates(-1, 2.5));
		std::cout << "\nx: " << d.x << " y: " << d.y <<"\n";
		#endif
		}
		
		
		
	void function10(int argc, char *argv[]){
		#ifndef dont_comp
		std::vector<coordinates> c = radius::tangent_points(coordinates(c_f(argv[2]), c_f(argv[3])), c_f(argv[4]), coordinates(c_f(argv[5]), c_f(argv[6])));
		if(c.size() == 2){
			std::cout << circle(coordinates(c_f(argv[2]), c_f(argv[3])), c_f(argv[4])).print() <<  std::endl;
			std::cout << coordinates(c_f(argv[5]), c_f(argv[6])).print_geogebra() <<  std::endl;
			std::cout <<  c[0].print_geogebra() << "\n" << c[1].print_geogebra() <<  std::endl;
			}
		#endif
		}
		
		
		
	void function11(int argc, char *argv[]){
		#ifndef dont_comp
		coordinates a(0, 0);
		decimal_n ang = -pi_const/4;
		switch(c_i(argv[2])){
			case 0:
				ang = pi_const/4;
				break;
			case 1:
				ang = 3*pi_const/4;
				break;
			case 2:
				ang = 5*pi_const/4;
				break;
			case 3:
				ang = 7*pi_const/4;
				break;
			default:
				ang = 0;
				break;
			
			}
		//~ decimal_n ang = 0;
		//~ decimal_n ang = -pi_const/6;
		decimal_n len = 5;
		coordinates c = a.make_local(len, ang);
		std::cout << c.x << "; " << c.y << std::endl;
		#endif
		}
		
		
	void function12(int argc, char *argv[]){
		#ifndef dont_comp
		coordinates a(0, 0);
		coordinates b(-1, -1);
		// ocekavane - 3, 4
		decimal_n ang = -pi_const/2;
		switch(c_i(argv[2])){
			case 0:
				ang = pi_const/4;
				break;
			case 1:
				ang = 3*pi_const/4;
				break;
			case 2:
				ang = 5*pi_const/4;
				break;
			case 3:
				ang = 7*pi_const/4;
				break;
			case 4:
				ang = pi_const;
				break;
			case 5:
				ang = pi_const/2.0;
				break;
			case 6:
				ang = -pi_const/2.0;
				break;
			default:
				ang = 0;
				break;
			
			}
		//~ decimal_n ang = -pi_const/6;
		//~ decimal_n ang = 0;
		coordinates c = coords_n(ang+pi_const/2, b);
		std::cout << c.x << "; " << c.y << std::endl;
		#endif
		}
		
		
	void function13(int argc, char *argv[]){
		#ifndef dont_comp
		coordinates c = line().intersection(line(0, 2, -14), line(-3, 5, -4));
		std::cout << c.x << "; " << c.y << std::endl;
		std::vector<coordinates> a = circle().intersection(line(-1, 1, 1), circle(1, 2, 3));
		std::cout << a[1].x << "; " << a[1].y << std::endl;
		
		a = circle().intersection(circle(1, 1, 2), circle(1, 2, 3));
		std::cout << a[a.size()-1].x << "; " << a[a.size()-1].y << std::endl;
		std::cout << a.size() << std::endl;
		#endif
		}
		
		
	void function14(int argc, char *argv[]){
		#ifndef dont_comp
		line l(1, 1, 4);
		line d = l.make_parallel(coordinates(2, 5));
		std::cout << d.print(d) << std::endl;
		#endif
		}
		
		
	void function15(int argc, char *argv[]){
		#ifndef dont_comp
		coordinates points[4] = {coordinates(1, 1), coordinates(0, 2), coordinates(4, 6), coordinates(5, 5)};
		wall w(points);
		bool c = w.inside(coordinates(c_f(argv[2]), c_f(argv[3])));
		std::cout << c << std::endl;
		std::vector<coordinates>  co = w.is_collision_course(line(-1, 1, 1));
		std::cout << co[co.size()-1].print() << std::endl;
		for(uint8_t i = 0; i < 4; i++)
			std::cout << w.properties.walls[i].print(w.properties.walls[i]) << std::endl;
		#endif
		}
		
		
	void function16(int argc, char *argv[]){
		#ifndef dont_comp
		map m;
		coordinates c[] = {coordinates(-10, 3), coordinates(-11, 4), coordinates(-7, 7), coordinates(-6, 6)};
		coordinates x[] = {coordinates(1, 1), coordinates(0, 2), coordinates(4, 6), coordinates(5, 5)};
		
		m._map_walls.push_back(wall(c));
		m._map_walls.push_back(wall(x));
		std::cout << m._map_walls[0].is_collision_course(circle(coordinates(-5, 2), 6))[1].print() << std::endl;
		angles a = angles().load_virtual(coordinates(-5, 2), m);
		for(auto i: a)
			std::cout << "uhel: " << i.angle << "   vzdalenost: " << i.distance << "\t" << i.position._coordinates.print() << std::endl;
		#endif
		}
		
		
	void function17(int argc, char *argv[]){
		#ifndef dont_comp
		/// this creates map and does math to calculations to make heatmap, therefore selecting the hottest spot and designing trace to it
		map m;
		m._map = m.grid(0, 0, 150, 150);
		coordinates c[] = {coordinates(-10, 3), coordinates(-11, 4), coordinates(-7, 7), coordinates(-6, 6)};
		coordinates x[] = {coordinates(1, 1), coordinates(0, 2), coordinates(4, 6), coordinates(5, 5)};
		coordinates z[] = {coordinates(10, 10), coordinates(0, 20), coordinates(40, 60), coordinates(50, 50)};
		
		m.append(candle(coordinates(4,3)));
		m.append(wall(c));
		m.append(wall(x));
		m.append(wall(z));
		//~ std::cout << m._map_walls[0].is_collision_course(circle(coordinates(-5, 2), 6))[1].print() << std::endl;
		angles a = angles().load_virtual_circular(coordinates(-5, 2), m, 0, 20, 0.06);
		//~ angles a = angles().load_virtual(coordinates(-5, 2), m);
		for(auto i: a)
			std::cout << "uhel: " << i.angle << "   vzdalenost: " << i.distance << "\t" << i.position._coordinates.print() << std::endl;
		std::cout << m._map_walls[0].get_box()[1].print() << "\t" << m._map_walls[0].get_box()[0].print() << std::endl;
		std::cout << m._map_candles[0].get_box()[1].print() << "\t" << m._map_candles[0].get_box()[0].print() << std::endl;
		//~ m.strip({coordinates(10, 10), coordinates(60, 60)})[0] -> set_point(location::_candle);
		m.edit_map(z);
		m.interest_calculate();
		m.interest_map();
		#endif
		}
		
		
	void function18(int argc, char *argv[]){
		#ifndef dont_comp
		std::cout << ((c_f(argv[2]) < 0)? 360:0) + atan2(c_f(argv[2]), c_f(argv[3])) * 180/pi_const << std::endl;
		#endif
		}
		
		
		
	void function19(int argc, char *argv[]){
		#ifndef dont_comp
		std::cout << circle().intersection(circle().circle_tangents(circle(coordinates(-6, -2), 5), circle(coordinates(6, 9), 5))[0], circle(coordinates(-6, -2), 5))[0].print() << std::endl;
		#endif
		}
		
		
		
	void function20(int argc, char *argv[]){
		#ifndef dont_comp
		std::cout << step(coordinates(-50, 10), coordinates(0, 60), coordinates(0, 10)).print_inkscape() << std::endl;
		#endif
		}
		


}
