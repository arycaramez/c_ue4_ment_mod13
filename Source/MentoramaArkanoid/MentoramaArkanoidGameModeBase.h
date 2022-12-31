// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "BrickManager.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MentoramaArkanoidGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartRound, int, round);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameOver,int, score);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameWon, int, score);

/**
 * 
 */
UCLASS()
class MENTORAMAARKANOID_API AMentoramaArkanoidGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	AMentoramaArkanoidGameModeBase();

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnyWhere)
	class UBrickManager* BrickManager;

	UFUNCTION()
		void OnAllBricksDestroyed();

	UFUNCTION()
		void OnAllBallsDestroyed();

	// Abaixo estão localizados elementos usados para iniciar uma nova partida.

	UPROPERTY(BlueprintReadOnly, EditAnyWhere)
		float TimeToStartRound = 0.5f;

	UPROPERTY(BlueprintReadOnly, EditAnyWhere)
		float TimeToRestartAfterDeth = 0.5f;

	UPROPERTY(BlueprintAssignable)
		FOnStartRound OnStartRound;

	UPROPERTY(BlueprintAssignable)
		FOnGameOver OnGameOver;

	UPROPERTY(BlueprintAssignable)
		FOnGameWon OnGameWon;
	
	UFUNCTION(BlueprintCallable)
		void StartRound(int round);

public:	

	UPROPERTY(BlueprintReadOnly, EditAnyWhere)
	int CurrentRound = 0;
};
