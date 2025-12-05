// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XmlParser.h"
#include "Interfaces/IPluginManager.h"


struct AzmuthValues
{
public:
	float AzimuthMin;
	float AzimuthMax;
	float ElevationMin;
	float ElevationMax;
};

class SYSTEMS_API Gimbal :public  USceneComponent
{
private:
		
	float PitchPanSpeed;
	float CurrentPitchPanSpeedValue;
	float YawPanSpeed;
	float CurrentYawPanSpeedValue;
	FRotator CurrentPanYaw;
	FRotator CurrentPanPitch;
	FRotator CurrentPanRot;
	FRotator InitialRotation;
	FVector InitialPosition;
	AzmuthValues azimuthValues;

public:
	Gimbal();
	~Gimbal();

	void Initialize();
	void ReadXmlFile();
	FRotator PanYaw(float);
	FRotator PanPitch(float);
	float IncPitchPanSpeed();
	float IncYawPanSpeed();
	float DecPitchPanSpeed();
	float DecYawPanSpeed();

private:

};
