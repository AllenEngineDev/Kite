cmake_minimum_required(VERSION 3.0)
project(SDLEngine)

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
     )




add_executable(SDLEngine ${SOURCES} ${IMGUI_SOURCES})


# Include directories for my own project"
target_include_directories(SDLEngine PUBLIC "src/")


#Make ImGUI available to us
target_include_directories(SDLEngine PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends")



# Add SDL and SDL2 Image include directories
target_include_directories(SDLEngine PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(SDLEngine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL2Image/include")

# GLEW and IMGUI
target_include_directories(SDLEngine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glew/include")

# # Compiling IMGUI into a library
# add_library(imgui
#      # Main Imgui files
#      "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui.cpp"
#      "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp"
#      "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp"
#      "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp"
#      # SDL2+OpenGL-specific files
#      "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_sdl2.cpp"
#      "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp"
# )


# # Make SDL2 available to Imgui
# target_include_directories(imgui PUBLIC ${SDL2_INCLUDE_DIRS})
# # imgui/backends/ contains the SDL implementation
# target_include_directories(imgui PUBLIC 
#     "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/" 
#     "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/")

# # so ImGUI can access OpenGL code
# target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glew/include")

# # Configure Imgui to use OpengGL through SDL2
# target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_CUSTOM=<SDL_opengl.h>  GL_GLEXT_PROTOTYPES=1)

# # Link IMGUI to GLEW
# target_link_libraries(imgui 
#    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glew/lib/Release/x64/glew32.lib" )

# Link the SDL and SDL2 image library
target_link_libraries(SDLEngine ${SDL2_LIBRARIES} SDL2_image::SDL2_image 
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glew/lib/Release/x64/glew32.lib"
    ) # ADD IMGUI 


