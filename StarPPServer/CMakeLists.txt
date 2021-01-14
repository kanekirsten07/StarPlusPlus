add_executable(StarPPServer Main.cpp)

#proxygen
find_package(proxygen CONFIG REQUIRED)
target_link_libraries(StarPPServer PRIVATE proxygen::proxygen proxygen::proxygenhttpserver)
