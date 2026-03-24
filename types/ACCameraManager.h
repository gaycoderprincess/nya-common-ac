enum class CameraMode {
	eCockpit = 0x0,
	eCar = 0x1,
	eDrivable = 0x2,
	eTrack = 0x3,
	eHelicopter = 0x4,
	eOnBoardFree = 0x5,
	eFree = 0x6,
	eDeprecated = 0x7,
	eImageGeneratorCamera = 0x8,
	eStart = 0x9,
};

enum class FadeMode {
	eFadeColor = 0x0,
	eFadeTexture = 0x1,
};

enum class DrivableCamera {
	eChase = 0x0, // close chase cam, also cockpit
	eChase2 = 0x1, // distant chase cam
	eBonnet = 0x2,
	eBumper = 0x3,
	eDash = 0x4,
};

class FadeModeDef {
public:
	FadeMode mode;
	float fadeTime;
	float fadeTotalTime;
	void *sender;
};

class PersistanceCameraModeDef {
public:
	CameraMode lastCameraMode;
	DrivableCamera lastDrivableCameraMode;
};

class CameraOnBoard;
class CameraMouseControl;
class CinematicFreeCamera;
class CameraTrack;
class CameraHelicopter;
class CameraOnBoardFree;
class CameraCarManager;
class CameraDrivableManager;
class CameraModeStart;
class ImageGeneratorCamera;
class ACCameraManager : public GameObject {
public:
	Event<int> evOnCameraSelectedIndex;
	Event<bool> evOnCameraUpdateDone;
	CameraOnBoard *cameraOnBoard;
	CameraMouseControl *mouseControl;
	CinematicFreeCamera *cinematicMouseControl;
	CameraTrack *cameraTrack;
	CameraHelicopter *cameraHelicopter;
	CameraOnBoardFree *cameraOnBoardFree;
	CameraCarManager *cameraCar;
	CameraDrivableManager *cameraDrivable;
	CameraModeStart *cameraStart;
	ImageGeneratorCamera *imageGeneratorCamera;
	bool isKeyboardCameraControlEnabled;
	int currentGlobalCameraIndex;
	float randomCameraTime;
	float randomOldCameraTime;
	float randomCameraMinTime;
	float randomCameraMaxTime;
	std::vector<int> randomCameraProbabilities;
	bool randomMode;
	CameraMode lastRandomCamera;
	Sim *sim;
	CameraForward *camera;
	CameraMode mode;
	CameraMode lastDrivingMode;
	FadeModeDef fadeMode;
	Texture fadeTexture;
	vec3f fadeColor;
	Event<bool> evOnFadeInFinished;
	PersistanceCameraModeDef persistanceCameraMode;
};