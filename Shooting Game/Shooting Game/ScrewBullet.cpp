#include "framework.h"
#include "ScrewBullet.h"

CScrewBullet::CScrewBullet() : m_fCenterAngle(0.f), m_fCenterSpeed(0.f), m_bStart(true) , m_fDis(0)
{
	ZeroMemory(&m_tCenterPos, sizeof(m_tCenterPos));
}

CScrewBullet::~CScrewBullet()
{
	Release();
}

void CScrewBullet::Initialize()
{
	m_tInfo.iCX = 20;
	m_tInfo.iCY = 20;

	m_fSpeed = 20.f;
	m_fDis = 50.f;

	m_fCenterSpeed = 5.f;
	m_fAngle = 90;
}

void CScrewBullet::LateInit()
{
}

int CScrewBullet::Update()
{
	if(m_bDead)
	{
		return EVENT::DEAD;
	}

	else
	{
		
		if (m_bStart)
		{
			m_tCenterPos.x = (LONG)m_tInfo.fX;
			m_tCenterPos.y = (LONG)m_tInfo.fY;
			m_fCenterAngle = m_fAngle;
			m_bStart = false;
			m_fAngle = 270;
		}
		

		m_tCenterPos.x += (LONG)(cosf(m_fCenterAngle * PI / 180.f) * m_fCenterSpeed);
		m_tCenterPos.y -= (LONG)(sinf(m_fCenterAngle * PI / 180.f) * m_fCenterSpeed);

		m_tInfo.fX = (m_tCenterPos.x + cosf(m_fAngle * PI / 180.f) * m_fDis);
		m_tInfo.fY = (m_tCenterPos.y - sinf(m_fAngle * PI / 180.f) * m_fDis) -100;

		m_fAngle -= m_fSpeed;

		RectUpdate();
	}


	return EVENT::NOEVENT;
}

void CScrewBullet::LateUpdate()
{
	RectUpdate();

	if (m_tRect.left <= 0 || m_tRect.top <= 0 || m_tRect.right >= WINCX || m_tRect.bottom >= WINCY)
	{
		m_bDead = true;
	}
}

void CScrewBullet::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CScrewBullet::Release()
{
	SAFE_DELETE_ARR(m_PolygonList);
	SAFE_DELETE_ARR(m_iPosDisArr);
}
