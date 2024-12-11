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

# set(EIGEN3_INCLUDE_DIR "C:/Program Files (x86)/eigen-3.4.0")
# list(APPEND CMAKE_MODULE_PATH ${EIGEN3_INCLUDE_DIR}/cmake)
# find_package(Eigen3 3.4 REQUIRED)
# if(TARGET Eigen3::Eigen)
#     message(STATUS "Eigen3 found")
# endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/include/common
    ${CMAKE_SOURCE_DIR}/include/utils
    ${CMAKE_SOURCE_DIR}/include/geo
    ${CMAKE_SOURCE_DIR}/include/mesh
    ${CMAKE_SOURCE_DIR}/include/numerical
    ${CMAKE_SOURCE_DIR}/include/integral
    ${CMAKE_SOURCE_DIR}/include/system
    ${CMAKE_SOURCE_DIR}/include/parallel
    # ${EIGEN3_INCLUDE_DIR}
)
# message(STATUS "CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR})

aux_source_directory(${CMAKE_SOURCE_DIR}/src/common COMMON_SRC)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/utils UTILS_SRC)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/mesh MESH_SRC)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/geo GEO_SRC)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/numerical NUM_SRC)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/integral INTEGRAL_SRC)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/system SYSTEM_SRC)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/parallel PARALLEL_SRC)

find_package(MPI REQUIRED)  
if(TARGET MPI)
    message(STATUS "MPI found")
elseif()
    message(STATUS "MPI not found")
endif()

include_directories(${MPI_INCLUDE_PATH})
# Path of header files.
# set(HEADERPATH ${PROJECT_SOURCE_DIR}/include)

# Ignore all warnings.
if(MSVC)
    # For Visual Studio compiler
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W0")
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # For GCC 和 Clang compiler
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
endif()

# Name of the executable file.
set(TEST1 test1)
set(TEST2 test2)
# Add subdirectories.

add_subdirectory(test/test3)
# add_subdirectory(test/test2)