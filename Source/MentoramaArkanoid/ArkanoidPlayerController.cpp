// Fill out your copyright notice in the Description page of Project Settings.


#include "ArkanoidPlayerController.h"
#include "Ball.h"

void AArkanoidPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AArkanoidPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(holdingBall) && IsValid(GetPawn())) {
		holdingBall->SetActorLocation(GetPawn()->GetActorLocation() + OffsetSpawnInitialBall);
	}
}

void AArkanoidPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAxis(HorizontalInputAxis, this, &AArkanoidPlayerController::HandleHorizontalAxis);
	InputComponent->BindAction(LaunchInput, IE_Pressed, this, &AArkanoidPlayerController::HandleLaunch);
}

ABall* AArkanoidPlayerController::SpawnBall()
{
	auto* ball = GetWorld()->SpawnActor<ABall>(BallClass.Get());

	ball->OnBallDestroyed.AddDynamic(this, &AArkanoidPlayerController::OnBallDestroyed);
	Balls.Add(ball);

	return ball;
}

void AArkanoidPlayerController::OnBallDestroyed(ABall* ball)
{
	Balls.Remove(ball);
	if (Balls.Num() <= 0) {
		UnPossess();
		OnAllBallsDestroyed.Broadcast();
	}
}

void AArkanoidPlayerController::DestroyAllBalls()
{
	for (ABall* ballElement : Balls) {
		ballElement->Destroy();
	}
	Balls.Reset();
}

void AArkanoidPlayerController::DestroyAllPowerUPs()
{
	for (AActor* powerUp : powerUps) {
		powerUp->Destroy();
	}
	powerUps.Reset();
}

void AArkanoidPlayerController::HandleHorizontalAxis(float value)
{
	if (!IsValid(GetPawn())) return;

	GetPawn()->AddMovementInput(FVector::ForwardVector,value);
}

void AArkanoidPlayerController::HandleLaunch()
{
	if (IsValid(holdingBall)) {
		holdingBall->Launch();
		holdingBall = nullptr;
	}
}

void AArkanoidPlayerController::StartInitialState()
{
	holdingBall = SpawnBall();
	if (IsValid(holdingBall) && IsValid(GetPawn())) {
		holdingBall->SetActorLocation(GetPawn()->GetActorLocation() + OffsetSpawnInitialBall);
	}
}
