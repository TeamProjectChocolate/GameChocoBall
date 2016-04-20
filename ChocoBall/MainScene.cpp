#include "MainScene.h"
#include "ObjectManager.h"
#include "Audio.h"

CMainScene::CMainScene(){
}

CMainScene::~CMainScene(){
}

void CMainScene::Initialize(){
	this->CreateSprite();
	SINSTANCE(CObjectManager)->GenerationObject<CPlayer>(_T("aaa"), 0);
	CPlayer* Player = new CPlayer;
	SINSTANCE(CObjectManager)->AddObject(Player, _T("bbb"));
	//for (short i = 0; i < 5; i++){
	//	LPCSTR name;
	//	name = CLASS_NAME(CPlayer);
	//	this->m_pPlayer[i] = new CPlayer;
		//this->m_pPlayer[i]->Initialize(((float)i - 5) * 2, 1.0f);
	//	SINSTANCE(CObjectManager)->AddObject(m_pPlayer[i],name,0);
	//}
	SINSTANCE(CObjectManager)->Intialize(m_pSprite);
	//SINSTANCE(CObjectManager)->GetGameObject<CPlayer>(_T("aaa"))->Initialize(0.0f,5.0f);
	char objectName[] = {
		"aaa"
	};
	SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(objectName)->Initialize(0.0f, 5.0f);
	SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("bbb"))->Initialize(0.0f, -5.0f);
	SINSTANCE(CObjectManager)->DeleteGameObject(objectName);

	m_pAudio = new CAudio;
	m_pAudio->Initialize("Audio/Audio.xgs", "Audio/Audio.xwb", "Audio/Audio.xsb");	// �e�퉹�y�t�@�C���Ǎ�
	m_pAudio->PlayCue("22-emiya[1]");	// ���y�Đ�
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
