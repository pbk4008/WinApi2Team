#pragma once
#ifndef __ABSTRACTFACTORY_H__
#define __ABSTRACTFACTORY_H__
class CObj;
class CScene;
template<typename T>
class CAbstractFactory
{
public:
	static CObj* CreateObj()
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->setScene(CSceneMgr::getInstance()->getCurrentScene());
		return pObj;
	}
	static CObj* CreateObj(float _x, float _y)
	{
		CObj* pObj = CreateObj();
		pObj->setPos(_x, _y);
		return pObj;
	}
	static CScene* CreateScene(SCENE::TAG _eTag)
	{
		CScene* pScene = new T;
		pScene->Initialize();
		pScene->setTag(_eTag);
		pScene->LateInit();
		return pScene;
	}
};
#endif