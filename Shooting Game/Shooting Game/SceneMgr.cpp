#include "framework.h"
#include "SceneMgr.h"
#include "Scene.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;
CSceneMgr::CSceneMgr():m_bChange(false)
{
	m_SceneVector.reserve(SCENE::END);
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::LateInit()
{
	m_SceneVector[m_eCurrentScene]->LateInit();
}

void CSceneMgr::Update()
{
	m_bChange = false;
	int iEvent=m_SceneVector[m_eCurrentScene]->Update();
	if (iEvent == SCENE_CHANGE)
	{
		SAFE_DELETE(m_SceneVector[m_eCurrentScene - 1]);
		m_bChange = true;
	}
}

void CSceneMgr::LateUpdate()
{
	if (!m_bChange)
		m_SceneVector[m_eCurrentScene]->LateUpdate();
}

void CSceneMgr::Render(HDC _hDC)
{
	if(!m_bChange)
		m_SceneVector[m_eCurrentScene]->Render(_hDC);
}

void CSceneMgr::Release()
{
	for_each(m_SceneVector.begin(), m_SceneVector.end(), Safe_Delete<CScene*>);
	m_SceneVector.clear();
}

CSceneMgr* CSceneMgr::getInstance()
{
	if (!m_pInstance)
		m_pInstance = new CSceneMgr;
	return m_pInstance;
}

void CSceneMgr::DestroyInstance()
{
	SAFE_DELETE(m_pInstance);
}
