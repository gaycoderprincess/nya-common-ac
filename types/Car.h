class ITyreModel;
class IRayCaster;
class ISuspension;
class IRayTrackCollisionProvider;
class IJoint;
class ISuspension;
class PhysicsEngine;
class ISphereCollisionCallback;
class CarControls;
class CarControlsInput;
class VibrationDef;

enum class DriverActions {
	eLookingLeft = 0x0,
	eLookingRight = 0x1,
	eDeprecated_2 = 0x2,
	eDeprecated_1 = 0x3,
	eHeadlightsSwitch = 0x4,
	eChangingCamera = 0x5,
	eHorn = 0x6,
	eShiftingUp = 0x7,
	eShiftingDown = 0x8,
	eLookingBack = 0x9,
	eHeadlightsFlash = 0xA,
	eTcUp = 0xB,
	eTcDown = 0xC,
	eAbsUp = 0xD,
	eAbsDown = 0xE,
	eTurboUp = 0xF,
	eTurboDown = 0x10,
	eBrakeBiasUp = 0x11,
	eBrakeBiasDown = 0x12,
	eDRS = 0x13,
	eKERS = 0x14,
	eEngineBrakeUp = 0x15,
	eEngineBrakeDown = 0x16,
	eMGUKDeliveryUp = 0x17,
	eMGUKDeliveryDown = 0x18,
	eMGUKRecoveryUp = 0x19,
	eMGUKRecoveryDown = 0x1A,
	eMGUHMode = 0x1B,
};

class ICarControlsProvider {
public:
	bool ffEnabled;
	float ffFilter;
	bool suppressPenalties;
	bool isAutoclutchNeeded;
	bool useFakeUndersteerFF;
	bool keyboardEnabled;

	virtual void _dtor();
	virtual void acquireControls(CarControls *, float, CarControlsInput *);
	virtual bool getAction(DriverActions);
	virtual void sendFF(float, float, float);
	virtual const char *getName();
	virtual float getFFGlobalGain();
	virtual bool isDeviceConnected();
	virtual void onAutoShifterChanged(bool);
	virtual bool IsKeyboardControl();
	virtual void setVibrations(const VibrationDef *);
	virtual void setEngineRPM(float, float, float);
	virtual bool shouldDelete();
};

class RaceEngineer {
public:
	Car *car;
	float fuelPerLapEvaluated;

	virtual void _dtor();
};

class AISplineRecorder;
class KeyboardCarControl : public ICarControlsProvider {
public:
	float minSteering;
	float steerSpeed;
	float steerOppositeDirectionFactor;
	float steerGain;
	float steerResetFactor;
	float lookAhead;
	float targetSpeed;
	float steerDecelerator;
	float speedDeceleringFactor;
	float turnDeceleringFactor;
	float intGas;
	float intSteer;
	RaceEngineer eng;
	float gasPedalSpeed;
	float understeerSteerCorrection;
	int currentSplinePos;
	float oldSteer;
	bool validated;
	bool mouseSteering;
	bool mouseAcceleratorBrake;
	float oldMouseValue;
	float mouseSpeed;
	HWND__ *activeWindow;
	tagPOINT mouseCoordinates;
	int keyGas;
	int keyRight;
	int keyLeft;
	int keyBrake;
	int keyGearUp;
	int keyGearDown;
	int keyGlanceLeft;
	int keyGlanceRight;
	int keyGlanceBack;
	int keyTurnOnHeadlights;
	int keyFlashHeadlights;
	int keyHorn;
	int keyHandbrake;
	int keyBrakeBalanceUp;
	int keyBrakeBalanceDn;
	int keyChangeCamera;
	int keyAbsUp;
	int keyAbsDn;
	int keyTcUp;
	int keyTcDn;
	int keyTurboUp;
	int keyTurboDn;
	int keyKers;
	int keyDrs;
	int keyEngineBrakeUp;
	int keyEngineBrakeDn;
	int keyMGUKDeliveryUp;
	int keyMGUKDeliveryDn;
	int keyMGUKRecoveryUp;
	int keyMGUKRecoveryDn;
	int keyMGUHMode;
	AISplineRecorder *aiSpline;
	Car *car;
};

class IRigidBody {
public:
	virtual void setMassExplicitInertia(float, float, float, float);
	virtual bool isEnabled();
	virtual void setEnabled(bool);
	virtual void setAutoDisable(bool);
	virtual void removeCollisionObjects();
	virtual float getMass();
	virtual void release();
	virtual void setMassBox(float, float, float, float);
	virtual vec3f *getLocalInertia(vec3f *result);
	virtual mat44f *getWorldMatrix(mat44f *result, float);
	virtual vec3f *localToWorld(vec3f *result, const vec3f *);
	virtual vec3f *worldToLocal(vec3f *result, const vec3f *);
	virtual vec3f *localToWorldNormal(vec3f *result, const vec3f *);
	virtual vec3f *worldToLocalNormal(vec3f *result, const vec3f *);
	virtual void stop(float);
	virtual vec3f *getVelocity(vec3f *result);
	virtual void setVelocity(const vec3f *);
	virtual void setAngularVelocity(const vec3f *);
	virtual void setPosition(const vec3f *);
	virtual void setRotation(const mat44f *);
	virtual vec3f *getPosition(vec3f *result, float interpolationT);
	virtual vec3f *getAngularVelocity(vec3f *result);
	virtual vec3f *getLocalAngularVelocity(vec3f *result);
	virtual vec3f *getLocalVelocity(vec3f *result);
	virtual void setBoxColliderMask(unsigned __int64, unsigned int);
	virtual unsigned __int64 addBoxCollider(const vec3f *, const vec3f *, unsigned int, unsigned int, unsigned int);
	virtual void addSphereCollider(const vec3f *, const float, unsigned int, ISphereCollisionCallback *);
	virtual void addLocalForce(const vec3f *);
	virtual void addLocalTorque(const vec3f *);
	virtual void addLocalForceAtPos(const vec3f *, const vec3f *);
	virtual void addLocalForceAtLocalPos(const vec3f *, const vec3f *);
	virtual void addForceAtLocalPos(const vec3f *, const vec3f *);
	virtual vec3f *getLocalPointVelocity(vec3f *result, const vec3f *);
	virtual vec3f *getPointVelocity(vec3f *result, const vec3f *);
	virtual void addForceAtPos(const vec3f *, const vec3f *);
	virtual void addTorque(const vec3f *);
	virtual void addMeshCollider(float *, unsigned int, unsigned __int16 *, unsigned int, mat44f, unsigned int, unsigned int, unsigned int);
	virtual void setMeshCollideCategory(unsigned int, unsigned int);
	virtual void setMeshCollideMask(unsigned int, unsigned int);
	virtual unsigned int getMeshCollideCategory(unsigned int);
	virtual unsigned int getMeshCollideMask(unsigned int);
	virtual void dtor();
};

