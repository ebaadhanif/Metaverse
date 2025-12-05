// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraChannel.h"
#include "XmlParser.h"



UCameraChannel::UCameraChannel()
{

}

UCameraChannel::~UCameraChannel()
{
}

void UCameraChannel::Initialize(AActor* actor)
{
	
	ReadXmlFile();
	if (CamerasData.IsEmpty()) return;
	SetupCameraComponent(actor);
	AssignData(0);
	CreateIRMaterialInstance();
}

void UCameraChannel::Initialize(AActor* actor, TArray<float> fovArr, float fPlane, float nPlane, float blurValue,FVector pos,FRotator rot)
{
	SetupCameraComponent(actor);

	CameraData camData;
	camData.FarPlane= fPlane;
	camData.NearPlane= nPlane;
	camData.Position = pos;
	camData.Rotation = rot;
	camData.FOVs = fovArr;
	camData.BlurIntensity = blurValue;
	CamerasData.Add(camData);

	AssignData(0);

}

void UCameraChannel::ZoomOut()
{
	currentFOV = FieldOfView + 1;
	currentFOV = FMath::Clamp(currentFOV, FOVData[0], FOVData[FOVData.Num() - 1]);
	FieldOfView = currentFOV;

}

void UCameraChannel::ZoomIn()
{
	currentFOV = FieldOfView - 1;
	currentFOV = FMath::Clamp(currentFOV, FOVData[0], FOVData[FOVData.Num() - 1]);
	FieldOfView = currentFOV;
}

void UCameraChannel::PrevFOV()
{
	int fovArrayIndex = FindNearestFovFromArray(currentFOV);
	if (fovArrayIndex > 0)
		SetFOVDataToCamera(FOVData[fovArrayIndex - 1]);
}

void UCameraChannel::NextFOV()
{
	int fovArrayIndex = FindNearestFovFromArray(currentFOV);
	if (fovArrayIndex < FOVData.Num() - 1)
		SetFOVDataToCamera(FOVData[fovArrayIndex + 1]);
}

void UCameraChannel::IncBlur()
{
	PostProcessSettings.bOverride_DepthOfFieldFocalDistance = true;
	PostProcessSettings.DepthOfFieldFocalDistance += 1.f;
	PostProcessSettings.DepthOfFieldFocalDistance = FMath::Clamp(PostProcessSettings.DepthOfFieldFocalDistance, 0, 50);
}

void UCameraChannel::DecBlur()
{
	PostProcessSettings.bOverride_DepthOfFieldFocalDistance = true;
	PostProcessSettings.DepthOfFieldFocalDistance -= 1.f;
	PostProcessSettings.DepthOfFieldFocalDistance = FMath::Clamp(PostProcessSettings.DepthOfFieldFocalDistance, 0, 50);
}


void UCameraChannel::SetFOVDataToCamera(float fov)
{
	currentFOV = fov;
	FieldOfView = currentFOV;
}

int UCameraChannel::FindNearestFovFromArray(float cFov)
{
	float smallestdiff = FMath::Abs(FOVData[0] - cFov);
	int closestFov = 0;
	for (int i = 0; i < FOVData.Num(); i++)
	{
		float diff = FMath::Abs(FOVData[i] - cFov);
		if (diff < smallestdiff)
		{
			closestFov = i;
			smallestdiff = diff;
		}
	}
	return closestFov;
}

UCameraComponent* UCameraChannel::CreateCameraComponent(AActor* actor)
{
	return NewObject<UCameraComponent>(actor, UCameraComponent::StaticClass(), TEXT("Title"));
}

void UCameraChannel::SetupCameraComponent(AActor* actor)
{
	
}

void UCameraChannel::AssignData(int n)
{
	Title = CamerasData[n].Title;
	camPosition = CamerasData[n].Position;
	camRotation = CamerasData[n].Rotation;
	nearPlane= CamerasData[n].NearPlane;
	farPlane = CamerasData[n].FarPlane;
	blurIntensity = CamerasData[n].BlurIntensity;
	FOVData = CamerasData[n].FOVs;
	AssignDataToCamera();
}

