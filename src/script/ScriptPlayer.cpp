﻿#include "ScriptPlayer.hpp"

EQ_SCRIPT_REGISTER(ScriptPlayer);

bool ScriptPlayer::OnCreate(Object* owner)
{
	owner->SetPos({ 448 / 2, 480 / 4 * 3 });
	owner->SetVisible(true);

	auto& sprite = owner->GetAsset()->m_sprite[0];

	m_spriteRenderer->SetSprite(sprite).
		SetLayer(2).
		SetBlendMode(BlendMode::Blend).
		SetPos({ owner->GetPos().x.GetInt(), owner->GetPos().y.GetInt() });

	int32_t x = -48;
	// オプションを作る
	for (int i = 0; i < 2; i++)
	{
		auto objHandler = owner->CreateChild("option");
		if (auto option = owner->GetObjectByHandler(objHandler))
		{
			option->SetLocalPos({ x, 32 });
			x *= -1;
		}
	}

	return true;
}

bool ScriptPlayer::FixedUpdate(Object* owner)
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

	return true;
}
