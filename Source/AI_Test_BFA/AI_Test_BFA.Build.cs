// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AI_Test_BFA : ModuleRules
{
	public AI_Test_BFA(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
