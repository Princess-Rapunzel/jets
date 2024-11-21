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
set(EIGEN3_INCLUDE_DIR "D:/APP/Eigen/share/eigen3/cmake")
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIRS})
if(TARGET Eigen3::Eigen)
    message(STATUS "Eigen3 found")
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/include/common
    ${CMAKE_SOURCE_DIR}/include/utils
    ${CMAKE_SOURCE_DIR}/include/geo
    ${CMAKE_SOURCE_DIR}/include/mesh
    ${CMAKE_SOURCE_DIR}/include/numerical
    ${CMAKE_SOURCE_DIR}/include/integral
    ${CMAKE_SOURCE_DIR}/include/system
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


# Path of header files.
# set(HEADERPATH ${PROJECT_SOURCE_DIR}/include)

# Name of the executable file.
set(TEST1 test1)
set(TEST2 test2)
# Add subdirectories.
add_subdirectory(test/test1)
# add_subdirectory(test/test2)