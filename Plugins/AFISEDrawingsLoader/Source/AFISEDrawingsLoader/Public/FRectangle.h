#pragma once

#include "IShape.h"



class AFISEDRAWINGSLOADER_API FRectangle : public IShape
{
public:
	FRectangle(const FVector& InWorldPos, const FVector& InLatLong, float InWidth, float InHeight);

	virtual FString GetShapeType() const override;
	virtual FVector GetWorldPosition() const override;
	TArray<FVector> GetWorldCornerPoints();
	virtual void Draw(UWorld* World) override;
	virtual void LogInfo() const override;
	virtual FVector GetLatLongHeightPosition() const override;
	virtual void SetLineColor(const FLinearColor& InColor) override;
	virtual void SetLineWidth(int32 InWidth) override;
	virtual void SetLineHeight(int32 InHeight) override;
	virtual void SetFillColor(const FLinearColor& InColor) override;
	virtual void Clear() override;
	virtual void CreateMeshes(UWorld* World) override;
	virtual void SetProjectionVisibility(bool bVisible) override;
	virtual void SetVisibility(bool bVisible) override;
	virtual void UpdateScale(UWorld* World) override;


private:
	FVector WorldPosition;
	FVector LatLongHeight;
	float Width;
	float Height;
	FLinearColor LineColor;
	FLinearColor FillColor;
	int32 LineWidth;
	int32 LineHeight;

	TArray<FVector> WorldCornerPoints;
 
};
