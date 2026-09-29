// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnrealGoogleAnalytics : ModuleRules
{
	public UnrealGoogleAnalytics(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
		});
		
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"CoreUObject", "Engine",
			"Slate", "SlateCore",
			"DeveloperSettings", "HTTP"
		});
	}
}
