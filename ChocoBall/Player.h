#pragma once
#include "C3DImage.h"
#include "DirectInput.h"

class CPlayer : public C3DImage
{
public:
	CPlayer();
	~CPlayer();
	void Initialize()override;
	void Initialize(float,float);
	void Update()override;
	void Draw()override;
	D3DXVECTOR3 GetPos(){
		return m_transform.position;
	}
private:
	CDirectInput* m_pInput;
};

