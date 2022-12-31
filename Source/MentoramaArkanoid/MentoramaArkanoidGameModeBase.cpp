// Copyright Epic Games, Inc. All Rights Reserved.


#include "MentoramaArkanoidGameModeBase.h"
#include "BrickManager.h"
#include "ArkanoidPlayerController.h"
#include "ArkanoidPlayerState.h"
#include "Helpers.h"

AMentoramaArkanoidGameModeBase::AMentoramaArkanoidGameModeBase() : Super()
{
	BrickManager = CreateDefaultSubobject<UBrickManager>(TEXT("BrickManager"));
	BrickManager->OnAllBricksDestroyed.AddDynamic(
		this, &AMentoramaArkanoidGameModeBase::OnAllBricksDestroyed);
}

void AMentoramaArkanoidGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	
	if (IsValid(BrickManager)) {
		BrickManager->SpawnBricks();
	}

	if (IsValid(GetWorld())) {
		auto* playerController = GetWorld()->GetFirstPlayerController();
		auto ArkanoidPlayerController = Cast<AArkanoidPlayerController>(playerController);
		
		if (IsValid(ArkanoidPlayerController)) {
			ArkanoidPlayerController->StartInitialState();
			ArkanoidPlayerController->OnAllBallsDestroyed.AddDynamic(
				this, &AMentoramaArkanoidGameModeBase::OnAllBallsDestroyed);
		}
	}
}

void AMentoramaArkanoidGameModeBase::OnAllBricksDestroyed()
{
	StartRound(CurrentRound + 1);
}

void AMentoramaArkanoidGameModeBase::OnAllBallsDestroyed()
{
	FTimerHandle startRoundTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		startRoundTimerHandle, [this]()
		{
			if (!IsValid(GetWorld())) return;
			auto* PlayerController = Cast<AArkanoidPlayerController>(GetWorld()->GetFirstPlayerController());
			if (!IsValid(PlayerController)) return;
			auto* playerState = PlayerController->GetPlayerState<AArkanoidPlayerState>();
			if (!IsValid(playerState)) return;

			if (PlayerController->Balls.Num() <= 0) {
				playerState->life--;
			}

			if (playerState->life > 0) {
				RestartPlayer(PlayerController);
				PlayerController->StartInitialState();
			}else {
				BrickManager->DestroyAllBricks();

				float score = playerState->GetScore();
				OnGameOver.Broadcast(score);
				float recordScore = UHelpers::LoadRecordScore();
				if (recordScore < score) {
					UHelpers::SaveRecordScore(score);
				}
				playerState->SetScore(0);
				
				playerState->life = playerState->initialLife;
				PlayerController->DestroyAllPowerUPs();
			}
		},
		TimeToRestartAfterDeth, false);
}

void AMentoramaArkanoidGameModeBase::StartRound(int round)
{
	if (!IsValid(GetWorld())) return;
	auto* PlayerController = Cast<AArkanoidPlayerController>(GetWorld()->GetFirstPlayerController());
	if (!IsValid(PlayerController)) return;

	if (!IsValid(BrickManager)) return;

	if (CurrentRound != round) {

		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [PlayerController]() {
			PlayerController->DestroyAllPowerUPs();
			}, 0.5f, false);

	}

	if (BrickManager->levelGeneratorNames.Num() <= round)
	{
		auto* playerState = PlayerController->GetPlayerState<AArkanoidPlayerState>();
		if (IsValid(playerState)) {
			BrickManager->DestroyAllBricks();

			float score = playerState->GetScore();
			OnGameWon.Broadcast(score);
			float recordScore = UHelpers::LoadRecordScore();
			if (recordScore < score) {
				UHelpers::SaveRecordScore(score);
			}
			playerState->SetScore(0);
			

			playerState->life = playerState->initialLife;
			PlayerController->DestroyAllPowerUPs();

			PlayerController->UnPossess();
			PlayerController->DestroyAllBalls();
			return;
		}
	}else {
		CurrentRound = round;
	}
	OnStartRound.Broadcast(round);
	PlayerController->UnPossess();
	PlayerController->DestroyAllBalls();
	
	FTimerHandle startRoundTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		startRoundTimerHandle, [this, PlayerController]()
		{
			BrickManager->SpawnBricks();
			RestartPlayer(PlayerController);
			PlayerController->StartInitialState();
		},
		TimeToStartRound,false);
}

