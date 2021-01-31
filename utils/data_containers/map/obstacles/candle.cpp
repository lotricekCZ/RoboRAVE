/*
 * candle.cpp
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


#include "candle.hpp"

#ifndef CANDLE_CPP
#define CANDLE_CPP

candle::candle()
	: obstacle()
{
	
}

candle::candle(coordinates c) : obstacle(){
	tube = circle(c, candle_r);
	
	}

std::string candle::inkscape_print(){
	return "<path style=\"opacity:1;fill:none;stroke:#008080;stroke-width:3.5;stroke-linecap:round;stroke-linejoin:round;paint-order:stroke fill markers\"\
			\tid=\"path833\"\n\
			\tsodipodi:type=\"arc\" \n\
			\tsodipodi:cx=\"" + std::to_string(tube.center.x) +"\"\n\
			\tsodipodi:cy=\"" + std::to_string(tube.center.y) +"\"\n\
			\tsodipodi:rx=\"" + std::to_string(tube.radius) +"\"\n\
			\tsodipodi:ry=\"" + std::to_string(tube.radius) +"\"\n\
			\tsodipodi:start=\"" + std::to_string(0) +"\"\n\
			\tsodipodi:end=\"" + std::to_string(2*pi) +"\"\n\
			\tsodipodi:arc-type=\"arc\"\n\
			\tsodipodi:open=\"false\" />\n";
	}
#endif
