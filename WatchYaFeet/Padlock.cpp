// EGJ2022 Phanuwat Chalee


#include "Padlock.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BirdCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "Lv1GameMode.h"
#include "Lv2GameMode.h"
#include "Lv3GameMode.h"


APadlock::APadlock() :

	SoundFXVolume(0.f)
{
	PrimaryActorTick.bCanEverTick = false;

	KeyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("KeyRoot"));
	RootComponent = KeyRoot;

	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh"));
	KeyMesh->SetupAttachment(GetRootComponent());
	KeyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BoxCollisionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionVolume"));
	BoxCollisionVolume->SetupAttachment(GetRootComponent());

	KeyValue = 1;
}


void APadlock::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &APadlock::OnOverlapBegin);
	BoxCollisionVolume->OnComponentEndOverlap.AddDynamic  (this, &APadlock::OnOverlapEnd);
}


void APadlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void APadlock::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), KeyOverlapSound, GetActorLocation(), SoundFXVolume);
				Lv1GameMode->AddKey(KeyValue);
				Destroy();
			}

			if (Lv2GameMode) {
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), KeyOverlapSound, GetActorLocation(), SoundFXVolume);
				Lv2GameMode->AddKey(KeyValue);
				Destroy();
			}

			if (Lv3GameMode) {
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), KeyOverlapSound, GetActorLocation(), SoundFXVolume);
				Lv3GameMode->AddKey(KeyValue);
				Destroy();
			}
		}
	}
}


void APadlock::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

