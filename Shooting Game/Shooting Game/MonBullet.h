#pragma once
#include "Obj.h"
class CMonBullet :
    public CObj
{
public: explicit CMonBullet();
public:	virtual ~CMonBullet();

public:	virtual void Initialize() override;
public: virtual void LateInit() override;
public: virtual int Update() override;
public: virtual void LateUpdate() override;
public: virtual void Render(HDC _hDC) override;
public: virtual void Release() override;



};

