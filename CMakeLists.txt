cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)	

# set the project name and version
project(roborave VERSION 0.1.2)
#~ target_link_libraries(roborave libserial pthread)

option(HasOpenCV "HasOpenCV" ON)
option(HasTorch "HasTorch" ON)

file(GLOB SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(YAML_CPP REQUIRED yaml-cpp)

if(HasOpenCV)
	pkg_search_module(OpenCV REQUIRED opencv4)
	if (OpenCV_FOUND)
	    # If the package has been found, several variables will
	    # be set, you can find the full list with descriptions
	    # in the OpenCVConfig.cmake file.
	    # Print some message showing some of them
	    message(STATUS "OpenCV library status:")
	    message(STATUS "    version: ${OpenCV_VERSION}")
	    message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}" \n)
	
	else ()
	    message(FATAL_ERROR "Could not locate OpenCV" \n)
	endif()
endif()

if (YAML_CPP_FOUND)
    # Print some message showing some of them
    message(STATUS "yaml-cpp library status:")
    message(STATUS "    version: ${YAML_CPP_VERSION}")
    message(STATUS "    include path: ${YAML_CPP_INCLUDEDIR}" )
    message(STATUS "    cpp flags: ${YAML_CPP_LIBRARIES}")
else ()
    message(FATAL_ERROR "Could not locate yaml-cpp" \n)
endif()

if(HasTorch)
	set(Torch_DIR libtorch/share/cmake/Torch)
	find_package(Torch PATHS ${Torch_DIR} NO_DEFAULT REQUIRED)
	if (Torch_FOUND)
	    message(STATUS "Torch library found!")
	    message(STATUS "    include path: ${TORCH_INCLUDE_DIRS}" \n)
	
	else ()
	    message(FATAL_ERROR "Could not locate Torch" \n)
	endif()
endif()

include_directories(roborave ${TORCH_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} ${YAML_CPP_INCLUDEDIR} ${YAML_CPP_INCLUDE_DIRS})
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/build)

add_library(yaml_worker SHARED ${CMAKE_CURRENT_SOURCE_DIR}/defines/yaml_worker.cpp)

target_include_directories(yaml_worker
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/defines
        ${YAML_CPP_INCLUDEDIR} 
        ${YAML_CPP_INCLUDE_DIRS}
)
add_executable(roborave ${SOURCE_FILES})

include(${CMAKE_CURRENT_SOURCE_DIR}/tests/main_functions/main_functions.txt)

add_library(log_maintain SHARED ${CMAKE_CURRENT_SOURCE_DIR}/utils/log_maintainer/log_maintain.cpp
							${CMAKE_CURRENT_SOURCE_DIR}/utils/log_maintainer/log_maintain.hpp)
							
