 /*
 * serial.hpp
 * 
 * Copyright 2020 Jakub Ramašeuski <jakub@jakub-ThinkPad-X250>
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


#ifndef SERIAL_HPP
#define SERIAL_HPP

#include <CppLinuxSerial/SerialPort.hpp>
#include <sys/ioctl.h>
//~ using namespace mn::CppLinuxSerial;

class serial: public mn::CppLinuxSerial::SerialPort {	
	public:
		std::string _port = "";
		using mn::CppLinuxSerial::SerialPort::ReadBinary;
		using mn::CppLinuxSerial::SerialPort::WriteBinary;
		using mn::CppLinuxSerial::SerialPort::Open;
		using mn::CppLinuxSerial::SerialPort::Close;
		using mn::CppLinuxSerial::SerialPort::SetDevice;
		using mn::CppLinuxSerial::SerialPort::SetBaudRate;
		using mn::CppLinuxSerial::SerialPort::InWaiting;
		//~ using mn::CppLinuxSerial::BaudRate;
		
		void open();
		void close();
		void read(std::vector<uint8_t> &data);
		void write(const std::vector<uint8_t> &data);
		
		void port(std::string); /// port like "/dev/ttyUSB0"
		
		void baudrate(speed_t);
		void baudrate(mn::CppLinuxSerial::BaudRate);
		signed_b in_waiting();
		serial(): SerialPort(){}
		serial(const std::string &a, mn::CppLinuxSerial::BaudRate b): SerialPort(a, b){
			_port = a;
			}
		serial(const std::string &a, speed_t b): SerialPort(a, b){}
		~serial();
	private:
		/* add your private declarations */
};

#endif /* SERIAL_HPP */ 
