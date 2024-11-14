# cmake_minimum_required(VERSION 3.10)
# project(jets)
# # cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..
# add_subdirectory(test/test1)

cmake_minimum_required(VERSION 3.10)
project(jets)
# # Path of static libraries.
# set(LIBPATH ${PROJECT_SOURCE_DIR}/lib)

# Path of executable files.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(
    # ${CMAKE_SOURCE_DIR}/include/common
    ${CMAKE_SOURCE_DIR}/include/utils
    ${CMAKE_SOURCE_DIR}/include/geo
)
message(STATUS "CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR})

# aux_source_directory(${CMAKE_SOURCE_DIR}/src/common COMMON_SRC)
# aux_source_directory(${CMAKE_SOURCE_DIR}/src/utils UTILS_SRC)
# aux_source_directory(${CMAKE_SOURCE_DIR}/src/mesh MESH_SRC)
# aux_source_directory(${CMAKE_SOURCE_DIR}/src/geo GEO_SRC)


# Path of header files.
# set(HEADERPATH ${PROJECT_SOURCE_DIR}/include)

# Name of the executable file.
set(TEST1 test1)
set(TEST2 test2)

# Add subdirectories.
# add_subdirectory(test/test1)
add_subdirectory(test/test2)