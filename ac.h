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

class ComparativeTelemetry;
class RaceControlScreen;
class EscMenuTimeTable;
class GLRenderer;
class Font;

enum class eFontAlign {
	eAlignLeft = 0x0,
	eAlignRight = 0x1,
	eAlignCenter = 0x2,
};

namespace ksgui {
	class ActiveButton;
	class Control;
	class Label;
	class Spinner;
	
	class ksRect {
	public:
		float left;
		float right;
		float top;
		float bottom;
	};

	struct OnControlClicked {
		Control *control;
		int localx;
		int localy;
	};
	
	class Control {
	public:
		ACSTD::wstring name;
		ksgui::ksRect rect;
		vec4f backColor;
		vec4f borderColor;
		vec4f foreColor;
		vec4f highlightTextColor;
		bool highlight;
		vec4f backTextureColor;
		ACSTD::shared_ptr<Font> font;
		ACSTD::vector<ksgui::Control *> controls;
		ksgui::Control *parent;
		eFontAlign fontAlign;
		Event<ksgui::OnControlClicked> evClicked;
		void *tag;
		Texture backTexture;
		bool drawBorder;
		bool drawBackground;
		float repeatInterval;
		float fontScale;
		ACSTD::wstring text;
		bool isHighlight;
		ksgui::GUI *gui;
		bool visible;
		bool isMouseDown;
		float intervalCounter;
		bool isRepeating;
		float scaleMult;
		GLRenderer *controlGLR;
		ksgui::ksRect rectBase;

		virtual void _dtor();
		virtual bool hitTest(int, int);
		virtual void addControl(ksgui::Control *);
		virtual void render(float);
		virtual vec2f *localToWorld(vec2f *result, const vec2f *);
		virtual vec2f *worldToLocal(vec2f *result, const vec2f *);
		virtual void getWorldRect(ksgui::ksRect *);
		virtual void setSize(float, float);
		virtual void onVisibleChanged(bool);
		virtual bool isMousePressing();
		virtual bool onMouseDown(const OnMouseDownEvent *);
		virtual void onMouseUp(const OnMouseUpEvent *);
		virtual void onMouseMove(const OnMouseMoveEvent *);
		virtual void onMouseWheelMovedEvent(const OnMouseWheelMovedEvent *);
		virtual void onKeyChar(const unsigned int);
		virtual void onKeyDown(const OnKeyEvent *);
		virtual void setRepeatInterval(float);
		virtual void setText(const ACSTD::wstring *);
		virtual const ACSTD::wstring *getText();
		virtual void scaleByMult(float);
		virtual void scaleByMult();
	};
}

class OnESCMenuTriggered {
public:
	ESCMenu *menu;
	bool visible;
	bool startReplay;
};

class TabBar;
class SetupTab;
class SetupInformation;
class SetupIOManager;
class SetupGearManager;
class SetupTyresManager;
class SetupFuelManager;
class SetupElectronics;
class SetupPitstopPresets;

enum class eShowClicksType
{
	eShowClicksNone = 0x0,
	eShowClicks = 0x1,
	eShowClicksAbs = 0x2,
};

class SetupItemDef {
public:
	ACSTD::wstring name;
	SetupItem *connection;
	double minValue;
	double maxValue;
	double step;
	float px;
	float py;
	eShowClicksType showClicksMode;
	int defaultValue;
	ACSTD::wstring helpKey;
};

class SetupTab : public ksgui::Control {
public:
	bool modifiedValues;
	ksgui::Label *titleLabel;
	ACSTD::vector<SetupItemDef *> items;
	ACSTD::vector<ksgui::Spinner *> spinners;
	Sim *sim;

	void ctor(ACSTD::wstring* aname, ksgui::GUI* aGui, Sim* sim) {
		auto f = (void(__fastcall*)(SetupTab*, ACSTD::wstring*, ksgui::GUI*, Sim*))(NyaHookLib::mEXEBase + 0x183130);
		return f(this, aname, aGui, sim);
	}

	auto addItem(SetupItemDef* item) {
		auto f = (void(__fastcall*)(SetupTab*, SetupItemDef*))(NyaHookLib::mEXEBase + 0x183850);
		return f(this, item);
	}
};
static_assert(offsetof(SetupTab, items) == 0x188);

class SetupScreen : public ksgui::Control {
public:
	ACSTD::wstring carName;
	Sim *sim;
	TabBar *tabBar;
	ACSTD::vector<SetupTab *> tabs;
	SetupInformation *setupInfo;
	SetupIOManager *ioManager;
	SetupGearManager *gearManager;
	SetupTyresManager *tyresManager;
	SetupFuelManager *fuelManager;
	SetupElectronics *electronicsManager;
	SetupPitstopPresets *pitstopManager;

	void ctor(Sim* sim) {
		auto f = (void(__fastcall*)(SetupScreen*, Sim*))(NyaHookLib::mEXEBase + 0x17C010);
		return f(this, sim);
	}

	auto getSetupTab(ACSTD::wstring* name) {
		auto f = (SetupTab*(__fastcall*)(SetupScreen*, ACSTD::wstring*))(NyaHookLib::mEXEBase + 0x17D650);
		return f(this, name);
	}
};

class ESCMenu : public ksgui::Control {
public:
	Event<OnESCMenuTriggered> evOnESCMenuTriggered;
	Event<bool> evOnDriveMenuPressed;
	SetupScreen *setupScreen;
	bool showLeaderboard;
	bool driveMenuPressed;
	float fadeTime;
	OnESCMenuTriggered message;
	float width;
	Texture acLogo;
	Sim *sim;
	ksgui::ActiveButton *butExit;
	ksgui::ActiveButton *butDrive;
	ksgui::ActiveButton *butDriveFake;
	ksgui::ActiveButton *butSetup;
	ksgui::ActiveButton *butTime;
	ksgui::ActiveButton *butNextSession;
	ksgui::ActiveButton *butComparativeTelemetry;
	ksgui::ActiveButton *lastSelected;
	ksgui::ActiveButton *butRaceControl;
	ComparativeTelemetry *comparativeTelemetry;
	RaceControlScreen *raceControl;
	EscMenuTimeTable *timeTable;
};