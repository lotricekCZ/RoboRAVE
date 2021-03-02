#ifndef yaml_worker_cpp
#define yaml_worker_cpp

#include "constants.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <yaml-cpp/yaml.h>
#include "yaml.h"

struct CharacterType{
  std::string attribute1;
  std::string attribute2;
};

//~ namespace YAML{
  //~ template<>
  //~ struct convert<CharacterType>{
    //~ static bool decode(const Node& node, CharacterType& cType){ 
       //~ cType.attribute1 = node["attribute1"].as<std::string>();
       //~ cType.attribute2 = node["attribute2"].as<std::string>();
       //~ return true;
    //~ }
  //~ };
//~ }



void load_config(){
	YAML::Node config = YAML::LoadFile("../defines/config.yaml");
	//~ YAML::Node config = YAML::Load("{candle: 3.14159, [0, 1]: integers}");
	//~ YAML::Node node = YAML::Load("{pi: 3.14159, [0, 1]: integers}");

// this needs the conversion from Node to double
	double pi = config["tresholds"]["mAP"]["candle"].as<double>();
	//~ YAML::Node ch = config["thresholds"];
	//~ YAML::Node ar = ch["mAP"];
	std::cout << pi << std::endl;
	//~ const double username = config["candle"].as<double>();
	//~ std::cout << password << std::endl;
	//~ std::cout << username << std::endl;
	//~ std::cout << list[2] << std::endl;
	//~ std::ofstream fout("../defines/config.yaml");
	//~ fout << config;	
	}

#endif // yaml_worker_cpp
