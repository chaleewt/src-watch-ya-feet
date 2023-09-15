// EGJ2022 Phanuwat Chalee


#include "Elevator.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BirdCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Lv1GameMode.h"
#include "Lv2GameMode.h"
#include "Lv3GameMode.h"


AElevator::AElevator()
{
	PrimaryActorTick.bCanEverTick = true;

	ElevatorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ElevatorMesh"));
	RootComponent = ElevatorMesh;
	ElevatorMesh->SetMobility(EComponentMobility::Movable);

	ElevatorSubMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ElevatorSubMesh"));
	ElevatorSubMesh->SetupAttachment(GetRootComponent());

	BoxCollisionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionVolume"));
	BoxCollisionVolume->SetupAttachment(GetRootComponent());
	BoxCollisionVolume->InitBoxExtent(FVector(80.f, 80.f, 32.f));
	BoxCollisionVolume->SetRelativeLocation(FVector(0.f, 0.f, 190.f));

	//.. Wall Collision
	WallCollisionVolumeTop = CreateDefaultSubobject<UBoxComponent>(TEXT("WallCollisionVolumeTop"));
	WallCollisionVolumeTop->SetupAttachment(GetRootComponent());
	WallCollisionVolumeTop->InitBoxExtent(FVector(1.f, 95.f, 50.f));
	WallCollisionVolumeTop->SetRelativeLocation(FVector(0.f, 0.f, 190.f));

	WallCollisionVolumeBelow = CreateDefaultSubobject<UBoxComponent>(TEXT("WallCollisionVolumeBelow"));
	WallCollisionVolumeBelow->SetupAttachment(GetRootComponent());
	WallCollisionVolumeBelow->InitBoxExtent(FVector(1.f, 95.f, 50.f));
	WallCollisionVolumeBelow->SetRelativeLocation(FVector(0.f, 0.f, 190.f));

	WallCollisionVolumeLeft = CreateDefaultSubobject<UBoxComponent>(TEXT("WallCollisionVolumeLeft"));
	WallCollisionVolumeLeft->SetupAttachment(GetRootComponent());
	WallCollisionVolumeLeft->InitBoxExtent(FVector(1.f, 95.f, 50.f));
	WallCollisionVolumeLeft->SetRelativeLocation(FVector(0.f, 0.f, 190.f));

	WallCollisionVolumeRight = CreateDefaultSubobject<UBoxComponent>(TEXT("WallCollisionVolumeRight"));
	WallCollisionVolumeRight->SetupAttachment(GetRootComponent());
	WallCollisionVolumeRight->InitBoxExtent(FVector(1.f, 95.f, 50.f));
	WallCollisionVolumeRight->SetRelativeLocation(FVector(0.f, 0.f, 190.f));
}


void AElevator::BeginPlay()
{
	Super::BeginPlay();
	
	ElevatorInitialLocation = ElevatorMesh->GetComponentLocation();

	BoxCollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &AElevator::OnOverlapBegin);
	BoxCollisionVolume->OnComponentEndOverlap.AddDynamic  (this, &AElevator::OnOverlapEnd  );
}


void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AElevator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AElevator::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		BirdCharacter = Cast<ABirdCharacter>(OtherActor);

		ALv1GameMode* Lv1GameMode = Cast<ALv1GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		ALv2GameMode* Lv2GameMode = Cast<ALv2GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		ALv3GameMode* Lv3GameMode = Cast<ALv3GameMode>(UGameplayStatics::GetGameMode(GetWorld()));

		if (BirdCharacter)
		{
			if (Lv1GameMode && Lv1GameMode->bHaveKey) {

				WallCollisionVolumeTop->SetCollisionResponseToAllChannels  (ECollisionResponse::ECR_Block);
				WallCollisionVolumeBelow->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
				WallCollisionVolumeLeft->SetCollisionResponseToAllChannels (ECollisionResponse::ECR_Block);
				WallCollisionVolumeRight->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

				BirdCharacter->bIsAbove = false;
				ElevatorDown();
			}

			if (Lv2GameMode && Lv2GameMode->bHaveKey) {
				
				WallCollisionVolumeTop->SetCollisionResponseToAllChannels  (ECollisionResponse::ECR_Block);
				WallCollisionVolumeBelow->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
				WallCollisionVolumeLeft->SetCollisionResponseToAllChannels (ECollisionResponse::ECR_Block);
				WallCollisionVolumeRight->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

				BirdCharacter->bIsAbove = false;
				ElevatorDown();
			}

			if (Lv3GameMode && Lv3GameMode->bHaveKey) {
				
				WallCollisionVolumeTop->SetCollisionResponseToAllChannels  (ECollisionResponse::ECR_Block);
				WallCollisionVolumeBelow->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
				WallCollisionVolumeLeft->SetCollisionResponseToAllChannels (ECollisionResponse::ECR_Block);
				WallCollisionVolumeRight->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

				BirdCharacter->bIsAbove = false;
				ElevatorDown();
			}
		}
	}
}


void AElevator::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}


void AElevator::UpdateElevatorPosition(float Z)
{
	FVector NewLocation = ElevatorInitialLocation;
	NewLocation.Z += Z;
	ElevatorMesh->SetWorldLocation(NewLocation);
}
