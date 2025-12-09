#pragma once

#include "CoreMinimal.h"



class METAVERSE_API OneEuroFilter
{
public:
	OneEuroFilter(float InMinCutoff = 1.0f, float InBeta = 0.0f, float InDCutoff = 1.0);

	FVector PositionFilter(const FVector& Value, float DeltaTime);
	FQuat RotationFilter(const FQuat& Value, float DeltaTime);
	float MinCutoff;
	float Beta;
	float DCutoff;

	FVector PrevRawPos;
	FVector PrevFilteredPos;
	FVector PrevDerivPos;
	bool bHasPrevPos = false;

	FQuat PrevRawRot;
	FQuat PrevFilteredRot;
	FVector PrevDerivRot;
	bool bHasPrevRot = false;


	float Alpha(float Cutoff, float DeltaTime);
	FVector LowPass(const FVector& Current, const FVector& Prev, float AlphaVal);

	FVector RotationToVector(const FQuat& Rot);
	FQuat VectorToRotation(const FVector& Vec);

};
