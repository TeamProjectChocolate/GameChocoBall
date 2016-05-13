#pragma once
#include "Scene.h"
#include "ResultBack.h"
#include "ResultSelect.h"
#include "ResultCursor.h"

class CSceneResult : 
	public CScene
{
public:
	CSceneResult();
	~CSceneResult();
	void Initialize()override;
	void Update()override;
	void Draw()override;
private:
	CResultBack m_rBack;
	CResultSelect m_rSelect[2];
	CResultCursor m_rCursor;
};
