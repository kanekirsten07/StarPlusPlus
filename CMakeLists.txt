cmake_minimum_required(VERSION 3.15)

# project name
project (StarPlusPlus)

find_package(proxygen CONFIG REQUIRED)
find_package(protobuf CONFIG REQUIRED)

#add the executable
add_subdirectory(Protos)
add_subdirectory(StarPPServer)

# c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

