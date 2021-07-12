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
	LoadPoint(L"../Data/Boss");
	SetGraphicPos();
	SetPivot();
	m_PolygonList = new POINT[m_PosList.size()];
	for (int i = 0; i < m_PosList.size(); i++)
	{
		POINT pt = { m_PosList[i]->fX,m_PosList[i]->fY };
		m_PolygonList[i] = pt;
	}
	setDis();
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
	PosUpdate();
}

void CStag1Boss::Render(HDC _hDC)
{
	//Rectangle(_hDC, m_tRect.left, m_tRect.top,m_tRect.right, m_tRect.bottom);
	HBRUSH hBrush = (HBRUSH)CreateSolidBrush(RGB(251,152,146));
	HBRUSH hObj = (HBRUSH)SelectObject(_hDC, hBrush);
	Polygon(_hDC, m_PolygonList, m_PosList.size());
	SelectObject(_hDC, hObj);
	DeleteObject(hBrush);
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
		m_fBulletAngle = 0;
		m_tInfo.fX += m_fSpeed;
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

