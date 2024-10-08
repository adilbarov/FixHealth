cmake_minimum_required(VERSION 3.15)
project(SAMP-EmptyProject)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(PSDK_EXAMPLES OFF)
set(PSDK_INSTALL  OFF)
set(PSDK_GTASA    ON)

include(FetchContent)

FetchContent_Declare(
	xbyak 
	GIT_REPOSITORY "https://github.com/herumi/xbyak.git"
	GIT_TAG "ce083a0dcc306c1717685a81f577a4e050193919"
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/xbyak
)

FetchContent_Declare( 
	ktsignal
	GIT_REPOSITORY "https://github.com/kin4stat/ktsignal.git"
	GIT_TAG "f08a19d9a00ad5284871bf44178d835da7b26ebf"
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ktsignal
)

FetchContent_Declare( 
	kthook
	GIT_REPOSITORY "https://github.com/kin4stat/kthook.git"
	GIT_TAG "21ca70481273d1efcc98ca49063178e46277009b"
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/kthook
)
FetchContent_Declare(
    plugin-sdk
    GIT_REPOSITORY https://github.com/imring/plugin-sdk.git
    GIT_TAG 81b18b744b64db3058f48344c144591c9030205b
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/pluginsdk
)
FetchContent_Declare(
    SAMPAPI
    GIT_REPOSITORY https://github.com/BlastHackNet/SAMP-API.git
    GIT_TAG 6d4db99ab41f19d1a6a7c6cd48f5878bd1e14b62
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sampapi
)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG 913151caa8905370229e361486b10c890aeaed45
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)
FetchContent_Declare( 
	rakhook
	GIT_REPOSITORY "https://github.com/imring/RakHook.git"
	GIT_TAG "625fd17897395997feb56ae293c7c07dbe49d26b"
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/rakhook
)
FetchContent_MakeAvailable(xbyak ktsignal kthook rakhook plugin-sdk sampapi imgui)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/imgui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/kthook)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/kthook/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/kthook/ktsignal/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/kthook/xbyak)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/imgui ${PROJECT_NAME}_LIST)
list(APPEND ${PROJECT_NAME}_LIST "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_win32.cpp")
list(APPEND ${PROJECT_NAME}_LIST "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_dx9.cpp")

add_library(${PROJECT_NAME} SHARED)
target_sources(${PROJECT_NAME} PRIVATE
  ${${PROJECT_NAME}_LIST}
  src/main.cpp
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
  OUTPUT_NAME ${PROJECT_NAME}
  SUFFIX ".asi"
)

if(NOT "${DXSDK_DIR}" STREQUAL "")
    target_include_directories( ${PROJECT_NAME} PUBLIC ${DXSDK_DIR}Include)
    target_link_directories(${PROJECT_NAME} PUBLIC ${DXSDK_DIR}Lib/x86)
elseif(NOT "$ENV{DXSDK_DIR}" STREQUAL "")
    target_include_directories( ${PROJECT_NAME} PUBLIC $ENV{DXSDK_DIR}Include)
    target_link_directories( ${PROJECT_NAME} PUBLIC $ENV{DXSDK_DIR}Lib/x86)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC d3d9 d3dx9 kthook rakhook pluginsdk::gtasa sampapi)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
