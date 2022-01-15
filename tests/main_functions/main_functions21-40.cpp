/*
 * main_functions21-40.cpp
 * 
 * Copyright 2021 Jakub Ramašeuski <jakub@skaryna.net>
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


#include "main_functions21-40.hpp"

namespace mf {
	void function21(int argc, char *argv[]){
		#ifndef dont_comp
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
		#endif
		}



	void function22(int argc, char *argv[]){
		#ifndef dont_comp
		std::cout << (coordinates(-50, 10) == coordinates(c_f(argv[2]), c_f(argv[3]))) << std::endl;
		#endif
		}



	void function23(int argc, char *argv[]){
		#ifndef dont_comp
		std::cout << std::to_string(speeds().to_hw_speed(c_f(argv[2]))) << std::endl;
		std::cout << std::to_string(speeds().from_hw_speed(c_f(argv[3]))) << std::endl;
		#endif
		}



	void function24(int argc, char *argv[]){
		#ifndef dont_comp
		using namespace cv;
		const decimal_n FPS_SMOOTHING = 0.9;
		cv::VideoCapture cap(0);//cap.set(cv::CAP_PROP_FRAME_WIDTH, 4);
		//~ cv::VideoCapture cap_1(1);//cap.set(cv::CAP_PROP_FRAME_WIDTH, 4);
		cap.set(cv::CAP_PROP_FRAME_WIDTH, 320);
		cap.set(cv::CAP_PROP_FRAME_HEIGHT, 160);
		//~ dnn::readNetFromONNX
		//~ dnn::DetectionModel d("best.mlmodel");
		cap.set(cv::CAP_PROP_FPS, 2);
		//~ std::vector<int> classIds;
		//~ std::vector<float> confidences;
		//~ std::vector<cv::Rect> boxes;
		static const std::string wname = "n";
		bool m = true;
		cv::Mat frame;
		cv::Mat frame_1;
		cv::Mat rame;
		cv::namedWindow(wname);
		
		cv::namedWindow("b");
		//~ Mat edit;
		float fps = 0.0;
		double prev = clock(); 
		while (true){
		    double now = (clock()/(double)CLOCKS_PER_SEC);
		    
		    fps = (fps*FPS_SMOOTHING + (1/(now - prev))*(1.0 - FPS_SMOOTHING));
		    prev = now;
			
		    //~ printf("fps: %.1f\n", fps);
	
		    if (cap.isOpened()){
		        cap.read(frame);
		        rame = frame;
		        if(m){
					frame_1 = frame;
					m = !m;
				}
		        //~ d.detect(frame, classIds, confidences, boxes);
		    }
		    //~ if (cap_1.isOpened()){
		        //~ cap_1.read(frame_1);
		        //~ d.detect(frame, classIds, confidences, boxes);
		    //~ }
		    //~ cv::cvtColor(frame, frame, COLOR_BGR2GRAY);
			//~ cv::GaussianBlur(frame, frame, Size(31, 31), 1.5);
			//~ cv::sqrBoxFilter(frame, frame, 2, cv::Size(5, 5));
			//~ cv::GaussianBlur(frame, frame, Size(5, 5), 1.5);
			//~ cv::absdiff(frame, frame_1, rame);
			//~ std::vector<std::vector<cv::Point>> contours;
			//~ std::vector<cv::Vec4i> hierarchy;
			//~ cv::threshold(rame, rame, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
			//~ cv::findContours(rame, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
			//~ cv::resize(rame, rame, cv::Size(720, 480));
			//~ cv::resize(frame, frame, cv::Size(288, 192));
		    //~ std::cout << frame << "\n\n\n\n\n\n\n" << std::endl;
			//~ cv::resize(frame, frame, cv::Size(720, 480));
			//~ cv::cvtColor(frame, frame, COLOR_GRAY2BGR);
			//~ cv::cvtColor(rame, rame, cv::COLOR_GRAY2BGR);
			//~ for(auto cont: contours)
			//~ {
			    //~ cv::Rect box = cv::boundingRect(cont);
			    //~ cv::rectangle(frame, box, cv::Scalar(rand()%255, rand()%255, rand()%255));
			//~ }
			if(!frame.empty()){
				//~ cv::cvtColor(frame, frame, COLOR_BGR2GRAY);
				//~ cv::Canny(frame, frame, 40, 150);
				cv::cvtColor(rame, rame, COLOR_BGR2GRAY);
				cv::GaussianBlur(rame, rame, cv::Size(25, 25), 6);
				signed_b x = 0, y = 0;
				//~ cv::Vec3b max = ;
				for(signed_b i = 0; i < rame.rows; i++){
					for(signed_b j = 0; j < rame.cols; j++){
						if(rame.at<uchar>(x, y) > rame.at<uchar>(i, j)){
							x = i;
							y = j;
							}								
						}
					}
				cv::Canny(rame, rame, 40, 50);
				//~ cv::cvtColor(frame, frame, COLOR_BGR5652BGR);
				cv::drawMarker(frame, cv::Point(320, 240), rame.at<cv::Vec3b>(240, 320)-cv::Vec3b(60, 60, 60), cv::MARKER_CROSS, 20, 6);
				cv::putText(frame, std::to_string(fps) +" fps", cv::Point(0, 40), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 0, 0), 3);
				cv::drawMarker(frame, cv::Point(y, x), cv::Scalar(0, 0, 255), cv::MARKER_CROSS, 20, 6);
				cv::line(frame, cv::Point(y, 0), cv::Point(y, variables::properties::camera::size_footage_horizontal), cv::Scalar(205, 60, 205), 2);
				
				//~ std::cout << "x: " << x << " y: " << y << " l: " << std::to_string(rame.at<uchar>(x, y)) << std::endl;
				cv::putText(frame, std::to_string(variables::properties::camera::angle_horizontal*((float)y/(float)variables::properties::camera::size_footage_vertical - 1/2.0f))+"*", cv::Point(y, x), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 0, 0), 1);
				cv::imshow("b", frame);
				cv::imshow("c", frame_1);

			    cv::imshow(wname, rame);
			    //~ cv::imshow("b", rame);
			    //~ frame_1 = frame;
			    cv::cvtColor(rame, rame, COLOR_GRAY2BGR);
		    }
		    rame.release();
		    frame.release();
		    //~ cv::imwrite("heck.png", frame);
		    //~ imshow("edit", edit);
		    if (cv::waitKey(2) == 27){
		        return;
		    }
		}
		#endif
		}



	void function25(int argc, char *argv[]){
		#ifndef dont_comp
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
		#endif
		}



	void function26(int argc, char *argv[]){
		#ifndef dont_comp
		std::cout << line(coordinates(c_f(argv[2]), c_f(argv[3])), coordinates(4, -4)).make_perpendicular(coordinates(4, -4)).print() << std::endl;
		std::cout << line(coordinates(c_f(argv[2]), c_f(argv[3])), coordinates(4, -4)).print() << std::endl;
		#endif
		}



	void function27(int argc, char *argv[]){
		#ifndef dont_comp
		coordinates x[] = {coordinates(1, 1), coordinates(0, 2), coordinates(4, 6), coordinates(5, 5)};
		coordinates y[] = {coordinates(-1, 1), coordinates(0, 2), coordinates(4, -2), coordinates(3, -3)};
		map m;
		m.append(wall(x));
		m.append(wall(y));
		
		std::cout << m.closest_wall(coordinates(2, 5)).closest_point(coordinates(2, 5)).print() << std::endl;	
		#endif
		}



	void function28(int argc, char *argv[]){
		#ifndef dont_comp
		std::cout << line(c_f(argv[2]), c_f(argv[3]), 0).print() << std::endl;				
		std::cout << line(c_f(argv[2]), c_f(argv[3]), 0).get_angle()/pi_const*180 << std::endl;				
		#endif
		}



	void function29(int argc, char *argv[]){
		#ifndef dont_comp
		std::cout << line(c_f(argv[2]), c_f(argv[3]), 0).print() << std::endl;				
		std::cout << line(line(c_f(argv[2]), c_f(argv[3]), 0).get_angle(), coordinates(1, 1)).print() << std::endl;				
		#endif
		}



	void function30(int argc, char *argv[]){
		#ifndef dont_comp
		std::cout << line(1, 0, -3).print() << std::endl;				
		std::cout << line(c_f(argv[2]), c_f(argv[3]), c_f(argv[4])).print() << std::endl;				
		std::cout << line().make_axis(line(1, 0, -3), line(c_f(argv[2]), c_f(argv[3]), c_f(argv[4]))).print() << std::endl;
		#endif
		}



	void function31(int argc, char *argv[]){
		#ifndef dont_comp
		std::cout << line(1, 2, -3).print() << std::endl;				
		std::cout << line().get_distance(line(1, 2, -3), coordinates(c_f(argv[2]), c_f(argv[3]))) << std::endl;
		#endif
		}



	void function32(int argc, char *argv[]){
		#ifndef dont_comp
		std::cout << line(1, 2, -3).print() << std::endl;				
		std::cout << line(1, 2, -3).get_distance(line(1, 2, c_f(argv[2]))) << std::endl;
		#endif
		}



	void function33(int argc, char *argv[]){
		#ifndef dont_comp
		
		#endif
		}



	void function34(int argc, char *argv[]){
		#ifndef dont_comp
		std::cout << circle(coordinates(2, 0), 2).print() << std::endl;				
		std::cout << circle(coordinates(2, 0), 2).on_segment(coordinates(0, 0), coordinates(2, 2), coordinates(4, 0), 1) << std::endl;				
		#endif
		}



	void function35(int argc, char *argv[]){
		#ifndef dont_comp
		step s(coordinates(1, 1), coordinates(c_f(argv[2]), c_f(argv[3])));
		std::pair<step, step> steps = step::get_perimeters(s, 2);
		std::cout << std::get<line>(s.formula).print() << std::endl;
		std::cout << std::get<line>(std::get<0>(steps).formula).print() << std::endl;
		std::cout << std::get<line>(std::get<1>(steps).formula).print() << std::endl;
		#endif
		}



	void function36(int argc, char *argv[]){
		#ifndef dont_comp
		step s(coordinates(0, 0), coordinates(3, 3), coordinates(c_f(argv[2]), c_f(argv[3])));
		std::pair<step, step> steps = step::get_perimeters(s, 2);
		std::cout << std::get<circle>(s.formula).print() << std::endl;
		std::cout << std::get<circle>(std::get<0>(steps).formula).print() << std::endl;
		std::cout << std::get<circle>(std::get<1>(steps).formula).print() << std::endl;
		std::cout << std::get<0>(steps).start.print() << "\t" << std::get<0>(steps).end.print() << std::endl;
		std::cout << std::get<1>(steps).start.print() << "\t" << std::get<1>(steps).end.print() << std::endl;
		#endif
		}



	void function37(int argc, char *argv[]){
		#ifndef dont_comp
		for(auto a: circle().circles(line(1, 8, 5), line(c_f(argv[2]), 3, 0), 2))
			std::cout << a.print() << std::endl;
		std::cout << line(1, 8, 5).print() << std::endl;
		std::cout << line(c_f(argv[2]), 3, 0).print() << std::endl;
		#endif
		}



	void function38(int argc, char *argv[]){
		#ifndef dont_comp
		map m;
	
		coordinates c[] = {coordinates(-10, 3), coordinates(-11, 4), coordinates(-7, 8), coordinates(-6, 7)};
		coordinates x[] = {coordinates(1, 1), coordinates(0, 2), coordinates(4, 6), coordinates(5, 5)};
		coordinates y[] = {coordinates(-1, 1), coordinates(0, 2), coordinates(4, -2), coordinates(3, -3)};
		coordinates z[] = {coordinates(4, 6), coordinates(5, 7), coordinates(9, 3), coordinates(8, 2)};
		coordinates a[] = {coordinates(3, -3), coordinates(6, 0), coordinates(7, -1), coordinates(4, -4)};
		
		//~ m.append(candle(coordinates(4,3)));
		m.append(wall(c));
		m.append(wall(x));
		m.append(wall(y));
		m.append(wall(z));
		m.append(wall(a));
		for(auto w: m._map_walls)
			std::cout << w.print_geogebra() << std::endl;
		planner p;
		//~ angles a = angles().load_virtual(coordinates(-5, 2), m);
		//~ for(auto i: a)
		//~ std::cout << a.get_angle(0).position._coordinates.print() << std::endl;
		//~ std::cout << a.get_angle(0).distance << std::endl;
		//~ std::cout << a.size() << std::endl;
		
		
		
		
		//~ std::vector <line> clan = p.plan_trace(plan, coordinates(c_f(argv[2]), c_f(argv[3])), coordinates(-5, 2), m);
		//~ std::cout << m._map_walls[0].is_collision_course(circle(coordinates(-5, 2), 6))[1].print() << std::endl;
		std::srand(std::time(nullptr)); 
		//~ for(auto i: plan)
			//~ std::cout << i.print() << std::endl;	
		//~ for(auto i: plan)
			//~ std::cout << i.print() << std::endl;
		
		//~ for(auto i: p.coincidental_points_generate(plan))
			//~ std::cout << i.print() << std::endl;
		
		
		std::vector <circle> plan = p.circle_generate(coordinates(c_f(argv[2]), c_f(argv[3])), coordinates(-5, 2), m, c_i(argv[4]));
		std::vector<coordinates> g = p.coincidental_points_generate(plan);
		//~ std::vector<coordinates> c_plan = p.make_path(g, coordinates(-5, 2), coordinates(c_f(argv[2]), c_f(argv[3])), m);
		std::vector<coordinates> c_plan({coordinates(-5, 2), coordinates(4, -5), coordinates(8, -1), coordinates(4, 3)});
		p.plan_make(c_plan, m, c_f(argv[5])*pi_const/c_f(argv[6]));
		
		#endif
		}



	void function39(int argc, char *argv[]){
		#ifndef dont_comp
		std::cout << circle(1, 2, 3).get_distance(coordinates(c_f(argv[2]), c_f(argv[3])), coordinates(c_f(argv[4]), c_f(argv[5]))) << std::endl;
		std::cout << circle(1, 2, 3).print() << std::endl;
		#endif
		}



	void function40(int argc, char *argv[]){
		#ifndef dont_comp
		circle start1(coordinates(3, 0), 3);
		circle start2(coordinates(-3, 0), 3);
		std::array<circle, 9> possible = {
			circle(coordinates(-3, 3*3), 2.5),
			circle(coordinates(1, 6), 2.5),
			circle(coordinates(6*2, 3*3), 2.5),
			//~ circle(coordinates(-6*2, 3*3), 2.5),
			circle(coordinates(6*2, 3), 2.5),
			//~ circle(coordinates(-6*2, 3), 2.5),
			circle(coordinates(6*2, -3), 2.5),
			//~ circle(coordinates(-6*2, -3), 2.5),
			circle(coordinates(6*2, 3*-3), 2.5),
			circle(coordinates(-6*2, 3*-3), 2.5),
			//~ circle(coordinates(3, 3*-3), 2.5),
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
			for(auto c: {start1/*, start2*/}){
				auto tangents = circle::circle_tangents(c, a);
				for(auto &b: tangents) {
					coordinates first = b.intersection(b.make_perpendicular(c.center));
					coordinates second = b.intersection(b.make_perpendicular(a.center));
					decimal_n vector_angle = first.get_gamma(second);
					decimal_n tangent_angle = c.center.get_gamma(first);
					decimal_n difference_angle = vector_angle - (tangent_angle + ((c.center.x < 0)?1:-1) * pi_const/2);
					if((std::abs(difference_angle) <= 1e-3 || (std::abs(difference_angle + ((c.center.x < 0)?2:-2)*pi_const) <= 1e-3))){
						std::cout << vector(first, second).print() << std::endl;
						}
					}
				}
			}
		#endif
		}
};
