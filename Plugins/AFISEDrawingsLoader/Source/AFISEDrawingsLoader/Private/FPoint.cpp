#include "FPoint.h"


FPoint::FPoint(const FVector& InWorldPos, const FVector& InLatLongHeight)
    : WorldPosition(InWorldPos), LatLongHeight(InLatLongHeight), Scale(1)
{

    TArray<FVector> LatLongPoints = { FVector(LatLongHeight.X, LatLongHeight.Y,500) };
    //WorldPosition = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(FVector(LatLongHeight.X, LatLongHeight.Y, MaxHeight));

   // WorldPosition = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(FVector(LatLongHeight.X, LatLongHeight.Y, 10000));
    MaterialPath = "/Game/Materials/Drawings/M_Point";
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

FString FPoint::GetShapeType() const { return TEXT("Point"); }
FVector FPoint::GetWorldPosition() const { return WorldPosition; }
FVector FPoint::GetLatLongHeightPosition() const { return LatLongHeight; }

void FPoint::SetScale(int32 InScale) { Scale = InScale * BaseLineWidth / 100.0f; }

void FPoint::UpdateScale(UWorld* World) {


}
void FPoint::LogInfo() const
{

}

void FPoint::Clear()
{
    if (SpawnedActor.IsValid())
    {
        SpawnedActor->Destroy();
        SpawnedActor = nullptr;
    }
    if (WallMeshComponent)
    {
        WallMeshComponent->DestroyComponent();
        WallMeshComponent = nullptr;
    }

}

void FPoint::CreateMeshes(UWorld* World) {

    DynamicMaterial = UMaterialInstanceDynamic::Create(Material, nullptr);
    //  DynamicMaterial->SetVectorParameterValue(FName("BaseColor"), LineColor);


    if (!SpawnedActor.IsValid())
    {
        // Spawn a sphere actor at the specified world position
        AStaticMeshActor* SphereActor = World->SpawnActor<AStaticMeshActor>(WorldPosition, FRotator::ZeroRotator);
        if (SphereActor)
        {
            // Set the mesh for the sphere actor
           // UStaticMesh* SphereMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Sphere.Sphere"));

            UStaticMesh* SphereMesh = LoadObject<UStaticMesh>(nullptr, *PointToMeshType(pointType));

            if (SphereMesh)
            {
                // Apply the sphere mesh and material
                SphereActor->SetMobility(EComponentMobility::Movable);

                UStaticMeshComponent* MeshComp = SphereActor->GetStaticMeshComponent();
                MeshComp->CreationMethod = EComponentCreationMethod::Instance;
                MeshComp->SetStaticMesh(SphereMesh);
                MeshComp->SetMaterial(0, DynamicMaterial);
                MeshComp->SetWorldScale3D(FVector(Scale, Scale, Scale));
                MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
                MeshComp->SetCastShadow(false);
                MeshComp->RegisterComponent();
                SpawnedActor = SphereActor;
            }
        }
    }
    else
    {
        SpawnedActor->SetActorLocation(WorldPosition);
    }


    TArray<FVector> LatLongPoints3d;
    //LatLongPoints3d.Add(FVector(LatLong.X, LatLong.Y, 0));  

    const float Offset = Scale;

    FVector TopRight = WorldPosition + FVector(Offset, Offset, 0);
    FVector TopLeft = WorldPosition + FVector(-Offset, Offset, 0);
    FVector BottomRight = WorldPosition + FVector(Offset, -Offset, 0);
    FVector BottomLeft = WorldPosition + FVector(-Offset, -Offset, 0);

    WorldProjectionPoints.Add(TopRight);
    WorldProjectionPoints.Add(TopLeft);
    WorldProjectionPoints.Add(BottomRight);
    WorldProjectionPoints.Add(BottomLeft);


    for (int32 i = 0; i < WorldProjectionPoints.Num(); i++) {
        FVector LatLongPosition = Georeference->TransformUnrealPositionToLongitudeLatitudeHeight(WorldProjectionPoints[i]);
        LatLongPoints3d.Add(FVector(LatLongPosition.X, LatLongPosition.Y, 0));
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

                FVector TopA = WorldProjectionPoints[i];
                FVector TopB = WorldProjectionPoints[i + 1];
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
                    // Colors.Add(LineColor);
                    Tangents.Add(FProcMeshTangent(1, 0, 0));
                }

                VertexIndex += 4;
            }

            WallMeshComponent->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);

        });


    Tileset->SampleHeightMostDetailed(LatLongPoints3d, CesiumCallback);

}

void FPoint::Draw(UWorld* World)
{
    if (WorldPosition.IsZero()) {
        TArray<FVector> LatLongPoints = { FVector(LatLongHeight.X, LatLongHeight.Y, LatLongHeight.Z) };
        SampleHeightAboveTerrain(LatLongPoints,
            [this, World]( TArray<FVector>& SampledWorldPoints , TArray<FVector> SampleWorldProjectionPoints)
            {
                WorldPosition = SampledWorldPoints[0];
                CreateMeshes(World);
            });
    }
    else {
        CreateMeshes(World);
    }

}

void FPoint::SetProjectionVisibility(bool bVisible)
{
    if (WallMeshComponent)
    {
        WallMeshComponent->SetVisibility(bVisible, true);
        WallMeshComponent->SetHiddenInGame(!bVisible);
    }
}

void FPoint::SetVisibility(bool bVisible)
{
    if (WallMeshComponent)
    {
        WallMeshComponent->SetVisibility(bVisible, true);
        WallMeshComponent->SetHiddenInGame(!bVisible);
    }

    UStaticMeshComponent* MeshComp = SpawnedActor->FindComponentByClass<UStaticMeshComponent>();
    if (MeshComp)
    {
        MeshComp->SetVisibility(bVisible);
    }
}



void FPoint::SetPointType(PointType type) {
    pointType = type;
}

PointType FPoint::GetPointType() {
    return pointType;
}
