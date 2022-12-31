// Fill out your copyright notice in the Description page of Project Settings.


#include "Helpers.h"
#include "GameWonData.h"
#include "Kismet/GameplayStatics.h"

bool UHelpers::SaveRecordScore(float score)
{
	auto* SaveGame = UGameplayStatics::CreateSaveGameObject(UGameWonData::StaticClass());

	if (const auto GameWonData = Cast<UGameWonData>(SaveGame)) {
		GameWonData->RecordScore = score;
		UGameplayStatics::SaveGameToSlot(GameWonData, TEXT("RecordScore"), 0);
		return true;
	}
	return false;
}

float UHelpers::LoadRecordScore()
{
	auto* SaveGame = UGameplayStatics::LoadGameFromSlot(TEXT("RecordScore"), 0);

	if (const auto GameWonData = Cast<UGameWonData>(SaveGame)) {

		return GameWonData->RecordScore;
	}
	return 0;
}