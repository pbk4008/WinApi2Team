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
};
#endif

