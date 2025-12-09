// Fill out your copyright notice in the Description page of Project Settings.


#include "RemoteEntityFactory.h"
#include "Kismet/GameplayStatics.h"


RemoteEntityFactory::RemoteEntityFactory()
{
	LoadObjectTypesEnumFile();
}

RemoteEntityFactory* RemoteEntityFactory::m_pRemoteEntityFactoryInstance = nullptr;

RemoteEntityFactory* RemoteEntityFactory::GetRemoteEntityFactoryInstance()
{
	if (m_pRemoteEntityFactoryInstance == nullptr)
	{
		m_pRemoteEntityFactoryInstance = new RemoteEntityFactory();
	}
	return m_pRemoteEntityFactoryInstance;
}

AEntityBase* RemoteEntityFactory::GetRemoteEntityObj(FEntityType entityType)
{
	AEntityBase* pEntitybase = nullptr;
	ERemoteEntityType objectType;
	//if objectType doesnt exist in map return nullpr
	if (ObjectTypeMap.Find(entityType) == nullptr)
	{
		objectType = GetUnknownEntity(entityType);
	}
	else
	{
		int32 value = static_cast<int32>(ObjectTypeMap[entityType]);
		objectType = static_cast<ERemoteEntityType>(value);
	}


	switch (objectType)
	{
	case ERemoteEntityType::ARMORED_VEHICLE:
	{
		pEntitybase = worldPtr->SpawnActor<ARemoteArmoredVehicle>(ARemoteArmoredVehicle::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		break;
	}
	case ERemoteEntityType::FIXEDWING_AIRCRAFT:
	{
		pEntitybase = worldPtr->SpawnActor<ARemoteFixedWingAircraft>(ARemoteFixedWingAircraft::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		break;
	}
	case ERemoteEntityType::GENERAL_VEHICLE:
	{
		pEntitybase = worldPtr->SpawnActor<ARemoteGeneralVehicle>(ARemoteGeneralVehicle::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		break;
	}
	case ERemoteEntityType::SHIPS:
	{
		pEntitybase = worldPtr->SpawnActor<ARemoteShips>(ARemoteShips::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		break;
	}
	case ERemoteEntityType::ROTORCRAFT:
	{
		pEntitybase = worldPtr->SpawnActor<ARemoteRotorcraft>(ARemoteRotorcraft::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		break;
	}
	case ERemoteEntityType::RADAR:
	{
		pEntitybase = worldPtr->SpawnActor<ARemoteRadar>(ARemoteRadar::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		break;
	}
	case ERemoteEntityType::MISSILE:
	{
		pEntitybase = worldPtr->SpawnActor<ARemoteMissile>(ARemoteMissile::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		break;
	}
	case ERemoteEntityType::CHAFF:
	{
		pEntitybase = worldPtr->SpawnActor<ARemoteChaff>(ARemoteChaff::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		break;
	}
	case ERemoteEntityType::FLARE:
	{
		pEntitybase = worldPtr->SpawnActor<ARemoteFlare>(ARemoteFlare::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		break;
	}
	case ERemoteEntityType::HUMAN:
	{
		pEntitybase = worldPtr->SpawnActor<ARemoteHuman>(ARemoteHuman::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		break;
	}
	case ERemoteEntityType::ANIMAL:
	{
		pEntitybase = worldPtr->SpawnActor<ARemoteAnimal>(ARemoteAnimal::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		break;
	}
	case ERemoteEntityType::STRUCTURE:
	{
		pEntitybase = worldPtr->SpawnActor<ARemoteStructure>(ARemoteStructure::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		break;
	}
	case ERemoteEntityType::OTHER_CULTURE_FEATURE:
	{
		pEntitybase = worldPtr->SpawnActor<ARemoteOtherCultureFeature>(ARemoteOtherCultureFeature::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		break;
	}
	case ERemoteEntityType::VEGETATION:
	{
		pEntitybase = worldPtr->SpawnActor<ARemoteVegetation>(ARemoteVegetation::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		break;
	}
	case ERemoteEntityType::SHELL:
	{
		pEntitybase = worldPtr->SpawnActor<ARemoteShell>(ARemoteShell::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		break;
	}
	case ERemoteEntityType::BOMB:
	{
		pEntitybase = worldPtr->SpawnActor<ARemoteBomb>(ARemoteBomb::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		break;
	}
	case ERemoteEntityType::MUNITION_LAUNCHER:
	{
		pEntitybase = worldPtr->SpawnActor<ARemoteMunitionLauncher>(ARemoteMunitionLauncher::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		break;
	}
	default:
	{
		pEntitybase = worldPtr->SpawnActor<ARemoteFixedWingAircraft>(ARemoteFixedWingAircraft::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		break;
	}

	}
	return pEntitybase;
}

void RemoteEntityFactory::SetWorld(UWorld* world)
{
	worldPtr = world;
}

void RemoteEntityFactory::LoadObjectTypesEnumFile()
{
	FString FullPath = FPaths::ProjectContentDir() + "Archive/ObjectTypesEnum.csv";
	//FString FullPath = "C:/PAF_Metaverse_GIT/PAFMetaVerse/Content/Archive/ObjectTypesEnum.csv";// FPaths::ProjectDir();// + TEXT("Content/Archive/ObjectTypesEnum.csv");

	FString FileContent;
	//check file exist
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FullPath))
	{
		return;
	}

	//Load File into string
	if (!FFileHelper::LoadFileToString(FileContent, *FullPath))
	{
		int a = 0;
		//return;
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
		int ObjectType = FCString::Atoi(*Columns[1]);
		int RadarRanges = FCString::Atoi(*Columns[10]);

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
		EntityRangeMap.Add(EntityType, RadarRanges);
	}

	int num;
	num = ObjectTypeMap.Num();




}

int RemoteEntityFactory::GetRadarRange(FEntityType entityType)
{
	if (EntityRangeMap.Find(entityType) != nullptr)
	{
		return EntityRangeMap[entityType];
	}
	return 0;
}

//ERemoteEntityType RemoteEntityFactory::GetMissingRemoteEntityType(FEntityType entityType)
//{
//	switch (entityType.entiyKind)
//	{
//	case 1: //platform entites
//	{
//		switch (entityType.domain)
//		{
//		case 1: //ground
//		{
//			switch (entityType.category)
//			{
//			case 1:
//			{
//				return ERemoteEntityType::ARMORED_VEHICLE;
//				break;
//			}
//			case 4:
//			{
//				return ERemoteEntityType::ARMORED_VEHICLE;
//				break;
//			}
//
//				
//			}
//			break;
//		
//			
//		}
//		case 2://air
//		{
//			switch (entityType.category)
//			{
//			case 1: //fixed wing
//			{
//				return ERemoteEntityType::FIXEDWING_AIRCRAFT;
//				break;
//			}
//			case 2: //rotorcraft
//			{
//				return ERemoteEntityType::ROTORCRAFT;
//				break;
//			}
//			default:
//			{
//				return ERemoteEntityType::FIXEDWING_AIRCRAFT;
//			}
//			}
//			break;
//		}
//
//
//		default:
//			break;
//		}
//		break;
//	}
//
//	default:
//		break;
//	}
//}

ERemoteEntityType RemoteEntityFactory::GetUnknownEntity(FEntityType entityType)
{
	ERemoteEntityType tempEntityType = ERemoteEntityType::FIXEDWING_AIRCRAFT;
	switch (entityType.entiyKind)
	{
	case 1: //platform
	{
		switch (entityType.domain)
		{
		case 1: //land
		{
			tempEntityType = ERemoteEntityType::GENERAL_VEHICLE;
			break;

		}
		case 2: //air
		{
			tempEntityType = ERemoteEntityType::FIXEDWING_AIRCRAFT;
			break;

		}
		case 3: //surface
		{
			tempEntityType = ERemoteEntityType::SHIPS;
			break;

		}
		}
		break;
	}

	case 2: //Munition
	{
		tempEntityType = ERemoteEntityType::MISSILE;
		break;
	}
	case 3: //lifeform
	{
		tempEntityType = ERemoteEntityType::HUMAN;
		break;
	}
	case 5://Cultural Feature
	{
		tempEntityType = ERemoteEntityType::STRUCTURE;
		break;

	}
	case 8: //Expandables
	{
		tempEntityType = ERemoteEntityType::FLARE;
		break;
	}
	case 9: //Sensor
	{
		tempEntityType = ERemoteEntityType::RADAR;
		break;
	}
	}
	return tempEntityType;
}

RemoteEntityFactory::~RemoteEntityFactory()
{

}
