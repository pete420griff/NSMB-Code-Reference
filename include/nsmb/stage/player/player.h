#pragma once
#include "playerbase.h"
#include "misc.h"


class Door;



class Player : public PlayerBase
{

public:

	typedef bool(Player::*StateFunction)();

	Door* door;
	Door* bossDoor;
	s32* unk7CC;
	s32* unk7D0;

	LineSensorH topSensor;
	LineSensorH botSensor;
	LineSensorV sideSensor;
	LineSensorH unk804;

	ActiveCollider slidingCollider;
	PendulumController pendulum;
	Class212f724 unk8E0;
	ProgressBarObject progressBarObject;

	Vec3s unk914;
	Vec3s unk920;

	Vec3 unk92C;
	Vec3 unk93C;
	Vec3 unk94C;

	Vec2 unk95C;
	Vec2 unk968;
	Vec2 unk974;

	StateFunction moveState; // TODO: better name
	StateFunction unk988;
	StateFunction deathState; // TODO: better name
	StateFunction unk998; // TODO: better name
	StateFunction metaState; // TODO: better name

	u32 modelFrameOrigin;
	u32 modelBlendFlag;

	u32 zLayer;
	u32 headAnimID;
	u32 unk9B8;
	u32 unk9BC;
	u32 prevAnimID;

	u32 unk9C4; // platform bitfield?
	u32 unk9C8[6];

	u32 unk9E0[8]; // various emitter IDs
	u32 unkA00[41]; // more emitter IDs

	u32 unkAA4[7];

	u32 unkAC0[3];
	u32 unkACC[3];

	fx32 modelAnimSpeed;
	u32 powerupScaleStep;
	fx32 modelScale;
	u32 unkAE4[4];
	u32 unkAF4[7];
	u32 unkB10; // collider speed X
	u32 unkB14; // chunk position X
	u32 unkB18;
	u32 unkB1C;
	u32 unkB20;
	u32 unkB24;
	u32 unkB28;
	u32 unkB2C;
	u32 unkB30;
	u32 unkB34;
	u32 unkB38;
	u32 unkB3C;
	u32 unkB40;
	u32 unkB44;
	u32 unkB48;
	u32 unkB4C;

	u16 animEndTrigger; // when the current animation frame reaches this value, an action is triggered
	u16 prevDirection; // jump keys pressed
	u16 unkB54; // rope related
	u16 unkB56; // padding?

	u32 unkB58[2];
	s16 cannonTimer;
	s16 unkB62;
	u32 unkB64;
	s16 deathTimer;
	u16 unkB6A;
	u32 unkB6C;
	u16 unkB70;
	u16 unkB72;
	u32 unkB74;
	u16 unkB78; // "timer"
	u16 modelAngle; // "spriteCollisionAngle"
	u16 unkB7C[2];
	u16 unkB80; // "groundPoundRotateTimer"
	u16 unkB82[9];
	u32 unkB94;

	s16 lookAtRotation;
	u16 prevAnimFrame;

	u8 unkB9C;
	u8 modelID;
	u8 unkB9E; // "moveStateMode"
	u8 unkB9F; // "notInPipeCannon"

	u8 consecutiveJumps;
	u8 jumpVariation;

	u8 unkBA2;
	u8 unkBA3;
	u8 unkBA4;
	u8 turnVerticalVelocityStep;
	u8 powerupChangeStep;
	u8 powerupScaleTimer;
	u8 unkBA8;
	u8 unkBA9;
	u8 unkBAA;
	u8 unkBAB;
	u8 unkBAC;
	u8 deathStateMode;
	u8 holdingItemFlag;
	u8 currentModel;

	u8 unkBB0[6];

	u8 textureID;

	u8 runKeyTimer; // goes from 10 to 0
	u8 pipeExitTimer; // goes from 8 to 0, once the player has fully exited the pipe
	u8 unkBB9;
	u8 carryKeyTimer; // goes from 8 to 0

	u8 unkBBB; // "walkRight"
	u8 unkBBC; // "walkRight"
	u8 unkBBD;
	u8 unkBBE;
	u8 unkBBF;
	u8 megaParticlesTimer;
	u8 unkBC1;
	u8 unkBC2;
	u8 unkBC3; // "slowLedgeJumpMaybe"
	u8 unkBC4; // "groundpoundRelated"
	u8 unkBC5; // "walkLeftCounter"
	u8 unkBC6; // "walkRightCounter"
	u8 unkBC7;
	u8 groundPoundTimer; // goes from 0 to 3
	bool groundPoundFlag;
	u8 unkBCA;
	bool lookAtInProgress; // set to true when "LookingAtTarget" is enabled and the player's head rotation is being calculated

	
	// 021006AC
	void setMovementState(bool (Player::*func)(s32), s32 args = 0);

	// 02120BB8
	void setAnimation(u32 id, u16 startFrame, u32 unk1, fx32 speed, u16 unk2);

	// 021209E0
	void setAnimationSpeed(fx32 speed);

	// 02120A24
	void updateAnimation();

	// 02104C9C
	void tryUnlinkActor(); // unlink actor if something is already linked

	// 02104CCC
	void unlinkActor(); // unlink actor with no checks

	// 0211F34C
	void freeze(bool lookAtBoss);

	// 0211F2EC
	void unfreeze();


	//
	Player();

	//D0:
	//D1:
	virtual ~Player();
};