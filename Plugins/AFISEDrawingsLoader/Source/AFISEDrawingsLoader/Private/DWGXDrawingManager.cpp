#include "DWGXDrawingManager.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "Engine/World.h"
#include "Framework/Application/SlateApplication.h"
#include "DesktopPlatformModule.h"  
#include "Kismet/GameplayStatics.h"


static float MapDistanceToUnits(float distCm,
	float dNear, float dFar,
	float tNear, float tFar,
	float gamma)
{
	if (dFar <= dNear) return tNear;
	float t = FMath::Clamp((distCm - dNear) / (dFar - dNear), 0.f, 1.f);
	if (gamma != 1.f) t = FMath::Pow(t, gamma);
	return FMath::Lerp(tNear, tFar, t);
}

static float MapHeightToUnits(float heightM,
	float hNear, float hFar,
	float tNear, float tFar,
	float gamma)
{
	if (hFar <= hNear) return tNear;
	float t = FMath::Clamp((heightM - hNear) / (hFar - hNear), 0.f, 1.f);
	if (gamma != 1.f) t = FMath::Pow(t, gamma);
	return FMath::Lerp(tNear, tFar, t);
}

UDWGXDrawingManager* UDWGXDrawingManager::SingletonInstance = nullptr;

UDWGXDrawingManager* UDWGXDrawingManager::Get(UObject* WorldContext)
{
	if (!SingletonInstance)
	{
		SingletonInstance = NewObject<UDWGXDrawingManager>(WorldContext);
		SingletonInstance->AddToRoot(); // Persist for the life of the app

		ACesiumGeoreference* Goereference = ACesiumGeoreference::GetDefaultGeoreference(WorldContext->GetWorld());
		ACesium3DTileset* Tileset = Cast< ACesium3DTileset>(UGameplayStatics::GetActorOfClass(WorldContext->GetWorld(), ACesium3DTileset::StaticClass()));

		SingletonInstance->DWGXReader = NewObject<UCustomDrawingReader>(WorldContext);

		IShape::SetTileset(Tileset);
		IShape::SetGeoreference(Goereference);
		IShape::SetWorld(WorldContext->GetWorld());
	}

	return SingletonInstance;
}


void UDWGXDrawingManager::LoadDrawingConfig() {

	if (DWGXReader)
	{
		FString ConfigFilePath = FPaths::ProjectContentDir() / TEXT("Archive/AppConfig.xml");
		DWGXReader->ReadHeightFromConfig(ConfigFilePath);
	}

}
void UDWGXDrawingManager::LoadAllDrawings()
{
	Shapes.Empty();

	const FString DrawingFolder = FPaths::ProjectContentDir() / TEXT("DrawingFiles/");
	TArray<FString> DrawingFiles;

	IFileManager::Get().FindFiles(DrawingFiles, *DrawingFolder, TEXT("*.dwgx"));

	for (const FString& File : DrawingFiles)
	{
		FString FullPath = DrawingFolder / File;
		LoadDrawingFromFile(FullPath);
	}
}


