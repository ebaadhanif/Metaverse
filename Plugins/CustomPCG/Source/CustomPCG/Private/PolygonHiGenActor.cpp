#include "PolygonHiGenActor.h"
#include "PCGGraph.h"
#include "Engine/World.h"
#include "RuntimeGen/SchedulingPolicies/PCGSchedulingPolicyDistanceAndDirection.h"


APolygonHiGenActor::APolygonHiGenActor()
{
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
	// BoxComponent->SetBoxExtent(FVector(20000.f, 20000.f, 200.f));
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BoxComponent->SetHiddenInGame(true);
	BoxComponent->SetVisibility(true, true);
	BoxComponent->bDrawOnlyIfSelected = false;

	BoxComponent->SetCanEverAffectNavigation(false);
	PCGComponent = CreateDefaultSubobject<UPCGComponent>(TEXT("PCGComponent"));

	PCGComponent->bActivated = true;
	PCGComponent->SetIsPartitioned(true);
	PCGComponent->GenerationTrigger = EPCGComponentGenerationTrigger::GenerateAtRuntime;
	TSubclassOf<UPCGSchedulingPolicyBase> PolicyClass = UPCGSchedulingPolicyDistanceAndDirection::StaticClass();
	PCGComponent->SetSchedulingPolicyClass(PolicyClass);
	PCGComponent->bOverrideGenerationRadii = true;
	FPCGRuntimeGenerationRadii bGenerationRadius;
	bGenerationRadius.GenerationRadius = 1024.0f;
	bGenerationRadius.GenerationRadius25600 = 1024.0f;
	bGenerationRadius.CleanupRadiusMultiplier = 1.1f;
	PCGComponent->GenerationRadii = bGenerationRadius;
}

void APolygonHiGenActor::AssignHiGenGraph()
{
	if (GraphName.IsEmpty() || !PCGComponent) return;

	BoxComponent->SetBoxExtent(BoxExtents);

	const FString GraphFolderPath = TEXT("/Game/PCGData/PolygonDataAssets/HiGen");
	FString AssetName = FString::Printf(TEXT("PolygonData_%s"), *GraphName);
	FString AssetPath = FString::Printf(TEXT("%s/%s.%s"), *GraphFolderPath, *AssetName, *AssetName);
	UPCGGraph* Graph = Cast<UPCGGraph>(StaticLoadObject(UPCGGraph::StaticClass(), nullptr, *AssetPath));
	if (!Graph)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load HiGen Graph: %s"), *GraphName);
		return;
	}
	PCGComponent->SetGraph(Graph);
	// DrawDebugBox(GetWorld(), BoxComponent->GetComponentLocation(), BoxComponent->GetScaledBoxExtent(), FColor::Red, true, -1.0f, 0, 50.0f);
}

void APolygonHiGenActor::CachePCGGeneratedComponents() {
	for (UActorComponent* Comp : GetComponents())
	{
		if (auto* HISMC = Cast<UHierarchicalInstancedStaticMeshComponent>(Comp)) {
			CachedHISM.Add(HISMC);
		}
		else if (auto* ISMC = Cast<UInstancedStaticMeshComponent>(Comp)) {
			CachedHISM.Add(ISMC);
		}
	}

}


void APolygonHiGenActor::ToggleVisibility(bool bVisible) {
	//for (auto& Component : CachedHISM)
	//{
	//    Component->SetVisibility(bVisible, true);
	//    Component->SetHiddenInGame(!bVisible);
	//}

	//PCGComponent->CleanupLocal(true, false);
	//PCGComponent->Deactivate();
	//PCGComponent->Cleanup();
	//PCGComponent->bActivated = false;
	//SetActorHiddenInGame(true);
}

void APolygonHiGenActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PCGComponent->IsRegistered()) {
		PCGComponent->Cleanup();
		PCGComponent->UnregisterComponent();
	}
	Super::EndPlay(EndPlayReason);
}
