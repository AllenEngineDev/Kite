cmake_minimum_required(VERSION 3.0)
project(SDLEngine)

set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui-docking")
set(YAML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/yaml-cpp")
set(NFD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/nfd")

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
    "src/Scene/*.cpp"
    "src/Layers/*.cpp"
    "src/GUI/*.cpp"
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

# Add YAML includes
target_include_directories(SDLEngine PRIVATE "${YAML_DIR}/include")


# Compiling IMGUI into a library
add_library(imgui
     # Main Imgui files
     "${IMGUI_DIR}/imgui.cpp"
     "${IMGUI_DIR}/imgui_draw.cpp"
     "${IMGUI_DIR}/imgui_tables.cpp"
     "${IMGUI_DIR}/imgui_widgets.cpp"
     "${IMGUI_DIR}/imgui_demo.cpp"

     # SDL2+SDL2Renderer-specific files
     "${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp"
     "${IMGUI_DIR}/backends/imgui_impl_sdlrenderer2.cpp"

)

target_include_directories(SDLEngine PRIVATE  "${IMGUI_DIR}" "${IMGUI_DIR}/backends")
target_include_directories(SDLEngine PRIVATE "${STB_DIR}")
target_include_directories(SDLEngine PRIVATE "${NFD_DIR}/include")


target_link_directories(SDLEngine PUBLIC ${YAML_DIR}/build)
target_link_directories(SDLEngine PUBLIC ${NFD_DIR}/lib)


# Link the SDL, SDL2 image, and IMGUI library
target_link_libraries(SDLEngine ${SDL2_LIBRARIES} SDL2_image::SDL2_image 
    imgui yaml-cpp nfd.lib)  


# Make SDL2 available to Imgui
target_include_directories(imgui PUBLIC ${SDL2_INCLUDE_DIRS})
# imgui/backends/ contains the SDL implementation
target_include_directories(imgui PUBLIC "${IMGUI_DIR}" "${IMGUI_DIR}/backends")
# Link SDL to imgui
target_link_libraries(imgui PUBLIC ${SDL2_LIBRARIES} )

