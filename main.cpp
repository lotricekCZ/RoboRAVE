#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <torch/script.h> // One-stop header.
#include <memory>

#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <inttypes.h>
#include <cmath>
#include <thread>
#include <chrono>
#include <future>
#include <limits>
#include <ctime>
#include <iostream>

#include "./utils/data_containers/setters/setters.tpp"
#include "./utils/data_containers/speeds/speeds.cpp"
#include "./utils/data_containers/coordinates/coordinates.cpp"
#include "./utils/data_containers/map/include.hpp"
#include "./utils/log_maintainer/log_maintain.hpp"
#include "./utils/data_containers/angles/angles/angles.cpp"
#include "./utils/planners/planner/planner.cpp"
#include "./defines/typedefines.h"

#define my_max(a, b) ((a>b)?a:b)

#include "./defines/constants.h"
#include "./defines/yaml_worker.cpp"

//~ const decimal_n omega_wheel_const = (pi * r_wheel) / (N_wheel * dist_wheel);
//~ const decimal_n wheel_step_lenght_const = (2 * pi * r_wheel) / (N_wheel);9

#include "./tank/tank.h"
#include "./elements/radius/radius.h"
#include "./utils/logic/logic.cpp"

#include "./hardware_interfaces/serial/serial.cpp"
#include "./hardware_interfaces/fire_sensors/fire_sensor.cpp"

decimal_n calculate_omega(decimal_n T_avg = 0){
	//~ printf("omega con %f\nTavg %f\n %.20Lf\n", omega_wheel_const, T_avg, pi);
	return (omega_wheel_const * T_avg);
	}

decimal_n calculate_T_avg(decimal_n T_left = 0, decimal_n T_right = 0){
	return ((T_right - T_left) / (decimal_n)(T_right * T_left));
	}

decimal_n calculate_distance_wheel(decimal_n period, decimal_n time){
	return abs((time * wheel_step_lenght_const)/(decimal_n)period);
	}

decimal_n c_f(char * input){
	return (decimal_n)atof(input);
	}

signed_n c_i(char * input){
	return atoi(input);
	}

decimal_n get_gamma(signed_n x_rel, signed_n y_rel){
	return atan((decimal_n)y_rel / (decimal_n)x_rel);
	}
	
decimal_n get_radius(decimal_n x_rel, decimal_n y_rel){
	return sqrt(pow(x_rel, 2) + pow(y_rel, 2));
	}


decimal_n coords_x(decimal_n alpha, decimal_n gamma, decimal_n radius, uint8_t dec){
	return (((dec >> 1) & 1? 1 : -1))*cos((alpha) + ((dec & 1)? (1) : (-1))* gamma)*radius;
	}

decimal_n coords_y(decimal_n alpha, decimal_n gamma, decimal_n radius, uint8_t dec){
	return (((dec >> 1) & 1? 1 : -1))*sin((alpha) + ((dec & 1)? (1) : (-1))* gamma)*radius;
	}
	
/*
 * 
 * name: coords_n
 * @param alpha - aktualni natoceni v prostoru
 * @param rel - relative coordinates / vector
 * @return delta souradnic v realnem prostoru
 * 
 */

coordinates coords_n(decimal_n alpha, coordinates rel){
	return coordinates(rel.x * cos(alpha) - (rel.y * sin(alpha)), rel.x * sin(alpha) + (rel.y * cos(alpha)));
	}





