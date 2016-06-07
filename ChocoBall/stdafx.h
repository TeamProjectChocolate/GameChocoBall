// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows �w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
// Windows �w�b�_�[ �t�@�C��:
#include <windows.h>

// C �����^�C�� �w�b�_�[ �t�@�C��
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>


// TODO: �v���O�����ɕK�v�Ȓǉ��w�b�_�[�������ŎQ�Ƃ��Ă��������B

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib, "Xinput.lib")

#include "d3d9.h"
#include "d3dx9.h"
#include "dinput.h"
#include<XInput.h>
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <memory>


#define SAFE_RELEASE(p)			{ if(p) { (p)->Release(); (p) = NULL; } }	//�C���X�^���X�����[�X
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p);   (p) = NULL; } }	//�C���X�^���X�z��폜
#define SAFE_DELETE(p)			{ if(p) { delete (p);     (p) = NULL; } }	//�C���X�^���X�폜

using namespace std;

#define SINGLETON_DECL(CLASS_NAME)				\
private:										\
	CLASS_NAME(){}								\
	~CLASS_NAME(){ DeleteAll(); SAFE_DELETE(m_instance); }				\
	static CLASS_NAME* m_instance;				\
public:											\
	static CLASS_NAME*	GetInstance()			\
	{											\
		return m_instance;						\
	}											\
	static CLASS_NAME*	CreateInstance()		\
	{											\
		if (m_instance == NULL){				\
			m_instance = new CLASS_NAME();			\
		}											\
		return m_instance;						\
}

const D3DXVECTOR3 CVec3Zero = { 0.0f, 0.0f, 0.0f };
const D3DXVECTOR3 CVec3Right = { 1.0f, 0.0f, 0.0f };
const D3DXVECTOR3 CVec3Left = { -1.0f, 0.0f, 0.0f };
const D3DXVECTOR3 CVec3Up = { 0.0f, 1.0f, 0.0f };
const D3DXVECTOR3 CVec3Down = { 0.0f, -1.0f, 0.0f };
const D3DXVECTOR3 CVec3Front = { 0.0f, 0.0f, 1.0f };
const D3DXVECTOR3 CVec3Back = { 0.0f, 0.0f, -1.0f };

const D3DXVECTOR3 CVec3AxisX = { 1.0f, 0.0f, 0.0f };
const D3DXVECTOR3 CVec3AxisY = { 0.0f, 1.0f, 0.0f };
const D3DXVECTOR3 CVec3AxisZ = { 0.0f, 0.0f, 1.0f };

#define fPI 3.14159265358979323846f

#define MOVE_SPEED  8.0f

const float g_cTurnSpeed D3DXToRadian(10.0f);

#define SINSTANCE(CLASS_NAME) CLASS_NAME::GetInstance()		// �V���O���g���I�u�W�F�N�g�̃C���X�^���X���擾����}�N���֐�(�������F�N���X��)

#define CLASS_NAME(p) typeid(p).name()		//�N���X���̕�������擾����}�N���֐�(�����F�N���X��)

#define DELTA_TIME 1.0f / 60.0f