void UCameraChannel::AssignDataToCamera()
{
	SetOrthoFarClipPlane(farPlane);
	SetOrthoNearClipPlane(nearPlane);
	SetFOVDataToCamera(FOVData[0]);
	SetRelativeLocationAndRotation(camPosition, camRotation);
	PostProcessSettings.bOverride_DepthOfFieldFocalDistance = true;
	PostProcessSettings.DepthOfFieldFocalDistance = blurIntensity;
}

void UCameraChannel::ReadXmlFile()
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


	FString PluginBaseDir = IPluginManager::Get().FindPlugin(TEXT("Sensors"))->GetBaseDir();
	FString ContentPath = TEXT("Content/OpticalCameraConfig.xml");
	FString Path = FPaths::Combine(PluginBaseDir, ContentPath);

	FXmlFile XmlFile(Path);
	const FXmlNode* Root = XmlFile.GetRootNode();
	const FXmlNode* Cameras = Root->FindChildNode("Cameras");
	if (Cameras)
	{
		for (const FXmlNode* Node : Cameras->GetChildrenNodes())
		{
			CameraData cam;
			TArray<FString> splitvalues;

			GetText(Node, "Position").ParseIntoArray(splitvalues, TEXT(","), true);

			cam.Position.X	   = ParseToUint8(splitvalues[0]);
			cam.Position.Y	   = ParseToUint8(splitvalues[1]);
			cam.Position.Z	   = ParseToUint8(splitvalues[2]);

			GetText(Node, "Rotation").ParseIntoArray(splitvalues, TEXT(","), true);

			cam.Rotation.Roll  = ParseToUint8(splitvalues[0]);
			cam.Rotation.Pitch = ParseToUint8(splitvalues[1]);
			cam.Rotation.Yaw   = ParseToUint8(splitvalues[2]);

			cam.Title		   = GetText(Node, "Title");
			cam.FarPlane	   = FCString::Atof(*GetText(Node, "FarPlane"));
			cam.NearPlane	   = FCString::Atof(*GetText(Node, "NearPlane"));
			cam.BlurIntensity  = FCString::Atof(*GetText(Node, "BlurIntensity"));

			const FXmlNode* fov = Node->FindChildNode("FOVs");
			for (const FXmlNode* fovNode : fov->GetChildrenNodes())
			{
				cam.FOVs.Add(FCString::Atof(*fovNode->GetContent()));
			}

			CamerasData.Add(cam);

		}
	}

}

TArray<FString> UCameraChannel::GetTagValues(FString& Source, FString Tag)
{
	TArray<FString> OutValues;

	FString StartTag = "<" + Tag + ">";
	FString EndTag = "</" + Tag + ">";

	int32 SearchPos = 0;

	while (true)
	{
		int32 Start = Source.Find(StartTag, ESearchCase::IgnoreCase, ESearchDir::FromStart, SearchPos);
		if (Start == INDEX_NONE) break;
		Start += StartTag.Len();
		int32 End = Source.Find(EndTag, ESearchCase::IgnoreCase, ESearchDir::FromStart, SearchPos);
		if (End == INDEX_NONE) break;

		FString Value = Source.Mid(Start, End - Start).TrimStartAndEnd();
		OutValues.Add(Value);
		SearchPos = End + EndTag.Len();

	}

	return OutValues;
}

void UCameraChannel::CreateIRMaterialInstance()
{
	UMaterialInterface* IRMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/IR_Effect.IR_Effect"));
	IRMaterialInstanceTest = UMaterialInstanceDynamic::Create(IRMaterial, this);
}

UCameraComponent* UCameraChannel::GetCameraComponent()
{
	return nullptr;
}


