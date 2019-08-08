
#include "ScriptBullet.hpp"

bool ScriptBullet::m_shotSound = false;

ScriptBullet::ScriptBullet()
{

}

ScriptBullet::~ScriptBullet()
{

}

std::shared_ptr<SpriteRenderer> ScriptBullet::RegisterSpriteRenderer()
{
	auto renderer = Script::GetRenderer();
	auto spriteRenderer = renderer->CreateRenderObject<SpriteRenderer>();

	auto ownerID = GetOwner();
	auto owner = Object::GetObjectByID(ownerID);
	owner.AddRenderObject(spriteRenderer);

	return spriteRenderer;
}

std::shared_ptr<LineRenderer> ScriptBullet::RegisterLineRenderer()
{
	auto renderer = Script::GetRenderer();
	auto lineRenderer = renderer->CreateRenderObject<LineRenderer>();

	auto ownerID = GetOwner();
	auto owner = Object::GetObjectByID(ownerID);
	owner.AddRenderObject(lineRenderer);

	return lineRenderer;
}

std::shared_ptr<RectRenderer> ScriptBullet::RegisterRectRenderer()
{
	auto renderer = Script::GetRenderer();
	auto castRenderer = renderer->CreateRenderObject<RectRenderer>();

	auto ownerID = GetOwner();
	auto owner = Object::GetObjectByID(ownerID);
	owner.AddRenderObject(castRenderer);

	return castRenderer;
}

std::shared_ptr<CircleRenderer> ScriptBullet::RegisterCircleRenderer()
{
	auto renderer = Script::GetRenderer();
	auto circleRenderer = renderer->CreateRenderObject<CircleRenderer>();

	auto ownerID = GetOwner();
	auto owner = Object::GetObjectByID(ownerID);
	owner.AddRenderObject(circleRenderer);

	return circleRenderer;
}

std::shared_ptr<TextRenderer> ScriptBullet::RegisterTextRenderer()
{
	auto renderer = Script::GetRenderer();
	auto textRenderer = renderer->CreateRenderObject<TextRenderer>();

	auto ownerID = GetOwner();
	auto owner = Object::GetObjectByID(ownerID);
	owner.AddRenderObject(textRenderer);

	return textRenderer;
}

