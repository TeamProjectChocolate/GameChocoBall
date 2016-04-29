#pragma once
class CCamera
{
public:
	CCamera();
	~CCamera();
	void Initialize();
	void Update();
	void SetCamera(LPD3DXEFFECT);
	inline void SetPos(D3DXVECTOR3 pos){
		m_position = pos;
	}
	inline D3DXVECTOR3 GetPos(){
		return m_position;
	}
	inline void SetTarget(D3DXVECTOR3 target){
		m_target = target;
	}
	inline void SetUp(D3DXVECTOR3 up){
		m_up = up;
	}
	inline void SetViewAngle(float angle){
		m_ViewAngle = angle;
	}
	inline void SetAspect(float aspect){
		m_aspect = aspect;
	}
	inline void SetNear(float Near){
		m_Near = Near;
	}
	inline void SetFar(float Far){
		m_Far = Far;
	}
private:
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_target;
	D3DXVECTOR3 m_up;
	float m_ViewAngle;	// ��p
	float m_aspect;
	float m_Near;
	float m_Far;
	D3DXMATRIX m_View;	// �r���[�ϊ��s��
	D3DXMATRIX m_Proj;	// �ˉe�ϊ��s��

};

