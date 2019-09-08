#pragma once

#include "Script.hpp"

class ScriptMain : public ScriptBase
{
public:
	ScriptMain() = default;
	~ScriptMain() = default;

	bool OnCreate(Object* owner);
	bool FixedUpdate(Object* owner);

private:
	SpriteRendererContainer m_spriteRenderer;
};

EQ_SCRIPT_REGISTER(ScriptMain);
