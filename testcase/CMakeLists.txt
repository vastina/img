set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)

add_executable(bmp1 ./bmp/bmp1.cpp)
target_link_libraries(bmp1 ${project2})

add_executable(png1 ./png/png1.cpp)
target_link_libraries(png1 ${project_name})