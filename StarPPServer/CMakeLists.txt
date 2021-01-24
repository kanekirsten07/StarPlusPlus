find_package(proxygen CONFIG REQUIRED)

file(GLOB_RECURSE PUBLIC_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include/**.h")
file(GLOB_RECURSE PRIVATE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp")

add_executable(StarPPServer

    ${PRIVATE_SOURCES}
    ${PUBLIC_INCLUDE}
)

target_include_directories(StarPPServer PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:include/>
    )

target_link_libraries(StarPPServer PRIVATE proxygen::proxygen proxygen::proxygenhttpserver)
target_link_libraries(StarPPServer PRIVATE StarPPServer-Protos)
