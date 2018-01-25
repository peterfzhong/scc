cmake_minimum_required(VERSION 2.8)
SET(CMAKE_BUILE_TYPE DEBUG) 
set(PROJECT_NAME scc)
project(${PROJECT_NAME})

message(STATUS "Project name:${PROJECT_NAME}\r\n")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O2 -pipe -fno-ident -MMD -D_GNU_SOURCE -D_REENTRANT")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c++11 -Wall -O2 -pipe -fno-ident -MMD -D_GNU_SOURCE -D_REENTRANT")

file(GLOB CPP_FILES "*.cpp")

foreach(SOURCE ${CPP_FILES})
    string(REPLACE ${PROJECT_SOURCE_DIR} "." CPP_FILE ${SOURCE})
    message(${CPP_FILE})
endforeach()


include_directories(
    ./include )

link_directories(
    /usr/local/lib 
	)

add_executable(${PROJECT_NAME} ${CPP_FILES})

target_link_libraries(${PROJECT_NAME} libevent.a)