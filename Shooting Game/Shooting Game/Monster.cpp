#include "framework.h"
#include "Monster.h"

CMonster::CMonster() : m_eType(ENEMY::END)
{
}

CMonster::~CMonster()
{
}

void CMonster::Initialize()
{
	m_tInfo.iCX = 60;
	m_tInfo.iCY = 60;

	m_fSpeed = 5.f;

}

void CMonster::LateInit()
{
	SetEnemy(ENEMY::ENEMY1);
}

int CMonster::Update()
{
	if (m_bDead)
		return EVENT::DEAD;

	//m_tInfo.fX += m_fSpeed;



	return EVENT::NOEVENT;
}

void CMonster::LateUpdate()
{
	RectUpdate();
	if (m_tRect.left <= 0 || m_tRect.right >= WINCX)
		m_fSpeed *= -1;


}

void CMonster::Render(HDC _hDC)
{
	if (m_eType == ENEMY::ENEMY1)
	{
		MoveToEx(_hDC, m_tRect.left, m_tRect.top, NULL);
		LineTo(_hDC, m_tRect.right, m_tRect.top);
		LineTo(_hDC, (m_tRect.right - m_tRect.left) / 2 + m_tRect.left, m_tRect.bottom);
		LineTo(_hDC, m_tRect.left, m_tRect.top);
	}
	else if (m_eType == ENEMY::ENEMY2)
	{
		Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}

void CMonster::Release()
{
}

void CMonster::CreateMonBullet()
{
	//CObj* pObj = nullptr;
	//pObj = CObjMgr::getInstance()->ObjPooling(OBJ::BOSSBULLET);
	//if (!pObj)
	//{
	//	pObj = CAbstractFactory<여기MonBullet구현하고 추가>::CreateObj(m_tInfo.fX, m_tInfo.fY);
	//	CObjMgr::getInstance()->getList(OBJ::BOSSBULLET).emplace_back(pObj);
	//}
}