bool ScriptBullet::OnCreate()
{
	Logger::OutputDebug("ScriptBullet::OnCreate");

	if (auto spriteRenderer = RegisterSpriteRenderer())
	{
		auto ownerID = GetOwner();
		auto owner = Object::GetObjectByID(ownerID);
		{
			auto asset = owner.GetAsset();
			int kind = rand() % 2;
			m_sprite = asset.m_sprite[kind];
			spriteRenderer->SetSprite(m_sprite).SetLayer(1 - kind).SetBlendMode(BlendMode::Blend);

			{
				auto pos = owner.GetPos();
				spriteRenderer->SetPos({ pos.x.GetInt(), pos.y.GetInt() });// .Calculation();
			}

			m_spriteRenderer = spriteRenderer;
			m_spriteRenderer->SetLayer(10);

			owner.SetVisible(false);
		}
	}

	if (auto lineRenderer = RegisterLineRenderer())
	{
		lineRenderer->SetLayer(10);
		m_lineRenderer = lineRenderer;
	}

	if (auto rectRenderer = RegisterRectRenderer())
	{
		rectRenderer->SetLayer(10);
		m_rectRenderer = rectRenderer;
	}

	if (auto circleRenderer = RegisterCircleRenderer())
	{
		circleRenderer->SetLayer(10);
		m_circleRenderer = circleRenderer;
	}

	if (auto textRenderer = RegisterTextRenderer())
	{
//		auto bitmap = Singleton<AssetManager>::GetInstance()->Load<Sprite>("system_font");
//		auto font = BitmapFont::CreateFromSprite(bitmap, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
//		auto font = Singleton<AssetManager>::GetInstance()->Load<BitmapFont>("system_font");

//		if (auto stream = FileStream::CreateFromPath(Path::GetFullPath("font/mgenplus-1pp-medium.ttf")))
//		if (auto stream = FileStream::CreateFromPath(Path::GetFullPath("font/mgenplus-1m-regular.ttf")))
		if (auto stream = Singleton<AssetManager>::GetInstance()->GetStreamByID("font/mgenplus-1pp-medium.ttf"))
		{
			if (auto font = FontManager::CreateFromStream(stream, 16))
			{
				//				font->MakeBitmapFont(u8"Hello World!国士無双九蓮宝燈", Color{255,255,255,255});
				auto bf = font->MakeBitmapFont(u8" 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz寿限無、寿限無\n五劫の擦り切れ\n海砂利水魚の\n水行末 雲来末 風来末\n食う寝る処に住む処\n藪ら柑子の藪柑子\nパイポ　パイポ　パイポのシューリンガン\nシューリンガンのグーリンダイ\nグーリンダイのポンポコピーのポンポコナーの\n長久命の長助", Color{ 255, 255, 255, 255 }, {512, 1024});
//				auto bf = font->MakeBitmapFont(u8"五長久命の長助", Color{ 255, 0, 0, 255 });
				textRenderer->SetBitmapFont(bf);
			}

		}

//		textRenderer->SetBitmapFont(font);
//		textRenderer->SetText("AB;C#$%@DEFG\nHIJK\n\nLMN\r\nOPQRSTUVWXYZ\nBAA");
		textRenderer->SetText(u8"寿限無、寿限無i\n五劫の擦り切れ\n海砂利水魚の\n水行末 雲来末 風来末\n食う寝る処に住む処\n藪ら柑子の藪柑子\nパイポ　パイポ　パイポのシューリンガン\nシューリンガンのグーリンダイ\nグーリンダイのポンポコピーのポンポコナーの\n長久命の長助\nWindows");
//		textRenderer->SetText("ABCDEFG\nHI JK\n\nLMN\r\nOPQRSTUVWXYZ\nBAA\n838861");
		textRenderer->SetBlendMode(BlendMode::Blend);
//		textRenderer->SetPivot({ 0.5f, 0.5f });
		textRenderer->SetPivot({ 0.f, 0.5f });

//		int m_x = 448 / 2;
		int m_x = 16;
		int m_y = 240;
		
		textRenderer->SetPos({ m_x, m_y });
		textRenderer->SetLayer(10);
		m_textRenderer = textRenderer;
	}

	m_shotSound = true;

	return true;
}

void ScriptBullet::SetBullet(FixedDec x, FixedDec y, int32_t angle, FixedDec speed)
{
	m_angle = rand() % 360;
	m_speed = 500 + (rand() % 400);

	auto ownerID = GetOwner();
	auto owner = Object::GetObjectByID(ownerID);

	{
		owner.SetPos({ rand() % 640, rand() % 480 });
		owner.SetVisible(true);
		m_spriteRenderer->SetVisible(true);
	}
}

