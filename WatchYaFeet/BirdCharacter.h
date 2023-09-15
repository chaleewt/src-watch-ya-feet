// EGJ2022 Phanuwat Chalee

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BirdCharacter.generated.h"

UCLASS()
class WATCHYAFEET_API ABirdCharacter : public ACharacter
{
	GENERATED_BODY()

	ABirdCharacter();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float OnDestroyTime;

protected:

	void MoveForward(float Value);

	void MoveRight  (float Value);


public:


	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return   CameraBoom; }
	FORCEINLINE class UCameraComponent*  GetFollowCamera() const { return FollowCamera; }

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void OnPlayerDestroy();

	void   PlayerDestroy();

	//.. Gaurd Case for Trap Prevent it from explode multiple times
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BirdCharacter")
	bool bDying = false;

	UPROPERTY(BlueprintReadWrite, Category = "BirdCharacter")
	bool bIsAbove;
};
