#include "framework.h"
#include "HomingBullet.h"

CHomingBullet::CHomingBullet() : m_BossTarget(nullptr)
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

	m_fSpeed =10.f;

	m_fAngle = 90.f;

	m_iAtk = 1;
}

void CHomingBullet::LateInit()
{
	
}

int CHomingBullet::Update()
{
	if(m_bDead)
	{
		return EVENT::DEAD;
	}

	else
	{
		list<CObj*> listMonster = CObjMgr::getInstance()->getList(OBJ::MONSTER);
		
		m_pTarget = Find_Monster();
		
		if(!m_pTarget && !CObjMgr::getInstance()->getList(OBJ::BOSS).empty())
		{
			m_pTarget = CObjMgr::getInstance()->getTarget(OBJ::BOSS, this);
		}
		
		
		
		if(!m_pTarget)
		{
			m_fAngle = 90.f;
		}

		else
		{
			m_fAngle = CMathMgr::getAngle(m_pTarget, this) * 180.f / PI;
			

			if (m_pTarget->getInfo().fY >= m_tInfo.fY)
			{
				m_fAngle *= -1.f;
			}
		}
		
		m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;

		
	}

	if (m_pCollisionTarget)
	{
		if (m_pCollisionTarget)
		{
			if (!CObjMgr::getInstance()->getList(OBJ::BOSS).empty() && m_pCollisionTarget == CObjMgr::getInstance()->getObj(OBJ::BOSS))
			{

			}
			else
			{
				m_pCollisionTarget->setDead(true);
				m_pCollisionTarget = nullptr;
				m_bDead = true;
			}
		}
	}

	RectUpdate();
	return EVENT::NOEVENT;
}

void CHomingBullet::LateUpdate()
{
	if(!m_bDead)
	{
		RectUpdate();

		if (m_tRect.left <= 0 || m_tRect.top <= 0 || m_tRect.right >= WINCX || m_tRect.bottom >= WINCY)
		{
			m_bDead = true;
		}
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
	SAFE_DELETE_ARR(m_PolygonList);
	SAFE_DELETE_ARR(m_iPosDisArr);

}

CObj* CHomingBullet::Find_Monster()
{
	list<CObj*> listMonster = CObjMgr::getInstance()->getList(OBJ::MONSTER);
	
	CObj* pObj= nullptr;
	int length = 0;
	
	for (auto& Monster : listMonster)
	{
		bool bMonDead = Monster->getDead();

		if (bMonDead)
		{
			//m_fAngle = 90.f;
			continue;
		}

		if (!bMonDead)
		{
			float fdis = CMathMgr::getDist(Monster, this);
			if(length >= fdis || length ==0 )
			{
				length = fdis;
				pObj = Monster;
			}
		}
	}

	if(length ==0)
	{
		return nullptr;
	}
	
	return pObj;
}
