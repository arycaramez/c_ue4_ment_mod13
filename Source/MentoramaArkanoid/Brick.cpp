// Fill out your copyright notice in the Description page of Project Settings.


#include "Brick.h"
#include "Ball.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "ArkanoidPlayerController.h"

// Sets default values
ABrick::ABrick()
{ 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	Super::BeginPlay();	

}

// Called every frame
void ABrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABrick::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	
	if (Other->IsA(ABall::StaticClass()) && Hit.bBlockingHit == 1) {
		onBrickDestroyed.Broadcast(this);

		//KillThisBrick();
		FTimerHandle timeHandle;
		GetWorld()->GetTimerManager().SetTimer(timeHandle,this,&ABrick::KillThisBrick, 0.1, false);
	}
	
}

void ABrick::KillThisBrick() {
	FVector pos = GetActorLocation();
	FRotator rot = GetActorRotation();

	if (IsValid(GetWorld()) && IsValid(PowerUpActor)) {
		GetWorld()->SpawnActor<AActor>(PowerUpActor, pos, rot);
	} else {
		UGameplayStatics::SpawnEmitterAtLocation(this, dethVFX, pos, rot, FVector(1, 1, 1), true, EPSCPoolMethod::None, true);
	}

	Destroy();
}

int ABrick::GetScoreValue() const
{
	return 10;
}

