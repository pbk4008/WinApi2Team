#include "framework.h"
#include "StartScene.h"
#include "Button.h"
#include "Mouse.h"
#include "CollisionMgr.h"
#include "BackGround.h"

CStartScene::CStartScene()
{
}

CStartScene::~CStartScene()
{
	Release();
}

void CStartScene::Initialize()
{
	if(!m_ObjMgr)
		m_ObjMgr = CObjMgr::getInstance();
	CObj* pBack = CAbstractFactory<CBackGround>::CreateObj();
	pBack->setPos(800, 100);
	dynamic_cast<CBackGround*>(pBack)->setSize(200, 200);
	dynamic_cast<CBackGround*>(pBack)->setGraphic(L"../Data/Sun");
	dynamic_cast<CBackGround*>(pBack)->setType(OBJ::SUN);
	m_ObjMgr->AddObject(OBJ::BACKGROUND, pBack);

	pBack = CAbstractFactory<CBackGround>::CreateObj();
	pBack->setPos(700, 300);
	dynamic_cast<CBackGround*>(pBack)->setSize(200, 100);
	dynamic_cast<CBackGround*>(pBack)->setGraphic(L"../Data/Cloud");
	dynamic_cast<CBackGround*>(pBack)->setType(OBJ::CLOUD);
	dynamic_cast<CBackGround*>(pBack)->setDir(DIRECTION::RIGHT);
	m_ObjMgr->AddObject(OBJ::BACKGROUND, pBack);

	pBack = CAbstractFactory<CBackGround>::CreateObj();
	pBack->setPos(800, 330);
	dynamic_cast<CBackGround*>(pBack)->setSize(200, 100);
	dynamic_cast<CBackGround*>(pBack)->setGraphic(L"../Data/Cloud");
	dynamic_cast<CBackGround*>(pBack)->setType(OBJ::CLOUD);
	dynamic_cast<CBackGround*>(pBack)->setDir(DIRECTION::RIGHT);
	m_ObjMgr->AddObject(OBJ::BACKGROUND, pBack);

	pBack = CAbstractFactory<CBackGround>::CreateObj();
	pBack->setPos(100, 500);
	dynamic_cast<CBackGround*>(pBack)->setSize(200, 100);
	dynamic_cast<CBackGround*>(pBack)->setGraphic(L"../Data/Cloud");
	dynamic_cast<CBackGround*>(pBack)->setType(OBJ::CLOUD);
	dynamic_cast<CBackGround*>(pBack)->setDir(DIRECTION::LEFT);
	m_ObjMgr->AddObject(OBJ::BACKGROUND, pBack);


	pBack = CAbstractFactory<CBackGround>::CreateObj();
	pBack->setPos(800, 800);
	dynamic_cast<CBackGround*>(pBack)->setSize(100, 100);
	dynamic_cast<CBackGround*>(pBack)->setGraphic(L"../Data/Bird");
	dynamic_cast<CBackGround*>(pBack)->setType(OBJ::BIRD);
	dynamic_cast<CBackGround*>(pBack)->setDir(DIRECTION::RIGHT);
	m_ObjMgr->AddObject(OBJ::BACKGROUND, pBack);

	pBack = CAbstractFactory<CBackGround>::CreateObj();
	pBack->setPos(100, 200);
	dynamic_cast<CBackGround*>(pBack)->setSize(100, 100);
	dynamic_cast<CBackGround*>(pBack)->setGraphic(L"../Data/Bird1");
	dynamic_cast<CBackGround*>(pBack)->setType(OBJ::BIRD);
	dynamic_cast<CBackGround*>(pBack)->setDir(DIRECTION::LEFT);
	m_ObjMgr->AddObject(OBJ::BACKGROUND, pBack);

	m_ObjMgr->AddObject(OBJ::BUTTON, CreateButton(BUTTON::START,WINCX/4,WINCY*2/3));
	m_ObjMgr->AddObject(OBJ::BUTTON, CreateButton(BUTTON::QUIT,WINCX*3/4,WINCY*2/3));
	CObj* pObj = CAbstractFactory<CMouse>::CreateObj();
	m_ObjMgr->AddObject(OBJ::MOUSE, pObj);
}

void CStartScene::LateInit()
{
	m_ObjMgr->LateInit();
}

int CStartScene::Update()
{
	int iEvent = m_ObjMgr->Update();
	if (iEvent == EVENT::GAME_START)
	{
		return SCENE_STATE::CHANGE;
	}
	return SCENE_STATE::NO;
}

void CStartScene::LateUpdate()
{
	m_ObjMgr->LateUpdate();
	CCollisionMgr::CollisionRect(CObjMgr::getInstance()->getList(OBJ::MOUSE), CObjMgr::getInstance()->getList(OBJ::BUTTON));
}

void CStartScene::Render(HDC _hDC)
{
	CreateBackGround(_hDC);
	m_ObjMgr->Render(_hDC);
}

void CStartScene::Release()
{
	m_ObjMgr->SceneObjectRemove(SCENE::START);
}

CObj* CStartScene::CreateButton(BUTTON::NAME _eName,float _x, float _y)
{
	CObj* pObj = CAbstractFactory<CButton>::CreateObj(_x, _y);
	dynamic_cast<CButton*>(pObj)->setName(_eName);
	return pObj;
}

void CStartScene::CreateBackGround(HDC _hDC)
{
	HBRUSH hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 191, 255));
	HBRUSH hObj = (HBRUSH)SelectObject(_hDC, hBrush);
	Rectangle(_hDC, 0, 0, WINCX, WINCY);
	SelectObject(_hDC, hObj);
	DeleteObject(hBrush);
}
