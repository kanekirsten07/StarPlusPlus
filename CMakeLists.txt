cmake_minimum_required(VERSION 3.10)

# project name
project (StarPlusPlus)

#add the executable
add_subdirectory(StarPlusPlus)

# c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#install(TARGETS StarPPServer DESTINATION bin)

#proxygen
#find_package(proxygen CONFIG REQUIRED)
#target_link_libraries(StarPPServer PRIVATE proxygen)
