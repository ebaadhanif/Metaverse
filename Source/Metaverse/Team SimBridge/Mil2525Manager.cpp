// Fill out your copyright notice in the Description page of Project Settings.


#include "Mil2525Manager.h"
#include "AppConstEnumStruct.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Modules/ModuleManager.h"
#include "Misc/FileHelper.h"
#include "Windows/WindowsHWrapper.h"

Mil2525Manager* Mil2525Manager::m_pMil2525ManagerInstance = nullptr;
Mil2525Manager* Mil2525Manager::GetMil2525ManagerInstance()
{
	if (m_pMil2525ManagerInstance == nullptr)
	{
		m_pMil2525ManagerInstance = new Mil2525Manager();
	}
	return m_pMil2525ManagerInstance;
}

Mil2525Manager::Mil2525Manager()
{
	LoadFileData();
	BillbordMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/Billboard/M_BillboardMat.M_BillboardMat"));
}

Mil2525Manager::~Mil2525Manager()
{
}
void Mil2525Manager::LoadFileData()
{
	FString FullPath = FPaths::ProjectContentDir() + "Archive/ObjectTypesEnum.csv";

	FString FileContent;
	//check file exist
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FullPath))
	{
		return;
	}

	//Load File into string
	if (!FFileHelper::LoadFileToString(FileContent, *FullPath))
	{
		return;
	}

	//split file into lines
	TArray<FString>lines;
	FileContent.ParseIntoArrayLines(lines);

	//skip header line
	bool bIsFirstline = true;

	for (const FString& line : lines)
	{
		if (bIsFirstline)
		{
			bIsFirstline = false;
			continue;
		}

		//Split line into Columns
		TArray <FString>Columns;
		line.ParseIntoArray(Columns, TEXT(","), true);

		//ensure correct number of columns
		if (Columns.Num() != 11)
		{
			continue;
		}

		FEntityType EntityType;
		FString ObjectType = Columns[9];

		auto ParseToUint8 = [](const FString& Str)->uint8
			{
				int32 Value = FCString::Atoi(*Str);
				return static_cast<uint8>(Value);
			};
		EntityType.entiyKind = ParseToUint8(Columns[2]);
		EntityType.domain = ParseToUint8(Columns[3]);
		int32 tempValue = FCString::Atoi(*Columns[4]);
		EntityType.country = static_cast<uint16>(tempValue);
		EntityType.category = ParseToUint8(Columns[5]);
		EntityType.subcategory = ParseToUint8(Columns[6]);
		EntityType.specific = ParseToUint8(Columns[7]);
		EntityType.extra = ParseToUint8(Columns[8]);
		//Add To Map
		ObjectTypeMap.Add(EntityType, ObjectType);
	}

}

UTexture2D* Mil2525Manager::LoadMil2525Sprite(FEntityType Entity, EForceType Force)
{
	FString FolderName;
	if (ObjectTypeMap.Find(Entity) == nullptr)
	{
		FolderName = GetUnknownEntity(Entity);
	}
	else
	{
		FolderName = ObjectTypeMap[Entity];
	}

	FolderName = FolderName.TrimEnd();
	FString ForceImage = "";

	switch (Force)
	{
	case EForceType::FRIENDLY:
	{
		ForceImage = "Blue.png";
		break;
	}

	case EForceType::NEUTRAL:
	{
		ForceImage = "Neutral.png";
		break;
	}
	case EForceType::OTHERS:
	{
		ForceImage = "Other.png";
		break;
	}
	case EForceType::OPPOSING:
	{
		ForceImage = "Red.png";
		break;
	}
	default: {
		ForceImage = "Blue.png";
		break;
	}
	}

	FString FullPath = FPaths::ProjectContentDir() + "Archive/MIL2525" + "/" + FolderName + "/" + ForceImage;

	TArray<uint8> FileData;
	if (!FFileHelper::LoadFileToArray(FileData, *FullPath))
	{
		return nullptr;
	}
	IImageWrapperModule& ImgWrapperMod = FModuleManager::LoadModuleChecked <IImageWrapperModule>(TEXT("ImageWrapper"));
	TSharedPtr<IImageWrapper> Wrapper = ImgWrapperMod.CreateImageWrapper(EImageFormat::PNG);

	if (Wrapper.IsValid() && Wrapper->SetCompressed(FileData.GetData(), FileData.Num())) {

		TArray<uint8> RawData;
		if (Wrapper->GetRaw(ERGBFormat::BGRA, 8, RawData)) {

			UTexture2D* Tex = UTexture2D::CreateTransient(Wrapper->GetWidth(), Wrapper->GetHeight(), PF_B8G8R8A8);
			if (!Tex) return nullptr;

			void* TextureData = Tex->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			FMemory::Memcpy(TextureData, RawData.GetData(), RawData.Num());

			Tex->GetPlatformData()->Mips[0].BulkData.Unlock();
			Tex->UpdateResource();
			return Tex;
		}
	}
	return nullptr;
}

