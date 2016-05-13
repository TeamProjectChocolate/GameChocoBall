#include "Number.h"

void CNumber::Initialize(){
	C2DImage::Initialize();
	m_transform.position = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	SetRotation(0.0f);
	m_transform.scale = D3DXVECTOR3(800, 800, 1);
	SetAlpha(0.5f);
	SetAlive(true);
	C2DImage::SetImage();
};

void CNumber::Update(){

};

void CNumber::Draw(){
	string value = to_string(m_value);

	if (m_pTexture != NULL){
		for (int idx = value.length() - 1, offset = 0; idx >= 0; idx--, offset++){
			short width = imgInfo.Width / NUMBER_NUM;
			char now = value[idx];
			int num = atoi(&now);
			RECT rect = { num * width, 0, (num + 1) * width, imgInfo.Height };
			D3DXVECTOR2 m_texCenter(float(width - width / 2), float(rect.bottom - rect.bottom / 2));
			D3DXVECTOR2 position(m_transform.position.x - (width * offset), m_transform.position.y);
			memcpy(&this->m_rect, &rect, sizeof(RECT));					//•`‰æ—ÌˆæƒZƒbƒg
			C2DImage::SetupMatrices(m_rect,position,m_texCenter);
			C2DImage::Draw();
			C2DImage::Draw();
		}
	}
}
