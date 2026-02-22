cmake_minimum_required(VERSION 3.28.3)
set(CMAKE_CXX_STANDARD 17)
project(SurvivorsGame)

# Find SDL2
find_package(SDL2 REQUIRED)

# Find SDL2_image
find_package(SDL2_image REQUIRED)

# Add executable
add_executable(Noise src/perlin.cpp)
add_executable(${PROJECT_NAME} src/main.cpp)

# Link using modern CMake targets (avoids variable name issues)
target_link_libraries(Noise PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image)