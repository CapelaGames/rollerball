// Fill out your copyright notice in the Description page of Project Settings.


#include "RollerBallGameModeBase.h"
#include "RollerBallWidget.h"
#include "Kismet/GameplayStatics.h"
#include "RollerBall/Items/RollerBallItemBase.h"

void ARollerBallGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARollerBallItemBase::StaticClass(), Items);
	ItemsInLevel = Items.Num();

	if(GameWidgetClass)
	{
		GameWidget = Cast<URollerBallWidget>(CreateWidget(GetWorld(),GameWidgetClass));

		if(GameWidget)
		{
			GameWidget->AddToViewport();
			UpdateItemText();
		}
	}
}

void ARollerBallGameModeBase::UpdateItemText()
{
	GameWidget->SetItemText(ItemsCollected, ItemsInLevel);
}

void ARollerBallGameModeBase::ItemCollected()
{
	ItemsCollected++;
	UpdateItemText();
}
