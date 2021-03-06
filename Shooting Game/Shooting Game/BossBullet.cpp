#include "framework.h"
#include "BossBullet.h"
#include "Stag1Boss.h"


CBossBullet::CBossBullet() : m_ePattern(BOSS::PATTENR_END), m_bSizeCheck(false), m_dwCurTime(0)
, m_bSplitCheck(false)
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
	if (m_bSizeCheck)
	{
		m_tInfo.iCX = 40;
		m_tInfo.iCY = 40;
		m_fSpeed = 5.f;
		m_dwCurTime = GetTickCount();
	}
	else
	{
		m_tInfo.iCX = 20;
		m_tInfo.iCY = 20;
		m_fSpeed = 10.f;
	}
}

int CBossBullet::Update()
{
	if (!m_pTarget || m_bDead)
		return EVENT::DEAD;
	switch (m_ePattern)
	{
	case BOSS::BASIC:
		m_tInfo.fY += m_fSpeed;
		break;
	case BOSS::PATTERN_1:
		m_tInfo.fX += cosf(DEGREE2RADIAN(m_fAngle)) * m_fSpeed;
		m_tInfo.fY -= sinf(DEGREE2RADIAN(m_fAngle)) * m_fSpeed;
		break;
	case BOSS::PATTERN_2:
		if (m_bSizeCheck)
		{
			m_tInfo.fY += m_fSpeed;
			if (m_dwCurTime + 500 == GetTickCount())
			{
				m_bSplitCheck = true;
				m_bDead = true;
			}
			
			if (m_bSplitCheck)
			{
				m_bSplitCheck = false;
				for (int i = 0; i < 5; i++)
					Split(216 + (i * 30));
			}
		}
		else
		{
			m_tInfo.fX += cosf(DEGREE2RADIAN(m_fAngle)) * m_fSpeed;
			m_tInfo.fY -= sinf(DEGREE2RADIAN(m_fAngle)) * m_fSpeed;
		}
		break;
	case BOSS::PATTERN_3:
		m_tInfo.iCX = 80;
		m_tInfo.iCY = 80;
		m_fSpeed = 3.f;
		m_fAngle = CMathMgr::getAngle(CObjMgr::getInstance()->getPlayer(), this);
		if (CObjMgr::getInstance()->getPlayer()->getInfo().fY > m_tInfo.fY)
			m_fAngle *= -1;
		m_tInfo.fX += cosf(m_fAngle) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle) * m_fSpeed;
		if (m_pCollisionTarget)
		{
			m_bDead = true;
			m_pCollisionTarget->setDead(true);
			m_pCollisionTarget = nullptr;
		}
		break;
	}
	return EVENT::NOEVENT;
}

void CBossBullet::LateUpdate()
{
	if (m_pTarget->getDead())
		m_bDead = true;
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

void CBossBullet::Render(HDC _hDC)
{
	if (!m_bDead)
	{
		HBRUSH hBrush;
		if (m_ePattern == BOSS::PATTERN_3)
			hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 255));
		else
			hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
		HBRUSH hObj = (HBRUSH)SelectObject(_hDC,hBrush);
		Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(_hDC, hObj);
		DeleteObject(hBrush);
	}
}
void CBossBullet::Release()
{
	SAFE_DELETE_ARR(m_PolygonList);
	SAFE_DELETE_ARR(m_iPosDisArr);
}

void CBossBullet::Split(float _Angle)
{
	CObj* pBullet = CObjMgr::getInstance()->ObjPooling(OBJ::BOSSBULLET, this);
	if (!pBullet)
	{
		pBullet = CAbstractFactory<CBossBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY);
		pBullet->setAngle(_Angle);
		dynamic_cast<CBossBullet*>(pBullet)->setSizeCheck(false);
		pBullet->LateInit();
		CObjMgr::getInstance()->getList(OBJ::BOSSBULLET).emplace_back(pBullet);
	}
	else
	{
		pBullet->setAngle(_Angle);
		pBullet->setPos(m_tInfo.fX, m_tInfo.fY);
		dynamic_cast<CBossBullet*>(pBullet)->setSizeCheck(false);
		dynamic_cast<CBossBullet*>(pBullet)->setPattern(BOSS::PATTERN_2);
		pBullet->LateInit();
	}
}