UMaterialInstanceDynamic* Mil2525Manager::SetupMil2525Material(FEntityType Entity, EForceType Force)
{
	UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(BillbordMaterial, nullptr);
	DynamicMaterial->SetTextureParameterValue("BillboardTexture", LoadMil2525Sprite(Entity, Force));
	return DynamicMaterial;
}

void Mil2525Manager::UpdateMil2525Symbol(UMaterialInstanceDynamic* DynamicMaterial, ELocalHealth Health)
{
	switch (Health)
	{
	case ELocalHealth::NO_DAMAGE:
	{
		DynamicMaterial->SetScalarParameterValue("Destroyed_Visible", 0);
		DynamicMaterial->SetScalarParameterValue("Malfunction_Visible", 0);
		break;
	}
	case ELocalHealth::MINOR_DAMAGE:
	case ELocalHealth::MEDIUM_DAMAGE:
	case ELocalHealth::MAJOR_DAMAGE:
	{
		DynamicMaterial->SetScalarParameterValue("Destroyed_Visible", 0);
		DynamicMaterial->SetScalarParameterValue("Malfunction_Visible", 1);
		break;
	}
	case ELocalHealth::DESTROYED:
	{
		DynamicMaterial->SetScalarParameterValue("Destroyed_Visible", 1);
		DynamicMaterial->SetScalarParameterValue("Malfunction_Visible", 0);
		break;
	}
	default:
	{
		DynamicMaterial->SetScalarParameterValue("Destroyed_Visible", 0);
		DynamicMaterial->SetScalarParameterValue("Malfunction_Visible", 0);
	}
	}
}




float Mil2525Manager::SetMil2525Height(float Height)
{
	Height = FMath::Clamp(Height, 0, 4000);
	if (Height < 4000) {

		Height = Height + 500.0f;
	}
	else
	{
		Height = 0;

	}

	return Height;
}
FString Mil2525Manager::GetUnknownEntity(FEntityType entityType)
{
	FString folderName = "AIRLINER";
	switch (entityType.entiyKind)
	{
	case 1: //platform
	{
		switch (entityType.domain)
		{
		case 1: //land
		{
			folderName = "GENERAL_VEHICLES";
			break;
		}
		case 2: //air
		{
			folderName = "AIRLINER";
			break;

		}
		case 3: //surface
		{
			folderName = "SURFACE_TANKER";
			break;

		}
		}
		break;
	}
	case 2: //Munition
	{
		folderName = "MISSILE";
		break;

	}
	case 3: //Lifeform
	{
		folderName = "LIFE_FORM";
		break;

	}
	case 5://Cultural Feature
	{
		folderName = "CULTURAL_FEATURES";
		break;
	}
	case 8: //Expandables
	{
		folderName = "EXPENDABLES";
		break;
	}
	case 9: //Sensor
	{
		folderName = "SENSOR";
		break;
	}
	}
	return folderName;
}