int main(int argc, char *argv[]) {
	load_config();
	auto start = std::chrono::steady_clock::now();
	switch(c_i(argv[1])){
		case 1:
			log_writer("dear Odin, fuck you", "general.txt");
			break;
			
		case 2:
			printf("result %.10f\n", calculate_T_avg(c_f(argv[2]), c_f(argv[3])));
			break;
			
		case 3:
			printf("result %.10f\n", get_radius(c_f(argv[2]), c_f(argv[3])));
			break;
		
		case 4:{
			coordinates a(-1, -2);
			coordinates b(1, -1);
			// ocekavane - 3, 4
			decimal_n ang = -pi_const/2;
			switch(c_i(argv[2])){
				case 0:
					ang = pi_const/4;
					break;
				case 1:
					ang = 3*pi_const/4;
					break;
				case 2:
					ang = 5*pi_const/4;
					break;
				case 3:
					ang = 7*pi_const/4;
					break;
				case 4:
					ang = pi_const;
					break;
				case 5:
					ang = pi_const/2.0;
					break;
				case 6:
					ang = -pi_const/2.0;
					break;
				default:
					ang = 0;
					break;
				
				}
			coordinates c = c.make_global(a, b, -3*pi_const/4);
			std::cout << c.x << "; " << c.y << std::endl;
			c = c.make_local(c, a, 3*pi_const/4);
			std::cout << c.x << "; " << c.y << std::endl;
			
			c = c.make_local(sqrt(5), -atan(1.0/2.0));
			std::cout << c.x << "; " << c.y << std::endl;
			//~ c = c.make_global(a, sqrt(5), pi/2 + atan(2));
			//~ std::cout << c.x << "; " << c.y << std::endl;
			//~ std::fstream f("t_1.svg", std::ios_base::app);
			//~ for(uint8_t i = 0; i < 60; i++){
				//~ c = c.make_global(a, coordinates(0, 4), -pi/2 + (decimal_n)i*1.6*(pi/180.0));
				//~ f << "<circle r=\"0.7080836\" cy=\""<< std::to_string(80.240021 + c.y*13) \
					//~ <<"\" cx=\"" << std::to_string(93.624962 + c.x*13) << "\"style=\"fill:#000000;stroke:none;stroke-width:22.1243;stroke-miterlimit:4;stroke-dasharray:none\"id=\"path2"<< std::to_string(i)<<"\" />" << std::endl;
				
				//~ c = c.make_global(a, coordinates(4, 2), +pi/2+(decimal_n)i*(pi/180.0));
				//~ f << "<circle r=\"1.080836\" cy=\""<< std::to_string(80.240021 + c.y*10) \
					//~ <<"\" cx=\"" << std::to_string(93.624962 + c.x*10) << "\"style=\"fill:#000000;stroke:none;stroke-width:22.1243;stroke-miterlimit:4;stroke-dasharray:none\"id=\"path3"<< std::to_string(i)<<"\" />" << std::endl;
				
				//~ c = c.make_global(a, coordinates(3, 0), +pi/2+(decimal_n)i*(pi/180.0));
				//~ f << "<circle r=\"0.580836\" cy=\""<< std::to_string(80.240021 + c.y*10) \
					//~ <<"\" cx=\"" << std::to_string(93.624962 + c.x*10) << "\"style=\"fill:#000000;stroke:none;stroke-width:22.1243;stroke-miterlimit:4;stroke-dasharray:none\"id=\"path3"<< std::to_string(i)<<"\" />" << std::endl;
				//~ std::cout << c.x << "; "<< c.y << std::endl;
				//~ /// tenci je 3; 0
				//~ }
			//~ c = c.make_global(a, coordinates(4, 2), -pi/2);
			//~ f << "<circle r=\"2.7080836\" cy=\""<< std::to_string(80.240021 - c.y*10) \
					//~ <<"\" cx=\"" << std::to_string(93.624962 - c.x*10) << "\"style=\"fill:#ff0000;stroke:#ff0000;stroke-width:22.1243;stroke-miterlimit:4;stroke-dasharray:none\"id=\"path5"<< std::to_string(46)<<"\" />" << std::endl;
			
			//~ c = c.make_global(a, coordinates(4, 2), +pi/2);
			//~ f << "<circle r=\"2.7080836\" cy=\""<< std::to_string(80.240021 + c.y*10) \
					//~ <<"\" cx=\"" << std::to_string(93.624962 + c.x*10) << "\"style=\"fill:#ff0000;stroke:#ff0000;stroke-width:22.1243;stroke-miterlimit:4;stroke-dasharray:none\"id=\"path5"<< std::to_string(46)<<"\" />" << std::endl;
			
			//~ c = c.make_global(a, coordinates(3, 0), +pi/2);
			//~ f << "<circle r=\"2.7080836\" cy=\""<< std::to_string(80.240021 + c.y*10) \
					//~ <<"\" cx=\"" << std::to_string(93.624962 + c.x*10) << "\"style=\"fill:#ff0000;stroke:#ff0000;stroke-width:22.1243;stroke-miterlimit:4;stroke-dasharray:none\"id=\"path5"<< std::to_string(55)<<"\" />" << std::endl;
			//~ f << "\n</g>\n</svg>\n";
			break;
		}
		case 5:{
			auto var = std::async(c_f, argv[2]);
			auto var1 = std::async(c_f, argv[3]);
			tank t;
			t.assign_speeds(var.get(), var1.get());
			break;
			}
		
		case 6:{
			auto var = std::async(c_f, argv[2]);
			auto var1 = std::async(c_f, argv[3]);
			
			float x = var.get();
			float y = var1.get();
			
			decimal_n rad = radius::from_speeds(x, y);
			std::cout << "poloměr: " << rad+dist_wheel/2 << " m" << std::endl;
			
			break;
			}
			
		case 7:{
			auto var = std::async(c_f, argv[2]);
			auto var1 = std::async(c_f, argv[3]);
			
			float x = var.get();
			float y = var1.get();
			tank t;
			t.assign_speeds(x, y);
			decimal_n rad = radius::from_speeds(t.velocities.left, t.velocities.right);
			coordinates r = radius::coords(rad, get_radius(x, y), x, y);
			std::cout << r.x << " "<< r.y << std::endl;
			break;
			}
			
		case 8:{
			uint8_t c = std::thread::hardware_concurrency();
			
			map m;
			for (uint16_t g = 0; g < 32; g++){
				std::vector<std::future< std::vector<location> > > o;
				for (uint8_t t = 0; t < c; t ++){
					o.push_back(std::move(std::async(&map::grid, m, t * map_h / c, 0, ((t+1) * map_h / c), map_l)));
					
					}
				for (auto &i: o){
					std::vector<location> out = i.get();
					
					m._map.insert(m._map.begin(), out.begin(), out.end());
					
					}
				//~ std::cout << "size " << m._map.size() << std::endl;
				m._map.clear();
				//~ for (auto d: m._map){
					
					//~ std::cout << d._coordinates.x << std::endl;
					//~ }
				
				}
			}
			
		case 9:{
			uint8_t c = std::thread::hardware_concurrency();
			
			map m;
			std::vector<std::future < std::vector<location> > > o;
			for (uint8_t t = 0; t < c; t ++){
				o.push_back(std::move(std::async(&map::grid, m, t * map_h / c, 0, ((t+1) * map_h / c), map_l)));
				
				}
			for (auto &i: o){
				std::vector<location> out = i.get();
				
				m._map.insert(m._map.begin(), out.begin(), out.end());
				
				}
		
		
			m._map[0].set_point(location::_discovered);
			m._map[30].set_point(location::_candle);
			std::cout << "x: " << m._map[0]._coordinates.x << "  y: " << m._map[0]._coordinates.y << std::endl;
			location loo = m.interest_calculate();
			std::cout << "x: " << loo._coordinates.x << "  y: " << loo._coordinates.y << std::endl;
			m.interest_map();
			decimal_n loc = m.calculate_location(location(10, 10));
			std::cout << "interest: " << loc << "\n";
			std::cout << radius::from_3_points(coordinates(4, 4), coordinates(-1, 1), coordinates(2, 4));
			coordinates d = radius::coords(coordinates(0, 0), coordinates(2, 2), coordinates(-1, 2.5));
			std::cout << "\nx: " << d.x << " y: " << d.y <<"\n";
			}
		
		case 10:{
			std::vector<coordinates> c = radius::tangent_points(coordinates(c_f(argv[2]), c_f(argv[3])), c_f(argv[3]), coordinates(c_f(argv[4]), c_f(argv[5])));
			if(c.size() == 2)
				std::cout <<  c[0].x << "; "<< c[0].y << "\n" << c[1].x << "; "<< c[1].y <<  std::endl;
			}
			
		case 11:{
			coordinates a(0, 0);
			decimal_n ang = -pi_const/4;
			switch(c_i(argv[2])){
				case 0:
					ang = pi_const/4;
					break;
				case 1:
					ang = 3*pi_const/4;
					break;
				case 2:
					ang = 5*pi_const/4;
					break;
				case 3:
					ang = 7*pi_const/4;
					break;
				default:
					ang = 0;
					break;
				
				}
			//~ decimal_n ang = 0;
			//~ decimal_n ang = -pi_const/6;
			decimal_n len = 5;
			coordinates c = a.make_local(len, ang);
			std::cout << c.x << "; " << c.y << std::endl;
			break;			
			}
			
		case 12:{
			coordinates a(0, 0);
			coordinates b(-1, -1);
			// ocekavane - 3, 4
			decimal_n ang = -pi_const/2;
			switch(c_i(argv[2])){
				case 0:
					ang = pi_const/4;
					break;
				case 1:
					ang = 3*pi_const/4;
					break;
				case 2:
					ang = 5*pi_const/4;
					break;
				case 3:
					ang = 7*pi_const/4;
					break;
				case 4:
					ang = pi_const;
					break;
				case 5:
					ang = pi_const/2.0;
					break;
				case 6:
					ang = -pi_const/2.0;
					break;
				default:
					ang = 0;
					break;
				
				}
			//~ decimal_n ang = -pi_const/6;
			//~ decimal_n ang = 0;
			coordinates c = coords_n(ang+pi_const/2, b);
			std::cout << c.x << "; " << c.y << std::endl;
			break;
			}
			
		case 13:{
			coordinates c = line().intersection(line(0, 2, -14), line(-3, 5, -4));
			std::cout << c.x << "; " << c.y << std::endl;
			std::vector<coordinates> a = circle().intersection(line(-1, 1, 1), circle(1, 2, 3));
			std::cout << a[1].x << "; " << a[1].y << std::endl;
			
			a = circle().intersection(circle(1, 1, 2), circle(1, 2, 3));
			std::cout << a[a.size()-1].x << "; " << a[a.size()-1].y << std::endl;
			std::cout << a.size() << std::endl;
			break;
			}
		case 14:{
			line l(1, 1, 4);
			line d = l.make_parallel(coordinates(2, 5));
			std::cout << d.print(d) << std::endl;
			break;
			}
			
		case 15:{
			coordinates points[4] = {coordinates(1, 1), coordinates(0, 2), coordinates(4, 6), coordinates(5, 5)};
			wall w(points);
			bool c = w.inside(coordinates(c_f(argv[2]), c_f(argv[3])));
			std::cout << c << std::endl;
			std::vector<coordinates>  co = w.is_collision_course(line(-1, 1, 1));
			std::cout << co[co.size()-1].print() << std::endl;
			for(uint8_t i = 0; i < 4; i++)
				std::cout << w.properties.walls[i].print(w.properties.walls[i]) << std::endl;
			break;
			}
			
		case 16:{
			
			map m;
			coordinates c[] = {coordinates(-10, 3), coordinates(-11, 4), coordinates(-7, 7), coordinates(-6, 6)};
			coordinates x[] = {coordinates(1, 1), coordinates(0, 2), coordinates(4, 6), coordinates(5, 5)};
			
			m._map_walls.push_back(wall(c));
			m._map_walls.push_back(wall(x));
			std::cout << m._map_walls[0].is_collision_course(circle(coordinates(-5, 2), 6))[1].print() << std::endl;
			angles a = angles().load_virtual(coordinates(-5, 2), m);
			for(auto i: a)
				std::cout << "uhel: " << i.angle << "   vzdalenost: " << i.distance << "\t" << i.position._coordinates.print() << std::endl;
			break;
			}
			
		case 17:{ 
			/// this creates map and does math to calculations to make heatmap, therefore selecting the hottest spot and designing trace to it
			map m;
			m._map = m.grid(0, 0, 150, 150);
			coordinates c[] = {coordinates(-10, 3), coordinates(-11, 4), coordinates(-7, 7), coordinates(-6, 6)};
			coordinates x[] = {coordinates(1, 1), coordinates(0, 2), coordinates(4, 6), coordinates(5, 5)};
			coordinates z[] = {coordinates(10, 10), coordinates(0, 20), coordinates(40, 60), coordinates(50, 50)};
			
			m.append(candle(coordinates(4,3)));
			m.append(wall(c));
			m.append(wall(x));
			m.append(wall(z));
			//~ std::cout << m._map_walls[0].is_collision_course(circle(coordinates(-5, 2), 6))[1].print() << std::endl;
			angles a = angles().load_virtual_circular(coordinates(-5, 2), m, 0, 20, 0.06);
			//~ angles a = angles().load_virtual(coordinates(-5, 2), m);
			for(auto i: a)
				std::cout << "uhel: " << i.angle << "   vzdalenost: " << i.distance << "\t" << i.position._coordinates.print() << std::endl;
			std::cout << m._map_walls[0].get_box()[1].print() << "\t" << m._map_walls[0].get_box()[0].print() << std::endl;
			std::cout << m._map_candles[0].get_box()[1].print() << "\t" << m._map_candles[0].get_box()[0].print() << std::endl;
			//~ m.strip({coordinates(10, 10), coordinates(60, 60)})[0] -> set_point(location::_candle);
			m.edit_map(z);
			m.interest_calculate();
			m.interest_map();
			break;
			}
			
		case 18:{ 
			std::cout << ((c_f(argv[2]) < 0)? 360:0) + atan2(c_f(argv[2]), c_f(argv[3])) * 180/pi_const << std::endl;
			break;
			}
			
		case 19:{
			std::cout << circle().intersection(circle().circle_tangents(circle(coordinates(-6, -2), 5), circle(coordinates(6, 9), 5))[0], circle(coordinates(-6, -2), 5))[0].print() << std::endl;
			break;
			}
			
		case 20:{
			std::cout << step(coordinates(-50, 10), coordinates(0, 60), coordinates(0, 10)).inkscape_print() << std::endl;
			break;
			}
		
		case 21:{ 
			/// this creates map and does math to calculations to make heatmap, therefore selecting the hottest spot and designing trace to it
			map m;
	
			coordinates c[] = {coordinates(-10, 3), coordinates(-11, 4), coordinates(-7, 8), coordinates(-6, 7)};
			coordinates x[] = {coordinates(1, 1), coordinates(0, 2), coordinates(4, 6), coordinates(5, 5)};
			coordinates y[] = {coordinates(-1, 1), coordinates(0, 2), coordinates(4, -2), coordinates(3, -3)};
			coordinates z[] = {coordinates(4, 6), coordinates(5, 7), coordinates(9, 3), coordinates(8, 2)};
			
			//~ m.append(candle(coordinates(4,3)));
			m.append(wall(c));
			m.append(wall(x));
			m.append(wall(y));
			//~ m.append(wall(z));
			planner p;
			//~ angles a = angles().load_virtual(coordinates(-5, 2), m);
			//~ for(auto i: a)
			//~ std::cout << a.get_angle(0).position._coordinates.print() << std::endl;
			//~ std::cout << a.get_angle(0).distance << std::endl;
			//~ std::cout << a.size() << std::endl;
			std::vector <circle> plan = p.circle_generate(coordinates(c_f(argv[2]), c_f(argv[3])), coordinates(-5, 2), m, c_i(argv[4]));
			//~ std::vector <line> clan = p.plan_trace(plan, coordinates(c_f(argv[2]), c_f(argv[3])), coordinates(-5, 2), m);
			//~ std::cout << m._map_walls[0].is_collision_course(circle(coordinates(-5, 2), 6))[1].print() << std::endl;
			std::srand(std::time(nullptr)); 
				
			for(auto i: plan)
				std::cout << i.print() << std::endl;
			
			//~ for(auto i: p.coincidental_points_generate(plan))
				//~ std::cout << i.print() << std::endl;
			std::vector<coordinates> g = p.coincidental_points_generate(plan);
			p.make_path(g, coordinates(-5, 2), coordinates(c_f(argv[2]), c_f(argv[3])), m);
			
			//~ for(auto i: clan)
				//~ std::cout << i.print() << std::endl;
			//~ m.strip({coordinates(10, 10), coordinates(60, 60)})[0] -> set_point(location::_candle);
			//~ for(uint8_t i = 0; i < 255; i++){
				//~ std::cout << line((decimal_n)((std::rand() % 256)-128)/128.0, ((decimal_n)((std::rand() % 256)-128))/128.0, 0).make_parallel(coordinates(-5, 2)).print() << std::endl;
				//~ }
			break;
			}
			
		case 22:{
			std::cout << (coordinates(-50, 10) == coordinates(c_f(argv[2]), c_f(argv[3]))) << std::endl;
			break;
			}
			
		case 23:{
			std::cout << std::to_string(speeds().to_hw_speed(c_f(argv[2]))) << std::endl;
			std::cout << std::to_string(speeds().from_hw_speed(c_f(argv[3]))) << std::endl;
			break;
			}
			
			
		case 24:{
			using namespace cv;
			const decimal_n FPS_SMOOTHING = 0.9;
			cv::VideoCapture cap(0);//cap.set(cv::CAP_PROP_FRAME_WIDTH, 4);
		    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 800);
		    //~ dnn::readNetFromONNX
		    //~ dnn::DetectionModel d("best.mlmodel");
		    cap.set(cv::CAP_PROP_FPS, 8);
		    //~ std::vector<int> classIds;
		    //~ std::vector<float> confidences;
			//~ std::vector<cv::Rect> boxes;
			static const std::string wname = "n";
		    cv::Mat frame;
		    cv::namedWindow(wname);
		    //~ Mat edit;
		    float fps = 0.0;
		    double prev = clock(); 
		    while (true){
		        double now = (clock()/(double)CLOCKS_PER_SEC);
		        
		        fps = (fps*FPS_SMOOTHING + (1/(now - prev))*(1.0 - FPS_SMOOTHING));
		        prev = now;
				
		        printf("fps: %.1f\n", fps);
		
		        if (cap.isOpened()){
		            cap.read(frame);
		            //~ d.detect(frame, classIds, confidences, boxes);
		        }
		        cvtColor(frame, frame, COLOR_BGR2GRAY);
				GaussianBlur(frame, frame, Size(5, 5), 1.5);
				cv::Canny(frame, frame, 50, 200);       
		        cv::imshow(wname, frame);
		        //~ cv::imwrite("heck.png", frame);
		        //~ imshow("edit", edit);
		        if (cv::waitKey(2) == 27){
		            break;
		        }
		    }
			}
			
		case 25:{
			map m;
			
			coordinates x[] = {coordinates(1, 1), coordinates(0, 2), coordinates(4, 6), coordinates(5, 5)};
			coordinates y[] = {coordinates(-1, 1), coordinates(0, 2), coordinates(4, -2), coordinates(3, -3)};
			
			m.append(wall(x));
			//~ m.append(wall(y));
			
			dijkstra d(m);
			
			//~ dijk_node a(1, x[0]);
			//~ dijk_node b(2, x[1]);
			//~ dijk_node c(3, x[2]);
			
			std::vector<coordinates> coords;
			coords.push_back(coordinates(-5, 2));
			coords.push_back(coordinates(1, 4));
			coords.push_back(coordinates(0, -1));
			coords.push_back(coordinates(4, -1));
			coords.push_back(coordinates(4, 9));
			coords.push_back(coordinates(7, 7));
			coords.push_back(coordinates(4, 3));
			
			d.nodes = d.generate_nodes(coords, coords[0]);
			d.p_nodes = d.generate_node_pointers(d.nodes);

			d.edges = d.generate_edges(d.nodes, m);
			d.p_edges = d.generate_edge_pointers(d.edges);
			//~ d.nodes.push_back(&a);
			//~ d.nodes.push_back(&b);
			//~ d.nodes.push_back(&c);
			//~ a.distance_start = 0;
			std::vector<dijk_node> nodes = d.dijkstras(d.p_nodes, d.p_edges);
			//~ std::cout << d.nodes[5].id << std::endl;
			//~ std::cout << d.nodes[2].id << std::endl;
			//~ std::cout << d.nodes[4].id << std::endl;
			for(auto i: nodes){
				std::cout << i.id << "  " << i.distance_start << " " << i.coords -> print() << std::endl;
				}
			std::cout << std::endl << d.nodes.size() << std::endl;
			for(auto &o: nodes)
				if(*o.coords == coords[5]){
					d.print_shortest_route(&o);
					break;
					}
			//~ d.print_shortest_route(d.nodes[4]);
			break;
			}
			
			case 26:{
				std::cout << line(coordinates(c_f(argv[2]), c_f(argv[3])), coordinates(4, -4)).make_perpendicular(coordinates(4, -4)).print() << std::endl;
				std::cout << line(coordinates(c_f(argv[2]), c_f(argv[3])), coordinates(4, -4)).print() << std::endl;
				break;
				}
				
			case 27:{
				coordinates x[] = {coordinates(1, 1), coordinates(0, 2), coordinates(4, 6), coordinates(5, 5)};
				coordinates y[] = {coordinates(-1, 1), coordinates(0, 2), coordinates(4, -2), coordinates(3, -3)};
				map m;	
				m.append(wall(x));
				m.append(wall(y));
				
				std::cout << m.closest_wall(coordinates(2, 5)).closest_point(coordinates(2, 5)).print() << std::endl;				
				break;
				}
				
			case 28:{
				std::cout << line(c_f(argv[2]), c_f(argv[3]), 0).print() << std::endl;				
				std::cout << line(c_f(argv[2]), c_f(argv[3]), 0).get_angle()/pi_const*180 << std::endl;				
				}
				
			case 29:{
				std::cout << line(c_f(argv[2]), c_f(argv[3]), 0).print() << std::endl;				
				std::cout << line(line(c_f(argv[2]), c_f(argv[3]), 0).get_angle(), coordinates(1, 1)).print() << std::endl;				
				break;
				}
				
			case 30:{
				std::cout << line(1, 0, -3).print() << std::endl;				
				std::cout << line(c_f(argv[2]), c_f(argv[3]), c_f(argv[4])).print() << std::endl;				
				std::cout << line().make_axis(line(1, 0, -3), line(c_f(argv[2]), c_f(argv[3]), c_f(argv[4]))).print() << std::endl;				
				break;
				}
				
			case 31:{
				std::cout << line(1, 2, -3).print() << std::endl;				
				std::cout << line().get_distance(line(1, 2, -3), coordinates(c_f(argv[2]), c_f(argv[3]))) << std::endl;
				break;
				}
				
			case 32:{
				std::cout << line(1, 2, -3).print() << std::endl;				
				std::cout << line(1, 2, -3).get_distance(line(1, 2, c_f(argv[2]))) << std::endl;
				break;
				}
				
			case 34:{
				std::cout << circle(coordinates(2, 0), 2).print() << std::endl;				
				std::cout << circle(coordinates(2, 0), 2).on_segment(coordinates(0, 0), coordinates(2, 2), coordinates(4, 0), 1) << std::endl;				
				break;
				}
				
			case 35:{
				step s(coordinates(1, 1), coordinates(c_f(argv[2]), c_f(argv[3])));
				std::pair<step, step> steps = step::get_perimeters(s, 2);
				std::cout << std::get<line>(s.formula).print() << std::endl;
				std::cout << std::get<line>(std::get<0>(steps).formula).print() << std::endl;
				std::cout << std::get<line>(std::get<1>(steps).formula).print() << std::endl;
				break;
				}
				
			case 36:{
				step s(coordinates(0, 0), coordinates(3, 3), coordinates(c_f(argv[2]), c_f(argv[3])));
				std::pair<step, step> steps = step::get_perimeters(s, 2);
				std::cout << std::get<circle>(s.formula).print() << std::endl;
				std::cout << std::get<circle>(std::get<0>(steps).formula).print() << std::endl;
				std::cout << std::get<circle>(std::get<1>(steps).formula).print() << std::endl;
				std::cout << std::get<0>(steps).start.print() << "\t" << std::get<0>(steps).end.print() << std::endl;
				std::cout << std::get<1>(steps).start.print() << "\t" << std::get<1>(steps).end.print() << std::endl;
				break;
				}
				
			case 37:{
				for(auto a: circle().circles(line(1, 8, 5), line(c_f(argv[2]), 3, 0), 2))
					std::cout << a.print() << std::endl;
				std::cout << line(1, 8, 5).print() << std::endl;
				std::cout << line(c_f(argv[2]), 3, 0).print() << std::endl;
				break;
				}
				
			case 38:{ 
			/// this creates map and does math to calculations to make heatmap, therefore selecting the hottest spot and designing trace to it
			map m;
	
			coordinates c[] = {coordinates(-10, 3), coordinates(-11, 4), coordinates(-7, 8), coordinates(-6, 7)};
			coordinates x[] = {coordinates(1, 1), coordinates(0, 2), coordinates(4, 6), coordinates(5, 5)};
			coordinates y[] = {coordinates(-1, 1), coordinates(0, 2), coordinates(4, -2), coordinates(3, -3)};
			coordinates z[] = {coordinates(4, 6), coordinates(5, 7), coordinates(9, 3), coordinates(8, 2)};
			
			//~ m.append(candle(coordinates(4,3)));
			m.append(wall(c));
			m.append(wall(x));
			m.append(wall(y));
			//~ m.append(wall(z));
			planner p;
			//~ angles a = angles().load_virtual(coordinates(-5, 2), m);
			//~ for(auto i: a)
			//~ std::cout << a.get_angle(0).position._coordinates.print() << std::endl;
			//~ std::cout << a.get_angle(0).distance << std::endl;
			//~ std::cout << a.size() << std::endl;
			std::vector <circle> plan = p.circle_generate(coordinates(c_f(argv[2]), c_f(argv[3])), coordinates(-5, 2), m, c_i(argv[4]));
			//~ std::vector <line> clan = p.plan_trace(plan, coordinates(c_f(argv[2]), c_f(argv[3])), coordinates(-5, 2), m);
			//~ std::cout << m._map_walls[0].is_collision_course(circle(coordinates(-5, 2), 6))[1].print() << std::endl;
			std::srand(std::time(nullptr)); 
				
			//~ for(auto i: plan)
				//~ std::cout << i.print() << std::endl;
			
			//~ for(auto i: p.coincidental_points_generate(plan))
				//~ std::cout << i.print() << std::endl;
			std::vector<coordinates> g = p.coincidental_points_generate(plan);
			std::vector<coordinates> c_plan = p.make_path(g, coordinates(-5, 2), coordinates(c_f(argv[2]), c_f(argv[3])), m);
			p.plan_make(c_plan, m, c_f(argv[5])*pi_const/c_f(argv[6]));
			
			break;
			}
			
			case 39:{
				std::cout << circle(1, 2, 3).get_distance(coordinates(c_f(argv[2]), c_f(argv[3])), coordinates(c_f(argv[4]), c_f(argv[5]))) << std::endl;
				std::cout << circle(1, 2, 3).print() << std::endl;
				break;
				}
				
			case 41:{
				std::fstream f("outrandom.txt", std::fstream::out);
				coordinates c(0, 0);
				coordinates a(-1, -2);
				for(unsigned_n i = 0; i < 90; i++){
					c = c.make_global(a, coordinates(0, 0.7+i/16.0), -pi_const/2 + (decimal_n)i*8*(pi_const/180.0));
					f << "<circle r=\"" << std::to_string((i+16)*(1.080836/384))<< "\" cy=\""<< std::to_string(80.240021 + c.y*5) \
						<<"\" cx=\"" << std::to_string(93.624962 + c.x*5) << "\"style=\"fill:#000000;stroke:none;stroke-width:22.1243;stroke-miterlimit:4;stroke-dasharray:none\"id=\"path4"<< std::to_string(i)<<"\" />" << std::endl;
					
					
					c = c.make_global(a, coordinates(0, 1.4+i/16.0), pi_const/2 + (decimal_n)i*8*(pi_const/180.0));
					f << "<circle r=\"" << std::to_string((i+16)*(1.080836/384))<< "\" cy=\""<< std::to_string(80.240021 + c.y*5) \
						<<"\" cx=\"" << std::to_string(93.624962 + c.x*5) << "\"style=\"fill:#000000;stroke:none;stroke-width:22.1243;stroke-miterlimit:4;stroke-dasharray:none\"id=\"path4"<< std::to_string(i)<<"\" />" << std::endl;
					
					c = c.make_global(a, coordinates(0, 0.7+i/16.0), pi_const + (decimal_n)i*8*(pi_const/180.0));
					f << "<circle r=\"" << std::to_string((i+16)*(1.080836/384))<< "\" cy=\""<< std::to_string(80.240021 + c.y*5) \
						<<"\" cx=\"" << std::to_string(93.624962 + c.x*5) << "\"style=\"fill:#000000;stroke:none;stroke-width:22.1243;stroke-miterlimit:4;stroke-dasharray:none\"id=\"path4"<< std::to_string(i)<<"\" />" << std::endl;
					
					
					c = c.make_global(a, coordinates(0, 1.4+i/16.0), 0 + (decimal_n)i*8*(pi_const/180.0));
					f << "<circle r=\"" << std::to_string((i+16)*(1.080836/384))<< "\" cy=\""<< std::to_string(80.240021 + c.y*5) \
						<<"\" cx=\"" << std::to_string(93.624962 + c.x*5) << "\"style=\"fill:#000000;stroke:none;stroke-width:22.1243;stroke-miterlimit:4;stroke-dasharray:none\"id=\"path4"<< std::to_string(i)<<"\" />" << std::endl;
					
					c = c.make_global(a, coordinates(0, 0.7+i/16.0), 7*pi_const/4 + (decimal_n)i*8*(pi_const/180.0));
					f << "<circle r=\"" << std::to_string((i+16)*(1.080836/384))<< "\" cy=\""<< std::to_string(80.240021 + c.y*5) \
						<<"\" cx=\"" << std::to_string(93.624962 + c.x*5) << "\"style=\"fill:#000000;stroke:none;stroke-width:22.1243;stroke-miterlimit:4;stroke-dasharray:none\"id=\"path4"<< std::to_string(i)<<"\" />" << std::endl;
					
					
					c = c.make_global(a, coordinates(0, 1.4+i/16.0), pi_const/4 + (decimal_n)i*8*(pi_const/180.0));
					f << "<circle r=\"" << std::to_string((i+16)*(1.080836/384))<< "\" cy=\""<< std::to_string(80.240021 + c.y*5) \
						<<"\" cx=\"" << std::to_string(93.624962 + c.x*5) << "\"style=\"fill:#000000;stroke:none;stroke-width:22.1243;stroke-miterlimit:4;stroke-dasharray:none\"id=\"path4"<< std::to_string(i)<<"\" />" << std::endl;
					
					c = c.make_global(a, coordinates(0, 0.7+i/16.0), 3*pi_const/4 + (decimal_n)i*8*(pi_const/180.0));
					f << "<circle r=\"" << std::to_string((i+16)*(1.080836/384))<< "\" cy=\""<< std::to_string(80.240021 + c.y*5) \
						<<"\" cx=\"" << std::to_string(93.624962 + c.x*5) << "\"style=\"fill:#000000;stroke:none;stroke-width:22.1243;stroke-miterlimit:4;stroke-dasharray:none\"id=\"path4"<< std::to_string(i)<<"\" />" << std::endl;
					
					
					c = c.make_global(a, coordinates(0, 1.4+i/16.0), 5*pi_const/4 + (decimal_n)i*8*(pi_const/180.0));
					f << "<circle r=\"" << std::to_string((i+16)*(1.080836/384))<< "\" cy=\""<< std::to_string(80.240021 + c.y*5) \
						<<"\" cx=\"" << std::to_string(93.624962 + c.x*5) << "\"style=\"fill:#000000;stroke:none;stroke-width:22.1243;stroke-miterlimit:4;stroke-dasharray:none\"id=\"path4"<< std::to_string(i)<<"\" />" << std::endl;
					
					}
				f.close();
				break;
				}
				
			case 40:{
				circle start1(coordinates(3, 0), 3);
				circle start2(coordinates(-3, 0), 3);
				std::array<circle, 13> possible = {
					circle(coordinates(-3, 3*3), 2.5),
					circle(coordinates(1, 6), 2.5),
					circle(coordinates(6*2, 3*3), 2.5),
					circle(coordinates(-6*2, 3*3), 2.5),
					circle(coordinates(6*2, 3), 2.5),
					circle(coordinates(-6*2, 3), 2.5),
					circle(coordinates(6*2, -3), 2.5),
					circle(coordinates(-6*2, -3), 2.5),
					circle(coordinates(6*2, 3*-3), 2.5),
					circle(coordinates(-6*2, 3*-3), 2.5),
					circle(coordinates(3, 3*-3), 2.5),
					circle(coordinates(-3, 3*-3), 2.5),
					circle(coordinates(6, -2.7), 0.5)
					};
				
				std::cout << start1.print() << std::endl;
				std::cout << start2.print() << std::endl;
				
				for(auto &a: possible){
					std::cout << a.print() << std::endl;
					std::cout << a.center.print() << std::endl;
				}
				
				for(auto &a: possible){
					for(auto c: {start1, start2}){
						for(auto &b: circle::circle_tangents(c, a)) {
							decimal_n vector_angle = c.intersection(b)[0].get_gamma(a.intersection(b)[0]);
							decimal_n tangent_angle = c.center.get_gamma(c.intersection(b)[0]);
							decimal_n difference_angle = vector_angle - (tangent_angle + ((c.center.x < 0)?1:-1) * pi_const/2);
							if((std::abs(difference_angle) <= 1e-3 || (std::abs(difference_angle + ((c.center.x < 0)?2:-2)*pi_const) <= 1e-3))){
								std::cout << "=Vector["<< c.intersection(b)[0].print() << ", " << a.intersection(b)[0].print() << "]" << std::endl;
								}
							}
						}
					}
				break;
				}
			}
	
    uint8_t c = std::thread::hardware_concurrency();	
    std::cout << " number of cores: " << std::to_string(c) << std::endl;
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	
	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
	return 0;
}
