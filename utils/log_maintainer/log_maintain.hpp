#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <ctime> 

#ifndef LOG_MAINTAIN
#define LOG_MAINTAIN

class log_writer{
	public:
		log_writer(std::string message, std::string filename);
		std::string generate_timestamp();
		
	};

#endif
