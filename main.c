//~ #include <iostream>
//~ #include <cstdio>
#include <pthread.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include <thread>
#include <future>


#define N_wheel 200.0f
#define r_wheel 0.044f // in meters
#define pi 3.141592653589793238462643383279502884L
#define dist_wheel 0.125f // in meters
#define decimal float
#define signed int16_t

const decimal omega_wheel_const = (pi * r_wheel) / (N_wheel * dist_wheel);
const decimal wheel_step_lenght_const = (2 * pi * r_wheel) / (N_wheel);

#include "./tank/tank.h"

decimal calculate_omega(decimal T_avg = 0){
	//~ printf("omega con %f\nTavg %f\n %.20Lf\n", omega_wheel_const, T_avg, pi);
	return (omega_wheel_const / T_avg);
	}

decimal calculate_T_avg(signed T_left = 0, signed T_right = 0){
	return ((T_right - T_left) / (decimal)(T_right * T_left));
	}

decimal calculate_distance_wheel(signed frequency, decimal time){
	return abs(frequency * time * wheel_step_lenght_const);
	}

decimal c_f(char * input){
	return (decimal)atof(input);
	}

signed c_i(char * input){
	return atoi(input);
	}

decimal get_gamma(signed x_rel, signed y_rel){
	return atan((decimal)y_rel / (decimal)x_rel);
	}
	
decimal get_radius(signed x_rel, signed y_rel){
	return sqrt(pow(x_rel, 2) + pow(y_rel, 2));
	}


decimal coords_x(decimal alpha, decimal gamma, decimal radius, uint8_t dec){
	return -1*(((dec >> 1) & 1? 1 : -1))*cos((alpha) + ((dec & 1)? (1) : (-1))* gamma)*radius;
	}

decimal coords_y(decimal alpha, decimal gamma, decimal radius, uint8_t dec){
	return -1*(((dec >> 1) & 1? 1 : -1))*sin((alpha) + ((dec & 1)? (1) : (-1))* gamma)*radius;
	}

void get_coords(decimal x_rel, decimal y_rel, decimal x, decimal y, decimal alpha){
	auto var = std::async(get_gamma, x_rel, y_rel);
	auto var1 = std::async(get_radius, x_rel, y_rel);
	decimal ralpha = alpha * pi / 180.0f;
	decimal gamma = var.get();
	decimal radius = var1.get();
	auto var2 = std::async(coords_x, ralpha, gamma, radius, (uint8_t) ((x_rel > 0) | (((x_rel < 0) & (y_rel > 0)) | ((x_rel > 0) && (y_rel < 0))) ));
	auto var3 = std::async(coords_y, ralpha, gamma, radius, (uint8_t)((x_rel > 0) | (((x_rel < 0) & (y_rel > 0)) | ((x_rel > 0) && (y_rel < 0)))));
	
	printf("result [%f; %f]\n",x + var2.get(), y + var3.get());	
	}

int main(int argc, char *argv[])
{

	switch((char)argv[1][0]){
		case '1':
			printf("result %.10f", (decimal)calculate_omega(c_f(argv[2])));
			break;
			
		case '2':
			printf("result %.10f", calculate_T_avg(c_i(argv[2]), c_i(argv[3])));
			break;
			
		case '3':
			printf("result %.10f", get_radius(c_i(argv[2]), c_i(argv[3])));
			break;
		
		case '4':
			auto var = std::async(c_f, argv[2]);
			auto var1 = std::async(c_f, argv[3]);
			auto var2 = std::async(c_f, argv[4]);
			auto var3 = std::async(c_f, argv[5]);
			auto var4 = std::async(c_f, argv[6]);
			get_coords(var.get(), var1.get(), var2.get(), var3.get(), var4.get());
			break;
		}
	return 0;
}
