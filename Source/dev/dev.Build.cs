using UnrealBuildTool;
using System.IO;

public class dev : ModuleRules
{
    public dev(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        CppStandard = CppStandardVersion.Cpp20;
        bEnableExceptions = true;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "CesiumRuntime"
        });

        string CesiumPluginDir = Path.Combine(ModuleDirectory, "..", "..", "Plugins", "cesium-unreal");
        string ThirdPartyInclude = Path.Combine(CesiumPluginDir, "Source", "ThirdParty", "include");
        PublicIncludePaths.Add(ThirdPartyInclude);
    }
}