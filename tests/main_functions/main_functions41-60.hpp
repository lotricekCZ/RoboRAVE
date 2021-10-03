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


#ifndef MAIN_FUNCTIONS41_60_HPP
#define MAIN_FUNCTIONS41_60_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

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

#include "./../../elements/vector/vector.hpp"
#include "./../../defines/variables.hpp"
#include "./../../utils/data_containers/setters/setters.tpp"
#include "./../../utils/data_containers/speeds/speeds.hpp"
#include "./../../utils/data_containers/coordinates/coordinates.hpp"
#include "./../../utils/data_containers/map/include.hpp"
#include "./../../utils/log_maintainer/log_maintain.hpp"
#include "./../../utils/planners/planner/step.hpp"
#include "./../../utils/planners/planner/planner.hpp"
#include "./../../utils/data_containers/angles/angles/angles.hpp"
#include "./../../obsolete/obsolete.hpp"
#include "./../../tank/tank.h"
#include "./../../elements/radius/radius.h"


namespace mf {
	void function41(int argc, char *argv[]);
	void function42(int argc, char *argv[]);
	void function43(int argc, char *argv[]);
	void function44(int argc, char *argv[]);
	void function45(int argc, char *argv[]);
	void function46(int argc, char *argv[]);
	void function47(int argc, char *argv[]);
	void function48(int argc, char *argv[]);
	void function49(int argc, char *argv[]);
	void function50(int argc, char *argv[]);
	
	void function51(int argc, char *argv[]);
	void function52(int argc, char *argv[]);
	void function53(int argc, char *argv[]);
	void function54(int argc, char *argv[]);
	void function55(int argc, char *argv[]);
	void function56(int argc, char *argv[]);
	void function57(int argc, char *argv[]);
	void function58(int argc, char *argv[]);
	void function59(int argc, char *argv[]);
	void function60(int argc, char *argv[]);
	
	};
#endif /* MAIN_FUNCTIONS41_60_HPP */ 
