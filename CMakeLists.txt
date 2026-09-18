cmake_minimum_required(VERSION 3.20)
project("vn" CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==============================================================================
# 1. Library Paths Configuration
# ==============================================================================
set(SDL3_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL3-3.4.16")
set(SDL3_image_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL3_image-3.4.6")
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries/imgui-master")
set(MINIAUDIO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries/MiniAudio")
set(LUA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries/lua-5.4.9/src")
set(SOL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries/sol2-3.3.0")
set(SPDLOG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries/spdlog")

# ==============================================================================
# 2. Third-Party Targets Setup
# ==============================================================================

# --- SDL3 ---
add_library(SDL3::SDL3 SHARED IMPORTED)
set_target_properties(SDL3::SDL3 PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${SDL3_DIR}/include"
    IMPORTED_IMPLIB "${SDL3_DIR}/lib/x64/SDL3.lib"
    IMPORTED_LOCATION "${SDL3_DIR}/lib/x64/SDL3.dll"
)

# --- SDL3_image ---
add_library(SDL3_image::SDL3_image SHARED IMPORTED)
set_target_properties(SDL3_image::SDL3_image PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${SDL3_image_DIR}/include"
    IMPORTED_IMPLIB "${SDL3_image_DIR}/lib/x64/SDL3_image.lib"
    IMPORTED_LOCATION "${SDL3_image_DIR}/lib/x64/SDL3_image.dll"
)

# --- Miniaudio ---
add_library(miniaudio INTERFACE)
target_include_directories(miniaudio INTERFACE "${MINIAUDIO_DIR}")
add_library(Miniaudio::Miniaudio ALIAS miniaudio)

# --- spdlog ---
add_library(spdlog INTERFACE)
target_include_directories(spdlog INTERFACE 
    "${SPDLOG_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/libraries"
)
add_library(spdlog::spdlog ALIAS spdlog)

# --- Lua 5.4.9 ---
file(GLOB LUA_SOURCES "${LUA_DIR}/*.c")
list(REMOVE_ITEM LUA_SOURCES
    "${LUA_DIR}/lua.c"
    "${LUA_DIR}/luac.c"
)
add_library(lua STATIC ${LUA_SOURCES})
add_library(lua::lua ALIAS lua)
target_include_directories(lua PUBLIC "${LUA_DIR}")

# คอมไพล์ Lua เป็น C++ บน MSVC เพื่อให้ sol2 จับ Exception ได้สมบูรณ์
if (MSVC)
    set_target_properties(lua PROPERTIES LINKER_LANGUAGE CXX)
    target_compile_options(lua PRIVATE /TP)
endif()

# --- sol2 3.3.0 ---
add_library(sol2 INTERFACE)
target_include_directories(sol2 INTERFACE 
    "${SOL2_DIR}/include"
    "${SOL2_DIR}"
)
target_link_libraries(sol2 INTERFACE lua::lua)
add_library(sol2::sol2 ALIAS sol2)

# --- ImGui ---
add_library(imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)
target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)
target_link_libraries(imgui PUBLIC SDL3::SDL3)

# ==============================================================================
# 3. Subprojects
# ==============================================================================
add_subdirectory(Engine)
add_subdirectory(Editor)