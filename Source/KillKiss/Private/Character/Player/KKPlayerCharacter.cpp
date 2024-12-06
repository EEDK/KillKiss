// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/KKPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Controllers/KKPlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/Input/KKInputComponent.h"
#include "DataAssets/DataAsset_InputConfig.h"
#include "KKGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"

AKKPlayerCharacter::AKKPlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

void AKKPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("입력 설정 데이터 에셋이 누락되었습니다."));
	ULocalPlayer* LocalPlayer = GetController<AKKPlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	// 입력 매핑 컨텍스트 추가
	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UKKInputComponent* KKInputComponent = CastChecked<UKKInputComponent>(PlayerInputComponent);

	// 액션 바인딩
	KKInputComponent->BindNativeInputAction(InputConfigDataAsset, KKGameplayTags::InputTag_Move,
	                                        ETriggerEvent::Triggered, this, &ThisClass::Input_Move);

	KKInputComponent->BindNativeInputAction(InputConfigDataAsset, KKGameplayTags::InputTag_Look,
	                                        ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
	KKInputComponent->BindNativeInputAction(InputConfigDataAsset, KKGameplayTags::InputTag_Jump,
	                                        ETriggerEvent::Triggered, this, &ThisClass::Input_Jump);
}

void AKKPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AKKPlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}
	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AKKPlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AKKPlayerCharacter::Input_Jump(const FInputActionValue& InputActionValue)
{
	Jump();
}
