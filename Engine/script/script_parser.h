#pragma once
#include "script_command.h"
#include <string>
#include <vector>
#include <unordered_map>

struct ParsedScript
{
	std::vector<ScriptCommand> commands;
	std::unordered_map
		<std::string, size_t> label_table; // เก็บ label -> index คำสั่
};

class ScriptParser
{
public:
	static ParsedScript parse_file(const std::string& filepath);
	static ParsedScript parse_string(const std::string& content);
		
private:
	static std::string trim(const std::string& str);
};