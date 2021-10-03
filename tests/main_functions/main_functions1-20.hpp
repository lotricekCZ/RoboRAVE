/*
 * main_functions1-20.hpp
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


#ifndef MAIN_FUNCTIONS1_20_HPP
#define MAIN_FUNCTIONS1_20_HPP

#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <inttypes.h>
#include <cmath>
#include <thread>
#include <chrono>
#include <future>
#include <limits>
#include <ctime>
#include <iostream>

#define dont_comp

#ifndef dont_comp

#include "./../../elements/vector/vector.hpp"
#include "./../../defines/variables.hpp"
#include "./../../utils/data_containers/setters/setters.tpp"
#include "./../../utils/data_containers/speeds/speeds.hpp"
#include "./../../utils/data_containers/coordinates/coordinates.hpp"
#include "./../../utils/data_containers/map/include.hpp"
#include "./../../utils/log_maintainer/log_maintain.hpp"
#include "./../../utils/planners/planner/step.hpp"
#include "./../../utils/data_containers/angles/angles/angles.hpp"
#include "./../../obsolete/obsolete.hpp"
#include "./../../tank/tank.h"
#include "./../../elements/radius/radius.h"

#endif


namespace mf {
	void function1();
	void function2(int argc, char *argv[]);
	void function3(int argc, char *argv[]);
	void function4(int argc, char *argv[]);
	void function5(int argc, char *argv[]);
	void function6(int argc, char *argv[]);
	void function7(int argc, char *argv[]);
	void function8(int argc, char *argv[]);
	void function9(int argc, char *argv[]);
	void function10(int argc, char *argv[]);
	
	void function11(int argc, char *argv[]);
	void function12(int argc, char *argv[]);
	void function13(int argc, char *argv[]);
	void function14(int argc, char *argv[]);
	void function15(int argc, char *argv[]);
	void function16(int argc, char *argv[]);
	void function17(int argc, char *argv[]);
	void function18(int argc, char *argv[]);
	void function19(int argc, char *argv[]);
	void function20(int argc, char *argv[]);
	
	};
#endif /* MAIN_FUNCTIONS1_20_HPP */ 
