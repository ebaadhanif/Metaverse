#pragma once
//#include "CoreMinimal.h"

constexpr float FPS_30 = 0.0333f;
constexpr float FPS_20 = 0.05f;
constexpr float FPS_10 = 0.1f;
constexpr float FPS_5 = 0.2f;
constexpr float FPS_1 = 1.0f;
#define FEETS_PER_METER 3.280839895013123;


enum class EForceType
{
	OTHERS = 0,
	FRIENDLY = 1,
	OPPOSING = 2,
	NEUTRAL = 3
};


enum class ERemoteEntityType
{
	FIXEDWING_AIRCRAFT = 1,
	ROTORCRAFT,
	ARMORED_VEHICLE,
	GENERAL_VEHICLE,
	SHIPS,
	HUMAN,
	ANIMAL,
	STRUCTURE,
	OTHER_CULTURE_FEATURE,
	VEGETATION,
	RADAR,
	MISSILE,
	BOMB,
	SHELL,
	CHAFF,
	FLARE,
	MUNITION_LAUNCHER,
	RADIO
};

enum class EFieldOfView
{
	WFOV = 1,
	MFOV,
	NFOV,
	SNFOV
};

enum class EProtocolAdapterType
{
	DIS,
	CIGI,
	HLA
};

UENUM()
enum class ELockLineType
{
	None,
	OpposingOnly,
	SameOnly,
	All

};

UENUM()
enum class ELayer {
	TopMost,
	Top,
	TopMid,
	Mid,
	BottomMid,
	Bottom
};

UENUM()
enum class EMarkerType {
	MilitaryBases,
	Cities,
	Villages,
	Roads
};

struct FEntityID
{
	uint16 SiteID;
	uint16 AppID;
	uint16 EntityID;

	FEntityID()
	{
		SiteID = 0;
		AppID = 0;
		EntityID = 0;
	}

	bool operator==(FEntityID entityID) const
	{
		return SiteID == entityID.SiteID && AppID == entityID.AppID && EntityID == entityID.EntityID;
	}
};

struct FEntityType
{
	UCHAR entiyKind;
	UCHAR domain;
	USHORT country;
	UCHAR category;
	UCHAR subcategory;
	UCHAR specific;
	UCHAR extra;

	FEntityType()
	{
		entiyKind = 0; subcategory = 0; category = 0; domain = 0; country = 0; specific = 0; extra = 0;

	}
	bool operator==(const FEntityType& entityType) const
	{
		return category == entityType.category && subcategory == entityType.subcategory &&
			entiyKind == entityType.entiyKind && domain == entityType.domain &&
			country == entityType.country && specific == entityType.specific &&
			extra == entityType.extra;
	}

};

FORCEINLINE uint32 GetTypeHash(const FEntityType& entityType)
{
	uint32 Hash = 0;
	Hash = HashCombine(Hash, GetTypeHash((uint8)entityType.entiyKind));
	Hash = HashCombine(Hash, GetTypeHash((uint8)entityType.domain));
	Hash = HashCombine(Hash, GetTypeHash((uint8)entityType.country));
	Hash = HashCombine(Hash, GetTypeHash((uint8)entityType.category));
	Hash = HashCombine(Hash, GetTypeHash((uint8)entityType.subcategory));
	Hash = HashCombine(Hash, GetTypeHash((uint8)entityType.specific));
	Hash = HashCombine(Hash, GetTypeHash((uint8)entityType.extra));
	return Hash;
}

FORCEINLINE uint32 GetTypeHash(const FEntityID& entityID)
{
	return HashCombine(
		HashCombine(::GetTypeHash(entityID.EntityID), ::GetTypeHash(entityID.AppID)), ::GetTypeHash(entityID.SiteID));
}

enum class ELocalHealth
{
	NO_DAMAGE = 100,
	MINOR_DAMAGE = 75,
	MEDIUM_DAMAGE = 50,
	MAJOR_DAMAGE = 25,
	DESTROYED = 0
};

enum class ModelVisualMode
{
	BattleSpaceMode = 0,
	TexturedMode = 1,
	Mil2525Mode = 2
};

struct FEntityState
{
	FEntityID Id;
	FEntityType entityType;
	ERemoteEntityType RemoteEntityType;
	FRotator Orientation;
	FVector GeodeticLocation;
	FVector WorldLocation;
	FString CallSign;
	EForceType forceType;
	TArray<FEntityID>TrackedEntitiesList;
	TArray<FEntityID>LockedEntitiesList;
	bool isSensorOn;
	ELocalHealth health;
	short speedInKnots;
	int WeightOnWheels;
	bool isLandingGearExtended;
	bool isNavLightsOn;
};

static FRotator ConvertAndNormalizeRadToDeg(FRotator rotator)
{
	FRotator rotatorToReturn;
	rotatorToReturn.Pitch = FMath::RadiansToDegrees(rotator.Pitch);
	rotatorToReturn.Yaw = FMath::RadiansToDegrees(rotator.Yaw) - 90.0f;
	rotatorToReturn.Roll = FMath::RadiansToDegrees(rotator.Roll);
	return rotatorToReturn;
}

struct FDetonationMessage
{
	FEntityID sourceEntityID;
	FEntityID targetEntityID;
	FEntityID explodingEntityID;
	FVector WorldLocation;
};

struct FFireMessage
{
	FEntityID firingEntityID;
	FEntityID targetEntityID;
	FEntityID munitionExpendibleID;
	FVector geodeticLocation;
};

