// Fill out your copyright notice in the Description page of Project Settings.


#include "KillZone.h"
#include "Ball.h"

AKillZone::AKillZone() {
	PrimaryActorTick.bCanEverTick = false;
}

void AKillZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	auto* Ball = Cast<ABall>(OtherActor);
	if (IsValid(Ball)) {
		Ball->Kill();
	}
}
