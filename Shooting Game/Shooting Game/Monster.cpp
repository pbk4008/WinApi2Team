#include "framework.h"
#include "Monster.h"
#include "MonBullet.h"

CMonster::CMonster() : m_eType(ENEMY::TYPE_END), m_bIsSpawn(false), m_fPosinDis(0.f), m_eCurPattern(ENEMY::PATTERN_END), m_ePattern(ENEMY::PATTERN_END)
	, m_bulletDelayTime(0)
{
	ZeroMemory(&m_tPosin, sizeof(m_tPosin));
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_tInfo.iCX = 60;
	m_tInfo.iCY = 60;

	m_fPosinDis = 50.f;
	m_fSpeed = 3.f;

	m_fAngle = -90.f;

	SetEnemy(ENEMY::ENEMY_1);	
	m_eCurPattern = ENEMY::PATTERN_1;
	SetPattern(ENEMY::PATTERN_1);
}

void CMonster::LateInit()
{

}

int CMonster::Update()
{
	if (m_bDead)
		return EVENT::DEAD;

	if (m_eType == ENEMY::ENEMY_1)
	{
		m_tInfo.fY += m_fSpeed;
	}	

	setTarget(CObjMgr::getInstance()->getPlayer());

	if (m_pTarget)
	{
		float	fX = m_pTarget->getInfo().fX - m_tInfo.fX;
		float	fY = m_pTarget->getInfo().fY - m_tInfo.fY;
		float	fDia = sqrtf(fX * fX + fY * fY);

		float	fRad = acosf(fX / fDia);
		m_fAngle = fRad * 180.f / PI;

		if (m_pTarget->getInfo().fY >= m_tInfo.fY)
			m_fAngle *= -1.f;
	}

	m_tPosin.x = (LONG)(m_tInfo.fX + cosf(m_fAngle * PI / 180.f) * m_fPosinDis);
	m_tPosin.y = (LONG)(m_tInfo.fY - sinf(m_fAngle * PI / 180.f) * m_fPosinDis);
	

	PlayPattern(ENEMY::PATTERN_1);	
	
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
	if (m_eType == ENEMY::ENEMY_1)
	{
		MoveToEx(_hDC, m_tRect.left, m_tRect.top, nullptr);
		LineTo(_hDC, m_tRect.right, m_tRect.top);
		LineTo(_hDC, (m_tRect.right - m_tRect.left) / 2 + m_tRect.left, m_tRect.bottom);
		LineTo(_hDC, m_tRect.left, m_tRect.top);

		if (m_bIsSpawn)
		{
			RendPosin(_hDC);
		}

		//Rectangle(_hDC, m_tPosin.x -5.f, m_tPosin.y +5.f , m_tPosin.x +5.f, m_tPosin.y + 35.f);
	}
	else if (m_eType == ENEMY::ENEMY_2)
	{
		//Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		MoveToEx(_hDC, m_tRect.left, m_tRect.top, nullptr);
		LineTo(_hDC, m_tRect.right, m_tRect.top);
		LineTo(_hDC, (m_tRect.right - m_tRect.left) / 2 + m_tRect.left, m_tRect.bottom);
		LineTo(_hDC, m_tRect.left, m_tRect.top);
		Rectangle(_hDC, m_tRect.left + 20, m_tRect.top + 20, m_tRect.left + 10, m_tRect.bottom + 5);
		Rectangle(_hDC, m_tRect.left + 40, m_tRect.top + 20, m_tRect.left + 50, m_tRect.bottom + 5);
	}
}

void CMonster::Release()
{
	SAFE_DELETE_ARR(m_PolygonList);
	SAFE_DELETE_ARR(m_iPosDisArr);
}

void CMonster::RendPosin(HDC _hDC)
{
	MoveToEx(_hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	LineTo(_hDC, m_tPosin.x, m_tPosin.y); 
}

void CMonster::CreateMonBullet(float _x, float _y)
{
	CObj* pObj = nullptr;
	pObj = CObjMgr::getInstance()->ObjPooling(OBJ::MONBULLET, this);
	if (!pObj)
	{
		pObj = CAbstractFactory<CMonBullet>::CreateObj(_x, _y);
		CObjMgr::getInstance()->getList(OBJ::MONBULLET).emplace_back(pObj);
	}
}

void CMonster::PlayPattern(ENEMY::PATTERN _type)
{
	switch (m_eCurPattern)
	{
	case ENEMY::PATTERN_1:
		//m_tInfo.fX += m_fSpeed;
		if (m_bulletDelayTime + 1000 <= GetTickCount())
		{
			m_bulletDelayTime = GetTickCount();
			CreateMonBullet(m_tPosin.x, m_tPosin.y);
		}
		break;
	}
}
