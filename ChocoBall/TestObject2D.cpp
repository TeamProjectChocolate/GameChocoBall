#include "stdafx.h"
#include "TestObject2D.h"
#include "InputManager.h"


CTestObject2D::CTestObject2D()
{
	strcpy(m_pFileName, "image/test.png");
}


CTestObject2D::~CTestObject2D()
{
}

void CTestObject2D::Initialize(){
	C2DImage::Initialize();
	m_Input = SINSTANCE(CInputManager)->GetInput();
	m_transform.position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_transform.angle = D3DXVECTOR3(1, 1, 1);
	m_transform.scale = D3DXVECTOR3(96, 80, 1);
	SetAlive(true);
	C2DImage::SetImage();
}

void CTestObject2D::Update(){ 
	if (m_Input->IsPressUp()){
		m_transform.position.y--/* -= 0.1f*/;
	}
	if (m_Input->IsPressDown()){
		m_transform.position.y++/* += 0.1f*/;
	}
	if (m_Input->IsPressLeft()){
		m_transform.position.x--/* -= 0.1f*/;
	}
	if (m_Input->IsPressRight()){
		m_transform.position.x++/* += 0.1f*/;
	}
}

void CTestObject2D::Draw(){
	C2DImage::SetupMatrices();
	C2DImage::Draw();

}
