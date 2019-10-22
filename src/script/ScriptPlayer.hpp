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
	SpriteRendererContainer m_spriteRenderer;
};

