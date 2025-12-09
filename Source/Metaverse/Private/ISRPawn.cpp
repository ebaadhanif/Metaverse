// Fill out your copyright notice in the Description page of Project Settings.


#include "ISRPawn.h"
#include "XboxInputHandler.h"





// Sets default values
AISRPawn::AISRPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(RootComponent);
	IRMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/IR_Effect.IR_Effect"));

	


	//Camera->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
	//Camera->SetWorldRotation(FRotator(0.0f,0.0f,-90.0f));
}

// Called when the game starts or when spawned
void AISRPawn::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	SetActorLocationAndRotation(FVector(-64710.0, 730410.0, 0), FRotator(0.0f, -90.0f, 0.0f));
	//Delay the calling till Maping Context is initialized
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AISRPawn::BindSpecificDeviceInputActionsToFunctions);
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AISRPawn::BindX65FInputActionsToFunctions);
	FOV = Camera->FieldOfView; //by default 90

	BRITEStarWidgetRef = Cast<AISRHUD>(PlayerControllerRef->GetHUD())->GetISRHUDWidget();
	


	if (!BRITEStarWidgetRef->azimuthbarsSlot) {
		BRITEStarWidgetRef->azimuthbarsSlot = Cast<UCanvasPanelSlot>(BRITEStarWidgetRef->azimuthbars->Slot);
		//ContainSize = azimuthbarsSlot->GetSize();
	}
	IRMaterialInstance = UMaterialInstanceDynamic::Create(IRMaterial, nullptr);
	_loadingManager = Cast<ALoadingManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ALoadingManager::StaticClass()));
	obj = _loadingManager->GetUModel3DAssetManager();

}


// Called every frame
void AISRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BRITEStarWidgetRef->SetTime();
	BRITEStarWidgetRef->SetDate();
}

void AISRPawn::BindSpecificDeviceInputActionsToFunctions()
{
	AXboxInputHandler* CurrentXboxInputHandlerObject = Cast<AXboxInputHandler>(UGameplayStatics::GetActorOfClass(GetWorld(), AXboxInputHandler::StaticClass()));
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_Gamepad_Right_Thumbstick_X,
		ETriggerEvent::Triggered,
		this,
		&AISRPawn::RotateCamX

	);

	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_Gamepad_Right_Thumbstick_Y,
		ETriggerEvent::Triggered,
		this,
		&AISRPawn::RotateCamY
	);
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_Gamepad_Dpad_Up,
		ETriggerEvent::Completed,
		this,
		&AISRPawn::NextFOV
	);
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_Gamepad_Dpad_Down,
		ETriggerEvent::Completed,
		this,
		&AISRPawn::PrevFOV
	);
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_Gamepad_Dpad_Left,
		ETriggerEvent::Triggered,
		this,
		&AISRPawn::ZoomOut
	);
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_Gamepad_Dpad_Right,
		ETriggerEvent::Triggered,
		this,
		&AISRPawn::ZoomIn
	);
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_Gamepad_Face_Button_Right,
		ETriggerEvent::Completed,
		this,
		&AISRPawn::ToggleIRMode
	);
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_Gamepad_Face_Button_Left,
		ETriggerEvent::Triggered,
		this,
		&AISRPawn::SwitchToTVMode
	);
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_Gamepad_Face_Button_Top,
		ETriggerEvent::Completed,
		this,
		&AISRPawn::SwitchToCageMode
	);
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_Gamepad_Face_Button_Bottom,
		ETriggerEvent::Completed,
		this,
		&AISRPawn::SwitchToStowMode
	);
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_Gamepad_Right_Shoulder,
		ETriggerEvent::Completed,
		this,
		&AISRPawn::ToggleCameraLock
	);
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_Gamepad_Left_Shoulder,
		ETriggerEvent::Triggered,
		this,
		&AISRPawn::ToggleLaser
		//& AISRPawn::SetOwnLatLong
	);

}

