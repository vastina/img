set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)

add_executable(bmp1 ./bmp/bmp1.cpp)
target_link_libraries(bmp1 ${project2})

add_executable(png1 ./png/png1.cpp)
target_link_libraries(png1 ${project_name})

find_package(Freetype REQUIRED)
add_executable(png_char ./png/char.cpp)
target_link_libraries(png_char ${FREETYPE_LIBRARIES})
target_include_directories(png_char PRIVATE ${FREETYPE_INCLUDE_DIRS})
target_link_libraries(png_char ${project_name})

add_executable(png_vastina ./png/vastina.cpp)
target_link_libraries(png_vastina ${FREETYPE_LIBRARIES})
target_include_directories(png_vastina PRIVATE ${FREETYPE_INCLUDE_DIRS})
target_link_libraries(png_vastina ${project_name})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
add_executable(png_window ./png/window.cpp)
target_link_libraries(png_window PRIVATE
  ${FREETYPE_LIBRARIES}
  # https://segmentfault.com/q/1010000042726734
  ${SDL2_LIBRARIES} SDL2_image::SDL2_image
  ${project_name}
)
target_include_directories(png_window PRIVATE ${FREETYPE_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})