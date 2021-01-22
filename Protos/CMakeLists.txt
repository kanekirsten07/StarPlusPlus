find_program (PROTOBUF_COMPILER protoc)
find_package(protobuf CONFIG REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/**.proto")

target_link_libraries(StarPPServer PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)