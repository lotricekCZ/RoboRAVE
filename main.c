//~ #include <iostream>
//~ #include <cstdio>
#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <inttypes.h>
#include <cmath>
#include <thread>
#include <chrono>
#include <future>


#define N_wheel 200.0f
#define r_wheel 0.044f // in meters
#define pi 3.141592653589793238462643383279502884L
#define dist_wheel 0.125f // in meters

#ifndef decimal_n
	#define decimal_n float
#endif

#ifndef signed_n
	#include <inttypes.h>
	#define signed_n int16_t
#endif


const decimal_n omega_wheel_const = (pi * r_wheel) / (N_wheel * dist_wheel);
const decimal_n wheel_step_lenght_const = (2 * pi * r_wheel) / (N_wheel);

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
			decimal_n rad = radius::from_hypotenuse(get_radius(x, y), get_gamma(x, y));
			std::cout << "poloměr: " << rad << " mm" << std::endl;
			std::cout << "tahlegamma: " << get_gamma(x, y) << " " << std::endl;
			printf("result [%f; %f]\n",	0, 0);
			break;
			}
		}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
	return 0;
}
