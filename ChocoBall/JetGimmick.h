#pragma once
#include "GameObject.h"
#include "ParticleEmitter.h"

class CJetGimmick :
	public CGameObject
{
public:
	CJetGimmick();
	~CJetGimmick();
	void Initialize()override;
	void Update()override;
	void Draw()override;
};