UENUM()
enum class EMenusVR
{
	None = 0,
	MainMenu = 1,
	ShortcutToolbar,
	MapLayers,
	BattlespaceGraphics,
	EntityVisuals,
	EntityLabels,
	Trails,
	Drawings
};

UENUM()
enum class EMenus
{
	None = 0,
	MainMenu = 1,
	EditMenu,
	SettingsMenu,
	ObserverMenu,
	HelpMenu,
	FileDropDown,
	ViewDropDown,
	SettingsDropDown,
	HelpDropDown,
	ObserverDropDown,
	StatusBar,
	EntityVisualsDropDown,
	TrailDropDown,
	MarkersDropDown,
	EntityList,
	ListDropDown,
	TerrainEditorDropDown,
	LocklinesDropDown,
	GraphicsDropDown,
	CoveragesDropDown,
	DrawingsDropDown,
	MAX UMETA(Hidden)
};

ENUM_RANGE_BY_COUNT(EMenus, EMenus::MAX)

UENUM()
enum class EButtonsName
{
	ShadedRelief,
	SplatMap,
	Contours,
	Markers,
	ToggleBorder,
	Borders,
	PakCities,
	IndCities,
	PakBases,
	IndBases,
	Towns,
	InternationalBorder,
	PreviewModels,
	GoToLocation,
	FullScreen,
	ObjectList,
	Hook,
	Unhook,
	Analytics,
	StatusBar,
	EntityVisuals,
	TextureModel,
	ForceBasedModel,
	Mil2525Model,
	EntitySmall,
	EntityMedium,
	EntityLarge,
	Compass,
	HorizontalTrail,
	VerticalTrail,
	Trail30Sec,
	Trail1Min,
	TrailLifetime,
	HorizontalTrail30Sec,
	HorizontalTrail1Min,
	HorizontalTrailLifetime,
	VerticalTrail30Sec,
	VerticalTrail1Min,
	VerticalTrailLifetime,
	EntityLabels,
	AllLocklines,
	OpposingLockline,
	SameLockline,
	GroundCoverages,
	GroundCoveragesFootprints,
	DomeRing,
	HeightVectorRings,
	AircraftCoverage,
	AircraftOriginalCoverage,
	HeadingVector,
	DownVector,
	UpVector,
	LoadDrawing,
	Drawings,
	DrawingsOn,
	DrawingsProjection,
	ClearDrawings,
	ShortcutToolBar,
	LabelSmall,
	LabelMedium,
	LabelLarge,
	LabelOffset1,
	LabelOffset2,
	LabelOffset3,
	Connection,
	AudioSettings,
	Weather,
	Scaling,
	Vegetation,
	VisualGraphics,
	Blink
};

UENUM()
enum class EVisualsButtonStateVR
{
	Off,
	TextureModel,
	ForceBasedModel,
	Mil2525Model
};

struct FButtonState
{
	bool bIsTerrainVisuals = false;
	bool bIsToggleBorder = true;
	bool bIsObjectList = false;
	bool bIsAnalytics = false;
	bool bIsStatusBar = false;
	bool bIsTextureModel = true;
	bool bIsForceBasedModel = false;
	bool bIsMil2525Model = false;
	bool bIsHook = false;
	bool bIsUnhook = false;
	bool bIsCompass = false;
	bool bIsHorizontalTrail = true;
	bool bIsVerticalTrail = true;
	bool bIsEntityLabels = true;
	bool bIsAllLocklines = true;
	bool bIsOpposingLockline = false;
	bool bIsSameLockline = false;
	bool bIsGroundCoverages = true;
	bool bIsGroundCoveragesFootprints = false;
	bool bIsDomeRing = false;
	bool bIsUpVector = true;
	bool bIsHeightVectorRings = true;
	bool bIsAircraftCoverage = false;
	bool bIsAircraftOriginalCoverage = false;
	bool bIsHeadingVector = true;
	bool bIsDownVector = true;
	bool bIsDrawings = true;
	bool bIsDrawingsProjection = true;
	bool bIsTrail = true;
	bool bIsTrail30Sec = false;
	bool bIsTrail1Min = false;
	bool bIsTrailLifetime = true;
	bool bIsShortcutToolBar = false;
	bool bIsBorders = true;
	bool bIsPakCities = true;
	bool bIsIndCities = true;
	bool bIsPakBases = true;
	bool bIsIndBases = true;
	bool bIsTowns = true;
	bool bIsInternationalBorder = true;
	bool bIsEntitySmall = true;
	bool bIsEntityMedium = false;
	bool bIsEntityLarge = false;
	bool bIsLabelSmall = true;
	bool bIsLabelMedium = false;
	bool bIsLabelLarge = false;
	bool bIsLabelOffset1 = true;
	bool bIsLabelOffset2 = false;
	bool bIsLabelOffset3 = false;
	bool bIsTerrainSplat = true;
	EVisualsButtonStateVR EntityVisualStateVR = EVisualsButtonStateVR::ForceBasedModel;
};

UENUM()
enum class Multiplier
{
	Small,
	Medium,
	Large
};

UENUM()
enum class ETrailChannel
{
	Horizontal,
	Vertical
};

struct FButtonStateStruct
{
	ESlateVisibility Visibility;
	bool FeatureActive = false;
	bool buttonVisibility = false;
};

