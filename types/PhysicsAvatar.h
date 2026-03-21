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

struct OnPhysicsStepCompleted {
	double pt;
	std::vector<CarPhysicsState> *states;
};

enum class FlagEventType {
	BlackFlag = 0x0,
	BlackFlagClear = 0x1,
};

struct OnFlagEvent {
	Car *car;
	FlagEventType type;
	PenaltyDescription description;
};

class SessionInfo {
public:
	SessionType type;
	double startTimeMS;
	double timeSecs;
	int laps;
	int index;
};

class PhysicsCore {
public:
	uint8_t _0[0x8];
	dxWorld* id;
};

enum class PenaltyMode {
	CutGas = 0x0,
	InvalidateLap = 0x1,
	RecoverTime = 0x2,
	Nothing = 0x3,
	CutDetection = 0x4,
};

enum class JumpStartPenaltyMode {
	eLockOnGridMode = 0x0,
	eTeleportToPitMode = 0x1,
	eDriveThroughMode = 0x2,
};

class PenaltyRules {
public:
	JumpStartPenaltyMode jumpStartPenaltyMode;
	__int16 basePitPenaltyLaps;
};

class ICollisionCallback {
public:
	virtual void _dtor();
	virtual void onCollisionCallBack(void *, void *, void *, void *, vec3f, vec3f, float);
};

class CoreCPUTimes {
public:
	double solverTime;
	double collisionTime;
	int contactPoints;
	int narrowPhaseTests;
};

class PhysicsCPUTimes {
public:
	double carStep;
	CoreCPUTimes coreCPUTimes;
	int currentCPU;
};

class SteerMzLowSpeedReduction {
public:
	float speedKMH;
	float minValue;
};

class Wind {
public:
	vec3f vector;
	Speed speed;
	float directionDeg;
};

class DynamicTempData {
public:
	Curve temperatureCurve;
	double temperatureStartTime;
	float baseRoad;
	float baseAir;
};

class IPhysicsCore;
class IDebugVisualizer;
class ThreadPool;
class PhysicsEngine : public ICollisionCallback {
public:
	std::vector<Car *> cars;
	double physicsTime;
	bool validated;
	uint8_t _30[0x28]; // Concurrency::concurrent_queue<ACPhysicsEvent,std::allocator<ACPhysicsEvent> > eventQueue;
	Event<OnFlagEvent> evOnFlagEvent;
	Event<double> evOnStepCompleted;
	Event<double> evOnPreStep;
	Event<SessionInfo> evOnNewSessionPhysics;
	bool allowTyreBlankets;
	double lockGearboxAtStartTimeMS;
	float fuelConsumptionRate;
	float tyreConsumptionRate;
	int allowedTyresOut;
	PenaltyMode penaltyMode;
	PenaltyRules penaltyRules;
	std::vector<SlipStream *> slipStreams;
	double gameTime;
	float ambientTemperature;
	float roadTemperature;
	float mechanicalDamageRate;
	PhysicsCPUTimes physicsCPUTimes;
	const float flatSpotFFGain;
	SteerMzLowSpeedReduction mzLowSpeedReduction;
	bool isEngineStallEnabled;
	float gyroWheelGain;
	float spinTorqueGain;
	float damperMinValue;
	float damperGain;
	Wind wind;
	SessionInfo sessionInfo;
	PhysicsCore *core;
	Track *track;
	IDebugVisualizer *debugVisualizer;
	unsigned int stepCounter;
	std::vector<ICarPhysicsStateProvider *> additionalPhysicsProviders;
	std::vector<std::wstring> legalTyreList;
	std::unique_ptr<ThreadPool> pool;
	DynamicTempData dynamicTemp;
};

class WindData {
public:
	Speed speed;
	float directionDEG;
};

class DICommand {
public:
	int index;
	int button;
	bool status;
	unsigned int keyCode;
	int powIndex;
	int powValue;
};

class TimerProcess;
class DirectInput;
class DICommandManager {
public:
	DirectInput *directInput;
	std::vector<DICommand> commands;
	Game *game;
};

class PhysicsDriveThread {
public:
	bool hasStarted;
	ACSTD::atomic<unsigned int> physicsLateLoops;
	ACSTD::atomic<int> occupancy;
	ACSTD::atomic<float> cpuTimeAtomic;
	Event<double> evPhysicsStepCompleted;
	double timeScale;
	bool useDirectInput;
	float cpuTimeLocal;
	bool shuttingDown;
	double currentTime;
	double startTime;
	PhysicsEngine *engine;
	bool isPaused;
	TimerProcess *tProcess;
	ACSTD::thread thread;
	bool useTimerProcess;
	bool setAffinityMask;
	bool isPhysicsInitialized;
	double lastStepTimestamp;
	DirectInput *directInput;
	DICommandManager diCommandManager;
};
static_assert(sizeof(PhysicsDriveThread) == 0xB8);

class TemperatureInfo {
public:
	float ambientTemperature;
	float roadTemperature;
};

class DynamicTrackStatus {
public:
	bool enabled;
	float currentGripLevel;
};

class ThreadMutex {
public:
	_RTL_CRITICAL_SECTION criticalSection;
};

class PhysicsAvatar : public GameObject {
public:
	PhysicsEngine engine;
	Event<OnPhysicsStepCompleted> evOnStepCompleted;
	Event<OnFlagEvent> evOnFlagEvent;
	int occupancy;
	float cpuTimeMS;
	bool useMatrixSmoothing;
	unsigned int physicsLateLoops;
	WindData windData;
	uint8_t _318[0x28]; // Concurrency::concurrent_queue<std::function<void __cdecl(void)>,std::allocator<std::function<void __cdecl(void)> > > commandQueue;
	PhysicsDriveThread driveThread;
	float timeMult;
	bool isPaused;
	Sim *sim;
	TemperatureInfo temperatureInfo;
	TemperatureInfo temperatureInfoPT;
	ThreadMutex mutex;
	std::vector<CarPhysicsState> currentStates;
	std::vector<std::vector<WingState>> wingStates;
	DynamicTrackStatus dynamicTrackStatus;
	DynamicTrackStatus dynamicTrackStatusPT;
	std::vector<std::vector<PenaltyRecord>> penaltyRecords;
};
static_assert(sizeof(PhysicsAvatar) == 0x498);
static_assert(offsetof(PhysicsAvatar, engine) == 0x58);
static_assert(offsetof(PhysicsAvatar, evOnStepCompleted) == 0x2D0);
static_assert(offsetof(PhysicsAvatar, dynamicTrackStatus) == 0x470);