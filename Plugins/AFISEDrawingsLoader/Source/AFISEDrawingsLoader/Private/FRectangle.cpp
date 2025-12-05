#include "FRectangle.h"
#include "CesiumGeoreference.h"

static float ComputeSignedAreaXY(const TArray<FVector>& P)
{
	// Standard 2D polygon area on X,Y plane, assumes last!=first
	double A = 0.0;
	const int32 N = P.Num();
	for (int32 i = 0; i < N; ++i)
	{
		const FVector& a = P[i];
		const FVector& b = P[(i + 1) % N];
		A += (double)a.X * (double)b.Y - (double)b.X * (double)a.Y;
	}
	return 0.5f * (float)A; // >0 => CCW, <0 => CW
}

FRectangle::FRectangle(const FVector& InWorldPos, const FVector& InLatLongHeight, float InWidth, float InHeight)
	: WorldPosition(InWorldPos), LatLongHeight(InLatLongHeight), Width(InWidth), Height(InHeight), LineWidth(1)
{
	//WorldPosition = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(FVector(LatLongHeight.X, LatLongHeight.Y, MaxHeight));

	MaterialPath = "/Game/Materials/Drawings/M_Rectangle";
	Material = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, *MaterialPath));
	if (Material)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(Material, nullptr);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load Material at path: %s"), *MaterialPath);
	}

	ProjectionMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, *ProjectionMaterialPath));
	if (ProjectionMaterial)
	{
		DynamicProjectionMaterial = UMaterialInstanceDynamic::Create(ProjectionMaterial, nullptr);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load Projection Material at path: %s"), *ProjectionMaterialPath);
	}

}


FString FRectangle::GetShapeType() const { return TEXT("Rectangle"); }

FVector FRectangle::GetLatLongHeightPosition() const { return LatLongHeight; }

void FRectangle::SetLineColor(const FLinearColor& InColor) { LineColor = InColor; }
void FRectangle::SetLineWidth(int32 InWidth) { LineWidth = InWidth * BaseLineWidth; }



void FRectangle::SetLineHeight(int32 InHeight)
{
	LineHeight = InHeight * BaseLineHeight;
}

void FRectangle::SetFillColor(const FLinearColor& InColor) { FillColor = InColor; }

FVector FRectangle::GetWorldPosition() const
{
	return WorldPosition;
}

TArray<FVector> FRectangle::GetWorldCornerPoints() {
	return WorldCornerPoints;
}

