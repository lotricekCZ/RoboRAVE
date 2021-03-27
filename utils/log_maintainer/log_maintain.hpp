#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <ctime> 

#ifndef LOG_MAINTAIN_HPP
#define LOG_MAINTAIN_HPP

class log_writer{
	public:
		log_writer(std::string message, std::string filename);
		std::string generate_timestamp();
		
	};

#endif
