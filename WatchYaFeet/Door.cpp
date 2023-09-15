// EGJ2022 Phanuwat Chalee


#include "Door.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BirdCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Lv1GameMode.h"
#include "Lv2GameMode.h"
#include "Lv3GameMode.h"


ADoor::ADoor() :

	WarpDelay(1.f), SoundFXVolume(0.f)

{
	PrimaryActorTick.bCanEverTick = true;

	DoorRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DoorRoot"));
	RootComponent = DoorRoot;

	DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrameMesh"));
	DoorFrameMesh->SetupAttachment(GetRootComponent());

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(DoorFrameMesh);

	BoxCollisionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionVolume"));
	BoxCollisionVolume->SetupAttachment(GetRootComponent());

	NextLevelTriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("NextLevelTriggerVolume"));
	NextLevelTriggerVolume->SetupAttachment(GetRootComponent());
}


void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	DoorInitialRotation = DoorMesh->GetComponentRotation();

	BoxCollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnOverlapBegin);
	BoxCollisionVolume->OnComponentEndOverlap.AddDynamic  (this, &ADoor::OnOverlapEnd  );

	NextLevelTriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnTriggerBeginOverlap);
	NextLevelTriggerVolume->OnComponentEndOverlap.AddDynamic  (this, &ADoor::OnTriggerEndOverlap  );
}


void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ADoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ABirdCharacter* BirdCharacter = Cast<ABirdCharacter>(OtherActor);

		ALv1GameMode* Lv1GameMode = Cast<ALv1GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		ALv2GameMode* Lv2GameMode = Cast<ALv2GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		ALv3GameMode* Lv3GameMode = Cast<ALv3GameMode>(UGameplayStatics::GetGameMode(GetWorld()));

		if (BirdCharacter)
		{
			if (Lv1GameMode && Lv1GameMode->bHaveKey) {
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), DoorOpenSound, GetActorLocation(), SoundFXVolume);
				DoorOpen();
			}

			if (Lv2GameMode && Lv2GameMode->bHaveKey) {
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), DoorOpenSound, GetActorLocation(), SoundFXVolume);
				DoorOpen();
			}

			if (Lv3GameMode && Lv3GameMode->bHaveKey) {
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), DoorOpenSound, GetActorLocation(), SoundFXVolume);
				DoorOpen();
			}
		}
	}
}


void ADoor::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ABirdCharacter* BirdCharacter = Cast<ABirdCharacter>(OtherActor);

		ALv1GameMode* Lv1GameMode = Cast<ALv1GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		ALv2GameMode* Lv2GameMode = Cast<ALv2GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		ALv3GameMode* Lv3GameMode = Cast<ALv3GameMode>(UGameplayStatics::GetGameMode(GetWorld()));

		if (BirdCharacter)
		{
			if (Lv1GameMode) {

				FVector SoundLocation = NextLevelTriggerVolume->GetComponentLocation();
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), TriggerSound, SoundLocation, SoundFXVolume);

				BirdCharacter->GetCharacterMovement()->DisableMovement();
				FTimerHandle TimerHandle;
				GetWorldTimerManager().SetTimer(TimerHandle, this, &ADoor::OpenVictoryMap, WarpDelay);
			}

			if (Lv2GameMode) {

				FVector SoundLocation = NextLevelTriggerVolume->GetComponentLocation();
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), TriggerSound, SoundLocation, SoundFXVolume);

				BirdCharacter->GetCharacterMovement()->DisableMovement();
				FTimerHandle TimerHandle;
				GetWorldTimerManager().SetTimer(TimerHandle, this, &ADoor::OpenVictoryMap, WarpDelay);
			}

			if (Lv3GameMode) {

				FVector SoundLocation = NextLevelTriggerVolume->GetComponentLocation();
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), TriggerSound, SoundLocation, SoundFXVolume);

				BirdCharacter->GetCharacterMovement()->DisableMovement();
				FTimerHandle TimerHandle;
				GetWorldTimerManager().SetTimer(TimerHandle, this, &ADoor::OpenVictoryMap, WarpDelay);
			}
		}
	}
}


void ADoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}


void ADoor::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}


void ADoor::DoorOpenUpdate(float YawRate)
{
	FRotator NewRotation = DoorInitialRotation;
	NewRotation.Yaw += YawRate;
	DoorMesh->SetWorldRotation(NewRotation);
}

void ADoor::OpenVictoryMap()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("Victory_Map"), true);
}
