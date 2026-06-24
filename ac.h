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
#include "types/GraphicsManager.h"
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

class AIBrakePointData {
public:
	float targetSpeed;
	float targetNormalized;
	float apexNormalized;
	bool wasObstacle;
	float lateralOffset;
	float speedDiff;
};

class AISinOffsetData {
public:
	double phase;
	double phaseSpeed;
	float steerOffset;
	float lastFinalOffset;
};

enum class SplineSelection {
	FastLane = 0x0,
	Pits = 0x1,
};

class HumanizeData {
public:
	double minTimeBetweenMistakesMS;
	double timeBetweenMistakesMS;
	float brakeMistakeTime;
	float tractionMistake;
	double nextBrakeMistake;
	double nextTractionMistake;
	float tractioMistakeSeverity;
};

class AITurboStrategy {
public:
	bool active;
	int qualifyHotLaps;
};

class AIKersArea {
public:
	float start;
	float end;
	float length;
	float time;
};

class AISplinePayload {
public:
	float speedMS;
	float radius;
	float sides[2];
	float camber;
	float direction;
	vec3f normal;
	vec3f forwardVector;
	float length;
	float gas;
	float brake;
	float grade;
	float grip;
	float distFromCorner;
	float distFromNextCorner;
	bool isPitlane;
	float compression;
};

class AIOpponentData {
public:
	float dist_front;
	float dist_back;
	float lateral_offset;
	bool isEngaged;
	float speedMS;
	float tti;
	float spaceLeft;
	float spaceRight;
	vec3f relPos;
	float relAngle;
	bool isBlocker;
	float isUnderAttack;
	float relXSpeed;
	float distToPass;
	Car *car;
	bool isOutsideTrack;
};

class AIBrakeObstacle {
public:
	float distance;
	float speedMS;
	AIOpponentData *odata;
};

struct AIBrakeProfilerItem {
	float npos;
	float speed;
	float accx;
	float accz;
};

class AIBrakeProfiler {
public:
	bool isEnabled;
	ACSTD::vector<AIBrakeProfilerItem> items;
	bool lastRecKeyStatus;
	float lastProfiledNPos;
};

class TyreCompoundStrategy {
public:
	float maxKm;
};

class AIVariation {
public:
	float blend;
	float startPush;
	float targetPush;
	float accum;
	float currentPush;
	float variationTime;
};

class AIWingSetup {
public:
	int index;
	SetupItem *item;
	float minValue;
	float maxValue;
};

class AISetup {
public:
	SetupItem *finalRatio;
	ACSTD::vector<float> ratios;
	double lastSetupChangeTime;
	ACSTD::vector<AIWingSetup> wings;
};

class AIDriver : public ICarControlsProvider {
public:
	float STRAIGHT_RADIUS;
	float aggression;
	float steerMinLookahead;
	float gasBrakeLookahead;
	float basePush;
	AIBrakePointData brakePoint;
	vec3f steerTarget;
	PIDController pidSteer;
	float steerGain;
	SplineSelection splineSelection;
	float brakeHintBase;
	float brakeHintLive;
	float changeUpRPM;
	float changeDnPerc;
	bool requestPitStop;
	float nextCarModifier;
	HumanizeData humanize;
	float distToNextCorner;
	float aeroHint;
	float tyresHint;
	float understeerFactor;
	float prjDNRPM;
	double timeToStart;
	float kerbModifier;
	float outsideOffset;
	float mongolinoMaxGas;
	float genome[20];
	bool useMagicForces;
	float understeerHint;
	float liveOffset;
	float offsetDistFromCorner;
	float ultraGrip;
	double lastGearUPChangeTime;
	double lastGearDNChangeTime;
	bool isChangingUp;
	bool isRetiring;
	AISinOffsetData sinOffsetData;
	double reactionTime;
	float oldSteer;
	float targetSpeed;
	unsigned int startTime;
	double avgSpeed;
	float requestedLane;
	float dynamicPush;
	int stepCount;
	int freqCounter;
	Car *car;
	bool isReactingSlow;
	AITurboStrategy turbo;
	RaceEngineer engineer;
	float autoBrakeAdjust;
	bool isSteeringToPit;
	float dangerPush;
	float wingVariation;
	ACSTD::vector<AIKersArea> kersAreas;
	float kersAccum;
	float tyreStopMinValue;
	float tyreStopMinValueVKM[4];
	AISplineRecorder *aiSplineRecorder;
	AISpline *currentSpline;
	float gasRequest;
	float brakeRequest;
	float steerRequest;
	bool pitLaneStartFlag;
	float currentOffset;
	float desiredOffset;
	AISplinePayload currentPayload;
	int lapsToComplete;
	double timeToStartRevvingAtStart;
	bool raceStartFlag;
	int runLapCounter;
	ACSTD::vector<AIOpponentData> opponentData;
	ACSTD::vector<AIBrakeObstacle> brakeObstacles;
	float gasApexDelay;
	int preferredCompound;
	bool hasChoosenTyres;
	AIBrakeProfiler brakeProfiler;
	float accidentStopCounter;
	ACSTD::map<ACSTD::wstring,TyreCompoundStrategy> tyreStrategies;
	SessionInfo currentSessionInfo;
	float locNpos;
	int currentPitLineIndex;
	float splineTargetSpeed;
	float oversteerTCMult;
	float minForwardSides[2];
	bool isEngaged;
	AIVariation aiVariation;
	float engagedPush;
	bool useAbs;
	AISetup aiSetup;
	double lastDRSActivationTime;
	float smoothLoads[4];
	float aggressionHint;
	float targetSteerFinal;
};
static_assert(sizeof(AIDriver) == 0x3E8);
static_assert(offsetof(AIDriver, aggression) == 0x1C);
static_assert(offsetof(AIDriver, nextCarModifier) == 0x80);
static_assert(offsetof(AIDriver, isRetiring) == 0x159);
static_assert(offsetof(AIDriver, wingVariation) == 0x1E4);
static_assert(offsetof(AIDriver, opponentData) == 0x2A8);
static_assert(offsetof(AIDriver, splineTargetSpeed) == 0x350);