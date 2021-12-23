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

#include "./obsolete/obsolete.hpp"
#include "./elements/vector/vector.hpp"
#include "./defines/variables.hpp"
#include "./utils/data_containers/setters/setters.tpp"
#include "./utils/data_containers/speeds/speeds.hpp"
#include "./utils/data_containers/coordinates/coordinates.hpp"
#include "./utils/data_containers/map/include.hpp"
#include "./utils/log_maintainer/log_maintain.hpp"
#include "./utils/data_containers/angles/angles/angles.hpp"
#include "./utils/planners/avoidance_planner/avoider.hpp"
#include "./utils/planners/planner/planner.hpp"
#include "./defines/typedefines.h"

#define my_max(a, b) ((a>b)?a:b)

#include "./defines/constants.h"
#include "./defines/yaml_worker.hpp"



#include "./tank/tank.h"
#include "./elements/radius/radius.h"
#include "./utils/logic/logic.cpp"

#include "./hardware_interfaces/serial/serial.cpp"
#include "./hardware_interfaces/fire_sensors/fire_sensor.cpp"
#include "./tests/main_functions/main_functions1-20.hpp"
#include "./tests/main_functions/main_functions21-40.hpp"
#include "./tests/main_functions/main_functions41-60.hpp"




int main(int argc, char *argv[]) {
	load_config();
	auto start = std::chrono::steady_clock::now();
	switch(c_i(argv[1])){
		case 1:
			mf::function1();
			break;
			
		case 2:
			mf::function2(argc, argv);
			break;
			
		case 3:
			mf::function3(argc, argv);
			break;
		
		case 4:{
			mf::function4(argc, argv);
			break;
			}
			
		case 5:{
			mf::function5(argc, argv);
			break;
			}
		
		case 6:{
			mf::function6(argc, argv);
			break;
			}
			
		case 7:{
			mf::function7(argc, argv);
			break;
			}
			
		case 8:{
			mf::function8(argc, argv);
			break;
			}
			
		case 9:{
			mf::function9(argc, argv);
			break;
			}
		
		case 10:{
			mf::function10(argc, argv);
			break;
			}
		
		case 11:{
			mf::function11(argc, argv);
			break;			
			}
			
		case 12:
			mf::function12(argc, argv);
			break;
			
		case 13:
			mf::function13(argc, argv);
			break;
		
		case 14:{
			mf::function14(argc, argv);
			break;
			}
			
		case 15:{
			mf::function15(argc, argv);
			break;
			}
		
		case 16:{
			mf::function16(argc, argv);
			break;
			}
			
		case 17:{
			mf::function17(argc, argv);
			break;
			}
			
		case 18:{
			mf::function18(argc, argv);
			break;
			}
			
		case 19:{
			mf::function19(argc, argv);
			break;
			}
		
		case 20:{
			mf::function20(argc, argv);
			break;
			}
		
		case 21:{ 
			/// this creates map and does math to calculations to make heatmap, therefore selecting the hottest spot and designing trace to it
			mf::function21(argc, argv);
			break;
			}
			
		case 22:{
			mf::function22(argc, argv);
			break;
			}
			
		case 23:{
			mf::function23(argc, argv);
			break;
			}
			
		case 24:{
			mf::function24(argc, argv);
			break;
			}
			
		case 25:{
			mf::function25(argc, argv);
			break;
			}
			
		case 26:{
			mf::function26(argc, argv);
			break;
			}
			
		case 27:{
			mf::function27(argc, argv);
			break;
			}
			
		case 28:{
			mf::function28(argc, argv);
			}
			
		case 29:{
			mf::function29(argc, argv);
			break;
			}
			
		case 30:{
			mf::function30(argc, argv);
			break;
			}
			
		case 31:{
			mf::function31(argc, argv);
			break;
			}
			
		case 32:{
			mf::function32(argc, argv);
			break;
			}
			
		case 34:{
			mf::function34(argc, argv);
			break;
			}
			
		case 35:{
			mf::function35(argc, argv);
			break;
			}
			
		case 36:{
			mf::function36(argc, argv);
			break;
			}
			
		case 37:{
			mf::function37(argc, argv);
			break;
			}
			
		case 38:{ 
			/// this creates map and does math to calculations to make heatmap, therefore selecting the hottest spot and designing trace to it
			mf::function38(argc, argv);
			break;
			}
		
		case 39:{
			mf::function39(argc, argv);
			break;
			}
			
		case 40:{
			mf::function40(argc, argv);
			break;
			}

		case 41:{
			mf::function41(argc, argv);
			break;
			}
			
		case 42:{
			mf::function42(argc, argv);
			break;
			}
			
		case 43:{
			mf::function43(argc, argv);
			break;
			}
			
		case 44:{
			mf::function44(argc, argv);
			break;
			}

		case 45:{
			mf::function45(argc, argv);
			break;
			}
			
		case 46:{
			mf::function46(argc, argv);
			break;
			}
			
		case 47:{
			mf::function47(argc, argv);
			break;
			}

		case 48:{
			mf::function48(argc, argv);
			break;
			}
			
		case 49:{
			mf::function49(argc, argv);
			break;
			}
			
		case 50:{ // distance of two linear steps ./roborave 50  0   0 3 2 1  6 5 2 -5 1
			mf::function50(argc, argv);
			break;
			}
			
		case 51:{ // distance of two linear steps ./roborave 51  0   0 3 2 1  6 5 2 -5 1
			mf::function51(argc, argv);
			break;
			}
			
		case 52:{ // distance of two circular steps ./roborave 52  0   -2 1 2 1  0 1 4 1 2 1 1 1
			mf::function52(argc, argv);
			break;
			}
			
		case 53:{
			mf::function53(argc, argv);
			break;
			}
			
		case 54:{
			mf::function54(argc, argv);
			break;
			}
			
		case 55:{ // show map as opencv mat
			mf::function55(argc, argv);
			break;
			}
		
		case 56:{
			mf::function56(argc, argv);
			break;
			}
			
		case 57:{
			mf::function57(argc, argv);
			break;
			}
			
		case 58:{
			mf::function58(argc, argv);
			break;
			}
			
		case 59:{
			mf::function59(argc, argv);
			break;
			}
			
		case 60:{
			mf::function60(argc, argv);
			break;
			}
				
		case 61:{
			//~ std::cout << (vector(coordinates(4, 0), coordinates(12, 5)) + vector(coordinates(4, 0), coordinates(-4, 5))).print() << std::endl;
			std::cout << sizeof(vector(coordinates(4, 0), coordinates(12, 5))) << std::endl;
			std::cout << sizeof(coordinates(4, 0)) << std::endl;
			std::cout << (vector(coordinates(0, 0), coordinates(3, 3)) - sqrt(2)).print() << std::endl;
			break;
			}
			
		case 62:{
			std::cout << (vector(coordinates(0, 0), coordinates(3, 3)) - sqrt(2)).print() << std::endl;
			break;
			}
			
						
		case 63:{
			step s = step(coordinates(c_f(argv[3]), c_f(argv[4])), coordinates(c_f(argv[5]), c_f(argv[6])), coordinates(0, 1), c_i(argv[2]));
			step c = step(coordinates(c_f(argv[7]), c_f(argv[8])), coordinates(c_f(argv[9]), c_f(argv[10])));
			std::cout << s.print_geogebra() << std::endl;
			std::cout << c.print_geogebra() << std::endl;
			std::cout << step::get_vector(s, c).print() << std::endl;
			break;
			}
			
		case 64:{
			step s = step(coordinates(c_f(argv[2]), c_f(argv[3])), coordinates(c_f(argv[4]), c_f(argv[5])));
			step c = step(coordinates(c_f(argv[6]), c_f(argv[7])), coordinates(c_f(argv[8]), c_f(argv[9])));
			std::cout << s.print_geogebra() << std::endl;
			std::cout << c.print_geogebra() << std::endl;
			std::cout << step::get_vector(s, c).print() << std::endl;
			break;
			}
			
		case 65:{
			step s = step(coordinates(c_f(argv[3]), c_f(argv[4])), coordinates(c_f(argv[5]), c_f(argv[6])), coordinates(0, 1), c_i(argv[2]));
			step c = step(coordinates(c_f(argv[7]), c_f(argv[8])), coordinates(c_f(argv[9]), c_f(argv[10])), coordinates(c_f(argv[11]), c_f(argv[12])), c_i(argv[13]));
			std::cout << s.print_geogebra() << std::endl;
			std::cout << c.print_geogebra() << std::endl;
			std::cout << step::get_vector(s, c).print() << std::endl;
			break;
			}
			
		case 66:{
			std::cout << (vector(coordinates(0, 0), coordinates(3, 3)) >> coordinates(c_f(argv[2]), c_f(argv[3]))).print() << std::endl;
			std::cout << (coordinates(c_f(argv[2]), c_f(argv[3]))).print() << std::endl;
			std::cout << (vector(coordinates(0, 0), coordinates(3, 3))).print() << std::endl;
			break;
			}
			
		case 67:{
			std::cout << (vector(coordinates(0, 0), coordinates(3, 3))).print() << std::endl;
			std::cout << (vector(coordinates(0, 0), coordinates(3, 3)) << coordinates(c_f(argv[2]), c_f(argv[3]))).print() << std::endl;
			std::cout << (coordinates(c_f(argv[2]), c_f(argv[3]))).print() << std::endl;
			break;
			}
		
		case 68:{ 
			/// this creates map and does math to calculations to make heatmap, therefore selecting the hottest spot and designing trace to it
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
			planner p;

			//~ std::vector <circle> plan = p.circle_generate(coordinates(c_f(argv[2]), c_f(argv[3])), coordinates(-5, 2), m, c_i(argv[4]));
			//~ std::vector<coordinates> g = p.coincidental_points_generate(plan);
			//~ std::vector<coordinates> c_plan = p.make_path(g, coordinates(-5, 2), coordinates(c_f(argv[2]), c_f(argv[3])), m);
			std::vector<coordinates> c_plan({coordinates(-5, 2), coordinates(4, -5), coordinates(8, -1), coordinates(4, 3)});
			for(auto i: m._map_walls)
				std::cout << i.print_geogebra() << std::endl;
				
			for(uint8_t i = 1; i < c_plan.size(); i++){
				std::cout << step(c_plan.at(i-1), c_plan.at(i)).print_geogebra() << std::endl;
				for(auto o: step::get_vectors(step(c_plan.at(i-1), c_plan.at(i)), planner::get_closest_wall(step(c_plan.at(i-1), c_plan.at(i)), m))){
					std::cout << o.print() << std::endl;
					}
				}
			//~ p.plan_make(c_plan, m, c_f(argv[5])*pi_const/c_f(argv[6]));
			
		break;
		}
		
		case 69:{
			coordinates c[] = {coordinates(-10, 3), coordinates(-11, 4), coordinates(-7, 8), coordinates(-6, 7)};
			step s = step(coordinates(c_f(argv[2]), c_f(argv[3])), coordinates(c_f(argv[4]), c_f(argv[5])));
			wall w(c);
			std::cout << w.print_geogebra() << std::endl;
			std::cout << s.print_geogebra() << std::endl;
			std::cout << step::get_distance(s, w) << std::endl;
			break;
			}
		
		case 70:{ // ./roborave 70 -4 11 -10 2
			coordinates c[] = {coordinates(-10, 3), coordinates(-11, 4), coordinates(-7, 8), coordinates(-6, 7)};
			wall w(c);
			map m;
			planner p;
			step s(coordinates(c_f(argv[4]), c_f(argv[5])), coordinates(c_f(argv[2]), c_f(argv[3])));
			step circular_first(s.start.make_global(coordinates(0, 0), s.start.get_gamma(s.end) - pi_const/2), 
								s.start.make_global(coordinates(-3, -3), s.start.get_gamma(s.end) - pi_const/2),
								s.start.make_global(coordinates(0, -3), s.start.get_gamma(s.end) - pi_const/2), 0);
								
			step circular_second(s.end.make_global(coordinates(0, 0), s.start.get_gamma(s.end) - pi_const/2), 
								s.end.make_global(coordinates(3, 3), s.start.get_gamma(s.end) - pi_const/2),
								s.end.make_global(coordinates(0, 3), s.start.get_gamma(s.end) - pi_const/2), 0);
			step linear_continue(circular_second.end, circular_second.end);

			std::cout << circular_first.print_geogebra() << std::endl;
			std::cout << circular_second.print_geogebra() << std::endl;
			
			std::vector<step> previous({linear_continue, circular_second, s, circular_first});
			std::cout << w.print_geogebra() << std::endl;
			std::cout << s.print_geogebra() << std::endl;
			std::cout << step::get_distance(s, w) << std::endl;
			m.append(w);
			planner::avoid(previous, m);
			break;
			}
		
		case 71:{ // perpendicular bisector of step ./roborave 71  0  0 1 4 1 2 1
			step s(coordinates(c_f(argv[3]), c_f(argv[4])), 
					coordinates(c_f(argv[5]), c_f(argv[6])), 
					coordinates(c_f(argv[7]), c_f(argv[8])), c_i(argv[2]));
					
			std::cout << s.print_geogebra() << std::endl;
			std::cout << s.perpendicular_bisector().print() << std::endl;
			break;
			}
		
		case 72:{ // listing suppressed possible options ./roborave 72  4 3  -3 2 2  -5 2  7
			coordinates end(c_f(argv[2]), c_f(argv[3]));
			coordinates start(c_f(argv[7]), c_f(argv[8]));
			std::vector<circle> circles({circle(c_f(argv[4]), c_f(argv[5]), c_f(argv[6])), circle(2, -4, 1), circle(c_f(argv[9]), 1, 1.5)}); 
			for(path p: planner::suppress_by_sensibility(planner::list_options(circles, end, start)))
				std::cout << p.print() << std::endl;
			break;
			}
		
		case 73:{ // listing possible options ./roborave 73  4 3  -3 2 2  -5 2  7
			coordinates end(c_f(argv[2]), c_f(argv[3]));
			coordinates start(c_f(argv[7]), c_f(argv[8]));
			std::vector<circle> circles({circle(c_f(argv[4]), c_f(argv[5]), c_f(argv[6])), circle(2, -4, 1), circle(c_f(argv[9]), 1, 1.5)}); 
			for(path p: planner::list_options(circles, end, start))
				std::cout << p.print() << std::endl;
			break;
			}
		
		case 74:{ // listing possible options ./roborave 74  4 3  -3 2
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
			planner p;
			
			coordinates end(c_f(argv[2]), c_f(argv[3]));
			coordinates start(c_f(argv[4]), c_f(argv[5]));
			step s(start, end);
			std::cout << s.print_geogebra() << std::endl;
			for(auto w: m._map_walls)
				std::cout << w.print_geogebra() << '\n' << wall::estimate_center(w).print() << std::endl;
			for(auto w: planner::intersecting_walls(s, m))
				for(auto c: w.first)
					std::cout << c.print() << '\n' << w.second.print_geogebra() << std::endl;
			planner::avoid(s, m);
			break;
			}
		
		case 75:{ // shows intersection with linears ./roborave 75  4 3  -3 2
			map m;
	
			coordinates x[] = {coordinates(1, 1), coordinates(0, 2), coordinates(4, 6), coordinates(5, 5)};
			
			//~ m.append(candle(coordinates(4,3)));

			m.append(wall(x));
			planner p;
			
			coordinates end(c_f(argv[2]), c_f(argv[3]));
			coordinates start(c_f(argv[4]), c_f(argv[5]));
			step s(start, end);
			std::cout << s.print_geogebra() << std::endl;
			for(auto w: m._map_walls)
				std::cout << w.print_geogebra() << std::endl;
			for(auto c: step::intersection(s, m._map_walls.at(0)))
				std::cout << c.print() << std::endl;
			//~ step::intersection(s, m);
			break;
			}
		
		case 76:{ // shows intersection with circulars ./roborave 76  4 3  -3 1 1.066037736 0.0188679245 1
			map m;
	
			coordinates x[] = {coordinates(1, 1), coordinates(0, 2), coordinates(4, 6), coordinates(5, 5)};
			
			//~ m.append(candle(coordinates(4,3)));

			m.append(wall(x));
			planner p;
			
			coordinates end(c_f(argv[2]), c_f(argv[3]));
			coordinates start(c_f(argv[4]), c_f(argv[5]));
			coordinates center(c_f(argv[6]), c_f(argv[7]));
			step s(start, end, center, c_i(argv[8]) % 2);
			std::cout << s.print_geogebra() << std::endl;
			for(auto w: m._map_walls)
				std::cout << w.print_geogebra() << std::endl;
			for(auto c: step::intersection(s, m._map_walls.at(0)))
				std::cout << c.print() << std::endl;
			//~ step::intersection(s, m);
			break;
			}
			
		case 77:{ // shows intersection with circulars ./roborave 77  4 3  -3 1 1.066037736 0.0188679245 1
			map m;
	
			coordinates x[] = {coordinates(1, 1), coordinates(0, 2), coordinates(4, 6), coordinates(5, 5)};
			
			//~ m.append(candle(coordinates(4,3)));

			m.append(wall(x));
			planner p;
			
			coordinates end(c_f(argv[2]), c_f(argv[3]));
			coordinates start(c_f(argv[4]), c_f(argv[5]));
			step s(start, end);
			std::cout << s.print_geogebra() << std::endl;
			for(auto w: m._map_walls)
				std::cout << w.print_geogebra() << std::endl;
			for(auto c: step::intersection(s, m._map_walls.at(0)))
				std::cout << c.print() << std::endl;
			//~ step::intersection(s, m);
			break;
			}
			
		case 78:{ // shows intersection with circulars ./roborave 77  4 3  -3 1 1.066037736 0.0188679245 1
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
			planner p;
			
			
			
			coordinates end(c_f(argv[2]), c_f(argv[3]));
			coordinates start(c_f(argv[4]), c_f(argv[5]));
			path pth(step(start, end));
			
			std::cout << pth.at(0).print_geogebra() << std::endl;
			for(auto w: m._map_walls)
				std::cout << w.print_geogebra() << std::endl;
				
			planner::avoid(pth, m);
			//~ step::intersection(s, m);
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
