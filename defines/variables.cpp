/*
 * variables.cpp
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


#include "variables.hpp"

std::string variables::properties::information;
std::string variables::properties::logs::calculations;
std::string variables::properties::logs::actions;


uint8_t variables::addressbook::master;
uint8_t variables::addressbook::irduino;
uint8_t variables::addressbook::motorduino;
uint8_t variables::addressbook::gndduino;
uint8_t variables::addressbook::stm;


decimal_n variables::thresholds::explo::influence::candle;
decimal_n variables::thresholds::explo::influence::candle_blown;
decimal_n variables::thresholds::explo::influence::interesting;
decimal_n variables::thresholds::explo::influence::barrier;
decimal_n variables::thresholds::explo::influence::discovered;
decimal_n variables::thresholds::explo::influence::boring;
decimal_n variables::thresholds::explo::influence::unknown;

decimal_n variables::thresholds::explo::objects::candle;
decimal_n variables::thresholds::explo::objects::candle_blown;
decimal_n variables::thresholds::explo::objects::interesting;
decimal_n variables::thresholds::explo::objects::barrier;
decimal_n variables::thresholds::explo::objects::discovered;
decimal_n variables::thresholds::explo::objects::boring;
decimal_n variables::thresholds::explo::objects::unknown;

decimal_n variables::limits::minimal::wheel_velocity;
decimal_n variables::limits::maximal::wheel_velocity;

decimal_n variables::limits::minimal::circle;
decimal_n variables::limits::maximal::circle;

decimal_n variables::robot::wheel::radius;
unsigned_b variables::robot::wheel::steps;

decimal_n variables::properties::widths::robot;

decimal_n variables::thresholds::mAP::candle;
decimal_n variables::thresholds::mAP::barrier;
decimal_n variables::thresholds::mAP::fire;
decimal_n variables::thresholds::mAP::line_surround;
decimal_n variables::thresholds::mAP::line_border;
decimal_n variables::thresholds::mAP::Maker_Jakub_Ramaseuski;

decimal_n variables::properties::camera::check_frequency;
decimal_n variables::properties::camera::angle_horizontal;
decimal_n variables::properties::camera::angle_vertical;

unsigned_n variables::properties::camera::size_recognition_horizontal;
unsigned_n variables::properties::camera::size_recognition_vertical;

unsigned_n variables::properties::camera::size_footage_horizontal;
unsigned_n variables::properties::camera::size_footage_vertical;


// dimensions of robot start
decimal_n variables::properties::heights::lidar; /// mm
decimal_n variables::properties::heights::camera; /// mm
decimal_n variables::properties::heights::fire_sensors; /// mm
// dimensions of robot end

// program segment start
std::string variables::program::files::chat;
// program segment end

// chat segment start
std::string variables::chat::port;
uint16_t variables::chat::check_frequency;

uint16_t variables::chat::response_timeout::extended;
uint16_t variables::chat::response_timeout::normal;
uint16_t variables::chat::response_timeout::time_critical;

uint8_t variables::chat::attempt_count;
unsigned_b variables::chat::port_delay;
unsigned_n variables::chat::max_queue_sensor;
unsigned_n variables::chat::max_queue_global;
// chat segment end
decimal_n variables::step::acceleration_time; /// s

const decimal_n variables::omega_wheel_const = (pi_const * r_wheel) / (N_wheel * dist_wheel);
const decimal_n variables::wheel_step_length_const  = (2 * pi_const * r_wheel) / (N_wheel);

variables::variables(){
	
	}