void UDWGXDrawingManager::LoadDrawingFromFile(const FString& FullFilePath)
{
	TArray<TSharedPtr<IShape>> LoadedShapes;

	if (DWGXReader->LoadCustomDrawing(FullFilePath, LoadedShapes))
	{
		for (TSharedPtr<IShape>& Shape : LoadedShapes)
		{
			AddShape(Shape);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load drawing: %s"), *FullFilePath);
	}
}

void UDWGXDrawingManager::AddShape(TSharedPtr<IShape> Shape)
{
	if (Shape)
	{
		Shapes.Add(Shape);
	}
}

void UDWGXDrawingManager::RemoveShape(TSharedPtr<IShape> Shape)
{
	Shapes.Remove(Shape);
}

void UDWGXDrawingManager::ClearAllShapes()
{
	for (TSharedPtr<IShape>& Shape : Shapes)
	{
		if (Shape.IsValid())
		{
			Shape->Clear();
		}
	}
	Shapes.Empty();
	LoadedFileSet.Empty();

}

const TArray<TSharedPtr<IShape>>& UDWGXDrawingManager::GetShapes() const
{
	return Shapes;
}

void UDWGXDrawingManager::UpdateShapeScalesForCamera(UWorld* World)
{
	if (!World) return;

	APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
	if (!PC || !PC->PlayerCameraManager) return;

	const FVector CamPos = PC->PlayerCameraManager->GetCameraLocation();
	UpdateShapeScalesForCameraAt(CamPos);
}

void UDWGXDrawingManager::UpdateShapeScalesForCameraAt(const FVector& CamPos)
{
	//UWorld* World = GetWorld();
	//if (!World) return;

	//for (const TSharedPtr<IShape>& Shape : Shapes)
	//{
	//	if (!Shape.IsValid()) continue;

	//	const FVector ShapePos = Shape->GetWorldPosition();
	//	if (ShapePos.IsNearlyZero()) continue;

	//	const float distCm = FVector::Dist(CamPos, ShapePos);

	//	const float desiredUnits =
	//		MapDistanceToUnits(distCm, NearDistanceCm, FarDistanceCm,
	//			NearThicknessUnits, FarThicknessUnits, Gamma);

	//	float* pLast = LastAppliedThickness.Find(Shape);
	//	if (pLast && FMath::Abs(*pLast - desiredUnits) <= ThicknessHysteresis)
	//		continue;

	//	const int32 step = FMath::Max(1, FMath::RoundToInt(desiredUnits));
	//	Shape->SetLineWidth(step);
	//	Shape->SetLineHeight(step);
	//	Shape->UpdateScale(World); // calls shape-specific inward-only updater

	//	LastAppliedThickness.Add(Shape, desiredUnits);
	//}
    UWorld* World = GetWorld();
	if (!World) return;
	float HeightMeters = 0.0f;

	ACesiumGeoreference* Geo = ACesiumGeoreference::GetDefaultGeoreference(World);
	if (Geo) {
		const FVector LLH = Geo->TransformUnrealPositionToLongitudeLatitudeHeight(CamPos);
		HeightMeters = LLH.Z;
	}
	else {
		HeightMeters = CamPos.Z / 100.0f;
	}


    const float desiredUnits =
		MapHeightToUnits(HeightMeters, NearHeightMeters, FarHeightMeters,
			NearThicknessUnits, FarThicknessUnits, Gamma);

	if (FMath::Abs(LastAppliedHeightUnits - desiredUnits) <= ThicknessHysteresis) return;
    const int32 step = FMath::Max(1, FMath::RoundToInt(desiredUnits));

	for (const TSharedPtr<IShape>& Shape : Shapes)
	{
		Shape->SetLineWidth(step);
		Shape->SetLineHeight(step);
		Shape->UpdateScale(World);
	}
	LastAppliedHeightUnits = desiredUnits;

}


void UDWGXDrawingManager::LoadDrawingFromFileExplorer()
{

	TArray<FString> OutFileNames;
	// Open the file explorer for DWGX files
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (DesktopPlatform)
	{
		const void* ParentWindowHandle = FSlateApplication::Get()
			.FindBestParentWindowHandleForDialogs(nullptr);


		// Open the file dialog
		bool bOpenDialog = DesktopPlatform->OpenFileDialog(
			ParentWindowHandle,  // Parent window handle (nullptr for default)
			TEXT("Select DWGX File"),  // Title of the file dialog
			TEXT(""),  // Default path (empty for desktop)
			TEXT(""),  // Default file name (empty)
			TEXT("DWGX Files (*.dwgx)|*.dwgx"),  // File filter (DWGX files only)
			EFileDialogFlags::None,  // File dialog flags (you can add options here)K
			OutFileNames  // The array that will store selected file paths
		);

		if (bOpenDialog && OutFileNames.Num() > 0)
		{
			// Load the selected DWGX file
			const FString SelectedFilePath = OutFileNames[0];
			const FString Key = NormalizePath(SelectedFilePath);

			if (LoadedFileSet.Contains(Key)) {
				return;
			}
			LoadDrawingFromFile(SelectedFilePath);
			LoadedFileSet.Add(Key);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No file selected"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load DesktopPlatform"));
	}
}


void UDWGXDrawingManager::Shutdown()
{
	if (SingletonInstance)
	{
		SingletonInstance->ClearAllShapes();
		SingletonInstance->RemoveFromRoot();
		LoadedFileSet.Empty();
		SingletonInstance = nullptr;
	}
}

void UDWGXDrawingManager::ToggleVisibility(bool isVisible)
{
	for (TSharedPtr<IShape>& Shape : Shapes)
	{
		if (Shape.IsValid())
		{
			Shape->SetVisibility(isVisible);
		}
	}
}

void UDWGXDrawingManager::ToggleProjectionVisibility(bool isVisible)
{
	for (TSharedPtr<IShape>& Shape : Shapes)
	{
		if (Shape.IsValid())
		{
			Shape->SetProjectionVisibility(isVisible);
		}
	}
}

FString UDWGXDrawingManager::NormalizePath(const FString& InPath) const
{

	FString AbsPath = FPaths::ConvertRelativePathToFull(InPath);
	FPaths::MakeStandardFilename(AbsPath);
	AbsPath.ToLowerInline();
	return AbsPath;
}

void UDWGXDrawingManager::CustomTick(float DeltaTime)
{
	if (++FramesSinceScaleUpdate >= DrawScaleEveryNFrames)
	{
		if (GetWorld())
		{
			UpdateShapeScalesForCamera(GetWorld());
		}
		FramesSinceScaleUpdate = 0;
	}
}