void AISRPawn::BindX65FInputActionsToFunctions()
{
	AASaitekX65FInputHandler* CurrentXboxInputHandlerObject = Cast<AASaitekX65FInputHandler>(UGameplayStatics::GetActorOfClass(GetWorld(), AASaitekX65FInputHandler::StaticClass()));
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_Stick_X_ValueChange,
		ETriggerEvent::Triggered,
		this,
		&AISRPawn::RotateCamXX65FDevice

	);

	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_Stick_Y_ValueChange,
		ETriggerEvent::Triggered,
		this,
		&AISRPawn::RotateCamYX65FDevice
	);
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_BowlHat_UP_Press,
		ETriggerEvent::Completed,
		this,
		&AISRPawn::NextFOV
	);
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_BowlHat_Down_Press,
		ETriggerEvent::Completed,
		this,
		&AISRPawn::PrevFOV
	);
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_ScrollWheel_Back,
		ETriggerEvent::Triggered,
		this,
		&AISRPawn::ZoomOut
	);
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_FlyingPinkieSwitch_Press,
		ETriggerEvent::Triggered,
		this,
		&AISRPawn::ZoomIn
	);
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_Pinkie_Button_Press,
		ETriggerEvent::Triggered,
		this,
		&AISRPawn::ZoomOut
	);
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_ScrollWheel_Forward,
		ETriggerEvent::Triggered,
		this,
		&AISRPawn::ZoomIn
	);
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_CastleHat_Right_Press,
		ETriggerEvent::Completed,
		this,
		&AISRPawn::ToggleIRMode
	);
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_CastleHat_Left_Press,
		ETriggerEvent::Triggered,
		this,
		&AISRPawn::SwitchToTVMode
	);
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_CastleHat_UP_Press,
		ETriggerEvent::Completed,
		this,
		&AISRPawn::SwitchToCageMode
	);
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_CastleHat_Down_Press,
		ETriggerEvent::Completed,
		this,
		&AISRPawn::SwitchToStowMode
	);
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_A_Button_Press,
		ETriggerEvent::Completed,
		this,
		&AISRPawn::ToggleCameraLock
	);
	CurrentXboxInputHandlerObject->BindActions(
		CurrentXboxInputHandlerObject->IA_B_Button_Press,
		ETriggerEvent::Triggered,
		this,
		&AISRPawn::ToggleLaser
		//& AISRPawn::SetOwnLatLong
	);
}

