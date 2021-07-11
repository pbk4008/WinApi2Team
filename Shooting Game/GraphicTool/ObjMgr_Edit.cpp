#include "framework.h"
#include "ObjMgr_Edit.h"
#include "Obj_Edit.h"

CObjMgr_Edit* CObjMgr_Edit::m_pInstance = nullptr;
CObjMgr_Edit::CObjMgr_Edit()
{
}

CObjMgr_Edit::~CObjMgr_Edit()
{
	Release();
}

CObjMgr_Edit* CObjMgr_Edit::getInstance()
{
	if (!m_pInstance)
		m_pInstance = new CObjMgr_Edit;
	return m_pInstance;
}

void CObjMgr_Edit::DestroyInstance()
{
	SAFE_DELETE(m_pInstance);
}

void CObjMgr_Edit::Update()
{
	for (auto pList : m_ObjList)
	{
		auto iter = pList.begin();
		for (; iter != pList.end();iter++)
		{
			int iEvent = (*iter)->Update();
			switch (iEvent)
			{
			case EDIT_EVENT::NODRAW:
				break;
			case EDIT_EVENT::NOEVENT:
				break;
			case EDIT_EVENT::REMOVE:
				CPosMgr_Edit::getInstance()->Release();
				break;
			case EDIT_EVENT::SAVE:
				break;
			}
			
		}
	}
}

void CObjMgr_Edit::Render(HDC _hDC)
{
	for (auto& pList : m_ObjList)
	{
		for (auto pObj : pList)
			pObj->Render(_hDC);
	}
}

void CObjMgr_Edit::Release()
{
	for (auto& pList : m_ObjList)
	{
		for_each(pList.begin(), pList.end(), Safe_Delete<CObj_Edit*>);
		pList.clear();
	}
}
