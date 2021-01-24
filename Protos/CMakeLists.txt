# Creates protobuf c++ files at cmake cache generation time
# Should be executed when the cache is created. This ensures the .h and .cc files exist when the project is created
# cmake knows about these files
#
# Parameters:
# - SOURCE_DIR: Directory where the .proto files exist
# - DEST_DIR: Where the .h and .cc files that are generated will be placed
function(generate_model SOURCE_DIR DEST_DIR)
    find_program (PROTOBUF_COMPILER protoc)

    file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/*.proto")

    file(REMOVE_RECURSE ${DEST_DIR})
    file(MAKE_DIRECTORY ${DEST_DIR})

    set(PROTOS_LIST "")

    foreach (FILE ${SOURCE_FILES})
        list(APPEND PROTOS_LIST ${FILE})
    endforeach()

    MESSAGE("Generating model: ${PROTOBUF_COMPILER} --proto_path=${SOURCE_DIR} --cpp_out=${DEST_DIR} ${PROTOS_LIST}")

    execute_process(
        COMMAND ${PROTOBUF_COMPILER} --proto_path=${SOURCE_DIR} --cpp_out=${DEST_DIR} ${PROTOS_LIST}
        WORKING_DIRECTORY ${SOURCE_DIR}
    )
endfunction()

# Creates protobuf c++ files at cmake cache generation time
# Should be executed when the cache is created. This ensures the .h and .cc files exist when the project is created
# cmake knows about these files
#
# Parameters:
# - ARTIFACT: library or program that depend on the protos model. This program will be built after the protos are regenerated
# - SOURCE_DIR: Directory where the .proto files exist
# - DEST_DIR: Where the .h and .cc files that are generated will be placed
# Adds a custom build target to refresh the model if changes happen in the .proto files
function(refresh_model ARTIFACT SOURCE_DIR DEST_DIR)
    find_program (PROTOBUF_COMPILER protoc)

    file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/*.proto")
    set(PROTOS_LIST "")
    foreach (FILE ${SOURCE_FILES})
        list(APPEND PROTOS_LIST ${FILE})
    endforeach()

    # Create the custom target that 
    add_custom_target(
        RunProtoc-${ARTIFACT}
        COMMAND ${PROTOBUF_COMPILER} --proto_path=${SOURCE_DIR} --cpp_out=${DEST_DIR} ${PROTOS_LIST}
        COMMENT "Running: ${PROTOBUF_COMPILER} --proto_path=${SOURCE_DIR} --cpp_out=${DEST_DIR} ${PROTOS_LIST}"
    )

    add_dependencies(
        ${ARTIFACT}

        RunProtoc-${ARTIFACT}
    )
endfunction()

set(GENERATED_DIR "${PROJECT_BINARY_DIR}/generated")
set(GENERATED_MODEL_DIR "${GENERATED_DIR}/protos")

# generate the model and then add the files to the project
# files will typically be in out/build/<configuration>/generated/protos
generate_model("${CMAKE_CURRENT_SOURCE_DIR}" ${GENERATED_MODEL_DIR})

file(GLOB_RECURSE GENERATED_PUBLIC_INCLUDE "${GENERATED_MODEL_DIR}/**.h")
file(GLOB_RECURSE GENERATED_PRIVATE_SOURCES "${GENERATED_MODEL_DIR}/**.cc")
file(GLOB_RECURSE PROTO_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/**.proto")

add_library(
    StarPPServer-Protos
    STATIC
    ${GENERATED_PUBLIC_INCLUDE}
    ${GENERATED_PRIVATE_SOURCES}
    ${PROTO_SOURCES}
)

refresh_model(StarPPServer-Protos "${CMAKE_CURRENT_SOURCE_DIR}" ${GENERATED_MODEL_DIR})

target_include_directories(
    StarPPServer-Protos
    PUBLIC
    $<BUILD_INTERFACE:${GENERATED_DIR}/>
    $<INSTALL_INTERFACE:${GENERATED_DIR}/>
)
target_link_libraries(StarPPServer-Protos PUBLIC protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)