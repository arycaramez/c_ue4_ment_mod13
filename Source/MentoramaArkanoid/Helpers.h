// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Helpers.generated.h"

/**
 * 
 */
UCLASS()
class MENTORAMAARKANOID_API UHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "SaveScore")
		static bool SaveRecordScore(float score);

	UFUNCTION(BlueprintPure, Category = "SaveScore")
		static float LoadRecordScore();
};
