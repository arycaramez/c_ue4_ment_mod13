// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPaddle.generated.h"

UCLASS()
class MENTORAMAARKANOID_API APlayerPaddle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPaddle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void UnPossessed() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float InitialSpeed = 500;

	UPROPERTY()
		float TimeAfterUnPossessed = 0.3f;

	UFUNCTION(BlueprintCallable)
		void AddSpeed(float value);

	UFUNCTION(BlueprintCallable)
		void ResetSpeed();
};
