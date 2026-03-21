class PostProcess;
class Shader;
class ShaderVariable;
class RenderTarget;
class CubeMap;
class PostProcessFXAA;
class HDR;

enum class eCameraClearMode {
	eColor = 0x0,
	eDepth = 0x1,
	eColorAndDepth = 0x2,
	eDontClear = 0x3,
};

enum class eAxisRendering {
	eAxisNone = 0x0,
	eAxisBefore3d = 0x1,
	eAxisAfter3d = 0x2,
	eAxisModelBefore3d = 0x3,
	eAxisModelAfter3d = 0x4,
};

class BoundingFrustum {
public:
	mat44f matViewProj;
	plane4f planes[6];
	mat44f invViewProj;

	virtual void _dtor();
};
static_assert(sizeof(BoundingFrustum) == 0xE8);

class Camera {
public:
	float fov;
	mat44f matrix;
	std::wstring name;
	float nearPlane;
	float farPlane;
	eCameraClearMode clearMode;
	eAxisRendering axisRenderingMode;
	vec4f clearColor;
	float clearDepth;
	SkyBox *skyBox;
	BoundingFrustum frustum;
	Node *axis3d;
	RenderTarget *renderTarget;
	bool solveTransparentBuffer;
	float exposure;
	float minExposure;
	float maxExposure;
	float aspectRatio;
	float maxLayer;
	float dofFactor;
	float dofFocus;
	float dofRange;
	bool isMirror;
	bool renderAudio;
	float lodMultiplier;
	bool isCubeMapCamera;
	GraphicsManager *graphics;
	mat44f virtualScreenPassOrgMatrix;

	virtual void _dtor();
	virtual void render(Node *, float);
	virtual mat44f *getPerspectiveMatrix(mat44f *result);
	virtual mat44f *getViewMatrix(mat44f *result);
	virtual mat44f *getFinalWorldMatrix(mat44f *result);
};
static_assert(sizeof(Camera) == 0x210);

class ShadowMapSettings {
public:
	float nearSplit;
	float farSplit;
	float height;
};

class CameraShadowMapped : public Camera {
public:
	std::vector<ShadowMapSettings> shadowMapSettings;
	float shadowBias;
	std::vector<RenderTarget *> shadowRT;
	std::vector<mat44f> shadowMatrices;
	mat44f stableShadowMatrix;
};
static_assert(sizeof(CameraShadowMapped) == 0x2A0);

class CubeMapRenderer {
public:
	int facesPerFrame;
	Event<int> evOnRenderBegin;
	Event<int> evOnRenderEnd;
	GraphicsManager *graphics;
	mat44f cameraMatrix[6];
	Camera camera;
	int currentFace;

	virtual void _dtor();
};

class CameraForward : public CameraShadowMapped {
public:
	float blurQuality;
	float blurRadialSpeed;
	bool useRadialBlur;
	bool chromaticAberrationEnabled;
	bool lensFlare;
	CubeMapRenderer cubeMapRenderer;
	CubeMap *cubeMap;
	bool tripleScreenAvailable;
	PostProcess *postProcessChain;
	RenderTarget *postTempTargets[2];
	RenderTarget *rtBlur;
	int postRenderTargetIndex;
	ACSTD::vector<PostProcess*> postProcesses;
	HDR *hdr;
	bool useBlur;
	Shader *blurShader;
	Shader *blurShaderRadial;
	ShaderVariable *svRadialSpeed;
	ShaderVariable *svProjInv;
	ShaderVariable *svProj;
	ShaderVariable *svCameraVelocity;
	ShaderVariable *svCameraAngularVelocity;
	ShaderVariable *svQuality;
	ShaderVariable *svFpsCorrection;
	mat44f lastWorldMatrix;
	PostProcessFXAA *ppFXAA;
	float currentBlurAngle;
};
static_assert(sizeof(CameraForward) == 0x788);