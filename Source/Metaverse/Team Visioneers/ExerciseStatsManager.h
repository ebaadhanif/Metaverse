// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Team SimBridge/EntityManager.h"
#include "../Team SimBridge/EntityBase.h"
#include "ExerciseStatsManager.generated.h"


struct EntityStats
{
	int TotatlEntities;

	int FriendlyEntities;
	int EnemyEntities;
	int NeutralEntities;
	int OtherEntities;

	int AliveEntities;
	int DeadEntities;

	int AirEntities;
	int GroundEntities;
	int SeaEntities;
	int Misiles;

	int FriendlyAliveEntities;
	int FriendlyDeadEntities;
	int EnemyAliveEntities;
	int EnemyDeadEntities;
	int NeutralAliveEntities;
	int NeutralDeadEntities;
	int OtherAliveEntities;
	int OtherDeadEntities;

	int FriendlyAirEntities;
	int FriendlyAirActiveEntities;
	int FriendlyAirDeadEntities;
	int FriendlyGroundEntities;
	int FriendlyGroundActiveEntities;
	int FriendlyGroundDeadEntities;
	int FriendlySeaEntities;
	int FriendlySeaActiveEntities;
	int FriendlySeaDeadEntities;
	int FriendlyMisiles;
	int FriendlyActiveMisiles;
	int FriendlyDeadMisiles;

	int EnemyAirEntities;
	int EnemyAirActiveEntities;
	int EnemyAirDeadEntities;
	int EnemyGroundEntities;
	int EnemyGroundActiveEntities;
	int EnemyGroundDeadEntities;
	int EnemySeaEntities;
	int EnemySeaActiveEntities;
	int EnemySeaDeadEntities;
	int EnemyMisiles;
	int EnemyActiveMisiles;
	int EnemyDeadMisiles;

	int NeutralAirActiveEntities;
	int NeutralAirDeadEntities;
	int NeutralGroundEntities;
	int NeutralAirEntities;
	int NeutralGroundActiveEntities;
	int NeutralGroundDeadEntities;
	int NeutralSeaEntities;
	int NeutralSeaActiveEntities;
	int NeutralSeaDeadEntities;
	int NeutralMisiles;
	int NeutralActiveMisiles;
	int NeutralDeadMisiles;

	int OtherAirEntities;
	int OtherAirActiveEntities;
	int OtherAirDeadEntities;
	int OtherGroundEntities;
	int OtherGroundActiveEntities;
	int OtherGroundDeadEntities;
	int OtherSeaEntities;
	int OtherSeaActiveEntities;
	int OtherSeaDeadEntities;
	int OtherMisiles;
	int OtherActiveMisiles;
	int OtherDeadMisiles;








	EntityStats() :
	 TotatlEntities(0),



	 FriendlyEntities(0),
	 EnemyEntities(0),
	 NeutralEntities(0),
	 OtherEntities(0),

     AliveEntities(0),
	 DeadEntities(0),


	 AirEntities(0),
	 GroundEntities(0),
	 SeaEntities(0),
	 Misiles(0),


	 FriendlyAliveEntities(0),
	 FriendlyDeadEntities(0),
	 EnemyAliveEntities(0),
	 EnemyDeadEntities(0),
	 NeutralAliveEntities(0),
	 NeutralDeadEntities(0),
	 OtherAliveEntities(0),
	 OtherDeadEntities(0),


	 FriendlyAirEntities(0),
	 FriendlyAirActiveEntities(0),
	 FriendlyAirDeadEntities(0),
	 FriendlyGroundEntities(0),
	 FriendlyGroundActiveEntities(0),
	 FriendlyGroundDeadEntities(0),
	 FriendlySeaEntities(0),
	 FriendlySeaActiveEntities(0),
	 FriendlySeaDeadEntities(0),
	 FriendlyMisiles(0),
	 FriendlyActiveMisiles(0),
	 FriendlyDeadMisiles(0),

