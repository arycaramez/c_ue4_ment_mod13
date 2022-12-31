// Fill out your copyright notice in the Description page of Project Settings.


#include "ArkanoidPlayerState.h"

void AArkanoidPlayerState::BeginPlay()
{
	Super::BeginPlay();

	life = initialLife;
}
