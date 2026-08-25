// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawns/Bird.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/SphereComponent.h"

ABird::ABird()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComponent=CreateDefaultSubobject<USphereComponent>(TEXT("Box"));
	SetRootComponent(SphereComponent);
	
	SkeletalMesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("StaticMesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());
}





void ABird::BeginPlay()
{
	Super::BeginPlay();
}

void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem=PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			Subsystem->AddMappingContext(Default, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent=Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABird::Move);
	}
}

void ABird::Move(const struct FInputActionValue& Value)
{
	if (Controller && Value.Get<FVector2D>().X == 0.f)
	{
		AddMovementInput(GetActorForwardVector(), Value.Get<FVector2D>().X);
	}
}