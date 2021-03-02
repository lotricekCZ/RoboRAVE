cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)	

# set the project name and version
project(roborave VERSION 0.1)
#~ target_link_libraries(roborave libserial pthread)

file(GLOB SOURCE_FILES *.cpp)

#~ add_executable(roborave ${SOURCE_FILES}) # 	main.cpp)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(OpenCV REQUIRED opencv4)
pkg_search_module(YAML_CPP REQUIRED yaml-cpp)
#~ find_package(yaml-cpp)

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

if (YAML_CPP_FOUND)
    # Print some message showing some of them
    message(STATUS "yaml-cpp library status:")
    message(STATUS "    version: ${YAML_CPP_VERSION}")
    message(STATUS "    include path: ${YAML_CPP_INCLUDEDIR}" )
    message(STATUS "    cpp flags: ${YAML_CPP_LIBRARIES}")
else ()
    message(FATAL_ERROR "Could not locate yaml-cpp" \n)
endif()

set(Torch_DIR libtorch/share/cmake/Torch)
find_package(Torch PATHS ${Torch_DIR} NO_DEFAULT REQUIRED)
if (Torch_FOUND)
    message(STATUS "Torch library found!")
    message(STATUS "    include path: ${TORCH_INCLUDE_DIRS}" \n)

else ()
    message(FATAL_ERROR "Could not locate Torch" \n)
endif()

include_directories(roborave ${TORCH_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} ${YAML_CPP_INCLUDEDIR} ${YAML_CPP_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "-std=c++17 ${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
add_executable(roborave ${SOURCE_FILES})

link_directories(${OpenCV_LIB_DIR})
target_compile_features(roborave PRIVATE cxx_std_17)
target_link_libraries(roborave Threads::Threads ${OpenCV_LIBRARIES} ${OpenCV_LDFLAGS} ${YAML_CPP_LIBRARIES}	${TORCH_LIBRARIES})
