#include "framework.h"
#include "BossBullet.h"
#include "Stag1Boss.h"


CBossBullet::CBossBullet() : m_pTarget(nullptr)
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
	m_pTarget = dynamic_cast<CBoss*>(CObjMgr::getInstance()->getObj(OBJ::BOSS));
	m_ePattern = m_pTarget->getPattern();
}

void CBossBullet::LateInit()
{
}

int CBossBullet::Update()
{
	if (!m_pTarget)
		return m_bDead;
	switch (m_ePattern)
	{
	case BOSS::BASIC:
		m_tInfo.fY += m_fSpeed;
		break;
	case BOSS::PATTERN_1:
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
	RectUpdate();
}

void CBossBullet::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}
void CBossBullet::Release()
{	
}
