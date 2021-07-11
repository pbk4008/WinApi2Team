#include "framework.h"
#include "Obj_Edit.h"

CObj_Edit::CObj_Edit() : m_pCollisonTarget(nullptr)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tRect, sizeof(m_tRect));
}

CObj_Edit::~CObj_Edit()
{
}

void CObj_Edit::RectUpdate()
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.iCX >> 1));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.iCX >> 1));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.iCY >> 1));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.iCY >> 1));
}
