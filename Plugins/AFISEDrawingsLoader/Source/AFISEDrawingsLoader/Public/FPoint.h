#pragma once
#include "IShape.h"


//enum class PointType: uint8
//{
//	CAP = 1 UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	LANDMARK  UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	FILLED_CIRCLE UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	MOU UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	RADAR_SITE UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	VITAL_POINT UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	SAM UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	GUN UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	BASE UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	BRIDGE UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	SHIP UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	GROUND_FORCE UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	BALLOON UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	ADOC UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	SMCC UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	OCC UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	OCS UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	GMCC UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	FILLED_TRIANGLE UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	TWCC UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	FILLED_SQUARE UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	SQUARE UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	DIAMOND UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	FILLED_DIAMOND UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/CAP.CAP'"),
//	NONE UMETA(DisplayName = "StaticMesh'/Game/MyModels/PointType/NONEPOINT.NONEPOINT'")
//};

enum class PointType : uint8
{
	CAP = 1,
	LANDMARK,
	FILLED_CIRCLE,
	MOU,
	RADAR_SITE,
	VITAL_POINT,
	SAM,
	GUN,
	BASE,
	BRIDGE,
	SHIP,
	GROUND_FORCE,
	BALLOON,
	ADOC,
	SMCC,
	OCC,
	OCS,
	GMCC,
	FILLED_TRIANGLE,
	TWCC,
	FILLED_SQUARE,
	SQUARE,
	DIAMOND,
	FILLED_DIAMOND,
	NONE
};



class AFISEDRAWINGSLOADER_API FPoint : public IShape
{
public:
	FPoint(const FVector& InWorldPos, const FVector& InLatLong);

	virtual FString GetShapeType() const override;
	virtual FVector GetWorldPosition() const override;
	virtual FVector GetLatLongHeightPosition() const override;
	virtual void Draw(UWorld* World) override;
	virtual void SetProjectionVisibility(bool bVisible) override;
	virtual void SetVisibility(bool bVisible) override;

	virtual void SetLineColor(const FLinearColor&) override {}
	virtual void SetFillColor(const FLinearColor&) override {}
	virtual void UpdateScale(UWorld* World) override;
	void SetScale(int32 InScale);
	virtual void LogInfo() const override;
	virtual void Clear() override;
	virtual void CreateMeshes(UWorld* World) override;


	void SetPointType(PointType type);
	PointType GetPointType();


private:
	FVector WorldPosition;
	FVector LatLongHeight;
	int32 Scale;
	TWeakObjectPtr<AActor> SpawnedActor;
	TArray<FVector> WorldProjectionPoints;
	PointType pointType;



	static const FString PointToMeshType(PointType type) {
		switch (type) {
		case PointType::CAP:
			return TEXT("StaticMesh'/Game/MyModels/PointType/NONEPOINT.NONEPOINT'");
		case PointType::LANDMARK:
			return TEXT("StaticMesh'/Game/MyModels/PointType/CAP.CAP'");
		case PointType::FILLED_CIRCLE:
			return TEXT("StaticMesh'/Game/MyModels/PointType/CAP.CAP'");
		case PointType::MOU:
			return TEXT("StaticMesh'/Game/MyModels/PointType/CAP.CAP'");
		case PointType::RADAR_SITE:
			return TEXT("StaticMesh'/Game/MyModels/PointType/CAP.CAP'");
		case PointType::VITAL_POINT:
			return TEXT("StaticMesh'/Game/MyModels/PointType/CAP.CAP'");
		case PointType::SAM:
			return TEXT("StaticMesh'/Game/MyModels/PointType/CAP.CAP'");
		case PointType::GUN:
			return TEXT("StaticMesh'/Game/MyModels/PointType/CAP.CAP'");
		case  PointType::BASE:
			return TEXT("StaticMesh'/Game/MyModels/PointType/CAP.CAP'");
		case  PointType::BRIDGE:
			return TEXT("StaticMesh'/Game/MyModels/PointType/CAP.CAP'");
		case PointType::SHIP:
			return TEXT("StaticMesh'/Game/MyModels/PointType/CAP.CAP'");
		case  PointType::GROUND_FORCE:
			return TEXT("StaticMesh'/Game/MyModels/PointType/CAP.CAP'");
		case  PointType::BALLOON:
			return TEXT("StaticMesh'/Game/MyModels/PointType/CAP.CAP'");
		case  PointType::ADOC:
			return TEXT("StaticMesh'/Game/MyModels/PointType/CAP.CAP'");
		case  PointType::SMCC:
			return TEXT("StaticMesh'/Game/MyModels/PointType/CAP.CAP'");
		case  PointType::OCC:
			return TEXT("StaticMesh'/Game/MyModels/PointType/CAP.CAP'");
		case  PointType::OCS:
			return TEXT("StaticMesh'/Game/MyModels/PointType/CAP.CAP'");
		case  PointType::GMCC:
			return TEXT("StaticMesh'/Game/MyModels/PointType/CAP.CAP'");
		case PointType::FILLED_TRIANGLE:
			return TEXT("StaticMesh'/Game/MyModels/PointType/CAP.CAP'");
		case  PointType::TWCC:
			return TEXT("StaticMesh'/Game/MyModels/PointType/CAP.CAP'");
		case  PointType::FILLED_SQUARE:
			return TEXT("StaticMesh'/Game/MyModels/PointType/CAP.CAP'");
		case  PointType::SQUARE:
			return TEXT("StaticMesh'/Game/MyModels/PointType/CAP.CAP'");
		case PointType::DIAMOND:
			return TEXT("StaticMesh'/Game/MyModels/PointType/CAP.CAP'");
		case  PointType::FILLED_DIAMOND:
			return TEXT("StaticMesh'/Game/MyModels/PointType/CAP.CAP'");
		case  PointType::NONE:
			return TEXT("StaticMesh'/Game/MyModels/PointType/NONEPOINT.NONEPOINT'");
		default:
			return TEXT("StaticMesh'/Game/MyModels/PointType/NONEPOINT.NONEPOINT'");
		}

	}

};
