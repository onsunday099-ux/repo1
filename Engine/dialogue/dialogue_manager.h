#pragma once
#include "../script/script_command.h"
#include "../script/script_parser.h"
#include <functional>

enum class DialogueState {
    Idle,
    Executing,
    WaitingForClick,
    WaitingForChoice
};

class DialogueManager {
public:
    DialogueManager() = default;

    void load_script(const std::string& filepath);
    void next();                     // เรียกเมื่อผู้เล่นคลิกเมาส์ หรือกด Spacebar
    void select_choice(size_t index); // เรียกเมื่อผู้เล่นคลิกปุ่มตัวเลือก

    DialogueState get_state() const { return m_state; }
    const DialogueData& get_current_dialogue() const { return m_current_dialogue; }
    const std::vector<MenuChoice>& get_current_choices() const { return m_current_choices; }

    // Callbacks สำหรับเชื่อมต่อกับระบบ Renderer / Scene
    std::function<void(const SceneData&)> on_scene_change;
    std::function<void(const ShowData&)> on_character_show;
    std::function<void(const HideData&)> on_character_hide;

private:
    void step();
    void jump_to(const std::string& label);

    ParsedScript m_script;
    size_t m_pc = 0; // Program Counter
    DialogueState m_state = DialogueState::Idle;

    DialogueData m_current_dialogue;
    std::vector<MenuChoice> m_current_choices;
};