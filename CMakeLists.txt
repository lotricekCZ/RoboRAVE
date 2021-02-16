cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(roborave VERSION 0.1)
#~ target_link_libraries(roborave libserial pthread)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(roborave main.cpp)

target_link_libraries(roborave PUBLIC CppLinuxSerial)
target_link_libraries(roborave PRIVATE Threads::Threads)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
