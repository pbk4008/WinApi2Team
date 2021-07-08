#include "framework.h"
#include "StartScene.h"
#include "Button.h"
#include "Mouse.h"
#include "CollisionMgr.h"

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
