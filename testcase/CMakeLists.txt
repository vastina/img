set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)

add_executable(bmp1 ./bmp/bmp1.cpp)
target_link_libraries(bmp1 ${project2})

add_executable(png1 ./png/png1.cpp)
target_link_libraries(png1 ${project_name})

find_package(Freetype REQUIRED)
add_executable(png_char ./png/char.cpp) # CMAKE_CURRENT_SOURCE_DIR is implicit here
target_link_libraries(png_char ${FREETYPE_LIBRARIES})
target_include_directories(png_char PRIVATE ${FREETYPE_INCLUDE_DIRS})
target_link_libraries(png_char ${project_name})