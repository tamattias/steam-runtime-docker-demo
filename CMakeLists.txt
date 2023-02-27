cmake_minimum_required(VERSION 3.13.2)

project(steamrt-demo)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Put built binaries in bin folder.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(steamrt-demo main.cc)

target_link_libraries(steamrt-demo
  SDL2::SDL2
  SDL2::SDL2main
  OpenGL::GL
)
