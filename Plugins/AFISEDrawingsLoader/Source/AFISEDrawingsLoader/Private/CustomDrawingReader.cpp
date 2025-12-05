#include "CustomDrawingReader.h"

#include "FRectangle.h"
#include "FCircle.h"
#include "FLine.h"
#include "FPoint.h"
#include "FPolygon.h"
#include "Misc/FileHelper.h"
#include "SceneManagement.h"
#include "Serialization/MemoryReader.h"
#include "Materials/MaterialInterface.h"
#include "Engine/World.h"
#include "XmlParser.h"
#include "CesiumGeoreference.h"

bool UCustomDrawingReader::LoadCustomDrawing(const FString& FilePath, TArray<TSharedPtr<IShape>>& OutShapes)
{

    TArray<uint8> FileBytes;
    if (!FFileHelper::LoadFileToArray(FileBytes, *FilePath))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load DWGX file: %s"), *FilePath);
        return false;
    }

    FMemoryReader Reader(FileBytes, true);
    Reader.Seek(0);

    char DwgVer[11];
    Reader.Serialize(DwgVer, 11);
    if (FCStringAnsi::Strcmp(DwgVer, "dwgx-5.2.0") != 0)
    {
        UE_LOG(LogTemp, Error, TEXT("Unsupported DWGX version."));
        return false;
    }

    int32 ShapeCount = 0;
    Reader << ShapeCount;

    for (int32 i = 0; i < ShapeCount && !Reader.AtEnd(); ++i)
    {
        char Label[50];
        Reader.Serialize(Label, 50);

        int32 ShapeTypeRaw;
        Reader << ShapeTypeRaw;
        EDrawingShapeType ShapeType = static_cast<EDrawingShapeType>(ShapeTypeRaw);

        TSharedPtr<IShape> CurrentShape = nullptr;

        switch (ShapeType)
        {
        case EDrawingShapeType::Circle:
        {
            double Radius, Lat, Lon;
            Reader << Radius << Lat << Lon;

            float R, G, B, A;
            Reader << R << G << B << A;
            FLinearColor LineColor(R, G, B, A);

            int32 LineWidth;
            Reader << LineWidth;

            Reader << R << G << B << A;
            FLinearColor FillColor(R, G, B, A);

            FVector LatLong(Lon, Lat, Height);
            CurrentShape = MakeShared<FCircle>(FVector::ZeroVector, LatLong, Radius);
            CurrentShape->SetLineColor(LineColor);
            CurrentShape->SetFillColor(FillColor);
            CurrentShape->SetLineWidth(LineWidth);
            CurrentShape->SetLineHeight(LineWidth);

            break;
        }

        case EDrawingShapeType::Rectangle:
        {
            double RWidth, RHeight, Lat, Lon;
            Reader << RWidth << RHeight << Lat << Lon;

            float R, G, B, A;
            Reader << R << G << B << A;
            FLinearColor LineColor(R, G, B, A);

            int32 LineWidth;
            Reader << LineWidth;

            Reader << R << G << B << A;
            FLinearColor FillColor(R, G, B, A);

            double Rotation;
            Reader << Rotation;

            FVector LatLong(Lon, Lat, Height);
            CurrentShape = MakeShared<FRectangle>(FVector::ZeroVector, LatLong, RWidth, RHeight);
            CurrentShape->SetLineColor(LineColor);
            CurrentShape->SetFillColor(FillColor);
            CurrentShape->SetLineWidth(LineWidth);
            CurrentShape->SetLineHeight(LineWidth);
           


            break;
        }
        case EDrawingShapeType::Polygon:
        {
            int32 NodeCount;
            Reader << NodeCount;

            TArray<FVector> LatLongVerts;
            for (int32 j = 0; j < NodeCount; ++j)
            {
                double Lat, Lon;
                Reader << Lat << Lon;
                LatLongVerts.Add(FVector(Lon, Lat,Height));
            }

            float R, G, B, A;
            Reader << R << G << B << A;
            FLinearColor LineColor(R, G, B, A);

            int32 LineWidth;
            Reader << LineWidth;

            CurrentShape = MakeShared<FPolygon>(LatLongVerts);
            CurrentShape->SetLineColor(LineColor);
            CurrentShape->SetLineWidth(LineWidth);
            CurrentShape->SetLineHeight(LineWidth);

            break;
        }

        case EDrawingShapeType::Line:
        {
            int32 NodeCount;
            Reader << NodeCount;

            TArray<FVector> LatLongPoints;
            for (int32 j = 0; j < NodeCount; ++j)
            {
                double Lat, Lon;
                Reader << Lat << Lon;
                LatLongPoints.Add(FVector(Lon, Lat, Height));
            }

            float R, G, B, A;
            Reader << R << G << B << A;
            FLinearColor LineColor(R, G, B, A);

            int32 LineWidth;
            Reader << LineWidth;

            CurrentShape = MakeShared<FLine>(LatLongPoints);
            CurrentShape->SetLineColor(LineColor);
            CurrentShape->SetLineWidth(LineWidth);
            CurrentShape->SetLineHeight(LineWidth);

            break;
        }



        case EDrawingShapeType::Point:
        {
            int32 pointType, Size;
            //  PointType pointType;

            Reader << pointType << Size;
            PointType Type = static_cast<PointType>(pointType);

            double Lat, Lon;
            Reader << Lat << Lon;

            FVector LatLong(Lon, Lat, Height);
            TSharedPtr<FPoint> Point = MakeShared<FPoint>(FVector::ZeroVector, LatLong);

            Point->SetPointType(Type);
            Point->SetScale(Size);
            CurrentShape = Point;
            break;
        }


        default:
            UE_LOG(LogTemp, Warning, TEXT("Unknown shape type ID: %d"), ShapeTypeRaw);
            break;
        }

        if (CurrentShape.IsValid())
        {
            FTimerHandle TimerHandle;

        /*    GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([this, CurrentShape]()
                {
                }), 2.0f, false);  */
            CurrentShape->Draw(GetWorld());
             OutShapes.Add(CurrentShape);

        }
    }

    return true;
}


float UCustomDrawingReader::ReadHeightFromConfig(const FString& ConfigFilePath)
{
    FString XmlContent;
    if (FFileHelper::LoadFileToString(XmlContent, *ConfigFilePath))
    {
        XmlContent.TrimStartAndEndInline(); // Remove BOM or stray spaces
        FXmlFile XmlFile(XmlContent, EConstructMethod::ConstructFromBuffer);

        if (XmlFile.IsValid())
        {
            FXmlNode* RootNode = XmlFile.GetRootNode();
            if (RootNode && RootNode->GetTag() == TEXT("AppConfig")) // Case-sensitive!
            {
                FXmlNode* HeightNode = RootNode->FindChildNode(TEXT("drawingheight"));
                if (HeightNode)
                {
                    FXmlNode* HeightValueNode = HeightNode->FindChildNode(TEXT("height"));
                    if (HeightValueNode)
                    {
                        FString HeightValueStr = HeightValueNode->GetContent().TrimStartAndEnd();
                        if (HeightValueStr.IsNumeric())
                        {
                            Height = FCString::Atof(*HeightValueStr);
                        }
                    }
                }
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Invalid XML File: %s"), *XmlFile.GetLastError());
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to read file: %s"), *ConfigFilePath);
    }

    return Height > 0.0f ? Height : 500.0f;
}
