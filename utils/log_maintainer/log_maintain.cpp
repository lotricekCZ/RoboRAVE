#include "log_maintain.hpp"

#ifndef LOG_MAINTAIN_CPP
#define LOG_MAINTAIN_CPP

log_writer::log_writer(std::string message, std::string filename){
			std::ofstream f(filename, std::ios::out | std::ios::app);
			//~ f.open();
			f << generate_timestamp() << message << "\r\n";
			f.flush();
			f.close();
			std::cout << generate_timestamp() << message << std::endl;
			}

std::string log_writer::generate_timestamp(){
	std::time_t t = std::time(nullptr);
	char str[42];

	std::strftime(str, sizeof(str), "[%F %T] @ ", std::localtime(&t));
	
	std::string returnable(str);
	returnable += std::to_string(t);
	returnable += " s: ";
	return returnable;
	
	}

#endif
