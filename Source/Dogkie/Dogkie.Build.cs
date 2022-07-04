// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Dogkie : ModuleRules
{
	public Dogkie(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "GameplayTasks", "Niagara" });
	}
}
