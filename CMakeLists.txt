cmake_minimum_required(VERSION 4.2)
project(ArcadeGameProject)

# Enables FetchContent
include(FetchContent)

# This line below tells SDL3 to expose those SDL hook methods and to handle the main() function.
# From what I know, this helps in case I want to make the project cross-compile which I intend for at least both Linux and Windows platforms.
set(SDL_MAIN_USE_CALLBACKS 1)

set(SHADER_DIR ${CMAKE_SOURCE_DIR}/shaders/)  # Path to shader directory
file(GLOB SHADERS ${SHADER_DIR}/*)  # List of all shaders present there
set(RESOURCE_DIR ${CMAKE_SOURCE_DIR}/resources/)
file(GLOB RESOURCES ${RESOURCE_DIR}/*)  # List of resources such as sprites

file(GLOB MAIN_HEADERS ${CMAKE_SOURCE_DIR}/src/*.hpp)
file(GLOB MAIN_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB UTILITY_HEADERS ${CMAKE_SOURCE_DIR}/src/utils/*.hpp)
file(GLOB UTILITY_SOURCES ${CMAKE_SOURCE_DIR}/src/utils/*.cpp)
file(GLOB RENDERER_HEADERS ${CMAKE_SOURCE_DIR}/src/renderer/*.hpp)
file(GLOB RENDERER_SOURCES ${CMAKE_SOURCE_DIR}/src/renderer/*.cpp)

# Subdirectory for shaders in build directory
set(SHADER_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/shaders)
# Command for copying shaders
add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SHADER_DIR} ${SHADER_OUTPUT_DIR}
    COMMENT "Copying shader files to shader subdirectory in build directory."
)

set(RESOURCE_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/resources)
add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${RESOURCE_DIR} ${RESOURCE_OUTPUT_DIR}
    COMMENT "Copying resource files to resource subdirectory in build directory."
)

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
    ${MAIN_HEADERS}
    ${MAIN_SOURCES}
    ${UTILITY_HEADERS}
    ${UTILITY_SOURCES}
    ${RENDERER_HEADERS}
    ${RENDERER_SOURCES}

    src/third_party/glad/glad.c
    src/third_party/stb/stb_image.h
    src/third_party/stb/stb_image.cpp
)
# From now on this is where I set the C++ standard for this project
target_compile_features(ArcadeGameProject PRIVATE cxx_std_20)

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
