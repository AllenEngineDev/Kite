cmake_minimum_required(VERSION 3.0)
project(SDLEngine)

set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui" )


# Find SDL and SDL2_image packages
find_package(SDL2 REQUIRED HINTS "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL/lib/cmake")
find_package(SDL2_image REQUIRED HINTS "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL2Image/lib/cmake")

# Find OpenGL
find_package(OpenGL REQUIRED)

# Add all files in src/
file(GLOB SOURCES CONFIGURE_DEPENDS 
    "src/*.cpp" 
    "src/Components/*.cpp"
    "src/Events/*.cpp"
    "src/Entities/*.cpp"
    "src/Game/*.cpp"
    "src/Layers/*.cpp"
     )



add_executable(SDLEngine ${SOURCES})

# Include directories for my own project"
target_include_directories(SDLEngine PUBLIC "src/")

#Make ImGUI available to us
target_include_directories(SDLEngine PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends")



# Add SDL and SDL2 Image include directories
target_include_directories(SDLEngine PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(SDLEngine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL2Image/include")


# Compiling IMGUI into a library
add_library(imgui
     # Main Imgui files
     "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_demo.cpp"

     # SDL2+SDL2Renderer-specific files
     "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_sdl2.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_sdlrenderer2.cpp"
)

target_include_directories(SDLEngine PRIVATE  "${IMGUI_DIR}" "${IMGUI_DIR}/backends")

# Link the SDL, SDL2 image, and IMGUI library
target_link_libraries(SDLEngine ${SDL2_LIBRARIES} SDL2_image::SDL2_image 
    imgui)  


# Make SDL2 available to Imgui
target_include_directories(imgui PUBLIC ${SDL2_INCLUDE_DIRS})
# imgui/backends/ contains the SDL implementation
target_include_directories(imgui PUBLIC "${IMGUI_DIR}" "${IMGUI_DIR}/backends")
# Link SDL to imgui
target_link_libraries(imgui PUBLIC ${SDL2_LIBRARIES})

