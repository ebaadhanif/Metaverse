#include "FShapeFileReader.h"
#include "Misc/Paths.h"
#include "Interfaces/IPluginManager.h"
#include "HAL/PlatformProcess.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"
THIRD_PARTY_INCLUDES_START
#include "ogrsf_frmts.h"
THIRD_PARTY_INCLUDES_END



FShapeFileReader::~FShapeFileReader()
{
}

void FShapeFileReader::LoadDllForGDAL()
{
    FString PluginBinDir = IPluginManager::Get().FindPlugin(TEXT("ShpFileReader"))->GetBaseDir();
    PluginBinDir = FPaths::Combine(PluginBinDir, TEXT("Binaries/Win64"));

    FPlatformProcess::PushDllDirectory(*PluginBinDir);

    // Load all DLLs from that folder manually
    TArray<FString> DllFiles;
    IFileManager::Get().FindFiles(DllFiles, *PluginBinDir, TEXT("*.dll"));

    for (const FString& Dll : DllFiles)
    {
        FString FullPath = FPaths::Combine(PluginBinDir, Dll);
        void* Handle = FPlatformProcess::GetDllHandle(*FullPath);

        if (!Handle)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to load DLL: %s"), *FullPath);
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("Loaded DLL: %s"), *FullPath);
        }
    }

    FPlatformProcess::PopDllDirectory(*PluginBinDir);

    // Now safe to call GDAL functions
    GDALAllRegister();
}

FShapeRawData FShapeFileReader::ReadShapefileRawData(const FString& FilePath)
{


    FShapeRawData Result;
    Result.CollectionName = FPaths::GetBaseFilename(FilePath);

    const std::string UTF8Path = TCHAR_TO_UTF8(*FilePath);
    GDALDataset* poDS = (GDALDataset*)GDALOpenEx(UTF8Path.c_str(), GDAL_OF_VECTOR, nullptr, nullptr, nullptr);
    if (!poDS) return Result;

    OGRLayer* poLayer = poDS->GetLayer(0);
    if (!poLayer) { GDALClose(poDS); return Result; }

    poLayer->ResetReading();
    OGRFeature* poFeature = nullptr;

    while ((poFeature = poLayer->GetNextFeature()) != nullptr)
    {
        TMap<FString, FString> AttributeMap;
        TArray<FVector> GeometryPoints;

        OGRFeatureDefn* poFDefn = poLayer->GetLayerDefn();
        for (int i = 0; i < poFDefn->GetFieldCount(); i++)
        {
            OGRFieldDefn* fieldDefn = poFDefn->GetFieldDefn(i);
            FString Name = UTF8_TO_TCHAR(fieldDefn->GetNameRef());
            switch (fieldDefn->GetType())
            {
            case OFTInteger:
                AttributeMap.Add(Name, FString::FromInt(poFeature->GetFieldAsInteger(i)));
                break;
            case OFTReal:
                AttributeMap.Add(Name, FString::Printf(TEXT("%.12f"), poFeature->GetFieldAsDouble(i)));
                break;
            case OFTString:
            default:
                AttributeMap.Add(Name, UTF8_TO_TCHAR(poFeature->GetFieldAsString(i)));
                break;
            }
        }

        OGRGeometry* poGeometry = poFeature->GetGeometryRef();
        if (poGeometry)
        {
            OGRwkbGeometryType GeoType = wkbFlatten(poGeometry->getGeometryType());

            if (GeoType == wkbPoint)
            {
                OGRPoint* Point = (OGRPoint*)poGeometry;
                GeometryPoints.Add(FVector(Point->getX(), Point->getY(), Point->getZ()));
            }
            else if (GeoType == wkbPolygon)
            {
                OGRPolygon* Polygon = (OGRPolygon*)poGeometry;
                OGRLinearRing* Ring = Polygon->getExteriorRing();
                for (int j = 0; j < Ring->getNumPoints(); j++)
                {
                    GeometryPoints.Add(FVector(Ring->getX(j), Ring->getY(j), 0));
                }
            }
        }

        Result.Attributes.Add(AttributeMap);
        Result.Geometries.Add(GeometryPoints);
        OGRFeature::DestroyFeature(poFeature);
    }

    GDALClose(poDS);
    return Result;
}

