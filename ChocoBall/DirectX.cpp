// DirectX.cpp : アプリケーションのエントリ ポイントを定義します。
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

// グローバル変数:
HINSTANCE hInst;								// 現在のインターフェイス
TCHAR szTitle[MAX_LOADSTRING];					// タイトル バーのテキスト
TCHAR szWindowClass[MAX_LOADSTRING];			// メイン ウィンドウ クラス名

HWND g_hWnd;
CGraphicsDevice g_graphicsDevice;
CMainScene MainScene;
CCamera g_camera;
void Initialize();
void Update();
void Draw();
void SharderDraw();


// このコード モジュールに含まれる関数の宣言を転送します:
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

 	// TODO: ここにコードを挿入してください。
	MSG msg;
	HACCEL hAccelTable;

	// グローバル文字列を初期化しています。
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DIRECTX, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// アプリケーションの初期化を実行します:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DIRECTX));

	Initialize();

	// メイン メッセージ ループ:
	do
	{
		//メッセージが存在するか検証
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);		//仮想キーメッセージを文字メッセージに変換
			DispatchMessage(&msg);		//メッセージをウィンドウプロシージャに送出
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
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
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
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します。
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // グローバル変数にインスタンス処理を格納します。

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
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND	- アプリケーション メニューの処理
//  WM_PAINT	- メイン ウィンドウの描画
//  WM_DESTROY	- 中止メッセージを表示して戻る
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
		// 選択されたメニューの解析:
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
		// TODO: 描画コードをここに追加してください...
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

// バージョン情報ボックスのメッセージ ハンドラーです。
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
	CEffect::CreateInstance();		// シングルトンクラス:エフェクトファイル管理クラスのインスタンスを生成
	SINSTANCE(CEffect)->SetEffect(_T("Shader/Effect00.hlsl"));	// 使用するshaderファイルを指定
	CImageManager::CreateInstance();		// シングルトンクラス:オブジェクトのモデル情報管理クラスのインスタンスを生成
	CObjectManager::CreateInstance();		// シングルトンクラス:オブジェクト管理クラスのインスタンスを生成
	CInputManager::CreateInstance();		// シングルトンクラス:入力インタフェース管理クラスのインスタンスを生成
	SINSTANCE(CInputManager)->InitManager();
	SINSTANCE(CInputManager)->DI_Init();
	SINSTANCE(CInputManager)->CreateKeyBoard(g_hWnd);
	MainScene.Initialize();
}

void Update()
{
	SINSTANCE(CInputManager)->Update();
	g_camera.Update();
	MainScene.Update();		//シーン更新
}

void SetupRenderState()
{
	// ライト設定(白色、鏡面反射)
	D3DXVECTOR3 vDirec(0, -1, -1);		// ライト方向
	D3DLIGHT9 light;					// ライト構造体
	ZeroMemory(&light, sizeof(D3DLIGHT9));		// 初期化
	light.Type = D3DLIGHT_DIRECTIONAL;		// 平行光源
	// 拡散光
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	// 鏡面光
	light.Specular.r = 1.0f;
	light.Specular.g = 1.0f;
	light.Specular.b = 1.0f;

	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vDirec);		// ライト方向の設定
	(*graphicsDevice()).SetLight(0, &light);			// ライト設定
	(*graphicsDevice()).LightEnable(0, TRUE);		// ライト当てる
	// Zバッファー、ライトの設定
	(*graphicsDevice()).SetRenderState(D3DRS_LIGHTING, TRUE);	// ライトを有効
	(*graphicsDevice()).SetRenderState(D3DRS_AMBIENT, 0x00aaaaaa);	// 環境光を設定
	(*graphicsDevice()).SetRenderState(D3DRS_SPECULARENABLE, TRUE);	// 鏡面反射有効
	(*graphicsDevice()).SetRenderState(D3DRS_ZENABLE, TRUE);			// Zバッファーを有効

	g_camera.SetCamera();	// カメラセット
}

void SharderDraw(){
	SINSTANCE(CEffect)->GetEffect()->SetTechnique("BasicTec");	// テクニックの選択
	UINT numPass;
	SINSTANCE(CEffect)->GetEffect()->Begin(&numPass/*テクニック内に定義されているパスの数が返却される*/, 0);
	SINSTANCE(CEffect)->GetEffect()->BeginPass(0);	//パスの番号を指定してどのパスを使用するか指定

	MainScene.Draw();		// メイン描画

	//ここで固定描画と同じように、ローカル座標に設定された頂点群をデバイスに渡す。通常と同じ方法。
	//	メッシュも同じく、マテリアルやテクスチャを設定
	//DrawSubset()を呼び出して描画

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