class ITorqueGenerator {
public:
	virtual void _dtor();
	virtual float getOutputTorque();
};

class ICoastGenerator {
public:
	virtual void _dtor();
	virtual float getCoastTorque();
};

struct OnStepCompleteEvent {
	Car *car;
	double physicsTime;
};

struct OnControlsProviderChanged {
	Car *car;
	ICarControlsProvider *newControlsProvider;
};

class OnCollisionEvent {
public:
	IRigidBody *body;
	float relativeSpeed;
	vec3f worldPos;
	vec3f relPos;
	unsigned int colliderGroup;
};

class CarControls {
public:
	bool gearUp;
	bool gearDn;
	bool drs;
	bool kers;
	bool brakeBalanceUp;
	bool brakeBalanceDn;
	int requestedGearIndex;
	bool isShifterSupported;
	float handBrake;
	bool absUp;
	bool absDn;
	bool tcUp;
	bool tcDn;
	bool turboUp;
	bool turboDn;
	bool engineBrakeUp;
	bool engineBrakeDn;
	bool MGUKDeliveryUp;
	bool MGUKDeliveryDn;
	bool MGUKRecoveryUp;
	bool MGUKRecoveryDn;
	bool MGUHMode;
	float gas;
	float brake;
	float steer;
	float clutch;
};

enum class eTimeLineCheckResponse {
	eOutOfRange = 0x0,
	eNegativeSide = 0x1,
	ePositiveSide = 0x2,
};

enum class OpenTrackTimeState {
	NotStarted = 0x0,
	Started = 0x1,
};

class TimeLineStatus {
public:
	bool isValid;
	eTimeLineCheckResponse lastResponse;
	unsigned int lastTime;
};

class TimeTransponder {
public:
	unsigned int t;
	unsigned int lastLap;
	unsigned int bestLap;
	unsigned int lapCount;
	bool finishLinePassed;
	bool wasLastLapValid;
	ACSTD::vector<TimeLineStatus> status;
	ACSTD::vector<unsigned int> lastLapSplits;
	ACSTD::vector<unsigned int> bestLapSplits;
	ACSTD::vector<unsigned int> currentSplits;
	Car *car;
	bool isFirstLapArmed;
	int cuts;
	bool extInvalid;
	OpenTrackTimeState openTrackState;
	bool isOpenTrack;

	auto step(float dt) { auto f = (void(__fastcall*)(TimeTransponder*, float))(NyaHookLib::mEXEBase + 0x2911F0); return f(this, dt); }
};

class CarCollisionBox {
public:
	vec3f centre;
	vec3f size;
	unsigned __int64 id;
};

class FileChangeObserver {
public:
	_FILETIME lastFileTime;
	ACSTD::wstring filename;
	unsigned int lastChanged;
};

class CarColliderManager {
public:
	bool isLive;
	ACSTD::vector<CarCollisionBox> boxes;
	FileChangeObserver observer;
	ACSTD::wstring carModel;
	IRigidBody *carBody;
	Car *car;

	auto step(float dt) { auto f = (void(__fastcall*)(CarColliderManager*, float))(NyaHookLib::mEXEBase + 0x2A3D50); return f(this, dt); }
};

class DynamicController;
class DrivetrainControllers {
public:
	ACSTD::unique_ptr<DynamicController> awdFrontShare;
	ACSTD::unique_ptr<DynamicController> awdCenterLock;
	ACSTD::unique_ptr<DynamicController> singleDiffLock;
	ACSTD::unique_ptr<DynamicController> awd2;
};

class GearElement {
public:
	double velocity;
	double inertia;
	double oldVelocity;
};

class SGearRatio {
public:
	double ratio;
	ACSTD::wstring name;
};

enum class DifferentialType {
	LSD = 0x0,
	Spool = 0x1,
};

enum class TractionType {
	RWD = 0x0,
	FWD = 0x1,
	AWD = 0x2,
	AWD_NEW = 0x3,
};

enum class GearChangeRequest {
	eNoGearRequest = 0x0,
	eChangeUp = 0x1,
	eChangeDown = 0x2,
	eChangeToGear = 0x3,
};

class GearRequestStatus {
public:
	GearChangeRequest request;
	double timeAccumulator;
	double timeout;
	int requestedGear;
};

class acEngineData {
public:
	Curve powerCurve;
	Curve coastCurve;
	float coast2;
	float coast1;
	float coast0;
	bool useCoastCurve;
	int minimum;
	int limiter;
	int limiterCycles;
	float overlapFreq;
	float overlapGain;
	float overlapIdealRPM;
};

class EngineStatus {
public:
	double outTorque;
	double externalCoastTorque;
	float turboBoost;
	bool isLimiterOn;
};

class TurboDef {
public:
	float maxBoost;
	float lagUP;
	float lagDN;
	float rpmRef;
	float gamma;
	float wastegate;
	bool isAdjustable;
};

class Turbo {
public:
	float userSetting;
	float rotation;
	TurboDef data;
};

class PushToPass {
public:
	bool enabled;
	bool active;
	float overboost;
	float timeS;
	float coolDownS;
	float timeAccum;
	int activations;
	float baseWastegate;
	int baseActivations;
	int basePositionCoeff;
	int maxActivations;
};

class SACEngineInput {
public:
	float gasInput;
	float carSpeed;
	float altitude;
	float rpm;
};

class DynamicWingController {
public:
	enum class eInputVar {
		eUndefined = 0x0,
		eBrake = 0x1,
		eGas = 0x2,
		eLatG = 0x3,
		eLonG = 0x4,
		eSteer = 0x5,
		eSpeed = 0x6,
		SusTravelLR = 0x7,
		SusTravelRR = 0x8,
	};
	enum class eCombinatorMode {
		eUndefinedMode = 0x0,
		eAdd = 0x1,
		eMult = 0x2,
	};
};
typedef DynamicWingController::eInputVar DynamicControllerInput;
typedef DynamicWingController::eCombinatorMode DynamicControllerCombinatorMode;