add_library(obsolete 		SHARED ${CMAKE_CURRENT_SOURCE_DIR}/obsolete/obsolete.cpp)
add_library(variables 		SHARED ${CMAKE_CURRENT_SOURCE_DIR}/defines/variables.cpp)
add_library(coordinates 	SHARED ${CMAKE_CURRENT_SOURCE_DIR}/utils/data_containers/coordinates/coordinates.cpp)
add_library(line 			SHARED ${CMAKE_CURRENT_SOURCE_DIR}/elements/line/line.cpp)
add_library(circle 			SHARED ${CMAKE_CURRENT_SOURCE_DIR}/elements/circle/circle.cpp)
add_library(vector 			SHARED ${CMAKE_CURRENT_SOURCE_DIR}/elements/vector/vector.cpp)
add_library(logic	 		SHARED ${CMAKE_CURRENT_SOURCE_DIR}/utils/logic/logic.cpp)
add_library(location 		SHARED ${CMAKE_CURRENT_SOURCE_DIR}/utils/data_containers/map/location.cpp)
add_library(node 			SHARED ${CMAKE_CURRENT_SOURCE_DIR}/utils/data_containers/angles/node/node.cpp)
add_library(speeds 			SHARED ${CMAKE_CURRENT_SOURCE_DIR}/utils/data_containers/speeds/speeds.cpp)
add_library(obstacle 		SHARED ${CMAKE_CURRENT_SOURCE_DIR}/utils/data_containers/map/obstacles/obstacle.cpp)
add_library(wall 			SHARED ${CMAKE_CURRENT_SOURCE_DIR}/utils/data_containers/map/obstacles/wall.cpp)
add_library(surround_circle SHARED ${CMAKE_CURRENT_SOURCE_DIR}/utils/data_containers/map/obstacles/surround_circle.cpp)
add_library(candle 			SHARED ${CMAKE_CURRENT_SOURCE_DIR}/utils/data_containers/map/obstacles/candle.cpp)
add_library(map 			SHARED ${CMAKE_CURRENT_SOURCE_DIR}/utils/data_containers/map/map.cpp)
add_library(dijkstra 		SHARED ${CMAKE_CURRENT_SOURCE_DIR}/utils/planners/planner/dijkstra.cpp)
add_library(step 			SHARED ${CMAKE_CURRENT_SOURCE_DIR}/utils/planners/planner/step.cpp)
add_library(angles 			SHARED ${CMAKE_CURRENT_SOURCE_DIR}/utils/data_containers/angles/angles/angles.cpp)
add_library(avoider 		SHARED ${CMAKE_CURRENT_SOURCE_DIR}/utils/planners/avoidance_planner/avoider.cpp)
add_library(plan_utils 		SHARED ${CMAKE_CURRENT_SOURCE_DIR}/utils/planners/planner/planner_utils.cpp)
add_library(planner 		SHARED ${CMAKE_CURRENT_SOURCE_DIR}/utils/planners/planner/planner.cpp)
add_library(path	 		SHARED ${CMAKE_CURRENT_SOURCE_DIR}/utils/planners/planner/path.cpp)
add_library(path_wrapper	SHARED ${CMAKE_CURRENT_SOURCE_DIR}/utils/logic/path_wrapper.cpp)


include(${CMAKE_CURRENT_SOURCE_DIR}/hardware_interfaces/hardware_interfaces.txt)
target_link_libraries(obsolete variables coordinates)
target_link_libraries(line coordinates)
target_link_libraries(location coordinates)
target_link_libraries(node location coordinates)
target_link_libraries(obstacle location coordinates)
target_link_libraries(vector coordinates)

target_link_libraries(wall location coordinates line circle obstacle)
target_link_libraries(surround_circle location coordinates line circle obstacle)
target_link_libraries(candle location coordinates line circle obstacle)
target_link_libraries(dijkstra map coordinates wall)

target_link_libraries(circle line coordinates)
target_link_libraries(step circle line coordinates vector)
target_link_libraries(path step circle line coordinates vector)
target_link_libraries(map location coordinates line circle wall surround_circle candle ${OpenCV_LIBRARIES} ${OpenCV_LDFLAGS})
target_link_libraries(angles map location coordinates wall surround_circle candle)
target_link_libraries(avoider location coordinates line circle wall surround_circle candle angles path)
target_link_libraries(plan_utils location coordinates line circle wall surround_circle candle angles path avoider)
target_link_libraries(planner location coordinates line circle wall surround_circle candle angles path avoider plan_utils)
target_link_libraries(path_wrapper planner location coordinates line circle wall surround_circle candle angles path avoider plan_utils)
target_link_libraries(logic location coordinates line circle wall surround_circle candle angles path avoider plan_utils)

#~ target_link_libraries(serial -lCppLinuxSerial)
target_link_libraries(yaml_worker variables ${YAML_CPP_LIBRARIES})


set(CMAKE_CXX_FLAGS "-std=c++17 -g ${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

link_directories(${OpenCV_LIB_DIR})
target_compile_features(roborave PRIVATE cxx_std_17)
if(HasOpenCV)
	target_link_libraries(roborave ${OpenCV_LIBRARIES} ${OpenCV_LDFLAGS}) 
endif()
target_link_libraries(roborave Threads::Threads 
					${YAML_CPP_LIBRARIES} ${TORCH_LIBRARIES}
					log_maintain yaml_worker
					line 	circle		location 
					node 	speeds		step
					wall	obstacle	surround_circle
					candle	map			dijkstra
					angles	planner		vector
					avoider obsolete	path
					plan_utils variables coordinates 
					logic path_wrapper 
					)
