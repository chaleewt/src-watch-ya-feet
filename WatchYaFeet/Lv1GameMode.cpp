// EGJ2022 Phanuwat Chalee


#include "Lv1GameMode.h"
#include "Kismet/GameplayStatics.h"

ALv1GameMode::ALv1GameMode()
{
	Keyrequired = 1;
	KeyTotal    = 0;
	bHaveKey    = false;

	LevelName   = "LEVEL - 1";
	PlayerLife  = 5;
}


void ALv1GameMode::AddKey(int32 Amount)
{
	KeyTotal += Amount;

	if (KeyTotal == Keyrequired)
	{
		bHaveKey = true;
	}
}