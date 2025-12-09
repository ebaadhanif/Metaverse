// Fill out your copyright notice in the Description page of Project Settings.


#include "InsetViewManager.h"
#include "GameFramework/Actor.h"
#include <Kismet/GameplayStatics.h>
#include "CesiumCameraManager.h"
#include "Components/SceneCaptureComponent2D.h"
#include <AKeyboardInputHandler.h>
//#include <Kismet/GameplayStatics.h>

// Sets default values
AInsetViewManager::AInsetViewManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraDistance = 4000;
	
}

// Called when the game starts or when spawned
void AInsetViewManager::BeginPlay()
{
	Super::BeginPlay();

	CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	ACesiumCameraManager* CesiumCameraManager = Cast<ACesiumCameraManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACesiumCameraManager::StaticClass()));
	TSubclassOf<AActor> RenderTargetClass = LoadClass<AActor>(nullptr, TEXT("/Game/Blueprints/BP_InsetViewRenderTarget.BP_InsetViewRenderTarget_C"));
	FVector CameraLocation = CameraManager->GetCameraLocation();

	if (RenderTargetClass) {
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), RenderTargetClass, FoundActors);
		if (FoundActors.Num() > 0) {
			USceneCaptureComponent2D* RenderTargetComponent = FoundActors[0]->FindComponentByClass<USceneCaptureComponent2D>();
			FCesiumCamera CesiumCamera;
			CesiumCamera.Location = FoundActors[0]->GetActorLocation();
			CesiumCamera.Rotation = FoundActors[0]->GetActorRotation();
			CesiumCamera.FieldOfViewDegrees = RenderTargetComponent->FOVAngle;
			CesiumCameraManager->AddCamera(CesiumCamera);
		}
	}


	//if (InsetViewParentActor && !InsetViewParentActor->GetRootComponent()) {
	//	InsetViewParentActor->SetActorLabel(TEXT("ParentActor"));
		
		InsetViewParentActor = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), FVector(0), FRotator(0));
#if WITH_EDITOR
		InsetViewParentActor->SetActorLabel(TEXT("InsetViews"));
#endif
		USceneComponent* Root = NewObject<USceneComponent>(InsetViewParentActor);
		Root->RegisterComponent();
		InsetViewParentActor->SetRootComponent(Root);
		FVector SpawnLocation = CameraManager->GetCameraLocation() ;
		FVector NewLocation = CameraLocation - SpawnLocation;
		FRotator LookAtRotation = FRotationMatrix::MakeFromX(NewLocation).Rotator();
		LookAtRotation.Pitch = 0;
		InsetViewParentActor->SetActorRotation(LookAtRotation);
		InsetViewParentActor->SetActorLocation(CameraLocation);
//	}
}

int AInsetViewManager::GetNextViewIndex()
{
	int lastViewIndex = InsetViewList[InsetViewList.Num() - 1]->GetIndex();
	int newViewIndex = 1000;
	if (lastViewIndex == 0) {
		newViewIndex = 1;
	}
	else if (lastViewIndex > 0) {
		newViewIndex = lastViewIndex * -1;
	}
	else
	{
		newViewIndex = lastViewIndex * -1;
		newViewIndex++;
	}
	return newViewIndex;
}

void AInsetViewManager::SetInsetViewPivot(AInsetView* insetVIew)
{
	double Y=0, Z=0;

	if (insetVIew->GetIndex() >=0) {
		Z = 1080 / 2;
		Y = (1920 / 2) * -1;
	}
	else
	{
		Z = 1080 / 2;
		Y = 1920 / 2;
	}

	insetVIew->WidgetComponent->SetRelativeLocation(FVector(0, Y, Z));
}

