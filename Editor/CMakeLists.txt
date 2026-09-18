file(GLOB EDITOR_SOURCES CONFIGURE_DEPENDS "*.cpp" "*.h")

add_executable(Editor
    ${EDITOR_SOURCES}
)

target_link_libraries(Editor PRIVATE
    SDL3::SDL3
    imgui
    SDL3_image::SDL3_image
    Miniaudio::Miniaudio
)

add_custom_command(TARGET Editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:SDL3::SDL3>"
    $<TARGET_FILE_DIR:Editor>
)

add_custom_command(TARGET Editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:SDL3_image::SDL3_image>"
    $<TARGET_FILE_DIR:Editor>
)