void AISRPawn::RotateCamX(const FInputActionValue& Value)
{
	
	
	/*else if (Intrpt && AzimuthAngle == 0)
	{
		BRITEStarWidgetRef->CameraModeText->SetText(FText::FromString("Tntrpt"));
		Intrpt = false;
	}
	else
	{
		Intrpt = false;
	}*/
	float InputValue = Value.GetMagnitude();
	CalculateAzimuth(InputValue);
	

	//FGeometry Geometry = BRITEStarWidgetRef->azimuthbars->GetCachedGeometry();
	//FGeometry StripGeometry = BRITEStarWidgetRef->HeadingStripImage->GetCachedGeometry();

	///*FGeometry azimuthBarMinus180Geometry = BRITEStarWidgetRef->azimuthBarMinus180->GetCachedGeometry();
	//FGeometry azimuthBarPlus180Geometry = BRITEStarWidgetRef->azimuthBarPlus180->GetCachedGeometry();*/

	//Size = Geometry.GetLocalSize();
	//StripSize = Geometry.GetLocalSize();
	//Position = Geometry.GetAbsolutePosition();
	///*azimuthBarMinus180Position = azimuthBarMinus180Geometry.GetAbsolutePosition();
	//azimuthBarPlus180Position = azimuthBarPlus180Geometry.GetAbsolutePosition();*/
	//StripPosition = Geometry.GetAbsolutePosition();

	//LeftX = azimuthBarMinus180Position.X/*Position.X*/;
	//StripLeftX = StripPosition.X;
	//RightX = azimuthBarPlus180Position.X/*Position.X + Size.X*/;
	//StripRightX = StripPosition.X + Size.X;
	//LeftX = LeftX - 500;
	//StripLeftX = StripLeftX-500;
	//RightX = RightX - 500;
	//StripRightX = StripRightX-500 ;
	//FVector2D ScreenResolution;
	//GEngine->GameViewport->GetViewportSize(ScreenResolution);

	////GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("StripRightX: %f"), StripLeftX));

	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("ScreenResolution: %dx%d"), (int32)ScreenResolution.X, (int32)ScreenResolution.Y));
	////FMargin Margin = BRITEStarWidgetRef->azimuthbarsSlot->GetOffsets();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("Left Right: %fx%f"), StripLeftX, StripRightX));
	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("HeadingStripPosition Right: %f"), HeadingStripPositionX));
	////GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("SizeX: %fx%f"), Size.X));
	////GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("X Y: %fx%f"), LeftX, RightX));
	////GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("Size.X Size.Y: %fx%f"), Size.X, Size.Y));
	//if (Value.GetMagnitude() >= 0.1 || Value.GetMagnitude() <= -0.1) { //0.1 because Xbox Joystick gives continous values of magnitude 0.05
	//	Yaw = Yaw + Value.GetMagnitude();

	//	FRotator newRotation = FRotator(Pitch, Yaw, 0.0);
	//	Camera->SetRelativeRotation(newRotation);


	//	AzimuthAngle = AzimuthAngle + Value.GetMagnitude();

	//	//CarretPositionX = CarretPositionX + Value.GetMagnitude() * 3.4142f;

	//	//HeadingStripPositionX = HeadingStripPositionX - (Value.GetMagnitude()/**1.0f*/ )/0.345f;

	//	LOSValue = LOSValue + Value.GetMagnitude();

	//	CarretPositionX = MapAngleToRangeLeftRight(AzimuthAngle,LeftX,RightX);
	//	HeadingStripPositionX = MapAngleToRange(LOSValue);
	//	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("Position: %f"), CarretPositionX));
	//	if (AzimuthAngle >= 180 && Value.GetMagnitude() > 0.0f)
	//	{

	//		AzimuthAngle = -180.0f;
	//		
	//	}
	//	else if (AzimuthAngle <= -180)
	//	{
	//		AzimuthAngle = 180.0f;
	//	}

	//	if (LOSValue>=360) {
	//		LOSValue = 0;
	//	}
	//	else if (LOSValue <= 0)
	//	{
	//		LOSValue = LOSValue + 360;
	//	}



		//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("Value: %d"), Value.GetMagnitude()));
		/*if (BRITEStarWidgetRef->ContainSize.X > 256.0)
		{
			UperLimit = BRITEStarWidgetRef->ContainSize.X - 256;
			UperLimit = UperLimit / 2;
		}
		if (BRITEStarWidgetRef->ContainSize.X < 256.0)
		{
			UperLimit =  256 - BRITEStarWidgetRef->ContainSize.X;
			UperLimit = UperLimit / 2;
		}*/
		//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("CarretPositionX : %f"), CarretPositionX));

		//if (CarretPositionX > RightX /*&& Value.GetMagnitude() > 0.0f*/)
		//{
		//	CarretPositionX = LeftX/*-255.0f + UperLimit*/;
		//	
		//	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("CarretPositionX YZ : %f"), CarretPositionX ));
  //  	}
		//else if (CarretPositionX < LeftX)
		//{
		//	CarretPositionX =RightX /*1140.0f + UperLimit*/;
	
		//	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("CarretPositionX   YX: %f"), CarretPositionX));

		//}
		//

		//if (HeadingStripPositionX <= -1100.0f && Value.GetMagnitude() > 0.0f)
		//{
		//	HeadingStripPositionX = /*StripLeftX-*//*HeadingStripPositionX-*/-60.01/*-255.0f + UperLimit*/;

		//	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("HeadingStripPosition Right: %f"), HeadingStripPositionX));

		//}
		//else if (HeadingStripPositionX >= -60.01f && Value.GetMagnitude() < 0.0f)
		//{
		//	HeadingStripPositionX = /*StripRightX+*//*HeadingStripPositionX+1160.f*/ /*1140.0f + UperLimit*/-1100.0f;

		//	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("HeadingStripPosition Left: %f"), HeadingStripPositionX));

		//}



		/*BRITEStarWidgetRef->SetAzimuth(AzimuthAngle);

		SetAzimuthCarret(CarretPositionX);
		SetLOS(LOSValue);
		SetLOSStrip(HeadingStripPositionX);
	    }

	    UpdateNortPointer(Yaw);*/


}








