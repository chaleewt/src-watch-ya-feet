// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WatchYaFeet : ModuleRules
{
	public WatchYaFeet(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "Niagara" });
	}
}