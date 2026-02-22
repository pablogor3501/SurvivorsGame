cmake_minimum_required(VERSION 3.28.3)

set(CMAKE_CXX_STANDARD 17)

project(SurvivorsGame)

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Find SDL2_image
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

# Add executable
add_executable(Noise src/perlin.cpp)

# Add executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Link libraries
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(Noise           ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})