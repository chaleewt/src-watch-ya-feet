// EGJ2022 Phanuwat Chalee


#include "BirdAnimInstance.h"
#include "BirdCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void UBirdAnimInstance::NativeInitializeAnimation()
{
	GetBirdCharacterRef();
}

void UBirdAnimInstance::UpdateAnimationProperties()
{
	if (!BirdCharacter) { GetBirdCharacterRef(); }

	if ( BirdCharacter)
	{
		FVector Velocity = BirdCharacter->GetVelocity();
		FVector LateralSpeed = FVector(Velocity.X, Velocity.Y, 0.f);
		Speed = LateralSpeed.Size();

		bIsInAir = BirdCharacter->GetCharacterMovement()->IsFalling();
	}
}

void UBirdAnimInstance::GetBirdCharacterRef()
{
	if (BirdCharacter == NULL) 
	{
		BirdCharacter = Cast<ABirdCharacter>(TryGetPawnOwner());
	}
}