void AISRPawn::RotateCamY(const FInputActionValue& Value)
{
	float InputValue = Value.GetMagnitude();

	CalculateElevation(InputValue);


	//FGeometry Geometry = BRITEStarWidgetRef->elevationBars->GetCachedGeometry();
	//Size = Geometry.GetLocalSize();
	//Position = Geometry.GetAbsolutePosition();

	//TopY = Position.Y;
	//BottomY = Position.Y + Size.Y;
	//TopY = TopY - 20;
	//BottomY = BottomY - 30;



	//if (Value.GetMagnitude() >= 0.1 || Value.GetMagnitude() <= -0.1)  //0.1 because Xbox Joystick gives continous values of magnitude 0.05
	//{
	//	Pitch = Pitch - Value.GetMagnitude();
	//	ElevationAngle = ElevationAngle - Value.GetMagnitude();

	//	/*GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("TopY : %f"), TopY));
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("TopY : %f"), BottomY));*/
	//	FRotator newRotation = FRotator(Pitch, Yaw, 0.0);
	//	Camera->SetRelativeRotation(newRotation);

	//	
	//	if ((ElevationAngle >= 30.0f) && (ElevationAngle > 0.0f))
	//	{
	//		ElevationAngle = 30.0f;

	//	}
	//	else if (ElevationAngle <= -120.0f)
	//	{
	//		ElevationAngle = -120.0f;
	//	}


	//	if (ElevCarretPositionY >= BottomY && Value.GetMagnitude() > 0.0f)
	//	{
	//		ElevCarretPositionY = BottomY/*-255.0f + UperLimit*/;
	//		
	//		//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("CarretPositionY Bottom : %f"), ElevCarretPositionY));
	//		
	//	}
	//	else if (ElevCarretPositionY <= TopY && Value.GetMagnitude() < 0.0f)
	//	{
	//		CarretPositionX = TopY /*1140.0f + UperLimit*/;

	//		//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("CarretPositionY   Top: %f"), ElevCarretPositionY));

	//	}
	//	else 
	//	{
	//	 
	//		 ElevCarretPositionY = ElevCarretPositionY + Value.GetMagnitude() * 3.4141f;
	//	 
	//	}

	///*	SetElevationCarret(ElevCarretPositionY);

	//	BRITEStarWidgetRef->SetElevationAngle(ElevationAngle);*/
	//	BRITEStarWidgetRef->SetElevationCarret(ElevCarretPositionY);
	//	BRITEStarWidgetRef->SetElevationAngle(ElevationAngle);
	//	
	//}
}

void AISRPawn::RotateCamXX65FDevice(const FInputActionValue& Value)
{
	float InputValue = Value.GetMagnitude();
	InputValue = (InputValue * 2) - 1;
	CalculateAzimuth(InputValue);
}


void  AISRPawn::CalculateAzimuth(float InputValue) 
{
	FGeometry Geometry = BRITEStarWidgetRef->azimuthbars->GetCachedGeometry();
	FGeometry StripGeometry = BRITEStarWidgetRef->HeadingStripImage->GetCachedGeometry();
	/*FGeometry azimuthBarMinus180Geometry = BRITEStarWidgetRef->azimuthBarMinus180->GetCachedGeometry();
	FGeometry azimuthBarPlus180Geometry = BRITEStarWidgetRef->azimuthBarPlus180->GetCachedGeometry();*/
	Size = Geometry.GetLocalSize();
	StripSize = Geometry.GetLocalSize();
	Position = Geometry.GetAbsolutePosition();
	/*azimuthBarMinus180Position = azimuthBarMinus180Geometry.GetAbsolutePosition();
	azimuthBarPlus180Position = azimuthBarPlus180Geometry.GetAbsolutePosition();*/
	StripPosition = Geometry.GetAbsolutePosition();
	LeftX = Position.X;
	StripLeftX = StripPosition.X;
	RightX = Position.X + Size.X;
	StripRightX = StripPosition.X + Size.X;
	LeftX = LeftX - 500;
	StripLeftX = StripLeftX-500;
	RightX = RightX - 500;
	StripRightX = StripRightX-500 ;
//	FVector2D ScreenResolution;
	/*GEngine->GameViewport->GetViewportSize(ScreenResolution);
	float ScreenCenterX = ScreenResolution.X / 2.0f;
	float CenterBoundX = (LeftX + RightX) / 2;
	float OffsetX = ScreenCenterX - CenterBoundX;
	if (FMath::Abs(OffsetX)>1.0f)
	{
		FVector2D CurrentTransform = BRITEStarWidgetRef->azimuthbars->RenderTransform.Translation;
		BRITEStarWidgetRef->azimuthbars->SetRenderTranslation(CurrentTransform+ FVector2D(OffsetX,0.0f));

	
	}*/
	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("StripRightX: %f"), StripLeftX));

	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("ScreenResolution: %dx%d"), (int32)ScreenResolution.X, (int32)ScreenResolution.Y));
	//FMargin Margin = BRITEStarWidgetRef->azimuthbarsSlot->GetOffsets();
