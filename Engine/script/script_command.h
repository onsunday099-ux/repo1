#pragma once
#include <string>
#include <vector>

// ประเภทของคำสั่งในเกม

enum class CommandType
{
	None,
	SetBackground,
	Dialogue,
	Wait,
	PlaySound,

};

// transition effect i guess
enum class TransitionType
{
	//None,
	Instant,
	Crossfade,
	FadeBlack,	
};

struct BackgroudData 
{
	std::string assetId;	//name "bg/bg2.jpg"
	TransitionType transition;
	float duration = 1.0f;	//fade time
};

struct DialogueData
{
	std::string speaker;	//name "character name"
	std::string text;		//text "Hello world"
};

struct ScriptCommand {
	CommandType type = CommandType::None;
	BackgroudData bgData;
	DialogueData dialogueData;
	int lineNumber = 0;	//line number in script file for debug

};
