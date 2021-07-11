#include "framework.h"
#include "Stag1Boss.h"
#include "BossBullet.h"
#include "HpBar.h"

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
	m_eNextPattern = BOSS::PATTERN_1;
	m_ePausePattern = BOSS::BASIC;
	m_eCurPattern = m_ePausePattern;
	m_dwCurTime = GetTickCount();
	m_dwPatternTime = 3000;
}

void CStag1Boss::LateInit()
{
	CObjMgr::getInstance()->AddObject(OBJ::HPBAR, CAbstractFactory<CHpBar>::CreateObj());
}

int CStag1Boss::Update()
{
	if (m_bDead)
		return EVENT::DEAD;
	setPattern();
	RunPattern();
	if (m_pCollisionTarget)
	{
		m_iCurrentHp -= m_pCollisionTarget->getAtk();
		m_pCollisionTarget->setDead(true);
		m_pCollisionTarget = nullptr;
	}
	return EVENT::NOEVENT;
}

void CStag1Boss::LateUpdate()
{
	if (m_iCurrentHp <= 0)
		m_bDead = true;
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
	SAFE_DELETE_ARR(m_PolygonList);
	SAFE_DELETE_ARR(m_iPosDisArr);
}

void CStag1Boss::setPattern()
{ 

	if (m_dwCurTime + m_dwPatternTime <= GetTickCount())
	{
		m_dwCurTime = GetTickCount();
		if (m_eCurPattern == m_ePausePattern)
		{
			m_eCurPattern = m_eNextPattern;
			m_eNextPattern = BOSS::PATTERN(m_eNextPattern + 1);
			if (m_eNextPattern == BOSS::PATTENR_END)
				m_eNextPattern = BOSS::PATTERN_1;
			m_dwPatternTime = 5000;
		}
		else
		{
			m_eCurPattern = m_ePausePattern;
			m_dwPatternTime = 3000;
		}
	}
}

void CStag1Boss::RunPattern()
{
	switch (m_eCurPattern)
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
				CreateBossBullet(180 + (m_fBulletAngle += 18));
		}
		break;
	case BOSS::PATTERN_2:
		m_tInfo.fX += m_fSpeed;
		if (m_bulletDelayTime + 500 <= GetTickCount())
		{
			m_bulletDelayTime = GetTickCount();
			CreateBossBullet(true);
		}
		break;
	case BOSS::PATTERN_3:
		m_tInfo.fX += m_fSpeed;
		if (m_bulletDelayTime + 2000 <= GetTickCount())
		{
			m_bulletDelayTime = GetTickCount();
			CreateBossBullet();
		}
		break;
	}
}

void CStag1Boss::CreateBossBullet(bool _bCheck)
{
	CObj* pObj=nullptr;
	pObj=CObjMgr::getInstance()->ObjPooling(OBJ::BOSSBULLET,this);
	if (!pObj)
	{
		pObj = CAbstractFactory<CBossBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY);
		dynamic_cast<CBossBullet*>(pObj)->setSizeCheck(_bCheck);
		pObj->LateInit();
		CObjMgr::getInstance()->getList(OBJ::BOSSBULLET).emplace_back(pObj);
	}
	else
	{
		dynamic_cast<CBossBullet*>(pObj)->setPattern(m_eCurPattern);
		dynamic_cast<CBossBullet*>(pObj)->setSizeCheck(_bCheck);
		pObj->LateInit();
	}
}

void CStag1Boss::CreateBossBullet(float _fAngle, bool _bCheck)
{
	CObj* pObj = nullptr;
	pObj = CObjMgr::getInstance()->ObjPooling(OBJ::BOSSBULLET,this);
	if (!pObj)
	{
		pObj = CAbstractFactory<CBossBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY);
		pObj->setAngle(_fAngle);
		dynamic_cast<CBossBullet*>(pObj)->setSizeCheck(_bCheck);
		pObj->LateInit();
		CObjMgr::getInstance()->getList(OBJ::BOSSBULLET).emplace_back(pObj);
	}
	else
	{
		pObj->setAngle(_fAngle);
		dynamic_cast<CBossBullet*>(pObj)->setPattern(m_eCurPattern);
		dynamic_cast<CBossBullet*>(pObj)->setSizeCheck(_bCheck);
		pObj->LateInit();
	}
}

