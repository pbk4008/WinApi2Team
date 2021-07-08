#include "framework.h"
#include "BossBullet.h"
#include "Stag1Boss.h"


CBossBullet::CBossBullet()
{
}

CBossBullet::~CBossBullet()
{
	Release();
}

void CBossBullet::Initialize()
{
	m_tInfo.iCX = 20;
	m_tInfo.iCY = 20;
	m_fSpeed = 10.f;
	m_pTarget = CObjMgr::getInstance()->getObj(OBJ::BOSS);
	m_ePattern = dynamic_cast<CBoss*>(m_pTarget)->getPattern();
	m_bPollingCheck = true;
}

void CBossBullet::LateInit()
{
}

int CBossBullet::Update()
{
	if (!m_pTarget||m_bDead)
		return EVENT::DEAD;
	switch (m_ePattern)
	{
	case BOSS::BASIC:
		m_tInfo.fY += m_fSpeed;
		break;
	case BOSS::PATTERN_1:
		m_tInfo.fX += cosf(DEGREE2RADIAN(m_fAngle))*m_fSpeed;
		m_tInfo.fY -= sinf(DEGREE2RADIAN(m_fAngle))*m_fSpeed;
		break;
	case BOSS::PATTERN_2:
		break;
	case BOSS::PATTERN_3:
		break;
	}
	return EVENT::NOEVENT;
}

void CBossBullet::LateUpdate()
{
	if (!m_bDead)
	{
		RectUpdate();
		if (m_tRect.bottom >= WINCY)
			m_bDead = true;
	}
}

void CBossBullet::Render(HDC _hDC)
{
	if(!m_bDead)
		Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}
void CBossBullet::Release()
{	
}
