#include "framework.h"
#include "ObjMgr_Edit.h"
#include "Obj_Edit.h"
#include "CLine.h"

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
				Save_Point();
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

void CObjMgr_Edit::Save_Point()
{
	HANDLE hFile = (HANDLE)CreateFile(L"../Data/Player", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, L"저장 실패", L"실패", MB_OK);
		return;
	}
	DWORD dwByte = 0;
	for (auto pLine : CPosMgr_Edit::getInstance()->getList())
	{
		WriteFile(hFile, &pLine->getInfo().tLPos, sizeof(POS), &dwByte, nullptr);
		WriteFile(hFile, &pLine->getInfo().tRPos, sizeof(POS), &dwByte, nullptr);
	}
	
	MessageBox(g_hWnd, L"저장 성공!", L"성공", MB_OK);
	CloseHandle(hFile);
}
