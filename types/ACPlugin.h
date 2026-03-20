class IACPPluginHost {
public:
	virtual HWND__ *getHwnd();
	virtual HINSTANCE__ *getHInstance();
	virtual void setABS(float);
	virtual void setTC(float);
	virtual void setStabilityControl(float);
	virtual void setIdealLine(bool, bool);
	virtual void setAutoShift(bool);
	virtual void setBrakeBias(float);
	virtual void setSystemMessage(const wchar_t *, const wchar_t *, bool);
};

class ACCarState;
class ACPluginContext;
class ICarControlsProvider;
class CarAvatar;
class Car;
class Sim;
class ACPlugin : public IACPPluginHost {
public:
	ACSTD::wstring name;
	HINSTANCE__ *hModule;
	bool (__fastcall *getName)(wchar_t *);
	bool (__fastcall *init)(IACPPluginHost *);
	bool (__fastcall *shutdown)();
	bool (__fastcall *p_update)(ACCarState *, float);
	bool (__fastcall *p_onGui)(ACPluginContext *);
	bool (__fastcall *getControls)(ICarControlsProvider **);
	CarAvatar *carAvatar;
	Car *car;
	Sim *sim;
};