#pragma once
#include "CoreMinimal.h"



struct FShapeRawData
{
	FString CollectionName;
	TArray<TMap<FString, FString>> Attributes;
	TArray<TArray<FVector>> Geometries;
};

class SHPFILEREADER_API FShapeFileReader
{
public:
	//FShapeFileReader();
	~FShapeFileReader();


public:
	static void LoadDllForGDAL();

	static FShapeRawData ReadShapefileRawData(const FString& FilePath);


};



