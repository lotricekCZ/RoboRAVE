#ifndef yaml_worker_cpp
#define yaml_worker_cpp

#include "constants.h"
#include "yaml_worker.hpp"
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
	YAML::Node thresholds		 = config["thresholds"];
	YAML::Node node_mAP			 = thresholds["mAP"];
	YAML::Node node_priority	 = config["priority"];
	YAML::Node node_influence	 = node_priority["influence"];
	YAML::Node node_exploration	 = node_priority["exploration"];
	YAML::Node node_properties	 = config["properties"];
	YAML::Node node_robot		 = node_properties["robot"];
	YAML::Node node_camera		 = node_properties["camera"];
	YAML::Node addressbook		 = config["addressbook"];
	YAML::Node program			 = config["program"];
	
	variables::addressbook::master = 						addressbook["master"].as<uint8_t>();
	variables::addressbook::irduino = 						addressbook["irduino"].as<uint8_t>();
	variables::addressbook::motorduino = 					addressbook["motorduino"].as<uint8_t>();
	variables::addressbook::gndduino = 						addressbook["gndduino"].as<uint8_t>();
	variables::addressbook::stm = 							addressbook["stm"].as<uint8_t>();
	
	variables::properties::logs::calculations = 			config["logs"]["calculations"].as<std::string>();
	variables::properties::logs::actions = 					config["logs"]["actions"].as<std::string>();
	variables::properties::information = 					config["information"].as<std::string>();
	
	variables::thresholds::mAP::candle = 					node_mAP["candle"].as<decimal_n>();
	variables::thresholds::mAP::barrier = 					node_mAP["barrier"].as<decimal_n>();
	variables::thresholds::mAP::fire = 						node_mAP["fire"].as<decimal_n>();
	variables::thresholds::mAP::line_surround = 			node_mAP["line_surround"].as<decimal_n>();
	variables::thresholds::mAP::line_border = 				node_mAP["line_border"].as<decimal_n>();
	variables::thresholds::mAP::Maker_Jakub_Ramaseuski = 	node_mAP["Maker_Jakub_Ramaseuski"].as<decimal_n>();

	variables::thresholds::explo::objects::barrier = 		node_exploration["barrier"].as<decimal_n>();
	variables::thresholds::explo::objects::candle = 		node_exploration["candle"].as<decimal_n>();
	variables::thresholds::explo::objects::unknown = 		node_exploration["unknown"].as<decimal_n>();
	variables::thresholds::explo::objects::candle_blown = 	node_exploration["candle_blown"].as<decimal_n>();
	variables::thresholds::explo::objects::discovered = 	node_exploration["discovered"].as<decimal_n>();
	variables::thresholds::explo::objects::interesting = 	node_exploration["interesting"].as<decimal_n>();
	variables::thresholds::explo::objects::boring = 		node_exploration["boring"].as<decimal_n>();
	
	variables::thresholds::explo::influence::barrier = 		node_influence["barrier"].as<decimal_n>();
	variables::thresholds::explo::influence::candle = 		node_influence["candle"].as<decimal_n>();
	variables::thresholds::explo::influence::unknown = 		node_influence["unknown"].as<decimal_n>();
	variables::thresholds::explo::influence::candle_blown = node_influence["candle_blown"].as<decimal_n>();
	variables::thresholds::explo::influence::discovered = 	node_influence["discovered"].as<decimal_n>();
	variables::thresholds::explo::influence::interesting = 	node_influence["interesting"].as<decimal_n>();
	variables::thresholds::explo::influence::boring = 		node_influence["boring"].as<decimal_n>();
	
	// camera properties
	variables::properties::camera::check_frequency = 				node_camera["check_frequency"].as<decimal_n>();
	variables::properties::camera::angle_horizontal = 				node_camera["angle_horizontal"].as<decimal_n>();
	variables::properties::camera::angle_vertical = 				node_camera["angle_vertical"].as<decimal_n>();
	variables::properties::camera::size_recognition_horizontal = 	node_camera["size_recognition_horizontal"].as<unsigned_n>();
	variables::properties::camera::size_recognition_vertical = 		node_camera["size_recognition_vertical"].as<unsigned_n>();
	variables::properties::camera::size_footage_horizontal = 		node_camera["size_footage_horizontal"].as<unsigned_n>();
	variables::properties::camera::size_footage_vertical = 			node_camera["size_footage_vertical"].as<unsigned_n>();
	variables::limits::minimal::circle = 							node_robot["minimal"]["circle"].as<decimal_n>();
	variables::limits::maximal::circle = 							node_robot["maximal"]["circle"].as<decimal_n>();
	//~ variables::properties::camera::size_footage_vertical = 		node_camera["size_footage_vertical"].as<unsigned_n>();
	
	// program segment start
	variables::program::files::chat = program["files"]["chat"].as<std::string>();
	// program segment end
	
	
	/// sub-file opening
	YAML::Node config_chat = YAML::LoadFile(variables::program::files::chat)["chat"];
	// chat segment start
	#ifdef __arm__
		variables::chat::port = 							config_chat["port-rpi"].as<std::string>();
	#else
		variables::chat::port = 							config_chat["port"].as<std::string>();
	#endif
	variables::chat::check_frequency = 					config_chat["check_frequency"].as<unsigned_n>();
	variables::chat::response_timeout::extended = 		config_chat["response_timeout"]["extended"].as<unsigned_n>();
	variables::chat::response_timeout::normal = 		config_chat["response_timeout"]["normal"].as<unsigned_n>();
	variables::chat::response_timeout::time_critical = 	config_chat["response_timeout"]["time_critical"].as<unsigned_n>();
	
	variables::chat::attempt_count =					config_chat["attempt_count"].as<unsigned_n>();
	variables::chat::port_delay =						config_chat["port_delay"].as<unsigned_b>();
	
	variables::chat::max_queue_sensor =					config_chat["max_queue_sensor"].as<unsigned_n>();
	variables::chat::max_queue_global =					config_chat["max_queue_global"].as<unsigned_b>();
	// chat segment end
	std::cout << variables::properties::information << std::endl;
	
	//~ std::ofstream fout("../defines/config.yaml");
	//~ fout << config;	
	}

#endif // yaml_worker_cpp
