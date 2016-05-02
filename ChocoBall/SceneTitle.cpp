//#include "stdafx.h"
//#include "SceneTitle.h"
//#include "InputManager.h"
//
//
//CSceneTitle::CSceneTitle()
//{
//	strcpy(m_pFileName, "image/noborin.png");
//}
//
//
//CSceneTitle::~CSceneTitle()
//{
//}
//
//void CSceneTitle::Initialize(){
//	C2DImage::Initialize();
//	m_Input = SINSTANCE(CInputManager)->GetInput();
//	m_transform.position = D3DXVECTOR3(100.100f, 100.0f, 1.0f);
//	m_transform.angle = D3DXVECTOR3(1, 1, 1);
//	m_transform.scale = D3DXVECTOR3(100, 100, 100);
//	SetAlive(true);
//	C2DImage::SetImage();
//}
//
//void CSceneTitle::Update(){
//	if (m_Input->IsPressUp()){
//		
//	}
//	if (m_Input->IsPressDown()){
//		
//	}
//	if (m_Input->IsPressLeft()){
//		
//	}
//	if (m_Input->IsPressRight()){
//		
//	}
//}
//
//void CSceneTitle::Draw(){
//	C2DImage::SetupMatrices();
//	C2DImage::Draw();
//
//}