// Fill out your copyright notice in the Description page of Project Settings.


#include "ExerciseStatsManager.h"

AExerciseStatsManager* AExerciseStatsManager::Instance = nullptr;


// Sets default values
AExerciseStatsManager::AExerciseStatsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatsData = EntityStats(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);

}

// Called when the game starts or when spawned
void AExerciseStatsManager::BeginPlay()
{
	Super::BeginPlay();

	if (Instance == nullptr)
	{
		Instance = this;
	}
	
}

//void AExerciseStatsManager::SetEntityStats(int InTotal, int InAir, int InGround, int InSea, int InFriendlyAir, int InEnemyAir, int InOtherAir, int InFriendlyActiveAir, int InFriendlyDeadAir, int InEnemyActiveAir, int InEnemyDeadAir, int InMisiles)
//{
//	StatsData.TotatlEntities = InTotal;
//	StatsData.AirEntities = InAir;
//	StatsData.GroundEntities = InGround;
//	StatsData.SeaEntities = InSea;
//	StatsData.FriendlyAirEntities = InFriendlyAir;
//	StatsData.EnemyAirEntities = InEnemyAir;
//	StatsData.OtherAirEntities = InOtherAir;
//	StatsData.FriendlyActiveAirEntities = InFriendlyActiveAir;
//	StatsData.FriendlyDeadAirEntities = InFriendlyDeadAir;
//	StatsData.EnemyActiveAirEntities = InEnemyActiveAir;
//	StatsData.EnemyDeadAirEntities = InEnemyDeadAir;
//	StatsData.Misiles = InMisiles;
//	
//
//}

EntityStats AExerciseStatsManager::GetEntityStats()
{
	return StatsData;
}

// Called every frame
void AExerciseStatsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedTime += DeltaTime;

	if (ElapsedTime > 1) {
		FMath::RoundToInt(1.0f / DeltaTime);
		ElapsedTime = 0;
		UpdateStatsData();
	}


}









AExerciseStatsManager* AExerciseStatsManager::GetInstance()
{
	return Instance;
}

bool AExerciseStatsManager::IsAirEntity(AEntityBase* Entity)
{
	return 
		Entity->GetRemoteEntityType() == ERemoteEntityType::FIXEDWING_AIRCRAFT || 
		Entity->GetRemoteEntityType() == ERemoteEntityType::ROTORCRAFT;
}

bool AExerciseStatsManager::IsGroundEntity(AEntityBase* Entity)
{
	return
		Entity->GetRemoteEntityType() == ERemoteEntityType::ARMORED_VEHICLE ||
		Entity->GetRemoteEntityType() == ERemoteEntityType::GENERAL_VEHICLE ||
		Entity->GetRemoteEntityType() == ERemoteEntityType::HUMAN ||
		Entity->GetRemoteEntityType() == ERemoteEntityType::ANIMAL ||
		Entity->GetRemoteEntityType() == ERemoteEntityType::STRUCTURE ||
		Entity->GetRemoteEntityType() == ERemoteEntityType::OTHER_CULTURE_FEATURE ||
		Entity->GetRemoteEntityType() == ERemoteEntityType::VEGETATION ||
		Entity->GetRemoteEntityType() == ERemoteEntityType::RADAR ||
		Entity->GetRemoteEntityType() == ERemoteEntityType::MUNITION_LAUNCHER;

}

bool AExerciseStatsManager::IsSeaEntity(AEntityBase* Entity)
{
	return 
		Entity->GetRemoteEntityType() == ERemoteEntityType::SHIPS;

		
}

bool AExerciseStatsManager::IsMissileEntity(AEntityBase* Entity)
{
	return
		Entity->GetRemoteEntityType() == ERemoteEntityType::MISSILE;


}




bool AExerciseStatsManager::IsAliveEntity(AEntityBase* Entity)
{
	return Entity->GetHealth() == ELocalHealth::NO_DAMAGE;
}

bool AExerciseStatsManager::IsDeadEntity(AEntityBase* Entity)
{
	return Entity->GetHealth() == ELocalHealth::DESTROYED;
}

bool AExerciseStatsManager::IsFriendlyEntity(AEntityBase* Entity)
{
	return Entity->GetForceType() == EForceType::FRIENDLY;
}

bool AExerciseStatsManager::IsEnemyEntity(AEntityBase* Entity)
{
	return Entity->GetForceType() == EForceType::OPPOSING;
}

bool AExerciseStatsManager::IsNeutralEntity(AEntityBase* Entity)
{
	return Entity->GetForceType() == EForceType::NEUTRAL;
}

bool AExerciseStatsManager::IsOtherEntity(AEntityBase* Entity)
{
	return Entity->GetForceType() == EForceType::OTHERS;
}








