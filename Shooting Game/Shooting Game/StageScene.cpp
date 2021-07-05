#include "framework.h"
#include "StageScene.h"
#include "CollisionMgr.h"

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
	
}

void CStageScene::Release()
{
	m_ObjMgr->SceneObjectRemove(SCENE::STAGE1);
}
