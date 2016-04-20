#include "Number.h"

void CNumber::Initialize(){
	m_texFileName = "image\\Number.png";
	m_angle = 0.0f;
	m_scale = D3DXVECTOR2(1.0f, 1.0f);
	m_backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	D3DXCreateTextureFromFileEx(graphicsDevice(), this->m_texFileName, 0, 0, 0, 0, D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0xff000000, &imgInfo, NULL, &this->m_pTexture);	//テクスチャ読込
};

void CNumber::Update(){

};

void CNumber::Draw(LPD3DXSPRITE sprite){
	string value = to_string(m_value);

	if (m_pTexture != NULL){
		for (int idx = value.length() - 1, offset = 0; idx >= 0; idx--, offset++){
			short width = imgInfo.Width / NUMBER_NUM;
			char now = value[idx];
			int num = atoi(&now);
			RECT rect = { num * width, 0, (num + 1) * width, imgInfo.Height };
			D3DXVECTOR2 m_texCenter(float(width - width / 2), float(rect.bottom - rect.bottom / 2));
			D3DXVECTOR2 position(m_position.x - (width * offset), m_position.y);
			memcpy(&this->m_rect, &rect, sizeof(RECT));					//描画領域セット
			D3DXMatrixIdentity(&this->m_transformMatrix);	//ワールド行列初期化
			D3DXMatrixTransformation2D(&this->m_transformMatrix, NULL, 0.0f, &this->m_scale, NULL, D3DXToRadian(this->m_angle), &D3DXVECTOR2(position.x, position.y));	//変換行列作成
			C2DImage::Draw(sprite);
		}
	}
}
