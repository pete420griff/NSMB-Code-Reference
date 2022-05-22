#pragma once
#include "nitro_if.h"
#include "nsmb/util.h"
#include "nsmb/math/vector.h"


extern "C" void PushCommand_impl(SNDCommandID command, u32 arg0, u32 arg1, u32 arg2, u32 arg3);


namespace SND {

	enum class StopFlags : u32
	{
		Sound = (1U << 0),
		Requests = (1U << 1),
	};

}

IMPL_ENUMCLASS_OPERATORS(SND::StopFlags);


//	Contains the functions used to play sounds in the game.
namespace SND {

	// 02088b54
	extern StopFlags stopFlags;


	__inline void soundOff() {
		stopFlags |= StopFlags::Sound;
	}

	__inline void soundOn() {
		stopFlags &= ~StopFlags::Sound;
	}

	__inline void requestsOff() {
		stopFlags |= StopFlags::Requests;
	}

	__inline void requestsOn() {
		stopFlags &= ~StopFlags::Requests;
	}


	
	constexpr inline u16 kPitchTable[SND_PITCH_TABLE_SIZE] = {
		0x0000, 0x003b, 0x0076, 0x00b2, 0x00ed, 0x0128, 0x0164, 0x019f,
		0x01db, 0x0217, 0x0252, 0x028e, 0x02ca, 0x0305, 0x0341, 0x037d,
		0x03b9, 0x03f5, 0x0431, 0x046e, 0x04aa, 0x04e6, 0x0522, 0x055f,
		0x059b, 0x05d8, 0x0614, 0x0651, 0x068d, 0x06ca, 0x0707, 0x0743,
		0x0780, 0x07bd, 0x07fa, 0x0837, 0x0874, 0x08b1, 0x08ef, 0x092c,
		0x0969, 0x09a7, 0x09e4, 0x0a21, 0x0a5f, 0x0a9c, 0x0ada, 0x0b18,
		0x0b56, 0x0b93, 0x0bd1, 0x0c0f, 0x0c4d, 0x0c8b, 0x0cc9, 0x0d07,
		0x0d45, 0x0d84, 0x0dc2, 0x0e00, 0x0e3f, 0x0e7d, 0x0ebc, 0x0efa,

		0x0f39, 0x0f78, 0x0fb6, 0x0ff5, 0x1034, 0x1073, 0x10b2, 0x10f1,
		0x1130, 0x116f, 0x11ae, 0x11ee, 0x122d, 0x126c, 0x12ac, 0x12eb,
		0x132b, 0x136b, 0x13aa, 0x13ea, 0x142a, 0x146a, 0x14a9, 0x14e9,
		0x1529, 0x1569, 0x15aa, 0x15ea, 0x162a, 0x166a, 0x16ab, 0x16eb,
		0x172c, 0x176c, 0x17ad, 0x17ed, 0x182e, 0x186f, 0x18b0, 0x18f0,
		0x1931, 0x1972, 0x19b3, 0x19f5, 0x1a36, 0x1a77, 0x1ab8, 0x1afa,
		0x1b3b, 0x1b7d, 0x1bbe, 0x1c00, 0x1c41, 0x1c83, 0x1cc5, 0x1d07,
		0x1d48, 0x1d8a, 0x1dcc, 0x1e0e, 0x1e51, 0x1e93, 0x1ed5, 0x1f17,

		0x1f5a, 0x1f9c, 0x1fdf, 0x2021, 0x2064, 0x20a6, 0x20e9, 0x212c,
		0x216f, 0x21b2, 0x21f5, 0x2238, 0x227b, 0x22be, 0x2301, 0x2344,
		0x2388, 0x23cb, 0x240e, 0x2452, 0x2496, 0x24d9, 0x251d, 0x2561,
		0x25a4, 0x25e8, 0x262c, 0x2670, 0x26b4, 0x26f8, 0x273d, 0x2781,
		0x27c5, 0x280a, 0x284e, 0x2892, 0x28d7, 0x291c, 0x2960, 0x29a5,
		0x29ea, 0x2a2f, 0x2a74, 0x2ab9, 0x2afe, 0x2b43, 0x2b88, 0x2bcd,
		0x2c13, 0x2c58, 0x2c9d, 0x2ce3, 0x2d28, 0x2d6e, 0x2db4, 0x2df9,
		0x2e3f, 0x2e85, 0x2ecb, 0x2f11, 0x2f57, 0x2f9d, 0x2fe3, 0x302a,

		0x3070, 0x30b6, 0x30fd, 0x3143, 0x318a, 0x31d0, 0x3217, 0x325e,
		0x32a5, 0x32ec, 0x3332, 0x3379, 0x33c1, 0x3408, 0x344f, 0x3496,
		0x34dd, 0x3525, 0x356c, 0x35b4, 0x35fb, 0x3643, 0x368b, 0x36d3,
		0x371a, 0x3762, 0x37aa, 0x37f2, 0x383a, 0x3883, 0x38cb, 0x3913,
		0x395c, 0x39a4, 0x39ed, 0x3a35, 0x3a7e, 0x3ac6, 0x3b0f, 0x3b58,
		0x3ba1, 0x3bea, 0x3c33, 0x3c7c, 0x3cc5, 0x3d0e, 0x3d58, 0x3da1,
		0x3dea, 0x3e34, 0x3e7d, 0x3ec7, 0x3f11, 0x3f5a, 0x3fa4, 0x3fee,
		0x4038, 0x4082, 0x40cc, 0x4116, 0x4161, 0x41ab, 0x41f5, 0x4240,

		0x428a, 0x42d5, 0x431f, 0x436a, 0x43b5, 0x4400, 0x444b, 0x4495,
		0x44e1, 0x452c, 0x4577, 0x45c2, 0x460d, 0x4659, 0x46a4, 0x46f0,
		0x473b, 0x4787, 0x47d3, 0x481e, 0x486a, 0x48b6, 0x4902, 0x494e,
		0x499a, 0x49e6, 0x4a33, 0x4a7f, 0x4acb, 0x4b18, 0x4b64, 0x4bb1,
		0x4bfe, 0x4c4a, 0x4c97, 0x4ce4, 0x4d31, 0x4d7e, 0x4dcb, 0x4e18,
		0x4e66, 0x4eb3, 0x4f00, 0x4f4e, 0x4f9b, 0x4fe9, 0x5036, 0x5084,
		0x50d2, 0x5120, 0x516e, 0x51bc, 0x520a, 0x5258, 0x52a6, 0x52f4,
		0x5343, 0x5391, 0x53e0, 0x542e, 0x547d, 0x54cc, 0x551a, 0x5569,

		0x55b8, 0x5607, 0x5656, 0x56a5, 0x56f4, 0x5744, 0x5793, 0x57e2,
		0x5832, 0x5882, 0x58d1, 0x5921, 0x5971, 0x59c1, 0x5a10, 0x5a60,
		0x5ab0, 0x5b01, 0x5b51, 0x5ba1, 0x5bf1, 0x5c42, 0x5c92, 0x5ce3,
		0x5d34, 0x5d84, 0x5dd5, 0x5e26, 0x5e77, 0x5ec8, 0x5f19, 0x5f6a,
		0x5fbb, 0x600d, 0x605e, 0x60b0, 0x6101, 0x6153, 0x61a4, 0x61f6,
		0x6248, 0x629a, 0x62ec, 0x633e, 0x6390, 0x63e2, 0x6434, 0x6487,
		0x64d9, 0x652c, 0x657e, 0x65d1, 0x6624, 0x6676, 0x66c9, 0x671c,
		0x676f, 0x67c2, 0x6815, 0x6869, 0x68bc, 0x690f, 0x6963, 0x69b6,

		0x6a0a, 0x6a5e, 0x6ab1, 0x6b05, 0x6b59, 0x6bad, 0x6c01, 0x6c55,
		0x6caa, 0x6cfe, 0x6d52, 0x6da7, 0x6dfb, 0x6e50, 0x6ea4, 0x6ef9,
		0x6f4e, 0x6fa3, 0x6ff8, 0x704d, 0x70a2, 0x70f7, 0x714d, 0x71a2,
		0x71f7, 0x724d, 0x72a2, 0x72f8, 0x734e, 0x73a4, 0x73fa, 0x7450,
		0x74a6, 0x74fc, 0x7552, 0x75a8, 0x75ff, 0x7655, 0x76ac, 0x7702,
		0x7759, 0x77b0, 0x7807, 0x785e, 0x78b4, 0x790c, 0x7963, 0x79ba,
		0x7a11, 0x7a69, 0x7ac0, 0x7b18, 0x7b6f, 0x7bc7, 0x7c1f, 0x7c77,
		0x7ccf, 0x7d27, 0x7d7f, 0x7dd7, 0x7e2f, 0x7e88, 0x7ee0, 0x7f38,

		0x7f91, 0x7fea, 0x8042, 0x809b, 0x80f4, 0x814d, 0x81a6, 0x81ff,
		0x8259, 0x82b2, 0x830b, 0x8365, 0x83be, 0x8418, 0x8472, 0x84cb,
		0x8525, 0x857f, 0x85d9, 0x8633, 0x868e, 0x86e8, 0x8742, 0x879d,
		0x87f7, 0x8852, 0x88ac, 0x8907, 0x8962, 0x89bd, 0x8a18, 0x8a73,
		0x8ace, 0x8b2a, 0x8b85, 0x8be0, 0x8c3c, 0x8c97, 0x8cf3, 0x8d4f,
		0x8dab, 0x8e07, 0x8e63, 0x8ebf, 0x8f1b, 0x8f77, 0x8fd4, 0x9030,
		0x908c, 0x90e9, 0x9146, 0x91a2, 0x91ff, 0x925c, 0x92b9, 0x9316,
		0x9373, 0x93d1, 0x942e, 0x948c, 0x94e9, 0x9547, 0x95a4, 0x9602,

		0x9660, 0x96be, 0x971c, 0x977a, 0x97d8, 0x9836, 0x9895, 0x98f3,
		0x9952, 0x99b0, 0x9a0f, 0x9a6e, 0x9acd, 0x9b2c, 0x9b8b, 0x9bea,
		0x9c49, 0x9ca8, 0x9d08, 0x9d67, 0x9dc7, 0x9e26, 0x9e86, 0x9ee6,
		0x9f46, 0x9fa6, 0xa006, 0xa066, 0xa0c6, 0xa127, 0xa187, 0xa1e8,
		0xa248, 0xa2a9, 0xa30a, 0xa36b, 0xa3cc, 0xa42d, 0xa48e, 0xa4ef,
		0xa550, 0xa5b2, 0xa613, 0xa675, 0xa6d6, 0xa738, 0xa79a, 0xa7fc,
		0xa85e, 0xa8c0, 0xa922, 0xa984, 0xa9e7, 0xaa49, 0xaaac, 0xab0e,
		0xab71, 0xabd4, 0xac37, 0xac9a, 0xacfd, 0xad60, 0xadc3, 0xae27,

		0xae8a, 0xaeed, 0xaf51, 0xafb5, 0xb019, 0xb07c, 0xb0e0, 0xb145,
		0xb1a9, 0xb20d, 0xb271, 0xb2d6, 0xb33a, 0xb39f, 0xb403, 0xb468,
		0xb4cd, 0xb532, 0xb597, 0xb5fc, 0xb662, 0xb6c7, 0xb72c, 0xb792,
		0xb7f7, 0xb85d, 0xb8c3, 0xb929, 0xb98f, 0xb9f5, 0xba5b, 0xbac1,
		0xbb28, 0xbb8e, 0xbbf5, 0xbc5b, 0xbcc2, 0xbd29, 0xbd90, 0xbdf7,
		0xbe5e, 0xbec5, 0xbf2c, 0xbf94, 0xbffb, 0xc063, 0xc0ca, 0xc132,
		0xc19a, 0xc202, 0xc26a, 0xc2d2, 0xc33a, 0xc3a2, 0xc40b, 0xc473,
		0xc4dc, 0xc544, 0xc5ad, 0xc616, 0xc67f, 0xc6e8, 0xc751, 0xc7bb,

		0xc824, 0xc88d, 0xc8f7, 0xc960, 0xc9ca, 0xca34, 0xca9e, 0xcb08,
		0xcb72, 0xcbdc, 0xcc47, 0xccb1, 0xcd1b, 0xcd86, 0xcdf1, 0xce5b,
		0xcec6, 0xcf31, 0xcf9c, 0xd008, 0xd073, 0xd0de, 0xd14a, 0xd1b5,
		0xd221, 0xd28d, 0xd2f8, 0xd364, 0xd3d0, 0xd43d, 0xd4a9, 0xd515,
		0xd582, 0xd5ee, 0xd65b, 0xd6c7, 0xd734, 0xd7a1, 0xd80e, 0xd87b,
		0xd8e9, 0xd956, 0xd9c3, 0xda31, 0xda9e, 0xdb0c, 0xdb7a, 0xdbe8,
		0xdc56, 0xdcc4, 0xdd32, 0xdda0, 0xde0f, 0xde7d, 0xdeec, 0xdf5b,
		0xdfc9, 0xe038, 0xe0a7, 0xe116, 0xe186, 0xe1f5, 0xe264, 0xe2d4,

		0xe343, 0xe3b3, 0xe423, 0xe493, 0xe503, 0xe573, 0xe5e3, 0xe654,
		0xe6c4, 0xe735, 0xe7a5, 0xe816, 0xe887, 0xe8f8, 0xe969, 0xe9da,
		0xea4b, 0xeabc, 0xeb2e, 0xeb9f, 0xec11, 0xec83, 0xecf5, 0xed66,
		0xedd9, 0xee4b, 0xeebd, 0xef2f, 0xefa2, 0xf014, 0xf087, 0xf0fa,
		0xf16d, 0xf1e0, 0xf253, 0xf2c6, 0xf339, 0xf3ad, 0xf420, 0xf494,
		0xf507, 0xf57b, 0xf5ef, 0xf663, 0xf6d7, 0xf74c, 0xf7c0, 0xf834,
		0xf8a9, 0xf91e, 0xf992, 0xfa07, 0xfa7c, 0xfaf1, 0xfb66, 0xfbdc,
		0xfc51, 0xfcc7, 0xfd3c, 0xfdb2, 0xfe28, 0xfe9e, 0xff14, 0xff8a
	};

