cmake_minimum_required(VERSION 3.10)

project(prisonersriddlecpp)

add_executable(prisonersriddlecpp main.cpp)

install(TARGETS prisonersriddlecpp RUNTIME DESTINATION bin)