class DynamicControllerStage {
public:
	DynamicControllerInput inputVar;
	DynamicControllerCombinatorMode combinatorMode;
	Curve lut;
	float filter;
	float upLimit;
	float downLimit;
	float currentValue;
	float constValue;
};

class DynamicController {
public:
	Car *car;
	ACSTD::vector<DynamicControllerStage> stages;
	bool ready;
};

class TurboDynamicController {
public:
	Turbo *turbo;
	DynamicController controller;
	bool isWastegate;
};

class PhysicsEngine;
class Engine {
public:
	acEngineData data;
	EngineStatus status;
	float coastTorqueMultiplier;
	float limiterMultiplier;
	float fuelPressure;
	float bov;
	ACSTD::vector<Turbo> turbos;
	bool isEngineStallEnabled;
	float starterTorque;
	float rpmDamageThreshold;
	float restrictor;
	PushToPass p2p;
	ACSTD::vector<ITorqueGenerator *> torqueGenerators;
	ACSTD::vector<ICoastGenerator *> coastGenerators;
	bool turboAdjustableFromCockpit;
	SACEngineInput lastInput;
	int defaultEngineLimiter;
	float inertia;
	int limiterOn;
	float electronicOverride;
	float maxPowerW_Dynamic;
	float maxPowerW;
	float maxTorqueNM;
	float maxPowerRPM;
	float maxTorqueRPM;
	PhysicsEngine *physicsEngine;
	Curve throttleResponseCurve;
	Curve throttleResponseCurveMax;
	float throttleResponseCurveMaxRef;
	float gasUsage;
	double lifeLeft;
	float turboBoostDamageThreshold;
	float turboBoostDamageK;
	float rpmDamageK;
	float bovThreshold;
	Car *car;
	ACSTD::vector<TurboDynamicController> turboControllers;
	float gasCoastOffset;
	Curve gasCoastOffsetCurve;
	int coastSettingsDefaultIndex;
	int coastEntryRpm;

	virtual bool init(const char *);
	virtual int getLimiterRPM();
	virtual bool *isLimiterOn();
};

class DifferentialSetting {
public:
	float power;
	float coast;
	float preload;
	DifferentialType type;
};

class DownshiftProtection {
public:
	bool isActive;
	bool isDebug;
	int overrev;
	bool lockN;
};

class AWD2Data {
public:
	double ramp;
	double maxTorque;
	float currentLockTorque;
};

class TyreInputs {
public:
	float brakeTorque;
	float handBrakeTorque;
	float electricTorque;
};

class TyreData {
public:
	float width;
	float radius;
	float k;
	float d;
	float angularInertia;
	float thermalFrictionK;
	float thermalRollingK;
	float thermalRollingSurfaceK;
	float grainThreshold;
	float blisterThreshold;
	float grainGamma;
	float blisterGamma;
	float grainGain;
	float blisterGain;
	float rimRadius;
	float optimumTemp;
	float softnessIndex;
	float radiusRaiseK;
};

class TyreModelData {
public:
	int version;
	float Dy0;
	float Dy1;
	float Dx0;
	float Dx1;
	float Fz0;
	float flexK;
	float speedSensitivity;
	float relaxationLength;
	float rr0;
	float rr1;
	float rr_sa;
	float rr_sr;
	float rr_slip;
	float camberGain;
	float pressureSpringGain;
	float pressureFlexGain;
	float pressureRRGain;
	float pressureGainD;
	float idealPressure;
	float pressureRef;
	Curve wearCurve;
	float dcamber0;
	float dcamber1;
	Curve dyLoadCurve;
	Curve dxLoadCurve;
	float lsMultY;
	float lsExpY;
	float lsMultX;
	float lsExpX;
	float maxWearKM;
	float maxWearMult;
	float asy;
	float cfXmult;
	float brakeDXMod;
	Curve dCamberCurve;
	bool useSmoothDCamberCurve;
	float combinedFactor;
};

class TyreStatus {
public:
	float depth;
	float load;
	float camberRAD;
	float slipAngleRAD;
	float slipRatio;
	float angularVelocity;
	float Fy;
	float Fx;
	float Mz;
	bool isLocked;
	float slipFactor;
	float ndSlip;
	float distToGround;
	float Dy;
	float Dx;
	float D;
	float dirtyLevel;
	float rollingResistence;
	float thermalInput;
	float feedbackTorque;
	float loadedRadius;
	float effectiveRadius;
	float liveRadius;
	float pressureStatic;
	float pressureDynamic;
	double virtualKM;
	float lastTempIMO[3];
	float peakSA;
	double grain;
	double blister;
	float inflation;
	double flatSpot;
	float lastGrain;
	float lastBlister;
	float normalizedSlideX;
	float normalizedSlideY;
	float finalDY;
	float wearMult;
};

class SignalGenerator {
public:
	float freqScale;
	int value;

	virtual void _dtor();
	virtual void step(float);
	virtual float getValue();
};

class SinSignalGenerator : public SignalGenerator {};

class TyrePatchData {
public:
	float surfaceTransfer;
	float patchTransfer;
	float patchCoreTransfer;
	float internalCoreTransfer;
	float coolFactorGain;
};

class TyreThermalPatch {
public:
	ACSTD::vector<TyreThermalPatch *> connections;
	float T;
	float inputT;
	int elementIndex;
	int stripeIndex;
};

class TyreThermalModel {
public:
	int elements;
	int stripes;
	ACSTD::vector<TyreThermalPatch> patches;
	double phase;
	TyrePatchData patchData;
	float coreTemp;
	Curve performanceCurve;
	bool isActive;
	float thermalMultD;
	float practicalTemp;
	float camberSpreadK;
	Car *car;
	float coreTInput;
};

class BrushTyreModelData {
public:
	float CF;
	float xu;
	float CF1;
	float Fz0;
	float maxSlip0;
	float maxSlip1;
	float falloffSpeed;
};

class BrushTyreModel {
public:
	BrushTyreModelData data;
};

