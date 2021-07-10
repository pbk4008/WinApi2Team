#include "framework.h"
#include "HpBar.h"
#include "Boss.h"

CHpBar::CHpBar()
{
}

CHpBar::~CHpBar()
{
	Release();
}

void CHpBar::Initialize()
{
	m_tInfo = { WINCX / 2, 70, WINCX-100, 30 };
	m_pTarget = CObjMgr::getInstance()->getObj(OBJ::BOSS);
}

void CHpBar::LateInit()
{
}

int CHpBar::Update()
{
	if (m_bDead)
		return EVENT::DEAD;
	return EVENT::NOEVENT;
}

void CHpBar::LateUpdate()
{
	if (m_pTarget->getHp()<=0)
		m_bDead = true;
	RectUpdate();
	m_tRect.right = m_tRect.left + (m_tInfo.iCX * dynamic_cast<CBoss*>(m_pTarget)->getRatio());
}

void CHpBar::Render(HDC _hDC)
{
	HBRUSH hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hObj = (HBRUSH)SelectObject(_hDC, hBrush);
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tInfo.fX+(m_tInfo.iCX>>1), m_tRect.bottom);
	SelectObject(_hDC, hObj);
	DeleteObject(hBrush);
	hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	hObj = (HBRUSH)SelectObject(_hDC, hBrush);
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(_hDC, hObj);
	DeleteObject(hBrush);	
}

void CHpBar::Release()
{
}
