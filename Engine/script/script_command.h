#pragma once
#include <string>
#include <vector>
#include <variant>

enum class CommandType {
    Scene,          // scene <bg_id> [fade|instant]
    Show,           // show <char_id> <expr> [at left|center|right]
    Hide,           // hide <char_id>
    Dialogue,       // speaker "text" หรือ "narrator text"
    Menu,           // menu:
    Jump,           // jump <label>
    Label           // label <name>:
};

// Data Structures
struct SceneData {
    std::string background_id;
    std::string transition = "instant";
};

struct ShowData {
    std::string character_id;
    std::string expression = "default";
    std::string position = "center";
};

struct HideData {
    std::string character_id;
};

struct DialogueData {
    std::string speaker; // ว่างไว้ถ้าเป็น Narrator
    std::string text;
};

struct MenuChoice {
    std::string text;
    std::string target_label;
};

struct MenuData {
    std::vector<MenuChoice> choices;
};

// รวม Payload ทั้งหมด
using CommandPayload = std::variant<
    std::monostate,
    SceneData,
    ShowData,
    HideData,
    DialogueData,
    MenuData,
    std::string // ใช้สำหรับ Jump target
>;

struct ScriptCommand {
    CommandType type;
    CommandPayload payload;
    int line_number = 0;
};