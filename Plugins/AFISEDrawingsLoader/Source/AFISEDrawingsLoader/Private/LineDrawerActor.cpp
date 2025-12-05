// Fill out your copyright notice in the Description page of Project Settings.

#include "LineDrawerActor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"                 
#include "Materials/MaterialInterface.h"       
#include "Materials/MaterialInstanceDynamic.h" 


ALineDrawerActor::ALineDrawerActor()
{
	PrimaryActorTick.bCanEverTick = true;
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	RootComponent = SplineComponent;
}

void ALineDrawerActor::BeginPlay()
{
	Super::BeginPlay();
}

void ALineDrawerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
// using spline mesh component:

//void ALineDrawerActor::UpdateLine(const TArray<FVector>& Points, UMaterialInterface* Material)
//{
//	for (USplineMeshComponent* SplineMesh : SplineMeshComponents)
//	{
//		if (SplineMesh)
//		{
//			SplineMesh->DestroyComponent();
//		}
//	}
//	SplineMeshComponents.Empty();
//
//	SplineComponent->ClearSplinePoints();
//	for (int32 i = 0; i < Points.Num(); ++i)
//	{
//		SplineComponent->AddSplinePoint(Points[i], ESplineCoordinateSpace::World);
//		SplineComponent->SetTangentAtSplinePoint(i, FVector::ZeroVector, ESplineCoordinateSpace::World);
//	}
//	CreateSplineMeshes(Material);
//}

// Using procedural mesh

void ALineDrawerActor::UpdateLine(const TArray<FVector>& Points, UMaterialInterface* Material)
{
	if (Points.Num() < 2) return;

	if (ProceduralMesh)
	{
		ProceduralMesh->DestroyComponent();
		ProceduralMesh = nullptr;
	}

	ProceduralMesh = NewObject<UProceduralMeshComponent>(this);
	ProceduralMesh->RegisterComponent();
	SetRootComponent(ProceduralMesh);

	const float HalfThickness = 100000.0f;

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FProcMeshTangent> Tangents;
	TArray<FLinearColor> Colors;

	TArray<FVector> OffsetPointsUp;
	TArray<FVector> OffsetPointsDown;

	// Step 1: Generate mitered offset direction per point
	for (int32 i = 0; i < Points.Num(); ++i)
	{
		FVector Prev = i > 0 ? Points[i - 1] : Points[i];
		FVector Next = i < Points.Num() - 1 ? Points[i + 1] : Points[i];

		FVector DirA = (Points[i] - Prev).GetSafeNormal();
		FVector DirB = (Next - Points[i]).GetSafeNormal();

		FVector AvgDir = (DirA + DirB).GetSafeNormal();

		// Use cross with Z to find lateral (right) vector
		FVector Right = FVector::CrossProduct(AvgDir, FVector::UpVector).GetSafeNormal();

		OffsetPointsUp.Add(Points[i] + Right * HalfThickness);
		OffsetPointsDown.Add(Points[i] - Right * HalfThickness);
	}

	// Step 2: Create quads using mitered edges
	int32 VertexIndex = 0;
	for (int32 i = 0; i < Points.Num() - 1; ++i)
	{
		FVector V0 = OffsetPointsUp[i];
		FVector V1 = OffsetPointsDown[i];
		FVector V2 = OffsetPointsUp[i + 1];
		FVector V3 = OffsetPointsDown[i + 1];

		Vertices.Add(V0);
		Vertices.Add(V1);
		Vertices.Add(V2);
		Vertices.Add(V3);

		Triangles.Add(VertexIndex + 0);
		Triangles.Add(VertexIndex + 2);
		Triangles.Add(VertexIndex + 1);
		Triangles.Add(VertexIndex + 2);
		Triangles.Add(VertexIndex + 3);
		Triangles.Add(VertexIndex + 1);

		for (int j = 0; j < 4; ++j)
		{
			Normals.Add(FVector::UpVector);
			UVs.Add(FVector2D(0, 0));
			Colors.Add(FLinearColor::White);
			Tangents.Add(FProcMeshTangent(1, 0, 0));
		}

		VertexIndex += 4;
	}

	ProceduralMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);
	ProceduralMesh->SetMaterial(0, Material);
	ProceduralMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}



void ALineDrawerActor::CreateSplineMeshes(UMaterialInterface* Material)
{
    for (int32 i = 0; i < SplineComponent->GetNumberOfSplinePoints() - 1; i++)
    {
        USplineMeshComponent* SplineMeshComp = NewObject<USplineMeshComponent>(this);
        SplineMeshComp->RegisterComponent();
		// "/Engine/VREditor/BasicMeshes/SM_Cube_01.SM_Cube_01"
        SplineMeshComp->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/VREditor/BasicMeshes/SM_Cube_01.SM_Cube_01")));

        SplineMeshComp->SetMaterial(0, Material); // Apply material to mesh

        FVector Start = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
        FVector End = SplineComponent->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::World);

        // Get the tangent vectors for smooth transition
        FVector StartTangent = SplineComponent->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::World);
        FVector EndTangent = SplineComponent->GetTangentAtSplinePoint(i + 1, ESplineCoordinateSpace::World);

        // Set the start and end positions for the spline mesh, and their tangents
        SplineMeshComp->SetStartAndEnd(Start, StartTangent, End, EndTangent);

        // Set the scale to make the line thick (ensure uniform scaling)
        float ScaleFactor = 1000.0f; // You can adjust this scale factor as needed
        FVector2D StartScale = FVector2D(ScaleFactor, ScaleFactor);  // Line thickness for start
        FVector2D EndScale = FVector2D(ScaleFactor, ScaleFactor);    // Line thickness for end


        // Set the scale for the spline mesh at both ends
        SplineMeshComp->SetStartScale(StartScale + 1000.0f);
        SplineMeshComp->SetEndScale(EndScale + 1000.0f);

        // Set collision and other properties
        SplineMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        SplineMeshComp->SetCastShadow(false);  // Optional: Disable shadow if not needed

        // Store the spline mesh component
        SplineMeshComponents.Add(SplineMeshComp);

		//SpawnSphereAtLocation(GetWorld(), Start); // Spawn sphere at the start of each segment
		//if (i == SplineComponent->GetNumberOfSplinePoints() - 2) // Avoid duplicating the last point
		//{
		//	SpawnSphereAtLocation(GetWorld(), End); // Spawn sphere at the last point
		//}

    }
}

void ALineDrawerActor::SpawnSphereAtLocation(UWorld* World, const FVector& Location)
{
	AStaticMeshActor* SphereActor = World->SpawnActor<AStaticMeshActor>(Location, FRotator::ZeroRotator);
	if (!SphereActor) return;

	UStaticMesh* SphereMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (!SphereMesh) return;

	UMaterialInterface* SphereMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/Drawings/M_SphereMaterial"));

	UStaticMeshComponent* MeshComp = SphereActor->GetStaticMeshComponent();
	MeshComp->SetStaticMesh(SphereMesh);
	MeshComp->SetMaterial(0, SphereMaterial);

	MeshComp->SetWorldScale3D(FVector(5000.00f, 5000.00f, 5000.00f));

	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereActor->SetMobility(EComponentMobility::Movable);
}





