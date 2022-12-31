// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickManager.h"
#include "Brick.h"
#include "ArkanoidPlayerState.h"
#include "MentoramaArkanoidGameModeBase.h"

// Sets default values for this component's properties
UBrickManager::UBrickManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UBrickManager::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UBrickManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBrickManager::SpawnBricks()
{
	// Carrega o arquivo que irá gerar o level.
	TArray<FString> result;
	if (!LoadLevelGeneratorInfo(result)) return;
	// Recebe o número de linhas e colunas usando os dados coletados no arquivo de texto.
	for (int z = 0; z < result.Num(); z++) {
		for (int x = 0; x < result[z].GetCharArray().Num(); x++) {

			auto* brick = GetWorld()->SpawnActor<ABrick>(GetBrickByPosition(result,x, z).Get());

			if (IsValid(brick)) {
				if (brickExtend.IsZero()) {
					FVector origin;
					brick->GetActorBounds(true, origin, brickExtend);
				}
				brick->onBrickDestroyed.AddDynamic(this, &UBrickManager::HandleBrickDestroyed);
				brick->SetActorLocation(GetPositionFor(x, z));
				allBricks.Add(brick);
			}
		}
	}
}

void UBrickManager::DestroyAllBricks()
{
	for (ABrick* brick: allBricks) {
		brick->Destroy();
	}
	allBricks.Reset();
}

FVector UBrickManager::GetPositionFor(int x, int z)
{
	FVector position = startSpawnPosition;
	
	position.X += x * brickExtend.X * 2;
	position.X += x * offsetBetweenBricks.X;

	position.Z -= z * brickExtend.Z * 2;
	position.Z -= z * offsetBetweenBricks.Z;

	return position;
}

TSubclassOf<ABrick> UBrickManager::GetBrickByPosition(TArray<FString> lvlGen,int x, int z)
{	
	int idBrick = (int)((lvlGen[z].GetCharArray()[x])-48);
	
	if (idBrick >= 0 && bricks.Num() > idBrick) {
		return bricks[idBrick];
	}
	return NULL;
}

bool UBrickManager::LoadLevelGeneratorInfo(TArray<FString> & result)
{
	if (!IsValid(GetWorld())) return false;
	auto* mentArkanoidGameModeBase = 
		Cast<AMentoramaArkanoidGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!IsValid(mentArkanoidGameModeBase)) return false;

	FString path = FPaths::GeneratedConfigDir() + levelGeneratorNames[mentArkanoidGameModeBase->CurrentRound];
	if (FFileHelper::LoadANSITextFileToStrings(*path, NULL, result)) {
		return true;
	}
	return false;
}

void UBrickManager::HandleBrickDestroyed(ABrick* destroyedBrick)
{
	ApplyScore(destroyedBrick);

	allBricks.Remove(destroyedBrick);
	if (allBricks.Num() <= 0) {
		OnAllBricksDestroyed.Broadcast();
	}
}

void UBrickManager::ApplyScore(ABrick* brick)
{
	auto* playerController = GetWorld()->GetFirstPlayerController();
	if (!IsValid(playerController)) return;
	auto* playerState = playerController->PlayerState;
	if (!IsValid(playerState)) return;
	//playerState->Score += brick->GetScoreValue();
	playerState->SetScore(playerState->GetScore() + brick->GetScoreValue());
}

