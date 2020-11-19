#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <inttypes.h>
#include <cmath>
#include <thread>
#include <chrono>
#include <future>
//~ #include <mutex>  

//~ std::mutex mtx;

#include "./utils/data_containers/setters/setters.tpp"
#include "./utils/data_containers/speeds/speeds.cpp"
#include "./utils/data_containers/coordinates/coordinates.cpp"
#include "./utils/data_containers/map/map.cpp"
#include "./utils/data_containers/angles/angles/angles.cpp"

#include "./defines/typedefines.h"

#define my_max(a, b) ((a>b)?a:b)

#include "./defines/constants.h"

//~ const decimal_n omega_wheel_const = (pi * r_wheel) / (N_wheel * dist_wheel);
//~ const decimal_n wheel_step_lenght_const = (2 * pi * r_wheel) / (N_wheel);

#include "./tank/tank.h"
#include "./elements/radius/radius.h"



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
	
decimal_n get_radius(signed_n x_rel, signed_n y_rel){
	return sqrt(pow(x_rel, 2) + pow(y_rel, 2));
	}


decimal_n coords_x(decimal_n alpha, decimal_n gamma, decimal_n radius, uint8_t dec){
	return -1*(((dec >> 1) & 1? 1 : -1))*cos((alpha) + ((dec & 1)? (1) : (-1))* gamma)*radius;
	}

decimal_n coords_y(decimal_n alpha, decimal_n gamma, decimal_n radius, uint8_t dec){
	return -1*(((dec >> 1) & 1? 1 : -1))*sin((alpha) + ((dec & 1)? (1) : (-1))* gamma)*radius;
	}

void get_coords(decimal_n x_rel, decimal_n y_rel, decimal_n x = 0, decimal_n y = 0, decimal_n alpha = 0){
	auto var = std::async(get_gamma, x_rel, y_rel);
	auto var1 = std::async(get_radius, x_rel, y_rel);
	decimal_n ralpha = alpha * pi / 180.0f;
	decimal_n gamma = var.get();
	decimal_n radius = var1.get();
	auto var2 = std::async(coords_x, ralpha, gamma, radius, (uint8_t) ((x_rel > 0) | (((x_rel < 0) & (y_rel > 0)) | ((x_rel > 0) && (y_rel < 0))) ));
	auto var3 = std::async(coords_y, ralpha, gamma, radius, (uint8_t)((x_rel > 0) | (((x_rel < 0) & (y_rel > 0)) | ((x_rel > 0) && (y_rel < 0)))));
	
	printf("result [%f; %f]\n",x + var2.get(), y + var3.get());	
	}



int main(int argc, char *argv[])
{
	
	auto start = std::chrono::steady_clock::now();
	switch((char)argv[1][0]){
		case '1':
			printf("result %.10f\n", (decimal_n)calculate_omega(c_f(argv[2])));
			break;
			
		case '2':
			printf("result %.10f\n", calculate_T_avg(c_f(argv[2]), c_f(argv[3])));
			break;
			
		case '3':
			printf("result %.10f\n", get_radius(c_f(argv[2]), c_f(argv[3])));
			break;
		
		case '4':{
			auto var = std::async(c_f, argv[2]);
			auto var1 = std::async(c_f, argv[3]);
			auto var2 = std::async(c_f, argv[4]);
			auto var3 = std::async(c_f, argv[5]);
			auto var4 = std::async(c_f, argv[6]);
			get_coords(var.get(), var1.get(), var2.get(), var3.get(), var4.get());
			break;
		}
		case '5':{
			auto var = std::async(c_f, argv[2]);
			auto var1 = std::async(c_f, argv[3]);
			tank t;
			t.assign_speeds(var.get(), var1.get());
			break;
			}
		
		case '6':{
			auto var = std::async(c_f, argv[2]);
			auto var1 = std::async(c_f, argv[3]);
			
			float x = var.get();
			float y = var1.get();
			
			decimal_n rad = radius::from_speeds(x, y);
			std::cout << "poloměr: " << rad+dist_wheel/2 << " m" << std::endl;
			
			break;
			}
			
		case '7':{
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
			
		case '8':{
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
			
		case '9':{
			uint8_t c = std::thread::hardware_concurrency();
			
			map m;
			std::vector<std::future< std::vector<location> > > o;
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
			
		}

	
    //~ uint8_t c = std::thread::hardware_concurrency();
    //~ std::cout << " number of cores: " << c << std::endl;
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	
	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
	return 0;
}
