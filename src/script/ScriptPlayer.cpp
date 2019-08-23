﻿#include "ScriptPlayer.hpp"

bool ScriptPlayer::OnCreate()
{
	auto ownerID = GetOwner();
	auto owner = Object::GetObjectByHandler(ownerID);

	if (auto spriteRenderer = GetRenderer()->CreateRenderObject<SpriteRenderer>())
	{
		owner->SetPos({ 448 / 2, 480 / 4 * 3 });

		auto& sprite = owner->GetAsset()->m_sprite[0];

		spriteRenderer->SetSprite(sprite).
			SetLayer(2).
			SetBlendMode(BlendMode::Blend).
			SetPos({owner->GetPos().x.GetInt(), owner->GetPos().y.GetInt()});

		owner->SetVisible(true);
		owner->AddRenderObject(spriteRenderer);

		m_spriteRenderer = spriteRenderer;
	}

	return true;
}

bool ScriptPlayer::FixedUpdate()
{
	auto ownerID = GetOwner();
	auto owner = Object::GetObjectByHandler(ownerID);

	{
		auto joy = Joystick::CreateByIndex(0);

		Point_t<FixedDec> point = owner->GetPos();

		const FixedDec speed = 6;
		const int16_t threthold = 10000;
		if (KB::KeyLeft.IsPress() ||
			joy->HatLeft().IsPress() ||
			joy->Axis(0) < -threthold)
		{
			point.x -= speed;
		}
		if (KB::KeyRight.IsPress() ||
			joy->HatRight().IsPress() ||
			joy->Axis(0) > threthold)
		{
			point.x += speed;
		}
		if (KB::KeyUp.IsPress() ||
			joy->HatUp().IsPress() ||
			joy->Axis(1) < -threthold)
		{
			point.y -= speed;
		}
		if (KB::KeyDown.IsPress() ||
			joy->HatDown().IsPress() ||
			joy->Axis(1) > threthold)
		{
			point.y += speed;
		}

		if (point.x < FixedDec(32))
		{
			point.x = 32;
		}
		if (point.x > FixedDec(448 - 32))
		{
			point.x = 448 - 32;
		}
		if (point.y < FixedDec(32))
		{
			point.y = 32;
		}
		if (point.y > FixedDec(480 - 32))
		{
			point.y = 480 - 32;
		}

		owner->SetPos(point);

		m_spriteRenderer->SetPos({ point.x.GetInt(), point.y.GetInt() });
	}

	return true;
}
