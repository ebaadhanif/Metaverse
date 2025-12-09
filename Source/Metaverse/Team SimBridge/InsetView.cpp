// Fill out your copyright notice in the Description page of Project Settings.


#include "InsetView.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AInsetView::AInsetView()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Index = 1000; 
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetBPClass(TEXT("/Game/Gadgets/InsetView/WBP_InsetView"));
	if (WidgetBPClass.Succeeded())
	{
		InsetViewClass = WidgetBPClass.Class;
	}
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetWidgetSpace(EWidgetSpace::World);

}

// Called when the game starts or when spawned
void AInsetView::BeginPlay()
{
	Super::BeginPlay();

	CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	CameraLocation = CameraManager->GetCameraLocation();

	//CameraLocation.Y += 500;
	
	WidgetComponent->RegisterComponent();
	AddInstanceComponent(WidgetComponent);
   	WidgetComponent->SetWidgetClass(InsetViewClass);
	WidgetComponent->SetDrawSize(FVector2D(1920,1080));
	//SetActorLocation(CameraManager->GetCameraLocation());
	//WidgetComponent->SetRelativeLocation(FVector(-2000,0,0));

	//WidgetComponent->SetWorldRotation(LookAtRotation);
}

// Called every frame
void AInsetView::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

