// By hzFishy - 2026 - Do whatever you want with it.

using UnrealBuildTool;

public class UnrealGoogleAnalyticsEditor : ModuleRules
{
    public UnrealGoogleAnalyticsEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject", "Engine", "InputCore",
                "Slate", "SlateCore", "ToolWidgets",
                "UnrealGoogleAnalytics"
            }
        );
    }
}