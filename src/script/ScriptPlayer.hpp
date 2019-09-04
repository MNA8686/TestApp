#pragma once

#include "Script.hpp"

class ScriptPlayer : public ScriptBase
{
public:
	ScriptPlayer() = default;
	~ScriptPlayer() = default;

	bool OnCreate(Object* owner);
	bool FixedUpdate(Object* owner);

private:
	int32_t m_spriteRenderer = -1;
};

EQ_SCRIPT_REGISTER(ScriptPlayer);
