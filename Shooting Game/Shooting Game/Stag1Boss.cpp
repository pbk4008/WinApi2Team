#include "framework.h"
#include "Stag1Boss.h"
#include "BossBullet.h"

CStag1Boss::CStag1Boss() :m_bulletDelayTime(0)
{
}

CStag1Boss::~CStag1Boss()
{
	Release();
}

void CStag1Boss::Initialize()
{
	m_tInfo.iCX = 200;
	m_tInfo.iCY = 200;
	m_iMaxHp = 100;
	m_iCurrentHp = m_iMaxHp;
	m_fSpeed = 5.f;
	m_ePattern = BOSS::BASIC;
	m_dwPatternTime = GetTickCount();
}

void CStag1Boss::LateInit()
{
}

int CStag1Boss::Update()
{
	if (m_bDead)
		return EVENT::DEAD;
	setPattern();
	RunPattern();

	return EVENT::NOEVENT;
}

void CStag1Boss::LateUpdate()
{
	RectUpdate();
	if (m_tRect.left <= 0 || m_tRect.right >= WINCX)
		m_fSpeed *= -1;
}

void CStag1Boss::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left, m_tRect.top,m_tRect.right, m_tRect.bottom);
}

void CStag1Boss::Release()
{
}

void CStag1Boss::setPattern()
{
	if (m_dwPatternTime + 3000 <= GetTickCount())
	{
		m_dwPatternTime = GetTickCount();
		m_ePattern = BOSS::PATTERN(m_ePattern + 1);
	}
}

void CStag1Boss::RunPattern()
{
	switch (m_ePattern)
	{
	case BOSS::BASIC:
		m_tInfo.fX += m_fSpeed;
		if (m_bulletDelayTime + 100 <= GetTickCount())
		{
			m_bulletDelayTime = GetTickCount();
			CreateBossBullet();
		}
		break;
	case BOSS::PATTERN_1:
		m_fBulletAngle = 0.f;
		m_tInfo.fX = float(WINCX >> 1);
		if (m_bulletDelayTime + 150 <= GetTickCount())
		{
			m_bulletDelayTime = GetTickCount();
			for (int i = 0; i < 20; i++)
			{
				CreateBossBullet(180 + (m_fBulletAngle += 18));
			}
		}
		
		break;
	case BOSS::PATTERN_2:
		break;
	case BOSS::PATTERN_3:
		break;
	}
}

void CStag1Boss::CreateBossBullet()
{
	CObj* pObj=nullptr;
	pObj=CObjMgr::getInstance()->ObjPooling(OBJ::BOSSBULLET);
	if (!pObj)
	{
		pObj = CAbstractFactory<CBossBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY);
		CObjMgr::getInstance()->getList(OBJ::BOSSBULLET).emplace_back(pObj);
	}
}

void CStag1Boss::CreateBossBullet(float _fAngle)
{
	CObj* pObj = nullptr;
	pObj = CObjMgr::getInstance()->ObjPooling(OBJ::BOSSBULLET);
	if (!pObj)
	{
		pObj = CAbstractFactory<CBossBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY);
		pObj->setAngle(_fAngle);
		CObjMgr::getInstance()->getList(OBJ::BOSSBULLET).emplace_back(pObj);
	}
	else
	{
		pObj->setAngle(_fAngle);
		dynamic_cast<CBossBullet*>(pObj)->setPattern(m_ePattern);
	}
}
