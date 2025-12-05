#pragma once

#include "IShape.h"


class AFISEDRAWINGSLOADER_API FLine : public IShape
{

public:

	FLine(const TArray<FVector>& InLatLongHeight);
	virtual FString GetShapeType() const override;
	virtual FVector GetWorldPosition() const override;
	virtual FVector GetLatLongHeightPosition() const override;
	TArray<FVector> GetLatLongHeightPositions();
	void CreateMeshes(UWorld* World);
	virtual void Draw(UWorld* World) override;
	virtual void SetLineColor(const FLinearColor& InColor) override;
	virtual void SetLineWidth(int32 InWidth) override;
	virtual void SetLineHeight(int32 InHeight) override;
	virtual void SetFillColor(const FLinearColor&) override {}
	virtual void LogInfo() const override;
	virtual void Clear() override;
	virtual void SetProjectionVisibility(bool bVisible) override;
	virtual void SetVisibility(bool bVisible) override;
	virtual void UpdateScale(UWorld* World) override;
	void DrawInternationalBorder(UWorld* World);


private:
	TArray<FVector> LatLongHeightPoints;
	TArray<FVector> WorldPoints;
	FLinearColor LineColor;
	int32 LineWidth = 1.0f;
	int32 LineHeight = 1.0f;
	TArray<FVector> WallVertices;
	TArray<int32> WallTriangles;
	TArray<FVector> WallNormals;
	TArray<FVector2D> WallUVs;
	TArray<FLinearColor> WallColors;
	TArray<FProcMeshTangent> WallTangents;
	mutable FVector CenterAvgPoint = FVector::ZeroVector;

};
