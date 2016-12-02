CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Numerophile)

FIND_PACKAGE(FLTK REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)

SET(CC gcc-6)
SET(CXX g++-6)

#set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

INCLUDE_DIRECTORIES(include)

FILE(GLOB SOURCES "src/*.cpp")


ADD_EXECUTABLE(main ${SOURCES})
TARGET_LINK_LIBRARIES(main ${FLTK_LIBRARIES})

#add_library(Deck_generator Deck_generator.cpp)
#add_library(Leaderboard Leaderboard.cpp)
#add_library(Parser Parser.cpp)
#add_library(Player Player.cpp)
#add_library(Sorted_button.cpp)
#add_library(Tile_selector Tile_selector.cpp)
#add_library(Token_stream Token_stream.cpp)