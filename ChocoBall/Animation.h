#pragma once
#include "stdafx.h"


class CAnimation
{
public:
	CAnimation(){
		m_pAnimController = nullptr;
		m_numAnimSet = 0;
		m_currentAnimationSetNo = -1;
		m_oldAnimationSetNo = -1;
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

	// �A�j���[�V�����Đ����x��ݒ�
	void SetAnimSpeed(float speed);

	//�A�j���[�V�����̏I���^�C����ݒ肷��֐�
	//������:int�^ �A�j���[�V�����C���f�b�N�X
	//      :double�^ �A�j���[�V�����̏I���^�C��
	//��-1.0���w�肷��ƃf�t�H���g�̏I�����Ԃ��ݒ肳��܂�
	void SetAnimationEndtime(int animationIndex, double endTime){
		m_animationEndTime[animationIndex] = endTime;
	}
#if 0
	// �A�j���[�V�����̃u�����f�B���O�Đ�
	// ������: int�^ �Đ��������A�j���[�V�����̃C���f�b�N�X
	void BlendAnimation(int);
#endif
	int GetNumAnimationSet() const{
		return m_numAnimSet;
	}
	bool IsHasAnimationController() const
	{
		return m_pAnimController;
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
	unique_ptr<double[]> m_animationEndTime;	// �A�j���[�V�����̏I���^�C���B�f�t�H���g�l��-1�B�w�肵�Ȃ��ꍇ��ID3DXAnimationSet�̃A�j���[�V�����I���^�C�����D�悳���B
	float m_localAnimationTime;	// ���[�J���A�j���[�V�����^�C��
};

