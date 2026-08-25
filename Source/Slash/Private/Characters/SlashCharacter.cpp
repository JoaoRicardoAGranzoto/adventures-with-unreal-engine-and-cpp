// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/SlashCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ASlashCharacter::ASlashCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	SpringArm=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	
	
	
	
	SpringArm->TargetArmLength = 300.f;
	SpringArm->SetupAttachment(RootComponent);
	
	Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASlashCharacter::Move(const struct FInputActionValue& Value)
{
	FRotator YawRotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	
	FVector Forward=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector Right=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	AddMovementInput(Forward, Value.Get<FVector2D>().X);
	AddMovementInput(Right, Value.Get<FVector2D>().Y);
}

void ASlashCharacter::Look(const struct FInputActionValue& Value)
{
	AddControllerPitchInput(Value.Get<FVector2D>().X);
	AddControllerYawInput(Value.Get<FVector2D>().Y);
}

void ASlashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController=Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem=PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		
			
			
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ThisClass::Jump);
}