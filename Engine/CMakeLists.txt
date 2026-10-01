file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)
list(FILTER ENGINE_SOURCES EXCLUDE REGEX ".*main\\.cpp$")

add_library(EngineLib STATIC ${ENGINE_SOURCES})

if (MSVC)
    target_compile_options(EngineLib PRIVATE /utf-8 /EHsc)
endif()

target_include_directories(EngineLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/audio
    ${CMAKE_CURRENT_SOURCE_DIR}/dialogue
    ${CMAKE_CURRENT_SOURCE_DIR}/scene
    ${CMAKE_CURRENT_SOURCE_DIR}/script
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    ${CMAKE_CURRENT_SOURCE_DIR}/ui
    ${CMAKE_CURRENT_SOURCE_DIR}/save
    ${CMAKE_SOURCE_DIR}/libraries/MiniAudio
    ${CMAKE_SOURCE_DIR}/libraries/spdlog/include
    ${CMAKE_SOURCE_DIR}/libraries/sol2-3.3.0/include
    ${CMAKE_SOURCE_DIR}/libraries/lua-5.4.9/src
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

target_link_libraries(EngineLib PUBLIC
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
    sol2::sol2
    lua::lua
    spdlog::spdlog
    imgui
)

add_executable(Engine main.cpp)

if (MSVC)
    target_compile_options(Engine PRIVATE /utf-8 /EHsc)
endif()


target_link_libraries(Engine PRIVATE EngineLib)

add_custom_command(TARGET Engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${SDL3_DIR}/lib/x64/SDL3.dll"
    $<TARGET_FILE_DIR:Engine>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${SDL3_image_DIR}/lib/x64/SDL3_image.dll"
    $<TARGET_FILE_DIR:Engine>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${SDL3_ttf_DIR}/lib/x64/SDL3_ttf.dll"
    $<TARGET_FILE_DIR:Engine>
)

if (EXISTS "${CMAKE_SOURCE_DIR}/Test")
    add_custom_command(TARGET Engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Test"
        "$<TARGET_FILE_DIR:Engine>/Test"
    )
endif()