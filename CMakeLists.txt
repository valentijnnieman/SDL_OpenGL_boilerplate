cmake_minimum_required (VERSION 3.0)
project (Bodhisattva)
set (Bodhisattva_VERSION_MAJOR 1)
set (Bodhisattva_VERSION_MINOR 0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-ldl")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Bodhisattva_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
find_package(assimp REQUIRED)
include_directories(${assimp_INCLUDE_DIR})

include_directories(
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/shaders
        ${PROJECT_SOURCE_DIR}/vendor/include
        ${PROJECT_SOURCE_DIR}/vendor/src
        ${PROJECT_SOURCE_DIR}/vendor/bullet3/src
        ${PROJECT_SOURCE_DIR}/vendor/glm/
        ${PROJECT_SOURCE_DIR}/vendor/assimp/
        ${PROJECT_SOURCE_DIR}/vendor/assimp/include/
)

file(GLOB PROJECT_HEADERS src/*.hpp src/Physics/*.hpp)
file(GLOB PROJECT_SOURCES src/*.cpp src/Physics/*.cpp)
file(GLOB PROJECT_SHADERS shaders/*.glsl)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})

message("Assimp: ${assimp_LIBRARIES}")

add_executable(Bodhisattva Example/main.cpp vendor/src/glad.c ${PROJECT_HEADERS} ${PROJECT_SOURCES} ${PROJECT_SHADERS})
target_link_libraries(Bodhisattva 
${SDL2_LIBRARIES} 
${SDL2_IMAGE_LIBRARIES}  
${GLM_LIBRARIES} 
${assimp_LIBRARIES}
${CMAKE_CURRENT_SOURCE_DIR}/vendor/bullet3/src/BulletDynamics/libBulletDynamics.a
${CMAKE_CURRENT_SOURCE_DIR}/vendor/bullet3/src/BulletCollision/libBulletCollision.a
${CMAKE_CURRENT_SOURCE_DIR}/vendor/bullet3/src/LinearMath/libLinearMath.a
-lm -ldl)