class TyreSlipInput {
public:
	float slip;
	float friction;
	float load;
	float normalizedSlipX;
	float normalizedSlipY;
	float D;
};

struct TyreSlipOutput {
	float normalizedForce;
	float slip;
};

class BrushSlipProvider {
public:
	BrushTyreModel brushModel;
	float asy;
	int version;
	float maximum;
	float maxSlip;

	virtual TyreSlipOutput getSlipForce(const TyreSlipInput *, bool);
};

class TyreCompoundDef {
public:
	unsigned int index;
	ACSTD::wstring name;
	ACSTD::wstring shortName;
	TyreModelData modelData;
	TyreData data;
	BrushSlipProvider slipProvider;
	float pressureStatic;
	TyrePatchData thermalPatchData;
	Curve thermalPerformanceCurve;
};

class TyreExternalInputs {
public:
	bool isActive;
	float load;
	float slipAngle;
	float slipRatio;
};

struct TyreModelOutput {
	float Fy;
	float Fx;
	float Mz;
	float trail;
	float ndSlip;
	float Dy;
	float Dx;
};

struct TyreModelInput {
	float load;
	float slipAngleRAD;
	float slipRatio;
	float camberRAD;
	float speed;
	float u;
	int tyreIndex;
	float cpLength;
	float grain;
	float blister;
	float pressureRatio;
	bool useSimpleModel;
};

class ITyreModel {
public:
	virtual void dtor();
	virtual TyreModelOutput *solve(TyreModelOutput *result, const TyreModelInput *);
};

class SCTM : public ITyreModel {
	float lsMultY;
	float lsExpY;
	float lsMultX;
	float lsExpX;
	float Fz0;
	float maxSlip0;
	float maxSlip1;
	float asy;
	float falloffSpeed;
	float speedSensitivity;
	float camberGain;
	float dcamber0;
	float dcamber1;
	float cfXmult;
	Curve dyLoadCurve;
	Curve dxLoadCurve;
	float pressureCfGain;
	float brakeDXMod;
	Curve dCamberCurve;
	bool useSmoothDCamberCurve;
	float dCamberBlend;
	float combinedFactor;
	float dy0;
	float dx0;
	float pacE;
	float pacCf;
	float pacFlex;
};

class Tyre {
public:
	TyreInputs inputs;
	TyreData data;
	TyreModelData modelData;
	TyreStatus status;
	ISuspension *hub;
	mat44f worldRotation;
	vec3f unmodifiedContactPoint;
	vec3f contactPoint;
	vec3f contactNormal;
	SurfaceDef *surfaceDef;
	bool debugOutput;
	float absOverride;
	TyreThermalModel thermalModel;
	ACSTD::vector<TyreCompoundDef> compoundDefs;
	ACSTD::function<void __cdecl(void)> onStepCompleted;
	float aiMult;
	BrushSlipProvider slipProvider;
	TyreExternalInputs externalInputs;
	vec3f roadRight;
	vec3f roadHeading;
	bool useLoadForVKM;
	bool driven;
	IRayTrackCollisionProvider *rayCollisionProvider;
	float oldAngularVelocity;
	float totalSlideVelocity;
	mat44f localWheelRotation;
	vec3f worldPosition;
	float slidingVelocityY;
	float slidingVelocityX;
	float roadVelocityX;
	float roadVelocityY;
	float totalHubVelocity;
	float rSlidingVelocityX;
	float rSlidingVelocityY;
	IRayCaster *rayCaster;
	int index;
	SinSignalGenerator shakeGenerator;
	Car *car;
	int currentCompoundIndex;
	bool tyreBlanketsOn;
	const float flatSpotK;
	ITyreModel *tyreModel;
	SCTM scTM;
	float explosionTemperature;
	float blanketTemperature;
	float pressureTemperatureGain;
	float localMX;
};

class OnGearRequestEvent {
public:
	GearChangeRequest request;
	int nextGear;
};

class Drivetrain {
public:
	bool isGearGrinding;
	float finalRatio;
	GearElement engine;
	GearElement drive;
	GearElement outShaftL;
	GearElement outShaftR;
	GearElement outShaftLF;
	GearElement outShaftRF;
	ACSTD::vector<SGearRatio> gears;
	double rootVelocity;
	bool clutchOpenState;
	double ratio;
	float diffPowerRamp;
	float diffCoastRamp;
	float diffPreLoad;
	DifferentialType diffType;
	double cutOff;
	Engine acEngine;
	bool isShifterSupported;
	double clutchMaxTorque;
	float totalTorque;
	float awdFrontShare;
	DifferentialSetting awdFrontDiff;
	DifferentialSetting awdRearDiff;
	DifferentialSetting awdCenterDiff;
	DownshiftProtection downshiftProtection;
	AWD2Data awd2;
	float currentClutchTorque;
	ACSTD::function<void __cdecl(void)> downshiftProtectionFunction;
	Event<OnGearRequestEvent> evOnGearRequest;
	Car *car;
	TractionType tractionType;
	int currentGear;
	double lastRatio;
	Tyre *tyreLeft;
	Tyre *tyreRight;
	GearRequestStatus gearRequest;
	double gearUpTime;
	double gearDnTime;
	double autoCutOffTime;
	double validShiftRPMWindow;
	double controlsWindowGain;
	ACSTD::vector<ITorqueGenerator *> wheelTorqueGenerators;
	double damageRpmWindow;
	double orgRpmWindow;
	int lockCounter[4];
	DrivetrainControllers controllers;
	float clutchInertia;
	float locClutch;
};

class ABS {
public:
	bool isPresent;
	bool isActive;
	float slipRatioLimit;
	float frequency;
	int channels;
	Car *car;
	float timeAccumulator;
	Curve valueCurve;
	unsigned int currentMode;
	float currentValue;
};

class TractionControl {
public:
	bool isPresent;
	bool isActive;
	float slipRatioLimit;
	bool isInAction;
	float frequency;
	Car *car;
	float minSpeedMS;
	float timeAccumulator;
	unsigned int currentMode;
	bool lastValue;
	Curve valueCurve;
};

class SpeedLimiter {
public:
	bool shoudLimit;
	bool isLimiting;
	Car *car;
};

class WingOverrideDef {
public:
	float overrideAngle;
	bool isActive;
};

