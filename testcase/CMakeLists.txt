set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)

add_executable(bmp1 ./bmp/bmp1.cpp)
target_link_libraries(bmp1 ${project2})
