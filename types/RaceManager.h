class RaceTimingServices;

class OnRaceInitEvent {
public:
	int laps;
};

class Lap {
public:
	unsigned int time;
	ACSTD::vector<unsigned int> splits;
	unsigned int cuts;
	bool isValid;
	ACSTD::wstring compound;
};

class SessionResult {
public:
	ACSTD::vector<ACSTD::vector<Lap>> laps;
	ACSTD::vector<Lap> bestLaps;
	ACSTD::vector<int> positions;
	ACSTD::vector<int> lapCount;
	ACSTD::vector<float> total;
};

class OnSessionEndEvent {
public:
	Session currentSession;
	SessionResult result;
};

class WindSettings {
public:
	float baseSpeed;
	float baseDirection;
};

class MultiplayerStatus {
public:
	std::vector<bool> completedFlags;
};

class RaceManager {
public:
	Event<OnRaceInitEvent> evOnRaceInit;
	Event<OnSessionEndEvent> evOnSessionEnd;
	Event<OnLapCompletedEvent> evOnLapCompleted;
	bool penaltiesEnabled;
	bool officialSpecialEvent;
	bool fixedSetup;
	bool pauseMode;
	int currentSessionIndex;
	float overTimeMult;
	bool timeRaceEnded;
	bool isTimedLastLap;
	bool hasAdditionalLap;
	float pitWindowStartTime;
	float pitWindowEndTime;
	WindSettings windSettings;
	MultiplayerStatus multiplayerStatus;
	bool leaderLastLap;
	Session currentSession;
	Trigger debugTrigger;
	Sim *sim;
	RaceTimingServices *raceTimingServices;
	//ACSTD::shared_ptr<Font> font;
	//ACSTD::vector<Session> sessions;
	//ACSTD::vector<RealTimeCarDesc> carsRealTimePosition;
	//ACSTD::vector<RaceStatusCarDesc> carsRaceStatus;
	//ACSTD::vector<LeaderboardEntry> mpCacheLeaderboard;
	//ACSTD::vector<ACSTD::vector<LeaderboardEntry>> leaderboardHistory;
	//ACSTD::vector<OnSessionEndEvent> sessionHistoryList;
};