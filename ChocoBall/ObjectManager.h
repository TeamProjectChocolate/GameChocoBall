#pragma once
#include "stdafx.h"
#include "GameObject.h"

#define MAX_PRIORTY 255


class CObjectManager
{
	SINGLETON_DECL(CObjectManager)
public:

	//指定したオブジェクトを自動生成する関数(優先度を指定したい場合)
	//引き数: LPCSTR型 インスタンスの名前 
	//		  short型 更新優先度(0が最小、数字が大きいほど優先度が低い)
	//返り値: T*型 生成したクラスのオブジェクトを返却
	//呼び出し例: SINSTANCE(CObjectManager)->GenerationObject<生成したいクラス名>(_T("インスタンスの名前"),0);
	//※オブジェクトの名前はインスタンスごとに被らないようにユニークなものをプログラマーが指定してください
	//※オブジェクトのインスタンスはCObjectManagerクラスの外部でdeleteしないこと
	//※必ずCObjectManagerクラスの削除関数(名前未定)を呼び出して行うこと
	template<class T>
	T* GenerationObject(LPCSTR ObjectName,short priorty){
		T* Object = new T;
		if (priorty > MAX_PRIORTY){
			priorty = MAX_PRIORTY;
		}
		this->Add(Object, ObjectName,priorty);
		return Object;
	}

	//指定したオブジェクトを自動生成する関数(優先度なし：自動的に優先度は最低になります)
	//引き数: LPCSTR型 インスタンスの名前
	//返り値: T*型 生成したクラスのオブジェクトを返却
	//呼び出し例: SINSTANCE(CObjectManager)->GenerationObject<生成したいクラス名>(_T("インスタンスの名前"));
	//※オブジェクトの名前はインスタンスごとに被らないようにユニークなものをプログラマーが指定してください
	//※オブジェクトのインスタンスはCObjectManagerクラスの外部でdeleteしないこと
	//※必ずCObjectManagerクラスの削除関数(名前未定)を呼び出して行うこと
	 template<class T>
	T* GenerationObject(LPCSTR ObjectName){
		T* Object = new T;
		short priorty = MAX_PRIORTY;
		this->Add(Object,ObjectName ,priorty);
		return Object;
	}

	//すでに生成されているオブジェクトをマネージャークラスに登録する関数(優先度を指定したい場合)
	//引き数: CGameObject*型 登録するGameObjectのポインタ
	//		　short型 更新優先度(0が最小、数字が大きいほど優先度が低い)
	//返り値: なし
	//呼び出し例: SINSTANCE(CObjectManager)->AddObject(追加したいインスタンスのポインタ,_T("インスタンスの名前"),0);
	//※オブジェクトの名前はインスタンスごとに被らないようにユニークなものをプログラマーが指定してください
	//※オブジェクトのインスタンスはCObjectManagerクラスの外部でdeleteしないこと
	//※必ずCObjectManagerクラスの削除関数(名前未定)を呼び出して行うこと
	void AddObject(CGameObject*,LPCSTR, short);

	//すでに生成されているオブジェクトをマネージャークラスに登録する関数(優先度なし：自動的に優先度は最低になります)
	//引き数: CGameObject*型 登録するGameObjectのポインタ
	//返り値: なし
	//呼び出し例: SINSTANCE(CObjectManager)->AddObject(追加したいインスタンスのポインタ,_T("インスタンスの名前"));
	//※インスタンスの名前は被らないようにユニークなものをプログラマーが指定してください
	//※オブジェクトのインスタンスはCObjectManagerクラスの外部でdeleteしないこと
	//※必ずCObjectManagerクラスの削除関数(名前未定)を呼び出して行うこと
	void AddObject(CGameObject*,LPCSTR);

	//Objectmanagerクラスに登録されているGameObjectのインスタンスを名前で検索する関数
	//引き数: LPCSTR型 インスタンスの名前
	//返り値: CGameObject*型 引き数の名前と一致したオブジェクトのポインタ(どれか一つ)
	//呼び出し例: SINSTANCE(CObjectManager)->FindGameObject<検索したいクラス名>(_T("インスタンスの名前"));
	//※複数名前が一致した場合どれか一つが返されます
	//※確実にそのインスタンスを取得したい場合はプログラマーがきちんとユニークな名前で登録してください
	//※オブジェクトのインスタンスはCObjectManagerクラスの外部でdeleteしないこと
	//※必ずCObjectManagerクラスの削除関数(名前未定)を呼び出して行うこと
	//※関数が重いため多用しないこと
	template<class T>
	T* FindGameObject(LPCSTR ObjectName)
	{
		int size = m_GameObjects.size();
		for (int idx = 0; idx < size; idx++){
			if (!strcmp(m_GameObjects[idx]->objectname,ObjectName)){
				return (T*)m_GameObjects[idx]->object;
			}
		}
		MessageBox(NULL, "オブジェクトが登録されていません", 0, 0);
		return nullptr;
	}

	//Objectmanagerクラスに登録されているGameObjectのインスタンスを名前で検索し、一致したものを一件削除する関数
	//引き数: LPCSTR型 インスタンスの名前
	//返り値: なし
	//呼び出し例: SINSTANCE(CObjectManager)->DeleteGameObject(_T("インスタンスの名前"));
	//※最初にインスタンスの名前が一致したものが一件だけ削除されます
	//※確実にそのインスタンスを削除したい場合はプログラマーがきちんとユニークな名前で登録してください
	//※オブジェクトのインスタンスはCObjectManagerクラスの外部でdeleteしないこと
	//※オブジェクトの削除は必ずこの関数を呼び出して行うこと
	//※関数が重いため多用しないこと
	void DeleteGameObject(LPCSTR);

	void Intialize(LPD3DXSPRITE);
	void Update();
	void Draw();
private:
	void Add(CGameObject*,LPCSTR, short);
	vector<OBJECT_DATA*> m_GameObjects;
};