#pragma once

#include "IShape.h"

class AFISEDRAWINGSLOADER_API FPolygon : public IShape
{
public:
    FPolygon(const TArray<FVector>& InLatLongHeight);

    virtual FString GetShapeType() const override;
    virtual FVector GetWorldPosition() const override;
    virtual FVector GetLatLongHeightPosition() const override;
    virtual void Draw(UWorld* World) override;
    TArray<FVector> GetLatLongHeightPositions();
    virtual void CreateMeshes(UWorld* World) override;
    virtual void SetLineColor(const FLinearColor& InColor) override;
    virtual void SetLineWidth(int32 InWidth) override;
    virtual void SetLineHeight(int32 InHeight) override;
    virtual void SetFillColor(const FLinearColor& InColor) override;
    virtual void LogInfo() const override;
    virtual void Clear() override;
    virtual void SetProjectionVisibility(bool bVisible) override;
    virtual void SetVisibility(bool bVisible) override;
    virtual void UpdateScale(UWorld* World) override;

private:
    TArray<FVector> LatLongHeightPoints;  
    TArray<FVector> WorldPoints;  
    FLinearColor LineColor;
    int32 LineWidth;
    int32 LineHeight;
    mutable FVector CenterAvgPoint = FVector::ZeroVector;
};




