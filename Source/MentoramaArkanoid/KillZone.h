// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KillZone.generated.h"

UCLASS()
class MENTORAMAARKANOID_API AKillZone : public AActor
{
	GENERATED_BODY()
	
protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

public:
	// Sets default values for this actor's properties
	AKillZone();

};
