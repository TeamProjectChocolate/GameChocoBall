#include "MainScene.h"
#include "ObjectManager.h"
#include "GameCamera.h"
#include "Audio.h"
#include "TestObject2D.h"

CMainScene::CMainScene(){
}

CMainScene::~CMainScene(){
}

void CMainScene::Initialize(){
	this->CreateSprite();
	SINSTANCE(CObjectManager)->GenerationObject<CGameCamera>(_T("3DCamera"), 0);
	SINSTANCE(CObjectManager)->GenerationObject<CPlayer>(_T("aaa"), 1);
	SINSTANCE(CObjectManager)->AddObject(&m_Player, _T("bbb"));
	SINSTANCE(CObjectManager)->GenerationObject<CTestObject2D>(_T("2DTest"), 3);
	char objectName[] = {
		"aaa"
	};
	SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(objectName)->SetFileName("image/Kanshou.x");
	SINSTANCE(CObjectManager)->Intialize(m_pSprite);
	SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(objectName)->Initialize(-0.25f, 1.5f);
	SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("bbb"))->Initialize(-0.25f, 1.25f);
	m_pAudio = new CAudio;
	m_pAudio->Initialize("Audio/Audio.xgs", "Audio/Audio.xwb", "Audio/Audio.xsb");	// �e�퉹�y�t�@�C���Ǎ�
	m_pAudio->PlayCue("emiya");	// ���y�Đ�
}

void CMainScene::Update(){
	m_pAudio->Run();		// ���y�X�V
	SINSTANCE(CObjectManager)->Update();
}

void CMainScene::Draw(){
	SINSTANCE(CObjectManager)->Draw();
}

HRESULT CMainScene::CreateSprite(){
	if (FAILED(D3DXCreateSprite(graphicsDevice(), &m_pSprite)))
	{
		MessageBox(0, TEXT("�X�v���C�g�쐬���s"), NULL, MB_OK);
		return E_FAIL;//���s�ԋp
	}
	return S_OK;
}
