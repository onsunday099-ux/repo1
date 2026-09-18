cmake_minimum_required(VERSION 3.20)

file(GLOB_RECURSE ENGINE_SOURCES
    "core/*.cpp"
    "renderer/*.cpp"
    "audio/*.cpp"
    "scene/*.cpp"
    "dialogue/*.cpp"
    "script/*.cpp"
    "assets/*.cpp"
    "ui/*.cpp"
    "*.cpp"
)

add_executable(Engine
    ${ENGINE_SOURCES}
)

target_include_directories(Engine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/audio
    ${CMAKE_CURRENT_SOURCE_DIR}/scene
    ${CMAKE_CURRENT_SOURCE_DIR}/dialogue
    ${CMAKE_CURRENT_SOURCE_DIR}/script
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    ${CMAKE_CURRENT_SOURCE_DIR}/ui
)

target_link_libraries(Engine PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    imgui
    Miniaudio::Miniaudio
    spdlog::spdlog
    lua
    sol2::sol2
)

add_custom_command(TARGET Engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:SDL3::SDL3>"
    $<TARGET_FILE_DIR:Engine>
)

add_custom_command(TARGET Engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:SDL3_image::SDL3_image>"
    $<TARGET_FILE_DIR:Engine>
)

if (MSVC)
    target_compile_options(Engine PRIVATE /utf-8)
endif()