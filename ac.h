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

#include "types/acstl.h"
#include "types/Game.h"
#include "types/Sim.h"
#include "types/CarAvatar.h"
#include "types/Car.h"
#include "types/ACPlugin.h"

class RayCastResult {
public:
	SurfaceDef *surfaceDef;
	vec3f pos;
	vec3f normal;
	bool hasHit;
	void *collisionObject;
};

class ICollisionObject;
class RayCastHit {
public:
	vec3f pos;
	vec3f normal;
	ICollisionObject *collisionObject;
	bool hasContact;
};

class Track {
public:
	bool rayCast(const vec3f *org, const vec3f *dir, RayCastResult *result, float length) {
		auto f = (bool(__fastcall*)(Track*, const vec3f *org, const vec3f *dir, RayCastResult *result, float length))(NyaHookLib::mEXEBase + 0x278BB0);
		return f(this, org, dir, result, length);
	}
};

class dxWorld {
public:
	void dWorldSetGravity(float x, float y, float z) {
		auto f = (void(__fastcall*)(dxWorld*, float, float, float))(NyaHookLib::mEXEBase + 0x3404A0);
		return f(this, x, y, z);
	}
};

class PhysicsCore {
public:
	uint8_t _0[0x8];
	dxWorld* id;
};

class PhysicsEngine {
public:
	uint8_t _0[0x190];
	PhysicsCore* core;
};