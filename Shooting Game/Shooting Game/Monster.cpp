#include "framework.h"
#include "Monster.h"
#include "MonBullet.h"

CMonster::CMonster() : m_eType(ENEMY::TYPE_END), m_bIsSpawn(false), m_fPosinDis(0.f), m_eCurPattern(ENEMY::PATTERN_END), m_ePattern(ENEMY::PATTERN_END)
	, m_bulletDelayTime(0), m_eDir(ENEMY::DIR_END)
{	
	ZeroMemory(&m_tHitBox, sizeof(m_tHitBox));
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

	m_bPollingCheck = true;

	if (!m_bIsSpawn)
	{
		m_tInfo.fX = -50.f;
		m_tInfo.fY = -50.f;
	}

	m_fPosinDis = 50.f;
	m_fSpeed = 3.f;

	m_fAngle = -90.f;
	m_pTarget = CObjMgr::getInstance()->getPlayer();

	SetPattern(ENEMY::PATTERN_1);
}

void CMonster::LateInit()
{	
}

int CMonster::Update()
{
	if (m_bDead)
		return EVENT::DEAD;
	
	if (m_pCollisionTarget)
	{
		m_pCollisionTarget = nullptr;
	}

	if (m_eType == ENEMY::ENEMY_1 && m_eDir == ENEMY::BOTTOM)
	{
		m_tInfo.fY += m_fSpeed;
		m_tHitBox.left = m_tInfo.fX - 10;
		m_tHitBox.right = m_tInfo.fX + 10;
		m_tHitBox.top = m_tInfo.fY - 10;
		m_tHitBox.bottom = m_tInfo.fY + 10;
	}

	if (m_eType == ENEMY::ENEMY_1 && m_eDir == ENEMY::RIGHT)
	{
		m_tInfo.fX += m_fSpeed;
		m_tHitBox.left = m_tInfo.fX - 10;
		m_tHitBox.right = m_tInfo.fX + 10;
		m_tHitBox.top = m_tInfo.fY - 10;
		m_tHitBox.bottom = m_tInfo.fY + 10;
	}

	if (m_eType == ENEMY::ENEMY_1 && m_eDir == ENEMY::LEFT)
	{
		m_tInfo.fX -= m_fSpeed;
		m_tHitBox.left = m_tInfo.fX - 10;
		m_tHitBox.right = m_tInfo.fX + 10;
		m_tHitBox.top = m_tInfo.fY - 10;
		m_tHitBox.bottom = m_tInfo.fY + 10;
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

	PlayPattern(ENEMY::PATTERN_1);
	return EVENT::NOEVENT;
}

void CMonster::LateUpdate()
{
	m_tPosin.x = (LONG)(m_tInfo.fX + cosf(m_fAngle * PI / 180.f) * m_fPosinDis);
	m_tPosin.y = (LONG)(m_tInfo.fY - sinf(m_fAngle * PI / 180.f) * m_fPosinDis);

	setAngle(m_fAngle);

	RectUpdate();
	if (m_tRect.left <= 0
		|| m_tRect.right >= WINCX
		|| m_tRect.top <= 0
		|| m_tRect.bottom >= WINCY)
	{
		m_bDead = true;	
		setPos(m_tInfo.fX, 1200);
	}	
}

void CMonster::Render(HDC _hDC)
{	
	if (m_bDead)
		return;

	if (m_eType == ENEMY::ENEMY_1)
	{	
		MoveToEx(_hDC, m_tRect.left, m_tRect.top, nullptr);
		LineTo(_hDC, m_tRect.right, m_tRect.top);
		LineTo(_hDC, (m_tRect.right - m_tRect.left) / 2 + m_tRect.left, m_tRect.bottom);
		LineTo(_hDC, m_tRect.left, m_tRect.top);		
		
		RendPosin(_hDC);

		Rectangle(_hDC, m_tHitBox.left, m_tHitBox.top, m_tHitBox.right, m_tHitBox.bottom);
	}
	else if (m_eType == ENEMY::ENEMY_2)
	{
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

inline void CMonster::SetPattern(ENEMY::PATTERN _pattern)
{
	SetEnemy(ENEMY::ENEMY_1);
	m_eCurPattern = _pattern;
	m_ePattern = _pattern;
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
		pObj = CAbstractFactory<CMonBullet>::CreateObj(_x, _y, m_fAngle);
		CObjMgr::getInstance()->getList(OBJ::MONBULLET).emplace_back(pObj);
	}
}

void CMonster::PlayPattern(ENEMY::PATTERN _type)
{
	switch (m_eCurPattern)
	{
	case ENEMY::PATTERN_1:
		if (m_bulletDelayTime + 1000 <= GetTickCount())
		{
			m_bulletDelayTime = GetTickCount();
			CreateMonBullet(m_tPosin.x, m_tPosin.y);
		}
		break;
	}
}

