cmake_minimum_required(VERSION 3.25)

project(Tracy)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-Wall")
set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/ThirdParty)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/Src)
set(EXAMPLES_PATH ${PROJECT_SOURCE_DIR}/Examples)

include_directories(${SRC_DIR})
include_directories(${THIRD_PARTY_DIR}/imgui/include)
include_directories(${THIRD_PARTY_DIR}/stb_image)

set(MAC_GL_PATH ${THIRD_PARTY_DIR}/mac)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexperimental-library")

include_directories(${MAC_GL_PATH}/glfw/include)
include_directories(${MAC_GL_PATH}/glfw/include/GLFW)
include_directories(${MAC_GL_PATH}/glew/include)
include_directories(${MAC_GL_PATH}/glew/include/GL)
include_directories(${MAC_GL_PATH}/glm/include)

link_directories(${MAC_GL_PATH}/glfw/lib)
link_directories(${MAC_GL_PATH}/glew/lib)

file(GLOB IMGUI_SOURCES ${THIRD_PARTY_DIR}/imgui/src/*.cpp)
file(GLOB SRC_SOURCES ${SRC_DIR}/*.cpp)
file(GLOB EXAMPLES ${EXAMPLES_PATH}/*)

add_library(${PROJECT_NAME} ${SRC_SOURCES} ${IMGUI_SOURCES})

foreach(EXAMPLE ${EXAMPLES})
    if (NOT IS_DIRECTORY ${EXAMPLE})
        continue()
    endif()
  get_filename_component(EXAMPLE_NAME ${EXAMPLE} NAME_WE)
  message("Building: " ${EXAMPLE_NAME})
  file(GLOB EXAMPLE_SOURCES ${EXAMPLE}/*.cpp)
  add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCES})
  target_link_libraries(${EXAMPLE_NAME} glfw glew "-framework OpenGL" ${PROJECT_NAME})
endforeach()

