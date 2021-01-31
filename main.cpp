#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <inttypes.h>
#include <cmath>
#include <thread>
#include <chrono>
#include <future>
#include <limits>

#include <iostream>

#include "./hardware_interfaces/Serial/serial.cpp"

#include "./utils/data_containers/setters/setters.tpp"
#include "./utils/data_containers/speeds/speeds.cpp"
#include "./utils/data_containers/coordinates/coordinates.cpp"
#include "./utils/data_containers/map/include.hpp"
#include "./utils/log_maintainer/log_maintain.cpp"
#include "./utils/data_containers/angles/angles/angles.cpp"
#include "./utils/planners/planner/planner.cpp"
#include "./defines/typedefines.h"

#define my_max(a, b) ((a>b)?a:b)

#include "./defines/constants.h"

//~ const decimal_n omega_wheel_const = (pi * r_wheel) / (N_wheel * dist_wheel);
//~ const decimal_n wheel_step_lenght_const = (2 * pi * r_wheel) / (N_wheel);9

#include "./tank/tank.h"
#include "./elements/radius/radius.h"
#include "./utils/logic/logic.cpp"


decimal_n calculate_omega(decimal_n T_avg = 0){
	//~ printf("omega con %f\nTavg %f\n %.20Lf\n", omega_wheel_const, T_avg, pi);
	return (omega_wheel_const * T_avg);
	}

decimal_n calculate_T_avg(decimal_n T_left = 0, decimal_n T_right = 0){
	return ((T_right - T_left) / (decimal_n)(T_right * T_left));
	}

decimal_n calculate_distance_wheel(decimal_n period, decimal_n time){
	return abs((time * wheel_step_lenght_const)/(decimal_n)period);
	}

decimal_n c_f(char * input){
	return (decimal_n)atof(input);
	}

signed_n c_i(char * input){
	return atoi(input);
	}

decimal_n get_gamma(signed_n x_rel, signed_n y_rel){
	return atan((decimal_n)y_rel / (decimal_n)x_rel);
	}
	
decimal_n get_radius(decimal_n x_rel, decimal_n y_rel){
	return sqrt(pow(x_rel, 2) + pow(y_rel, 2));
	}


decimal_n coords_x(decimal_n alpha, decimal_n gamma, decimal_n radius, uint8_t dec){
	return (((dec >> 1) & 1? 1 : -1))*cos((alpha) + ((dec & 1)? (1) : (-1))* gamma)*radius;
	}

decimal_n coords_y(decimal_n alpha, decimal_n gamma, decimal_n radius, uint8_t dec){
	return (((dec >> 1) & 1? 1 : -1))*sin((alpha) + ((dec & 1)? (1) : (-1))* gamma)*radius;
	}
	
/*
 * 
 * name: coords_n
 * @param alpha - aktualni natoceni v prostoru
 * @param rel - relative coordinates / vector
 * @return delta souradnic v realnem prostoru
 * 
 */

coordinates coords_n(decimal_n alpha, coordinates rel){
	return coordinates(rel.x * cos(alpha) - (rel.y * sin(alpha)), rel.x * sin(alpha) + (rel.y * cos(alpha)));
	}