void AInsetViewManager::SetInsetViewPosition(AInsetView* insetVIew)
{
	
	if (insetVIew->GetIndex() > 2 || insetVIew->GetIndex() < -2) {

	}

	if (insetVIew->GetIndex()==0) {
		FVector SpawnLocation = CameraManager->GetCameraLocation() + CameraManager->GetCameraRotation().Vector() * CameraDistance;
		SpawnLocation.Y -= 1920 / 2;
		SpawnLocation.Z -= 1080 / 2;
		insetVIew->SetActorLocation(SpawnLocation);

	}

	else
	{
		for (int i = InsetViewList.Num()-2; i >= 0; i--) //-2 so to ommit oneself
		{
			
			if (insetVIew->GetIndex() > 0) {
				if (InsetViewList[i]->GetIndex() >= 0 && InsetViewList[i]->GetIndex() <2 ) { //for right side views
					FVector PreviousLocation = InsetViewList[i]->GetActorLocation();
					FVector RightVector = FVector(0,1,0);
					FVector RotatedRightVector = InsetViewList[i]->GetActorRotation().RotateVector(RightVector);
					FVector NewLocation = PreviousLocation + (RotatedRightVector * (- 1930.0f));
					insetVIew->SetActorLocation(NewLocation);
					FRotator NewRotation = InsetViewList[i]->GetActorRotation();
					NewRotation.Yaw += RightSideAngle;
					RightSideAngle += 30;
					insetVIew->SetActorRotation(NewRotation);
				
					
					return;
				}
				if (InsetViewList[i]->GetIndex() == 2) {
					FVector PreviousLocation = InsetViewList[0]->GetActorLocation()+FVector(0,0,1090);
					insetVIew->SetActorLocation(PreviousLocation);
					insetVIew->SetActorRotation(InsetViewList[0]->GetActorRotation());
					RightSideAngle = 30;
					LeftSideAngle = -30;
					return;
				}
				if (InsetViewList[i]->GetIndex()  > 2) {
					FVector PreviousLocation = InsetViewList[i]->GetActorLocation();
					insetVIew->SetActorLocation(PreviousLocation);
					FVector RightVector = FVector(0, 1, 0);
					FVector RotatedRightVector = InsetViewList[i]->GetActorRotation().RotateVector(RightVector);
					FVector NewLocation = PreviousLocation + (RotatedRightVector * (-1930.0f));
					insetVIew->SetActorLocation(NewLocation);
					FRotator NewRotation = InsetViewList[i]->GetActorRotation();
					NewRotation.Yaw += RightSideAngle;
					RightSideAngle += 30;
					insetVIew->SetActorRotation(NewRotation);
					return;

				}

			}
			
			else
			{
				if (InsetViewList[i]->GetIndex() <= 0) { //for left side views
					if (insetVIew->GetIndex() == -1) {
						insetVIew->SetActorLocation(InsetViewList[i]->GetActorLocation() +FVector(0,-10,0));
						FRotator NewRotation = InsetViewList[i]->GetActorRotation();
						NewRotation.Yaw += LeftSideAngle;
						LeftSideAngle -= 30;
						insetVIew->SetActorRotation(NewRotation);
						return;
					}
					if (insetVIew->GetIndex() < -1 && insetVIew->GetIndex() > -3) {
						FVector PreviousLocation = InsetViewList[i]->GetActorLocation();
						FVector LeftVector = FVector(0, -1, 0);
						FVector RotatedLeftVector = InsetViewList[i]->GetActorRotation().RotateVector(LeftVector);
						FVector NewLocation = PreviousLocation + (RotatedLeftVector * (-1930.0f));
						insetVIew->SetActorLocation(NewLocation);
						FRotator NewRotation = InsetViewList[i]->GetActorRotation();
						NewRotation.Yaw += LeftSideAngle;
						LeftSideAngle -= 30;
						insetVIew->SetActorRotation(NewRotation);
						return;
					}
					if (insetVIew->GetIndex() == -3)
					{
						insetVIew->SetActorLocation(InsetViewList[5]->GetActorLocation() + FVector(0, -10, 0));
						FRotator NewRotation = InsetViewList[5]->GetActorRotation();
						NewRotation.Yaw += LeftSideAngle;
						LeftSideAngle -= 30;
						insetVIew->SetActorRotation(NewRotation);
						return;
					}
					if (insetVIew->GetIndex() < -3)
					{
					FVector PreviousLocation = InsetViewList[i]->GetActorLocation();
						FVector LeftVector = FVector(0, -1, 0);
						FVector RotatedLeftVector = InsetViewList[i]->GetActorRotation().RotateVector(LeftVector);
						FVector NewLocation = PreviousLocation + (RotatedLeftVector * (-1930.0f));
						insetVIew->SetActorLocation(NewLocation);
						FRotator NewRotation = InsetViewList[i]->GetActorRotation();
						NewRotation.Yaw += LeftSideAngle;
						LeftSideAngle -= 30;
						insetVIew->SetActorRotation(NewRotation);
						return;
					
					
				    }

				}
				
			}
		}
	}
}

