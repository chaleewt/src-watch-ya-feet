// EGJ2022 Phanuwat Chalee


#include "Lv3GameMode.h"


ALv3GameMode::ALv3GameMode()
{
	Keyrequired = 3;
	KeyTotal    = 0;
	bHaveKey    = false;

	LevelName   = "LEVEL - 3";
	PlayerLife  = 20;
}


void ALv3GameMode::AddKey(int32 Amount)
{
	KeyTotal += Amount;

	if (KeyTotal == Keyrequired)
	{
		bHaveKey = true;
	}
}