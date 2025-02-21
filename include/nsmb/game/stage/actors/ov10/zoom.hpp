#pragma once

#include <nsmb/game/stage/entity.hpp>

// vtable at 02125094 (ov10)
class Zoom : public StageEntity
{
public:

	// D0: 020D7E5C
	// D1: 020D7E00
	virtual ~Zoom();

	// 020D7FE8
	s32 onCreate() override;
	// 020D7FE0
	s32 onDestroy() override;
	// 020D7EC0
	s32 onUpdate() override;
	// 020D7FD4
	s32 onRender() override;
	// 020D7FDC
	void onCleanupResources() override;

	static constexpr u16 ObjectID = 0x31;

	static constexpr u16 UpdatePriority = ObjectID;
	static constexpr u16 RenderPriority = 0x3F;

	// 02125088
	static const ActorProfile profile;


	fx32 zoomLeft;
	fx32 zoomRight;
	fx32 triggerLeft;
	fx32 triggerRight;
	fx32 triggerHeight;
	fx32 triggerWidth;
	fx32 zoomTime;
	u32 playerZoomState[2];


#if NTR_EXT_EXISTS(Zoom)
	#include NTR_EXT_INCLUDE(Zoom)
#endif

};
#if !NTR_EXT_EXISTS(Zoom)
NTR_SIZE_GUARD(Zoom, 0x418);
#endif
