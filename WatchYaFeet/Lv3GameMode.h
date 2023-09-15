// EGJ2022 Phanuwat Chalee

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Lv3GameMode.generated.h"



UCLASS()
class WATCHYAFEET_API ALv3GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	ALv3GameMode  ();

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly , Category = "Lv3")
	int32 Keyrequired;

	UPROPERTY(VisibleAnywhere , BlueprintReadWrite, Category = "Lv3")
	bool  bHaveKey;

	UPROPERTY(VisibleAnywhere , BlueprintReadWrite, Category = "Lv3")
	int32 KeyTotal;

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , Category = "Lv3")
	FString LevelName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Lv3")
	int32 PlayerLife;

	UPROPERTY(VisibleAnywhere , BlueprintReadWrite, Category = "Lv3")
	bool bPlayerDie = false;

	UFUNCTION()
	void AddKey(int32 Amount);
};
