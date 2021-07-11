#include "framework.h"
#include "Mouse_Edit.h"

CMouse_Edit::CMouse_Edit() : m_bDrawCheck(false)
{
}

CMouse_Edit::~CMouse_Edit()
{
	Release();
}

void CMouse_Edit::Initialize()
{
	m_tInfo.iCX = 10;
	m_tInfo.iCY = 10;
}

int CMouse_Edit::Update()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	m_tInfo.fX = (float)pt.x;
	m_tInfo.fY = (float)pt.y;

	RectUpdate();
	if (m_bDrawCheck=moveCheck())
		return EDIT_EVENT::NODRAW;

	if (m_bDrawCheck)
	{

	}

	return EDIT_EVENT::NOEVENT;
}

void CMouse_Edit::Render(HDC _hDC)
{
	if(!m_bDrawCheck)
		Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMouse_Edit::Release()
{
}

bool CMouse_Edit::moveCheck()
{
	if (m_tRect.left <= m_tBoard.left
		|| m_tRect.right >= m_tBoard.right
		|| m_tRect.top <= m_tBoard.top
		||m_tRect.bottom >= m_tBoard.bottom)
	{
		return true;
	}
	return false;
}
