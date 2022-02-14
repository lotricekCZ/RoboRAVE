/*
 * serial.cpp
 * 
 * Copyright 2020 Jakub Ramašeuski <jakub@skaryna.net>
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


#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../../defines/typedefines.h"
#include "serial.hpp"


//~ serial::serial(){}

//~ serial::serial(const std::string &device, BaudRate baudRate){
	//~ }

//~ serial::serial(const std::string &device, speed_t baudRate){
	//~ }
int c_open(std::string f){
	return open(f.c_str(), O_RDONLY);
	}
	
void c_close(int fd){
	close(fd);
	}
	
serial::~serial(){}



void serial::open(){
	Open();
	}



//~ bool serial::is_opened(){
	//~ return IsOpen();
	//~ }


	
void serial::close(){
	Close();
	}



void serial::write(const std::vector<uint8_t>& data){
	WriteBinary(data);
	}


	
void serial::read(std::vector<uint8_t>& data){
	ReadBinary(data);
	}



void serial::baudrate(speed_t data){
	SetBaudRate(data);
	}


	
void serial::port(std::string data){
	_port = data;
	SetDevice(data);
	}


	
void serial::baudrate(mn::CppLinuxSerial::BaudRate data){
	SetBaudRate(data);
	}


	
signed_b serial::in_waiting(){
	return (signed_b)Available();
	}