class Wing {
public:
	WingData data;
	WingState status;
	ACSTD::vector<DynamicWingController> dynamicControllers;
	Car *car;
	RaceEngineer engineer;
	float damageCL[5];
	float damageCD[5];
	bool hasDamage;
	WingOverrideDef overrideStatus;
	const float SPEED_DAMAGE_COEFF;
	const float SURFACE_DAMAGE_COEFF;
};

class AeroMap {
public:
	float referenceArea;
	float CD;
	float CL;
	float frontShare;
	float CDX;
	float CDY;
	float CDA;
	IRigidBody *carBody;
	float dynamicCD;
	float dynamicCL;
	float airDensity;
	ACSTD::vector<Wing> wings;
	vec3f frontApplicationPoint;
	vec3f rearApplicationPoint;
	Car *car;
};

enum class EBBMode {
	Disabled = 0x0,
	Internal = 0x1,
	DynamicController = 0x2,
};

class SteerBrake {
public:
	bool isActive;
	DynamicController controller;
};

class BrakeDisc {
public:
	float t;
	float coolTransfer;
	float torqueK;
	float coolSpeedFactor;
	Curve perfCurve;
};

class BrakeSystem {
public:
	float frontBias;
	float brakePowerMultiplier;
	float electronicOverride;
	float handBrakeTorque;
	float ebbInstant;
	BrakeDisc discs[4];
	float limitDown;
	float limitUp;
	float rearCorrectionTorque;
	Car *car;
	float brakePower;
	float biasOverride;
	bool hasCockpitBias;
	float biasStep;
	EBBMode ebbMode;
	float ebbFrontMultiplier;
	SteerBrake steerBrake;
	bool hasBrakeTempsData;
	ACSTD::ofstream tempRunFile;
	DynamicController ebbController;
};

class ClutchSequence {
public:
	Curve clutchCurve;
	float currentTime;
	bool isDone;
};

class Autoclutch {
public:
	float rpmMin;
	float rpmMax;
	float clutchSpeed;
	bool useAutoOnStart;
	bool useAutoOnChange;
	bool isForced;
	Car *car;
	ClutchSequence clutchSequence;
	Curve upshiftProfile;
	Curve downshiftProfile;
	float clutchValueSignal;
};

enum class TelemetryUnits {
	eUnitMeters = 0x0,
	eUnitC = 0x1,
	eUnitG = 0x2,
	eUnitRadSec = 0x3,
	eUnitGeneric = 0x4,
	eUnitMeterSec = 0x5,
	eUnitBar = 0x6,
	eUnitMS = 0x7,
	eUnitNumber = 0x8,
	eUnitPercentage = 0x9,
	eUnitPowerWatt = 0xA,
	eUnitVolumeMQ = 0xB,
	eUnitVoltageV = 0xC,
	eUnitTorqueNM = 0xD,
	eUnitRad = 0xE,
	eUnitForceN = 0xF,
	eUnitMillimiters = 0x10,
	eUnitDeg = 0x11,
	eUnitForceKG = 0x12,
	eUnitRPM = 0x13,
};

class TelemetryChannelData {
public:
	ACSTD::vector<float> values;
	TelemetryUnits units;
	int frequency;
};

class TelemetryChannel {
public:
	ACSTD::string name;
	TelemetryChannelData data;
	float *dataSource;
	double lastTickTime;
	float scale;
};

class Telemetry {
public:
	ACSTD::vector<TelemetryChannel> channels;
	bool isEnabled;
	ACSTD::wstring driverName;
	bool debugPhysics;
	bool debugAI;
	Car *car;
	float totLift;
	float totDrag;
	float lapBeacon;
	float carSpeedMS;
	float roty;
	float steerAngle;
	float gas;
	float brake;
	float gear;
	float clutch;
	float aiTargetSpeed;
	float aiBGTargetSpeed;
	float aiOutsideOffset;
	float rpms;
	float susTravel[4];
	float wheelSpeed[4];
	TimeTransponder *timeTransponder;
	bool exportEntireSession;
	float awdFrontShare;
	float awdCenterLock;
	float oversteerFactor;
	float rearSpeedRatio;
	float ebbInstant;
	float clutchOpenState;
	float engineVel;
	float driveVel;
	float rootVel;
	float clutchSlip;
	float avgSurfaceTemps[4];
	float practicalTemps[4];
	float splinePosition;

	auto step(float dt) { auto f = (void(__fastcall*)(Telemetry*, float))(NyaHookLib::mEXEBase + 0x2BF5B0); return f(this, dt); }
};

class AutoBlip {
public:
	bool isActive;
	Car *car;
	Curve blipProfile;
	double blipStartTime;
	bool isElectronic;
	double blipPerformTime;
};

class AutoShifter {
public:
	bool isActive;
	int changeUpRpm;
	int changeDnRpm;
	float slipThreshold;
	Car *car;
	bool butGearUp;
	bool butGearDn;
	float gasCutoff;
	float gasCutoffTime;
};

class GearChanger {
public:
	bool wasGearUpTriggered;
	bool wasGearDnTriggered;
	Car *car;
	bool lastGearUp;
	bool lastGearDn;
};

class EDL {
public:
	bool isPresent;
	bool isActive;
	float wheelSpeedGainPower;
	float wheelSpeedGainCoast;
	float deadZonePower;
	float deadZoneCoast;
	float brakeTorquePower;
	float brakeTorqueCoast;
	float outLevel;
	float outBrakeTorque;
	float speedDiff;
	Car *car;
	int leftTyreIndex;
	int rightTyreIndex;
};

class AntirollBar {
public:
	IRigidBody *carBody;
	ISuspension *hubs[2];
	DynamicController ctrl;
	float k;
};

class StabilityControl {
public:
	float gain;
	bool useBeta;
	Car *car;
	float maxGain;
};

class DriftModeComponent {
public:
	Car *car;
	float driftStraightTimer;
	double points;
	double instantDrift;
	double currentSpeedMultiplier;
	double currentDriftAngle;
	int comboCounter;
	int lastDriftDirection;
	bool extremeDrifting;
	bool drifting;
	bool invalid;
	float oldDamageZones[5];

	auto step(float dt) { auto f = (void(__fastcall*)(DriftModeComponent*, float))(NyaHookLib::mEXEBase + 0x2BFF20); return f(this, dt); }
};

