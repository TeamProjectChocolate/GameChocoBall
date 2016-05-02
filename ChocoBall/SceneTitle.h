#pragma once
#include "Scene.h"
#include "DirectInput.h"
#include "TitleBack.h"

class CSceneTitle:
	public CScene
{
public:
	CSceneTitle();
	~CSceneTitle();
	void Initialize()override;
	void Update()override;
	void Draw()override;
private:
	CDirectInput* m_Input;
	CTitleBack m_Back;
};