// Called every frame
void AInsetViewManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	InsetViewFaceCamera();
}

void AInsetViewManager::SpawnInsetView()
{
	if (!CameraManager) return;
	
	FVector CameraLocation = CameraManager->GetCameraLocation();
	FRotator CameraRotation = CameraManager->GetCameraRotation();
	FVector SpawnLocation = CameraManager->GetCameraLocation() + CameraManager->GetCameraRotation().Vector() * CameraDistance;
	AInsetView* InsetViewActor = nullptr;
	
	float SideOffset = 100;
	//InsetViewParentActor =  GetWorld()->SpawnActor<AActor>(AActor::StaticClass, FVector(0), FRotator(0));
	if (InsetViewList.Num() < 11) //spawn to fix length 
	{
		
		InsetViewActor = GetWorld()->SpawnActor<AInsetView>(AInsetView::StaticClass(), FVector(0), FRotator(0));

	}
	//}
	//else {
	//	return;
	//
	//}

	if (InsetViewActor) {
		if (InsetViewList.Num() > 0) {
			InsetViewActor->SetIndex(GetNextViewIndex());
		}
		else
		{
			InsetViewActor->SetIndex(0);
		}
		SetInsetViewPivot(InsetViewActor);
		InsetViewList.Add(InsetViewActor);

		if (InsetViewActor->GetIndex()==0) {
			
			FVector NewLocation = CameraLocation - SpawnLocation;
			FRotator LookAtRotation = FRotationMatrix::MakeFromX(NewLocation).Rotator();
			LookAtRotation.Pitch = 0;
			InsetViewActor->SetActorRotation(LookAtRotation);
		}
		InsetViewActor->AttachToActor(InsetViewParentActor, FAttachmentTransformRules::KeepWorldTransform);
		SetInsetViewPosition(InsetViewActor);
	}
//	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, FString::Printf(TEXT("Desired Height: %d"), DesiredHeightRange));
	//PositionCircularInsetView(InsetViewActor, SpawnLocation);
}
//void AInsetViewManager::SetMil2525Height()
//{
//	//	DesiredHeightRange = FMath::Clamp(DesiredHeightRange, 1, 4000);
//		//if (DesiredHeightRange<=4000) {
//
//	DesiredHeightRange = 500;
//	//}
//	//else 
//	//{
//	//	DesiredHeightRange = 4000;
//
//	//}
//	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, FString::Printf(TEXT("Desired Height: %d"), DesiredHeightRange));
//}
void AInsetViewManager::InsetViewFaceCamera()
{
	if (!CameraManager) return;

	FVector CameraLocation = CameraManager->GetCameraLocation();
	FRotator CameraRotation = CameraManager->GetCameraRotation();
	FVector SpawnLocation = CameraManager->GetCameraLocation() + CameraManager->GetCameraRotation().Vector() * 2000;

	
		if (InsetViewParentActor) {
			FVector Location = InsetViewParentActor->GetActorLocation();
			FVector NewLocation = CameraLocation - Location;
			/*FVector Pivot =*/

		/*	float pivotY = 540.0f;
			float pivotX = 960.0f;*/

			FRotator LookAtRotation = FRotationMatrix::MakeFromX(CameraLocation).Rotator();

			// InsetViewParentActor->SetActorRotation(LookAtRotation);
			InsetViewParentActor->SetActorLocation(CameraLocation);
		}
	

}
void AInsetViewManager::DeleteInsetView(int Index ) 
{
	Index = 0;

	FVector TempLocation = InsetViewList[Index]->GetActorLocation();
	FRotator TempRotation = InsetViewList[Index]->GetActorRotation();
	if (!InsetViewList.IsValidIndex(Index)) return;
	AActor* ActorToRemove = InsetViewList[Index];

	if (ActorToRemove) 
	{ 
		ActorToRemove->Destroy();
	}

	InsetViewList.RemoveAt(Index);
	
//	TArray<AInsetView*> ReversedArray;

	/*for (int i=InsetViewList.Num()-2; i>=0; i--) 
	{
	


		ReversedArray.Add(InsetViewList[i]);
	    
	}
	InsetViewList = ReversedArray;*/

	//for (AInsetView* insetView : InsetViewList) {
	//	if (insetView) {
	//	
	//		if (insetView->GetIndex() == 0) {
	//			InsetViewList.Add(InsetViewList[1]);
	//			FVector NewLocation = CameraLocation - SpawnLocation;
	//			FRotator LookAtRotation = FRotationMatrix::MakeFromX(NewLocation).Rotator();
	//			LookAtRotation.Pitch = 0;
	//			insetView->SetActorRotation(LookAtRotation);
	//			SetInsetViewPosition(insetView);
	//		}

	//		
	//	}
	//}

	for (AInsetView* insetView : InsetViewList) {
		if (insetView) {
		
			/*if (InsetViewList.Num() > 0) {
				insetView->SetIndex(GetNextViewIndex());
			}
			else
			{
				insetView->SetIndex(0);
			}
			SetInsetViewPivot(insetView);
			if (insetView->GetIndex() == 0) {

				
				FRotator LookAtRotation = FRotationMatrix::MakeFromX(TempLocation).Rotator();
				LookAtRotation.Pitch = 0;
				insetView->SetActorRotation(LookAtRotation);
			}*/
			SetInsetViewPosition(insetView);
			

			
		}
	}







	//SetInsetViewPosition(InsetViewList[1]);
	//for (int i = 0; i < InsetViewList.Num()-1; i++) {

	//	if (InsetViewList[i] && InsetViewList[i+1]) {
	//	
	//		
	//		InsetViewList[i]->SetActorLocation(i == 0 ? TempLocation : InsetViewList[i - 1]->GetActorLocation());
	//		InsetViewList[i]->SetActorRotation(i == 0 ? TempRotation : InsetViewList[i - 1]->GetActorRotation());
	//		/*if (InsetViewList.Num() > 0) {
	//			InsetViewList[i]->SetIndex(GetNextViewIndex());
	//		}
	//		else
	//		{
	//			InsetViewList[i]->SetIndex(0);
	//		}*/
	//		SetInsetViewPivot(InsetViewList[i]);
	//	}



	//	//if (i > Index && (Index+1)<= InsetViewList.Num())
	//	//{
	//	//	int next = i + 1;
	//	//	InsetViewList[next]->SetActorLocation(TempLocation);
	//	//	
	//
	//
	//	//	//InsetViewList[i] =
	//	//	//InsetViewList[Index + 1]->SetActorLocation(TempLocation);
	//	//	TempLocation = InsetViewList[i]->GetActorLocation();
	//	//}
	//}

	
}






