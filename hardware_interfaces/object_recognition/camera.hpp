/*
 * camera.hpp
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


#ifndef CAMERA_HPP
#define CAMERA_HPP

class camera
{
	decimal_n angle_horizontal = 			properties::camera::angle_horizontal;
	decimal_n angle_vertical = 				properties::camera::angle_vertical;
	decimal_n height =						properties::heights::camera;
	unsigned_n px_recognition_horizontal = 	properties::camera::size_recognition_horizontal;
	unsigned_n px_recognition_vertical = 	properties::camera::size_recognition_vertical;
	unsigned_n px_footage_horizontal = 		properties::camera::size_footage_horizontal;
	unsigned_n px_footage_vertical = 		properties::camera::size_footage_vertical;
	
	public:
		camera();
			
	private:
		/* add your private declarations */
};

#endif /* CAMERA_HPP */ 
