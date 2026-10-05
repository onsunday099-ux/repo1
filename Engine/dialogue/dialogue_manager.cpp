#include "dialogue_manager.h"
#include <iostream>
#include <variant>
#include <string>

void DialogueManager::load_script(const std::string& filepath) {
    m_script = ScriptParser::parse_file(filepath);
    m_pc = 0;
    m_state = DialogueState::Executing;
    step();
}

void DialogueManager::next() {
    if (m_state == DialogueState::WaitingForClick) {
        m_state = DialogueState::Executing;
        m_pc++;
        step();
    }
}

void DialogueManager::select_choice(size_t index) {
    if (m_state == DialogueState::WaitingForChoice && index < m_current_choices.size()) {
        std::string target = m_current_choices[index].target_label;
        m_current_choices.clear();
        jump_to(target);
        m_state = DialogueState::Executing;
        step();
    }
}

void DialogueManager::jump_to(const std::string& label) {
    if (m_script.label_table.contains(label)) {
        m_pc = m_script.label_table[label];
    }
    else {
        std::cerr << "[DialogueManager] Unknown label: " << label << "\n";
    }
}

void DialogueManager::step() {
    while (m_pc < m_script.commands.size() && m_state == DialogueState::Executing) {
        const auto& cmd = m_script.commands[m_pc];

        switch (cmd.type) {
        case CommandType::Scene:
            if (on_scene_change) on_scene_change(std::get<SceneData>(cmd.payload));
            m_pc++;
            break;

        case CommandType::Show:
            if (on_character_show) on_character_show(std::get<ShowData>(cmd.payload));
            m_pc++;
            break;

        case CommandType::Hide:
            if (on_character_hide) on_character_hide(std::get<HideData>(cmd.payload));
            m_pc++;
            break;

        case CommandType::Dialogue:
            m_current_dialogue = std::get<DialogueData>(cmd.payload);
            m_state = DialogueState::WaitingForClick; // หยุดรอคลิก
            return;

        case CommandType::Jump:
            jump_to(std::get<std::string>(cmd.payload));
            break;

        case CommandType::Menu:
            m_current_choices = std::get<MenuData>(cmd.payload).choices;
            m_state = DialogueState::WaitingForChoice; // หยุดรอเลือก
            return;

        default:
            m_pc++;
            break;
        }
    }

    if (m_pc >= m_script.commands.size()) {
        m_state = DialogueState::Idle;
    }
}