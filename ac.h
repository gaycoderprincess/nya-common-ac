#include <d3d9.h>

class vec2f {
public:
	float x;
	float y;
};

class vec3f : public NyaVec3 {
public:
	using NyaVec3::NyaVec3;

	vec3f(const NyaVec3& v) : NyaVec3(v) {}
};

class vec4f : public NyaVec4 {
public:
	using NyaVec4::NyaVec4;

	vec4f(const NyaVec4& v) : NyaVec4(v) {}
};

class mat44f : public NyaMat4x4 {
public:
	using NyaMat4x4::NyaMat4x4;

	mat44f(const NyaMat4x4& m) : NyaMat4x4(m) {}
};

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