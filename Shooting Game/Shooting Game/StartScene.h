#pragma once
#ifndef __STARTSCENE_H__
#define __STARTSCENE_H__
#include "Scene.h"
class CStartScene :
    public CScene
{
public:
    CStartScene();
    virtual ~CStartScene();
public:
    virtual void Initialize() override;
    virtual void LateInit() override;
    virtual int Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;
private:
    CObj* CreateButton(BUTTON::NAME _eName, float _x, float _y);
};
#endif