	constexpr inline s16 kDecibelTable[SND_DECIBEL_TABLE_SIZE] = {
		-32768, -421, -361, -325, -300, -281, -265, -252,
		-240, -230, -221, -212, -205, -198, -192, -186,
		-180, -175, -170, -165, -161, -156, -152, -148,
		-145, -141, -138, -134, -131, -128, -125, -122,
		-120, -117, -114, -112, -110, -107, -105, -103,
		-100, -98, -96, -94, -92, -90, -88, -86,
		-85, -83, -81, -79, -78, -76, -74, -73,
		-71, -70, -68, -67, -65, -64, -62, -61,
		-60, -58, -57, -56, -54, -53, -52, -51,
		-49, -48, -47, -46, -45, -43, -42, -41,
		-40, -39, -38, -37, -36, -35, -34, -33,
		-32, -31, -30, -29, -28, -27, -26, -25,
		-24, -23, -23, -22, -21, -20, -19, -18,
		-17, -17, -16, -15, -14, -13, -12, -12,
		-11, -10, -9, -9, -8, -7, -6, -6,
		-5, -4, -3, -3, -2, -1, -1, 0
	};

	constexpr int calcTimer(int base_timer, int pitch) {

		pitch = -pitch;

		int shift = 0;
		while (pitch < 0) {
			shift--;
			pitch += SND_PITCH_TABLE_SIZE;
		}

		while (pitch >= SND_PITCH_TABLE_SIZE) {
			shift++;
			pitch -= SND_PITCH_TABLE_SIZE;
		}

		u64 timer = kPitchTable[pitch];

		timer += SND_PITCH_TABLE_BIAS;     // 0x10000 - 0x1ffff
		timer *= base_timer;               // 0x0 - 0x0002000000000000

		shift -= SND_PITCH_TABLE_SHIFT;
		if (shift <= 0) {
			timer >>= -shift;
		}
		else if (shift < 32) {
			const u64 mask = (0xffffffffffffffff << (32 - shift));

			// overflow
			if (timer & mask) {
				return SND_CHANNEL_TIMER_MAX;
			}
			else {
				timer <<= shift;
			}
		}
		else {
			return SND_CHANNEL_TIMER_MAX;
		}

		return static_cast<u16>(MATH_CLAMP(timer, SND_CHANNEL_TIMER_MIN, SND_CHANNEL_TIMER_MAX));
	}

