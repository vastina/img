cmake_minimum_required(VERSION 3.9)

set(project_name png)
project(${project_name})
set(project2 bmp)
project(${project2})

add_compile_options("-Wall" "-Wextra")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

set(project_dir "./code")
include_directories("${project_dir}/include")

find_package(ZLIB)
file(GLOB SOURCES "${project_dir}/${project_name}/*.cpp")
add_library(${project_name} STATIC ${SOURCES})
target_link_libraries(${project_name} ZLIB::ZLIB)

file(GLOB SOURCES_BMP "${project_dir}/${project2}/*.cpp")
add_library(${project2} STATIC ${SOURCES_BMP})

add_subdirectory(${CMAKE_SOURCE_DIR}/testcase)

find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG)

pybind11_add_module(
  vas_${project2}
  "${project_dir}/bind/${project2}.cpp"
  ${SOURCES_BMP}
)