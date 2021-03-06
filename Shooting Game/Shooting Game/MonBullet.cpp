#include "framework.h"
#include "MonBullet.h"
#include "Monster.h"

CMonBullet::CMonBullet() : m_ePattern(ENEMY::PATTERN_END)
{
}

CMonBullet::~CMonBullet()
{
	Release();
}

void CMonBullet::Initialize()
{
	m_tInfo.iCX = 20;
	m_tInfo.iCY = 20;
	m_fSpeed = 10.f;
	m_pTarget = CObjMgr::getInstance()->getObj(OBJ::MONSTER);
	m_ePattern = ENEMY::PATTERN_1;
	//m_ePattern = static_cast<CMonster*>(m_pTarget)->getPattern();
	//m_bPollingCheck = true;
}

void CMonBullet::LateInit()
{
}

int CMonBullet::Update()
{
	if (!m_pTarget || m_bDead)
	{
		return EVENT::DEAD;
	}

	if (m_pCollisionTarget)
	{
		//m_pCollisionTarget->setDead(true);
		m_pCollisionTarget = nullptr;
	}

	switch (m_ePattern)
	{
	case ENEMY::PATTERN_1:
		m_tInfo.fX = (LONG)(m_tInfo.fX + cosf(m_fAngle * PI / 180.f) * m_fSpeed);
		m_tInfo.fY = (LONG)(m_tInfo.fY - sinf(m_fAngle * PI / 180.f) * m_fSpeed);
		break;
	}
	return EVENT::NOEVENT;
}

void CMonBullet::LateUpdate()
{
	if (!m_bDead)
	{
		RectUpdate();
		if (m_tRect.left <= 0
			|| m_tRect.right >= WINCX
			|| m_tRect.top <= 0
			|| m_tRect.bottom >= WINCY)
			m_bDead = true;
	}
}

void CMonBullet::Render(HDC _hDC)
{
	if (!m_bDead)
		Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonBullet::Release()
{
	SAFE_DELETE_ARR(m_PolygonList);
	SAFE_DELETE_ARR(m_iPosDisArr);
}
