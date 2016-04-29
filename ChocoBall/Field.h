#pragma once
#include "C3DImage.h"
class CField :
	public C3DImage
{
public:
	CField();
	~CField();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void SetUpTechnique()override{
		m_pEffect->SetTechnique("ShadowTec");
	}
};

