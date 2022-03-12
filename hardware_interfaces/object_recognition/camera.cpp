/*
 * camera.cpp
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

#ifndef steady // time point
	#include <chrono>
	#define steady std::chrono::time_point<std::chrono::steady_clock>
#endif

//~ #ifndef duration // time point
	//~ #include <chrono>
	//~ #define duration std::chrono::duration<decimal_n>
//~ #endif

#include <string>
#include <chrono>
#include <vector>
#include <fstream>
#include <iostream>

#include "../../defines/constants.h"
#include "camera.hpp"


camera::camera(decimal_n freq){
	
	}



bool camera::init(){
	_camera.open(0);
	_camera.set(cv::VideoCaptureProperties::CAP_PROP_FPS, check_frequency);
	_camera.set(cv::VideoCaptureProperties::CAP_PROP_FRAME_WIDTH, px_footage_horizontal);
	_camera.set(cv::VideoCaptureProperties::CAP_PROP_FRAME_HEIGHT, px_footage_vertical);
	
	//~ std::cout << __LINE__ << std::endl;
	return _camera.isOpened();
	}


void camera::run(steady used){
	if(std::chrono::duration<decimal_n>(used - last_used).count() >= (1.0f/check_frequency)){
		if(!_camera.isOpened()){
			std::cerr << "ERROR! Camera not opened.\n";
			return;
			}
		_camera.read(frame);
		if(frame.empty()) {
			std::cerr << "ERROR! blank frame grabbed\n";
			last_used = used;
			return;
			}
		cv::Mat lame = frame;
		cv::cvtColor(lame, lame, cv::COLOR_BGR2GRAY);
		cv::blur(lame, lame, cv::Size(5, 5));
		//~ cv::cvtColor(frame, frame, cv::COLOR_GRAY2BGR);
		//~ cv::threshold(frame, frame, cv::COLOR_GRAY2BGR);
		cv::threshold(lame, lame, 20, 255, cv::THRESH_BINARY);
		cv::cvtColor(lame, lame, cv::COLOR_GRAY2BGR);
		//~ cv::threshold(frame, frame, 30, 255, cv::THRESH_BINARY);
		cv::imshow("Hive", lame);
		cv::bitwise_and(frame, lame, frame);
		cv::imshow("Live", frame);
		//~ cv::imshow("Live", lame);
		cv::waitKey(1);
		std::cout << "pass" << std::endl;
		last_used = used;
		}
	}


//~ #ifdef steady
	//~ #undef steady
//~ #endif
