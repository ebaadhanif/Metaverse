#include "FLine.h"
#include "Engine/World.h"
#include "Engine/StaticMeshActor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "LineDrawerActor.h"

FLine::FLine(const TArray<FVector>& InLatLongHeight)
	: LatLongHeightPoints(InLatLongHeight)
{

	//for (const FVector& LatLong : LatLongHeightPoints)
	//{
	//	WorldPoints.Add(Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(FVector(LatLong.X, LatLong.Y, 10000)));
	//}

    MaterialPath = "/Game/Materials/Drawings/M_Line";
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


void FLine::SetLineColor(const FLinearColor& InColor)
{
	LineColor = InColor;
}

void FLine::SetLineWidth(int32 InWidth)
{
	LineWidth = InWidth * BaseLineWidth;
}

void FLine::SetLineHeight(int32 InHeight)
{
	LineHeight = InHeight * BaseLineHeight;
}

FString FLine::GetShapeType() const
{
	return TEXT("Line");
}

FVector FLine::GetWorldPosition() const
{
    if (!CenterAvgPoint.IsZero()) return CenterAvgPoint;
    const int32 N = WorldPoints.Num();
    if (N == 0) return FVector::ZeroVector;
    const bool bClosed = (N > 1 && WorldPoints[0].Equals(WorldPoints[N - 1], KINDA_SMALL_NUMBER));
    const int32 Count = bClosed ? (N - 1) : N;

    FVector Sum = FVector::ZeroVector;
    for (int32 i = 0; i < Count; ++i)
    {
        Sum += WorldPoints[i];
    }
    CenterAvgPoint = Sum / Count;
    return CenterAvgPoint;

    //if(LineMeshComponent)       UE_LOG(LogTemp, Error, TEXT("World Location: %s"), *LineMeshComponent->GetComponentLocation().ToString())
    //return LineMeshComponent ? LineMeshComponent->GetComponentLocation() : FVector::ZeroVector;


}

FVector FLine::GetLatLongHeightPosition() const
{
	return LatLongHeightPoints.Num() > 0 ? LatLongHeightPoints[0] : FVector::ZeroVector;
}

TArray<FVector> FLine::GetLatLongHeightPositions() {
    return LatLongHeightPoints;
}

void FLine::Clear()
{

    if (LineMeshComponent && WallMeshComponent)
    {
        LineMeshComponent->DestroyComponent();
        WallMeshComponent->DestroyComponent();
        LineMeshComponent = nullptr;
        WallMeshComponent = nullptr;
    }
}

void FLine::LogInfo() const
{


}

void FLine::CreateMeshes(UWorld* World) {

    const float HalfWidth = LineWidth;
    const float HalfHeight = LineHeight;

    TArray<FVector> Vertices;
    TArray<int32> Triangles;
    TArray<FVector> Normals;
    TArray<FVector2D> UVs;
    TArray<FLinearColor> Colors;
    TArray<FProcMeshTangent> Tangents;
    int32 VertexIndex = 0;

    //if (DynamicMaterial) {
    //    DynamicMaterial->SetVectorParameterValue(FName("BaseColor"), LineColor);
    //}
    //if (DynamicProjectionMaterial) {
    //    DynamicProjectionMaterial->SetVectorParameterValue(FName("ProjectionColor"), LineColor);
    //}
    // --- Compute Corner Offsets ---
    struct FLineCorner { FVector Left; FVector Right; };
    TArray<FLineCorner> Corners;
    Corners.SetNum(WorldPoints.Num());

    // Computing corner offsets for the line width and height
    for (int32 i = 0; i < WorldPoints.Num(); ++i)
    {
        FVector PrevDir, NextDir;

        if (i == 0)
        {
            NextDir = (WorldPoints[i + 1] - WorldPoints[i]).GetSafeNormal();
            FVector Right = FVector::CrossProduct(NextDir, FVector::UpVector).GetSafeNormal();
            Corners[i].Right = Right * HalfWidth;
            Corners[i].Left = -Right * HalfWidth;
        }
        else if (i == WorldPoints.Num() - 1)
        {
            PrevDir = (WorldPoints[i] - WorldPoints[i - 1]).GetSafeNormal();
            FVector Right = FVector::CrossProduct(PrevDir, FVector::UpVector).GetSafeNormal();
            Corners[i].Right = Right * HalfWidth;
            Corners[i].Left = -Right * HalfWidth;
        }
        else
        {
            PrevDir = (WorldPoints[i] - WorldPoints[i - 1]).GetSafeNormal();
            NextDir = (WorldPoints[i + 1] - WorldPoints[i]).GetSafeNormal();

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
    for (int32 i = 0; i < WorldPoints.Num() - 1; ++i)
    {
        FVector A = WorldPoints[i];
        FVector B = WorldPoints[i + 1];

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

        // Side faces
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
        Normals.Add(FVector::UpVector);  // Use UpVector for top/bottom
        UVs.Add(FVector2D(0, 0));        // Optional: Customize for UV mapping
        Colors.Add(LineColor);           // Line color
        Tangents.Add(FProcMeshTangent(1, 0, 0));  // Tangent direction
    }

    // --- Mesh Component ---
    if (!LineMeshComponent)
    {
        LineMeshComponent = NewObject<UProceduralMeshComponent>(World->GetWorldSettings());
        if (!LineMeshComponent) return;

        LineMeshComponent->RegisterComponent();
        LineMeshComponent->AttachToComponent(World->GetWorldSettings()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
        if (Material) {
            DynamicMaterial = LineMeshComponent->CreateDynamicMaterialInstance(0, Material);
            DynamicMaterial->SetVectorParameterValue(FName("BaseColor"), LineColor);
        }
    }
    else
    {
        LineMeshComponent->ClearAllMeshSections();
    }

    // Set Mesh Section and Dynamic Material
    LineMeshComponent->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);
  //  LineMeshComponent->SetMaterial(0, DynamicMaterial);  // Apply dynamic material to line
    LineMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    LineMeshComponent->SetCastShadow(false);
    LineMeshComponent->SetCastInsetShadow(false);
    LineMeshComponent->SetCastHiddenShadow(false);




    // --- Wall Projection (height adjustment based on Cesium data) ---
    TArray<FVector> LatLongPoints3d;
    for (const FVector& LatLong : LatLongHeightPoints)
    {
        LatLongPoints3d.Add(FVector(LatLong.X, LatLong.Y, LatLong.Z));
    }


    // Creating and attaching procedural mesh for walls
    if (!WallMeshComponent)
    {
        WallMeshComponent = NewObject<UProceduralMeshComponent>(World->GetWorldSettings());
        if (!WallMeshComponent) return;
        WallMeshComponent->RegisterComponent();
        WallMeshComponent->AttachToComponent(World->GetWorldSettings()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
        if (ProjectionMaterial) {
            DynamicProjectionMaterial = WallMeshComponent->CreateDynamicMaterialInstance(0, ProjectionMaterial);
            DynamicProjectionMaterial->SetVectorParameterValue(FName("ProjectionColor"), LineColor);
        }
    }
    else
    {
        WallMeshComponent->ClearAllMeshSections();
    }

   // WallMeshComponent->SetMaterial(0, DynamicProjectionMaterial);
    WallMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    FCesiumSampleHeightMostDetailedCallback CesiumCallback;
    CesiumCallback.BindLambda([this, World](ACesium3DTileset*, const TArray<FCesiumSampleHeightResult>& Results, const TArray<FString>&)
        {
            if (Results.Num() != WorldPoints.Num()) return;

            TArray<FVector> Vertices;
            TArray<int32> Triangles;
            TArray<FVector> Normals;
            TArray<FVector2D> UVs;
            TArray<FLinearColor> Colors;
            TArray<FProcMeshTangent> Tangents;
            int32 VertexIndex = 0;

            // Projecting walls using sampled height data
            for (int32 i = 0; i < Results.Num() - 1; ++i)
            {
                if (!Results[i].SampleSuccess || !Results[i + 1].SampleSuccess) continue;

                FVector TopA = WorldPoints[i];
                FVector TopB = WorldPoints[i + 1];
                FVector BottomA = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(Results[i].LongitudeLatitudeHeight);
                FVector BottomB = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(Results[i + 1].LongitudeLatitudeHeight);

                Vertices.Append({ TopA, BottomA, BottomB, TopB });
                Triangles.Append({
                    VertexIndex, VertexIndex + 2, VertexIndex + 1,
                    VertexIndex, VertexIndex + 3, VertexIndex + 2
                    });

                for (int j = 0; j < 4; ++j)
                {
                    Normals.Add(FVector::UpVector);  // Normal pointing upward
                    UVs.Add(FVector2D(0, 0));        // UV Coordinates
                    Colors.Add(LineColor);           // Line color
                    Tangents.Add(FProcMeshTangent(1, 0, 0));  // Tangents
                }

                VertexIndex += 4;
            }

            WallMeshComponent->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);

        });


    Tileset->SampleHeightMostDetailed(LatLongPoints3d, CesiumCallback);

}

void FLine::Draw(UWorld* World)
{
    if (WorldPoints.Num() > 0)
    {
        CreateMeshes(World);
    }
    else {
        SampleHeightAboveTerrain(LatLongHeightPoints,
            [this, World](TArray<FVector>& SampledWorldPoints ,  TArray<FVector> SampleWorldProjectionPoints)
            {
                WorldPoints = SampledWorldPoints;
                CreateMeshes(World);
            });
    }

}


void FLine::SetProjectionVisibility(bool bVisible)
{
	if (WallMeshComponent)
	{
		WallMeshComponent->SetVisibility(bVisible, true);
		WallMeshComponent->SetHiddenInGame(!bVisible);
	}
}

void FLine::SetVisibility(bool bVisible)
{
	if (WallMeshComponent && LineMeshComponent)
	{
		WallMeshComponent->SetVisibility(bVisible, true);
		WallMeshComponent->SetHiddenInGame(!bVisible);
		LineMeshComponent->SetVisibility(bVisible, true);
		LineMeshComponent->SetHiddenInGame(!bVisible);
	}

}


void FLine::UpdateScale(UWorld* World)
{

    // Recalculate the corner offsets based on the new width and height
    const float HalfWidth = LineWidth / 2.0f;
    const float HalfHeight = LineHeight / 2.0f;

    TArray<FVector> Vertices;
    TArray<int32> Triangles;
    TArray<FVector> Normals;
    TArray<FVector2D> UVs;
    TArray<FLinearColor> Colors;  // Using FLinearColor instead of FColor
    TArray<FProcMeshTangent> Tangents;
    int32 VertexIndex = 0;

    // --- Compute Corner Offsets ---
    struct FLineCorner { FVector Left; FVector Right; };
    TArray<FLineCorner> Corners;
    Corners.SetNum(WorldPoints.Num());

    for (int32 i = 0; i < WorldPoints.Num(); ++i)
    {
        FVector PrevDir, NextDir;

        if (i == 0)
        {
            NextDir = (WorldPoints[i + 1] - WorldPoints[i]).GetSafeNormal();
            FVector Right = FVector::CrossProduct(NextDir, FVector::UpVector).GetSafeNormal();
            Corners[i].Right = Right * HalfWidth;
            Corners[i].Left = -Right * HalfWidth;
        }
        else if (i == WorldPoints.Num() - 1)
        {
            PrevDir = (WorldPoints[i] - WorldPoints[i - 1]).GetSafeNormal();
            FVector Right = FVector::CrossProduct(PrevDir, FVector::UpVector).GetSafeNormal();
            Corners[i].Right = Right * HalfWidth;
            Corners[i].Left = -Right * HalfWidth;
        }
        else
        {
            PrevDir = (WorldPoints[i] - WorldPoints[i - 1]).GetSafeNormal();
            NextDir = (WorldPoints[i + 1] - WorldPoints[i]).GetSafeNormal();

            FVector PrevRight = FVector::CrossProduct(PrevDir, FVector::UpVector).GetSafeNormal();
            FVector NextRight = FVector::CrossProduct(NextDir, FVector::UpVector).GetSafeNormal();

            FVector AvgRight = (PrevRight + NextRight).GetSafeNormal();
            float Dot = FVector::DotProduct(AvgRight, FVector::CrossProduct(NextDir, FVector::UpVector));
            float MiterLength = FMath::Abs(Dot) > KINDA_SMALL_NUMBER ? HalfWidth / Dot : HalfWidth;

            const float MaxMiter = HalfWidth * 2.0f;
            MiterLength = FMath::Clamp(MiterLength, 0.0f, MaxMiter);

            Corners[i].Right = AvgRight * MiterLength;
            Corners[i].Left = -AvgRight * MiterLength;
        }
    }

    // --- Build Mesh Between Segments ---
    for (int32 i = 0; i < WorldPoints.Num() - 1; ++i)
    {
        FVector A = WorldPoints[i];
        FVector B = WorldPoints[i + 1];

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

        // Side faces
        Vertices.Append({ RT0, RB0, RB1, RT1 });
        Triangles.Append({
            VertexIndex, VertexIndex + 2, VertexIndex + 1,
            VertexIndex, VertexIndex + 3, VertexIndex + 2
            });
        VertexIndex += 4;

        Vertices.Append({ LT1, LB1, LB0, LT0 });
        Triangles.Append({
            VertexIndex, VertexIndex + 2, VertexIndex + 1,
            VertexIndex, VertexIndex + 3, VertexIndex + 2
            });
        VertexIndex += 4;

        Vertices.Append({ RT1, RB1, LB1, LT1 });
        Triangles.Append({
            VertexIndex, VertexIndex + 2, VertexIndex + 1,
            VertexIndex, VertexIndex + 3, VertexIndex + 2
            });
        VertexIndex += 4;

        Vertices.Append({ LT0, LB0, RB0, RT0 });
        Triangles.Append({
            VertexIndex, VertexIndex + 2, VertexIndex + 1,
            VertexIndex, VertexIndex + 3, VertexIndex + 2
            });
        VertexIndex += 4;
    }

    // Apply updated vertex attributes
    for (int32 i = 0; i < Vertices.Num(); ++i)
    {
        Normals.Add(FVector::UpVector);  // Use UpVector for top/bottom
        UVs.Add(FVector2D(0, 0));        // Optional: Customize for UV mapping
        Colors.Add(LineColor);           // Line color
        Tangents.Add(FProcMeshTangent(1, 0, 0));  // Tangent direction
    }

    UKismetProceduralMeshLibrary::CalculateTangentsForMesh(
        Vertices, Triangles, UVs, Normals, Tangents);
    // Update the existing mesh using the correct method
    if (LineMeshComponent)
    {
        // Now using UpdateMeshSection_LinearColor to update with FLinearColor
        LineMeshComponent->UpdateMeshSection_LinearColor(0, Vertices, Normals, UVs, Colors, Tangents, true);
    }

}


void FLine::DrawInternationalBorder(UWorld* World)
{
    if (!World || !Material || WorldPoints.Num() < 2) return;

    const float HalfWidth = LineWidth;
    const float HalfHeight = LineHeight;

    // Minimum distance between points (adjust as needed)
    const float MinimumDistanceBetweenPoints = 0.0001f; // Small distance threshold to avoid closely packed points

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

    // --- Compute Corners for International Border ---
    struct FLineCorner { FVector Left; FVector Right; };
    TArray<FLineCorner> Corners;
    Corners.SetNum(WorldPoints.Num());

    // Create mesh and compute corner offsets, but skip very close points to reduce distortion
    for (int32 i = 0; i < WorldPoints.Num(); ++i)
    {
        if (i > 0 && FVector::Dist(WorldPoints[i], WorldPoints[i - 1]) < MinimumDistanceBetweenPoints)
        {
            continue; // Skip points that are too close to each other
        }

        FVector PrevDir, NextDir;

        if (i == 0)
        {
            NextDir = (WorldPoints[i + 1] - WorldPoints[i]).GetSafeNormal();
            FVector Right = FVector::CrossProduct(NextDir, FVector::UpVector).GetSafeNormal();
            Corners[i].Right = Right * HalfWidth;
            Corners[i].Left = -Right * HalfWidth;
        }
        else if (i == WorldPoints.Num() - 1)
        {
            PrevDir = (WorldPoints[i] - WorldPoints[i - 1]).GetSafeNormal();
            FVector Right = FVector::CrossProduct(PrevDir, FVector::UpVector).GetSafeNormal();
            Corners[i].Right = Right * HalfWidth;
            Corners[i].Left = -Right * HalfWidth;
        }
        else
        {
            PrevDir = (WorldPoints[i] - WorldPoints[i - 1]).GetSafeNormal();
            NextDir = (WorldPoints[i + 1] - WorldPoints[i]).GetSafeNormal();

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
    for (int32 i = 0; i < WorldPoints.Num() - 1; ++i)
    {
        FVector A = WorldPoints[i];
        FVector B = WorldPoints[i + 1];

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

        // Side faces
        Vertices.Append({ RT0, RB0, RB1, RT1 });
        Triangles.Append({
            VertexIndex, VertexIndex + 2, VertexIndex + 1,
            VertexIndex, VertexIndex + 3, VertexIndex + 2
            });
        VertexIndex += 4;

        Vertices.Append({ LT1, LB1, LB0, LT0 });
        Triangles.Append({
            VertexIndex, VertexIndex + 2, VertexIndex + 1,
            VertexIndex, VertexIndex + 3, VertexIndex + 2
            });
        VertexIndex += 4;

        Vertices.Append({ RT1, RB1, LB1, LT1 });
        Triangles.Append({
            VertexIndex, VertexIndex + 2, VertexIndex + 1,
            VertexIndex, VertexIndex + 3, VertexIndex + 2
            });
        VertexIndex += 4;

        Vertices.Append({ LT0, LB0, RB0, RT0 });
        Triangles.Append({
            VertexIndex, VertexIndex + 2, VertexIndex + 1,
            VertexIndex, VertexIndex + 3, VertexIndex + 2
            });
        VertexIndex += 4;
    }

    // Apply Vertex Attributes
    for (int32 i = 0; i < Vertices.Num(); ++i)
    {
        Normals.Add(FVector::UpVector);  // Use UpVector for top/bottom
        UVs.Add(FVector2D(0, 0));        // Optional: Customize for UV mapping
        Colors.Add(LineColor);           // Line color
        Tangents.Add(FProcMeshTangent(1, 0, 0));  // Tangent direction
    }

    // Create Mesh Component if needed
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

    // Set Mesh Section and Dynamic Material
    LineMeshComponent->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);
    LineMeshComponent->SetMaterial(0, DynamicMaterial);  // Apply dynamic material to line
    LineMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    LineMeshComponent->SetCastShadow(false);
    LineMeshComponent->SetCastInsetShadow(false);
    LineMeshComponent->SetCastHiddenShadow(false);
}


// Spline Mesh Components(Line Draw Actor)

//void FLine::Draw(UWorld* World, UMaterialInterface* Material)
//{
//	if (!World || !Material) return;
//
//	TArray<FVector> Points;
//	for (const FVector& Pt : WorldPoints)
//	{
//		Points.Add(Pt);
//	}
//
//	TArray<FVector> LatLongPoints3d;
//	for (const FVector2D& LatLong : LatLongPoints)
//	{
//		LatLongPoints3d.Add(FVector(LatLong.X, LatLong.Y, 0));
//	}
//
//	ALineDrawerActor* LineDrawer = World->SpawnActor<ALineDrawerActor>(FVector::ZeroVector, FRotator::ZeroRotator);
//	if (LineDrawer)
//	{
//		LineDrawer->UpdateLine(Points, Material);
//	}
//
//	FString MaterialPath = "/Game/Materials/Drawings/M_Plane";
//	UMaterialInterface* PlaneMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, *MaterialPath));
//	if (!PlaneMaterial) return;
//
//	FCesiumSampleHeightMostDetailedCallback CesiumCallback;
//
//	// Bind lambda safely
//	CesiumCallback.BindLambda(
//		[this, World, PlaneMaterial](ACesium3DTileset* /*Tileset*/, const TArray<FCesiumSampleHeightResult>& Results, const TArray<FString>& /*Warnings*/)
//		{
//			if (Results.Num() != WorldPoints.Num())
//			{
//				UE_LOG(LogTemp, Error, TEXT("Mismatch between WorldPoints (%d) and Results (%d)"), WorldPoints.Num(), Results.Num());
//				return;
//			}
//
//			for (int32 i = 0; i < Results.Num() - 1; ++i)
//			{
//				const auto& ResultA = Results[i];
//				const auto& ResultB = Results[i + 1];
//
//				if (ResultA.SampleSuccess && ResultB.SampleSuccess)
//				{
//					FVector GroundA = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(ResultA.LongitudeLatitudeHeight);
//					FVector GroundB = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(ResultB.LongitudeLatitudeHeight);
//
//					// Use the original WorldPoints for top, sampled heights for bottom
//					SpawnWallQuad(World, WorldPoints[i], GroundA, WorldPoints[i + 1], GroundB, PlaneMaterial);
//				}
//				else
//				{
//					UE_LOG(LogTemp, Warning, TEXT("Skipping wall at segment %d due to failed height sampling"), i);
//				}
//			}
//		});
//
//	Tileset->SampleHeightMostDetailed(LatLongPoints3d, CesiumCallback);
//}

//2d planer line
//void FLine::Draw(UWorld* World, UMaterialInterface* Material)
//{
//	if (!World || !Material || WorldPoints.Num() < 2) return;
//
//	// Prepare top-face line mesh (procedural)
//	const float HalfThickness = 100000.0f;
//
//
//	TArray<FVector> OffsetPointsUp;
//	TArray<FVector> OffsetPointsDown;
//
//	for (int32 i = 0; i < WorldPoints.Num(); ++i)
//	{
//		FVector Prev = i > 0 ? WorldPoints[i - 1] : WorldPoints[i];
//		FVector Next = i < WorldPoints.Num() - 1 ? WorldPoints[i + 1] : WorldPoints[i];
//
//		FVector DirA = (WorldPoints[i] - Prev).GetSafeNormal();
//		FVector DirB = (Next - WorldPoints[i]).GetSafeNormal();
//		FVector AvgDir = (DirA + DirB).GetSafeNormal();
//
//		FVector Right = FVector::CrossProduct(AvgDir, FVector::UpVector).GetSafeNormal();
//		OffsetPointsUp.Add(WorldPoints[i] + Right * HalfThickness);
//		OffsetPointsDown.Add(WorldPoints[i] - Right * HalfThickness);
//	}
//
//	// Build mesh data
//	TArray<FVector> Vertices;
//	TArray<int32> Triangles;
//	TArray<FVector> Normals;
//	TArray<FVector2D> UVs;
//	TArray<FLinearColor> Colors;
//	TArray<FProcMeshTangent> Tangents;
//	int32 VertexIndex = 0;
//
//	for (int32 i = 0; i < WorldPoints.Num() - 1; ++i)
//	{
//		FVector V0 = OffsetPointsUp[i];
//		FVector V1 = OffsetPointsDown[i];
//		FVector V2 = OffsetPointsUp[i + 1];
//		FVector V3 = OffsetPointsDown[i + 1];
//
//		Vertices.Append({ V0, V1, V2, V3 });
//		Triangles.Append({ VertexIndex, VertexIndex + 2, VertexIndex + 1, VertexIndex + 2, VertexIndex + 3, VertexIndex + 1 });
//
//		for (int j = 0; j < 4; ++j)
//		{
//			Normals.Add(FVector::UpVector);
//			UVs.Add(FVector2D(0, 0));
//			Colors.Add(LineColor);
//			Tangents.Add(FProcMeshTangent(1, 0, 0));
//		}
//		VertexIndex += 4;
//	}
//
//
//	if (!LineMeshComponent)
//	{
//		LineMeshComponent = NewObject<UProceduralMeshComponent>(World->GetWorldSettings());
//		if (!LineMeshComponent) return;
//
//		LineMeshComponent->RegisterComponent();
//		LineMeshComponent->AttachToComponent(World->GetWorldSettings()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
//	}
//	else
//	{
//		LineMeshComponent->ClearAllMeshSections();
//	}
//
//	LineMeshComponent->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);
//	LineMeshComponent->SetMaterial(0, Material);
//	LineMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//
//	// --- TERRAIN PROJECTION (WALLS) ---
//
//	TArray<FVector> LatLongPoints3d;
//	for (const FVector2D& LatLong : LatLongPoints)
//	{
//		LatLongPoints3d.Add(FVector(LatLong.X, LatLong.Y, 0));
//	}
//
//	FString MaterialPath = "/Game/Materials/Drawings/M_Plane";
//	UMaterialInterface* PlaneMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, *MaterialPath));
//	if (!PlaneMaterial) return;
//
//	FCesiumSampleHeightMostDetailedCallback CesiumCallback;
//	CesiumCallback.BindLambda(
//		[this, World, PlaneMaterial](ACesium3DTileset* /*Tileset*/, const TArray<FCesiumSampleHeightResult>& Results, const TArray<FString>& /*Warnings*/)
//		{
//			if (Results.Num() != WorldPoints.Num())
//			{
//				UE_LOG(LogTemp, Error, TEXT("Line projection mismatch: %d points vs %d results"), WorldPoints.Num(), Results.Num());
//				return;
//			}
//
//			TArray<FVector> Vertices;
//			TArray<int32> Triangles;
//			TArray<FVector> Normals;
//			TArray<FVector2D> UVs;
//			TArray<FLinearColor> Colors;
//			TArray<FProcMeshTangent> Tangents;
//
//			int32 VertexIndex = 0;
//
//			for (int32 i = 0; i < Results.Num() - 1; ++i)
//			{
//				if (!Results[i].SampleSuccess || !Results[i + 1].SampleSuccess) continue;
//
//				FVector TopA = WorldPoints[i];
//				FVector TopB = WorldPoints[i + 1];
//				FVector BottomA = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(Results[i].LongitudeLatitudeHeight);
//				FVector BottomB = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(Results[i + 1].LongitudeLatitudeHeight);
//
//				Vertices.Append({ TopA, BottomA, BottomB, TopB });
//				Triangles.Append({ VertexIndex, VertexIndex + 2, VertexIndex + 1, VertexIndex, VertexIndex + 3, VertexIndex + 2 });
//
//				for (int j = 0; j < 4; ++j)
//				{
//					Normals.Add(FVector::UpVector);
//					UVs.Add(FVector2D(0, 0));
//					Colors.Add(LineColor);
//					Tangents.Add(FProcMeshTangent(1, 0, 0));
//				}
//
//				VertexIndex += 4;
//			}
//
//			if (!WallMeshComponent)
//			{
//				WallMeshComponent = NewObject<UProceduralMeshComponent>(World->GetWorldSettings());
//				if (!WallMeshComponent) return;
//
//				WallMeshComponent->RegisterComponent();
//				WallMeshComponent->AttachToComponent(World->GetWorldSettings()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
//			}
//			else
//			{
//				WallMeshComponent->ClearAllMeshSections();
//			}
//
//			WallMeshComponent->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);
//			WallMeshComponent->SetMaterial(0, PlaneMaterial);
//			WallMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//		});
//
//	Tileset->SampleHeightMostDetailed(LatLongPoints3d, CesiumCallback);
//}
