// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBallDestroyed, class ABall*, ball);

class UMaterialInstanceDynamic;

UCLASS()
class MENTORAMAARKANOID_API ABall : public AActor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ABall();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly)
	class UStaticMeshComponent* sphere;

	UFUNCTION()
	void Launch();

	UPROPERTY(EditAnyWhere)
		FVector launchDirection = FVector(-1,0,1);

	UPROPERTY(EditAnyWhere)
		float launchSpeed = 500;

	UPROPERTY()
		float currentSpeed;

	UFUNCTION(BlueprintCallable)
		void AddSpeed(float value);

	UFUNCTION()
		void ResetSpeed();

	UPROPERTY()
		FOnBallDestroyed OnBallDestroyed;

	void Kill();


};
