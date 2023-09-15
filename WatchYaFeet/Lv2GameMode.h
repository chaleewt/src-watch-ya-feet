// EGJ2022 Phanuwat Chalee


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Lv2GameMode.generated.h"



UCLASS()
class WATCHYAFEET_API ALv2GameMode : public AGameModeBase
{
	GENERATED_BODY()

	ALv2GameMode  ();


public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly , Category = "Lv2")
	int32 Keyrequired;

	UPROPERTY(VisibleAnywhere , BlueprintReadWrite, Category = "Lv2")
	bool  bHaveKey;

	UPROPERTY(VisibleAnywhere , BlueprintReadWrite, Category = "Lv2")
	int32 KeyTotal;

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , Category = "Lv2")
	FString LevelName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Lv2")
	int32 PlayerLife;

	UPROPERTY(VisibleAnywhere , BlueprintReadWrite, Category = "Lv2")
	bool bPlayerDie = false;

	UFUNCTION()
	void AddKey(int32 Amount);
};
