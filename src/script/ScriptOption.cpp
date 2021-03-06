﻿#include "ScriptOption.hpp"
#include "graphic/RenderObject.hpp"

EQ_SCRIPT_REGISTER(ScriptOption);

bool ScriptOption::OnCreate(Object* owner)
{
	owner->SetRelativeParent(true);
	owner->SetVisible(true);

	auto& sprite = owner->GetAsset()->m_sprite[0];

	m_spriteRenderer->SetSprite(sprite).
		SetLayer(2).
		SetBlendMode(BlendMode::Add).
		SetPos({ owner->GetPos().x.GetInt(), owner->GetPos().y.GetInt() });

	return true;
}

bool ScriptOption::FixedUpdate(Object* owner)
{
	m_spriteRenderer->SetPos({ owner->GetPos().x.GetInt(), owner->GetPos().y.GetInt() });

	return true;
}