void FRectangle::Clear()
{
	if (LineMeshComponent && WallMeshComponent)
	{
		LineMeshComponent->DestroyComponent();
		WallMeshComponent->DestroyComponent();
		LineMeshComponent = nullptr;
		WallMeshComponent = nullptr;
	}
}
void FRectangle::CreateMeshes(UWorld* World) {

	if (LineMeshComponent && WallMeshComponent)
	{
		LineMeshComponent->DestroyComponent();
		WallMeshComponent->DestroyComponent();
		LineMeshComponent = nullptr;
		WallMeshComponent = nullptr;
	}

	const float NM_TO_CM = 185200.0f;

	float HeightInCM = Height * NM_TO_CM;
	float WidthInCM = Width * NM_TO_CM;

	FVector TopLeft = WorldPosition + FVector(-HeightInCM / 2.0f, -WidthInCM / 2.0f, 0);
	FVector TopRight = WorldPosition + FVector(HeightInCM / 2.0f, -WidthInCM / 2.0f, 0);
	FVector BottomLeft = WorldPosition + FVector(-HeightInCM / 2.0f, WidthInCM / 2.0f, 0);
	FVector BottomRight = WorldPosition + FVector(HeightInCM / 2.0f, WidthInCM / 2.0f, 0);


	TArray<FVector2D>  LatLongPoints;

	WorldCornerPoints.Add(TopLeft);
	WorldCornerPoints.Add(TopRight);
	WorldCornerPoints.Add(BottomRight);
	WorldCornerPoints.Add(BottomLeft);
	WorldCornerPoints.Add(TopLeft);
	WorldCornerPoints.Add(TopRight);



	for (int32 i = 0; i < WorldCornerPoints.Num(); i++) {
		FVector LatLongPosition = Georeference->TransformUnrealPositionToLongitudeLatitudeHeight(WorldCornerPoints[i]);
		LatLongPoints.Add(FVector2d(LatLongPosition.X, LatLongPosition.Y));
	}

	if (!World || !Material || WorldCornerPoints.Num() < 2) return;

	const float HalfWidth = LineWidth;
	const float HalfHeight = LineHeight;

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FLinearColor> Colors;
	TArray<FProcMeshTangent> Tangents;
	int32 VertexIndex = 0;

	if (DynamicMaterial) {
		DynamicMaterial->SetVectorParameterValue(FName("BaseColor"), LineColor);
	}
	DynamicProjectionMaterial = UMaterialInstanceDynamic::Create(ProjectionMaterial, WallMeshComponent);
	if (DynamicProjectionMaterial) {
		DynamicProjectionMaterial->SetVectorParameterValue(FName("ProjectionColor"), LineColor);
	}


	// --- Compute Corner Offsets ---
	struct FLineCorner { FVector Left; FVector Right; };
	TArray<FLineCorner> Corners;
	Corners.SetNum(WorldCornerPoints.Num());

	for (int32 i = 0; i < WorldCornerPoints.Num(); ++i)
	{
		FVector PrevDir, NextDir;

		if (i == 0)
		{
			NextDir = (WorldCornerPoints[i + 1] - WorldCornerPoints[i]).GetSafeNormal();
			FVector Right = FVector::CrossProduct(NextDir, FVector::UpVector).GetSafeNormal();
			Corners[i].Right = Right * HalfWidth;
			Corners[i].Left = -Right * HalfWidth;
		}
		else if (i == WorldCornerPoints.Num() - 1)
		{
			PrevDir = (WorldCornerPoints[i] - WorldCornerPoints[i - 1]).GetSafeNormal();
			FVector Right = FVector::CrossProduct(PrevDir, FVector::UpVector).GetSafeNormal();
			Corners[i].Right = Right * HalfWidth;
			Corners[i].Left = -Right * HalfWidth;
		}
		else
		{
			PrevDir = (WorldCornerPoints[i] - WorldCornerPoints[i - 1]).GetSafeNormal();
			NextDir = (WorldCornerPoints[i + 1] - WorldCornerPoints[i]).GetSafeNormal();

			FVector PrevRight = FVector::CrossProduct(PrevDir, FVector::UpVector).GetSafeNormal();
			FVector NextRight = FVector::CrossProduct(NextDir, FVector::UpVector).GetSafeNormal();

			FVector AvgRight = (PrevRight + NextRight).GetSafeNormal();
			float Dot = FVector::DotProduct(AvgRight, FVector::CrossProduct(NextDir, FVector::UpVector));
			float MiterLength = FMath::Abs(Dot) > KINDA_SMALL_NUMBER ? HalfWidth / Dot : HalfWidth;

			// Clamp miter to avoid spikes
			const float MaxMiter = HalfWidth * 2.0f;
			MiterLength = FMath::Clamp(MiterLength, 0.0f, MaxMiter);

			Corners[i].Right = AvgRight * MiterLength;
			Corners[i].Left = -AvgRight * MiterLength;
		}
	}

	// --- Build Mesh Between Segments ---
	for (int32 i = 0; i < WorldCornerPoints.Num() - 1; ++i)
	{
		FVector A = WorldCornerPoints[i];
		FVector B = WorldCornerPoints[i + 1];

		FVector RT0 = A + Corners[i].Right;
		FVector LT0 = A + Corners[i].Left;
		FVector RT1 = B + Corners[i + 1].Right;
		FVector LT1 = B + Corners[i + 1].Left;

		FVector RB0 = RT0 - FVector(0, 0, HalfHeight);
		FVector LB0 = LT0 - FVector(0, 0, HalfHeight);
		FVector RB1 = RT1 - FVector(0, 0, HalfHeight);
		FVector LB1 = LT1 - FVector(0, 0, HalfHeight);

		// Top face
		Vertices.Append({ RT0, LT0, RT1, LT1 });
		Triangles.Append({
			VertexIndex, VertexIndex + 2, VertexIndex + 1,
			VertexIndex + 2, VertexIndex + 3, VertexIndex + 1
			});
		VertexIndex += 4;

		// Bottom face
		Vertices.Append({ RB0, RB1, LB0, LB1 });
		Triangles.Append({
			VertexIndex, VertexIndex + 2, VertexIndex + 1,
			VertexIndex + 2, VertexIndex + 3, VertexIndex + 1
			});
		VertexIndex += 4;

		// Side 1 (outer)
		Vertices.Append({ RT0, RB0, RB1, RT1 });
		Triangles.Append({
			VertexIndex, VertexIndex + 2, VertexIndex + 1,
			VertexIndex, VertexIndex + 3, VertexIndex + 2
			});
		VertexIndex += 4;

		// Side 2 (inner)
		Vertices.Append({ LT1, LB1, LB0, LT0 });
		Triangles.Append({
			VertexIndex, VertexIndex + 2, VertexIndex + 1,
			VertexIndex, VertexIndex + 3, VertexIndex + 2
			});
		VertexIndex += 4;

		// Forward face
		Vertices.Append({ RT1, RB1, LB1, LT1 });
		Triangles.Append({
			VertexIndex, VertexIndex + 2, VertexIndex + 1,
			VertexIndex, VertexIndex + 3, VertexIndex + 2
			});
		VertexIndex += 4;

		// Back face
		Vertices.Append({ LT0, LB0, RB0, RT0 });
		Triangles.Append({
			VertexIndex, VertexIndex + 2, VertexIndex + 1,
			VertexIndex, VertexIndex + 3, VertexIndex + 2
			});
		VertexIndex += 4;
	}

	// --- Apply Vertex Attributes ---
	for (int32 i = 0; i < Vertices.Num(); ++i)
	{
		Normals.Add(FVector::UpVector);
		UVs.Add(FVector2D(0, 0));
		Colors.Add(LineColor);
		Tangents.Add(FProcMeshTangent(1, 0, 0));
	}

	// --- Mesh Component ---
	if (!LineMeshComponent)
	{
		LineMeshComponent = NewObject<UProceduralMeshComponent>(World->GetWorldSettings());
		if (!LineMeshComponent) return;

		LineMeshComponent->RegisterComponent();
		LineMeshComponent->AttachToComponent(World->GetWorldSettings()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}
	else
	{
		LineMeshComponent->ClearAllMeshSections();
	}

	LineMeshComponent->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);
	LineMeshComponent->SetMaterial(0, DynamicMaterial);
	LineMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LineMeshComponent->SetCastShadow(false);
	LineMeshComponent->SetCastInsetShadow(false);
	LineMeshComponent->SetCastHiddenShadow(false);


	// --- Wall Projection ---
	TArray<FVector> LatLongPoints3d;
	for (const FVector2D& InLatLong : LatLongPoints)
	{
		LatLongPoints3d.Add(FVector(InLatLong.X, InLatLong.Y, 0));
	}

	if (!WallMeshComponent)
	{
		WallMeshComponent = NewObject<UProceduralMeshComponent>(World->GetWorldSettings());
		if (!WallMeshComponent) return;

		WallMeshComponent->RegisterComponent();
		WallMeshComponent->AttachToComponent(World->GetWorldSettings()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}
	else
	{
		WallMeshComponent->ClearAllMeshSections();
	}

	WallMeshComponent->SetMaterial(0, DynamicProjectionMaterial);
	WallMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	FCesiumSampleHeightMostDetailedCallback CesiumCallback;
	CesiumCallback.BindLambda(
		[this, World](ACesium3DTileset*, const TArray<FCesiumSampleHeightResult>& Results, const TArray<FString>&)
		{
			if (Results.Num() != WorldCornerPoints.Num()) return;

			TArray<FVector> Vertices;
			TArray<int32> Triangles;
			TArray<FVector> Normals;
			TArray<FVector2D> UVs;
			TArray<FLinearColor> Colors;
			TArray<FProcMeshTangent> Tangents;
			int32 VertexIndex = 0;

			for (int32 i = 0; i < Results.Num() - 1; ++i)
			{
				if (!Results[i].SampleSuccess || !Results[i + 1].SampleSuccess) continue;

				FVector TopA = WorldCornerPoints[i];
				FVector TopB = WorldCornerPoints[i + 1];
				FVector BottomA = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(Results[i].LongitudeLatitudeHeight);
				FVector BottomB = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(Results[i + 1].LongitudeLatitudeHeight);

				Vertices.Append({ TopA, BottomA, BottomB, TopB });
				Triangles.Append({
					VertexIndex, VertexIndex + 2, VertexIndex + 1,
					VertexIndex, VertexIndex + 3, VertexIndex + 2
					});

				for (int j = 0; j < 4; ++j)
				{
					Normals.Add(FVector::UpVector);
					UVs.Add(FVector2D(0, 0));
					Colors.Add(LineColor);
					Tangents.Add(FProcMeshTangent(1, 0, 0));
				}

				VertexIndex += 4;
			}

			WallMeshComponent->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);

		});

	Tileset->SampleHeightMostDetailed(LatLongPoints3d, CesiumCallback);


}

