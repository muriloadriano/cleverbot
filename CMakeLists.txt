cmake_minimum_required(VERSION 2.8)

project(bot)

#g++-mp-4.7 -std=c++11 -Wall main.cpp connection.cpp bot.cpp logger.cpp -o bot -lboost_system -ggdb
#g++ -std=c++11 -Wall *.cpp -lboost_system -lboost_thread -lpthread -o bot

file(GLOB SOURCES src/*.cpp)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE(Boost REQUIRED COMPONENTS system thread)
IF(Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
  LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

find_package(Threads)

#urdl dependency
#git clone https://github.com/chriskohlhoff/urdl
#include_directories(./urdl/include/)

set(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")
ADD_EXECUTABLE(release ${SOURCES})
TARGET_LINK_LIBRARIES(release ${USED_LIBS})

