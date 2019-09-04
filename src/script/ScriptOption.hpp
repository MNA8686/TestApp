#pragma once

#include "Script.hpp"

class ScriptOption : public ScriptBase
{
public:
	ScriptOption() = default;
	~ScriptOption() = default;

	bool OnCreate(Object* owner);
	bool FixedUpdate(Object* owner);

private:
	int32_t m_spriteRenderer = -1;
};

EQ_SCRIPT_REGISTER(ScriptOption);