void FRectangle::UpdateScale(UWorld* World)
{
	const bool bHasSection = (LineMeshComponent && LineMeshComponent->GetNumSections() > 0);
	if (!bHasSection) return;

	// Recompute the rectangle path (the OUTER boundary stays fixed to these points)
	const float NM_TO_CM = 185200.0f;
	const float HeightInCM = Height * NM_TO_CM;
	const float WidthInCM = Width * NM_TO_CM;

	const FVector TopLeft = WorldPosition + FVector(-HeightInCM / 2.0f, -WidthInCM / 2.0f, 0);
	const FVector TopRight = WorldPosition + FVector(HeightInCM / 2.0f, -WidthInCM / 2.0f, 0);
	const FVector BottomLeft = WorldPosition + FVector(-HeightInCM / 2.0f, WidthInCM / 2.0f, 0);
	const FVector BottomRight = WorldPosition + FVector(HeightInCM / 2.0f, WidthInCM / 2.0f, 0);

	WorldCornerPoints.Empty();
	WorldCornerPoints.Add(TopLeft);
	WorldCornerPoints.Add(TopRight);
	WorldCornerPoints.Add(BottomRight);
	WorldCornerPoints.Add(BottomLeft);
	WorldCornerPoints.Add(TopLeft);
	WorldCornerPoints.Add(TopRight); // path layout maintained to match CreateMeshes()

	if (!World || !Material || WorldCornerPoints.Num() < 2) return;

	// IMPORTANT: In CreateMeshes(), HalfWidth == LineWidth and total thickness ~= 2*HalfWidth.
	// To keep that visual thickness while fixing the outer edge, we offset the INNER edge by 2*HalfWidth.
	const float HalfWidth = LineWidth;
	const float InnerWidth = HalfWidth * 2.0f;     // move inward only by full thickness
	const float HalfHeight = LineHeight;

	// Determine polygon orientation to know which side is "inside".
	const float SignedArea = ComputeSignedAreaXY(WorldCornerPoints);
	const bool  bCCW = (SignedArea > 0.0f);  // CCW => interior on LEFT of edges

	auto InsideNormalForDir = [bCCW](const FVector& Dir) -> FVector
		{
			const FVector Right = FVector::CrossProduct(Dir, FVector::UpVector).GetSafeNormal();
			return bCCW ? (-Right) : Right; // CCW interior is Left (-Right), CW interior is Right
		};

	struct FStrokeCorner { FVector Out; FVector In; };
	TArray<FStrokeCorner> Corners;
	Corners.SetNum(WorldCornerPoints.Num());

	// Compute per-vertex offsets: OUT = 0 (fixed), IN = inward miter
	for (int32 i = 0; i < WorldCornerPoints.Num(); ++i)
	{
		Corners[i].Out = FVector::ZeroVector;

		FVector PrevDir, NextDir;

		const bool bFirst = (i == 0);
		const bool bLast = (i == WorldCornerPoints.Num() - 1);

		if (bFirst)
		{
			NextDir = (WorldCornerPoints[i + 1] - WorldCornerPoints[i]).GetSafeNormal();
			Corners[i].In = InsideNormalForDir(NextDir) * InnerWidth;
		}
		else if (bLast)
		{
			PrevDir = (WorldCornerPoints[i] - WorldCornerPoints[i - 1]).GetSafeNormal();
			Corners[i].In = InsideNormalForDir(PrevDir) * InnerWidth;
		}
		else
		{
			PrevDir = (WorldCornerPoints[i] - WorldCornerPoints[i - 1]).GetSafeNormal();
			NextDir = (WorldCornerPoints[i + 1] - WorldCornerPoints[i]).GetSafeNormal();

			const FVector PrevIn = InsideNormalForDir(PrevDir);
			const FVector NextIn = InsideNormalForDir(NextDir);
			const FVector AvgIn = (PrevIn + NextIn).GetSafeNormal();

			// Project against the "inside" normal of the next segment to get miter length
			const FVector NextInRef = InsideNormalForDir(NextDir);
			float Dot = FVector::DotProduct(AvgIn, NextInRef);
			float MiterLen = (FMath::Abs(Dot) > KINDA_SMALL_NUMBER) ? (InnerWidth / Dot) : InnerWidth;

			// Clamp miter to avoid spikes on sharp angles
			const float MaxMiter = InnerWidth * 2.0f;
			MiterLen = FMath::Clamp(MiterLen, 0.0f, MaxMiter);

			Corners[i].In = AvgIn * MiterLen;
		}
	}

	// Build updated vertices (same topology/count as CreateMeshes)
	TArray<FVector> Vertices;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FLinearColor> Colors;
	TArray<FProcMeshTangent> Tangents;
	Vertices.Reserve(WorldCornerPoints.Num() * 6 * 4); // rough reservation

	int32 VertexIndex = 0;

	for (int32 i = 0; i < WorldCornerPoints.Num() - 1; ++i)
	{
		const FVector A = WorldCornerPoints[i];
		const FVector B = WorldCornerPoints[i + 1];

		// Outer stays on the path, Inner is offset inward
		const FVector Out0 = A + Corners[i].Out;
		const FVector In0 = A + Corners[i].In;
		const FVector Out1 = B + Corners[i + 1].Out;
		const FVector In1 = B + Corners[i + 1].In;

		// Map to RT/LT consistently with CreateMeshes() expectations:
		// For CCW: OUT is to the "Right" of the edge; for CW it's to the "Left".
		FVector RT0, LT0, RT1, LT1;
		if (bCCW)
		{
			RT0 = Out0; LT0 = In0; RT1 = Out1; LT1 = In1;
		}
		else
		{
			RT0 = In0;  LT0 = Out0; RT1 = In1;  LT1 = Out1;
		}

		// Vertical duplicates for bottom and sides
		const FVector RB0 = RT0 - FVector(0, 0, HalfHeight);
		const FVector LB0 = LT0 - FVector(0, 0, HalfHeight);
		const FVector RB1 = RT1 - FVector(0, 0, HalfHeight);
		const FVector LB1 = LT1 - FVector(0, 0, HalfHeight);

		// --- Top face (outer/inner strip) ---
		Vertices.Append({ RT0, LT0, RT1, LT1 });
		VertexIndex += 4;

		// --- Bottom face ---
		Vertices.Append({ RB0, RB1, LB0, LB1 });
		VertexIndex += 4;

		// --- Side 1 (outer wall) ---
		Vertices.Append({ RT0, RB0, RB1, RT1 });
		VertexIndex += 4;

		// --- Side 2 (inner wall) ---
		Vertices.Append({ LT1, LB1, LB0, LT0 });
		VertexIndex += 4;

		// --- Forward face (cap) ---
		Vertices.Append({ RT1, RB1, LB1, LT1 });
		VertexIndex += 4;

		// --- Back face (cap) ---
		Vertices.Append({ LT0, LB0, RB0, RT0 });
		VertexIndex += 4;
	}

	// Attributes (match counts from CreateMeshes)
	Normals.SetNum(Vertices.Num());
	UVs.SetNum(Vertices.Num());
	Colors.SetNum(Vertices.Num());
	Tangents.SetNum(Vertices.Num());

	for (int32 i = 0; i < Vertices.Num(); ++i)
	{
		Normals[i] = FVector::UpVector;
		UVs[i] = FVector2D(0, 0);
		Colors[i] = LineColor;
		Tangents[i] = FProcMeshTangent(1, 0, 0);
	}

	// Update (triangles unchanged)
	LineMeshComponent->UpdateMeshSection_LinearColor(0, Vertices, Normals, UVs, Colors, Tangents, true);
}

