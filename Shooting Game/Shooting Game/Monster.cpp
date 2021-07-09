#include "framework.h"
#include "Monster.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}

void CMonster::Initialize()
{
	m_tInfo.iCX = 60;
	m_tInfo.iCY = 60;
	m_tInfo.fX = 300.f;
	m_tInfo.fY = 300.f;

	m_fSpeed = 5.f;

}

void CMonster::LateInit()
{
}

int CMonster::Update()
{
	if (m_bDead)
		return EVENT::DEAD;




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
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release()
{
}