class PerformancePair {
public:
	unsigned int t;
	float speedMS;
};

class PerformanceMeter {
public:
	bool isEnabled;
	Car *car;
	ACSTD::vector<PerformancePair> currentLap;
	ACSTD::vector<PerformancePair> bestLap;
	double bestLapTime;
	int lastLapIndex;
	double currentDistance;
	double lastRecordedDistance;
	double currentDiff;
	float currentSpeedDiffMS;

	auto step(float dt) { auto f = (void(__fastcall*)(PerformanceMeter*, float))(NyaHookLib::mEXEBase + 0x26B8E0); return f(this, dt); }
};

class SetupItem {
public:
	ACSTD::wstring name;
	float *connectedFloat;
	ACSTD::wstring units;
	float multiplier;
	float newValue;
	bool attached;
	ACSTD::function<void __cdecl(SetupItem *)> onValueChanged;
	float labelMultiplier;

	virtual void _dtor();
};

enum class DRWWingConnectionMode {
	UseEffect = 0x0,
	UseAngle = 0x1,
};

class DRSWingConnection {
public:
	Wing *wing;
	float effect;
	float angle;
	DRWWingConnectionMode mode;
};

class SetupManager {
public:
	ACSTD::vector<SetupItem> items;
	bool checkRules;
	Car *car;
	ACSTD::vector<float> gearSettings;
	float minimumHeight_m;
	const float maxWaitTime;
	float waitTime;
	CarSetupState setupState;

	auto step(float dt) { auto f = (void(__fastcall*)(SetupManager*, float))(NyaHookLib::mEXEBase + 0x28D090); return f(this, dt); }
};

class DRS {
public:
	bool isPresent;
	bool isActive;
	bool isAvailable;
	bool ignoreZones;
	ACSTD::vector<DRSWingConnection> wings;
	Car *car;
	bool lastState;
	float limitG;
};

enum class KersAttachment {
	Engine = 0x0,
	Wheels = 0x1,
};

class Kers : public ITorqueGenerator {
public:
	KersAttachment attachment;
	Car *car;
	bool present;
	float input;
	float brakeForMaxCharge;
	float charge;
	float chargeK;
	float dischargeK;
	float angularVelocity;
	float negativeInputChargeK;
	bool hasButtonOverride;
	float currentJ;
	float maxJ;
	Curve torqueLUT;
	DynamicController controller;
	bool hasController;
};

class ERSStatus {
public:
	float kineticRecovery;
	float heatRecovery;
};

class ERSPowerController {
public:
	ACSTD::wstring name;
	DynamicController ctrl;
};

class ERSCockpitControls {
public:
	bool recovery;
	bool mguHMode;
	bool deliveryProfile;
};

class ERS : public ITorqueGenerator, public ICoastGenerator {
public:
	bool present;
	float kineticRecovery;
	ERSStatus status;
	bool isHeatCharginBattery;
	ACSTD::vector<ERSPowerController> ersPowerControllers;
	ACSTD::vector<ERSPowerController> ersPowerControllersFront;
	int defaultPowerControllerIndex;
	bool isCharging;
	ERSCockpitControls cockpitControls;
	Car *car;
	double chargeK;
	double dischargeK;
	double dischargeKFront;
	bool hasButtonOverride;
	Curve torqueLUT;
	Curve coastLUT;
	DynamicController controller;
	DynamicController controllerFront;
	double charge;
	float maxJ;
	float currentJ;
	float input;
	double heatChargeK;
	float heatTorque;
	float rearCorrectionTorque;
	DynamicController frontController;
	Curve frontTorqueLUT;
	float frontTorqueVectoringBias;
};

class LapInvalidator {
public:
	double collisionSafeTime;
	Car *car;
	int currentTyresOut;
	bool isInPenaltyZone;
	float lastBlackFlagTime;

	auto step(float dt) { auto f = (void(__fastcall*)(LapInvalidator*, float))(NyaHookLib::mEXEBase + 0x2C0580); return f(this, dt); }
};

enum class PenaltyDescription {
	eNothing = 0x0,
	eJumpStart = 0x1,
	eCantPitPenalty = 0x2,
	eMandatoryPit = 0x3,
	eCut = 0x4,
};
typedef PenaltyDescription PenaltyType;

class PenaltyRecord {
public:
	unsigned int lap;
	unsigned int seconds;
	PenaltyDescription descr;
};

class OnPenaltyEvent {
public:
	Car *car;
	PenaltyType ptype;
};

class PenaltyManager {
public:
	Event<OnPenaltyEvent> evOnPenalty;
	Car *car;
	PenaltyType pendingPenaltyType;
	bool isServingPitPenalty;
	bool rearmPitPenalty;
	__int16 pitPenaltyLaps;
	ACSTD::vector<PenaltyRecord> penaltyRecords;
	unsigned int penaltySecs;
	float inPitMeterCounter;

	auto step(float dt) { auto f = (void(__fastcall*)(PenaltyManager*, float))(NyaHookLib::mEXEBase + 0x265E10); return f(this, dt); }
};

class SplineLocatorData {
public:
	float npos;
	unsigned int currentIndex;
	float lateralOffset;
	float splineLength;
	float sides[2];
	float sidesFromIL[2];
	float sideVelocity;
	bool isOutsideTrackLimits;
};

class FuelLapEvaluator {
public:
	Car *car;
	int lapCount;
	double lapStartFuel;
	double fuelPerLap;
	double totalM;
	double totalLiters;
	double startFuel;
	double oldFuelPerLap;
	bool ignoreLap;

	auto step(float dt) { auto f = (void(__fastcall*)(FuelLapEvaluator*, float))(NyaHookLib::mEXEBase + 0x28D360); return f(this, dt); }
};

class HeaveSpringStatus {
public:
	float travel;
};

class Damper {
public:
	float reboundSlow;
	float reboundFast;
	float bumpSlow;
	float bumpFast;
	float fastThresholdBump;
	float fastThresholdRebound;
};

class SDWSuspensionData {
public:
	vec3f carTopWB_F;
	vec3f carTopWB_R;
	vec3f carBottomWB_F;
	vec3f carBottomWB_R;
	vec3f tyreTopWB;
	vec3f tyreBottomWB;
	vec3f carSteer;
	vec3f tyreSteer;
	vec3f refPoint;
	float hubMass;
	vec3f hubInertiaBox;
};

