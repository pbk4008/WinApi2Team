#include "framework.h"
#include "ObjMgr.h"
#include "Obj.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;
CObjMgr::CObjMgr()
{
}
CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::LateInit()
{
	for (auto& pList : m_ObjList)
	{
		for (auto pObj : pList)
		{
			SCENE::TAG eScene = CSceneMgr::getInstance()->getCurrentScene();
			if (eScene == pObj->getScene())
			{
				pObj->LateInit();
			}
		}
	}
}

int CObjMgr::Update()
{
	SCENE::TAG eScene = CSceneMgr::getInstance()->getCurrentScene();
	for (auto& pList : m_ObjList)
	{
		auto iter = pList.begin();
		for (; iter != pList.end();)
		{
			if (eScene != (*iter)->getScene())
				continue;
			int iEvent = (*iter)->Update();
			if (iEvent == EVENT::DEAD)
			{
				if (!(*iter)->getNotDestory() && !(*iter)->getPoolingCheck())
				{
					Safe_Delete(*iter);
					iter = pList.erase(iter);
				}
				else
					++iter;
			}
			else if (iEvent == EVENT::GAME_START)
			{
				return SCENE_CHANGE;
			}
			else if (iEvent == EVENT::GAME_END)
			{
				return GAME_QUIT;
			}
			else
				++iter;
		}
	}
	return NO_SCENE;
}

void CObjMgr::LateUpdate()
{
	SCENE::TAG eScene = CSceneMgr::getInstance()->getCurrentScene();
	for (auto& pList : m_ObjList)
	{
		for (auto pObj : pList)
		{
			if (eScene == pObj->getScene())
			{
				pObj->LateUpdate();
			}
		}
	}
}

void CObjMgr::Render(HDC _hDC)
{
	SCENE::TAG eScene = CSceneMgr::getInstance()->getCurrentScene();
	for (auto& pList : m_ObjList)
	{
		for (auto pObj : pList)
		{
			if (eScene == pObj->getScene())
			{
				pObj->Render(_hDC);
			}
		}
	}
}

void CObjMgr::Release()
{
	for (auto& pList : m_ObjList)
	{
		for_each(pList.begin(), pList.end(), Safe_Delete<CObj*>);
		pList.clear();
	}
}

CObjMgr* CObjMgr::getInstance()
{
	if (!m_pInstance)
		m_pInstance = new CObjMgr;
	return m_pInstance;
}

void CObjMgr::DestroyInstance()
{
	SAFE_DELETE(m_pInstance);
}

void CObjMgr::SceneObjectRemove(SCENE::TAG _eTag)
{
	for (auto& pList : m_ObjList)
	{
		auto iter = pList.begin();
		for (; iter != pList.end();)
		{
			if (_eTag == (*iter)->getScene() && !(*iter)->getNotDestory())
			{
				SAFE_DELETE((*iter));
				iter = pList.erase(iter);
			}
			else 
				++iter;
		}
	}
}

CObj* CObjMgr::ObjPooling(OBJ::ID _eID)
{
	if (m_ObjList[_eID].empty())
		return nullptr;
	for (auto pObj : m_ObjList[_eID])
	{
		if (pObj->getDead())
		{
			pObj->setDead(false);
			pObj->setPos(pObj->getTarget()->getInfo().fX, pObj->getTarget()->getInfo().fY);
			return pObj;
		}
		if(pObj==m_ObjList[_eID].back())
			return nullptr;
	}

}


CObj* CObjMgr::DeadCheck(OBJ::ID _eID)
{
	for (auto pObj : m_ObjList[_eID])
	{
		if (pObj->getDead())
		{
			pObj->setDead(false);
			return pObj;
		}
	}
	return nullptr;
}
