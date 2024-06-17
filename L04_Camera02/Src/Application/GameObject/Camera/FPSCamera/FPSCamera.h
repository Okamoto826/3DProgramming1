#pragma once
#include "../CameraBase.h"

class FPSCamera : public CameraBase
{
public:
	FPSCamera() {}
	virtual ~FPSCamera()	override {}

	void Init()					override;
	void Update()				override;

private:

	void UpdateRotateMouse();

	POINT m_FixMousePos;
};