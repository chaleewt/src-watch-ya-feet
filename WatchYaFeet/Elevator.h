// EGJ2022 Phanuwat Chalee

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Elevator.generated.h"

UCLASS()
class WATCHYAFEET_API AElevator : public APawn
{
	GENERATED_BODY()

	AElevator();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elevator", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ElevatorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elevator", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ElevatorSubMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elevator", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent*  BoxCollisionVolume;

	FVector ElevatorInitialLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Elevator", meta = (AllowPrivateAccess = "true"))
    class USoundBase* ElevatorSound;

	class ABirdCharacter* BirdCharacter;

	//.. Wall Collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elevator", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WallCollisionVolumeTop;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elevator", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WallCollisionVolumeBelow;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elevator", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WallCollisionVolumeLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elevator", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WallCollisionVolumeRight;

public:

	UFUNCTION(Category = "Elevator", BlueprintImplementableEvent)
	void ElevatorDown();

	UFUNCTION(Category = "Elevator", BlueprintImplementableEvent, BlueprintCallable)
	void ElevatorUp  ();

	UFUNCTION(Category = "Elevator", BlueprintCallable)
	void UpdateElevatorPosition(float Z);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
