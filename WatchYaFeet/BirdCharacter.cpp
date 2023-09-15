// EGJ2022 Phanuwat Chalee


#include "BirdCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Lv1GameMode.h"
#include "Lv2GameMode.h"
#include "Lv3GameMode.h"


ABirdCharacter::ABirdCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 50.0f);

	//.. Camera Config
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 700.0f;	
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 500.f);
	CameraBoom->bUsePawnControlRotation = true; 

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->SetRelativeRotation(FRotator(-30, 0, 0));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw   = false;
	bUseControllerRotationRoll  = false;

	//.. Character movement Config
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 250.f; //.. Default 500.f 
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	OnDestroyTime = 3.f;
	bIsAbove = true;
}


void ABirdCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABirdCharacter::OnOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic  (this, &ABirdCharacter::OnOverlapEnd  );
}


void ABirdCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABirdCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move / Forward&Backward", this, &ABirdCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move / Left&Right"      , this, &ABirdCharacter::MoveRight  );

	PlayerInputComponent->BindAxis("Turn / Left&Right", this, &APawn::AddControllerYawInput  );
	PlayerInputComponent->BindAxis("Look / Up&Down"   , this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed , this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
}


void ABirdCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABirdCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ABirdCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//..
}

void ABirdCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//..
}


void ABirdCharacter::OnPlayerDestroy()
{
	FTimerHandle TimeHandle;
	GetWorldTimerManager().SetTimer(TimeHandle, this, &ABirdCharacter::PlayerDestroy, OnDestroyTime);
}

void ABirdCharacter::PlayerDestroy()
{
	ALv1GameMode* Lv1GameMode = Cast<ALv1GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ALv2GameMode* Lv2GameMode = Cast<ALv2GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ALv3GameMode* Lv3GameMode = Cast<ALv3GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	
	if (Lv1GameMode) Lv1GameMode->bPlayerDie = true;
	if (Lv2GameMode) Lv2GameMode->bPlayerDie = true;
	if (Lv3GameMode) Lv3GameMode->bPlayerDie = true;
}