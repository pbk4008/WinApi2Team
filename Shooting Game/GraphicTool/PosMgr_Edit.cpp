#include "framework.h"
#include "PosMgr_Edit.h"
#include "CLine.h"

CPosMgr_Edit* CPosMgr_Edit::m_pInstance = nullptr;
CPosMgr_Edit::CPosMgr_Edit()
{
}

CPosMgr_Edit::~CPosMgr_Edit()
{
	Release();
}

void CPosMgr_Edit::Render(HDC _hDC)
{
	for (auto pLine : m_PosList)
	{
		pLine->Render(_hDC);
	}
}

void CPosMgr_Edit::Release()
{
	for_each(m_PosList.begin(), m_PosList.end(), Safe_Delete<CLine*>);
	m_PosList.clear();
}

CPosMgr_Edit* CPosMgr_Edit::getInstance()
{
	if (!m_pInstance)
		m_pInstance = new CPosMgr_Edit;
	return m_pInstance;
}

void CPosMgr_Edit::DestroyInstance()
{
	SAFE_DELETE(m_pInstance);
}
