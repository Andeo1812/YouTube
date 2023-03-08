cmake_minimum_required(VERSION 3.16)
project(static_web_server)

set(CMAKE_CXX_STANDARD 20)

include_directories(project/include)

add_executable(
        static_web_server
        project/main.cpp
        project/include/server.hpp
        project/include/constants.hpp
        project/src/server.cpp
        project/src/http_handler.cpp
        project/include/http_handler.hpp
        project/src/utils.cpp
        project/include/utils.hpp
        project/include/responses.hpp)

target_link_libraries(static_web_server -lpthread)