//	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("Left Right: %fx%f"), StripLeftX, StripRightX));
	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("HeadingStripPosition Right: %f"), HeadingStripPositionX));
	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("SizeX: %fx%f"), Size.X));
	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("X Y: %fx%f"), LeftX, RightX));
	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("Size.X Size.Y: %fx%f"), Size.X, Size.Y));


	if (InputValue >= 0.1 || InputValue <= -0.1) { //0.1 because Xbox Joystick gives continous values of magnitude 0.05
		Yaw = Yaw + InputValue * CamSpeed;
		AzimuthAngle = AzimuthAngle + InputValue;
		FRotator newRotation = FRotator(Pitch, Yaw, 0.0);
		Camera->SetRelativeRotation(newRotation);
		if (AzimuthAngle > 0)
		{
			BRITEStarWidgetRef->CameraModeText->SetText(FText::FromString("Intrpt"));

		}

		

		//CarretPositionX = CarretPositionX + Value.GetMagnitude() * 3.4142f;

		//HeadingStripPositionX = HeadingStripPositionX - (Value.GetMagnitude()/**1.0f*/ )/0.345f;

		LOSValue = NormalizeAngleTo360( AzimuthAngle) /*LOSValue + InputValue*/;
		
		CarretPositionX = MapAngleToRangeLeftRight(AzimuthAngle,LeftX,RightX);
		HeadingStripPositionX = MapAngleToRange(LOSValue);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("Position: %f"), CarretPositionX));
		if (AzimuthAngle >= 180 && InputValue > 0.0f)
		{
			AzimuthAngle = -180.0f;
		}
		else if (AzimuthAngle <= -180)
		{
			AzimuthAngle = 180.0f;
		}

		if (LOSValue>=360) {
			LOSValue = 0;
		}
		else if (LOSValue <= 0)
		{
			LOSValue = LOSValue + 360;
		}

		//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("Value: %d"), Value.GetMagnitude()));
		/*if (BRITEStarWidgetRef->ContainSize.X > 256.0)
		{
			UperLimit = BRITEStarWidgetRef->ContainSize.X - 256;
			UperLimit = UperLimit / 2;
		}
		if (BRITEStarWidgetRef->ContainSize.X < 256.0)
		{
			UperLimit =  256 - BRITEStarWidgetRef->ContainSize.X;
			UperLimit = UperLimit / 2;
		}*/
		//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("CarretPositionX : %f"), CarretPositionX));

		if (CarretPositionX > RightX /*&& Value.GetMagnitude() > 0.0f*/)
		{
			CarretPositionX = LeftX/*-255.0f + UperLimit*/;
			
			//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("CarretPositionX YZ : %f"), CarretPositionX ));
    	}
		else if (CarretPositionX < LeftX)
		{
			CarretPositionX =RightX /*1140.0f + UperLimit*/;
	
			//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("CarretPositionX   YX: %f"), CarretPositionX));

		}
		

		if (HeadingStripPositionX <= -1100.0f && InputValue > 0.0f)
		{
			HeadingStripPositionX = /*StripLeftX-*//*HeadingStripPositionX-*/-60.01f/*-255.0f + UperLimit*/;

			//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("HeadingStripPosition Right: %f"), HeadingStripPositionX));

		}
		else if (HeadingStripPositionX >= -60.01f && InputValue < 0.0f)
		{
			HeadingStripPositionX = /*StripRightX+*//*HeadingStripPositionX+1160.f*/ /*1140.0f + UperLimit*/-1100.0f;

			//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("HeadingStripPosition Left: %f"), HeadingStripPositionX));

		}



		BRITEStarWidgetRef->SetAzimuth(AzimuthAngle);
		BRITEStarWidgetRef->SetAzimuthCarret(CarretPositionX);


		//SetAzimuthCarret(CarretPositionX);
	
		//BRITEStarWidgetRef->Update(AzimuthAngle, ElevationAngle, CarretPositionX, ElevCarretPositionY);
		
		SetLOS(LOSValue);
		SetLOSStrip(HeadingStripPositionX);
		UpdateNortPointer(Yaw);
	}
	
}

void  AISRPawn::CalculateElevation(float InputValue)
{

	FGeometry Geometry = BRITEStarWidgetRef->elevationBars->GetCachedGeometry();
	Size = Geometry.GetLocalSize();
	Position = Geometry.GetAbsolutePosition();

	TopY = Position.Y;
	BottomY = Position.Y + Size.Y;
	TopY = TopY - 20;
	BottomY = BottomY - 30;


	/*GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("TopY : %f"), TopY));
    GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("TopY : %f"), BottomY));*/



	if (InputValue >= 0.1 || InputValue <= -0.1)  //0.1 because Xbox Joystick gives continous values of magnitude 0.05
	{
		Pitch = Pitch - InputValue * CamSpeed;
		ElevationAngle = ElevationAngle - InputValue;

		
		FRotator newRotation = FRotator(Pitch, Yaw, 0.0);
		Camera->SetRelativeRotation(newRotation);

		if ((ElevationAngle >= 30.0f) && (ElevationAngle > 0.0f))
		{
			ElevationAngle = 30.0f;

		}
		else if (ElevationAngle <= -120.0f)
		{
			ElevationAngle = -120.0f;
		}

		//if (ElevCarretPositionY >= BottomY )
		//{
		//	ElevCarretPositionY = BottomY/*-255.0f + UperLimit*/;

		//	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("CarretPositionY Bottom : %f"), ElevCarretPositionY));

		//}
		//else if (ElevCarretPositionY <= TopY )
		//{
		//	ElevCarretPositionY = TopY /*1140.0f + UperLimit*/;

		//	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("CarretPositionY   Top: %f"), ElevCarretPositionY));
		//}
		//else {

			ElevCarretPositionY = MapAngleToRangeTopBottom(ElevationAngle, BottomY,TopY)/*ElevCarretPositionY + InputValue * 3.4141f*/;

		/*}*/
		//SetElevationCarret(ElevCarretPositionY);
		BRITEStarWidgetRef->SetElevationCarret(ElevCarretPositionY);
    	BRITEStarWidgetRef->SetElevationAngle(ElevationAngle);
		//BRITEStarWidgetRef->Update(AzimuthAngle, ElevationAngle, CarretPositionX, ElevCarretPositionY);
	}

}

