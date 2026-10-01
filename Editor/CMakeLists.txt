file(GLOB_RECURSE EDITOR_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

message(STATUS "Editor sources: ${EDITOR_SOURCES}")

add_executable(Editor ${EDITOR_SOURCES})

target_include_directories(Editor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/panels
    ${CMAKE_SOURCE_DIR}/Engine
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

target_link_libraries(Editor PRIVATE
    EngineLib
    imgui
)

if (MSVC)
    target_compile_options(Editor PRIVATE /W3 /EHsc /utf-8)
endif()

add_custom_command(TARGET Editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${SDL3_DIR}/lib/x64/SDL3.dll"
    $<TARGET_FILE_DIR:Editor>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${SDL3_image_DIR}/lib/x64/SDL3_image.dll"
    $<TARGET_FILE_DIR:Editor>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${SDL3_ttf_DIR}/lib/x64/SDL3_ttf.dll"
    $<TARGET_FILE_DIR:Editor>
)

if (EXISTS "${CMAKE_SOURCE_DIR}/Test")
    add_custom_command(TARGET Editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Test"
        "$<TARGET_FILE_DIR:Editor>/Test"
    )
endif()