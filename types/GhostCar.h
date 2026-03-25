class GhostCarFrame {
public:
	mat44f body;
	mat44f wheels[4];
	mat44f suspensions[4];
};

class GhostCarRecorder : public GameObject {
public:
	float blend;
	double lastLapStartingTime;
	Car *car;
	CarAvatar *avatar;
	ACSTD::vector<GhostCarFrame> recordingBuffer;
	ACSTD::vector<GhostCarFrame> playingBuffer;
	ACSTD::wstring ghostDriverName;
	ACSTD::wstring trackName;
	ACSTD::wstring carUnixName;
	ACSTD::wstring trackConfig;
	double advantageTimeMS;
	unsigned int ghostCarLap;
	bool linePassedForTheFirstTime;
	bool isGhostCarLapValid;
	unsigned int currentFrame;
	double lastRecordTime;
	double lastPlayingTime;
	bool needToSave;
	bool recordingSwitch;
	bool playingSwitch;
	int currentLap;
	int version;
	int suspensionWheelsEnabled;
};

class Material {
public:
	auto setVar(const ACSTD::wstring *name, const vec4f *value) { auto f = (void(__fastcall*)(Material*, const ACSTD::wstring*, const vec4f*))(NyaHookLib::mEXEBase + 0x20B910); return f(this, name, value); }
};

class CompileContext;
class RenderContext;
class Node {
public:
	mat44f matrix;
	mat44f matrixWS;
	bool isWSIdentity;
	std::vector<Node *> nodes;
	Node *parent;
	int priority;
	bool needsMatrixWS;
	std::wstring name;
	bool isActive;

	virtual void _dtor();
	virtual void addChild(Node *);
	virtual void compile(CompileContext *);
	virtual void render(RenderContext *);
	virtual void removeChild(Node *);
	virtual Node *findChildByName(const std::wstring *, bool);
	virtual void findChildrenByName(const std::wstring *, std::vector<Node *> *);
	virtual void findChildrenByPrefix(const std::wstring *, std::vector<Node *> *);
	virtual mat44f *getWorldMatrix(mat44f *result);
	virtual void printTree(int);
	virtual void renderAudio();
};
static_assert(offsetof(Node, matrix) == 0x8);

class Renderable : public Node {
public:
	bool castShadows;
	bool isVisible;
	bool isTransparent;
	bool noCull;
	sphere boundingSphere;
	int layer;
	float lodIN;
	float lodOUT;
	bool isStatic;
};

class NodeBoundingSphere : public Renderable {
public:
	Node *delegateNode;
};

class GhostCar : public GameObject {
public:
	NodeBoundingSphere *carNode;
	CarAvatar *car;
	Node *bodyTransform;
	Node *modelLink;
	Node *wheelTransforms[4];
	Node *susTransforms[4];
	GhostCarRecorder *gcRecorder;
	ACSTD::shared_ptr<Material> material;
	float maxDistance;
	float minDistance;
	float maxOpacity;
	vec3f gcColor;
	mat44f lastBodyMatrix;
	mat44f lastWheelMatrix[4];
	mat44f lastSuspMatrix[4];
	double playCounter;
};
static_assert(offsetof(GhostCar, car) == 0x60);
static_assert(offsetof(GhostCar, bodyTransform) == 0x68);

class ReplayRecorder;
class ReplayLap;
class ReplayInterface;
class ReplayAutosave;
class ReplayManager : public GameObject {
public:
	Event<bool> evOnReplayStarted;
	Event<bool> evOnReplayStopped;
	Event<int> evOnReplayRewind;
	Event<bool> evDidFinishedSavingReplay;
	bool hasLoadedReplay;
	eReplayStatus status;
	ACSTD::wstring lastFilename;
	ACSTD::vector<ReplayRecorder *> recorders;
	ACSTD::map<CarAvatar *,ACSTD::vector<ReplayLap>> replayLaps;
	eReplayStatus oldStatus;
	ReplayInterface *replayInterface;
	CameraMode oldCameraMode;
	DrivableCamera oldDrivableMode;
	int oldCameraTrackSet;
	int oldCameraCar;
	Sim *sim;
	float timeMult;
	float slowMoCounter;
	float slowMoLevel;
	double playCounter;
	bool replayMode;
	int recordedFrames;
	int currentRecordingIndex;
	double lastRecordTime;
	int maxFrames;
	int minFrames;
	int cutOut;
	int cutIn;
	float maxSizeMB;
	int currentFrame;
	SessionType currentSessionType;
	ACSTD::map<enum SessionType,ReplayAutosave> autoSaveData;
	bool autoSaveEnabled;
};