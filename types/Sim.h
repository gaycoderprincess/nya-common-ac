class PauseMenu;
class ESCMenu;
class Node;
class CarNodeSorter;
class NodeEvent;
class TrackAvatar;
class DrivingAssistManager;
class MirrorTextureRenderer;
class ACCameraManager;
class SystemMessage;
class SystemNotification;
class RaceManager;
class ReplayManager;
class PhysicsAvatar;
class ScreenCapturer;
class ACClient;
class PitStop;
class TimeLimitedTest;
class QuickMenu;
class MicroSectors;
class CarAvatar;
class Console;
class SimScreen;
class CameraForward;
class SkyBox;
class ACErrorHandler;
class DebugVisualizer;
namespace ksgui {
	class GameScreen;
	class FormRenderStats;
}
class EndSessionDisplayer;
class SessionLeaderboard;
class VirtualMirrorRenderer;

struct OnNewCarLoadedEvent {
	CarAvatar *car;
};

enum eReplayStatus {
	eReplayPlay = 0x0,
	eReplayPause = 0x1,
	eReplayStop = 0x2,
	eReplayRewind = 0x3,
	eReplayFastForward = 0x4,
	eReplaySlowMotion = 0x5,
	eReplayModeEnter = 0x6,
	eReplayModeExit = 0x7,
	eReplayChangeCar = 0x8,
	eReplayClearing = 0x9,
	eReplaySliderInteraction = 0xA,
	ePhotoMode = 0xB,
	eSingleFrame = 0xC,
};

class OnReplayStatusChanged {
public:
	eReplayStatus status;
	float timeMult;
	float slowMotionLevel;
};

class CollisionEvent {
public:
	int carIndex;
	float normalForce;
	vec3f pos;
	vec3f normal;
	float impactAngle;
	float relativeSpeed;
	unsigned int colliderCategory;
};

enum SessionType {
	Undefined = 0x0,
	Pratice = 0x1,
	Qualify = 0x2,
	Race = 0x3,
	Hotlap = 0x4,
	TimeAttack = 0x5,
	Drift = 0x6,
	Drag = 0x7,
};

class Session {
public:
	SessionType sessionType;
	bool isTimedRace;
	bool hasAdditionalLap;
	int laps;
	float durationMinutes;
	float overtime_ms;
	ACSTD::wstring spawSet;
	ACSTD::wstring name;
	double startTime;
	int forcedPosition;
	bool isOver;
	unsigned int leaderCompletedLaps;
};

class OnNewSessionEvent {
public:
	Session newSession;
	int16_t index;
};

class HDRLevels {
public:
	float minExposure;
	float maxExposure;
};

class CommandItem {
public:
	int key;
};

class CommandManager {
public:
	ACSTD::map<ACSTD::wstring,CommandItem> commands;
};

class OptionsManager {
public:
	ACSTD::map<ACSTD::wstring,float> options;

	virtual void _dtor();
};

class Trigger {
public:
	bool state;
	bool lastState;
	float accumulator;
	float accumulatorLimit;
};

class Texture {
public:
	void *kid;
	ACSTD::wstring fileName;
};

template<typename T>
class BufferedChannel {
public:
	uint8_t _0[0x28];
};

class IKeyEventListener {
public:
	virtual void onKeyDown(const OnKeyEvent *);
	virtual void onKeyChar(const unsigned int);
};

class Sim : public GameObject, public IKeyEventListener {
public:
	Event<OnNewCarLoadedEvent> evNewCarLoaded;
	Event<OnReplayStatusChanged> evOnReplayStatusChanged;
	Event<bool> evOnPauseModeChanged;
	Event<CollisionEvent> evOnCollisionEvent;
	Event<OnNewSessionEvent> evOnNewSession;
	HDRLevels hdrLevels;
	CommandManager commandManager;
	OptionsManager optionsManager;
	ksgui::GameScreen *gameScreen;
	PauseMenu *pauseMenu;
	ESCMenu *escMenu;
	Node *rootNode;
	Node *trackNode;
	CarNodeSorter *carsNode;
	Node *skidMarkNode;
	Node *particlesNode;
	NodeEvent *carFakeShadowsNode;
	TrackAvatar *track;
	Node *blurredNode;
	Node *unblurredNode;
	DrivingAssistManager *drivingAidsManager;
	NodeEvent *renderFinishedNodeEvent;
	NodeEvent *beforeCarsNode;
	MirrorTextureRenderer *mirrorTextureRenderer;
	ACCameraManager *cameraManager;
	struct NodeDirtCamera *cameraDirtNode;
	SystemMessage *systemMessage;
	SystemNotification *systemNotification;
	RaceManager *raceManager;
	ReplayManager *replayManager;
	PhysicsAvatar *physicsAvatar;
	ScreenCapturer *screenCapturer;
	ACClient *client;
	PitStop *pitStop;
	TimeLimitedTest *timeLimitedTest;
	bool useProView;
	bool isVrConnected;
	bool isRoomVR;
	bool isVirtualMirrorForced;
	bool useMousePitstop;
	QuickMenu *quickMenu;
	MicroSectors *microSectors;
	bool serializeForms;
	int connectedCarsCount;
	bool allowFreeCamera;
	bool tripleScreenMode;
	bool audioPerformanceSpew;
	ACSTD::vector<CarAvatar *> cars;
	unsigned int focusedCarIndex;
	float cameraFadeTime;
	Console *console;
	SimScreen *simScreen;
	CameraForward *sceneCamera;
	SkyBox *skyBox;
	ACErrorHandler *errorHandler;
	DebugVisualizer *debugVisualizer;
	ksgui::FormRenderStats *formRenderStats;
	EndSessionDisplayer *endSessionDisplayer;
	SessionLeaderboard *leaderboard;
	Trigger changingCameraTrigger;
	VirtualMirrorRenderer *virtualMirrorRenderer;
	BufferedChannel<ACSTD::function<void __cdecl(void)> > chFunctions;
	float lastDT;
	NodeEvent *node3DGUI;
	ACSTD::map<ACSTD::wstring,Texture> flagMapCache;
};
static_assert(sizeof(Sim) == 0x2D0);
static_assert(offsetof(Sim, carsNode) == 0x130);