int main(int argc, char *argv[]) {
	auto start = std::chrono::steady_clock::now();
	switch(c_i(argv[1])){
		case 1:
			log_writer("dear Odin, fuck you", "general.txt");
			break;
			
		case 2:
			printf("result %.10f\n", calculate_T_avg(c_f(argv[2]), c_f(argv[3])));
			break;
			
		case 3:
			printf("result %.10f\n", get_radius(c_f(argv[2]), c_f(argv[3])));
			break;
		
		case 4:{
			coordinates a(-1, -2);
			coordinates b(1, -1);
			// ocekavane - 3, 4
			decimal_n ang = -pi/2;
			switch(c_i(argv[2])){
				case 0:
					ang = pi/4;
					break;
				case 1:
					ang = 3*pi/4;
					break;
				case 2:
					ang = 5*pi/4;
					break;
				case 3:
					ang = 7*pi/4;
					break;
				case 4:
					ang = pi;
					break;
				case 5:
					ang = pi/2.0;
					break;
				case 6:
					ang = -pi/2.0;
					break;
				default:
					ang = 0;
					break;
				
				}
			coordinates c = c.make_global(a, b, -3*pi/4);
			std::cout << c.x << "; " << c.y << std::endl;
			c = c.make_local(c, a, 3*pi/4);
			std::cout << c.x << "; " << c.y << std::endl;
			
			c = c.make_local(sqrt(5), -atan(1.0/2.0));
			std::cout << c.x << "; " << c.y << std::endl;
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
			break;
		}
		case 5:{
			auto var = std::async(c_f, argv[2]);
			auto var1 = std::async(c_f, argv[3]);
			tank t;
			t.assign_speeds(var.get(), var1.get());
			break;
			}
		
		case 6:{
			auto var = std::async(c_f, argv[2]);
			auto var1 = std::async(c_f, argv[3]);
			
			float x = var.get();
			float y = var1.get();
			
			decimal_n rad = radius::from_speeds(x, y);
			std::cout << "poloměr: " << rad+dist_wheel/2 << " m" << std::endl;
			
			break;
			}
			
		case 7:{
			auto var = std::async(c_f, argv[2]);
			auto var1 = std::async(c_f, argv[3]);
			
			float x = var.get();
			float y = var1.get();
			tank t;
			t.assign_speeds(x, y);
			decimal_n rad = radius::from_speeds(t.velocities.left, t.velocities.right);
			coordinates r = radius::coords(rad, get_radius(x, y), x, y);
			std::cout << r.x << " "<< r.y << std::endl;
			break;
			}
			
		case 8:{
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
			}
			
		case 9:{
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
		
		
			//~ m._map[0].set_point(location::_discovered);
			//~ m._map[30].set_point(location::_candle);
			//~ std::cout << "x: " << m._map[0]._coordinates.x << "  y: " << m._map[0]._coordinates.y << std::endl;
			location loo = m.interest_calculate();
			std::cout << "x: " << loo._coordinates.x << "  y: " << loo._coordinates.y << std::endl;
			//~ m.interest_map();
			decimal_n loc = m.calculate_location(location(10, 10));
			std::cout << "interest: " << loc << "\n";
			std::cout << radius::from_3_points(coordinates(-4, 0), coordinates(4, 0), coordinates(0, 4));
			coordinates d = radius::coords(coordinates(0, 0), coordinates(2, 2), coordinates(-1, 2.5));
			std::cout << "\nx: " << d.x << " y: " << d.y <<"\n";
			}
		
		case 10:{
			std::vector<coordinates> c = radius::tangent_points(coordinates(c_f(argv[2]), c_f(argv[3])), c_f(argv[3]), coordinates(c_f(argv[4]), c_f(argv[5])));
			if(c.size() == 2)
				std::cout <<  c[0].x << "; "<< c[0].y << "\n" << c[1].x << "; "<< c[1].y <<  std::endl;
			}
			
		case 11:{
			coordinates a(0, 0);
			decimal_n ang = -pi/4;
			switch(c_i(argv[2])){
				case 0:
					ang = pi/4;
					break;
				case 1:
					ang = 3*pi/4;
					break;
				case 2:
					ang = 5*pi/4;
					break;
				case 3:
					ang = 7*pi/4;
					break;
				default:
					ang = 0;
					break;
				
				}
			//~ decimal_n ang = 0;
			//~ decimal_n ang = -pi/6;
			decimal_n len = 5;
			coordinates c = a.make_local(len, ang);
			std::cout << c.x << "; " << c.y << std::endl;
			break;			
			}
			
		case 12:{
			coordinates a(0, 0);
			coordinates b(-1, -1);
			// ocekavane - 3, 4
			decimal_n ang = -pi/2;
			switch(c_i(argv[2])){
				case 0:
					ang = pi/4;
					break;
				case 1:
					ang = 3*pi/4;
					break;
				case 2:
					ang = 5*pi/4;
					break;
				case 3:
					ang = 7*pi/4;
					break;
				case 4:
					ang = pi;
					break;
				case 5:
					ang = pi/2.0;
					break;
				case 6:
					ang = -pi/2.0;
					break;
				default:
					ang = 0;
					break;
				
				}
			//~ decimal_n ang = -pi/6;
			//~ decimal_n ang = 0;
			coordinates c = coords_n(ang+pi/2, b);
			std::cout << c.x << "; " << c.y << std::endl;
			break;
			}
			
		case 13:{
			coordinates c = line().intersection(line(0, 2, -14), line(-3, 5, -4));
			std::cout << c.x << "; " << c.y << std::endl;
			std::vector<coordinates> a = circle().intersection(line(-1, 1, 1), circle(1, 2, 3));
			std::cout << a[1].x << "; " << a[1].y << std::endl;
			
			a = circle().intersection(circle(1, 1, 2), circle(1, 2, 3));
			std::cout << a[a.size()-1].x << "; " << a[a.size()-1].y << std::endl;
			std::cout << a.size() << std::endl;
			break;
			}
		case 14:{
			line l(1, 1, 4);
			line d = l.make_parallel(coordinates(2, 5));
			std::cout << d.print(d) << std::endl;
			break;
			}
			
		case 15:{
			coordinates points[4] = {coordinates(1, 1), coordinates(0, 2), coordinates(4, 6), coordinates(5, 5)};
			wall w(points);
			bool c = w.inside(coordinates(c_f(argv[2]), c_f(argv[3])));
			std::cout << c << std::endl;
			std::vector<coordinates>  co = w.is_collision_course(line(-1, 1, 1));
			std::cout << co[co.size()-1].print() << std::endl;
			for(uint8_t i = 0; i < 4; i++)
				std::cout << w.properties.walls[i].print(w.properties.walls[i]) << std::endl;
			break;
			}
			
		case 16:{
			
			map m;
			coordinates c[] = {coordinates(-10, 3), coordinates(-11, 4), coordinates(-7, 7), coordinates(-6, 6)};
			coordinates x[] = {coordinates(1, 1), coordinates(0, 2), coordinates(4, 6), coordinates(5, 5)};
			
			m._map_walls.push_back(wall(c));
			m._map_walls.push_back(wall(x));
			std::cout << m._map_walls[0].is_collision_course(circle(coordinates(-5, 2), 6))[1].print() << std::endl;
			angles a = angles().load_virtual(coordinates(-5, 2), m);
			for(auto i: a)
				std::cout << "uhel: " << i.angle << "   vzdalenost: " << i.distance << "\t" << i.position._coordinates.print() << std::endl;
			break;
			}
			
		case 17:{ 
			/// this creates map and does math to calculations to make heatmap, therefore selecting the hottest spot and designing trace to it
			map m;
			m._map = m.grid(0, 0, 90, 90);
			coordinates c[] = {coordinates(-10, 3), coordinates(-11, 4), coordinates(-7, 7), coordinates(-6, 6)};
			coordinates x[] = {coordinates(1, 1), coordinates(0, 2), coordinates(4, 6), coordinates(5, 5)};
			
			m.append(candle(coordinates(4,3)));
			m.append(wall(c));
			m.append(wall(x));
			//~ std::cout << m._map_walls[0].is_collision_course(circle(coordinates(-5, 2), 6))[1].print() << std::endl;
			angles a = angles().load_virtual_circular(coordinates(-5, 2), m, 0, 20, 0.06);
			//~ angles a = angles().load_virtual(coordinates(-5, 2), m);
			for(auto i: a)
				std::cout << "uhel: " << i.angle << "   vzdalenost: " << i.distance << "\t" << i.position._coordinates.print() << std::endl;
			std::cout << m._map_walls[0].get_box()[1].print() << "\t" << m._map_walls[0].get_box()[0].print() << std::endl;
			std::cout << m._map_candles[0].get_box()[1].print() << "\t" << m._map_candles[0].get_box()[0].print() << std::endl;
			m.strip({coordinates(10, 10), coordinates(60, 60)})[0] -> set_point(location::_candle);
			
			m.interest_calculate();
			m.interest_map();
			break;
			}
			
		case 18:{ 
			std::cout << ((c_f(argv[2]) < 0)? 360:0) + atan2(c_f(argv[2]), c_f(argv[3])) * 180/pi << std::endl;
			break;
			}
			
		}

	
    //~ uint8_t c = std::thread::hardware_concurrency();
    //~ std::cout << " number of cores: " << c << std::endl;
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	
	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
	return 0;
}
