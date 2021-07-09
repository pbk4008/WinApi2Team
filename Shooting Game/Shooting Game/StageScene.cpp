#include "framework.h"
#include "StageScene.h"
#include "Stag1Boss.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "Monster.h"

CStageScene::CStageScene() : m_iPlayTime(0), m_iControlTime(0), m_dwPlayTime(0)
{
}

CStageScene::~CStageScene()
{
	Release();
}

void CStageScene::Initialize()
{
	m_ObjMgr = CObjMgr::getInstance();
	m_ObjMgr->AddObject(OBJ::BOSS, CAbstractFactory<CStag1Boss>::CreateObj(100, 200));
	m_ObjMgr->AddObject(OBJ::PLAYER, CAbstractFactory<CPlayer>::CreateObj((float)WINCX/2, 500.f));
	for (int i = 0; i < 20; ++i)
	{
		m_ObjMgr->AddObject(OBJ::MONSTER, CAbstractFactory<CMonster>::CreateObj(1200 + i * 50, 600));
	}
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

	if (m_dwPlayTime + 10 < GetTickCount())
	{
		++m_iControlTime;
		if (m_iControlTime > 63)
		{
			++m_iPlayTime;
			m_iControlTime = 0;
		}

		TCHAR	szPlayTime[32] = L"";
		swprintf_s(szPlayTime, L"PlayTime: %d", m_iPlayTime);
		TextOut(_hDC, 460, 10, szPlayTime, lstrlen(szPlayTime));

		m_dwPlayTime = GetTickCount();
	}
}

void CStageScene::Release()
{
	m_ObjMgr->SceneObjectRemove(SCENE::STAGE1);
}
