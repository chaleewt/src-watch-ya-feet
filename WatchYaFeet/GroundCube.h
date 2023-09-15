// EGJ2022 Phanuwat Chalee

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundCube.generated.h"

UCLASS()
class WATCHYAFEET_API AGroundCube : public AActor
{
	GENERATED_BODY()
	
	AGroundCube   ();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly, Category = "GroundCube", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* GroundCube;

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly, Category = "GroundCube", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* ReactCollisionVolume;


	//.. Initial Location Of The Cube!!
	FVector GroundCubeInstanceLocation;

	UPROPERTY(EditAnywhere   , BlueprintReadOnly, Category = "GroundCube", meta = (AllowPrivateAccess = "true"))
	float BounceRate;
	
	//.. Trap Collisions
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly, Category = "GroundCube", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* TrapCollisionVolume;

	//.. Trap Explosion Sound
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GroundCube", meta = (AllowPrivateAccess = "true"))
	class USoundBase* TrapHitSound; // Hit Sound


	UPROPERTY()
	class ABirdCharacter* PlayerCharacter;

	void ReleasePlayer();

	UPROPERTY(EditAnywhere, Category = "GroundCube", meta = (AllowPrivateAccess = "true"), meta = (ToolTip = "Player unable to move when hit the trap"))
	float TrapLockTime;

public:

	//.. Trap
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GroundCube")
	bool bIsTrap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GroundCube")
	float SoundFXVolume;

	UFUNCTION(BlueprintImplementableEvent, Category = "GroundCube")
	void Rise();

	UFUNCTION(BlueprintImplementableEvent, Category = "GroundCube")
	void Down();

	UFUNCTION(Category = "GroundCube", BlueprintCallable)
	void UpdateGroundPosition(float Z);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//.. Trap
	UFUNCTION()
	void OnOverlapTrapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapTrapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
