class OnLapCompletedEvent {
public:
	unsigned int carIndex;
	unsigned int lapTime;
	unsigned int lapCount;
	ACSTD::vector<unsigned int> splits;
	double eventTime;
	bool isValid;
	int cuts;
};

struct OnSectorSplitEvent {
	unsigned int carIndex;
	unsigned int sectorIndex;
	unsigned int sectorTime;
	unsigned int cuts;
};

class OnTyreCompoundChanged {
public:
	int tyreIndex;
	int compoundIndex;
	ACSTD::wstring compoundName;
	ACSTD::wstring shortName;
};

template<typename T>
class EventTriggerOnChange {
public:
	uint8_t _0[0x30];
};

class NodeBoundingSphere;
class CarAudioFMOD;
class SkidMarkBuffer;
class RaceEngineer;
class DriverModel;
class ISuspensionAvatar;
class NetCarStateProvider;
class CarLodManager;
class ConstrainedObjectsManager;
class BackfireParams;
class Car;
class IEventTrigger;
class ICarPhysicsStateProvider;
class CarAnimations;

struct Speed {
	float f;

	static inline auto& useMPH = *(bool*)(NyaHookLib::mEXEBase + 0x204C70);
};

class SurfaceDef {
public:
	wchar_t wavString[64];
	float wavPitchSpeed;
	void *userPointer;
	float gripMod;
	int sectorID;
	float dirtAdditiveK;
	unsigned int collisionCategory;
	bool isValidTrack;
	float blackFlagTime;
	float sinHeight;
	float sinLength;
	bool isPitlane;
	float damping;
	float granularity;
	float vibrationGain;
	float vibrationLength;
};

class SCarStateAero {
public:
	float CD;
	float CL_Front;
	float CL_Rear;
};

class DriverActionsState {
public:
	int state;
};

class TyreThermalState {
public:
	float temps[12][3];
	float coreTemp;
	float thermalInput;
	float dynamicPressure;
	float staticPressure;
	float lastSetIMO[3];
	float cpTemperature;
	float lastGrain;
	float lastBlister;
	float mult;
	bool isHot;
};

enum class CarSetupState {
	UnKnown = 0x0,
	Legal = 0x1,
	Illegal = 0x2,
};

class CarPhysicsState {
public:
	unsigned __int8 physicsGUID;
	mat44f worldMatrix;
	mat44f suspensionMatrix[4];
	mat44f tyreMatrix[4];
	float engineRPM;
	bool isEngineLimiterOn;
	float wheelAngularSpeed[4];
	float steer;
	float gas;
	float brake;
	float clutch;
	int gear;
	Speed speed;
	vec3f velocity;
	vec3f localVelocity;
	vec3f localAngularVelocity;
	vec3f angularVelocity;
	float slipAngle[4];
	float slipRatio[4];
	float tyreSlip[4];
	float ndSlip[4];
	float load[4];
	float Dy[4];
	float Mz[4];
	float tyreDirtyLevel[4];
	SurfaceDef tyreSurfaceDef[4];
	float cgHeight;
	vec3f accG;
	unsigned int lapTime;
	unsigned int lastLap;
	unsigned int bestLap;
	unsigned int lapCount;
	float lastFF_Pure;
	float lastFF_Final;
	SCarStateAero aero;
	vec3f tyreContactPoint[4];
	vec3f tyreContactNormal[4];
	float camberRAD[4];
	float tyreRadius[4];
	float tyreLoadedRadius[4];
	float suspensionTravel[4];
	float normalizedSplinePosition;
	float driftPoints;
	float instantDrift;
	bool isDriftValid;
	int driftComboCounter;
	bool driftBonusOn;
	float drivetrainSpeed;
	float turboBoost;
	float performanceMeter;
	float performanceMeterSpeedDiffMS;
	bool isGearGrinding;
	float bodyWorkVolume;
	float tyreVirtualKM[4];
	float damageZoneLevel[5];
	int limiterRPM;
	plane4f groundPlane;
	double timeStamp;
	float airDensity;
	float fuel;
	float fuelLaps;
	float rideHeight[2];
	bool isRetired;
	float engineLifeLeft;
	float turboBov;
	float turboBoostLevel;
	float tyreGrain[4];
	float tyreBlister[4];
	DriverActionsState actionsState;
	CarSetupState setupState;
	float tyreInflation[4];
	float kersCharge;
	float kersInput;
	float gearRpmWindow;
	float susDamage[4];
	float tyreFlatSpot[4];
	float water;
	TyreThermalState tyreThermalStates[4];
	float discTemps[4];
	float wear[4];
	float wearMult[4];
	float lockControlsTime;
	float kersCurrentKJ;
	bool kersIsCharging;
	unsigned int statusBytes;
	unsigned __int8 p2pStatus;
	unsigned __int8 p2pActivations;
	float antiSquat;
	float caster[2];
};
static_assert(sizeof(CarPhysicsState) == 0xB70);
static_assert(offsetof(CarPhysicsState, tyreMatrix) == 0x144);
static_assert(offsetof(CarPhysicsState, slipAngle) == 0x2A4);
static_assert(offsetof(CarPhysicsState, tyreLoadedRadius) == 0x6FC);
static_assert(offsetof(CarPhysicsState, groundPlane) == 0x774);
static_assert(offsetof(CarPhysicsState, timeStamp) == 0x788);
static_assert(offsetof(CarPhysicsState, engineLifeLeft) == 0x7A8);
static_assert(offsetof(CarPhysicsState, actionsState) == 0x7D4);
static_assert(offsetof(CarPhysicsState, tyreThermalStates) == 0x81C);
static_assert(offsetof(CarPhysicsState, kersIsCharging) == 0xB54);

