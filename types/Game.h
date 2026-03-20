class GraphicsManager;
class AudioEngine;
class GameObject;
class RenderWindow;
class IKeyEventListener;
class Joypad;

namespace ksgui {
	class GUI;
}

template<typename T>
class Event {
public:
	std::vector<void*> handlers; // todo?
};

enum JoypadButton {
	None = 0x0,
	Left = 0x1,
	Right = 0x2,
	Up = 0x3,
	Down = 0x4,
	A = 0x5,
	B = 0x6,
	X = 0x7,
	Y = 0x8,
	LeftShoulder = 0x9,
	RightShoulder = 0xA,
	LeftThumb = 0xB,
	RightThumb = 0xC,
	Start = 0xD,
	Back = 0xE,
	LeftTrigger = 0xF,
	RightTrigger = 0x10,
};
typedef JoypadButton MouseButton;

class MouseEvent {
public:
	int x;
	int y;
	MouseButton button;
};

class OnMouseDownEvent : public MouseEvent {};
class OnMouseUpEvent : public MouseEvent {};
class OnMouseMoveEvent : public MouseEvent {};
class OnMouseWheelMovedEvent : public MouseEvent {
public:
	float delta;
};

class OnWindowResizeEvent {
public:
	int width;
	int height;
	RenderWindow *renderWindow;
};

class OnKeyCharEvent {
public:
	unsigned int key;
};

class OnWindowClosedEvent {
public:
	RenderWindow *renderWindow;
};

class OnKeyEvent {
public:
	unsigned int keyCode;
};

class GameStats {
public:
	double cpuTime;
	double updateTime;
	double renderHUDTime;
	double renderTime;
	double renderAudioTime;
};
static_assert(sizeof(GameStats) == 0x28);

class KeyboardManager {
public:
	RenderWindow *renderWindow;
	ACSTD::vector<IKeyEventListener *> listeners;
	IKeyEventListener *focusListener;

	virtual void _dtor();
};
static_assert(sizeof(KeyboardManager) == 0x30);

class JoypadManager {
public:
	ACSTD::unique_ptr<Joypad> joypad;
};

class RenderWindow {
public:
	void *hWnd;
	Event<OnMouseDownEvent> evOnMouseDown;
	Event<OnMouseWheelMovedEvent> evOnMouseWheelMoved;
	Event<OnMouseUpEvent> evOnMouseUp;
	Event<OnMouseMoveEvent> evOnMouseMove;
	Event<OnWindowResizeEvent> evOnWindowResize;
	Event<OnKeyCharEvent> evOnKeyChar;
	Event<OnKeyEvent> evOnKeyDown;
	Event<OnWindowClosedEvent> evOnWindowClosed;
	Event<OnKeyEvent> evOnKeyUp;
	bool disableEventsWithMouseHidden;

	virtual void _dtor();
};
static_assert(sizeof(RenderWindow) == 0xF0);

class GameTime {
public:
	double now;
	float deltaT;
	float smoothDeltaT;
	float fps;
	bool useStabilizer;
	double cappedFPS;
	double startTime;
	bool m_isUsingHRT;

	virtual void _dtor();
};
static_assert(sizeof(GameTime) == 0x38);

class Game {
public:
	bool isRenderingGui;
	bool isSwappingBuffer;
	bool isSuppressingAudioUpdate;
	GameTime gameTime;
	RenderWindow window;
	GraphicsManager *graphics;
	float masterVolume;
	AudioEngine *audioEngine;
	GameStats stats;
	GameObject *root;
	ksgui::GUI *gui;
	KeyboardManager keyboardManager;
	JoypadManager joypadManager;
	int sleepTime;
	Event<float> evOnPreGUI;
	Event<float> evOnPostGui;
	Event<float> evOnRenderFinished;
	Event<float> evOnPostUpdate;
	Event<double> evOnBeginFrame;
	Event<double> evOnEndFrame;
	Event<int> evOnShutdownRequested;
	bool isClosing;

	virtual void _dtor();
	virtual void shutdown();
};
static_assert(sizeof(Game) == 0x278);
static_assert(offsetof(Game, gameTime) == 0x10);
static_assert(offsetof(Game, window) == 0x48);
static_assert(offsetof(Game, masterVolume) == 0x140);
static_assert(offsetof(Game, keyboardManager) == 0x188);

class GameObject {
public:
	Game *game;
	ACSTD::wstring name;
	bool isActive;
	GameObject* parent;
	ACSTD::vector<GameObject*> gameObjects;

	virtual void _dtor();
	virtual void update(float);
	virtual void render(float);
	virtual void renderHUD(float);
	virtual void renderAudio(float);
	virtual void shutdown();
};
static_assert(sizeof(GameObject) == 0x58);