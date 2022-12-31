// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Brick.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BrickManager.generated.h"

class ABrick;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllBricksDestroyed);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MENTORAMAARKANOID_API UBrickManager : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
		FVector GetPositionFor(int x, int z);

	UFUNCTION()
		void HandleBrickDestroyed(ABrick* destroyedBrick);

	UFUNCTION()
		void ApplyScore(ABrick* brick);

	UFUNCTION()
		TSubclassOf<ABrick> GetBrickByPosition(TArray<FString> lvlGen, int x, int z);

	UFUNCTION()
		bool LoadLevelGeneratorInfo(TArray<FString>& Result);

	UPROPERTY()
		TArray<ABrick*> allBricks;

public:
	UBrickManager();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION()
	virtual void SpawnBricks();

	UFUNCTION(BlueprintCallable)
		void DestroyAllBricks();
	
	UPROPERTY(EditDefaultsOnly)
		TArray<FString> levelGeneratorNames = { TEXT("LevelGen_00.txt"), TEXT("LevelGen_01.txt"), TEXT("LevelGen_02.txt") };

	UPROPERTY(EditDefaultsOnly)
		TArray<TSubclassOf<ABrick>> bricks;

	UPROPERTY(EditDefaultsOnly)
		FVector brickExtend;

	UPROPERTY(EditDefaultsOnly)
		FVector offsetBetweenBricks;

	UPROPERTY(EditDefaultsOnly)
		FVector startSpawnPosition;

	FOnAllBricksDestroyed OnAllBricksDestroyed;
};