float AISRPawn::MapAngleToRange(float AngleDegrees) 
{
	float ClampAngle = FMath::Fmod(AngleDegrees,360.0f);
	return FMath::GetMappedRangeValueClamped(
		FVector2D(0.0f, 360.0f),
		FVector2D(-60.0f, -1100.0f),
		ClampAngle
	);
}
float AISRPawn::MapAngleToRangeLeftRight(float AngleDegrees, float Left,float Right)
{
	float ClampAngle ;
	/*if (AzimuthAngle >= 180 )
	{

		AzimuthAngle = -180.0f;

	}
	else if (AzimuthAngle <= -180)
	{
		AzimuthAngle = 180.0f;
	}*/
	float angle;
	if (AzimuthAngle >0)
	{
		
		ClampAngle = FMath::Fmod(AngleDegrees, -180.0f);
		return FMath::GetMappedRangeValueClamped(

			FVector2D(0.0f, 180.0),
			FVector2D(440.0f, Right),
			ClampAngle
		);
	}
	else
	{
		angle = 180.0f;
		ClampAngle = FMath::Fmod(AngleDegrees, 180.0f);
		return FMath::GetMappedRangeValueClamped(

			FVector2D(-180.0f, 0.0),
			FVector2D(LeftX, 440.0f),
			ClampAngle
		);

	}
	/*return FMath::GetMappedRangeValueClamped(

		FVector2D(0.0f, angle),
		FVector2D(Left, Right),
		ClampAngle
	);*/

}
//float AISRPawn::MapAngleToRangeTopBottom(float AngleDegrees, float Bottom, float Top)
//{
//	float ClampAngle;
//	float angle;
//	if (AngleDegrees > 0)
//	{
//
//		ClampAngle = FMath::Fmod(AngleDegrees, 30.0f);
//		return FMath::GetMappedRangeValueClamped(
//			FVector2D(0.0f, 30.0f),
//			FVector2D(360.0f, Top),
//			ClampAngle
//		);
//	}
//	else
//	{
//		angle = 180.0f;
//		ClampAngle = FMath::Fmod(AngleDegrees, -120.0f);
//		return FMath::GetMappedRangeValueClamped(
//			FVector2D(-120.0f, 0.0),
//			FVector2D(Bottom, 360.0f),
//			ClampAngle
//		);
//
//	}
//	
//}

float AISRPawn::MapAngleToRangeTopBottom(float AngleDegrees, float Bottom, float Top)
{
	//float ClampAngle;
	//float angle;
	float ClampAngle = FMath::Fmod(AngleDegrees, 360.0f);
	return FMath::GetMappedRangeValueClamped(
		FVector2D(30.0f, -120.0f),
		FVector2D(Top, Bottom),
		ClampAngle
	);

	/*if (AngleDegrees > 0)
	{

		ClampAngle = FMath::Fmod(AngleDegrees, 30.0f);
		return FMath::GetMappedRangeValueClamped(
			FVector2D(0.0f, 30.0f),
			FVector2D(360.0f, Top),
			ClampAngle
		);
	}
	else
	{
		angle = 180.0f;
		ClampAngle = FMath::Fmod(AngleDegrees, -120.0f);
		return FMath::GetMappedRangeValueClamped(
			FVector2D(-120.0f, 0.0),
			FVector2D(Bottom, 360.0f),
			ClampAngle
		);

	}*/

}





void AISRPawn::RotateCamYX65FDevice(const FInputActionValue& Value)
{
	float InputValue = Value.GetMagnitude();
	InputValue = (InputValue * 2) - 1;
	CalculateElevation(InputValue);
}

