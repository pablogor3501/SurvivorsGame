file(GLOB game_sources "*.cpp")
add_library(game ${game_sources})
target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})