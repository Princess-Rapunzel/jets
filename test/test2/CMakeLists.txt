cmake_minimum_required(VERSION 3.10)
project(test2)

aux_source_directory(. DIR_SRCS)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/geo GEO_SRC)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/utils UTILS_SRC)
add_executable(test2 
    ${GEO_SRC} ${DIR_SRCS}
)