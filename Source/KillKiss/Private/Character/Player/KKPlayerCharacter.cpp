// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/KKPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Controllers/KKPlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "KKDebugHelper.h"
#include "Components/Input/KKInputComponent.h"
#include "DataAssets/DataAsset_InputConfig.h"
#include "KKGameplayTags.h"
#include "AbilitySystem/KKAbilitySystemComponent.h"
#include "Character/Player/KKPlayerState.h"
#include "DataAssets/StartupData/DataAsset_StartupDataBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/KKHUD.h"

AKKPlayerCharacter::AKKPlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2048.f;
}

int32 AKKPlayerCharacter::GetPlayerLevel()
{
	const AKKPlayerState* KKPlayerState = Cast<AKKPlayerState>(GetPlayerState());
	check(KKPlayerState);

	return KKPlayerState->GetPlayerLevel();
}

FVector AKKPlayerCharacter::GetLeftHandSocket()
{
	return GetMesh()->GetSocketLocation(LeftHandSocketName);
}

FVector AKKPlayerCharacter::GetRightHandSocket()
{
	return GetMesh()->GetSocketLocation(RightHandSocketName);
}

void AKKPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("입력 설정 데이터 에셋이 누락되었습니다."));
	const ULocalPlayer* LocalPlayer = GetController<AKKPlayerController>()->GetLocalPlayer();

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

	KKInputComponent->BindAbilityInputAction(InputConfigDataAsset, this,
	                                         &ThisClass::Input_AbilityInputPressed,
	                                         &ThisClass::Input_AbilityInputReleased);
}

void AKKPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AKKPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
}

void AKKPlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	if (AbilitySystemComponent->HasMatchingGameplayTag(KKGameplayTags::Player_State_AttributeMenuOpen))
	{
		return;
	}

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
	if (AbilitySystemComponent->HasMatchingGameplayTag(KKGameplayTags::Player_State_AttributeMenuOpen))
	{
		return;
	}

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
	if (AbilitySystemComponent->HasMatchingGameplayTag(KKGameplayTags::Player_State_AttributeMenuOpen))
	{
		return;
	}

	Jump();
}

void AKKPlayerCharacter::InitAbilityActorInfo()
{
	AKKPlayerState* KKPlayerState = GetPlayerState<AKKPlayerState>();
	check(KKPlayerState);
	KKPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(KKPlayerState, this);

	AbilitySystemComponent = KKPlayerState->GetAbilitySystemComponent();
	AttributeSet = KKPlayerState->GetAttributeSet();

	ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());

	if (UDataAsset_StartupDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
	{
		if (UKKAbilitySystemComponent* KKAbilitySystemComponent =
			Cast<UKKAbilitySystemComponent>(AbilitySystemComponent))
		{
			LoadedData->GiveToAbilitySystemComponent(KKAbilitySystemComponent, 1.f);
		}
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (AKKHUD* KKHUD = Cast<AKKHUD>(PlayerController->GetHUD()))
		{
			KKHUD->InitOverlay(PlayerController, KKPlayerState, GetAbilitySystemComponent(), GetAttributeSet());
		}
	}
}

void AKKPlayerCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	UKKAbilitySystemComponent* KKASC = CastChecked<UKKAbilitySystemComponent>(AbilitySystemComponent);
	KKASC->OnAbilityInputPressed(InInputTag);
}

void AKKPlayerCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	UKKAbilitySystemComponent* KKASC = CastChecked<UKKAbilitySystemComponent>(AbilitySystemComponent);
	KKASC->OnAbilityInputReleased(InInputTag);
}
