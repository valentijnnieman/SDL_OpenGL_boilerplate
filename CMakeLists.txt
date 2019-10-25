cmake_minimum_required(VERSION 3.0)
project(Bodhisattva)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

option(BUILD_BULLET2_DEMOS OFF)
option(BUILD_CPU_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_OPENGL3_DEMOS OFF)
option(BUILD_UNIT_TESTS OFF)
OPTION(USE_MSVC_RUNTIME_LIBRARY_DLL "Use MSVC Runtime Library DLL (/MD or /MDd)" ON)
OPTION(USE_MSVC_INCREMENTAL_LINKING "Use MSVC Incremental Linking" OFF)
add_subdirectory(vendor/bullet3/)


set(SDL2_IMAGE_DIR ${PROJECT_SOURCE_DIR}/vendor/SDL2_image) 
set(SDL2_LIBRARY ${PROJECT_SOURCE_DIR}/vendor/SDL2/x64/Debug/SDL2.lib) 
set(SDL2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/vendor/SDL2) 
set(SDL2_IMAGE_LIBRARY ${PROJECT_SOURCE_DIR}/vendor/SDL2_image/x64/SDL2_image.lib) 
set(SDL2_IMAGE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/SDL)

option(SDL2_BUILDING_LIBRARY ON)
find_package(SDL2)
find_package(SDL2_image)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(vendor/assimp)

include_directories(
		include/
		include/SDL
)

file(GLOB VENDORS_SOURCES vendor/glad/src/glad.c)
file(GLOB PROJECT_HEADERS include/*.hpp)
file(GLOB PROJECT_SOURCES src/*.cpp)
file(GLOB PROJECT_SHADERS shaders/*.glsl)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Vendors" FILES ${VENDORS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_library(Bodhisattva STATIC ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
                               ${VENDORS_SOURCES})
target_link_libraries(Bodhisattva
						${GLAD_LIBRARIES}
					   assimp
					   BulletDynamics BulletCollision LinearMath Bullet3Common
					   SDL_image
					   ${SDL2_IMAGE_LIBRARY}
					   ${SDL2_LIBRARY})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
    DEPENDS ${PROJECT_SHADERS})

