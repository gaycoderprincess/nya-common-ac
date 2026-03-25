class IdealLine;
class TrackObject;
class Model;
class LollipopCrew;
class DynamicTrackManager;

class TrackInfo {
public:
	float length;
};

namespace SunPosition {
	struct Location {
		double longitude;
		double latitude;
		int gmt;
		double nordOffset;
	};
}

class TrackAvatar : public GameObject {
public:
	IdealLine *idealLine;
	ACSTD::vector<TrackObject *> trackObjects;
	TrackInfo info;
	ACSTD::wstring unixName;
	ACSTD::wstring config;
	int playerPitPosition;
	SunPosition::Location trackLocation;
	Sim *sim;
	Model *model;
	Track physicsTrack;
	//ACSTD::map<ACSTD::wstring,ACSTD::vector<Node *>> spawnPositions;
	//SurfacesManager surfacesManager;
	//struct DisplayList *displayList;
	//ACSTD::wstring igPhysicalizePrefix;
	//struct GridSpaceDisplayer *spacePartitioner;
	//ACSTD::vector<LollipopCrew *> lollipopCrews;
	//TrackPhysicsStats physicsStats;
	//ACSTD::vector<DynamicTrackObject> dynamicObjects;
	//DynamicTrackManager *dynamicTrackManager;
	//ACSTD::vector<TrackAvatar::SectorDescription> sectorDescriptions;
};