class PIDController {
public:
	float P;
	float I;
	float D;
	float currentError;
	float integral;
};

class ActiveActuator {
public:
	float targetTravel;
	PIDController pid;
};

class SuspensionStatus {
public:
	float travel;
	float damperSpeedMS;
};

class SusDamageDef {
public:
	float damageAmount;
	float damageDirection;
	float minVelocity;
	float damageGain;
	float maxDamage;
	bool isDebug;
	float lastAmount;
};

class DebugLine {
public:
	vec3f p0;
	vec3f p1;
	vec4f color;
	float seconds;
};

class ISuspension {
public:
	float k;
	float progressiveK;
	float bumpStopRate;
	float bumpStopProgressive;
	float staticCamber;
	float bumpStopUp;
	float bumpStopDn;
	float rodLength;
	float toeOUT_Linear;
	float packerRange;
	float baseCFM;

	virtual void _dtor();
	virtual mat44f *getHubWorldMatrix(mat44f *result);
	virtual vec3f *getPointVelocity(vec3f *result, const vec3f *);
	virtual void addForceAtPos(const vec3f *, const vec3f *, bool, bool);
	virtual void addTorque(const vec3f *);
	virtual void setSteerLengthOffset(float);
	virtual float getSteerTorque();
	virtual vec3f *getHubAngularVelocity(vec3f *result);
	virtual void attach();
	virtual SuspensionStatus *getStatus();
	virtual vec3f *getBasePosition(vec3f *result);
	virtual float getK();
	virtual Damper *getDamper();
	virtual float getPackerRange();
	virtual ACSTD::vector<DebugLine> *getDebugLines(ACSTD::vector<DebugLine> *result, const mat44f *, const mat44f *);
	virtual void setDamage(float);
	virtual void resetDamage();
	virtual float getDamage();
	virtual float getMass();
	virtual void stop();
	virtual vec3f *getVelocity(vec3f *result);
	virtual void getSteerBasis(vec3f *, vec3f *);
	virtual void step(float);
	virtual void setERPCFM(float, float);
	virtual void addLocalForceAndTorque(const vec3f *, const vec3f *, const vec3f *);
};

class Suspension : public ISuspension {
public:
	IRigidBody *carBody;
	IRigidBody *hub;
	vec3f basePosition;
	Car *car;
	bool useActiveActuator;
	IJoint *joints[5];
	IJoint *bumpStopJoint;
	SDWSuspensionData dataRelToWheel;
	SDWSuspensionData dataRelToBody;
	Damper damper;
	ActiveActuator activeActuator;
	SuspensionStatus status;
	int index;
	PhysicsEngine *physicsEngine;
	float steerLinkBaseLength;
	float steerTorque;
	vec3f baseCarSteerPosition;
	float steerAngle;
	SusDamageDef damageData;
};

class MLBall {
public:
	vec3f relToTyre;
	vec3f relToCar;
};

class MLJoint {
public:
	MLBall ballCar;
	MLBall ballTyre;
	IJoint *joint;
};

class SuspensionML : public ISuspension {
public:
	IRigidBody *hub;
	SuspensionStatus status;
	Damper damper;
	Car *car;
	int index;
	std::vector<MLJoint> joints;
	float hubMass;
	vec3f basePosition;
	float steerTorque;
	SusDamageDef damageData;
	vec3f baseCarSteerPosition;
};

class AxleBall {
public:
	vec3f relToAxle;
	vec3f relToCar;
	IJoint *joint;
};

class AxleJoint {
public:
	AxleBall ballCar;
	AxleBall ballAxle;
};

typedef JoypadButton RigidAxleSide;
class SuspensionAxle : public ISuspension {
public:
	RigidAxleSide side;
	Damper damper;
	Car *car;
	IRigidBody *axle;
	SuspensionStatus status;
	vec3f axleBasePos;
	float track;
	float referenceY;
	std::vector<AxleJoint> joints;
	vec3f leafSpringK;
	float attachRelativePos;
};

class SStrutSuspensionData {
public:
	vec3f carStrut;
	vec3f tyreStrut;
	vec3f carBottomWB_F;
	vec3f carBottomWB_R;
	vec3f tyreBottomWB;
	vec3f carSteer;
	vec3f tyreSteer;
	vec3f refPoint;
	float hubMass;
	vec3f hubInertiaBox;
};

class SusStrutDamageDef {
public:
	float damageAmount;
	float damageDirection;
	float minVelocity;
	float damageGain;
	float maxDamage;
	bool isDebug;
	float lastAmount;
};

class SuspensionStrut : public ISuspension {
public:
	IRigidBody *carBody;
	IRigidBody *hub;
	vec3f basePosition;
	IJoint *joints[5];
	IJoint *bumpStopJoint;
	SStrutSuspensionData dataRelToWheel;
	SStrutSuspensionData dataRelToBody;
	Damper damper;
	SuspensionStatus status;
	int index;
	PhysicsEngine *physicsEngine;
	float steerLinkBaseLength;
	float steerTorque;
	vec3f baseCarSteerPosition;
	float steerAngle;
	float strutBaseLength;
	IRigidBody *strutBody;
	float strutBodyLength;
	SusStrutDamageDef damageData;
	Car *car;
};

class HeaveSpring {
public:
	bool isPresent;
	float rodLength;
	HeaveSpringStatus status;
	float k;
	float progressiveK;
	float packerRange;
	float bumpStopRate;
	float bumpStopUp;
	float bumpStopDn;
	Damper damper;
	bool isFront;
	Suspension *suspensions[2];
	Car *car;
};

class SteeringSystem {
public:
	float linearRatio;
	Car *car;
	bool has4ws;
	DynamicController ctrl4ws;
};

enum class SuspensionType {
	DoubleWishbone = 0x0,
	Strut = 0x1,
	Axle = 0x2,
	Multilink = 0x3,
};

class ThermalObject {
public:
	float tmass;
	float coolSpeedK;
	float coolFactor;
	float heatFactor;
	float t;
	float heatAccumulator;

	virtual void _dtor();
};

class CarCollisionBounds {
public:
	vec3f min;
	vec3f max;
	float length;
	float width;
	float lengthFront;
	float lengthRear;
};

class Triangle {
	vec3f points[3];
	plane4f plane;

