#pragma once
#ifndef __MOUSE_H__
#define __MOUSE_H__
#include "Obj.h"
class CMouse :
    public CObj
{
public:
    CMouse();
    virtual ~CMouse();
public:
    // CObj��(��) ���� ��ӵ�
    virtual void Initialize() override;
    virtual void LateInit() override;
    virtual int Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;
};
#endif