	constexpr s16 calcDecibel(int scale) {
		return kDecibelTable[MATH_CLAMP(scale, 0, 127)];
	}

	__inline u16 calcChannelVolume(int dB) {
		return SND_CalcChannelVolume(dB);
	}

	constexpr int frequencyToTimer(int frequency) {
		return SND_TIMER_CLOCK / (frequency * 8);
	}

	constexpr int keyToTimer(int key, int baseTimer = frequencyToTimer(440), int rootKey = 69) {
		return calcTimer(baseTimer, (key - rootKey) * 64);
	}



	template<class T0, class T1 = u32, class T2 = u32, class T3 = u32>
	__inline void pushCommand(SNDCommandID c, T0 a0, T1 a1 = T1(), T2 a2 = T2(), T3 a3 = T3()) {
		PushCommand_impl(c, u32(a0), u32(a1), u32(a2), u32(a3));
	}

	__inline void setMasterVolume(int volume) {
		pushCommand(SND_COMMAND_MASTER_VOLUME, volume);
	}

	__inline void setMasterPan(int pan) {
		pushCommand(SND_COMMAND_MASTER_PAN, pan);
	}

	__inline void resetMasterPan() {
		setMasterPan(-1);
	}

	__inline void setupChannelPcm(int chNo, SNDWaveFormat format, const void* dataAddr, SNDChannelLoop loop, int loopStart, int dataLen, int volume, SNDChannelDataShift shift, int timer, int pan) {
		SND_SetupChannelPcm(chNo, format, dataAddr, loop, loopStart, dataLen, volume, shift, timer, pan);
	}

