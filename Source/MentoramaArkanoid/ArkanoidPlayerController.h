// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ArkanoidPlayerController.generated.h"

class ABall;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllBallsDestroyed);

/**
 * 
 */
UCLASS()
class MENTORAMAARKANOID_API AArkanoidPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnBallDestroyed(ABall* ball);

public:

	UFUNCTION()
	void SetupInputComponent();

	UFUNCTION()
	ABall* SpawnBall();

	UPROPERTY(EditDefaultsOnly, Category="Input")
		FName HorizontalInputAxis = TEXT("Horizontal");

	UPROPERTY(EditDefaultsOnly, Category = "Input")
		FName LaunchInput = TEXT("Launch");

	UFUNCTION()
	void HandleHorizontalAxis(float value);

	UFUNCTION()
		void HandleLaunch();

	UFUNCTION()
		void StartInitialState();

	UPROPERTY(EditAnyWhere, Category = "Ball")
		FVector OffsetSpawnInitialBall = FVector(0,0,30);

	UPROPERTY(EditAnyWhere,Category="Ball")
		TSubclassOf<ABall> BallClass;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "PowerUp")
		TArray<AActor*> powerUps;

	UFUNCTION()
		void DestroyAllBalls();

	UFUNCTION()
		void DestroyAllPowerUPs();

	UPROPERTY()
	FOnAllBallsDestroyed OnAllBallsDestroyed;

	UPROPERTY(EditAnyWhere,BlueprintReadWrite, Category = "Balls")
	TArray<ABall*> Balls;

private:
	UPROPERTY()
		ABall* holdingBall;

};
