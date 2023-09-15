// EGJ2022 Phanuwat Chalee

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Lv1GameMode.generated.h"


UCLASS()
class WATCHYAFEET_API ALv1GameMode : public AGameModeBase
{
	GENERATED_BODY()

	ALv1GameMode  ();


public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly , Category = "Lv1")
	int32 Keyrequired;

	UPROPERTY(VisibleAnywhere , BlueprintReadWrite, Category = "Lv1")
	bool  bHaveKey;

	UPROPERTY(VisibleAnywhere , BlueprintReadWrite, Category = "Lv1")
	int32 KeyTotal;

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , Category = "Lv1")
	FString LevelName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Lv1")
	int32 PlayerLife;

	UPROPERTY(VisibleAnywhere , BlueprintReadWrite, Category = "Lv1")
	bool bPlayerDie = false;

	UFUNCTION()
	void AddKey(int32 Amount);

	
};
