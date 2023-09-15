// EGJ2022 Phanuwat Chalee

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BirdAnimInstance.generated.h"


class ABirdCharacter;

UCLASS()
class WATCHYAFEET_API UBirdAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	virtual void NativeInitializeAnimation() override;

	void GetBirdCharacterRef();

	UFUNCTION(BlueprintCallable, Category = "BirdAnimInstance", meta = (AllowPrivateAccess = "true"))
	void UpdateAnimationProperties();


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BirdAnimInstance", meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BirdAnimInstance", meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BirdAnimInstance", meta = (AllowPrivateAccess = "true"))
	ABirdCharacter* BirdCharacter;
};
