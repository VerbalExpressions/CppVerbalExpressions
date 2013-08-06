CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7)
PROJECT(CppVerbalExpressions)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11 -Wall -Wextra -Weffc++ -pedantic")
IF(IS_DIRECTORY /opt/boxen)
	SET(BOOST_ROOT /opt/boxen/homebrew)
ENDIF()
FIND_PACKAGE(Boost 1.46.0 REQUIRED COMPONENTS regex)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIRS})
ADD_EXECUTABLE(CppVerbalExpressionsExample example.cpp)
TARGET_LINK_LIBRARIES(CppVerbalExpressionsExample ${Boost_LIBRARIES})
