#include "script_parser.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <iostream>

std::string ScriptParser::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

ParsedScript ScriptParser::parse_file(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "[ScriptParser] Cannot open file: " << filepath << "\n";
        return {};
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return parse_string(buffer.str());
}

ParsedScript ScriptParser::parse_string(const std::string& content) {
    ParsedScript result;
    std::istringstream stream(content);
    std::string raw_line;
    int line_num = 0;

    bool in_menu = false;
    MenuData current_menu;

    // Regex สำหรับ Dialogue:
    // speaker "text" หรือ "text"
    std::regex dialogue_regex(R"(^(?:([a-zA-Z0-9_]+)\s+)?"([^"]*)"$)");
        // Choice ภายใน menu: "ตัวเลือก" -> label
        std::regex choice_regex(R"(^"([^"]*)"\s * ->\s * ([a - zA - Z0 - 9_] + )$)");

        while (std::getline(stream, raw_line)) {
            line_num++;
            std::string line = trim(raw_line);

            if (line.empty() || line.starts_with("#")) continue;

            // จัดการบล็อก menu:
            if (in_menu) {
                std::smatch m;
                if (std::regex_match(line, m, choice_regex)) {
                    current_menu.choices.push_back({ m[1].str(), m[2].str() });
                    continue;
                }
                else {
                    result.commands.push_back({ CommandType::Menu, current_menu, line_num });
                    in_menu = false;
                    current_menu.choices.clear();
                }
            }

            std::istringstream ls(line);
            std::string keyword;
            ls >> keyword;

            if (keyword == "scene") {
                std::string bg, trans = "instant";
                ls >> bg;
                ls >> trans; // เช่น fade
                result.commands.push_back({ CommandType::Scene, SceneData{bg, trans}, line_num });
            }
            else if (keyword == "show") {
                std::string char_id, expr = "default", at_str, pos = "center";
                ls >> char_id >> expr;
                if (ls >> at_str && at_str == "at") {
                    ls >> pos;
                }
                result.commands.push_back({ CommandType::Show, ShowData{char_id, expr, pos}, line_num });
            }
            else if (keyword == "hide") {
                std::string char_id;
                ls >> char_id;
                result.commands.push_back({ CommandType::Hide, HideData{char_id}, line_num });
            }
            else if (keyword == "label") {
                std::string name;
                ls >> name;
                if (name.ends_with(':')) name.pop_back();
                // บันทึกตำแหน่งคำสั่งถัดไปที่ label นี้ชี้ไป
                result.label_table[name] = result.commands.size();
            }
            else if (keyword == "jump") {
                std::string target;
                ls >> target;
                result.commands.push_back({ CommandType::Jump, target, line_num });
            }
            else if (keyword == "menu:") {
                in_menu = true;
                current_menu.choices.clear();
            }
            else {
                // Dialogue
                std::smatch m;
                if (std::regex_match(line, m, dialogue_regex)) {
                    std::string speaker = m[1].matched ? m[1].str() : "";
                    std::string text = m[2].str();
                    result.commands.push_back({ CommandType::Dialogue, DialogueData{speaker, text}, line_num });
                }
            }
        }

    if (in_menu && !current_menu.choices.empty()) {
        result.commands.push_back({ CommandType::Menu, current_menu, line_num });
    }

    return result;
}