#include "Equisetum2.h"
#include "Object.hpp"
#include "Node.hpp"
#include "Application.hpp"

using namespace Equisetum2;

class TestApp : public Application
{
public:
	TestApp() = default;
	~TestApp() = default;

	friend Singleton<TestApp>;	// �V���O���g������C���X�^���X���쐬���Ă��炦��悤�ɂ���

private:

	virtual bool OnCreate(void);
	virtual bool OnInit(void);
	virtual void OnQuit(void);
	virtual bool OnUpdate(void);
	virtual bool OnDraw(void);

	virtual String GetOrganizationName(void);
	virtual String GetApplicationName(void);

	// test
	NodeHandler m_rootObject;
	std::shared_ptr<Texture> m_targetTexture;
	std::shared_ptr<Sprite> m_targetSprite;
	std::shared_ptr<RenderObject> m_targetRenderObject;
};

static bool g_save = true;

String TestApp::GetOrganizationName(void)
{
	return "Equinox";
}

String TestApp::GetApplicationName(void)
{
	return "TestApp";
}

void heap_test();

bool TestApp::OnCreate(void)
{

	heap_test();

	Window::SetTitle(u8"App Test Program");
	Window::SetStyle(WindowStyle::Sizeable);
	Window::SetMinimumSize(320, 240);
	Window::SetSize(1280, 720);
	Window::Centering();

	//Singleton<AssetManager>::GetInstance()->SetArchivePath("asset.eq2", "equinox");

	return true;
}

bool TestApp::OnInit(void)
{
	auto renderer = GetRenderer();

	// �X�N���v�g������
	ScriptBase::m_renderer = renderer;

	// ���[�g�I�u�W�F�N�g�쐬
	m_rootObject = Object::Create("main");
	if (m_rootObject.id < 0)
	{
		return false;
	}

	// �����_�����O�p�e�N�X�`�����쐬����
	Size windowsSize = Window::Size();
	m_targetTexture = Texture::CreateBlank(512, 512, Texture::AccessFlag::RenderTarget);
	if (m_targetTexture)
	{
		m_targetSprite = Sprite::CreateFromTexture(m_targetTexture);
		if (m_targetSprite)
		{
			std::vector<stSpriteAnimAtlas> v;
			stSpriteAnimAtlas anim;
			anim.m_pivot = { 0.5, 0.5 };
			anim.m_point = { 0, 0 };
			anim.m_srcSize = { 448, 480 };
			v.push_back(anim);

			m_targetSprite->SetAnimAtlas(v);

			m_targetRenderObject = renderer->CreateRenderObject<SpriteRenderer>();

			auto spriteRenderer = static_cast<SpriteRenderer*>(m_targetRenderObject.get());
			spriteRenderer->SetPos({ windowsSize.x / 2, windowsSize.y / 2 });
			float rate = std::min(windowsSize.x / 448.f, windowsSize.y / 480.f);
			spriteRenderer->SetScale( rate, rate );
			spriteRenderer->SetSprite(m_targetSprite);
		}
	}

	Node<Object>::Dump();
	
	return true;
}

void TestApp::OnQuit(void)
{
	m_targetRenderObject = nullptr;
	m_targetSprite = nullptr;
	m_targetTexture = nullptr;
	m_rootObject = {};
}

bool TestApp::OnUpdate(void)
{
	static bool pause = false;

	// �t���X�N���[���؂�ւ�
	if (KB::KeyF.IsDown())
	{
		static bool fullscreen = false;

		fullscreen = !fullscreen;
		Window::SetFullscreen(fullscreen);
	}

	auto renderer = GetRenderer();

	// �|�[�Y�؂�ւ�
	if (KB::KeyP.IsDown())
	{
		pause = !pause;
	}

	// �|�[�Y�@�\
	if (pause && !KB::KeyO.IsDown())
	{
		return true;
	}

	if (KB::KeyEscape.IsDown())
	{
		Quit();
	}

	Object::Update();

	return true;
}

bool TestApp::OnDraw(void)
{
	auto& renderer = GetRenderer();
		renderer->SetRenderTarget(m_targetTexture);

	// �Q�[���̐��E�������_�����O
	{
		renderer->SetRenderTarget(m_targetTexture);

		renderer->Clear({ 0, 128, 255, 0 });

		//if (m_rootObject)
		{
			auto* obj = Object::GetObjectByHandler(m_rootObject);
			obj->OnDraw(renderer);
		}

		renderer->Render();
	}

	// �Q�[����ʂ��X�g���b�`�\��
	{
		renderer->SetRenderTarget(nullptr);

		Size windowsSize = Window::Size();
		renderer->SetViewport(Rect{ 0,0,windowsSize.x, windowsSize.y });
		{
			auto spriteRenderer = static_cast<SpriteRenderer*>(m_targetRenderObject.get());
			spriteRenderer->SetPos({ windowsSize.x / 2, windowsSize.y / 2 });
			float rate = std::min(windowsSize.x / 448.f, windowsSize.y / 480.f);
			spriteRenderer->SetScale(rate, rate);
		}

		renderer->Clear({ 128, 128, 128, 0 });
		renderer->AddRenderQueue(m_targetRenderObject.get());
		renderer->Render();
	}
	
	return true;
}

extern Application* GetApplication(void)
{
	return Singleton<TestApp>::GetInstance();
}
