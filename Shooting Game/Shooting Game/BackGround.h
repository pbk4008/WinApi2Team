#pragma once
#include "Obj.h"
class CBackGround :
    public CObj
{
private:
    float m_fSettingX;
    float m_fSettingY;
    DWORD m_dwCurTime;
    OBJ::BACK m_eType;
    DIRECTION::DIR m_eDir;
public:
    CBackGround();
    virtual ~CBackGround();
public:
    virtual void Initialize() override;
    virtual void LateInit() override;
    virtual int Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;
public:
    inline void setSize(int _icx, int _icy) { m_tInfo.iCX = _icx; m_tInfo.iCY = _icy; };
    inline void setDir(DIRECTION::DIR _eDir) { m_eDir = _eDir; }
    inline void setType(OBJ::BACK _eType) { m_eType = _eType; }
private:
    void setColor(HBRUSH& _hBrush);
public:
    void setGraphic(const TCHAR* _str);

};

