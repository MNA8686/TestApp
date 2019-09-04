#include "ScriptOption.hpp"

bool ScriptOption::OnCreate(Object* owner)
{
	if (auto spriteRenderer = GetRenderer()->CreateRenderObject<SpriteRenderer>())
	{
		owner->SetRelativeParent(true);
		owner->SetVisible(true);

		auto& sprite = owner->GetAsset()->m_sprite[0];

		spriteRenderer->SetSprite(sprite).
			SetLayer(2).
			SetBlendMode(BlendMode::Add).
			SetPos({owner->GetPos().x.GetInt(), owner->GetPos().y.GetInt()});

		m_spriteRenderer = owner->AddRenderObject(spriteRenderer);
	}

	return true;
}

bool ScriptOption::FixedUpdate(Object* owner)
{
	if (auto renderObject = owner->GetRenderObject(m_spriteRenderer))
	{
		auto spriteRenderer = static_cast<SpriteRenderer*>(renderObject);

		spriteRenderer->SetPos({ owner->GetPos().x.GetInt(), owner->GetPos().y.GetInt() });
	}

	return true;
}
