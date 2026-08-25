// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Item.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
}

void AItem::Tick(float DeltaTime)




{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;
	
	float DeltaZ = 0.25f * FMath::Sin(RunningTime * 5.f);
	
	AddActorLocalOffset(FVector(GetActorLocation().X, GetActorLocation().Y, DeltaZ));
	AddActorLocalRotation(FRotator(0.f, DeltaZ, 0.f));
	
	if (GetWorld())
	{
		DrawDebugSphere(GetWorld(), GetActorLocation(), 100.f, 10, FColor::Red);
		DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 500.f, FColor::Red);
	}
}