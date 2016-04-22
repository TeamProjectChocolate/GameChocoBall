// DirectX.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "DirectX.h"
#include "MainScene.h"
#include "Effect.h"
#include "Camera.h"
#include "ImageManager.h"
#include "ObjectManager.h"
#include "InputManager.h"


#define MAX_LOADSTRING 100

// �O���[�o���ϐ�:
HINSTANCE hInst;								// ���݂̃C���^�[�t�F�C�X
TCHAR szTitle[MAX_LOADSTRING];					// �^�C�g�� �o�[�̃e�L�X�g
TCHAR szWindowClass[MAX_LOADSTRING];			// ���C�� �E�B���h�E �N���X��

HWND g_hWnd;
CGraphicsDevice g_graphicsDevice;
CMainScene MainScene;
CCamera g_camera;
void Initialize();
void Update();
void Draw();
void SharderDraw();


// ���̃R�[�h ���W���[���Ɋ܂܂��֐��̐錾��]�����܂�:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �����ɃR�[�h��}�����Ă��������B
	MSG msg;
	HACCEL hAccelTable;

	// �O���[�o������������������Ă��܂��B
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DIRECTX, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// �A�v���P�[�V�����̏����������s���܂�:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DIRECTX));

	Initialize();

	// ���C�� ���b�Z�[�W ���[�v:
	do
	{
		//���b�Z�[�W�����݂��邩����
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);		//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�ɕϊ�
			DispatchMessage(&msg);		//���b�Z�[�W���E�B���h�E�v���V�[�W���ɑ��o
		}
		else
		{
			Update();
			Draw();
			SINSTANCE(CObjectManager)->ExcuteDeleteObjects();
		}

	} while (msg.message != WM_QUIT);

	g_graphicsDevice.FreeDX();

	return (int) msg.wParam;
}



//
//  �֐�: MyRegisterClass()
//
//  �ړI: �E�B���h�E �N���X��o�^���܂��B
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DIRECTX));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_DIRECTX);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   �֐�: InitInstance(HINSTANCE, int)
//
//   �ړI: �C���X�^���X �n���h����ۑ����āA���C�� �E�B���h�E���쐬���܂��B
//
//   �R�����g:
//
//        ���̊֐��ŁA�O���[�o���ϐ��ŃC���X�^���X �n���h����ۑ����A
//        ���C�� �v���O���� �E�B���h�E���쐬����ѕ\�����܂��B
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // �O���[�o���ϐ��ɃC���X�^���X�������i�[���܂��B

	g_hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!g_hWnd)
	{
		return FALSE;
	}

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	return TRUE;
}

//
//  �֐�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �ړI:    ���C�� �E�B���h�E�̃��b�Z�[�W���������܂��B
//
//  WM_COMMAND	- �A�v���P�[�V���� ���j���[�̏���
//  WM_PAINT	- ���C�� �E�B���h�E�̕`��
//  WM_DESTROY	- ���~���b�Z�[�W��\�����Ė߂�
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �I�����ꂽ���j���[�̉��:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �`��R�[�h�������ɒǉ����Ă�������...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �o�[�W�������{�b�N�X�̃��b�Z�[�W �n���h���[�ł��B
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void Initialize()
{
	graphicsDevice().InitD3d(g_hWnd);
	g_camera.Initialize();
	CEffect::CreateInstance();		// �V���O���g���N���X:�G�t�F�N�g�t�@�C���Ǘ��N���X�̃C���X�^���X�𐶐�
	SINSTANCE(CEffect)->SetEffect(_T("Shader/Effect00.hlsl"));	// �g�p����shader�t�@�C�����w��
	CImageManager::CreateInstance();		// �V���O���g���N���X:�I�u�W�F�N�g�̃��f�����Ǘ��N���X�̃C���X�^���X�𐶐�
	CObjectManager::CreateInstance();		// �V���O���g���N���X:�I�u�W�F�N�g�Ǘ��N���X�̃C���X�^���X�𐶐�
	CInputManager::CreateInstance();		// �V���O���g���N���X:���̓C���^�t�F�[�X�Ǘ��N���X�̃C���X�^���X�𐶐�
	SINSTANCE(CInputManager)->InitManager();
	SINSTANCE(CInputManager)->DI_Init();
	SINSTANCE(CInputManager)->CreateKeyBoard(g_hWnd);
	MainScene.Initialize();
}

void Update()
{
	SINSTANCE(CInputManager)->Update();
	g_camera.Update();
	MainScene.Update();		//�V�[���X�V
}

void SetupRenderState()
{
	// ���C�g�ݒ�(���F�A���ʔ���)
	D3DXVECTOR3 vDirec(0, -1, -1);		// ���C�g����
	D3DLIGHT9 light;					// ���C�g�\����
	ZeroMemory(&light, sizeof(D3DLIGHT9));		// ������
	light.Type = D3DLIGHT_DIRECTIONAL;		// ���s����
	// �g�U��
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	// ���ʌ�
	light.Specular.r = 1.0f;
	light.Specular.g = 1.0f;
	light.Specular.b = 1.0f;

	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vDirec);		// ���C�g�����̐ݒ�
	(*graphicsDevice()).SetLight(0, &light);			// ���C�g�ݒ�
	(*graphicsDevice()).LightEnable(0, TRUE);		// ���C�g���Ă�
	// Z�o�b�t�@�[�A���C�g�̐ݒ�
	(*graphicsDevice()).SetRenderState(D3DRS_LIGHTING, TRUE);	// ���C�g��L��
	(*graphicsDevice()).SetRenderState(D3DRS_AMBIENT, 0x00aaaaaa);	// ������ݒ�
	(*graphicsDevice()).SetRenderState(D3DRS_SPECULARENABLE, TRUE);	// ���ʔ��˗L��
	(*graphicsDevice()).SetRenderState(D3DRS_ZENABLE, TRUE);			// Z�o�b�t�@�[��L��

	g_camera.SetCamera();	// �J�����Z�b�g
}

void SharderDraw(){
	SINSTANCE(CEffect)->GetEffect()->SetTechnique("BasicTec");	// �e�N�j�b�N�̑I��
	UINT numPass;
	SINSTANCE(CEffect)->GetEffect()->Begin(&numPass/*�e�N�j�b�N���ɒ�`����Ă���p�X�̐����ԋp�����*/, 0);
	SINSTANCE(CEffect)->GetEffect()->BeginPass(0);	//�p�X�̔ԍ����w�肵�Ăǂ̃p�X���g�p���邩�w��

	MainScene.Draw();		// ���C���`��

	//�����ŌŒ�`��Ɠ����悤�ɁA���[�J�����W�ɐݒ肳�ꂽ���_�Q���f�o�C�X�ɓn���B�ʏ�Ɠ������@�B
	//	���b�V�����������A�}�e���A����e�N�X�`����ݒ�
	//DrawSubset()���Ăяo���ĕ`��

	SINSTANCE(CEffect)->GetEffect()->EndPass();
	SINSTANCE(CEffect)->GetEffect()->End();
}

void Draw()
{
	(*graphicsDevice()).Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	if (SUCCEEDED((*graphicsDevice()).BeginScene()))
	{
		SetupRenderState();
		SharderDraw();
		(*graphicsDevice()).EndScene();
	}
	(*graphicsDevice()).Present(NULL, NULL, NULL, NULL);
}