	 EnemyAirEntities(0),
	 EnemyAirActiveEntities(0),
	 EnemyAirDeadEntities(0),
	 EnemyGroundEntities(0),
	 EnemyGroundActiveEntities(0),
	 EnemyGroundDeadEntities(0),
	 EnemySeaEntities(0),
	 EnemySeaActiveEntities(0),
	 EnemySeaDeadEntities(0),
	 EnemyMisiles(0),
	 EnemyActiveMisiles(0),
	 EnemyDeadMisiles(0),

	 NeutralAirActiveEntities(0),
	 NeutralAirDeadEntities(0),
	 NeutralGroundEntities(0),
	 NeutralAirEntities(0),
	 NeutralGroundActiveEntities(0),
	 NeutralGroundDeadEntities(0),
	 NeutralSeaEntities(0),
	 NeutralSeaActiveEntities(0),
	 NeutralSeaDeadEntities(0),
	 NeutralMisiles(0),
	 NeutralActiveMisiles(0),
	 NeutralDeadMisiles(0),

	 OtherAirEntities(0),
	 OtherAirActiveEntities(0),
	 OtherAirDeadEntities(0),
	 OtherGroundEntities(0),
	 OtherGroundActiveEntities(0),
	 OtherGroundDeadEntities(0),
	 OtherSeaEntities(0),
	 OtherSeaActiveEntities(0),
	 OtherSeaDeadEntities(0),
	 OtherMisiles(0),
	 OtherActiveMisiles(0),
	 OtherDeadMisiles(0)
	{}

	 EntityStats(
     int TotatlEntities,	 
		 
     int FriendlyEntities,
	 int EnemyEntities,
	 int NeutralEntities,
	 int OtherEntities,

	 int AliveEntities,
	 int DeadEntities,

	 int AirEntities,
	 int GroundEntities,
	 int SeaEntities,
	 int Misiles,

     int FriendlyAliveEntities,
	 int FriendlyDeadEntities,
	 int EnemyAliveEntities,
	 int EnemyDeadEntities,
	 int NeutralAliveEntities,
	 int NeutralDeadEntities,
	 int OtherAliveEntities,
	 int OtherDeadEntities,

	 int FriendlyAirEntities,
	 int FriendlyAirActiveEntities,
	 int FriendlyAirDeadEntities,
	 int FriendlyGroundEntities,
	 int FriendlyGroundActiveEntities,
	 int FriendlyGroundDeadEntities,
	 int FriendlySeaEntities,
	 int FriendlySeaActiveEntities,
	 int FriendlySeaDeadEntities,
	 int FriendlyMisiles,
	 int FriendlyActiveMisiles,
	 int FriendlyDeadMisiles,

	 int EnemyAirEntities,
	 int EnemyAirActiveEntities,
	 int EnemyAirDeadEntities,
	 int EnemyGroundEntities,
	 int EnemyGroundActiveEntities,
	 int EnemyGroundDeadEntities,
	 int EnemySeaEntities,
	 int EnemySeaActiveEntities,
	 int EnemySeaDeadEntities,
	 int EnemyMisiles,
	 int EnemyActiveMisiles,
	 int EnemyDeadMisiles,

	 int NeutralAirActiveEntities,
	 int NeutralAirDeadEntities,
	 int NeutralGroundEntities,
	 int NeutralAirEntities,
	 int NeutralGroundActiveEntities,
	 int NeutralGroundDeadEntities,
	 int NeutralSeaEntities,
	 int NeutralSeaActiveEntities,
	 int NeutralSeaDeadEntities,
	 int NeutralMisiles,
	 int NeutralActiveMisiles,
	 int NeutralDeadMisiles,

	 int OtherAirEntities,
	 int OtherAirActiveEntities,
	 int OtherAirDeadEntities,
	 int OtherGroundEntities,
	 int OtherGroundActiveEntities,
	 int OtherGroundDeadEntities,
	 int OtherSeaEntities,
	 int OtherSeaActiveEntities,
	 int OtherSeaDeadEntities,
	 int OtherMisiles,
	 int OtherActiveMisiles,
	 int OtherDeadMisiles
	 ) :
	     TotatlEntities(TotatlEntities),
		 FriendlyEntities(FriendlyEntities),
		 EnemyEntities(EnemyEntities),
		 NeutralEntities(NeutralEntities),
		 OtherEntities(OtherEntities),
		 AliveEntities(AliveEntities),
		 DeadEntities(DeadEntities),
		 AirEntities(AirEntities),
		 GroundEntities(GroundEntities),
		 SeaEntities(SeaEntities),
		 Misiles(Misiles),

