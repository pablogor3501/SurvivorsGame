cmake_minimum_required(VERSION 3.28.3)
set(CMAKE_CXX_STANDARD 17)

project(SurvivorsGame)

# ─────────────────────────────
# Find SDL2
# ─────────────────────────────
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# ─────────────────────────────
# Main game executable
# ─────────────────────────────
add_executable(${PROJECT_NAME}
    src/Game.cpp
    src/Player.cpp
    src/Enemy.cpp
    src/Entity.cpp
    src/Camera.cpp
    src/World.cpp
    src/Tile.cpp
    src/PerlinNoise.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image
    )