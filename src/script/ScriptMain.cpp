#include "ScriptMain.hpp"

bool ScriptMain::OnCreate()
{
	Logger::OutputDebug("ScriptMain::OnCreate");

	auto ownerID = GetOwner();
	auto owner = Object::GetObjectByHandler(ownerID);

	{
		// 背景を作る
		if (auto spriteRenderer = GetRenderer()->CreateRenderObject<SpriteRenderer>())
		{
			auto& sprite = owner->GetAsset()->m_sprite[0];

			spriteRenderer->SetSprite(sprite).
				SetLayer(0).
				SetBlendMode(BlendMode::Blend).
				SetPos({ 448 / 2, 480 / 2 }).
				SetScale(1.5f, 1.5f);

			owner->SetVisible(true);
			owner->AddRenderObject(spriteRenderer);
		}

		// テキストを作る
		if (auto textRenderer = GetRenderer()->CreateRenderObject<TextRenderer>())
		{
			const String text = u8"Equisetum2 TestApp\nTキーを押すとテスト画面へ入れます。";

			if (auto font = Singleton<AssetManager>::GetInstance()->Load<FontManager>("mgenplus-1pp-medium.ttf?20"))
			{
				auto bf = font->MakeBitmapFont(text, Color{255,255,255,255});
				textRenderer->SetBitmapFont(bf);

				textRenderer->SetText(text);
				textRenderer->SetBlendMode(BlendMode::Blend);
				textRenderer->SetPivot({ 0.5f, 0.5f });
				textRenderer->SetTextHAlignment(TextHAlignment::Center);

				int m_x = 448 / 2;
				int m_y = 80;

				textRenderer->SetPos({ m_x, m_y });
				textRenderer->SetLayer(10);

				// レンダーキューに追加
				owner->AddRenderObject(textRenderer);
			}
		}

		// 自機を作る
		auto objHandler = Object::Create("player");
		if(auto* obj = Object::GetObjectByHandler(objHandler))
		{
			obj->SetParentHandler(owner->GetNodeHandler());
		}

		// BGMを再生開始
		owner->GetAsset()->m_bgm[0]->SetVolume(0.5f);
		owner->GetAsset()->m_bgm[0]->Play(true);
	}

	return true;
}

bool ScriptMain::FixedUpdate()
{
	return true;
}
