#pragma once

#include "view.hpp"
#include <nsmb/core/math/vector.hpp>


//ov8
class PerspView : public View
{
public:

	Vec3 target;
	Vec3 position;
	Vec3 up;
	Vec3s rotation;

	//D0:0218cd58
	//D1:0218cd00
	virtual ~PerspView();

};
NTR_SIZE_GUARD(PerspView, 0x108);
