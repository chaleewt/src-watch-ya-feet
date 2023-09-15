// EGJ2022 Phanuwat Chalee


#include "GroundCube.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BirdCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "NiagaraFunctionLibrary.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "NiagaraSystem.h"


AGroundCube::AGroundCube() :

	BounceRate(15.f), TrapLockTime(3.f), SoundFXVolume(0.f), bIsTrap(false)
{
	PrimaryActorTick.bCanEverTick = true;

	GroundCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GroundCube"));
	RootComponent = GroundCube;
	GroundCube->SetMobility(EComponentMobility::Movable);

	ReactCollisionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("ReactCollision"));
	ReactCollisionVolume->SetupAttachment(GroundCube);
	ReactCollisionVolume->InitBoxExtent(FVector(90.f, 90.f, 32.f));
	ReactCollisionVolume->SetRelativeLocation(FVector(0.f, 0.f, 190.f));

	TrapCollisionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TrapCollisionVolume"));
	TrapCollisionVolume->SetupAttachment(GroundCube);
	TrapCollisionVolume->InitBoxExtent(FVector(5.f, 5.f, 32.f));
	TrapCollisionVolume->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
}


void AGroundCube::BeginPlay()
{
	Super::BeginPlay();
	
	GroundCubeInstanceLocation = GroundCube->GetComponentLocation();

	ReactCollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &AGroundCube::OnOverlapBegin);
	ReactCollisionVolume->OnComponentEndOverlap.AddDynamic  (this, &AGroundCube::OnOverlapEnd  );

	TrapCollisionVolume->OnComponentBeginOverlap.AddDynamic (this, &AGroundCube::OnOverlapTrapBegin);
	TrapCollisionVolume->OnComponentEndOverlap.AddDynamic   (this, &AGroundCube::OnOverlapTrapEnd  );
}


void AGroundCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AGroundCube::UpdateGroundPosition(float Z)
{
	FVector NewLocation = GroundCubeInstanceLocation;
	NewLocation.Z += Z;
	GroundCube->SetWorldLocation(NewLocation);
}


void AGroundCube::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ABirdCharacter* Player = Cast<ABirdCharacter>(OtherActor);

		if (Player)
		{
			Down();
		}
	}
}


void AGroundCube::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		ABirdCharacter* Player = Cast<ABirdCharacter>(OtherActor);

		if (Player)
		{
			Rise();
		}
	}
}


void AGroundCube::OnOverlapTrapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ABirdCharacter* BirdCharacter = Cast<ABirdCharacter>(OtherActor);

		if (BirdCharacter)
		{
			if (bIsTrap && !BirdCharacter->bDying) {

				PlayerCharacter = BirdCharacter;

				GroundCube->SetCollisionProfileName("NoCollision");

				//.. On Dying Callback Function
				//BirdCharacter->OnPlayerDestroy();
				//BirdCharacter->bDying = true;

				//.. Freeze Player
				//BirdCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
				//FTimerHandle Timer;
				//GetWorldTimerManager().SetTimer(Timer, this, &AGroundCube::ReleasePlayer, TrapLockTime);
			}
		}
	}
}
void AGroundCube::OnOverlapTrapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//..
}


/*void AGroundCube::OnSpikeOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ABirdCharacter* BirdCharacter = Cast<ABirdCharacter>(OtherActor);

		if (BirdCharacter)
		{
			if (bIsTrap && !BirdCharacter->bDying) {

				PlayerCharacter = BirdCharacter;

				//.. Play Sound Fx
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), TrapHitSound, BirdCharacter->GetActorLocation(), SoundFXVolume);

				//.. Freeze Player
				BirdCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
				FTimerHandle Timer;
				GetWorldTimerManager().SetTimer(Timer, this, &AGroundCube::ReleasePlayer, TrapLockTime);

				//.. On Dying Callback Function
				BirdCharacter->OnPlayerDestroy();
				BirdCharacter->bDying = true;

				//.. Ground Blinking Red if Gets hit
				bAlert = true;
			}
		}
	}
}*/


void AGroundCube::ReleasePlayer()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}

