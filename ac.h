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
#include "types/SetupScreen.h"
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

enum class eGLPrimitiveType {
	eLines = 0x0,
	eLinesStrip = 0x1,
	eTriangles = 0x2,
	eQuads = 0x3,
};

class MeshVertex {
public:
	vec3f pos;
	vec3f normal;
	vec2f texCoord;
	vec3f tangent;
};

template<typename T>
class VertexBuffer;

class IndexBuffer;
class GLRenderer {
public:
	ACSTD::vector<ACSTD::pair<int,void *>> buffers;
	int currentIndex;
	GraphicsManager *graphics;
	eGLPrimitiveType primitive;
	vec4f color;
	bool useTexture;
	vec2f texCoord;
	Shader *shader;
	IndexBuffer *fullQuadIB;
	VertexBuffer<MeshVertex> *fullQuadVB;
	Shader *glShader;
	Shader *glShaderTex;
	unsigned int tempCounter;
	MeshVertex tempVertices[3];
	MeshVertex *tempBuffer;
	unsigned int maxVertices;

	auto begin(eGLPrimitiveType type, Shader *ishader) {
		auto f = (void(__fastcall*)(GLRenderer*, eGLPrimitiveType, Shader*))(NyaHookLib::mEXEBase + 0x1FE800);
		return f(this, type, ishader);
	}
	auto end() {
		auto f = (void(__fastcall*)(GLRenderer*))(NyaHookLib::mEXEBase + 0x1FE870);
		return f(this);
	}
	auto color4f(float r, float g, float b, float a) {
		auto f = (void(__fastcall*)(GLRenderer*, float, float, float, float))(NyaHookLib::mEXEBase + 0x1FE850);
		return f(this, r, g, b, a);
	}
	auto vertex3f(float x, float y, float z) {
		auto f = (void(__fastcall*)(GLRenderer*, float, float, float))(NyaHookLib::mEXEBase + 0x1FFC20);
		return f(this, x, y, z);
	}
	auto quad(float x, float y, float width, float height, bool textured, Shader* shader) {
		auto f = (void(__fastcall*)(GLRenderer*, float, float, float, float, bool, Shader*))(NyaHookLib::mEXEBase + 0x1FF420);
		return f(this, x, y, width, height, textured, shader);
	}

	virtual void _dtor();
};
static_assert(offsetof(GLRenderer, useTexture) == 0x44);
static_assert(offsetof(GLRenderer, texCoord) == 0x48);
static_assert(offsetof(GLRenderer, maxVertices) == 0x108);

enum class DepthMode {
	eDepthNormal = 0x0,
	eDepthNoWrite = 0x1,
	eDepthOff = 0x2,
	eDepthLessEqual = 0x3,
};

enum class BlendMode {
	eOpaque = 0x0,
	eAlphaBlend = 0x1,
	eAlphaToCoverage = 0x2,
};

enum class CullMode {
	eCullFront = 0x0,
	eCullBack = 0x1,
	eCullNone = 0x2,
	eCullBiased = 0x3,
	eCullWireFrame = 0x4,
	eCullFrontNoMS = 0x5,
};

class RenderState {
public:
	void *textures[32];
	CullMode cullMode;
	BlendMode blendMode;
	DepthMode depthState;
	Material *material;
	mat44f projectionMatrix;
	mat44f viewMatrix;
	mat44f worldMatrix;
	Shader *shader;
	void *currentRenderTarget;
	void *currentDepth;
	bool overrideNoMS;
};

class RenderStats {
public:
	int dipCalls;
	int sceneDipCalls;
	int triangles;
	int sceneTriangles;
	bool isInMainRenderPass;
};

class LightingSettings {
public:
	vec3f lightDirection;
	vec3f lightColor;
	vec3f horizonLow;
	vec3f horizonHigh;
	vec3f skyLow;
	vec3f skyHigh;
	vec3f sunLow;
	vec3f sunHigh;
	float angle;
	float headingAngle;
	float pitchAngle;
	vec3f ambientLow;
	vec3f ambientHigh;
	vec3f fogColor;
	float fogLinear;
	float fogBlend;
	float cloudCover;
	float cloudCutoff;
	float cloudColor;
	float cloudOffset;
	float saturation;
	float gameTime;
	float sunAngleGamma;
};

class RendererFlags {
public:
	int maxFrameLatency;
	float mipLodBias;
};

struct OnWindowResize {
	int width;
	int height;
};

class ResourceStore;
class GPUProfiler;
class PvsProcessor;
class GraphicsManager {
public:
	bool useCustomSunDirection;
	float exposureMultiplier;
	VideoSettings videoSettings;
	RenderStats stats;
	LightingSettings lightingSettings;
	RendererFlags renderFlags;
	bool suspendViewportUpdateOnSetRenderTarget;
	GPUProfiler *gpuProfiler;
	PvsProcessor *pvsProcessor;
	CubeMap *currentCubeMap;
	Event<OnWindowResize> evWindowResize;
	Event<OnWindowResize> evWindowPreResize;
	ACSTD::unique_ptr<ResourceStore> resourceStore;
	RenderState state;
	GLRenderer *gl;
	vec3f customSunDirection;
	ACSTD::vector<std::wstring> errorStrings;
	ACSTD::vector<GLRenderer *> glRenderers;
	int multiSampleQuality;
	//SamplerStates samplerStates;
	//SystemCBuffers sysBuffers;
	//ACSTD::map<std::wstring,CBuffer *> cBuffersMap;
	//ShaderManager shaderManager;

	auto setTexture(int slot, const Texture *tex) {
		auto f = (void(__fastcall*)(GraphicsManager*, int, const Texture*))(NyaHookLib::mEXEBase + 0x204C70);
		return f(this, slot, tex);
	}

	auto setCullMode(CullMode mode) {
		auto f = (void(__fastcall*)(GraphicsManager*, CullMode))(NyaHookLib::mEXEBase + 0x204510);
		return f(this, mode);
	}

	virtual void _dtor();
};
static_assert(offsetof(GraphicsManager, videoSettings) == 0x10);
static_assert(offsetof(GraphicsManager, gpuProfiler) == 0x138);
static_assert(offsetof(GraphicsManager, gl) == 0x380);