void AExerciseStatsManager::UpdateStatsData()
{




	StatsData.Reset();

	TArray<AEntityBase*> Entities = EntityManager::GetEntityManagerInstance()->GetEntityList();
	for (AEntityBase* Entity : Entities)
	{
		StatsData.TotatlEntities += 1;
		if (IsAliveEntity(Entity)) StatsData.AliveEntities++;
		if (IsDeadEntity(Entity)) StatsData.DeadEntities++;
	
		if (IsFriendlyEntity(Entity)) StatsData.FriendlyEntities++;
		if (IsEnemyEntity(Entity)) StatsData.EnemyEntities++;
		if (IsNeutralEntity(Entity)) StatsData.NeutralEntities++;
		if (IsOtherEntity(Entity)) StatsData.OtherEntities++;

		if (IsAirEntity(Entity)) StatsData.AirEntities++;
		if (IsGroundEntity(Entity)) StatsData.GroundEntities++;
		if (IsSeaEntity(Entity)) StatsData.SeaEntities++;
		if (IsMissileEntity(Entity)) StatsData.Misiles++;

		if (IsFriendlyEntity(Entity) && IsAliveEntity(Entity)) StatsData.FriendlyAliveEntities++;
		if (IsEnemyEntity(Entity) && IsAliveEntity(Entity)) StatsData.EnemyAliveEntities++;
		if (IsNeutralEntity(Entity) && IsAliveEntity(Entity)) StatsData.NeutralAliveEntities++;
		if (IsOtherEntity(Entity) && IsAliveEntity(Entity)) StatsData.OtherAliveEntities++;

		if (IsFriendlyEntity(Entity) && IsDeadEntity(Entity)) StatsData.FriendlyDeadEntities++;
		if (IsEnemyEntity(Entity) && IsDeadEntity(Entity)) StatsData.EnemyDeadEntities++;
		if (IsNeutralEntity(Entity) && IsDeadEntity(Entity)) StatsData.NeutralDeadEntities++;
		if (IsOtherEntity(Entity) && IsDeadEntity(Entity)) StatsData.OtherDeadEntities++;


		if (IsFriendlyEntity(Entity) && IsAirEntity(Entity)) StatsData.FriendlyAirEntities++;
		if (IsFriendlyEntity(Entity) && IsGroundEntity(Entity)) StatsData.FriendlyGroundEntities++;
		if (IsFriendlyEntity(Entity) && IsSeaEntity(Entity)) StatsData.FriendlySeaEntities++;
		if (IsFriendlyEntity(Entity) && IsMissileEntity(Entity)) StatsData.FriendlyMisiles++;


		if (IsFriendlyEntity(Entity) && IsAirEntity(Entity) && IsAliveEntity(Entity)) StatsData.FriendlyAirActiveEntities++;
		if (IsFriendlyEntity(Entity) && IsGroundEntity(Entity) && IsAliveEntity(Entity)) StatsData.FriendlyGroundActiveEntities++;
		if (IsFriendlyEntity(Entity) && IsSeaEntity(Entity) && IsAliveEntity(Entity)) StatsData.FriendlySeaActiveEntities++;
		if (IsFriendlyEntity(Entity) && IsMissileEntity(Entity) && IsAliveEntity(Entity)) StatsData.FriendlyActiveMisiles++;

		if (IsFriendlyEntity(Entity) && IsAirEntity(Entity) && IsDeadEntity(Entity)) StatsData.FriendlyAirDeadEntities++;
		if (IsFriendlyEntity(Entity) && IsGroundEntity(Entity) && IsDeadEntity(Entity)) StatsData.FriendlyGroundDeadEntities++;
		if (IsFriendlyEntity(Entity) && IsSeaEntity(Entity) && IsDeadEntity(Entity)) StatsData.FriendlySeaDeadEntities++;
		if (IsFriendlyEntity(Entity) && IsMissileEntity(Entity) && IsDeadEntity(Entity)) StatsData.FriendlyDeadMisiles++;








		if (IsEnemyEntity(Entity) && IsAirEntity(Entity)) StatsData.EnemyAirEntities++;
		if (IsEnemyEntity(Entity) && IsGroundEntity(Entity)) StatsData.EnemyGroundEntities++;
		if (IsEnemyEntity(Entity) && IsSeaEntity(Entity)) StatsData.EnemySeaEntities++;
		if (IsEnemyEntity(Entity) && IsMissileEntity(Entity)) StatsData.EnemyMisiles++;


		if (IsEnemyEntity(Entity) && IsAirEntity(Entity) && IsAliveEntity(Entity)) StatsData.EnemyAirActiveEntities++;
		if (IsEnemyEntity(Entity) && IsGroundEntity(Entity) && IsAliveEntity(Entity)) StatsData.EnemyGroundActiveEntities++;
		if (IsEnemyEntity(Entity) && IsSeaEntity(Entity) && IsAliveEntity(Entity)) StatsData.EnemySeaActiveEntities++;
		if (IsEnemyEntity(Entity) && IsMissileEntity(Entity) && IsAliveEntity(Entity)) StatsData.EnemyActiveMisiles++;

		if (IsEnemyEntity(Entity) && IsAirEntity(Entity) && IsDeadEntity(Entity)) StatsData.EnemyAirDeadEntities++;
		if (IsEnemyEntity(Entity) && IsGroundEntity(Entity) && IsDeadEntity(Entity)) StatsData.EnemyGroundDeadEntities++;
		if (IsEnemyEntity(Entity) && IsSeaEntity(Entity) && IsDeadEntity(Entity)) StatsData.EnemySeaDeadEntities++;
		if (IsEnemyEntity(Entity) && IsMissileEntity(Entity) && IsDeadEntity(Entity)) StatsData.EnemyDeadMisiles++;






		if (IsNeutralEntity(Entity) && IsAirEntity(Entity)) StatsData.NeutralAirEntities++;
		if (IsNeutralEntity(Entity) && IsGroundEntity(Entity)) StatsData.NeutralGroundEntities++;
		if (IsNeutralEntity(Entity) && IsSeaEntity(Entity)) StatsData.NeutralSeaEntities++;
		if (IsNeutralEntity(Entity) && IsMissileEntity(Entity)) StatsData.NeutralMisiles++;


		if (IsNeutralEntity(Entity) && IsAirEntity(Entity) && IsAliveEntity(Entity)) StatsData.NeutralAirActiveEntities++;
		if (IsNeutralEntity(Entity) && IsGroundEntity(Entity) && IsAliveEntity(Entity)) StatsData.NeutralGroundActiveEntities++;
		if (IsNeutralEntity(Entity) && IsSeaEntity(Entity) && IsAliveEntity(Entity)) StatsData.NeutralSeaActiveEntities++;
		if (IsNeutralEntity(Entity) && IsMissileEntity(Entity) && IsAliveEntity(Entity)) StatsData.NeutralActiveMisiles++;

		if (IsNeutralEntity(Entity) && IsAirEntity(Entity) && IsDeadEntity(Entity)) StatsData.NeutralAirDeadEntities++;
		if (IsNeutralEntity(Entity) && IsGroundEntity(Entity) && IsDeadEntity(Entity)) StatsData.NeutralGroundDeadEntities++;
		if (IsNeutralEntity(Entity) && IsSeaEntity(Entity) && IsDeadEntity(Entity)) StatsData.NeutralSeaDeadEntities++;
		if (IsNeutralEntity(Entity) && IsMissileEntity(Entity) && IsDeadEntity(Entity)) StatsData.NeutralDeadMisiles++;










		if (IsOtherEntity(Entity) && IsAirEntity(Entity)) StatsData.OtherAirEntities++;
		if (IsOtherEntity(Entity) && IsGroundEntity(Entity)) StatsData.OtherGroundEntities++;
		if (IsOtherEntity(Entity) && IsSeaEntity(Entity)) StatsData.OtherSeaEntities++;
		if (IsOtherEntity(Entity) && IsMissileEntity(Entity)) StatsData.OtherMisiles++;


		if (IsOtherEntity(Entity) && IsAirEntity(Entity) && IsAliveEntity(Entity)) StatsData.OtherAirActiveEntities++;
		if (IsOtherEntity(Entity) && IsGroundEntity(Entity) && IsAliveEntity(Entity)) StatsData.OtherGroundActiveEntities++;
		if (IsOtherEntity(Entity) && IsSeaEntity(Entity) && IsAliveEntity(Entity)) StatsData.OtherSeaActiveEntities++;
		if (IsOtherEntity(Entity) && IsMissileEntity(Entity) && IsAliveEntity(Entity)) StatsData.OtherActiveMisiles++;

		if (IsOtherEntity(Entity) && IsAirEntity(Entity) && IsDeadEntity(Entity)) StatsData.OtherAirDeadEntities++;
		if (IsOtherEntity(Entity) && IsGroundEntity(Entity) && IsDeadEntity(Entity)) StatsData.OtherGroundDeadEntities++;
		if (IsOtherEntity(Entity) && IsSeaEntity(Entity) && IsDeadEntity(Entity)) StatsData.OtherSeaDeadEntities++;
		if (IsOtherEntity(Entity) && IsMissileEntity(Entity) && IsDeadEntity(Entity)) StatsData.OtherDeadMisiles++;



		//if (Entity->GetForceType() == EForceType::FRIENDLY && IsDeadEntity(Entity)) StatsData.BlueDead++;

		//if (Entity->GetForceType() == EForceType::OPPOSING) StatsData.RedTotal++;
		//if (Entity->GetForceType() == EForceType::OPPOSING && IsAliveEntity(Entity)) StatsData.RedAlive++;
		//if (Entity->GetForceType() == EForceType::OPPOSING && IsDeadEntity(Entity)) StatsData.RedDead++;

		//if (Entity->GetForceType() == EForceType::NEUTRAL) StatsData.NeutralTotal++;
		//if (Entity->GetForceType() == EForceType::NEUTRAL && IsAliveEntity(Entity)) StatsData.NeutralAlive++;
		//if (Entity->GetForceType() == EForceType::NEUTRAL && IsDeadEntity(Entity)) StatsData.NeutralDead++;

		//if (Entity->GetForceType() == EForceType::OTHERS) StatsData.OtherTotal++;
		//if (Entity->GetForceType() == EForceType::OTHERS && IsAliveEntity(Entity)) StatsData.OtherAlive++;
		//if (Entity->GetForceType() == EForceType::OTHERS && IsDeadEntity(Entity)) StatsData.OtherDead++;

		//if (IsAirEntity(Entity)) StatsData.AirEntities++;
		//if (IsGroundEntity(Entity)) StatsData.GroundEntities++;
		//if (IsSeaEntity(Entity)) StatsData.SeaEntities++;
		//if (Entity->GetRemoteEntityType() == ERemoteEntityType::MISSILE) StatsData.Misiles++;

		//if (IsAirEntity(Entity) && Entity->GetForceType() == EForceType::FRIENDLY) StatsData.FriendlyAirEntities++;
		//if (IsAirEntity(Entity) && Entity->GetForceType() == EForceType::OPPOSING) StatsData.EnemyAirEntities++;
		//if (IsAirEntity(Entity) && Entity->GetForceType() == EForceType::NEUTRAL) StatsData.NeutralAirEntities++;
		//if (IsAirEntity(Entity) && Entity->GetForceType() == EForceType::OTHERS) StatsData.OtherAirEntities++;
		//if (IsAirEntity(Entity) && Entity->GetForceType() == EForceType::FRIENDLY && Entity->GetHealth() == ELocalHealth::NO_DAMAGE) StatsData.FriendlyActiveAirEntities++;
		//if (IsAirEntity(Entity) && Entity->GetForceType() == EForceType::FRIENDLY && Entity->GetHealth() == ELocalHealth::DESTROYED) StatsData.FriendlyDeadAirEntities++;
		//if (IsAirEntity(Entity) && Entity->GetForceType() == EForceType::OPPOSING && Entity->GetHealth() == ELocalHealth::NO_DAMAGE) StatsData.EnemyActiveAirEntities++;
		//if (IsAirEntity(Entity) && Entity->GetForceType() == EForceType::OPPOSING && Entity->GetHealth() == ELocalHealth::DESTROYED) StatsData.EnemyDeadAirEntities++;



	/*	UE_LOG(LogTemp, Log, TEXT("Value %s"), *Entity->GetCallSign());
		if (Entity->GetForceType() == EForceType::FRIENDLY)
		{
			StatsData.FriendlyAirEntities++;
			if (Entity->GetHealth() == ELocalHealth::NO_DAMAGE)
			{
				StatsData.FriendlyActiveAirEntities++;
			}
			if (Entity->GetHealth() == ELocalHealth::DESTROYED)
			{
				StatsData.FriendlyDeadAirEntities++;
			}
		}
		if (Entity->GetForceType() == EForceType::OPPOSING)
		{

			StatsData.EnemyAirEntities++;

			if (Entity->GetHealth() == ELocalHealth::NO_DAMAGE)
			{
				StatsData.EnemyActiveAirEntities++;
			}
			if (Entity->GetHealth() == ELocalHealth::DESTROYED)
			{
				StatsData.EnemyDeadAirEntities++;
			}
		}
		if (Entity->GetForceType() == EForceType::NEUTRAL)
		{

			StatsData.NeutralAirEntities++;
		}
		if (Entity->GetForceType() == EForceType::OTHERS)
		{

			StatsData.NeutralAirEntities++;
		}
		
		if (Entity->GetRemoteEntityType() == ERemoteEntityType::MISSILE)
		{

			StatsData.Misiles++;
		}

		if (Entity->GetRemoteEntityType() == ERemoteEntityType::FIXEDWING_AIRCRAFT)
		{

			StatsData.AirEntities++;
		}*/

	}
}