		 FriendlyAliveEntities(FriendlyAliveEntities),
		 FriendlyDeadEntities(FriendlyDeadEntities),
		 EnemyAliveEntities(EnemyAliveEntities),
		 EnemyDeadEntities(EnemyDeadEntities),
		 NeutralAliveEntities(NeutralAliveEntities),
		 NeutralDeadEntities(NeutralDeadEntities),
		 OtherAliveEntities(OtherAliveEntities),
		 OtherDeadEntities(OtherDeadEntities),

		 FriendlyAirEntities(FriendlyAirEntities),
		 FriendlyAirActiveEntities(FriendlyAirActiveEntities),
		 FriendlyAirDeadEntities(FriendlyAirDeadEntities),
		 FriendlyGroundEntities(FriendlyGroundEntities),
		 FriendlyGroundActiveEntities(FriendlyGroundActiveEntities),
		 FriendlyGroundDeadEntities(FriendlyGroundDeadEntities),
		 FriendlySeaEntities(FriendlySeaEntities),
		 FriendlySeaActiveEntities(FriendlySeaActiveEntities),
		 FriendlySeaDeadEntities(FriendlySeaDeadEntities),
		 FriendlyMisiles(FriendlyMisiles),
		 FriendlyActiveMisiles(FriendlyActiveMisiles),
		 FriendlyDeadMisiles(FriendlyDeadMisiles),
		 EnemyAirEntities(EnemyAirEntities),
		 EnemyAirActiveEntities(EnemyAirActiveEntities),
		 EnemyAirDeadEntities(EnemyAirDeadEntities),
		 EnemyGroundEntities(EnemyGroundEntities),
		 EnemyGroundActiveEntities(EnemyGroundActiveEntities),
		 EnemyGroundDeadEntities(EnemyGroundDeadEntities),
		 EnemySeaEntities(EnemySeaEntities),
		 EnemySeaActiveEntities(EnemySeaActiveEntities),
		 EnemySeaDeadEntities(EnemySeaDeadEntities),
		 EnemyMisiles(EnemyMisiles),
		 EnemyActiveMisiles(EnemyActiveMisiles),
		 EnemyDeadMisiles(EnemyDeadMisiles),
		 NeutralAirActiveEntities(NeutralAirActiveEntities),
		 NeutralAirDeadEntities(NeutralAirDeadEntities),
		 NeutralGroundEntities(NeutralGroundEntities),
		 NeutralAirEntities(NeutralAirEntities),
		 NeutralGroundActiveEntities(NeutralGroundActiveEntities),
		 NeutralGroundDeadEntities(NeutralGroundDeadEntities),
		 NeutralSeaEntities(NeutralSeaEntities),
		 NeutralSeaActiveEntities(NeutralSeaActiveEntities),
		 NeutralSeaDeadEntities(NeutralSeaDeadEntities),
		 NeutralMisiles(NeutralMisiles),
		 NeutralActiveMisiles(NeutralActiveMisiles),
		 NeutralDeadMisiles(NeutralDeadMisiles),
		 OtherAirEntities(OtherAirEntities),
		 OtherAirActiveEntities(OtherAirActiveEntities),
		 OtherAirDeadEntities(OtherAirDeadEntities),
		 OtherGroundEntities(OtherGroundEntities),
		 OtherGroundActiveEntities(OtherGroundActiveEntities),
		 OtherGroundDeadEntities(OtherGroundDeadEntities),
		 OtherSeaEntities(OtherSeaEntities),
		 OtherSeaActiveEntities(OtherSeaActiveEntities),
		 OtherSeaDeadEntities(OtherSeaDeadEntities),
		 OtherMisiles(OtherMisiles),
		 OtherActiveMisiles(OtherActiveMisiles),
		 OtherDeadMisiles(OtherDeadMisiles)
	 {};