class AIState {
public:
	float currentSteerSignal;
	vec3f steerTarget;
	float gasBrakeTarget;
	bool isActive;
	float targetSpeed;
	float targetLateralOffset;
	float brakeTargetSpeed;
	float brakeTargetDist;
	float currentNormalizedSplinePosition;
	float outsideOffset;
	float projDNRPM;
	float understeerFactor;
	float currentPush;
};

class ModelBoundariesCoordinates {
public:
	float front;
	float rear;
	float left;
	float right;
	float top;
	float bottom;
};

template<typename T1, typename T2>
class CubicSpline {
public:
	struct Element {
		T1 x;
		T2 a;
		T2 b;
		T2 c;
		T2 d;
	};

	ACSTD::vector<Element> mElements;

	virtual void _dtor();
};

class Curve {
public:
	ACSTD::vector<float> references;
	ACSTD::vector<float> values;
	float fastStep;
	bool cubicSplineReady;
	CubicSpline<float,float> cSpline;
	ACSTD::wstring filename;

	virtual void _dtor();
};

class WingData {
public:
	ACSTD::wstring name;
	float chord;
	float span;
	vec3f position;
	Curve lutAOA_CL;
	Curve lutAOA_CD;
	Curve lutGH_CL;
	Curve lutGH_CD;
	float clGain;
	float cdGain;
	bool hasController;
	float yawGain;
	float area;
	bool isVertical;
};

class WingState {
public:
	float aoa;
	float cd;
	float cl;
	float angle;
	float inputAngle;
	float groundHeight;
	float frontShare;
	float dragKG;
	float liftKG;
	float angleMult;
	float groundEffectLift;
	float groundEffectDrag;
	float yawAngle;
	bool isVertical;
	vec3f liftVector;
};

class CameraCarDefinition {
public:
	mat44f matrix;
	float fov;
	float exposure;
	bool externalSound;
};

class ICarPhysicsStateProvider {
public:
	virtual void _dtor();
	virtual void getPhysicsState(CarPhysicsState *);
	virtual void getWingState(ACSTD::vector<WingState> *);
};

class PhysicsCarStateProvider : public ICarPhysicsStateProvider {
public:
	Car *car;
};

class DriverInfo {
public:
	ACSTD::wstring name;
	ACSTD::wstring team;
	ACSTD::wstring nationality;
	ACSTD::wstring nationCode;
};

class CarRaceInfo {
public:
	CarAvatar *car;
	ACSTD::map<ACSTD::wstring,int> spawnPositionIndex;
	RaceManager *raceManager;

	virtual void _dtor();
};
static_assert(sizeof(CarRaceInfo) == 0x28);
static_assert(offsetof(CarRaceInfo, spawnPositionIndex) == 0x10);
static_assert(offsetof(CarRaceInfo, raceManager) == 0x20);

class KPI {
public:
	float angleRAD;
	float scrubRadius;
};

class CarPhysicsInfo {
public:
	float steerLock;
	int maxGear;
	float caster;
	float tyreRadius[4];
	float tyreWidth[4];
	float totalMass;
	float bodyMass;
	float unsprungWeights[4];
	ACSTD::vector<WingData> wingData;
	float maxTorqueNM;
	float maxPowerW;
	float bumpStopsUp[4];
	float bumpStopsDn[4];
	double maxFuel;
	vec3f ridePickupPoint[2];
	vec3f susBasePos[4];
	ACSTD::vector<ACSTD::wstring> tyreCompounds;
	float minHeightM;
	float wheelAngularInertia[4];
	KPI kpi;
	float maxTurboBoost;
	int turboCount;
	float kersMaxJ;
	float ersMaxJ;
	float powerClassIndex;
	bool hasKERS;
	bool hasERS;
	bool hasCockpitERSRecovery;
	bool hasCockpitERSDeliveryProfile;
	bool hasCockpitEngineBrake;
	bool hasCockpitERSMguHMode;
	bool hasDRS;
	int engineBrakeSettingsCount;
	int ersPowerControllerCount;
	int engineDamageRPM;
	bool hasAdjustableTurbo;
	int maxRpm;
};
static_assert(sizeof(CarPhysicsInfo) == 0x140);
static_assert(offsetof(CarPhysicsInfo, bumpStopsUp) == 0x68);
static_assert(offsetof(CarPhysicsInfo, ridePickupPoint) == 0x90);
static_assert(offsetof(CarPhysicsInfo, tyreCompounds) == 0xD8);
static_assert(offsetof(CarPhysicsInfo, maxTurboBoost) == 0x10C);
static_assert(offsetof(CarPhysicsInfo, hasCockpitERSRecovery) == 0x122);
static_assert(offsetof(CarPhysicsInfo, hasAdjustableTurbo) == 0x134);

