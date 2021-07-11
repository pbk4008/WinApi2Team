#include"framework.h"
#include "Player.h"

#include "HomingBullet.h"
#include "PlayerBullet.h"
#include "ScrewBullet.h"
#include "Shield.h"

CPlayer::CPlayer() : m_shieldCount(0) , dwTime(GetTickCount())
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo.fX = (float)WINCX/2;
	m_tInfo.fY = 400.f;
	
	m_tInfo.iCX = 100;
	m_tInfo.iCY = 100;
	m_fSpeed = 5.f;

	m_iMaxHp = 3;
	m_iCurrentHp = m_iMaxHp;
	m_bPollingCheck = true;
}

void CPlayer::LateInit()
{
	
}

int CPlayer::Update()
{
	if (m_bDead)
	{
		return EVENT::DEAD;
	}

	else
	{
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		{
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
			{
				m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
				m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
			}

			else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
			{
				m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
				m_tInfo.fY += m_fSpeed / sqrtf(2.f);
			}
			else
				m_tInfo.fX -= m_fSpeed;
		}

		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		{
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
			{
				m_tInfo.fX += m_fSpeed / sqrtf(2.f);
				m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
			}

			else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
			{
				m_tInfo.fX += m_fSpeed / sqrtf(2.f);
				m_tInfo.fY += m_fSpeed / sqrtf(2.f);
			}
			else
				m_tInfo.fX += m_fSpeed;
		}

		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			m_tInfo.fY -= m_fSpeed;
		}

		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			m_tInfo.fY += m_fSpeed;
		}

		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE) && dwTime + 50 <= GetTickCount())
		{
			dwTime = GetTickCount();
			Create_Bullet();
		}

		
		if (CKeyMgr::Get_Instance()->Key_Pressing('S') && m_shieldCount <= 35)
		{
			++m_shieldCount;

			Create_Shield();
		}

		if(CKeyMgr::Get_Instance()->Key_Up('S'))
		{
			for(auto& Shield : CObjMgr::getInstance()->getList(OBJ::SHIELD))
			{
				Shield->setDead(true);
			}
			m_shieldCount = 0;
		}


		if(CKeyMgr::Get_Instance()->Key_Pressing('A'))
		{
			CObjMgr::getInstance()->AddObject(OBJ::SCREWBULLET, Create_ScrewBullet());
		}


		if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
		{
			CObjMgr::getInstance()->AddObject(OBJ::HOMINGBULLET, Create_HomingBullet());
		}


		if (m_pCollisionTarget)
		{
			--m_iCurrentHp;
			m_pCollisionTarget->setDead(true);
			m_pCollisionTarget = nullptr;
		}

	}


	return EVENT::NOEVENT;
}

void CPlayer::LateUpdate()
{
	
	if(0 == m_iCurrentHp)
	{
		m_bDead = true;
	}
	
	else
	{
		RectUpdate();
		if (0 >= m_tRect.left)
		{
			m_tInfo.fX -= m_tRect.left;
		}

		if (WINCX <= m_tRect.right)
		{
			m_tInfo.fX -= m_tRect.right - WINCX;
		}

		if (0 >= m_tRect.top)
		{
			m_tInfo.fY -= m_tRect.top;
		}

		if (WINCY <= m_tRect.bottom)
		{
			m_tInfo.fY -= m_tRect.bottom - WINCY;
		}
	}
}

void CPlayer::Render(HDC _hDC)
{
	if(!m_bDead)
	{
		RectUpdate();
		Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}

}

void CPlayer::Release()
{
}

void CPlayer::Create_Bullet()
{
	CObj* pObj = nullptr;
	pObj = CObjMgr::getInstance()->ObjPooling(OBJ::BULLET, this);
	if (!pObj)
	{
		pObj = CAbstractFactory<CPlayerBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY);
		pObj->LateInit();
		CObjMgr::getInstance()->getList(OBJ::BULLET).emplace_back(pObj);
	}
	else
	{
		pObj->setAngle(0);
	};
	
}

CObj* CPlayer::Create_ScrewBullet()
{
	return CAbstractFactory<CScrewBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY);
}

CObj* CPlayer::Create_HomingBullet()
{
	return CAbstractFactory<CHomingBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY);
}

void CPlayer::Create_Shield()
{
	CObj* pObj = nullptr;
	pObj = CObjMgr::getInstance()->ObjPooling(OBJ::SHIELD, this);
	if (!pObj)
	{
		pObj = CAbstractFactory<CShield>::CreateObj(this);
		pObj->LateInit();
		CObjMgr::getInstance()->getList(OBJ::SHIELD).emplace_back(pObj);
	}

	else
	{
		pObj->setAngle(0);
	}
}
