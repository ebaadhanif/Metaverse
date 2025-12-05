
#include "IShape.h"
#include "Async/Async.h"                 // <-- required for AsyncTask(...)
#include "Async/TaskGraphInterfaces.h"   // <-- for ENamedThreads (sometimes pulled in transitively, add explicitly)

ACesiumGeoreference* IShape::Georeference = nullptr;
ACesium3DTileset* IShape::Tileset = nullptr;
UWorld* IShape::ParentWorld = nullptr;


void IShape::SetGeoreference(ACesiumGeoreference* InGeoref)
{
	IShape::Georeference = InGeoref;
}

void IShape::SampleHeightAboveTerrain(
	const TArray<FVector>& LatLongPoints,
	TFunction<void(TArray<FVector>&, TArray<FVector>&)> OnComplete)
{
	TWeakPtr<IShape> weakthis = AsShared();
	FCesiumSampleHeightMostDetailedCallback CesiumCallback;
	CesiumCallback.BindLambda([weakthis, LatLongPoints, OnComplete](ACesium3DTileset*, const TArray<FCesiumSampleHeightResult>& Results, const TArray<FString>& Warnings)
		{
			TArray<FVector> OutWorldPoints;
			TArray<FVector> OutWorldProjectionPoints;
			if (!weakthis.IsValid()) {
				OnComplete(OutWorldPoints, OutWorldProjectionPoints);
				return;
			}
			float MaxHeight = 0;
			for (const FString& warning : Warnings) {
				UE_LOG(LogTemp, Error, TEXT("Warning Came from Height Sampling:%s "), *warning);
			}
			for (const FCesiumSampleHeightResult& Result : Results)
			{
				if (Result.SampleSuccess)
				{
					FVector Point = Result.LongitudeLatitudeHeight;
					OutWorldProjectionPoints.Add(Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(FVector(Point.X, Point.Y, Point.Z)));

					MaxHeight = FMath::Max(MaxHeight, Result.LongitudeLatitudeHeight[2]);
				}
				else {
					FVector Point = Result.LongitudeLatitudeHeight;
					FVector PointXYZ = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(FVector(Point.X, Point.Y, Point.Z));
					UE_LOG(LogTemp, Error, TEXT("Failed Point:%s "), *PointXYZ.ToString());

				}
			}

			UE_LOG(LogTemp, Error, TEXT("MAX Height:%f "), MaxHeight);

	/*		if (MaxHeight > 450) {
				MaxHeight += (LatLongPoints[0].Z * 10);
			}
			else {
			}*/
			MaxHeight += LatLongPoints[0].Z;

			for (const FVector& LatLong : LatLongPoints)
			{
				OutWorldPoints.Add(Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(
					FVector(LatLong.X, LatLong.Y, MaxHeight)));
			}
			AsyncTask(ENamedThreads::GameThread, [weakthis, OnComplete, OutWorldPoints = MoveTemp(OutWorldPoints), OutWorldProjectionPoints= MoveTemp(OutWorldProjectionPoints)]() mutable {
				if (!weakthis.IsValid()) return;
				OnComplete(OutWorldPoints, OutWorldProjectionPoints);
				});
		});
	Tileset->SampleHeightMostDetailed(LatLongPoints, CesiumCallback);
}


ACesiumGeoreference* IShape::GetGeoreference()
{
	return IShape::Georeference;
}

void IShape::SetTileset(ACesium3DTileset* InTileset)
{
	IShape::Tileset = InTileset;
}
void IShape::SetWorld(UWorld* InWorld) {
	IShape::ParentWorld = InWorld;
}

UWorld* IShape::GetWorld() {
	return ParentWorld;
}

ACesium3DTileset* IShape::GetTileset()
{
	return Tileset;
}








