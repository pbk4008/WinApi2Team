#pragma once
#ifndef __STAGESCENE_H__
#define __STAGESCENE_H__
#include "Scene.h"
class CStageScene :
    public CScene
{
public:
    CStageScene();
    virtual ~CStageScene();
public:
    virtual void Initialize() override;
    virtual void LateInit() override;
    virtual int Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;

public: void MonPattern(ENEMY::PATTERN _pattern);

private: int m_iPlayTime;
private: int m_iControlTime;
private: DWORD m_dwPlayTime;

};
#endif

