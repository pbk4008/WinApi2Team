#include "framework.h"
#include "Shield.h"

CShield::CShield() : m_fDis(0)
{
}

CShield::~CShield()
{
	Release();
}

void CShield::Initialize()
{
	m_tInfo.iCX = 30;
	m_tInfo.iCY = 30;

	m_fSpeed = 10.f;
	m_fDis = 100.f;

	m_pTarget = CObjMgr::getInstance()->getPlayer();

	m_bPollingCheck = true;
}

void CShield::LateInit()
{
}

int CShield::Update()
{
	if(m_bDead)
	{
		return EVENT::DEAD;
	}

	else
	{
		m_fAngle += m_fSpeed;

		m_tInfo.fX = m_pTarget->getInfo().fX + cosf(m_fAngle * PI / 180.f) * m_fDis;
		m_tInfo.fY = m_pTarget->getInfo().fY - sinf(m_fAngle * PI / 180.f) * m_fDis;

		if (m_pCollisionTarget)
		{
			m_pCollisionTarget->setDead(true);
			m_pCollisionTarget = nullptr;
		}

		RectUpdate();
	}


	return EVENT::NOEVENT;
}

void CShield::LateUpdate()
{
	
}

void CShield::Render(HDC _hDC)
{
	if(!m_bDead)
	{
		Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}

}

void CShield::Release()
{
	SAFE_DELETE_ARR(m_PolygonList);
	SAFE_DELETE_ARR(m_iPosDisArr);
}
