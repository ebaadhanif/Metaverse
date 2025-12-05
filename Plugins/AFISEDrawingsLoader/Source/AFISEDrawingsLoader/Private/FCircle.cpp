#include "FCircle.h"
#include "UObject/Package.h"                 // <- makes UPackage : UObject known
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "ProceduralMeshComponent.h"

FCircle::FCircle(const FVector& InWorldPos, const FVector& InLatLongHeight, float InRadius)
    : WorldPosition(InWorldPos),
    LatLongHeight(InLatLongHeight),
    Radius(InRadius),
    LineWidth(1)
{
    // WorldPosition = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(FVector(LatLongHeight.X, LatLongHeight.Y, 10000));
    MaterialPath = "/Game/Materials/Drawings/M_Circle";
    Material = Cast<UMaterialInterface>(
        StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, *MaterialPath));

    if (Material)
    {
        // Use GetTransientPackage() instead of nullptr
        DynamicMaterial = UMaterialInstanceDynamic::Create(Material, LineMeshComponent);
        // DynamicMaterial->AddToRoot(); // optional if you want to prevent GC
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load Material at path: %s"), *MaterialPath);
    }

    ProjectionMaterial = Cast<UMaterialInterface>(
        StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, *ProjectionMaterialPath));

    if (ProjectionMaterial)
    {
        // Use GetTransientPackage() instead of nullptr
        DynamicProjectionMaterial = UMaterialInstanceDynamic::Create(ProjectionMaterial, WallMeshComponent);
        // DynamicProjectionMaterial->AddToRoot(); // optional if you want to prevent GC
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load Projection Material at path: %s"), *ProjectionMaterialPath);
    }
}

FString FCircle::GetShapeType() const { return TEXT("Circle"); }
FVector FCircle::GetWorldPosition() const { return WorldPosition; }
FVector FCircle::GetLatLongHeightPosition() const { return LatLongHeight; }