	virtual void _dtor();
};

class SlipStream {
public:
	Triangle triangle;
	float speedFactorMult;
	float effectGainMult;
	vec3f dir;
	PhysicsEngine *physicsEngine;
	float length;
	float speedFactor;
};

enum class TorqueModeEX {
	original = 0x0,
	reactionTorques = 0x1,
	driveTorques = 0x2,
};

class AISpline;
class Track;
class SplineLocator {
public:
	AISpline *currentSpline;
	Car *car;
	int currentIndex;
	Track *track;
	float normalizedPos;
	float offset;
	bool isOutsideLimits;

	auto step(float dt) { auto f = (void(__fastcall*)(SplineLocator*, float))(NyaHookLib::mEXEBase + 0x2AB5C0); return f(this, dt); }
};

class PitStopTimings {
public:
	float tyreChangeTimeSec;
	float fuelChangeTimeSec;
	float bodyRepairTimeSec;
	float engineRepairTimeSec;
	float suspRepairTimeSec;
};

class PhysicsValueCache {
public:
	Speed speed;
};

class Car {
public:
	float finalSteerAngleSignal;
	float powerClassIndex;
	Event<OnStepCompleteEvent> evOnStepComplete;
	Event<OnControlsProviderChanged> evOnControlsProviderChanged;
	Event<OnLapCompletedEvent> evOnLapCompleted;
	Event<OnSectorSplitEvent> evOnSectorSplit;
	Event<vec3f> evOnForcedPositionCompleted;
	Event<ACSTD::pair<int,int> > evOnTyreCompoundChanged;
	Event<OnCollisionEvent> evOnCollisionEvent;
	Event<double> evOnJumpStartEvent;
	Event<ACSTD::pair<int,int> > evOnPush2Pass;
	float carHalfWidth;
	float userFFGain;
	bool isRetired;
	ACSTD::vector<ACSTD::wstring> tyreCompounds;
	void *tag;
	IRigidBody *body;
	IRigidBody *fuelTankBody;
	IRigidBody *rigidAxle;
	IJoint *fuelTankJoint;
	PhysicsEngine *ksPhysics;
	CarControls controls;
	float steerLock;
	float steerRatio;
	float steerLinearRatio;
	ACSTD::wstring unixName;
	ACSTD::wstring configName;
	ACSTD::wstring carDataPath;
	float mass;
	float ffMult;
	vec3f accG;
	TimeTransponder transponder;
	CarColliderManager colliderManager;
	Drivetrain drivetrain;
	ABS abs;
	TractionControl tractionControl;
	SpeedLimiter speedLimiter;
	AeroMap aeroMap;
	Tyre tyres[4];
	ACSTD::vector<ISuspension *> suspensions;
	BrakeSystem brakeSystem;
	Autoclutch autoClutch;
	unsigned int physicsGUID;
	Telemetry telemetry;
	AutoBlip autoBlip;
	AutoShifter autoShift;
	GearChanger gearChanger;
	EDL edl;
	AntirollBar antirollBars[2];
	StabilityControl stabilityControl;
	double lastCollisionTime;
	DriftModeComponent driftMode;
	PerformanceMeter performanceMeter;
	SetupManager setupManager;
	ACSTD::wstring screenName;
	DRS drs;
	Kers kers;
	ERS ers;
	LapInvalidator lapInvalidator;
	PenaltyManager penaltyManager;
	bool isGearboxLocked;
	bool isGentleStopping;
	double penaltyPerfTarget;
	mat44f pitPosition;
	SplineLocatorData splineLocatorData;
	FuelLapEvaluator fuelLapEvaluator;
	HeaveSpring heaveSprings[2];
	SteeringSystem steeringSystem;
	double lastCollisionWithCarTime;
	SuspensionType suspensionTypeF;
	SuspensionType suspensionTypeR;
	float axleTorqueReaction;
	float lastGyroFF;
	float lastFF;
	float lastPureMZFF;
	ThermalObject water;
	float steerAssist;
	bool isRequestingPitStop;
	int aiLapsToComplete;
	bool lightsOn;
	CarCollisionBounds bounds;
	SlipStream slipStream;
	TorqueModeEX torqueModeEx;
	bool isControlsLocked;
	double lockControlsTime;
	bool blackFlagged;
	double penaltyTimeAccumulator;
	double penaltyTime;
	float expectedFuelPerLap;
	mat44f meshColliderBodyMatrix;
	ICarControlsProvider *controlsProvider;
	vec3f lastVelocity;
	int sleepingFrames;
	float mzCurrent;
	vec3f bodyInertia;
	vec3f explicitInertia;
	double fuel;
	double fuelConsumptionK;
	double maxFuel;
	float requestedFuel;
	double lastBodyMassUpdateTime;
	float damageZoneLevel[5];
	vec3f ridePickupPoint[2];
	vec3f fuelTankPos;
	float vibrationPhase;
	float slipVibrationPhase;
	float flatSpotPhase;
	float slipStreamEffectGain;
	int framesToSleep;
	bool disableMinSpeedPenaltyClear;
	float ballastKG;
	float lastSteerPosition;
	SplineLocator splineLocator;
	bool isCollisionOffForPits;
	PitStopTimings pitTimings;
	vec3f gridPosition;
	bool hasGridPosition;
	bool lastLigthSwitchState;
	PhysicsValueCache valueCache;
	float fuelKG;
	bool externalControl;

	virtual void _dtor();

	auto pollControls(float dt) { auto f = (void(__fastcall*)(Car*, float))(NyaHookLib::mEXEBase + 0x274E70); return f(this, dt); }
	auto updateColliderStatus(float dt) { auto f = (void(__fastcall*)(Car*, float))(NyaHookLib::mEXEBase + 0x276DF0); return f(this, dt); }
	auto stepJumpStart(float dt) { auto f = (void(__fastcall*)(Car*, float))(NyaHookLib::mEXEBase + 0x276780); return f(this, dt); }
	auto isInPits() { auto f = (bool(__fastcall*)(Car*))(NyaHookLib::mEXEBase + 0x274530); return f(this); }
	auto onTyresStepCompleted() { auto f = (void(__fastcall*)(Car*))(NyaHookLib::mEXEBase + 0x274CD0); return f(this); }
};
static_assert(sizeof(Car) == 0x3EA0);