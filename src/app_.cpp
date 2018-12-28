#include "Equisetum2.h"
#include "Object.hpp"
#include "Node.hpp"
#include "Application.hpp"

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>


using namespace Equisetum2;

class TestApp : public Application
{
public:
	TestApp() = default;
	~TestApp() = default;

	template<class Archive>
	void serialize(Archive & archive)
	{
//		archive(CEREAL_NVP(m_spriteRenderer));
#if 1
//		archive(CEREAL_NVP(m_spriteRenderer2));
//		archive(CEREAL_NVP(m_vSprite));
#endif
//		archive(CEREAL_NVP(x));
//		archive(CEREAL_NVP(angle));

		// test
		archive(CEREAL_NVP(m_rootObject));
	}

private:

	virtual bool OnInit(void);
	virtual void OnQuit(void);
	virtual bool OnUpdate(void);
	virtual bool OnDraw(void);

//	std::shared_ptr<SpriteRenderer> m_spriteRenderer;
//	std::shared_ptr<SpriteRenderer> m_spriteRenderer2;
//	std::vector<std::shared_ptr<SpriteRenderer>> m_vSprite;
//	int x = 0;
//	float angle = 0;


	// test
	std::shared_ptr<Object> m_rootObject;
//	std::shared_ptr<Node<Object>> m_rootNode;
};

static bool g_save = true;
//static bool g_save = false;

extern const std::vector<stScriptTbl>& GetScriptTbl();
bool TestApp::OnInit(void)
{
	auto renderer = GetRenderer();

	// スクリプト初期化
	Script::SetScriptTbl(GetScriptTbl());
	Script::m_renderer = renderer;

#if 1
	// ルートオブジェクト作成
	m_rootObject = Object::Create("main");
	if (!m_rootObject)
	{
		return false;
	}
#endif

	return true;
}

void TestApp::OnQuit(void)
{
}

#include <iostream>
#include <fstream>

bool TestApp::OnUpdate(void)
{
	auto nowFps = NowFps();
	Logger::OutputInfo("fps : %d", nowFps);

	if (KB::KeyL.IsDown())
	{
		Node<Object>::DestroyThemAll();

		std::ifstream ifs(Path::GetFullPath("out.json").c_str());
		if (ifs)
		{
			cereal::JSONInputArchive i_archive(ifs);
			Singleton<NodePool<Object>>::GetInstance()->serialize(i_archive);
			i_archive(*this);

			Object::m_dirty = true;
		}
	}
	else if (KB::KeyS.IsDown())
	{
		std::ofstream ofs(Path::GetFullPath("out.json").c_str());
		if (ofs)
		{
			cereal::JSONOutputArchive o_archive(ofs);
			Singleton<NodePool<Object>>::GetInstance()->serialize(o_archive);
			o_archive(*this);
		}
	}

	static bool pause = false;

	if (KB::KeyEscape.IsDown())
	{
		Quit();
	}

	// ポーズ切り替え
	if (KB::KeyP.IsDown())
	{
		pause = !pause;
	}

	// ポーズ機能
	if (pause && !KB::KeyO.IsDown())
	{
		System::Sleep(1);
		return true;
	}

	auto renderer = GetRenderer();

	Object::Update();

	return true;
}

bool TestApp::OnDraw(void)
{
	auto& renderer = GetRenderer();

	renderer->Clear({ 0, 128, 255, 0 });

	if (m_rootObject)
	{
		m_rootObject->OnDraw(renderer);
	}

	renderer->Render();

	return true;
}

std::shared_ptr<Application> GetApplication(void)
{
	return std::make_shared<TestApp>();
}