void FCircle::CreateMeshes(UWorld* World) {
    if (!World || !Material) return;
    if (isCleared) return;
    //if (LineMeshComponent && WallMeshComponent)
    //{
    //    LineMeshComponent->DestroyComponent();
    //    WallMeshComponent->DestroyComponent();
    //    LineMeshComponent = nullptr;
    //    WallMeshComponent = nullptr;
    //}
    //if (DynamicMaterial) {

    //    DynamicMaterial->SetVectorParameterValue(FName("BaseColor"), LineColor);
    //}




    // Step 4: Create the mesh for the circle
    TArray<FVector> Vertices;
    TArray<int32> Triangles;
    TArray<FVector> Normals;
    TArray<FVector2D> UVs;
    TArray<FLinearColor> Colors;
    TArray<FProcMeshTangent> Tangents;

    int32 VertexIndex = 0;

  //  NumSegments = FMath::Clamp(FMath::CeilToInt((2 * PI * Radius * NM_TO_CM) / TargetEdgeLength), 16, 512);


    // Loop through the segments and create triangles between the outer and inner circle points
    for (int32 i = 0; i < NumSegments; ++i)
    {
        int32 Next = (i + 1) % NumSegments;

        // Outer circle vertices
        FVector OuterA = WorldOuterPoints[i];
        FVector OuterB = WorldOuterPoints[Next];

        // Inner circle vertices
        FVector InnerA = WorldInnerPoints[i];
        FVector InnerB = WorldInnerPoints[Next];

        // Add the vertices for the top face (at Z = 0)
        Vertices.Add(OuterA);  // 0
        Vertices.Add(OuterB);  // 1
        Vertices.Add(InnerA);  // 2
        Vertices.Add(InnerB);  // 3

        // Add the triangles (two per segment) for the top face
        Triangles.Append({
            VertexIndex + 0, VertexIndex + 2, VertexIndex + 1,
            VertexIndex + 2, VertexIndex + 3, VertexIndex + 1
            });

        // Add normals, UVs, and other attributes for the top face
        for (int32 j = 0; j < 4; ++j)
        {
            Normals.Add(FVector::UpVector);
            UVs.Add(FVector2D(0, 0));  // Default UV mapping
            Colors.Add(LineColor);      // Color
            Tangents.Add(FProcMeshTangent(1, 0, 0));  // Tangents
        }

        // Bottom face vertices (at Z = -LineHeight)
        FVector BottomOuterA = OuterA - FVector(0, 0, LineHeight);
        FVector BottomOuterB = OuterB - FVector(0, 0, LineHeight);
        FVector BottomInnerA = InnerA - FVector(0, 0, LineHeight);
        FVector BottomInnerB = InnerB - FVector(0, 0, LineHeight);

        // Add the vertices for the bottom face (at Z = -LineHeight)
        Vertices.Add(BottomOuterA);  // 4
        Vertices.Add(BottomOuterB);  // 5
        Vertices.Add(BottomInnerA);  // 6
        Vertices.Add(BottomInnerB);  // 7

        // Add the triangles (two per segment) for the bottom face
        Triangles.Append({
            VertexIndex + 4, VertexIndex + 6, VertexIndex + 5,
            VertexIndex + 6, VertexIndex + 7, VertexIndex + 5
            });

        // Add normals, UVs, and other attributes for the bottom face
        for (int32 j = 0; j < 4; ++j)
        {
            Normals.Add(FVector::DownVector);
            UVs.Add(FVector2D(0, 0));  // Default UV mapping
            Colors.Add(LineColor);      // Color
            Tangents.Add(FProcMeshTangent(1, 0, 0));  // Tangents
        }

        // Side faces (connecting the outer and inner circle)
        // Side 1 (outer)
        Vertices.Add(OuterA);
        Vertices.Add(OuterB);
        Vertices.Add(BottomOuterA);
        Vertices.Add(BottomOuterB);

        // Side 2 (inner)
        Vertices.Add(InnerA);
        Vertices.Add(InnerB);
        Vertices.Add(BottomInnerA);
        Vertices.Add(BottomInnerB);

        // Side triangles
        Triangles.Append({
            VertexIndex + 0, VertexIndex + 2, VertexIndex + 1,
            VertexIndex + 1, VertexIndex + 2, VertexIndex + 3,
            VertexIndex + 4, VertexIndex + 6, VertexIndex + 5,
            VertexIndex + 5, VertexIndex + 6, VertexIndex + 7
            });

        // Add normals, UVs, and other attributes for the side faces
        for (int32 j = 0; j < 8; ++j)
        {
            Normals.Add(FVector::UpVector);
            UVs.Add(FVector2D(0, 0));  // Default UV mapping
            Colors.Add(LineColor);      // Color
            Tangents.Add(FProcMeshTangent(1, 0, 0));  // Tangents
        }

        VertexIndex += 8;
    }

    // Step 5: Create the Procedural Mesh Component
    if (!LineMeshComponent)
    {
        LineMeshComponent = NewObject<UProceduralMeshComponent>(World->GetWorldSettings());
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

    // Step 6: Create the mesh section for the circle
    LineMeshComponent->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);
  //  LineMeshComponent->SetMaterial(0, DynamicMaterial);  // Apply dynamic material to the circle
    LineMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    LineMeshComponent->SetCastShadow(false);
    LineMeshComponent->SetCastInsetShadow(false);
    LineMeshComponent->SetCastHiddenShadow(false);

    if (!WallMeshComponent)
    {
        WallMeshComponent = NewObject<UProceduralMeshComponent>(World->GetWorldSettings());
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

    //if (DynamicProjectionMaterial) {
    //    WallMeshComponent->SetMaterial(0, DynamicProjectionMaterial);
    //}

    //if (DynamicProjectionMaterial) {
    //    DynamicProjectionMaterial->SetVectorParameterValue(FName("ProjectionColor"), LineColor);
    //}


    TArray<FVector> Vertices2;
    TArray<int32> Triangles2;
    TArray<FVector> Normals2;
    TArray<FVector2D> UVs2;
    TArray<FLinearColor> VertexColors2;
    TArray<FProcMeshTangent> Tangents2;


    int32 VertexIndex2 = 0;
    for (int32 i = 0; i < WorldSampledProjectionPoints.Num(); ++i)
    {
        int32 Next = (i + 1) % WorldSampledProjectionPoints.Num();
   
        FVector TopA = WorldOuterPoints[i];
        FVector TopB = WorldOuterPoints[Next];
        FVector BottomA = WorldSampledProjectionPoints[i];
        FVector BottomB = WorldSampledProjectionPoints[Next];

        // Add quad vertices
        Vertices2.Add(TopA);     // 0
        Vertices2.Add(BottomA);  // 1
        Vertices2.Add(BottomB);  // 2
        Vertices2.Add(TopB);     // 3

        Triangles2.Append({
            VertexIndex2 + 0, VertexIndex2 + 2, VertexIndex2 + 1,
            VertexIndex2 + 0, VertexIndex2 + 3, VertexIndex2 + 2
            });

        for (int j = 0; j < 4; ++j)
        {
            Normals2.Add(FVector::UpVector);  // Normal pointing upward
            UVs2.Add(FVector2D(0, 0));        // Default UV Coordinates
            VertexColors2.Add(LineColor);     // Color
            Tangents2.Add(FProcMeshTangent(1, 0, 0));  // Tangents
        }

        VertexIndex2 += 4;
    }

    if (WallMeshComponent) {
        WallMeshComponent->CreateMeshSection_LinearColor(0, Vertices2, Triangles2, Normals2, UVs2, VertexColors2, Tangents2, true);
        WallMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

void FCircle::Draw(UWorld* World)
{

    WorldPosition = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(
        FVector(LatLongHeight.X, LatLongHeight.Y, LatLongHeight.Z));


    const float RadiusCM = Radius * NM_TO_CM;
    // NumSegments = FMath::Clamp(FMath::CeilToInt((4 * PI * Radius * NM_TO_CM) / TargetEdgeLength), 16, 2500);

     // Step 1: Calculate the number of segments for the circle perimeter
    const float AngleStep = 4 * PI / NumSegments;

    // Step 2: Generate the points along the circle perimeter for outer and inner radii
    TArray<FVector> OuterCirclePoints;
    TArray<FVector> InnerCirclePoints;

    for (int32 i = 0; i < NumSegments; ++i)
    {
        float AngleRad = AngleStep * i;
        float X = FMath::Cos(AngleRad);
        float Y = FMath::Sin(AngleRad);

        // Outer and Inner Circle Points (adjusted by radius)
        OuterCirclePoints.Add(FVector(X * RadiusCM, Y * RadiusCM, 0));
        InnerCirclePoints.Add(FVector(X * (RadiusCM - LineWidth), Y * (RadiusCM - LineWidth), 0)); // Inner radius
    }

    for (const FVector& Pt : OuterCirclePoints)
    {
        WorldOuterPoints.Add(WorldPosition + Pt);
    }

    TArray<FVector> WorldPoints3D;
    WorldPoints3D.Add(LatLongHeight);
    for (const FVector& Pt : WorldOuterPoints)
    {
        FVector Point = Georeference->TransformUnrealPositionToLongitudeLatitudeHeight(Pt);
        WorldPoints3D.Add(Point);
    }

    SampleHeightAboveTerrain(WorldPoints3D,
        [this, World, OuterCirclePoints, InnerCirclePoints](TArray<FVector>& SampledWorldPoints, TArray<FVector> SampleWorldProjectionPoints)
        {
            if (isCleared) return;
            WorldOuterPoints.Reset();
            WorldInnerPoints.Reset();
            WorldSampledPoints.Reset();
            WorldSampledProjectionPoints.Reset();

            if (SampledWorldPoints.Num() > 0 && SampleWorldProjectionPoints.Num() > 0) {
                WorldPosition = SampledWorldPoints[0];
                //SampledWorldPoints.RemoveAt(0);
                //SampleWorldProjectionPoints.RemoveAt(0);
                //WorldSampledPoints = SampledWorldPoints;
                //WorldSampledProjectionPoints = SampleWorldProjectionPoints;
                for (int32 i = 1; i < SampledWorldPoints.Num(); i++) {
                    WorldSampledPoints.Add(SampledWorldPoints[i]);
                }
                for (int32 i = 1; i < SampleWorldProjectionPoints.Num(); i++) {
                    WorldSampledProjectionPoints.Add(SampleWorldProjectionPoints[i]);
                }
            }

            for (const FVector& Pt : OuterCirclePoints)
            {
                WorldOuterPoints.Add(WorldPosition + Pt);
            }

            for (const FVector& Pt : InnerCirclePoints)
            {
                WorldInnerPoints.Add(WorldPosition + Pt);
            }

            CreateMeshes(World);
        });


    for (const FVector& pt : WorldInnerPoints) {
        UE_LOG(LogTemp, Error, TEXT("World Inner Points : %s "), *pt.ToString());
    }

    for (const FVector& pt : WorldOuterPoints) {
        UE_LOG(LogTemp, Error, TEXT("World Outer Points : %s "), *pt.ToString());
    }


}

void FCircle::UpdateScale(UWorld* World)
{
    const bool bHasSection = (LineMeshComponent && LineMeshComponent->GetNumSections() > 0);
    if (!bHasSection)
    {
        return;
    }

    // Convert radius from nautical miles to centimeters (Unreal units)
    const float RadiusCM = Radius * NM_TO_CM;

    // Step 1: Calculate the number of segments for the circle perimeter
    //const int32 NumSegments = 360;
    const float AngleStep = 4 * PI / NumSegments;

    // Step 2: Generate the points along the circle perimeter for outer and inner radii
    TArray<FVector> OuterCirclePoints;
    TArray<FVector> InnerCirclePoints;

    for (int32 i = 0; i < NumSegments; ++i)
    {
        float AngleRad = AngleStep * i;
        float X = FMath::Cos(AngleRad);
        float Y = FMath::Sin(AngleRad);

        // Outer and Inner Circle Points (adjusted by radius)
        OuterCirclePoints.Add(FVector(X * RadiusCM, Y * RadiusCM, 0));
        InnerCirclePoints.Add(FVector(X * (RadiusCM - LineWidth), Y * (RadiusCM - LineWidth), 0)); // Inner radius
    }

    // Step 3: Transform points to world space
 /*   TArray<FVector> WorldOuterPoints;
    TArray<FVector> WorldInnerPoints;*/
    WorldOuterPoints.Reset();
    WorldInnerPoints.Reset();

    for (const FVector& Pt : OuterCirclePoints)
    {
        WorldOuterPoints.Add(WorldPosition + Pt);
    }

    for (const FVector& Pt : InnerCirclePoints)
    {
        WorldInnerPoints.Add(WorldPosition + Pt);
    }

    // Step 4: Create the mesh for the circle
    TArray<FVector> Vertices;
    TArray<int32> Triangles;
    TArray<FVector> Normals;
    TArray<FVector2D> UVs;
    TArray<FLinearColor> Colors;
    TArray<FProcMeshTangent> Tangents;

    int32 VertexIndex = 0;

    // Loop through the segments and create triangles between the outer and inner circle points
    for (int32 i = 0; i < NumSegments; ++i)
    {
        int32 Next = (i + 1) % NumSegments;

        // Outer circle vertices
        FVector OuterA = WorldOuterPoints[i];
        FVector OuterB = WorldOuterPoints[Next];

        // Inner circle vertices
        FVector InnerA = WorldInnerPoints[i];
        FVector InnerB = WorldInnerPoints[Next];

        // Add the vertices for the top face (at Z = 0)
        Vertices.Add(OuterA);  // 0
        Vertices.Add(OuterB);  // 1
        Vertices.Add(InnerA);  // 2
        Vertices.Add(InnerB);  // 3

        // Add the triangles (two per segment) for the top face
        Triangles.Append({
            VertexIndex + 0, VertexIndex + 2, VertexIndex + 1,
            VertexIndex + 2, VertexIndex + 3, VertexIndex + 1
            });

        // Add normals, UVs, and other attributes for the top face
        for (int32 j = 0; j < 4; ++j)
        {
            Normals.Add(FVector::UpVector);
            UVs.Add(FVector2D(0, 0));  // Default UV mapping
            Colors.Add(LineColor);      // Color
            Tangents.Add(FProcMeshTangent(1, 0, 0));  // Tangents
        }

        // Bottom face vertices (at Z = -LineHeight)
        FVector BottomOuterA = OuterA - FVector(0, 0, LineHeight);
        FVector BottomOuterB = OuterB - FVector(0, 0, LineHeight);
        FVector BottomInnerA = InnerA - FVector(0, 0, LineHeight);
        FVector BottomInnerB = InnerB - FVector(0, 0, LineHeight);

        // Add the vertices for the bottom face (at Z = -LineHeight)
        Vertices.Add(BottomOuterA);  // 4
        Vertices.Add(BottomOuterB);  // 5
        Vertices.Add(BottomInnerA);  // 6
        Vertices.Add(BottomInnerB);  // 7

        // Add the triangles (two per segment) for the bottom face
        Triangles.Append({
            VertexIndex + 4, VertexIndex + 6, VertexIndex + 5,
            VertexIndex + 6, VertexIndex + 7, VertexIndex + 5
            });

        // Add normals, UVs, and other attributes for the bottom face
        for (int32 j = 0; j < 4; ++j)
        {
            Normals.Add(FVector::DownVector);
            UVs.Add(FVector2D(0, 0));  // Default UV mapping
            Colors.Add(LineColor);      // Color
            Tangents.Add(FProcMeshTangent(1, 0, 0));  // Tangents
        }

        // Side faces (connecting the outer and inner circle)
        // Side 1 (outer)
        Vertices.Add(OuterA);
        Vertices.Add(OuterB);
        Vertices.Add(BottomOuterA);
        Vertices.Add(BottomOuterB);

        // Side 2 (inner)
        Vertices.Add(InnerA);
        Vertices.Add(InnerB);
        Vertices.Add(BottomInnerA);
        Vertices.Add(BottomInnerB);

        // Side triangles
        Triangles.Append({
            VertexIndex + 0, VertexIndex + 2, VertexIndex + 1,
            VertexIndex + 1, VertexIndex + 2, VertexIndex + 3,
            VertexIndex + 4, VertexIndex + 6, VertexIndex + 5,
            VertexIndex + 5, VertexIndex + 6, VertexIndex + 7
            });

        // Add normals, UVs, and other attributes for the side faces
        for (int32 j = 0; j < 8; ++j)
        {
            Normals.Add(FVector::UpVector);
            UVs.Add(FVector2D(0, 0));  // Default UV mapping
            Colors.Add(LineColor);      // Color
            Tangents.Add(FProcMeshTangent(1, 0, 0));  // Tangents
        }

        VertexIndex += 8;
    }

    if (LineMeshComponent)
    {
        LineMeshComponent->UpdateMeshSection_LinearColor(0, Vertices, Normals, UVs, Colors, Tangents, true);
    }


}



void FCircle::DrawCoverageFootPrint(UWorld* World, int32 Height) {

    WorldPosition = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(
        FVector(LatLongHeight.X, LatLongHeight.Y, LatLongHeight.Z));  //+ Height

    if (!World || !Material) return;

    if (isCleared) return;

    if (LineMeshComponent && WallMeshComponent)
    {
        LineMeshComponent->DestroyComponent();
        WallMeshComponent->DestroyComponent();
        LineMeshComponent = nullptr;
        WallMeshComponent = nullptr;
    }


    if (DynamicMaterial) {
        DynamicMaterial->SetVectorParameterValue(FName("BaseColor"), LineColor);
    }

    DynamicProjectionMaterial = UMaterialInstanceDynamic::Create(ProjectionMaterial, GetTransientPackage());


    if (DynamicProjectionMaterial) {
        DynamicProjectionMaterial->SetVectorParameterValue(FName("ProjectionColor"), LineColor);
    }



    // Convert radius from nautical miles to centimeters (Unreal units)
    const float RadiusCM = Radius * NM_TO_CM;

    // Step 1: Calculate the number of segments for the circle perimeter
    const float AngleStep = 4 * PI / NumSegments;

    // Step 2: Generate the points along the circle perimeter for outer and inner radii
    TArray<FVector> OuterCirclePoints;
    TArray<FVector> InnerCirclePoints;

    for (int32 i = 0; i < NumSegments; ++i)
    {
        float AngleRad = AngleStep * i;
        float X = FMath::Cos(AngleRad);
        float Y = FMath::Sin(AngleRad);

        // Outer and Inner Circle Points (adjusted by radius)
        OuterCirclePoints.Add(FVector(X * RadiusCM, Y * RadiusCM, 0));
        InnerCirclePoints.Add(FVector(X * (RadiusCM - LineWidth * 1000), Y * (RadiusCM - LineWidth * 1000), 0)); // Inner radius
    }



    for (const FVector& Pt : OuterCirclePoints)
    {
        WorldOuterPoints.Add(WorldPosition + Pt);
    }

    for (const FVector& Pt : InnerCirclePoints)
    {
        WorldInnerPoints.Add(WorldPosition + Pt);
    }

    // Step 4: Create the mesh for the circle
    TArray<FVector> Vertices;
    TArray<int32> Triangles;
    TArray<FVector> Normals;
    TArray<FVector2D> UVs;
    TArray<FLinearColor> Colors;
    TArray<FProcMeshTangent> Tangents;

    int32 VertexIndex = 0;

    // Loop through the segments and create triangles between the outer and inner circle points
    for (int32 i = 0; i < NumSegments; ++i)
    {
        int32 Next = (i + 1) % NumSegments;

        // Outer circle vertices
        FVector OuterA = WorldOuterPoints[i];
        FVector OuterB = WorldOuterPoints[Next];

        // Inner circle vertices
        FVector InnerA = WorldInnerPoints[i];
        FVector InnerB = WorldInnerPoints[Next];

        // Add the vertices for the top face (at Z = 0)
        Vertices.Add(OuterA);  // 0
        Vertices.Add(OuterB);  // 1
        Vertices.Add(InnerA);  // 2
        Vertices.Add(InnerB);  // 3

        // Add the triangles (two per segment) for the top face
        Triangles.Append({
            VertexIndex + 0, VertexIndex + 2, VertexIndex + 1,
            VertexIndex + 2, VertexIndex + 3, VertexIndex + 1
            });

        // Add normals, UVs, and other attributes for the top face
        for (int32 j = 0; j < 4; ++j)
        {
            Normals.Add(FVector::UpVector);
            UVs.Add(FVector2D(0, 0));  // Default UV mapping
            Colors.Add(LineColor);      // Color
            Tangents.Add(FProcMeshTangent(1, 0, 0));  // Tangents
        }

        // Bottom face vertices (at Z = -LineHeight)
        FVector BottomOuterA = OuterA - FVector(0, 0, LineHeight);
        FVector BottomOuterB = OuterB - FVector(0, 0, LineHeight);
        FVector BottomInnerA = InnerA - FVector(0, 0, LineHeight);
        FVector BottomInnerB = InnerB - FVector(0, 0, LineHeight);

        // Add the vertices for the bottom face (at Z = -LineHeight)
        Vertices.Add(BottomOuterA);  // 4
        Vertices.Add(BottomOuterB);  // 5
        Vertices.Add(BottomInnerA);  // 6
        Vertices.Add(BottomInnerB);  // 7

        // Add the triangles (two per segment) for the bottom face
        Triangles.Append({
            VertexIndex + 4, VertexIndex + 6, VertexIndex + 5,
            VertexIndex + 6, VertexIndex + 7, VertexIndex + 5
            });

        // Add normals, UVs, and other attributes for the bottom face
        for (int32 j = 0; j < 4; ++j)
        {
            Normals.Add(FVector::DownVector);
            UVs.Add(FVector2D(0, 0));  // Default UV mapping
            Colors.Add(LineColor);      // Color
            Tangents.Add(FProcMeshTangent(1, 0, 0));  // Tangents
        }

        // Side faces (connecting the outer and inner circle)
        // Side 1 (outer)
        Vertices.Add(OuterA);
        Vertices.Add(OuterB);
        Vertices.Add(BottomOuterA);
        Vertices.Add(BottomOuterB);

        // Side 2 (inner)
        Vertices.Add(InnerA);
        Vertices.Add(InnerB);
        Vertices.Add(BottomInnerA);
        Vertices.Add(BottomInnerB);

        // Side triangles
        Triangles.Append({
            VertexIndex + 0, VertexIndex + 2, VertexIndex + 1,
            VertexIndex + 1, VertexIndex + 2, VertexIndex + 3,
            VertexIndex + 4, VertexIndex + 6, VertexIndex + 5,
            VertexIndex + 5, VertexIndex + 6, VertexIndex + 7
            });

        // Add normals, UVs, and other attributes for the side faces
        for (int32 j = 0; j < 8; ++j)
        {
            Normals.Add(FVector::UpVector);
            UVs.Add(FVector2D(0, 0));  // Default UV mapping
            Colors.Add(LineColor);      // Color
            Tangents.Add(FProcMeshTangent(1, 0, 0));  // Tangents
        }

        VertexIndex += 8;
    }

    // Step 5: Create the Procedural Mesh Component
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

    // Step 6: Create the mesh section for the circle
    LineMeshComponent->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);
    LineMeshComponent->SetMaterial(0, DynamicMaterial);  // Apply dynamic material to the circle
    LineMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    LineMeshComponent->SetCastShadow(false);
    LineMeshComponent->SetCastInsetShadow(false);
    LineMeshComponent->SetCastHiddenShadow(false);

    TArray<FVector> WorldPoints3D;
    TArray<FVector> Results;

    for (const FVector& Pt : WorldOuterPoints)
    {
        FVector Point = Georeference->TransformUnrealPositionToLongitudeLatitudeHeight(Pt);
        WorldPoints3D.Add(Point);
        Point.Z -= LatLongHeight.Z;
        Point.Z -= Height;
        Point.Z -= 100000.0f;
        Results.Add(Point);
    }

    if (!DynamicProjectionMaterial) return;
    if (isCleared) return;

    if (Results.Num() != WorldOuterPoints.Num()) return;

    TArray<FVector> Vertices2;
    TArray<int32> Triangles2;
    TArray<FVector> Normals2;
    TArray<FVector2D> UVs2;
    TArray<FLinearColor> VertexColors2;
    TArray<FProcMeshTangent> Tangents2;

    int32 VertexIndex2 = 0;
    for (int32 i = 0; i < Results.Num(); ++i)
    {
        int32 Next = (i + 1) % Results.Num();
      
        FVector TopA = WorldOuterPoints[i];
        FVector TopB = WorldOuterPoints[Next];
        FVector BottomA = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(Results[i]);
        FVector BottomB = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(Results[Next]);

        // Add quad vertices
        Vertices2.Add(TopA);     // 0
        Vertices2.Add(BottomA);  // 1
        Vertices2.Add(BottomB);  // 2
        Vertices2.Add(TopB);     // 3

        Triangles2.Append({
            VertexIndex2 + 0, VertexIndex2 + 2, VertexIndex2 + 1,
            VertexIndex2 + 0, VertexIndex2 + 3, VertexIndex2 + 2
            });

        for (int j = 0; j < 4; ++j)
        {
            Normals2.Add(FVector::UpVector);  // Normal pointing upward
            UVs2.Add(FVector2D(0, 0));        // Default UV Coordinates
            VertexColors2.Add(LineColor);     // Color
            Tangents2.Add(FProcMeshTangent(1, 0, 0));  // Tangents
        }

        VertexIndex2 += 4;
    }

    // Create and attach procedural mesh for walls
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
    bool isValid = WallMeshComponent->IsValidLowLevel();
    int32 NumSections = WallMeshComponent->GetNumSections();

    if (WallMeshComponent && WallMeshComponent->IsRegistered()) {

        WallMeshComponent->CreateMeshSection_LinearColor(0, Vertices2, Triangles2, Normals2, UVs2, VertexColors2, Tangents2, true);
        if (DynamicProjectionMaterial) {
            WallMeshComponent->SetMaterial(0, DynamicProjectionMaterial);
        }
        WallMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }



}

void FCircle::SetLineColor(const FLinearColor& InColor) { LineColor = InColor; }

void FCircle::SetLineHeight(int32 InHeight)
{
	LineHeight = InHeight * BaseLineHeight;

}

void FCircle::SetLineWidth(int32 InWidth) { LineWidth = InWidth * BaseLineWidth; }

void FCircle::SetFillColor(const FLinearColor& InColor) { FillColor = InColor; }

void FCircle::Clear()
{
    if (LineMeshComponent && WallMeshComponent)
    {
        LineMeshComponent->DestroyComponent();
        WallMeshComponent->DestroyComponent();
        LineMeshComponent = nullptr;
        WallMeshComponent = nullptr;
        //DynamicMaterial->RemoveFromRoot();
        //DynamicMaterial = nullptr;
        //DynamicProjectionMaterial->RemoveFromRoot();
        //DynamicProjectionMaterial = nullptr;
    }
    isCleared = true;
}

void FCircle::LogInfo() const
{



}

void FCircle::SetProjectionVisibility(bool bVisible)
{
    if (WallMeshComponent)
    {
        WallMeshComponent->SetVisibility(bVisible, true);
        WallMeshComponent->SetHiddenInGame(!bVisible);
    }
}

void FCircle::SetVisibility(bool bVisible)
{
    if (WallMeshComponent && LineMeshComponent)
    {
        WallMeshComponent->SetVisibility(bVisible, true);
        WallMeshComponent->SetHiddenInGame(!bVisible);
        LineMeshComponent->SetVisibility(bVisible, true);
        LineMeshComponent->SetHiddenInGame(!bVisible);
    }
}



//void FCircle::SampleHeightAboveTerrain(
//    const TArray<FVector>& LatLongPoints,
//    TFunction<void(TArray<FVector>&, TArray<FVector>&)> OnComplete)
//{
//    TWeakPtr<IShape> weakthis = AsShared();
//    FCesiumSampleHeightMostDetailedCallback CesiumCallback;
//    CesiumCallback.BindLambda([weakthis, LatLongPoints, OnComplete](ACesium3DTileset*, const TArray<FCesiumSampleHeightResult>& Results, const TArray<FString>& Warnings)
//        {
//            TArray<FVector> OutWorldPoints;
//            TArray<FVector> OutWorldProjectionPoints;
//            //TArray<FVector> TempArray;
//
//            if (!weakthis.IsValid()) {
//                OnComplete(OutWorldPoints, OutWorldProjectionPoints);
//                return;
//            }
//            float MaxHeight = 0;
//            float Height = LatLongPoints[0].Z;
//            FVector MaxHeightPoint;
//            for (const FString& warning : Warnings) {
//                UE_LOG(LogTemp, Error, TEXT("Warning Came from Height Sampling:%s "), *warning);
//            }
//            for (const FCesiumSampleHeightResult& Result : Results)
//            {
//            
//                if (Result.SampleSuccess)
//                {
//                    FVector Point = Result.LongitudeLatitudeHeight;
//                    //TempArray.Add(Point);
//                    OutWorldProjectionPoints.Add(Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(FVector(Point.X, Point.Y, Point.Z)));
//                    //MaxHeight = FMath::Max(MaxHeight, Result.LongitudeLatitudeHeight[2]);
//    /*                if (MaxHeight < Result.LongitudeLatitudeHeight[2]) {
//                        MaxHeightPoint = Point;
//                        MaxHeight = Result.LongitudeLatitudeHeight[2];
//                    }*/
//                    OutWorldPoints.Add(Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(
//                        FVector(Point.X, Point.Y, Point.Z + Height)));
//                }
//            }
//
//
//            AsyncTask(ENamedThreads::GameThread, [weakthis, OnComplete, OutWorldPoints = MoveTemp(OutWorldPoints), OutWorldProjectionPoints = MoveTemp(OutWorldProjectionPoints)]() mutable {
//                if (!weakthis.IsValid()) return;
//                OnComplete(OutWorldPoints, OutWorldProjectionPoints);
//                });
//        });
//    Tileset->SampleHeightMostDetailed(LatLongPoints, CesiumCallback);
//}
//

//Some Helper functions

//plane based- approach
//void FCircle::Draw(UWorld* World, UMaterialInterface* Material)
//{
//	if (!World || !Material) return;
//
//	ACesiumGeoreference* Georef = IShape::GetGeoreference();
//	if (!Georef) return;
//
//	if (SpawnedActor.IsValid())
//	{
//		SpawnedActor->Destroy();
//	}
//
//
//	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, nullptr);
//	DynamicMaterial->SetVectorParameterValue(FName("BaseColor"), LineColor);
//	float InnerWidth = 0.5 - (LineWidth / 100.0f);
//	DynamicMaterial->SetScalarParameterValue(FName("Outer"),0.5);
//	DynamicMaterial->SetScalarParameterValue(FName("Inner"),InnerWidth);
//
//	ProjectionMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, *ProjectionMaterialPath));
//	DynamicProjectionMaterial = UMaterialInstanceDynamic::Create(ProjectionMaterial, nullptr);
//	DynamicProjectionMaterial->SetVectorParameterValue(FName("ProjectionColor"), LineColor);
//
//
//	// Step 1: Spawn the circular surface (hollow ring)
//	WorldPosition = Georef->TransformLongitudeLatitudeHeightPositionToUnreal(FVector(LatLong.X, LatLong.Y, 50000));
//
//	AStaticMeshActor* PlaneActor = World->SpawnActor<AStaticMeshActor>(WorldPosition, FRotator::ZeroRotator);
//	if (!PlaneActor) return;
//
//	UStaticMesh* PlaneMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/EditorMeshes/PhAT_FloorBox.PhAT_FloorBox"));
//	if (!PlaneMesh) return;
//
//	UStaticMeshComponent* MeshComp = PlaneActor->GetStaticMeshComponent();
//	MeshComp->SetStaticMesh(PlaneMesh);
//	MeshComp->SetMaterial(0, DynamicMaterial);
//
//	constexpr float NM_TO_CM = 185200.0f;
//	const float RadiusCM = Radius * NM_TO_CM;
//	const float PlaneSizeCM = 1000.0f;
//
//	const float Scale = RadiusCM / (PlaneSizeCM / 2.0f);
//	MeshComp->SetWorldScale3D(FVector(Scale, Scale, LineHeight));
//	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//	PlaneActor->SetMobility(EComponentMobility::Movable);
//	SpawnedActor = PlaneActor;
//
//	// Step 2: Create circle perimeter points
//	const int32 NumSegments = 64;
//	TArray<FVector> LocalCirclePoints;
//	for (int32 i = 0; i < NumSegments; ++i)
//	{
//		float AngleRad = (2 * PI * i) / NumSegments;
//		float X = FMath::Cos(AngleRad) * 500.0f; // Unreal plane: 100x100 cm, so radius = 50
//		float Y = FMath::Sin(AngleRad) * 500.0f;
//		LocalCirclePoints.Add(FVector(X, Y, 0));
//	}
//
//	// Step 3: Transform points to world space
//	FTransform PlaneTransform = PlaneActor->GetActorTransform();
//	TArray<FVector> WorldCirclePoints;
//	for (const FVector& Pt : LocalCirclePoints)
//	{
//		WorldCirclePoints.Add(PlaneTransform.TransformPosition(Pt));
//	}
//
//	// Step 4: Convert to LatLong for height sampling
//	TArray<FVector> LatLongPoints;
//	for (const FVector& Pt : WorldCirclePoints)
//	{
//		FVector InLatLong = Georef->TransformUnrealPositionToLongitudeLatitudeHeight(Pt);
//		InLatLong.Z = 0;
//		LatLongPoints.Add(InLatLong);
//	}
//
//	// Load shading material
//
//	// Step 5: Height sampling + create one procedural mesh for all walls
//	FCesiumSampleHeightMostDetailedCallback Callback;
//	Callback.BindLambda(
//		[this, World, WorldCirclePoints](ACesium3DTileset* /*Tileset*/, const TArray<FCesiumSampleHeightResult>& Results, const TArray<FString>& /*Warnings*/)
//		{
//			if (Results.Num() != WorldCirclePoints.Num()) return;
//
//			TArray<FVector> Vertices;
//			TArray<int32> Triangles;
//			TArray<FVector> Normals;
//			TArray<FVector2D> UVs;
//			TArray<FLinearColor> VertexColors;
//			TArray<FProcMeshTangent> Tangents;
//
//			int32 VertexIndex = 0;
//			for (int32 i = 0; i < Results.Num(); ++i)
//			{
//				int32 Next = (i + 1) % Results.Num();
//				if (!Results[i].SampleSuccess || !Results[Next].SampleSuccess) continue;
//
//				FVector TopA = WorldCirclePoints[i];
//				FVector TopB = WorldCirclePoints[Next];
//				FVector BottomA = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(Results[i].LongitudeLatitudeHeight);
//				FVector BottomB = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(Results[Next].LongitudeLatitudeHeight);
//
//				// Quad vertices
//				Vertices.Add(TopA);     // 0
//				Vertices.Add(BottomA);  // 1
//				Vertices.Add(BottomB);  // 2
//				Vertices.Add(TopB);     // 3
//
//				// Two triangles
//				Triangles.Append({
//					VertexIndex + 0, VertexIndex + 2, VertexIndex + 1,
//					VertexIndex + 0, VertexIndex + 3, VertexIndex + 2
//					});
//
//				for (int j = 0; j < 4; ++j)
//				{
//					Normals.Add(FVector::UpVector);
//					UVs.Add(FVector2D(0, 0));
//					VertexColors.Add(LineColor);
//					Tangents.Add(FProcMeshTangent(1, 0, 0));
//				}
//
//				VertexIndex += 4;
//			}
//
//			ProjectionMeshComponent = NewObject<UProceduralMeshComponent>(World->GetWorldSettings());
//			UProceduralMeshComponent* MeshComp = ProjectionMeshComponent;
//
//			if (!MeshComp) return;
//
//			MeshComp->RegisterComponent();
//			MeshComp->AttachToComponent(World->GetWorldSettings()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
//
//			MeshComp->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, VertexColors, Tangents, true);
//			MeshComp->SetMaterial(0, DynamicProjectionMaterial);
//			MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//		});
//
//	Tileset->SampleHeightMostDetailed(LatLongPoints, Callback);
//}




// mesh based 
//void FCircle::Draw(UWorld* World, UMaterialInterface* Material)
//{
//    if (!World || !Material) return;
//
//    ACesiumGeoreference* Georef = IShape::GetGeoreference();
//    if (!Georef) return;
//
//    if (SpawnedActor.IsValid())
//    {
//        SpawnedActor->Destroy();
//    }
//
//    // Dynamic Material for the Circle
//    DynamicMaterial = UMaterialInstanceDynamic::Create(Material, nullptr);
//    DynamicMaterial->SetVectorParameterValue(FName("BaseColor"), LineColor);
//    float InnerWidth = 0.5 - (LineWidth / 100.0f);
//    DynamicMaterial->SetScalarParameterValue(FName("Outer"), 0.5);
//    DynamicMaterial->SetScalarParameterValue(FName("Inner"), InnerWidth);
//
//    // Projection Material for the walls
//    ProjectionMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, *ProjectionMaterialPath));
//    DynamicProjectionMaterial = UMaterialInstanceDynamic::Create(ProjectionMaterial, nullptr);
//    DynamicProjectionMaterial->SetVectorParameterValue(FName("ProjectionColor"), LineColor);
//
//    // Convert radius from nautical miles to centimeters (Unreal units)
//    const float NM_TO_CM = 185200.0f;
//    const float RadiusCM = Radius * NM_TO_CM;
//
//    // Step 1: Calculate the number of segments for the circle perimeter
//    const int32 NumSegments = 60;
//    const float AngleStep = 2 * PI / NumSegments;
//
//    // Step 2: Generate the points along the circle perimeter for outer and inner radii
//    TArray<FVector> OuterCirclePoints;
//    TArray<FVector> InnerCirclePoints;
//
//    for (int32 i = 0; i < NumSegments; ++i)
//    {
//        float AngleRad = AngleStep * i;
//        float X = FMath::Cos(AngleRad);
//        float Y = FMath::Sin(AngleRad);
//
//
//        // Outer and Inner Circle Points (adjusted by radius)
//        OuterCirclePoints.Add(FVector(X * RadiusCM, Y * RadiusCM, 0));
//        InnerCirclePoints.Add(FVector(X * (RadiusCM - LineWidth), Y * (RadiusCM - LineWidth), 0)); // Inner radius
//    }
//
//    // Step 3: Transform points to world space
//    TArray<FVector> WorldOuterPoints;
//    TArray<FVector> WorldInnerPoints;
//
//    for (const FVector& Pt : OuterCirclePoints)
//    {
//        WorldOuterPoints.Add(WorldPosition + Pt);
//    }
//
//    for (const FVector& Pt : InnerCirclePoints)
//    {
//        WorldInnerPoints.Add(WorldPosition + Pt);
//    }
//
//
//    // Step 4: Create the mesh for the circle
//    TArray<FVector> Vertices;
//    TArray<int32> Triangles;
//    TArray<FVector> Normals;
//    TArray<FVector2D> UVs;
//    TArray<FLinearColor> Colors;
//    TArray<FProcMeshTangent> Tangents;
//
//    int32 VertexIndex = 0;
//
//    // Loop through the segments and create triangles between the outer and inner circle points
//    for (int32 i = 0; i < NumSegments; ++i)
//    {
//        int32 Next = (i + 1) % NumSegments;
//
//        // Outer circle vertices
//        FVector OuterA = WorldOuterPoints[i];
//        FVector OuterB = WorldOuterPoints[Next];
//
//        // Inner circle vertices
//        FVector InnerA = WorldInnerPoints[i];
//        FVector InnerB = WorldInnerPoints[Next];
//
//        // Add the vertices for the triangle
//        Vertices.Add(OuterA);  // 0
//        Vertices.Add(OuterB);  // 1
//        Vertices.Add(InnerA);  // 2
//        Vertices.Add(InnerB);  // 3
//
//        // Add the triangles (two per segment)
//        Triangles.Append({
//            VertexIndex + 0, VertexIndex + 2, VertexIndex + 1,
//            VertexIndex + 2, VertexIndex + 3, VertexIndex + 1
//            });
//
//        // Add normals, UVs, and other attributes
//        for (int32 j = 0; j < 4; ++j)
//        {
//            Normals.Add(FVector::UpVector);
//            UVs.Add(FVector2D(0, 0));  // Default UV mapping
//            Colors.Add(LineColor);      // Color
//            Tangents.Add(FProcMeshTangent(1, 0, 0));  // Tangents
//        }
//
//        VertexIndex += 4;
//    }
//
//    // Step 5: Create the Procedural Mesh Component
//    if (!CircleMeshComponent)
//    {
//        CircleMeshComponent = NewObject<UProceduralMeshComponent>(World->GetWorldSettings());
//        if (!CircleMeshComponent) return;
//
//        CircleMeshComponent->RegisterComponent();
//        CircleMeshComponent->AttachToComponent(World->GetWorldSettings()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
//    }
//    else
//    {
//        CircleMeshComponent->ClearAllMeshSections();
//    }
//
//    // Step 6: Create the mesh section for the circle
//    CircleMeshComponent->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);
//    CircleMeshComponent->SetMaterial(0, DynamicMaterial);  // Apply dynamic material to the circle
//    CircleMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//    CircleMeshComponent->SetCastShadow(false);
//    CircleMeshComponent->SetCastInsetShadow(false);
//    CircleMeshComponent->SetCastHiddenShadow(false);
//
//    // Step 7: Wall Projection (Height Adjustment based on Cesium Data)
//    FCesiumSampleHeightMostDetailedCallback Callback;
//    Callback.BindLambda([this, World, WorldOuterPoints](ACesium3DTileset* /*Tileset*/, const TArray<FCesiumSampleHeightResult>& Results, const TArray<FString>& /*Warnings*/)
//        {
//            if (Results.Num() != WorldOuterPoints.Num()) return;
//
//            TArray<FVector> Vertices;
//            TArray<int32> Triangles;
//            TArray<FVector> Normals;
//            TArray<FVector2D> UVs;
//            TArray<FLinearColor> VertexColors;
//            TArray<FProcMeshTangent> Tangents;
//
//            int32 VertexIndex = 0;
//            for (int32 i = 0; i < Results.Num(); ++i)
//            {
//                int32 Next = (i + 1) % Results.Num();
//                if (!Results[i].SampleSuccess || !Results[Next].SampleSuccess) {
//                    continue;
//                }
//                FVector TopA = WorldOuterPoints[i];
//                FVector TopB = WorldOuterPoints[Next];
//                FVector BottomA = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(Results[i].LongitudeLatitudeHeight);
//                FVector BottomB = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(Results[Next].LongitudeLatitudeHeight);
//
//                // Add quad vertices
//                Vertices.Add(TopA);     // 0
//                Vertices.Add(BottomA);  // 1
//                Vertices.Add(BottomB);  // 2
//                Vertices.Add(TopB);     // 3
//
//                Triangles.Append({
//                    VertexIndex + 0, VertexIndex + 2, VertexIndex + 1,
//                    VertexIndex + 0, VertexIndex + 3, VertexIndex + 2
//                    });
//
//                for (int j = 0; j < 4; ++j)
//                {
//                    Normals.Add(FVector::UpVector);  // Normal pointing upward
//                    UVs.Add(FVector2D(0, 0));        // Default UV Coordinates
//                    VertexColors.Add(LineColor);     // Color
//                    Tangents.Add(FProcMeshTangent(1, 0, 0));  // Tangents
//                }
//
//                VertexIndex += 4;
//            }
//
//            // Create and attach procedural mesh for walls
//            if (!WallMeshComponent)
//            {
//                WallMeshComponent = NewObject<UProceduralMeshComponent>(World->GetWorldSettings());
//                if (!WallMeshComponent) return;
//
//                WallMeshComponent->RegisterComponent();
//                WallMeshComponent->AttachToComponent(World->GetWorldSettings()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
//            }
//            else
//            {
//                WallMeshComponent->ClearAllMeshSections();
//            }
//
//            WallMeshComponent->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, VertexColors, Tangents, true);
//            WallMeshComponent->SetMaterial(0, DynamicProjectionMaterial);
//            WallMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//
//        });
//
//    // Sample height data based on world coordinates
//    TArray<FVector> WorldPoints3D;
//    for (const FVector& Pt : WorldOuterPoints)
//    {
//        FVector Point = Georeference->TransformUnrealPositionToLongitudeLatitudeHeight(Pt);
//        WorldPoints3D.Add(Point);
//    }
//
//    Tileset->SampleHeightMostDetailed(WorldPoints3D, Callback);
//}





    //Callback.BindLambda([this, World, WorldOuterPoints](ACesium3DTileset* /*Tileset*/, const TArray<FCesiumSampleHeightResult>& Results, const TArray<FString>& /*Warnings*/)
    //    {

    //        AsyncTask(ENamedThreads::GameThread, [this, World, WorldOuterPoints, Results]()
    //            {
    //                if (!DynamicProjectionMaterial) return;
    //                if (isCleared) return;

    //                if (Results.Num() != WorldOuterPoints.Num()) return;

    //                TArray<FVector> Vertices;
    //                TArray<int32> Triangles;
    //                TArray<FVector> Normals;
    //                TArray<FVector2D> UVs;
    //                TArray<FLinearColor> VertexColors;
    //                TArray<FProcMeshTangent> Tangents;

    //                int32 VertexIndex = 0;
    //                for (int32 i = 0; i < Results.Num(); ++i)
    //                {
    //                    int32 Next = (i + 1) % Results.Num();
    //                    if (!Results[i].SampleSuccess || !Results[Next].SampleSuccess) {
    //                        continue;
    //                    }
    //                    FVector TopA = WorldOuterPoints[i];
    //                    FVector TopB = WorldOuterPoints[Next];
    //                    FVector BottomA = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(Results[i].LongitudeLatitudeHeight);
    //                    FVector BottomB = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(Results[Next].LongitudeLatitudeHeight);

    //                    // Add quad vertices
    //                    Vertices.Add(TopA);     // 0
    //                    Vertices.Add(BottomA);  // 1
    //                    Vertices.Add(BottomB);  // 2
    //                    Vertices.Add(TopB);     // 3

    //                    Triangles.Append({
    //                        VertexIndex + 0, VertexIndex + 2, VertexIndex + 1,
    //                        VertexIndex + 0, VertexIndex + 3, VertexIndex + 2
    //                        });

    //                    for (int j = 0; j < 4; ++j)
    //                    {
    //                        Normals.Add(FVector::UpVector);  // Normal pointing upward
    //                        UVs.Add(FVector2D(0, 0));        // Default UV Coordinates
    //                        VertexColors.Add(LineColor);     // Color
    //                        Tangents.Add(FProcMeshTangent(1, 0, 0));  // Tangents
    //                    }

    //                    VertexIndex += 4;
    //                }

    //                // Create and attach procedural mesh for walls
    //                if (!WallMeshComponent)
    //                {
    //                    WallMeshComponent = NewObject<UProceduralMeshComponent>(World->GetWorldSettings());
    //                    if (!WallMeshComponent) return;

    //                    WallMeshComponent->RegisterComponent();
    //                    WallMeshComponent->AttachToComponent(World->GetWorldSettings()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
    //                }
    //                else
    //                {
    //                    WallMeshComponent->ClearAllMeshSections();
    //                }
    //                if (WallMeshComponent) {
    //                    WallMeshComponent->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, VertexColors, Tangents, true);
    //                    if (DynamicProjectionMaterial) {
    //                        WallMeshComponent->SetMaterial(0, DynamicProjectionMaterial);
    //                    }
    //                    WallMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    //                }
    //                
    //            });
    //       
    //    });

