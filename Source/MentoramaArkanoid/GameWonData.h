// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameWonData.generated.h"

/**
 * 
 */
UCLASS()
class MENTORAMAARKANOID_API UGameWonData : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	float RecordScore;
};
