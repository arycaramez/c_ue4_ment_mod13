// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "PlayerPaddle.h"
#include "EngineGlobals.h"
#include "Brick.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));

	RootComponent = sphere;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (currentSpeed <= 0) return;

	FVector velocity = GetVelocity();

	if (velocity.IsNearlyZero()) return;

	velocity.Normalize();
	float tolerance = 0.03f;
	if (FMath::IsNearlyZero(velocity.X, tolerance)) {
		velocity.X = tolerance * (FMath::RandBool() ? 1 : -1);
	}
	if (FMath::IsNearlyZero(velocity.Z, tolerance)) {
		velocity.Z = tolerance * (FMath::RandBool() ? 1 : -1);
	}
	velocity *= currentSpeed;
	sphere->SetPhysicsLinearVelocity(velocity);
	
}

void ABall::Launch()
{
	sphere->AddImpulse(launchDirection.GetSafeNormal() * launchSpeed,NAME_None,true);
	currentSpeed = launchSpeed;
}

void ABall::AddSpeed(float value)
{
	currentSpeed += value;
}

void ABall::ResetSpeed()
{
	currentSpeed = launchSpeed;
}

void ABall::Kill()
{
	OnBallDestroyed.Broadcast(this);
	Destroy();
}


