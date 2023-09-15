// EGJ2022 Phanuwat Chalee

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class WATCHYAFEET_API ADoor : public AActor
{
	GENERATED_BODY()
	
	ADoor();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DoorRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* DoorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* DoorFrameMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollisionVolume;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* NextLevelTriggerVolume;

	FRotator DoorInitialRotation;

	UPROPERTY(EditAnywhere  , BlueprintReadOnly, Category = "Door", meta = (AllowPrivateAccess = "true"))
	float WarpDelay;

	UFUNCTION()
	void OpenVictoryMap();


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Door", meta = (AllowPrivateAccess = "true"))
	class USoundBase* DoorOpenSound; // Wood Door Open

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Door", meta = (AllowPrivateAccess = "true"))
	class USoundBase* TriggerSound; // Unlock Sound

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	float SoundFXVolume;

	UFUNCTION(Category = "Door", BlueprintImplementableEvent)
	void DoorOpen();

	UFUNCTION(Category = "Door", BlueprintCallable)
	void DoorOpenUpdate(float YawRate);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnTriggerBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggerEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
