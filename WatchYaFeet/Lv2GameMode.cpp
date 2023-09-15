// EGJ2022 Phanuwat Chalee


#include "Lv2GameMode.h"


ALv2GameMode::ALv2GameMode()
{
	Keyrequired = 2;
	KeyTotal    = 0;
	bHaveKey    = false;

	LevelName   = "LEVEL - 2";
	PlayerLife  = 10;
}


void ALv2GameMode::AddKey(int32 Amount)
{
	KeyTotal += Amount;

	if (KeyTotal == Keyrequired)
	{
		bHaveKey = true;
	}
}