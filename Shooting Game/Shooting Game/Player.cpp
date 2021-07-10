#include"framework.h"
#include "Player.h"

#include "PlayerBullet.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo.fX = (float)WINCX/2;
	m_tInfo.fY = 400.f;
	
	m_tInfo.iCX = 100;
	m_tInfo.iCY = 100;
	m_fSpeed = 5.f;

	m_iMaxHp = 3;
	m_iCurrentHp = m_iMaxHp;
}

void CPlayer::LateInit()
{
	
}

int CPlayer::Update()
{
	if (m_bDead)
		return EVENT::DEAD;

	if(GetAsyncKeyState(VK_LEFT) & 0x8000) // TODO HJ : keyMgr »ý¼º
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}

		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else
			m_tInfo.fX -= m_fSpeed;
	}

	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}

		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else
			m_tInfo.fX += m_fSpeed;
	}

	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_tInfo.fY -= m_fSpeed;
	}
	
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_tInfo.fY += m_fSpeed;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		CObjMgr::getInstance()->AddObject(OBJ::BULLET, Create_Bullet());
	}

	RectUpdate();
	return EVENT::NOEVENT;
}

void CPlayer::LateUpdate()
{
	if( 0 >= m_tRect.left)
	{
		m_tInfo.fX -= m_tRect.left;
	}

	if (WINCX <= m_tRect.right)
	{
		m_tInfo.fX -= m_tRect.right - WINCX;
	}

	if (0 >= m_tRect.top)
	{
		m_tInfo.fY -= m_tRect.top;
	}
	
	if (WINCY <= m_tRect.bottom)
	{
		m_tInfo.fY -= m_tRect.bottom - WINCY;
	}
}

void CPlayer::Render(HDC _hDC)
{
	RectUpdate();
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release()
{
}

CObj* CPlayer::Create_Bullet()
{
	
	return CAbstractFactory<CPlayerBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY);
	
}
