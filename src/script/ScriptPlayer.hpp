#pragma once

#include "Script.hpp"

class ScriptPlayer : public ScriptBase
{
public:
	ScriptPlayer() = default;
	~ScriptPlayer() = default;

	bool OnCreate(Object* owner);
	bool FixedUpdate(Object* owner);

	std::shared_ptr<SpriteRenderer> m_spriteRenderer;
};

EQ_SCRIPT_REGISTER(ScriptPlayer);
