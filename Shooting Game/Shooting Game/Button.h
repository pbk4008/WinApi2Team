#pragma once
#ifndef __BUTTON_H__
#define __BUTTON_H__
#include "Obj.h"
class CButton :
    public CObj
{
private:
    BUTTON::NAME m_eName;
    TCHAR m_szText[32];
public:
    CButton();
    virtual ~CButton();
public:
    virtual void Initialize() override;
    virtual void LateInit() override;
    virtual int Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;
public:
    inline void setName(BUTTON::NAME _eName) { m_eName = _eName; }
public:
    inline BUTTON::NAME getButtonName() { return m_eName; }
};
#endif

