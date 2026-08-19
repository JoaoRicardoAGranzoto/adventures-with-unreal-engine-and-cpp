// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Item.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("AItem::BeginPlay()"));
}

void AItem::Tick(float DeltaTime)
{
	
	
	
	
	Super::Tick(DeltaTime);

	if (GetWorld())
	{
		DrawDebugSphere(GetWorld(), GetActorLocation(), 100.f, 10, FColor::Red);
		DrawDebugLine(GetWorld(), GetActorLocation(), GetActorForwardVector() * 1000.f, FColor::Red);
	}
}