void AISRPawn::ZoomIn(const FInputActionValue& Value)
{
	FOV = FOV - 0.5;
	FOV= FMath::Clamp(FOV,0.5f,90.0f);
	Camera->SetFieldOfView(FOV);
	if (FOV < 10)
	{
		CamSpeed = 0.1f;
	}
	else if (FOV < 30) {
		CamSpeed = 0.5f;
	}
	
	//BRITEStarWidgetRef->SetOwnLatLong(123, 123);
}

void AISRPawn::ZoomOut(const FInputActionValue& Value)
{
	FOV = FOV + 0.5;
	FOV = FMath::Clamp(FOV, 0.5f, 90.0f);
	Camera->SetFieldOfView(FOV);
	if (FOV > 30) {
		CamSpeed = 1.0f;
	}
	else if (FOV > 10)
	{
		CamSpeed = 0.5f;
	}
}

void AISRPawn::PrevFOV(const FInputActionValue& Value)
{

	FOV = FOV + 5;
	Camera->SetFieldOfView(FOV);
	BRITEStarWidgetRef->PrevFOV();
}

void AISRPawn::NextFOV(const FInputActionValue& Value)
{
	FOV = FOV - 5;
	Camera->SetFieldOfView(FOV);
	BRITEStarWidgetRef->NextFOV();
}

void AISRPawn::SetOwnLatLong(const FInputActionValue& Value)
{

	BRITEStarWidgetRef->SetOwnLatLong(123, 123);

	//CrosshairWideImage->SetVisibility(ESlateVisibility::Visible);

}

void AISRPawn::UpdateTrgtLatLong()
{






	//BRITEStarWidgetRef->SetTargetLatLong(123, 123);

	//CrosshairWideImage->SetVisibility(ESlateVisibility::Visible);

}

void AISRPawn::UpdateTargetAltitude()
{

	//BRITEStarWidgetRef->SetTargetAltitude(123);

	//CrosshairWideImage->SetVisibility(ESlateVisibility::Visible);

}

void AISRPawn::UpdateTargetDistance()
{

	BRITEStarWidgetRef->SetTargetDistance(123);

	//CrosshairWideImage->SetVisibility(ESlateVisibility::Visible);

}

void AISRPawn::SetAzimuthAngle(float camPitch)
{
	if (camPitch < 180 && camPitch > 0) {
		BRITEStarWidgetRef->SetAzimuth(camPitch);
	}
	if (camPitch > -180 && camPitch < 0) {
		BRITEStarWidgetRef->SetAzimuth(camPitch);
	}
	if (camPitch < -180)
	{
		camPitch -= 360;

	}
	if (camPitch > 180)
	{
		camPitch += 360;

	}
}
void AISRPawn::UpdateNortPointer(float yaw)
{
	
	if (!BRITEStarWidgetRef->NorthPointerImage) return;
	float CompassYaw = FMath::Fmod(yaw - 90.f + 360.f, 360.f);
	CompassYaw = FMath::Fmod(CompassYaw + 180.f, 360.f);
	float RotationAngle = -CompassYaw;
	BRITEStarWidgetRef->NorthPointerImage->SetRenderTransformAngle(RotationAngle);
    //if (CompassYawText)
	//{
	//	//FString YawString = FString::Printf(TEXT("Yaw: %.2f"), GetDisplayValue(GetNormalizedYaw(Yaw + 90)));
	//	FString YawString = GetDisplayValue(GetNormalizedYaw(Yaw + 90));
	//	CompassYawText->SetText(FText::FromString(YawString));
	//}
}

//void AISRPawn::SetLOSStrip(double PositionX)
//{
//	FVector2D HeadingStripAnchor = FVector2D(PositionX, -15.42865);
//
//	//BRITEStarWidgetRef->
//
//
//}
void AISRPawn::SetLOS(double LOS)
{
	BRITEStarWidgetRef->SetLOSValue(LOS);
	//BRITEStarWidgetRef->
}

void AISRPawn::SetAzimuthCarret(double PositionX)
{
	FVector2D CarretAnchor = FVector2D(PositionX, -15.42865);

	//BRITEStarWidgetRef->SetAzimuthCarret(CarretAnchor);

}

void AISRPawn::SetLOSStrip(double PositionX)
{
	FVector2D HeadingStripAnchor = FVector2D(PositionX, 0.0f);
	
	BRITEStarWidgetRef->SetHeadingStripImage(HeadingStripAnchor);
	
}

void AISRPawn::SetElevationCarret(double PositionX)
{
	FVector2D CarretAnchor = FVector2D(104.0, PositionX);

	//BRITEStarWidgetRef->SetElevationCarret(CarretAnchor);

}

