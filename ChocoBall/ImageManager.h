#pragma once
#include "stdafx.h"
#include "Infomation.h"

class CImageManager
{
	SINGLETON_DECL(CImageManager)
public:
	void Add2D(LPCSTR, LPDIRECT3DTEXTURE9, RECT);
	void Add3D(LPCSTR, D3DMATERIAL9*,LPDIRECT3DTEXTURE9*,DWORD,LPD3DXMESH);
	IMAGE2D* Find2DImage(LPCSTR);
	IMAGE3D* Find3DImage(LPCSTR);
private:
	vector<IMAGE3D*> m_ModelList;
	vector<IMAGE2D*> m_ImageList;

	//vectorに登録された要素をすべて削除する関数
	//※デストラクタにて呼び出される
	void DeleteAll();
};