class CarAvatar : public GameObject {
public:
	EventTriggerOnChange<int> evOnGearChanged;
	Event<OnLapCompletedEvent> evOnLapCompleted;
	Event<OnSectorSplitEvent> evOnSectorSplit;
	Event<OnTyreCompoundChanged> evOnTyreCompoundChanged;
	Event<bool> evOnBackfireTriggered;
	Event<bool> evOnDownshiftProtection;
	ACSTD::wstring externalTyreCompoundShortName;
	vec3f mirrorPosition;
	Sim *sim;
	ACSTD::wstring unixName;
	ACSTD::wstring configName;
	ACSTD::wstring guiName;
	ACSTD::wstring guiShortName;
	Node *bodyTransform;
	Node *steerTransformHR;
	Node *steerTransformLR;
	mat44f orgSteerMatrix;
	NodeBoundingSphere *carNode;
	vec3f driverEyesPosition;
	mat44f bodyMatrix;
	CarPhysicsState physicsState;
	AIState aiState;
	CarAudioFMOD *carAudioFMOD;
	SkidMarkBuffer *skidMarkBuffers[4];
	CarPhysicsInfo physicsInfo;
	ACSTD::unique_ptr<RaceEngineer> raceEngineer;
	ModelBoundariesCoordinates modelBoundaries;
	ACSTD::vector<WingState> wingsStatus;
	float onBoardExposure;
	float outBoardExposure;
	float dashBoardExposure;
	ACSTD::vector<CameraCarDefinition> cameras;
	bool isDriverHR;
	DriverModel *driverModel_HR;
	DriverModel *driverModel_LR;
	ISuspensionAvatar *suspensionAvatar;
	bool isBlackFlagged;
	NetCarStateProvider *netCarStateProvider;
	CarLodManager *lodManager;
	ConstrainedObjectsManager *constrainedObjectManager;
	BufferedChannel<ACSTD::pair<int,int> > chTyreCompound;
	float fuelInExhaust;
	vec3f graphicsOffset;
	float graphicsPitchRotation;
	float userFFGain;
	float graphicSteerLockDegrees;
	BackfireParams *backfireParams;
	Node *meshCollider;
	mat44f pitPosition;
	DriverInfo driverInfo;
	ACSTD::wstring currentSkin;
	int guid;
	Node *modelLink;
	Car *physics;
	vec3f lastSkidPosition[4];
	ACSTD::vector<IEventTrigger *> eventTriggers;
	ICarPhysicsStateProvider *physicsStateProvider;
	bool lockVirtualSteer;
	bool hideArmsInCockpit;
	bool hideSteer;
	CarRaceInfo raceInfo;
	ACSTD::unique_ptr<PhysicsCarStateProvider> physicsCarStateProvider;
	BufferedChannel<OnLapCompletedEvent> lapQueue;
	BufferedChannel<OnSectorSplitEvent> splitQueue;
	ICarPhysicsStateProvider *nonReplayPhysicsStateProvider;
	Node *beltOffNode;
	Node *beltOnNode;
	int currentTyreCompoundIndex[4];
	CarAnimations *carAnimations;
	float filteredSpeed;
	int currentEngineBrakeSetting;
	bool isHeatChargingBatteries;
	int currentERSPowerIndex;
	int currentERSRecovery;
	float lastERSBatteryCharge;
	float currentERSNormalizedRecharge;
	bool showDownShiftProtetion;
	bool mandatoryPitstopDone;
	float lastPitstopTime;
	bool inPitlane;
	bool wasInPitlane;
	float pitLaneEntryTime;
	float pitLaneExitTime;

	auto makeBodyMatrix(const mat44f *bm, mat44f *res) { auto f = (void(__fastcall*)(CarAvatar*, const mat44f*, mat44f*))(NyaHookLib::mEXEBase + 0xD8EC0); return f(this, bm, res); }
};
static_assert(sizeof(CarAvatar) == 0x12A8);
static_assert(offsetof(CarAvatar, steerTransformHR) == 0x1C0);
static_assert(offsetof(CarAvatar, physicsInfo) == 0xE40);
static_assert(offsetof(CarAvatar, raceEngineer) == 0xF80);
static_assert(offsetof(CarAvatar, dashBoardExposure) == 0xFC0);
static_assert(offsetof(CarAvatar, lodManager) == 0x1010);
static_assert(offsetof(CarAvatar, raceInfo) == 0x11C8);
static_assert(offsetof(CarAvatar, physicsCarStateProvider) == 0x11F0);
static_assert(offsetof(CarAvatar, splitQueue) == 0x1220);
static_assert(offsetof(CarAvatar, filteredSpeed) == 0x1278);
static_assert(offsetof(CarAvatar, wasInPitlane) == 0x129D);