bool ScriptBullet::FixedUpdate()
{
#if 0
	if (m_shotSound)
	{
		if (auto owner = m_ownerObject.lock())
		{
//			owner->GetAsset().m_se[0]->Play(false);
		}

		m_shotSound = false;
	}
#endif

	auto ownerID = GetOwner();
	auto owner = Object::GetObjectByID(ownerID);

	{
		if (owner.IsVisible())
		{
			static int visiCount = 0;

			if (KB::KeyZ.IsDown())
			{
				m_textRenderer->SetText("");
			}
			if (KB::KeyX.IsDown())
			{
				m_textRenderer->SetText("0123");
			}
			if (KB::KeyC.IsDown())
			{
				m_textRenderer->SetText("ABCDEFG\nHI JK\n\nLMN\r\nOPQRSTUVWXYZ\nBAA");
								m_textRenderer->SetFlipX(true);
								m_textRenderer->SetFlipY(true);
								m_textRenderer->SetColor(Color{ 255, 128, 128, 128 });
			}
			if (KB::KeyV.IsDown())
			{
//				m_textRenderer->SetColor(Color{ 255, 128, 128, 128 });
//				m_textRenderer->SetScale(2.f, 2.f);
//				m_textRenderer->SetFlipX(true);
//				m_textRenderer->SetFlipY(true);

//				m_textRenderer->SetTextHAlignment(TextHAlignment::Left);

#if 1
				auto bitmap = Singleton<AssetManager>::GetInstance()->Load<Sprite>("system_font");
				auto font = BitmapFont::CreateFromSprite(bitmap, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
				m_textRenderer->SetBitmapFont(font);
#endif

//				m_textRenderer->SetVisible(false);

#if 0
				for (int i = 0; i < m_textRenderer->GetLetterSize(); i++)
				{
					auto renderer = m_textRenderer->GetLetter(i);
					renderer->SetVisible(false);
				}
				visiCount = 0;
#endif
			}
			if (KB::KeyB.IsDown())
			{
//				m_textRenderer->SetScale(1.f, 1.f);
//				m_textRenderer->SetFlipX(false);
//				m_textRenderer->SetFlipY(false);

#if 1
				auto bitmap = Singleton<AssetManager>::GetInstance()->Load<Sprite>("font_name_entry");
				auto font = BitmapFont::CreateFromSprite(bitmap, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
				m_textRenderer->SetBitmapFont(font);
#endif

//				m_textRenderer->SetTextHAlignment(TextHAlignment::Center);
				 
//				m_textRenderer->SetPivot({ 0.5f, 0.5f });

//				m_textRenderer->SetVisible(true);

#if 0
				if (auto renderer = m_textRenderer->GetLetter(visiCount))
				{
					renderer->SetVisible(true);
				}
				visiCount++;
#endif
			}

			m_spriteRenderer->SetVisible(true);

			if (1)
			{
				auto rag = m_angle * 3.14159265358979323846f / 180.f;
				auto pos = owner.GetPos();
				Point_t<FixedDec> new_pos;
				new_pos.x.SetRaw(pos.x.GetRaw() + m_speed * cos(rag));
				new_pos.y.SetRaw(pos.y.GetRaw() + m_speed * -sin(rag));
				owner.SetPos(new_pos);

				{
					auto pos = owner.GetPos();
					m_spriteRenderer->SetPos({ pos.x.GetInt(), pos.y.GetInt() });// .Calculation();

#if 0
					m_lineRenderer->Clear()
						.PushLine({ pos.x.GetInt(), pos.y.GetInt() }, { pos.x.GetInt() + 20, pos.y.GetInt() })
						.PushLine({ pos.x.GetInt() + 20, pos.y.GetInt() }, { pos.x.GetInt() + 20, pos.y.GetInt() + 20 })
						.PushLine({ pos.x.GetInt() + 20, pos.y.GetInt() + 20 }, { pos.x.GetInt(), pos.y.GetInt() + 20 })
						.PushLine({ pos.x.GetInt(), pos.y.GetInt() + 20 }, { pos.x.GetInt(), pos.y.GetInt() })
						.Calculation();
#endif

#if 0
					m_circleRenderer->SetCircle({ pos.x.GetInt(), pos.y.GetInt() }, 24, false)
						.Calculation();
#endif

#if 0
					m_rectRenderer->SetRect({ pos.x.GetInt(), pos.y.GetInt(), 40, 40 }, true)
						.SetColor(ColorDef::Red, ColorDef::Green, ColorDef::Blue, ColorDef::White)
						.Calculation();
#endif
				}


				if (new_pos.x.GetInt() < -20 || new_pos.x.GetInt() > 640 + 20 ||
					new_pos.y.GetInt() < -20 || new_pos.y.GetInt() > 480 + 20)
				{
					//			owner->Destroy();
					owner.SetVisible(false);
					m_spriteRenderer->SetVisible(false);
				}
			}
		}
	}

	return true;
}

