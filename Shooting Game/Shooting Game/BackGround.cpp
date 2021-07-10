#include "framework.h"
#include "BackGround.h"

CBackGround::CBackGround()
{
}

CBackGround::~CBackGround()
{
	Release();
}
void CBackGround::CheckSize(int* _iCX, int* _iCY)
{
	int iMinX = 0, iMaxX = 0, iMinY = 0, iMaxY = 0;

	for (auto pos : m_PosList)
	{
		if (pos->x < iMinX || iMinX == 0)
		{
			iMinX = pos->x;
		}
		if (pos->x > iMaxX || iMaxX == 0)
		{
			iMinX = pos->x;
		}
		if (pos->y < iMinY || iMinY == 0)
		{
			iMinY = pos->y;
		}
		if (pos->x > iMaxY || iMaxY == 0)
		{
			iMinY = pos->y;
		}
	}
	*_iCX = iMaxX - iMinX;
	*_iCY = iMaxY - iMinY;
}
void CBackGround::Lode_Pos(TCHAR _strName)
{
	TCHAR szBuff[64] = {};
	swprintf_s(szBuff, L"../Data/%s", _strName);
	HANDLE hFile = (HANDLE)CreateFile(szBuff, GENERIC_READ, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return;
	}
	DWORD dwByte = 0;
	POINT pt = {};
	while (true)
	{
		ReadFile(hFile, &pt, sizeof(POINT), &dwByte, nullptr);
		if (dwByte == 0)
			break;
		m_PosList.emplace_back(pt);
	}
	CloseHandle(hFile);
}

void CBackGround::UpdatePos()
{
	int iCX = 0, iCY = 0;
	CheckSize(&iCX, &iCY);
	

}
