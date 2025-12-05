// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserRanging.h"
#include "XmlParser.h"


// Sets default values for this component's properties
ULaserRanging::ULaserRanging()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	//Initialize();
	// ...
}

void ULaserRanging::Initialize()
{
	Title = "LRF";
	GetDefaultValuesFromXML(Title);
}

void ULaserRanging::Initialize(int range, FRotator rotation, FVector position)
{
	laserRange = range;
	Rotation = rotation;
	Position = position;
}

int ULaserRanging::Activate()
{
	float Distance = 0.0f;
	bIsActive = true;
	UWorld* World = GetWorld();
	AActor* Owner = GetOwner();

	if (!World || !Owner) return Distance;

	FVector Origin = GetComponentLocation();
	FVector ForwardVector = GetForwardVector();
	FVector Endpoint = Origin * ForwardVector * laserRange;

	FCollisionQueryParams Params(SCENE_QUERY_STAT(LaserRangeFinder), false, Owner);
	Params.bReturnPhysicalMaterial = false;
	Params.AddIgnoredActor(Owner);

	FHitResult Hit;
	const bool bHit = World->LineTraceSingleByChannel(
		Hit,
		Origin,
		Endpoint,
		ECC_Visibility,
		Params
	);

	if (bHit)
	{
		Distance = Hit.Distance / 100.0f; //cm to m
	}

	return CalculateError(Distance);
}


void ULaserRanging::GetDefaultValuesFromXML(FString title)
{
	auto GetText = [](const FXmlNode* Parent, const FString& Tag) -> FString
		{
			const FXmlNode* Node = Parent->FindChildNode(Tag);
			return Node ? Node->GetContent() : "";
		};

	auto ParseToUint8 = [](const FString& Str)->uint8
		{
			int32 Value = FCString::Atoi(*Str);
			return static_cast<uint8>(Value);
		};

	FString PluginBaseDir = IPluginManager::Get().FindPlugin(TEXT("Systems"))->GetBaseDir();
	FString ContentPath = TEXT("Content/LRFConfig.xml");
	FString Path = FPaths::Combine(PluginBaseDir, ContentPath);

	FXmlFile XmlFile(Path);
	const FXmlNode* Root = XmlFile.GetRootNode();
	const FXmlNode* LRFs = Root->FindChildNode("LRFs");
	if (LRFs)
	{
		for (const FXmlNode* Node : LRFs->GetChildrenNodes())
		{
			if (GetText(Node, "Title") == title)
			{
				TArray<FString> splitvalues;
				GetText(Node, "Position").ParseIntoArray(splitvalues, TEXT(","), true);
				Position.X = ParseToUint8(splitvalues[0]);
				Position.Y = ParseToUint8(splitvalues[1]);
				Position.Z = ParseToUint8(splitvalues[2]);

				GetText(Node, "Rotation").ParseIntoArray(splitvalues, TEXT(","), true);
				Rotation.Roll = ParseToUint8(splitvalues[0]);
				Rotation.Pitch = ParseToUint8(splitvalues[1]);
				Rotation.Yaw = ParseToUint8(splitvalues[2]);

				FString range = GetText(Node, "Range");
				laserRange = ParseToUint8(range) * KM_TO_CM;
			}
		}
	}
}

int ULaserRanging::CalculateError(float Dist)
{
	int error = (RangeError * Dist) / 1000;
	bool randVal = FMath::RandBool();
	if (randVal) return Dist + error;
	else return Dist - error;
}

// Called when the game starts
void ULaserRanging::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void ULaserRanging::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

