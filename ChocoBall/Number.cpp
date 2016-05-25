#include "Number.h"

void CNumber::Initialize(){
	C2DImage::Initialize();
	m_transform.position = D3DXVECTOR3(150.0f, 50.0f, 0.0f);
	SetRotation(0.0f);
	m_transform.scale = D3DXVECTOR3(50, 80, 1);
	SetAlpha(1.0f);
	SetAlive(true);
	m_Split.x = 10;
	C2DImage::SetImage();
	m_value = 100;
};

void CNumber::Update(){

};

void CNumber::Draw(){
	string value = to_string(m_value);

	if (m_pImage->pTex != NULL){
		m_Now.x = 0;
		for (int idx = value.length() - 1, offset = 0; idx >= 0; idx--, offset++){
			D3DXVECTOR3 OldPos = m_transform.position;	// 元のポジションを確保

			float width = m_pImage->UnRealSize.x / NUMBER_NUM/* * (m_pImage->RealSize.x / m_pImage->UnRealSize.x)*/;
			char now = value[idx];
			int num = atoi(&now);
			m_Now.x = num;
			//RECT rect = { num * width, 0, (num + 1) * width, m_rect.bottom };
			//D3DXVECTOR2 m_texCenter(float(width - width / 2), float(rect.bottom - rect.bottom / 2));
			D3DXVECTOR3 position = D3DXVECTOR3(OldPos.x - (width * offset),OldPos.y,OldPos.z);
			m_transform.position = position;	// 桁が上がればポジションをずらす
			//memcpy(&this->m_rect, &rect, sizeof(RECT));					//描画領域セット
			C2DImage::SetupMatrices();
			C2DImage::Draw();
			m_transform.position = OldPos;	// 退避しておいたポジションを元に戻す
		}
	}
}
