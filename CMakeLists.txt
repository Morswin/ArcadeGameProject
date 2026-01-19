cmake_minimum_required(VERSION 3.21)
project(ArcadeGameProject)

set(CMAKE_CXX_STANDARD 20)

# Path to shader directory
set(SHADER_DIR ${CMAKE_SOURCE_DIR}/shaders/)
# List of all shaders present there
file(GLOB SHADERS ${SHADER_DIR}/*)
# Subdirectory for shaders in build directory
set(SHADER_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/shaders)
# Command for copying shaders
add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SHADER_DIR} ${SHADER_OUTPUT_DIR}
    COMMENT "Copying shader files to shader subdirectory in build directory."
)

set(RESOURCE_DIR ${CMAKE_SOURCE_DIR}/resources/)
file(GLOB RESOURCES ${RESOURCE_DIR}/*)
set(RESOURCE_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/resources)
add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${RESOURCE_DIR} ${RESOURCE_OUTPUT_DIR}
    COMMENT "Copying resource files to resource subdirectory in build directory."
)

# Enables FetchContent
include(FetchContent)

# define a function for adding git dependencies
function(include_dependency libName gitURL gitTag)
    # setup the declare
    FetchContent_Declare(${libName}
            GIT_REPOSITORY ${gitURL}
            GIT_TAG        ${gitTag}
            GIT_SHALLOW    TRUE
            GIT_PROGRESS   TRUE
    )

    FetchContent_MakeAvailable(${libName})
endfunction()

# add SDL3 support
find_package(SDL3 QUIET)
if (NOT SDL3_FOUND)
    message(STATUS "Getting SDL3 from Github")
#    include_dependency(SDL3 https://github.com/libsdl-org/SDL.git release-3.2.18)
    include_dependency(SDL3 https://github.com/libsdl-org/SDL.git main)
else()
    message(STATUS "Using local SDL3")
endif()

message(STATUS "Getting GLM from Github")
include_dependency(glm https://github.com/g-truc/glm.git 1.0.1)

add_executable(ArcadeGameProject
    src/main.cpp

    src/game.hpp
    src/game.cpp
    src/game_element.hpp
    src/game_element.cpp
    src/environment.hpp
    src/environment.cpp
    src/entity.hpp
    src/entity.cpp
    src/map.hpp
    src/map.cpp
    src/map_position.hpp
    src/player.hpp
    src/player.cpp
    src/zdobycz.hpp
    src/settings.hpp
    src/settings.cpp
    src/wall.hpp
    src/wall.cpp
    src/floor.hpp
    src/floor.cpp
    src/enemy.hpp
    src/enemy.cpp
    src/pocisk.hpp
    src/rng.hpp
    src/rng.cpp
    src/room.hpp
    src/room.cpp
    src/collision.hpp
    src/collision.cpp

    src/sdl_error.hpp

    src/third_party/glad/glad.c
    src/third_party/stb/stb_image.h
    src/third_party/stb/stb_image.cpp

    src/renderer/element_buffer.hpp
    src/renderer/element_buffer.cpp
    src/renderer/render_mesh.hpp
    src/renderer/render_mesh.cpp
    src/renderer/renderer.hpp
    src/renderer/renderer.cpp
    src/renderer/vertex_buffer.hpp
    src/renderer/vertex_buffer.cpp
    src/renderer/vertex_array.hpp
    src/renderer/vertex_array.cpp
    src/renderer/vertex_buffer_layout.hpp
    src/renderer/vertex_buffer_layout.cpp
    src/renderer/shader.hpp
    src/renderer/shader.cpp
    src/renderer/renderer_utils.hpp
    src/renderer/renderer_utils.cpp
    src/renderer/texture.hpp
    src/renderer/texture.cpp
    src/renderer/transform2d.hpp
    src/renderer/transform2d.cpp
)

# Link against SDL3
#target_link_libraries(ArcadeGameProject PRIVATE SDL3::SDL3-static)

# set the include directory
target_include_directories(ArcadeGameProject PUBLIC ${SDL3_INCLUDE_DIRS})
target_include_directories(ArcadeGameProject PRIVATE include/)

target_compile_definitions(ArcadeGameProject PRIVATE SDL_MAIN_USE_CALLBACKS)

# link all libraries to the project
target_link_libraries(ArcadeGameProject PRIVATE SDL3::SDL3)
target_link_libraries(ArcadeGameProject PRIVATE glm::glm)

# Perform the copy of shaders to build subdirectory
add_dependencies(ArcadeGameProject copy_shaders)
add_dependencies(ArcadeGameProject copy_resources)

if (WIN32)
    add_custom_command(
            TARGET ArcadeGameProject POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL3::SDL3>" "$<TARGET_FILE_DIR:ArcadeGameProject>"
            VERBATIM
    )
endif()
