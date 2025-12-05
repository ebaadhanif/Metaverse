// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimbal.h"

Gimbal::Gimbal()
{


}

Gimbal::~Gimbal()
{

}


void Gimbal::Initialize()
{
	
}

float Gimbal::IncPitchPanSpeed()
{
	return CurrentPitchPanSpeedValue += 1;
}

float Gimbal::IncYawPanSpeed()
{
	return CurrentYawPanSpeedValue += 1;
}

float Gimbal::DecPitchPanSpeed()
{
	return CurrentPitchPanSpeedValue -= 1;
}

float Gimbal::DecYawPanSpeed()
{
	return CurrentYawPanSpeedValue -= 1;
}

FRotator Gimbal::PanYaw(float val)
{
	return CurrentPanRot += FRotator(0, CurrentYawPanSpeedValue * val, 0);
	//return FRotator(0);
}

FRotator Gimbal::PanPitch(float val)
{
	return CurrentPanRot += FRotator( CurrentPitchPanSpeedValue* val, 0,0);
	//return FRotator(0);

}

void Gimbal::ReadXmlFile()
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
	FString ContentPath = TEXT("Content/GimbelConfig.xml");
	FString Path = FPaths::Combine(PluginBaseDir, ContentPath);

	FXmlFile XmlFile(Path);
	const FXmlNode* Root = XmlFile.GetRootNode();
	const FXmlNode* Azimuth = Root->FindChildNode("Gimbal");

	if (Azimuth)
	{
		for (const FXmlNode* Node : Azimuth->GetChildrenNodes())
		{
			if (Node->GetTag() == "AzimuthValues")
			{
				azimuthValues.AzimuthMin   = FCString::Atof(*GetText(Node, "AzimuthMin"));
				azimuthValues.AzimuthMax   = FCString::Atof(*GetText(Node, "AzimuthMax"));
				azimuthValues.ElevationMax = FCString::Atof(*GetText(Node, "ElevationMin"));
				azimuthValues.ElevationMin = FCString::Atof(*GetText(Node, "ElevationMax"));

			}
			else
			{
				PitchPanSpeed = FCString::Atof(*GetText(Node, "PitchPanSpeed"));
				YawPanSpeed   = FCString::Atof(*GetText(Node, "YawPanSpeed"));

				TArray<FString> splitvalues;
				FString value;

				value = GetText(Node, "InitialRotation");
				if (!value.IsEmpty())
				{

					value.ParseIntoArray(splitvalues, TEXT(","), true);

					InitialRotation.Roll  = ParseToUint8(splitvalues[0]);
					InitialRotation.Pitch = ParseToUint8(splitvalues[1]);
					InitialRotation.Yaw   = ParseToUint8(splitvalues[2]);

				}

				value = GetText(Node, "InitialPosition");

				if (!value.IsEmpty())
				{

					GetText(Node, "InitialPosition").ParseIntoArray(splitvalues, TEXT(","), true);

					InitialPosition.X = ParseToUint8(splitvalues[0]);
					InitialPosition.Y = ParseToUint8(splitvalues[1]);
					InitialPosition.Z = ParseToUint8(splitvalues[2]);
				}
			}
		}
	}

	CurrentPanRot = InitialRotation;
	CurrentPanPitch = InitialRotation;
	CurrentPanYaw = InitialRotation;
	CurrentPitchPanSpeedValue = PitchPanSpeed;
	CurrentYawPanSpeedValue = YawPanSpeed;

}
