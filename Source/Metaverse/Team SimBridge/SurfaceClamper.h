// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

class AEntityBase;
//Singleton Class
class METAVERSE_API SurfaceClamper
{
private:
	static SurfaceClamper* m_SurfaceClamperInstance;
	SurfaceClamper();
public:
	static SurfaceClamper* GetSurfaceClamperInstance();
	FVector GroundClampEntity(FVector Actorlocation, AEntityBase* entityPtr, UWorld* world);
	~SurfaceClamper();
};
