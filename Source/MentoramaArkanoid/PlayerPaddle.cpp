// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPaddle.h"
#include "Ball.h"

// Sets default values
APlayerPaddle::APlayerPaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerPaddle::BeginPlay()
{
	Super::BeginPlay();

	speed = InitialSpeed;
}

void APlayerPaddle::UnPossessed()
{
	Super::UnPossessed();

	SetLifeSpan(TimeAfterUnPossessed);
}

// Called every frame
void APlayerPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector movementInput = ConsumeMovementInputVector();
	AddActorLocalOffset(movementInput * speed * DeltaTime, true);
}

void APlayerPaddle::AddSpeed(float value)
{
	speed += value;
}

void APlayerPaddle::ResetSpeed() 
{
	speed = InitialSpeed;
}
