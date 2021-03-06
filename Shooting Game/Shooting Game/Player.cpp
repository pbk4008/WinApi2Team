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

	LoadPoint(L"../Data/Player");
   	SetGraphicPos();
	SetPivot();
	m_PolygonList = new POINT[m_PosList.size()];
	for (int i = 0; i < m_PosList.size(); i++)
	{
		POINT pt = { m_PosList[i]->fX,m_PosList[i]->fY };
		m_PolygonList[i] = pt;
	}
	setDis();
	//PosUpdate();
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
			//CObjMgr::getInstance()->AddObject(OBJ::SCREWBULLET, Create_ScrewBullet());
			Create_ScrewBullet();
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
		{
			//CObjMgr::getInstance()->AddObject(OBJ::HOMINGBULLET, Create_HomingBullet());
			Create_HomingBullet();
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
	PosUpdate();
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
		//RectUpdate();
		//Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		HBRUSH hBrush = (HBRUSH)CreateSolidBrush(RGB(80, 80, 80));
		HBRUSH hObj = (HBRUSH)SelectObject(_hDC, hBrush);
		Polygon(_hDC, m_PolygonList, m_PosList.size());
		SelectObject(_hDC, hObj);
		DeleteObject(hBrush);
	}
}

void CPlayer::Release()
{
	SAFE_DELETE_ARR(m_PolygonList);
	SAFE_DELETE_ARR(m_iPosDisArr);
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

void CPlayer::Create_ScrewBullet()
{
	//return CAbstractFactory<CScrewBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY);
	CObj* pObj = nullptr;
	pObj = CObjMgr::getInstance()->ObjPooling(OBJ::SCREWBULLET, this);
	if (!pObj)
	{
		pObj = CAbstractFactory<CScrewBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY);
		pObj->LateInit();
		CObjMgr::getInstance()->getList(OBJ::SCREWBULLET).emplace_back(pObj);
	}

	else
	{
		pObj->setAngle(0);
	}
	
}

void CPlayer::Create_HomingBullet()
{
	//return CAbstractFactory<CHomingBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY);

	CObj* pObj = nullptr;
	pObj = CObjMgr::getInstance()->ObjPooling(OBJ::HOMINGBULLET, this);
	if (!pObj)
	{
		pObj = CAbstractFactory<CHomingBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY);
		pObj->LateInit();
		CObjMgr::getInstance()->getList(OBJ::HOMINGBULLET).emplace_back(pObj);
	}

	else
	{
		pObj->setAngle(0);
	}

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