	__inline void setupChannelPsg(int chNo, SNDDuty duty, int volume, SNDChannelDataShift shift, int timer, int pan) {
		pushCommand(SND_COMMAND_SETUP_CHANNEL_PSG, chNo, volume | shift << 8, pan | timer << 8, duty);
	}

	__inline void setupChannelNoise(int chNo, int volume, SNDChannelDataShift shift, int timer, int pan) {
		pushCommand(SND_COMMAND_SETUP_CHANNEL_NOISE, chNo, volume | shift << 8, pan | timer << 8);
	}

	__inline void setChannelVolume(u32 chBitMask, int volume, SNDChannelDataShift shift) {
		pushCommand(SND_COMMAND_CHANNEL_VOLUME, chBitMask, volume, shift, 0);
	}

	__inline void setChannelTimer(u32 chBitMask, int timer) {
		pushCommand(SND_COMMAND_CHANNEL_TIMER, chBitMask, timer, 0, 0);
	}

	__inline void setChannelPan(u32 chBitMask, int pan) {
		pushCommand(SND_COMMAND_CHANNEL_PAN, chBitMask, pan, 0, 0);
	}

	__inline void startTimer(u32 chBitMask, u32 capBitMask, u32 alarmBitMask, u32 flags) {
		SND_StartTimer(chBitMask, capBitMask, alarmBitMask, flags);
	}

