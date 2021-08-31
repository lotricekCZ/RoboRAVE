#ifndef yaml_worker_cpp
#define yaml_worker_cpp

#include "constants.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <yaml-cpp/yaml.h>
//~ #include "yaml.h"



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
	YAML::Node node_mAP			 = node_mAP;
	YAML::Node node_priority	 = config["priority"];
	YAML::Node node_influence	 = node_priority["influence"];
	YAML::Node node_exploration	 = node_priority["exploration"];
	YAML::Node node_camera		 = node_priority["camera"];
	
	properties::logs::calculations = 			config["logs"]["calculations"].as<std::string>();
	properties::logs::actions = 				config["logs"]["actions"].as<std::string>();
	properties::information = 					config["information"].as<std::string>();
	
	thresholds::mAP::candle = 					node_mAP["candle"].as<decimal_n>();
	thresholds::mAP::barrier = 					node_mAP["barrier"].as<decimal_n>();
	thresholds::mAP::fire = 					node_mAP["fire"].as<decimal_n>();
	thresholds::mAP::line_surround = 			node_mAP["line_surround"].as<decimal_n>();
	thresholds::mAP::line_border = 				node_mAP["line_border"].as<decimal_n>();
	thresholds::mAP::Maker_Jakub_Ramaseuski = 	node_mAP["Maker_Jakub_Ramaseuski"].as<decimal_n>();
	
	thresholds::explo::objects::barrier = 		node_exploration["barrier"].as<decimal_n>();
	thresholds::explo::objects::candle = 		node_exploration["candle"].as<decimal_n>();
	thresholds::explo::objects::unknown = 		node_exploration["unknown"].as<decimal_n>();
	thresholds::explo::objects::candle_blown = 	node_exploration["candle_blown"].as<decimal_n>();
	thresholds::explo::objects::discovered = 	node_exploration["discovered"].as<decimal_n>();
	thresholds::explo::objects::interesting = 	node_exploration["interesting"].as<decimal_n>();
	thresholds::explo::objects::boring = 		node_exploration["boring"].as<decimal_n>();
	
	thresholds::explo::influence::barrier = 		node_influence["barrier"].as<decimal_n>();
	thresholds::explo::influence::candle = 			node_influence["candle"].as<decimal_n>();
	thresholds::explo::influence::unknown = 		node_influence["unknown"].as<decimal_n>();
	thresholds::explo::influence::candle_blown = 	node_influence["candle_blown"].as<decimal_n>();
	thresholds::explo::influence::discovered = 		node_influence["discovered"].as<decimal_n>();
	thresholds::explo::influence::interesting = 	node_influence["interesting"].as<decimal_n>();
	thresholds::explo::influence::boring = 			node_influence["boring"].as<decimal_n>();
	
	properties::camera::angle_horizontal = 				node_camera["angle_horizontal"].as<decimal_n>();
	properties::camera::angle_vertical = 				node_camera["angle_vertical"].as<decimal_n>();
	properties::camera::size_recognition_horizontal = 	node_camera["size_recognition_horizontal"].as<unsigned_n>();
	properties::camera::size_recognition_vertical = 	node_camera["size_recognition_vertical"].as<unsigned_n>();
	properties::camera::size_footage_horizontal = 		node_camera["size_footage_horizontal"].as<unsigned_n>();
	properties::camera::size_footage_vertical = 		node_camera["size_footage_vertical"].as<unsigned_n>();
	properties::camera::size_footage_vertical = 		node_camera["size_footage_vertical"].as<unsigned_n>();
	std::cout << properties::information << std::endl;
	
	//~ std::ofstream fout("../defines/config.yaml");
	//~ fout << config;	
	}

#endif // yaml_worker_cpp
