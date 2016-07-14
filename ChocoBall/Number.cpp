#include "stdafx.h"
#include "Number.h"

CNumber::CNumber(){
	strcpy(m_pFileName, "image\\Number.png");
	m_value = 0;
}
void CNumber::Initialize(){
	C2DImage::Initialize();
	m_transform.position = D3DXVECTOR3(230.0f, 50.0f, 0.0f);
	SetRotation(0.0f);
	m_transform.scale = D3DXVECTOR3(50, 80, 1);
	SetAlpha(1.0f);
	SetAlive(true);
	m_Split.x = 10.0f;
	m_Split.y = 1.0f;
	m_Now = D3DXVECTOR2(0.0f, 0.0f);
	C2DImage::SetImage();
	m_value = 0;
};
CNumber::~CNumber()
{
}
void CNumber::Update(){
	
}

void CNumber::Draw(){
	string value = to_string(m_value);
	if (m_pImage->pTex != NULL){

		m_Now.x = 0.0f;
		m_Now.y = 0.0f;
		for (int idx = value.length() - 1, offset = 0; idx >= 0; idx--, offset++){
			D3DXVECTOR3 OldPos = m_transform.position;	// 元のポジションを確保
			float width = m_pImage->UnRealSize.x / NUMBER_NUM;
			char now[] = {'0','\0'};
			now[0] = value[idx];	
			int num = atoi(now);
			m_Now.x = static_cast<float>(num);
			m_transform.position = D3DXVECTOR3(OldPos.x - (width * offset), OldPos.y, OldPos.z);	// 桁が上がればポジションをずらす
			C2DImage::SetupMatrices();
			C2DImage::Draw();
			m_transform.position = OldPos;	// 退避しておいたポジションを元に戻す
		}
	}
}
