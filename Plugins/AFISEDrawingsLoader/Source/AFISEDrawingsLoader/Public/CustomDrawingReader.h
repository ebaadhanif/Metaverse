
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IShape.h"
#include "CustomDrawingReader.generated.h"


UENUM(BlueprintType)
enum class EDrawingShapeType : uint8
{
    Circle = 0 UMETA(DisplayName = "Circle"),
    Rectangle = 1 UMETA(DisplayName = "Rectangle"),
    Polygon = 2 UMETA(DisplayName = "Polygon"),
    Line = 3 UMETA(DisplayName = "Line"),
    Point = 4 UMETA(DisplayName = "Point")
};


UENUM(BlueprintType)
enum class EDrawingMaterialType : uint8
{
    Circle      UMETA(DisplayName = "Circle", ToolTip = "Material for Circle Shape"),
    Rectangle   UMETA(DisplayName = "Rectangle", ToolTip = "Material for Rectangle Shape"),
    Polygon     UMETA(DisplayName = "Polygon", ToolTip = "Material for Polygon Shape"),
    Line        UMETA(DisplayName = "Line", ToolTip = "Material for Line Shape"),
    Point       UMETA(DisplayName = "Point", ToolTip = "Material for Point Shape")
};

UCLASS()
class AFISEDRAWINGSLOADER_API UCustomDrawingReader : public UObject
{
    GENERATED_BODY()

public:

    bool LoadCustomDrawing(const FString& FilePath, TArray<TSharedPtr<IShape>>& LoadedShapes);

    float ReadHeightFromConfig(const FString& ConfigFilePath);

    float Height = 0.0f;


};