void AISRPawn::SwitchToCageMode(const FInputActionValue& Value)
{
	
	AzimuthAngle = 0;
	ElevationAngle = 0;
	Yaw = -90.0f;
	Pitch = 0;
	SetLOS(0);
	SetLOSStrip(-57.0f);
	CalculateAzimuth(0.1f);
	//UpdateNortPointer(Yaw);
	CalculateElevation(0.1f);
	//BRITEStarWidgetRef->Update(AzimuthAngle, ElevationAngle, CarretPositionX, ElevCarretPositionY);
	
	BRITEStarWidgetRef->CameraModeText->SetText(FText::FromString("Cage"));
}

void AISRPawn::SwitchToStowMode(const FInputActionValue& Value)
{
	ElevationAngle = -90;
	AzimuthAngle = 0;
	Pitch = -90.0f;
	Yaw = -90.0f;
	SetLOS(0);
	SetLOSStrip(-57.0f);
	CalculateAzimuth(0.1f);
	UpdateNortPointer(Yaw);
	CalculateElevation(0.1f);
	//BRITEStarWidgetRef->Update(AzimuthAngle, ElevationAngle, CarretPositionX, ElevCarretPositionY);
	//BRITEStarWidgetRef->Update(AzimuthAngle, ElevationAngle, CarretPositionX, ElevCarretPositionY);

	BRITEStarWidgetRef->CameraModeText->SetText(FText::FromString("Stow"));

}

float AISRPawn::NormalizeAngleTo360(float Angle)
{
	float result = FMath::Fmod(Angle,360.0f);
	if (result < 0) 
    {
		result += 360.0f;
	}
	return result;
}
void AISRPawn::UpdateIRTexture()
{
	/*for (auto* entity : m_RemoteEntitiesList)
	{

		entity->Mil2525Height = Mil2525Manager::GetMil2525ManagerInstance()->SetMil2525Height(entity->Mil2525Height);
	}*/
	
		for (AEntityBase* entity : EntityManager::GetEntityManagerInstance()->GetEntityList())
		{
			if (entity)
			{
				obj->HandleIRStandardTextures(entity, obj->IRTexture);
				
				//uModel3DAssetManager->IRTexture
			}
		}
	

}




void AISRPawn::ToggleIRMode(const FInputActionValue& Value)
{
	BRITEStarWidgetRef->ModeText->SetText(FText::FromString("IR"));
	//IRMaterialInstance = UMaterialInstanceDynamic::Create(IRMaterial, nullptr);

	if (isWHot) {

		IRMaterialInstance->SetScalarParameterValue("IRSwitch", 0);
		isWHot = false;
		BRITEStarWidgetRef->IRModeText->SetText(FText::FromString("Wht"));

	}
	else
	{
		IRMaterialInstance->SetScalarParameterValue("IRSwitch", 1);
		isWHot = true;
		
		BRITEStarWidgetRef->IRModeText->SetText(FText::FromString("Blk"));
	}
	Camera->PostProcessSettings.AddBlendable(IRMaterialInstance, 1.0f);
	UpdateIRTexture();
}

void AISRPawn::SwitchToTVMode(const FInputActionValue& Value)
{
	Camera->PostProcessSettings.AddBlendable(IRMaterialInstance, 0.0f);
	BRITEStarWidgetRef->ModeText->SetText(FText::FromString("TV"));
	BRITEStarWidgetRef->IRModeText->SetText(FText::FromString(""));

	for (AEntityBase* entity : EntityManager::GetEntityManagerInstance()->GetEntityList())
	{
		obj->RevertToOrignalTextures(entity);
	}
}

void AISRPawn::ToggleLaser(const FInputActionValue& Value)
{

}

void AISRPawn::ToggleCameraLock(const FInputActionValue& Value)
{
	ToggleLockBox();
	UpdateTrgtLatLong();
	UpdateTargetAltitude();
	UpdateTargetDistance();
	
}

void AISRPawn::ToggleLockBox()
{
	
	if (!LckBoxVisible)
	{
		BRITEStarWidgetRef->LockBoxImage->SetVisibility(ESlateVisibility::Hidden);
		BRITEStarWidgetRef->LockModeText->SetText(FText::FromString("Trk/Cst"));
			LckBoxVisible = true;

	}
	else 
	{
		BRITEStarWidgetRef->LockBoxImage->SetVisibility(ESlateVisibility::Visible);
		BRITEStarWidgetRef->LockModeText->SetText(FText::FromString("Trk/T"));
		LckBoxVisible = false;
	}
	
}






// Called to bind functionality to input
void AISRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

