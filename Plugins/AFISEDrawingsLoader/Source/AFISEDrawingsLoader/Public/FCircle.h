#pragma once

#include "IShape.h"

class AFISEDRAWINGSLOADER_API FCircle : public IShape
{
public:
	FCircle(const FVector& InWorldPos, const FVector& InLatLongHeight, float InRadius);

	virtual FString GetShapeType() const override;
	virtual FVector GetWorldPosition() const override;
	virtual FVector GetLatLongHeightPosition() const override;
	virtual void CreateMeshes(UWorld* World) override;
	virtual void Draw(UWorld* World) override;
	void DrawCoverageFootPrint(UWorld* World, int32 Height);
	virtual void SetProjectionVisibility(bool bVisible) override;
	virtual void SetVisibility(bool bVisible) override;
	virtual void SetLineColor(const FLinearColor& InColor) override;
	virtual void SetLineHeight(int32 InHeight) override;
	virtual void SetLineWidth(int32 InWidth) override;
	virtual void SetFillColor(const FLinearColor& InColor) override;
	virtual void LogInfo() const override;
	virtual void UpdateScale(UWorld* World) override;
	virtual void Clear() override;


private:
	FVector WorldPosition;
	FVector LatLongHeight;
	float Radius;
	FLinearColor LineColor;
	FLinearColor FillColor;
	int32 LineWidth;
	int32 LineHeight;
	bool isCleared = false;

	int32 NumSegments = 1200;

	TArray<FVector> WorldOuterPoints;
	TArray<FVector> WorldInnerPoints;

	TArray<FVector> WorldSampledPoints;
	TArray<FVector> WorldSampledProjectionPoints;

	const float TargetEdgeLength = 5000.0f;
	const float NM_TO_CM = 185200.0f;


  // void SampleHeightAboveTerrain(
  //const TArray<FVector>& LatLongPoints,
//TFunction<void(TArray<FVector>&, TArray<FVector>&)> OnComplete);



};
