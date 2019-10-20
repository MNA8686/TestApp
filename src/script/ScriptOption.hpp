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
	SpriteRendererContainer m_spriteRenderer;
};

EQ_SCRIPT_REGISTER(ScriptOption);
