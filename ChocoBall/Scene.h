#pragma once

class CAudio;

class CScene
{
public:
	CScene();
	~CScene();
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
protected:
	CAudio* m_pAudio;
};

