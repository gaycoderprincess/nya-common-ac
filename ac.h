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
#include "types/Camera.h"
#include "types/PhysicsAvatar.h"
#include "types/ACPlugin.h"