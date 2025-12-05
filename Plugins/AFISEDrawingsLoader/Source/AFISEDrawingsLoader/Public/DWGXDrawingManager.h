// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CustomDrawingReader.h" 
#include "IShape.h"
#include "DWGXDrawingManager.generated.h"



UCLASS()
class AFISEDRAWINGSLOADER_API UDWGXDrawingManager : public UObject
{
	GENERATED_BODY()

public:
	// Singleton access
	static UDWGXDrawingManager* Get(UObject* WorldContext);


	void LoadDrawingConfig();


	void LoadAllDrawings();

	void LoadDrawingFromFile(const FString& FullFilePath);

	// Add, Remove, Clear shapes
	void AddShape(TSharedPtr<IShape> Shape);
	void RemoveShape(TSharedPtr<IShape> Shape);
	void ClearAllShapes();

	const TArray<TSharedPtr<IShape>>& GetShapes() const;

	void LoadDrawingFromFileExplorer();

	void Shutdown();


	void ToggleVisibility(bool isVisible);

	void ToggleProjectionVisibility(bool isVisible);

	TSet<FString> LoadedFileSet;

	void SetScale(float Scale);

	// Tuning (cm & abstract "units" your setters consume)
	UPROPERTY(EditAnywhere, Category = "DWGX|DistanceScale") float NearDistanceCm = 3000.f;   // 30 m
	UPROPERTY(EditAnywhere, Category = "DWGX|DistanceScale") float FarDistanceCm = 30000000.f; // 300 km
	UPROPERTY(EditAnywhere, Category = "DWGX|DistanceScale") float NearThicknessUnits = 1.0f;
	UPROPERTY(EditAnywhere, Category = "DWGX|DistanceScale") float FarThicknessUnits = 300000.f;
	UPROPERTY(EditAnywhere, Category = "DWGX|DistanceScale") float Gamma = 1.0f;                // 1 = linear
	UPROPERTY(EditAnywhere, Category = "DWGX|DistanceScale") float ThicknessHysteresis = 0.15f; // skip tiny changes


	UPROPERTY(EditAnywhere, Category = "DWGX|HeightBasedScale") float NearHeightMeters = 30.f;  //30 m
	UPROPERTY(EditAnywhere, Category = "DWGX|HeightBasedScale") float FarHeightMeters = 500000.f;  //500km 


	float LastAppliedHeightUnits = -FLT_MAX;


	// Cache (avoid thrashing)
	TMap<TWeakPtr<IShape>, float> LastAppliedThickness;

	// Update using the world's primary camera (no project dep)
	void UpdateShapeScalesForCamera(UWorld* World);

	// Or: update using an explicit camera position
	void UpdateShapeScalesForCameraAt(const FVector& CamPos);

	UPROPERTY(EditAnywhere, Category = "DWGX|DistanceScale")
	int32 DrawScaleEveryNFrames = 30;
	int32 FramesSinceScaleUpdate = 0;
	void CustomTick(float DeltaTime);
private:

	TArray<TSharedPtr<IShape>> Shapes;

	static UDWGXDrawingManager* SingletonInstance;

	UPROPERTY()
	UCustomDrawingReader* DWGXReader;

	FString NormalizePath(const FString& InPath) const;

	bool isFileLoaded(const FString& FullFilePath) const { return LoadedFileSet.Contains(NormalizePath(FullFilePath)); }




};
