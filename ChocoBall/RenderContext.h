#pragma once

#include "stdafx.h"
#include "Light.h"

class CCamera;

class CRenderContext{
	SINGLETON_DECL(CRenderContext)
public:
	void SetCurrentCamera(CCamera* cam)
	{
		m_pCamera = cam;
	}
	CCamera* GetCurrentCamera()
	{
		return m_pCamera;
	}
	void SetCurrentLight(CLight* light){
		m_pLight = light;
	}
	CLight* GetCurrentLight(){
		return m_pLight;
	}
private:
	CCamera* m_pCamera = nullptr;
	CLight* m_pLight = nullptr;
	void DeleteAll(){};
};
