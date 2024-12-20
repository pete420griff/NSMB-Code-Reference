#pragma once

#include <nsmb/game/stage/entity.hpp>
#include <nsmb/game/physics/collider.hpp>
#include "chainchomplogrenderer.hpp"

// vtable at 0217556C (ov57)
class ChainChompLog : public StageEntity
{
public:

	// Do NOT change
	static constexpr auto MaxChainChompCount = 1;

	using StateFunction = bool(ChainChompLog::*)();

	enum class State : u8
	{
		Inactive,
		Active,
		Destroyed
	};

	enum class GroundPoundType : u32
	{
		None,
		Normal,
		Mega
	};

	enum class DamageType : u8
	{
		Normal,
		Mega
	};


	// D0: 02172868
	// D1: 021727F8
	virtual ~ChainChompLog();

	// 021729CC
	s32 onCreate() override;
	// 021728E0
	s32 onDestroy() override;
	// 02172918
	s32 onRender() override;
	// 0217306C
	bool onPrepareResources() override;

	// 02172994
	bool updateMain() override;

	// 02172EB8
	void spawnChainChomps(u32 count);
	// 02172E68
	void despawnChainChomps();
	// 02172E18
	void releaseChainChomps();
	// 02172D9C
	GroundPoundType checkPlayerGroundPounding() const;
	// 02172D04
	void updateColliderRect();

	// 02172F88
	bool switchState(StateFunction function);
	// 02172F4C
	void updateState();

	// 02172C7C
	bool mainState();
	// 02172B30
	bool poundedState();

	// 0217307C
	static bool loadResources();

	static constexpr u16 ObjectID = 44;

	static constexpr u16 UpdatePriority = ObjectID;
	static constexpr u16 RenderPriority = 58;

	// 02175560
	static const ActorProfile profile;


	Collider collider;

	ChainChompLogRenderer log;

	u32 chainChompGUIDs[MaxChainChompCount];
	u32 chainChompCount;

	StateFunction updateFunction;

	fx32 currentHeight;
	fx32 targetHeight;

	s8 updateStep;
	u8 damageLevel;
	State activeState;
	DamageType damageType;


#if NTR_EXT_EXISTS(ChainChompLog)
	#include NTR_EXT_INCLUDE(ChainChompLog)
#endif

};
#if !NTR_EXT_EXISTS(ChainChompLog)
NTR_SIZE_GUARD(ChainChompLog, 0x48C);
#endif

static_assert(ChainChompLog::MaxChainChompCount == 1, "Invalid ChainChomp count specified in ChainChompLog");
