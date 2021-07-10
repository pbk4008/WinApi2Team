#include "framework.h"
#include "HomingBullet.h"

CHomingBullet::CHomingBullet()
{
}

CHomingBullet::~CHomingBullet()
{
	Release();
}

void CHomingBullet::Initialize()
{
	m_tInfo.iCX = 20;
	m_tInfo.iCY = 20;

	m_fSpeed = 20.f;
}

void CHomingBullet::LateInit()
{
	
}

int CHomingBullet::Update()
{
	if(m_bDead || m_pCollisionTarget)
	{
		return EVENT::DEAD;
	}

	else
	{
		m_pTarget = CObjMgr::getInstance()->getTarget(OBJ::MONSTER, this);

		if(m_pTarget)
		{
			float fX = m_pTarget->getInfo().fX - m_tInfo.fX;
			float fY = m_pTarget->getInfo().fY - m_tInfo.fY;
			float fDia = sqrtf(fX * fX + fY * fY);

			float fRad = acosf(fX / fDia);
			m_fAngle = fRad * 180.f / PI;

			if(m_pTarget->getInfo().fY >= m_tInfo.fY)
			{
				m_fAngle *= -1.f;
			}
		}

		m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;

		RectUpdate();
	}


	return EVENT::NOEVENT;
}

void CHomingBullet::LateUpdate()
{
	RectUpdate();

	if (m_tRect.left <= 0 || m_tRect.top <= 0 || m_tRect.right >= WINCX || m_tRect.bottom >= WINCY)
	{
		m_bDead = true;
	}
}

void CHomingBullet::Render(HDC _hDC)
{
	if(!m_bDead)
	{
		Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}

}

void CHomingBullet::Release()
{
}
