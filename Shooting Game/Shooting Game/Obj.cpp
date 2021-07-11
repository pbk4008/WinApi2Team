#include"framework.h"
#include "Obj.h"
CObj::CObj() : m_bNotDestroy(false), m_eScene(SCENE::END)
, m_pCollisionTarget(nullptr), m_bDead(false), m_fSpeed(0.f), m_bPollingCheck(false)
, m_pTarget(nullptr), m_iMaxHp(0),m_iCurrentHp(0),m_iAtk(0)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tRect, sizeof(m_tRect));
	ZeroMemory(&m_PolygonList, sizeof(POINT));
	ZeroMemory(&m_iPosDisArr, sizeof(DISINFO));
}

CObj::~CObj()
{
}

void CObj::setDis()
{
	m_iPosDisArr = new DISINFO[m_PosList.size()];
	for (int i = 0; i < m_PosList.size(); i++)
	{
		int iCX = abs(m_PolygonList[i].x - m_tInfo.fX);
		int iCY = abs(m_PolygonList[i].y - m_tInfo.fY);
		DISINFO argInfo = { iCX,iCY };
		m_iPosDisArr[i] = argInfo;
	}
}

void CObj::RectUpdate()
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.iCX >> 1));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.iCX >> 1));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.iCY >> 1));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.iCY >> 1));
}

void CObj::LoadPoint(const TCHAR* _str)
{
	HANDLE hFile = (HANDLE)CreateFile(_str, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, L"로드실패", L"실패", MB_OK);
		return;
	}
	DWORD dwByte = 0;

	while (true)
	{
		POS* argPos = new POS;
		ReadFile(hFile, argPos, sizeof(POS), &dwByte, nullptr);
		if (dwByte == 0)
			break;
		m_PosList.emplace_back(argPos);
	}
	CloseHandle(hFile);
}

void CObj::SetGraphicPos()
{
	int icx = CMathMgr::getHorizontal(m_PosList);
	int icy = CMathMgr::getVertical(m_PosList);

	for (auto pPos : m_PosList)
	{
		pPos->fX = (pPos->fX * m_tInfo.iCX) / icx;
		pPos->fY = (pPos->fY * m_tInfo.iCY) / icy;
	}
}

void CObj::SetPivot()
{
	int iMinX = 0;
	int iMaxX = 0;
	int iMinY = 0;
	int iMaxY = 0;
	for (auto pPos : m_PosList)
	{
		if (pPos->fX < iMinX || iMinX == 0)
			iMinX = pPos->fX;
		if (pPos->fX > iMaxX || iMaxX == 0)
			iMaxX = pPos->fX;
		if (pPos->fY < iMinY || iMinY == 0)
			iMinY = pPos->fY;
		if (pPos->fY > iMaxY|| iMaxY == 0)
			iMaxY = pPos->fY;
	}
	float iCenterX = float(iMinX + iMaxX) / 2.f;
	float iCenterY = float(iMinY + iMaxY) / 2.f;

	int iResX = iCenterX - m_tInfo.fX;
	int iResY = iCenterY - m_tInfo.fY;

	for (auto pPos : m_PosList)
	{
		pPos->fX -= iResX;
		pPos->fY -= iResY;
	}
}

void CObj::PosUpdate()
{
	for(int i=0; i< m_PosList.size(); i++)
	{
		if (m_PolygonList[i].x < m_tInfo.fX)
			m_PolygonList[i].x = m_tInfo.fX - m_iPosDisArr[i].iCX;
		if(m_PolygonList[i].x > m_tInfo.fX)
			m_PolygonList[i].x = m_tInfo.fX + m_iPosDisArr[i].iCX;
		if(m_PolygonList[i].y < m_tInfo.fY)
			m_PolygonList[i].y = m_tInfo.fY - m_iPosDisArr[i].iCY;
		if(m_PolygonList[i].y > m_tInfo.fY)
			m_PolygonList[i].y = m_tInfo.fY + m_iPosDisArr[i].iCY;
	}
}
