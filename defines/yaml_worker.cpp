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

	tresholds::mAP::candle = 					config["tresholds"]["mAP"]["candle"].as<decimal_n>();
	tresholds::mAP::barrier = 					config["tresholds"]["mAP"]["barrier"].as<decimal_n>();
	tresholds::mAP::fire = 						config["tresholds"]["mAP"]["fire"].as<decimal_n>();
	tresholds::mAP::line_surround = 			config["tresholds"]["mAP"]["line_surround"].as<decimal_n>();
	tresholds::mAP::line_border = 				config["tresholds"]["mAP"]["line_border"].as<decimal_n>();
	tresholds::mAP::Maker_Jakub_Ramaseuski = 	config["tresholds"]["mAP"]["Maker_Jakub_Ramaseuski"].as<decimal_n>();
	
	tresholds::explo::objects::barrier = 		config["priority"]["exploration"]["barrier"].as<decimal_n>();
	tresholds::explo::objects::candle = 		config["priority"]["exploration"]["candle"].as<decimal_n>();
	tresholds::explo::objects::unknown = 		config["priority"]["exploration"]["unknown"].as<decimal_n>();
	tresholds::explo::objects::candle_blown = 	config["priority"]["exploration"]["candle_blown"].as<decimal_n>();
	tresholds::explo::objects::discovered = 	config["priority"]["exploration"]["discovered"].as<decimal_n>();
	tresholds::explo::objects::interesting = 	config["priority"]["exploration"]["interesting"].as<decimal_n>();
	tresholds::explo::objects::boring = 		config["priority"]["exploration"]["boring"].as<decimal_n>();
	
	tresholds::explo::influence::barrier = 		config["priority"]["influence"]["barrier"].as<decimal_n>();
	tresholds::explo::influence::candle = 		config["priority"]["influence"]["candle"].as<decimal_n>();
	tresholds::explo::influence::unknown = 		config["priority"]["influence"]["unknown"].as<decimal_n>();
	tresholds::explo::influence::candle_blown = config["priority"]["influence"]["candle_blown"].as<decimal_n>();
	tresholds::explo::influence::discovered = 	config["priority"]["influence"]["discovered"].as<decimal_n>();
	tresholds::explo::influence::interesting = 	config["priority"]["influence"]["interesting"].as<decimal_n>();
	tresholds::explo::influence::boring = 		config["priority"]["influence"]["boring"].as<decimal_n>();
	
	properties::camera::angle_horizontal = 				config["properties"]["camera"]["angle_horizontal"].as<decimal_n>();
	properties::camera::angle_vertical = 				config["properties"]["camera"]["angle_vertical"].as<decimal_n>();
	properties::camera::size_recognition_horizontal = 	config["properties"]["camera"]["size_recognition_horizontal"].as<unsigned_n>();
	properties::camera::size_recognition_vertical = 	config["properties"]["camera"]["size_recognition_vertical"].as<unsigned_n>();
	properties::camera::size_footage_horizontal = 		config["properties"]["camera"]["size_footage_horizontal"].as<unsigned_n>();
	properties::camera::size_footage_vertical = 		config["properties"]["camera"]["size_footage_vertical"].as<unsigned_n>();
	
	
	//~ std::ofstream fout("../defines/config.yaml");
	//~ fout << config;	
	}

#endif // yaml_worker_cpp
