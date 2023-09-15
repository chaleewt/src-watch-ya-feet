// EGJ2022 Phanuwat Chalee

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Padlock.generated.h"

UCLASS()
class WATCHYAFEET_API APadlock : public AActor
{
	GENERATED_BODY()
	
	APadlock();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Padlock(Key)", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* KeyRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Padlock(Key)", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* KeyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Padlock(Key)", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollisionVolume;

	//.. Sound Component
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Padlock(Key)", meta = (AllowPrivateAccess = "true"))
	class USoundBase* KeyOverlapSound; // Pickup Sound

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Padlock(Key)")
	float SoundFXVolume;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Padlock(Key)")
	int32 KeyValue;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
