// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ArkanoidPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MENTORAMAARKANOID_API AArkanoidPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(BlueprintReadOnly)
		int life;

	UPROPERTY(BlueprintReadOnly, EditAnyWhere)
		int initialLife = 3;
};
