#include <d3d9.h>

class vec2f {
public:
	float x;
	float y;
};

typedef NyaVec3 vec3f;
typedef NyaVec4 vec4f;
typedef NyaMat4x4 mat44f;

class plane4f {
public:
	vec3f normal;
	float d;
};
static_assert(sizeof(plane4f) == 0x10);

class sphere {
public:
	vec3f center;
	float radius;
};

#include "types/acstl.h"
#include "types/Game.h"
#include "types/Sim.h"
#include "types/CarAvatar.h"
#include "types/Car.h"
#include "types/Camera.h"
#include "types/PhysicsAvatar.h"
#include "types/RaceManager.h"
#include "types/ACCameraManager.h"
#include "types/GhostCar.h"
#include "types/TrackAvatar.h"
#include "types/ACPlugin.h"

enum class SystemMessageType {
	eDefault = 0x0,
	eNewGhostCar = 0x1,
	eServerPlayerDisconnected = 0x2,
	eServerPlayerJoined = 0x3,
	eServerKickedMsg = 0x4,
	eServerSessionVoting = 0x5,
	eServerKickVoting = 0x6,
	eServerVote = 0x7,
	eABS = 0x8,
	eTC = 0x9,
	eTurbo = 0xA,
	eBrakeBias = 0xB,
	eBrakeEngine = 0xC,
	eMGU = 0xD,
};

class SystemMessage {
public:
	auto addMessage(const ACSTD::wstring *imessage, const ACSTD::wstring *description, SystemMessageType type) { auto f = (void(__fastcall*)(SystemMessage*, const ACSTD::wstring*, const ACSTD::wstring*, SystemMessageType))(NyaHookLib::mEXEBase + 0x1B61C0); return f(this, imessage, description, type); }
};