void FRectangle::Draw(UWorld* World)
{
	if (WorldPosition.IsZero()) {
		TArray<FVector> LatLongPoints = { FVector(LatLongHeight.X, LatLongHeight.Y, LatLongHeight.Z) };

		SampleHeightAboveTerrain(LatLongPoints,
			[this, World]( TArray<FVector>& SampledWorldPoints,  TArray<FVector> SampleWorldProjectionPoints)
			{
				WorldPosition = SampledWorldPoints[0];
				CreateMeshes(World);  
			});
	}
	else {
		CreateMeshes(World);
	}

}

void FRectangle::SetProjectionVisibility(bool bVisible)
{
	if (WallMeshComponent)
	{
		WallMeshComponent->SetVisibility(bVisible, true); 
		WallMeshComponent->SetHiddenInGame(!bVisible);
	}
}

void FRectangle::SetVisibility(bool bVisible)
{
	if (WallMeshComponent && LineMeshComponent)
	{
		WallMeshComponent->SetVisibility(bVisible, true);
		WallMeshComponent->SetHiddenInGame(!bVisible);
		LineMeshComponent->SetVisibility(bVisible, true);
		LineMeshComponent->SetHiddenInGame(!bVisible);
	}
}

DEFINE_LOG_CATEGORY_STATIC(LogShape, Log, All);
void FRectangle::LogInfo() const
{
	UE_LOG(LogShape, Log, TEXT("Rectangle Info:"));
	UE_LOG(LogShape, Log, TEXT(" - World Position: %s"), *WorldPosition.ToString());
	UE_LOG(LogShape, Log, TEXT(" - LatLong Position: X=%f, Y=%f"), LatLongHeight.X, LatLongHeight.Y);
	UE_LOG(LogShape, Log, TEXT(" - Width: %f"), Width);
	UE_LOG(LogShape, Log, TEXT(" - Height: %f"), Height);
	UE_LOG(LogShape, Log, TEXT(" - Fill Color: %s"), *FillColor.ToString());
	UE_LOG(LogShape, Log, TEXT(" - Line Color: %s"), *LineColor.ToString());
	UE_LOG(LogShape, Log, TEXT(" - Line Width: %d"), LineWidth);
}