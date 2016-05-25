#pragma once
#include "stdafx.h"


class CAnimation
{
public:
	CAnimation(){
		m_pAnimController = nullptr;
		m_numAnimSet = 0;
		m_currentAnimationSetNo = 0;
		m_currentTrackNo = 0;
		m_numMaxTracks = 0;
		m_isBlending = false;
		m_isInterpolate = false;
		m_interpolateEndTime = 0.0f;
		m_interpolateTime = 0.0f;
	};
	~CAnimation();

	void Initialize(ID3DXAnimationController*);
	void Update(float);

	// �A�j���[�V�����Đ��֐�
	// ������: int�^ �Đ��������A�j���[�V�����̃C���f�b�N�X
	void PlayAnimation(int);

	// �A�j���[�V�����Đ��֐�
	// ������: int�^ �Đ��������A�j���[�V�����̃C���f�b�N�X
	//		�@ float�^ �⊮����
	void PlayAnimation(int, float);

#if 0
	// �A�j���[�V�����̃u�����f�B���O�Đ�
	// ������: int�^ �Đ��������A�j���[�V�����̃C���f�b�N�X
	void BlendAnimation(int);
#endif
	int GetNumAnimationSet() const{
		return m_numAnimSet;
	}
private:
	// �A�j���[�V�����p�����o�ϐ�
	ID3DXAnimationController* m_pAnimController;	// �A�j���[�V�����R���g���[��
	int m_numAnimSet;	// �A�j���[�V�����Z�b�g�̐�(���[�V�����̎�ސ�)
	unique_ptr<ID3DXAnimationSet*[]> m_AnimationSets;	// �A�j���[�V�����Z�b�g�̔z��
	unique_ptr<float[]> m_blendRateTable;		// �u�����f�B���O���[�g�̃e�[�u��
	int m_currentAnimationSetNo;			// ���ݍĐ����̃A�j���[�V�����Z�b�g�̔ԍ�
	int m_oldAnimationSetNo;				// 1�t���[���O�̃A�j���[�V�����Z�b�g�̔ԍ�
	int m_currentTrackNo;			// ���݂̃g���b�N�̔ԍ�
	int m_numMaxTracks;				// �A�j���[�V�����g���b�N�̍ő吔
	bool m_isBlending;				// �A�j���[�V�����u�����f�B���O�����ǂ����̃t���O
	bool m_isInterpolate;		    // ��Ԓ����̃t���O
	float m_interpolateEndTime;		// ��ԏI������
	float m_interpolateTime;		// ��Ԏ���
};