	__inline void stopTimer(u32 chBitMask, u32 capBitMask, u32 alarmBitMask, u32 flags) {
		SND_StopTimer(chBitMask, capBitMask, alarmBitMask, flags);
	}

	__inline void setupAlarm(int alarmNo, u32 tick, u32 period, SNDAlarmHandler handler, void* arg) {
		SND_SetupAlarm(alarmNo, tick, period, handler, arg);
	}

	__inline void setupCapture(SNDCapture capture, SNDCaptureFormat format, void* buffer_p, u32 length, BOOL loopFlag, SNDCaptureIn in, SNDCaptureOut out) {
		SND_SetupCapture(capture, format, buffer_p, length, loopFlag, in, out);
	}

	constexpr u32 microsecondsToTicks(int us) {
		return (OSTick(SND_TIMER_CLOCK / 1000) * us) / 32 / 1000;
	}
	constexpr u32 millisecondsToTicks(int ms) {
		return (OSTick(SND_TIMER_CLOCK / 1000) * ms) / 32;
	}
	constexpr u32 secondsToTicks(int s) {
		return OSTick(SND_TIMER_CLOCK * s) / 32;
	}


	//	This sound sub region which I named of "Internal" is the region that works with the NNS functions.
	namespace Internal {

		//	Information structure for where to play a sound effect.
		struct SFXPlayInfo
		{
			s32 x;
			s32 y;
			s32 volume;
		};

		/*
			Enables 2 extra insturments for world 8 map.
			Used after the bridge has emerged and the second part is revealed.
		*/
		void setTrackPanForWorld8(bool useCustomPan);

