#pragma once
#include "C3DImage.h"
#include "Light.h"


class Skybox : public C3DImage{
public:
	Skybox();
	~Skybox();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void SetUpTechnique()override
	{
		m_pEffect->SetTechnique("NotNormalMapNonAnimationBloomTec");
	}
private:

	CLight light;
};