# include_directories(
#     ${CMAKE_SOURCE_DIR}/include/common
#     ${CMAKE_SOURCE_DIR}/include/utils
# )

# aux_source_directory(${CMAKE_SOURCE_DIR}/src/common COMMON_SRC)
# aux_source_directory(${CMAKE_SOURCE_DIR}/src/utils UTILS_SRC)
# aux_source_directory(. DIR_SRCS)
# add_executable(test1 
#     ${COMMON_SRC} ${UTILS_SRC} ${DIR_SRCS}
# )

# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
aux_source_directory(. DIR_SRCS)
add_executable(test1 
    ${COMMON_SRC} ${UTILS_SRC} ${DIR_SRCS}
)