void AInsetViewManager::PositionInsetView(AInsetView* InsetViewActor)
{
	if (!FirstTime) {
		FirstTime = true;

		return;
	}
	else
	{


		FRotator CameraRotation = CameraManager->GetCameraRotation();
		FVector CameraLocation = CameraManager->GetCameraLocation();
		FVector RightVector = FRotationMatrix(CameraRotation).GetUnitAxis(EAxis::Y);

		float HorizentalSpacing = 1550.0f;
		FVector SideOffset = FVector(0);



		int32 OffsetIndex = 0;
		for (int i = 1; i < InsetViewList.Num(); i++)
		{
			int32 step = (i + 1) / 2;
			int32 direction = (i % 2 == 0) ? 1 : -1;


			OffsetIndex = direction * step;
			SideOffset = RightVector * OffsetIndex * HorizentalSpacing;


		}
		/*for (AInsetView* insetView : InsetViewList) {
			if (insetView) {*/
		FVector Location = InsetViewActor->GetActorLocation();
		FVector NewLocation = Location + SideOffset;

		//FRotator LookAtRotation = FRotationMatrix::MakeFromX(NewLocation).Rotator();

		InsetViewActor->SetActorLocation(NewLocation);

		//	}
		//}
	}

}

void AInsetViewManager::PositionCircularInsetView(AInsetView* InsetViewActor, FVector SpawnLoc)
{

	float stepAngle = 30;
	float ForwardStep = 100.0;

	FVector Forward = (CameraManager->GetCameraRotation()).Vector();
	FVector Up = FVector::UpVector;
	FVector NewLoc = InsetViewActor->GetActorLocation();

	if (!FirstTime1) {
		FirstTime1 = true;

		return;
	}
	else
	{


		//	FRotator CameraRotation = CameraManager->GetCameraRotation();
		FVector CameraLocation = CameraManager->GetCameraLocation();
		//	FVector RightVector = FRotationMatrix(CameraRotation).GetUnitAxis(EAxis::Y);
		float HorizentalSpacing = 2000.0f;
		FVector SideOffset = FVector(0);
		FRotator NewRotation= FRotator(0,0,0);
		FRotator PrevRot = InsetViewActor->GetActorRotation();
		FVector PrevLoc = InsetViewActor->GetActorLocation();
		//NewLoc = InsetViewActor->GetActorLocation();
		int32 OffsetIndex = 960;
		//NewLoc.Y += 960;
		for (int i = 1; i < InsetViewList.Num(); i++)
		{

			int32 step = (i + 1) / 2;
			int32 direction = (i % 2 == 0) ? -1 : 1;
			InsetViewActor->WidgetComponent->SetRelativeLocation(FVector(0, (960 * direction), 540));
			NewLoc.Y = SpawnLoc.Y + (1920 * direction * step);//* FVector(0, 6000 * direction, 0);

			stepAngle = direction * stepAngle;

			if (i > 2 && i % 2 != 0) {
				ForwardStep = ForwardStep;
				stepAngle = stepAngle * 2;

			}

			//SideOffset = RightVector * OffsetIndex * HorizentalSpacing;
			/*float Angle = step *SideOffset */
		//RotateDir = Forward.RotateAngleAxis(stepAngle,Up);
		}


		NewLoc.Y -= 960;
		NewLoc.Z -= 540;



		//	NewRotation = PrevRot + FRotator(0, -stepAngle, 0);

			//NewLoc = PrevLoc + PrevRot.Vector() * ForwardStep;*/
			/*NewLoc.X= NewLoc.X + 940;
			NewLoc.Y= NewLoc.Y + 540;*/
		//FRotator LookAtRot = (CameraLocation - NewLoc).Rotation();


		InsetViewActor->SetActorLocation(NewLoc);
		//InsetViewActor->SetActorRotation(LookAtRot);
		//	/*for (AInsetView* insetView : InsetViewList) {
		//		if (insetView) {*/
		//	FVector Location = InsetViewActor->GetActorLocation();
		//	FVector NewLocation = Location + SideOffset;



			//FRotator LookAtRotation = FRotationMatrix::MakeFromX(NewLocation).Rotator();

			//FVector NewLocation1 = CameraLocation - Location;

			//FRotator LookAtRotation = FRotationMatrix::MakeFromX(NewLocation1).Rotator();

			//	}
			//}
	}
}
