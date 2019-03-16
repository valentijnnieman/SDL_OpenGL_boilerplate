cmake_minimum_required (VERSION 3.0)
project (SDL_OpenGL_Boilerplate)
set (SDL_OpenGL_Boilerplate_VERSION_MAJOR 1)
set (SDL_OpenGL_Boilerplate_VERSION_MINOR 0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SDL_OpenGL_Boilerplate_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
find_package(assimp REQUIRED)
include_directories(${assimp_INCLUDE_DIRS})

include_directories(
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/shaders
        ${PROJECT_SOURCE_DIR}/vendor/include
        ${PROJECT_SOURCE_DIR}/vendor/src
        ${PROJECT_SOURCE_DIR}/vendor/bullet3/src
        ${PROJECT_SOURCE_DIR}/vendor/glm/
        ${PROJECT_SOURCE_DIR}/vendor/assimp/include
        ${PROJECT_SOURCE_DIR}/vendor/SDL-mirror/include
        ${PROJECT_SOURCE_DIR}/vendor/SDL-mirror/src
        ${PROJECT_SOURCE_DIR}/vendor/SDL_image/include
        ${PROJECT_SOURCE_DIR}/vendor/SDL_image/src
)

file(GLOB PROJECT_HEADERS src/*.hpp)
file(GLOB PROJECT_SOURCES src/*.cpp)
file(GLOB PROJECT_SHADERS shaders/*.glsl)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})

message("Assimp: ${assimp_LIBRARIES}")

add_executable(SDL_OpenGL_Boilerplate Example/main.cpp vendor/src/glad.c ${PROJECT_HEADERS} ${PROJECT_SOURCES} ${PROJECT_SHADERS})
target_link_libraries(SDL_OpenGL_Boilerplate ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES}  ${GLM_LIBRARIES} ${assimp_LIBRARIES})
