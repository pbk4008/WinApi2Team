#include "framework.h"
#include "MainGraphic.h"
#include "Mouse_Edit.h"
#include "Button_Edit.h"


MainGraphic::MainGraphic()
{
}

MainGraphic::~MainGraphic()
{
	Release();
}

void MainGraphic::Initialize()
{
	m_hDC = GetDC(g_hWnd);
	m_MemDC = CreateCompatibleDC(m_hDC);
	m_hBit = CreateCompatibleBitmap(m_hDC,WINCX,WINCY);
	m_hOldBit = (HBITMAP)SelectObject(m_MemDC, m_hBit);

	CObj_Edit* pObj;
	pObj = new CMouse_Edit;
	RECT rc = { 300,100,700,500 };
	pObj->Initialize();
	dynamic_cast<CMouse_Edit*>(pObj)->setBoard(rc);
	CObjMgr_Edit::getInstance()->AddObj(EDIT_OBJ::MOUSE,pObj);

	pObj = new CButton_Edit(BUTTON::REMOVE);
	pObj->Initialize();
	dynamic_cast<CButton_Edit*>(pObj)->setPos(EDITWINCX*1/4,600);
	CObjMgr_Edit::getInstance()->AddObj(EDIT_OBJ::BUTTON, pObj);
	pObj = new CButton_Edit(BUTTON::SAVE);
	pObj->Initialize();
	dynamic_cast<CButton_Edit*>(pObj)->setPos(EDITWINCX * 3 / 4, 600);
	CObjMgr_Edit::getInstance()->AddObj(EDIT_OBJ::BUTTON, pObj);


}

void MainGraphic::Update()
{
	CObjMgr_Edit::getInstance()->Update();

	CCollisionMgr::CollisionRect(*CObjMgr_Edit::getInstance()->getList(EDIT_OBJ::MOUSE), *CObjMgr_Edit::getInstance()->getList(EDIT_OBJ::BUTTON));
}

void MainGraphic::Render()
{
	Rectangle(m_MemDC,0, 0, EDITWINCX, EDITWINCY);
	Rectangle(m_MemDC,300, 100, 700, 500);
	CObjMgr_Edit::getInstance()->Render(m_MemDC);
	CPosMgr_Edit::getInstance()->Render(m_MemDC);
	BitBlt(m_hDC, 0, 0, EDITWINCX, EDITWINCY, m_MemDC, 0, 0, SRCCOPY);
}

void MainGraphic::Release()
{
	CObjMgr_Edit::DestroyInstance();
	CPosMgr_Edit::DestroyInstance();

	SelectObject(m_MemDC, m_hOldBit);
	DeleteObject(m_hOldBit);
	DeleteDC(m_MemDC);
	ReleaseDC(g_hWnd,m_hDC);
}
