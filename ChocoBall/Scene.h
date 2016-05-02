#pragma once

class CAudio;

class CScene
{
public:
	CScene(){ m_ManagerNewFlg = false; };
	~CScene(){};
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	inline void ActiveManagerNewFlg(){
		m_ManagerNewFlg = true;
	}
protected:
	CAudio* m_pAudio;
private:
	bool m_ManagerNewFlg;	// ObjectManager�N���X��new���ꂽ���̂����肷��ϐ�
};