		/*
			Allocates the boss sound heap.
			Used in clearAndLoadLevelSeqs if a level field is checked.
			Level field: reinterpret_cast<u16*>(Block3)[1];
		*/
		bool allocBossSndHeapState();

		//	Sets the current sound archive to use. 
		void setCurrentSoundArc(int arcID);

		//	Sets if game is supposed to use Luigi sound effect set.
		void setUseLuigiSounds(bool value);

		//	Sets how many sequences can play at once.
		void setPlayableSeqCount(int seqCount);

		/*
			Child of the Sound::loop function.
			Updates when the enemies are supposed to jump.
		*/
		void updateBahps(void* bahpStruct);

		//	Checks if a value is in range. (Math library duplicate)
		bool inRange(s32 val, s32 low, s32 high);

		//	returns the absolute value of a number. (Math library duplicate)
		s32 abs(s32 val);

		//	returns a clamped number. (Math library duplicate)
		s32 clamp(s32 val, s32 low, s32 high);

		//	returns a wrapped range. (Math library duplicate)
		s32 wrapRange(s32 val, s32 low, s32 max);

		/*
			Sets the sound output effect.
			This function should not be used directly.
			Use Options::setOutputEffect instead.
		*/
		void setOutputEffect(NNSSndCaptureOutputEffectType type);

		//	Fades the music to another volume.
		void moveVolume(s32 targetVolume, s32 frames);

		//	Stops all sound effects playing.
		void stopAllSFX(s32 fadeFrame);

		//	Plays a sound effect from the sound archives.
		void playArcSFX(s32 seqArcIndex, s32 seqArcNo);

		//	Plays a sound effect from the sound archives at a specified position.
		bool playArcSFXAtPos(s32 seqArcIndex, s32 seqArcNo, SFXPlayInfo* playInfo, s32 channel);

		//	Gets the handle for a sound effect.
		NNSSndHandle* getHandleForArcSFX(s32 seqArcNo, s32 seqArcIndex);

		//	Gets the handle for a sound effect in range.
		NNSSndHandle* getHandleForArcSFXInRange(bool lastHandleFound);

		//	returns if the music play exists.
		bool playerExists();

		/*
			Fades a music away and then stops it.
			fadeFrame = Fade-out frame. Takes a value between 0 and 65535.
		*/
		void stopSeq(s32 fadeFrame);

		//	Pauses a music when true, unpauses when false.
		void pauseSeq(bool flag);

		//	Sets the music tempo ratio for a player.
		bool setTempoRatioForPlayer(NNSSndSeqPlayer* player, s32 ratio);

		//	Sets the music tempo ratio.
		bool setTempoRatio(s32 ratio);

		//	Starts a music sequence.
		bool startSeq(s32 seqId);

		/*
			Stops a music sequence while also fading out volume.
			sfx_frames = Frame count over which to fade sound effects.
			seq_frames = Frame count over which to fade the music sequence.
		*/
		bool stopSFXAndSeq(s32 sfx_frames, s32 seq_frames);

		/*
			Child of the Sound::loop function.
			Keeps music playing.
		*/
		bool updateSounds();

		//	Loads an archive for a sound effect set.
		bool loadArcForSFXSet(s32 sfxSetId);

		//	Loads a sound effect set.
		bool loadSFXSet(s32 sfxSetId);

		//	Loads the heap state.
		void loadHeapState();

		//	Loads the heap state and swaps to boss heap state if true.
		void loadHeapStateAndChange(bool changeState);

		//	Resets all heap states, clears all the loaded musics and sounds.
		void resetHeapStates();

		//	Initializes the sound data.
		void initSDAT();

		//	Loads a music sequence.
		bool loadSeq(s32 seqId);

		//	Starts the output effect capturing.
		bool startOutputEffect(void* buffer_p, u32 bufSize);

		//	Initializes the sound data for download play.
		void initSDAT_DLP(void* sdat);

		//	Sets up NNS for working with the sound heap.
		void reset(void* heap, int size);

	};

	/*
		Call functions:
		void FUN_0204E2F8(); //Calls playArcSFXAtPos
		void FUN_0204F2D4(); //Calls initSDAT

		Unused functions:
		void FUN_02012624(); //Clears a variable that is unused

		Unused variables:
		int 0x02088B58
	*/
};
