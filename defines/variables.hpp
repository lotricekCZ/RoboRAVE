/*
 * variables.hpp
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

#include "typedefines.h"
#include "constants.h"
#include <string>

#ifndef VARIABLES_HPP
#define VARIABLES_HPP

static class variables { // I hate myself for this!!!
	public:
		static const decimal_n omega_wheel_const;
		static const decimal_n wheel_step_lenght_const;
		static class properties {
			public:
			static std::string information;
			
			static class logs {
				public:
				static std::string actions;
				static std::string calculations;
				} logs;
				
			static class camera {
				public:
				static decimal_n angle_horizontal; /// degrees
				static decimal_n angle_vertical; /// degrees
				static unsigned_n size_recognition_horizontal; /// px
				static unsigned_n size_recognition_vertical; /// px
				static unsigned_n size_footage_horizontal; /// px
				static unsigned_n size_footage_vertical; /// px
				} camera;
		
			static class heights {
				/// TODO: All these heights should be remeasured
				public:
				static decimal_n lidar; /// mm
				static decimal_n camera; /// mm
				static decimal_n fire_sensors; /// mm
				} heights;
				
			 static class widths {
				public:
				static decimal_n robot; /// mm, maximal width and a diameter
				} widths;
				
			} properties;
		
		
		static class limits {
			public:
			static class maximal {
				public:
				static decimal_n wheel_velocity;		/// m*s^-1 maximal wheel velocity that is allowed and proably safe (3ms:3ms)
				static decimal_n circle;		/// REMOVE AFTER plan_make tests
				//~ static decimal_n circle 		= 0.4; /// m maximal allowed circle, speed is key.
				static unsigned_n period;	/// us, maximal time between pulses 
				} maximal;
		
			static class minimal {
				public:
				static decimal_n wheel_velocity;	/// m*s^-1 maximal wheel velocity that is allowed and proably safe
				//~ static decimal_n circle 		= 0.1;		/// m minimal allowed circle, speed is key. (it's ratio is 14ms:3ms )
				static decimal_n circle; 
				static unsigned_n period;		/// us, minimal time between pulses, lower values might will make mess with motor
				} minimal;
	
			} limits;
			
			static class thresholds {
				public:
				static class mAP { 
					public:
					// ammount of confidence image recognition needs to have
					static decimal_n candle;
					static decimal_n line_border;
					static decimal_n line_surround;
					static decimal_n fire;
					static decimal_n barrier;
					static decimal_n person;
					static decimal_n Maker_Jakub_Ramaseuski;
					} mAP;
					
				static class explo {
					public:
					static class objects{
						public:
						static decimal_n candle;
						static decimal_n candle_blown;
						static decimal_n unknown;
						static decimal_n barrier;
						static decimal_n discovered;
						static decimal_n interesting;
						static decimal_n boring;
						} objects;
						
					static class influence{
						public:
						static decimal_n candle;
						static decimal_n candle_blown;
						static decimal_n unknown;
						static decimal_n barrier;
						static decimal_n discovered;
						static decimal_n boring;
						static decimal_n interesting;
						} influence;
						 
					} explo;
					
				} thresholds;

			
		variables();
			
	private:
		/* add your private declarations */
} variables;

#endif /* VARIABLES_HPP */ 
