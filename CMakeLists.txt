cmake_minimum_required(VERSION 3.0)
project(SDLEngine)

# Find SDL and SDL2_image packages
find_package(SDL2 REQUIRED HINTS "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL/lib/cmake")
find_package(SDL2_image REQUIRED HINTS "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL2Image/lib/cmake")

# Add all files in src/
file(GLOB SOURCES CONFIGURE_DEPENDS 
    "src/*.cpp" 
    "src/Components/*.cpp"
    "src/Events/*.cpp"
    "src/Entities/*.cpp"
    "src/Game/*.cpp"
     )
message("SOURCES: ${SOURCES}")

add_executable(SDLEngine ${SOURCES})

# Include directories for my own project
target_include_directories(SDLEngine PUBLIC "src/")

# Add SDL and SDL2 Image include directories
target_include_directories(SDLEngine PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(SDLEngine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL2Image/include")


# Add the SDL and SDL2 image library
target_link_libraries(SDLEngine ${SDL2_LIBRARIES} SDL2_image::SDL2_image)