#include "framework.h"
#include "StageScene.h"
#include "Stag1Boss.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "Monster.h"

CStageScene::CStageScene()
{
}

CStageScene::~CStageScene()
{
	Release();
}

void CStageScene::Initialize()
{
	m_ObjMgr = CObjMgr::getInstance();
	//m_ObjMgr->AddObject(OBJ::BOSS, CAbstractFactory<CStag1Boss>::CreateObj(100, 200));
	m_ObjMgr->AddObject(OBJ::PLAYER, CAbstractFactory<CPlayer>::CreateObj((float)WINCX/2, 500.f));
	m_ObjMgr->AddObject(OBJ::MONSTER, CAbstractFactory<CMonster>::CreateObj(300, 300));
}

void CStageScene::LateInit()
{
	m_ObjMgr->LateInit();
}

int CStageScene::Update()
{
	int iEvent=m_ObjMgr->Update();
	return SCENE_STATE::NO;
}

void CStageScene::LateUpdate()
{
	m_ObjMgr->LateUpdate();
}

void CStageScene::Render(HDC _hDC)
{
	m_ObjMgr->Render(_hDC);
	TCHAR szText[32] = {};
	swprintf_s(szText, L"Bullet : %d", CObjMgr::getInstance()->getList(OBJ::BOSSBULLET).size());
	TextOut(_hDC, 10, 10, szText, lstrlen(szText));
}

void CStageScene::Release()
{
	m_ObjMgr->SceneObjectRemove(SCENE::STAGE1);
}
