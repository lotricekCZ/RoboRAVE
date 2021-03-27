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
#include "serial.hpp"


//~ serial::serial(){}

//~ serial::serial(const std::string &device, BaudRate baudRate){
	//~ }

//~ serial::serial(const std::string &device, speed_t baudRate){
	//~ }

serial::~serial(){}

void serial::open(){
	mn::CppLinuxSerial::SerialPort::Open();
	}
	
void serial::close(){
	mn::CppLinuxSerial::SerialPort::Close();
	}

void serial::write(const std::string& data){
	mn::CppLinuxSerial::SerialPort::Write(data);
	}
	
void serial::read(std::string& data){
	mn::CppLinuxSerial::SerialPort::Read(data);
	}
	
void serial::baudrate(speed_t data){
	mn::CppLinuxSerial::SerialPort::SetBaudRate(data);
	}
	
void serial::port(std::string data){
	mn::CppLinuxSerial::SerialPort::SetDevice(data);
	}
	
void serial::baudrate(mn::CppLinuxSerial::BaudRate data){
	mn::CppLinuxSerial::SerialPort::SetBaudRate(data);
	}
