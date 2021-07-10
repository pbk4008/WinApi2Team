#include "framework.h"
#include "PlayerBullet.h"

CPlayerBullet::CPlayerBullet()
{
}

CPlayerBullet::~CPlayerBullet()
{
	Release();
}

void CPlayerBullet::Initialize()
{
	m_tInfo.iCX = 20;
	m_tInfo.iCY = 20;

	m_fSpeed = 10.f;
}

void CPlayerBullet::LateInit()
{
}

int CPlayerBullet::Update()
{
	if(m_bDead)
	{
		return EVENT::DEAD;
	}

	m_tInfo.fY -= m_fSpeed;
	
	
	return EVENT::NOEVENT;
}

void CPlayerBullet::LateUpdate()
{
	RectUpdate();
	
	if(m_tRect.left <= 0 || m_tRect.top <= 0 || m_tRect.right >= WINCX || m_tRect.bottom >= WINCY)
	{
		m_bDead = true;
	}
}

void CPlayerBullet::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayerBullet::Release()
{
}
