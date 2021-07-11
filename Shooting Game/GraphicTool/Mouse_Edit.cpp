#include "framework.h"
#include "Mouse_Edit.h"
#include "Button_Edit.h"
#include "CLine.h"

CMouse_Edit::CMouse_Edit() : m_bDrawCheck(false), m_bDrawFirstCheck(false)
{
	ZeroMemory(&m_tPos, sizeof(POS));
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
	if (m_bDrawCheck = moveCheck())
	{
		if (m_pCollisonTarget)
		{
			if (!CCollisionMgr::RectCheck(this, m_pCollisonTarget))
			{
				m_pCollisonTarget = nullptr;
				return EDIT_EVENT::NODRAW;
			}
			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
			{
				switch (dynamic_cast<CButton_Edit*>(m_pCollisonTarget)->getName())
				{
				case BUTTON::REMOVE:
					return EDIT_EVENT::REMOVE;
				case BUTTON::SAVE:
					return EDIT_EVENT::SAVE;
				}
			}
		}
	}
	Draw();

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

void CMouse_Edit::Draw()
{
	if (!m_bDrawCheck)
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (!m_bDrawFirstCheck)
			{
				m_tPos[0] = { m_tInfo.fX, m_tInfo.fY };
				m_bDrawFirstCheck = true;
			}
			else
			{
				m_tPos[1] = { m_tInfo.fX, m_tInfo.fY };
				CPosMgr_Edit::getInstance()->AddPos(new CLine(m_tPos[0], m_tPos[1]));
				memcpy(&m_tPos[0], &m_tPos[1], sizeof(POS));
			}
		}
		if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
		{
			m_bDrawFirstCheck = false;
		}
	}
}
