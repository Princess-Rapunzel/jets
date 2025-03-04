cmake_minimum_required(VERSION 3.10)
project(test3)

aux_source_directory(. DIR_SRCS)
add_executable(test3 mpi-test.C
    ${COMMON_SRC}       ${UTILS_SRC}    ${MESH_SRC} 
    ${GEO_SRC}          ${NUM_SRC}      ${DIR_SRCS}
    ${INTEGRAL_SRC}     ${SYSTEM_SRC}   ${PARALLEL_SRC}
)

target_link_libraries(test3 ${MPI_LIBRARIES})