	void Reset() 
	{
		TotatlEntities = 0;
		FriendlyEntities = 0;
		EnemyEntities = 0;
		NeutralEntities = 0;
		OtherEntities = 0;
		AliveEntities = 0;
		DeadEntities = 0;
		AirEntities = 0;
		GroundEntities = 0;
		SeaEntities = 0;
		Misiles = 0;

		FriendlyAliveEntities = 0;
		FriendlyDeadEntities = 0;
		EnemyAliveEntities = 0;
		EnemyDeadEntities = 0;
		NeutralAliveEntities = 0;
		NeutralDeadEntities = 0;
		OtherAliveEntities = 0;
		OtherDeadEntities = 0;

		FriendlyAirEntities = 0;
		FriendlyAirActiveEntities = 0;
		FriendlyAirDeadEntities = 0;
		FriendlyGroundEntities = 0;
		FriendlyGroundActiveEntities = 0;
		FriendlyGroundDeadEntities = 0;
		FriendlySeaEntities = 0;
		FriendlySeaActiveEntities = 0;
		FriendlySeaDeadEntities = 0;
		FriendlyMisiles = 0;
		FriendlyActiveMisiles = 0;
		FriendlyDeadMisiles = 0;
		EnemyAirEntities = 0;
		EnemyAirActiveEntities = 0;
		EnemyAirDeadEntities = 0;
		EnemyGroundEntities = 0;
		EnemyGroundActiveEntities = 0;
		EnemyGroundDeadEntities = 0;
		EnemySeaEntities = 0;
		EnemySeaActiveEntities = 0;
		EnemySeaDeadEntities = 0;
		EnemyMisiles = 0;
		EnemyActiveMisiles = 0;
		EnemyDeadMisiles = 0;
		NeutralAirActiveEntities = 0;
		NeutralAirDeadEntities = 0;
		NeutralGroundEntities = 0;
		NeutralAirEntities = 0;
		NeutralGroundActiveEntities = 0;
		NeutralGroundDeadEntities = 0;
		NeutralSeaEntities = 0;
		NeutralSeaActiveEntities = 0;
		NeutralSeaDeadEntities = 0;
		NeutralMisiles = 0;
		NeutralActiveMisiles = 0;
		NeutralDeadMisiles = 0;
		OtherAirEntities = 0;
		OtherAirActiveEntities = 0;
		OtherAirDeadEntities = 0;
		OtherGroundEntities = 0;
		OtherGroundActiveEntities = 0;
		OtherGroundDeadEntities = 0;
		OtherSeaEntities = 0;
		OtherSeaActiveEntities = 0;
		OtherSeaDeadEntities = 0;
		OtherMisiles = 0;
		OtherActiveMisiles = 0;
		OtherDeadMisiles = 0;
	}
};

UCLASS()
class METAVERSE_API AExerciseStatsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	//void SetEntityStats(int InTotal, int InAir, int InGround, int InSea, int InFriendlyAir, int InEnemyAir, int InOtherAir, int InFriendlyActiveAir, int InFriendlyDeadAir, int InEnemyActiveAir, int InEnemyDeadAir, int InMisiles);
	EntityStats GetEntityStats();
	// Sets default values for this actor's properties
	AExerciseStatsManager();
	static AExerciseStatsManager* GetInstance();

	bool IsAirEntity(AEntityBase* Entity);
	bool IsGroundEntity(AEntityBase* Entity);
	bool IsSeaEntity(AEntityBase* Entity);
	bool IsMissileEntity(AEntityBase* Entity);
	bool IsAliveEntity(AEntityBase* Entity);
	bool IsDeadEntity(AEntityBase* Entity);
	bool IsFriendlyEntity(AEntityBase* Entity);
	bool IsEnemyEntity(AEntityBase* Entity);
	bool IsNeutralEntity(AEntityBase* Entity);
	bool IsOtherEntity(AEntityBase* Entity);
	


	void UpdateStatsData();

	float ElapsedTime = 0;

private:
	static AExerciseStatsManager* Instance;
	EntityStats StatsData;


};
