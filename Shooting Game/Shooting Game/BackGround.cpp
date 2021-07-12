#include "framework.h"
#include "BackGround.h"

CBackGround::CBackGround() : m_dwCurTime(0), m_eDir(DIRECTION::END)
{
}

CBackGround::~CBackGround()
{
	Release();
}

void CBackGround::Initialize()
{
	m_dwCurTime = GetTickCount();
	m_fSpeed = 3.f;
	m_bPollingCheck = true;
}

void CBackGround::LateInit()
{
	m_fSettingX = m_tInfo.fX;
	m_fSettingY = m_tInfo.fY;
}

int CBackGround::Update()
{
	if (m_bDead)
	{
		if (m_eScene == SCENE::STAGE1)
		{
			switch (m_eDir)
			{
			case DIRECTION::RIGHT:
			case DIRECTION::LEFT:
				m_fSettingY = rand() % WINCY;
				break;
			case DIRECTION::UP:
			case DIRECTION::DOWN:
				m_fSettingX = rand() % WINCX;
				break;
			}
		}

		m_tInfo.fX = m_fSettingX;
		m_tInfo.fY = m_fSettingY;
		m_bDead = false;
		return EVENT::DEAD;
	}
	switch (m_eDir)
	{
		case DIRECTION::RIGHT:
			m_tInfo.fX -= m_fSpeed;
			break;
		case DIRECTION::LEFT:
			m_tInfo.fX += m_fSpeed;
			break;
		case DIRECTION::UP:
			m_tInfo.fY += m_fSpeed;
			break;
		case DIRECTION::DOWN:
			m_tInfo.fY -= m_fSpeed;
			break;
	}
	return EVENT::NOEVENT;
}

void CBackGround::LateUpdate()
{
	RectUpdate();
	PosUpdate();
	switch (m_eDir)
	{
		case DIRECTION::LEFT:
			if (m_tRect.left >= WINCX)
			m_bDead = true;
			break;
		case DIRECTION::RIGHT:
			if (m_tRect.right <= 0)
				m_bDead = true;
			break;
		case DIRECTION::UP:
			if (m_tRect.top >= WINCY)
				m_bDead = true;
			break;
		case DIRECTION::DOWN:
			if (m_tRect.bottom<=0)
			m_bDead = true;
		break;
	}
}

void CBackGround::Render(HDC _hDC)
{
	HBRUSH hBrush;
	HBRUSH hObj;
	setColor(hBrush);
	hObj = (HBRUSH)SelectObject(_hDC, hBrush);
	Polygon(_hDC, m_PolygonList, m_PosList.size());
	SelectObject(_hDC, hObj);
	DeleteObject(hBrush);
}

void CBackGround::Release()
{
}

void CBackGround::setColor(HBRUSH& _hBrush)
{
	switch (m_eType)
	{
	case OBJ::CLOUD:
		_hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
		break;
	case OBJ::BIRD:
		_hBrush = (HBRUSH)CreateSolidBrush(RGB(0,0,0));
		break;
	case OBJ::SUN:
		_hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		break;
	case OBJ::HUMAN:
		_hBrush = (HBRUSH)CreateSolidBrush(RGB(251, 206, 177));//»ì»ö
		break;
	}
}

void CBackGround::setGraphic(const TCHAR* _str)
{
	LoadPoint(_str);
	SetGraphicPos();
	SetPivot();
	m_PolygonList = new POINT[m_PosList.size()];
	for (int i = 0; i < m_PosList.size(); i++)
	{
		POINT pt = { m_PosList[i]->fX,m_PosList[i]->fY };
		m_PolygonList[i] = pt;
	}
	setDis();
}
