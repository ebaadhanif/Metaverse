using System.IO;
using UnrealBuildTool;

public class DISIntegerator : ModuleRules
{
    public DISIntegerator(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

       // CppStandard = CppStandardVersion.Cpp17;
        bEnableExceptions = true;
        bUseRTTI = true;

        bool bIsDebug = Target.Configuration == UnrealTargetConfiguration.Debug || Target.Configuration == UnrealTargetConfiguration.DebugGame;
        string PlatformName = Target.Platform == UnrealTargetPlatform.Win64 ? "x64" : "x86";
        string ModulePath = ModuleDirectory;
        string ThirdPartyPath = Path.Combine(ModulePath, "../../ThirdParty/DIS");

        // Include Paths
        PublicIncludePaths.AddRange(new string[] {
            Path.Combine(ModulePath, "Public"),
            Path.Combine(ThirdPartyPath, "include"), // DIS7, DISUtils, DISEnums
            //Path.Combine(ThirdPartyPath, "ThirdParty/BoostLib/include"),
            Path.Combine(ThirdPartyPath, "ThirdParty/GeographicLib/include")
        });


        string LibPath_DIS = Path.Combine(ThirdPartyPath, "lib/vs2022");
        string LibPath_Geographic = Path.Combine(ThirdPartyPath, $"ThirdParty/GeographicLib/lib/{PlatformName}/MD");


        PublicAdditionalLibraries.AddRange(new string[] {
            Path.Combine(LibPath_DIS, "DISV7.lib"),
            Path.Combine(LibPath_Geographic, "Geographic.lib")
        });


        //string BinariesPath = Path.Combine(ModulePath, "../../Binaries/Win64");

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core", "Projects"
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "CoreUObject", "Engine", "Slate", "SlateCore"
        });


        PublicDefinitions.Add("DIS7_EXPORTS=0");       // Don't export from our side
        PublicDefinitions.Add("EXPORT_MACRO=");        // Neutralize macro if used in headers
        PublicDefinitions.Add("__NVCC___WORKAROUND_GUARD=");        // Neutralize macro if used in headers
        PublicDefinitions.Add("__NVCC__=");        // Neutralize macro if used in headers

        RuntimeDependencies.Add("$(PluginDir)/Binaries/*", StagedFileType.NonUFS);
        RuntimeDependencies.Add("$(TargetOutputDir)/DISV7.dll", "$(PluginDir)/Binaries/Win64/DISV7.dll", StagedFileType.NonUFS);
        RuntimeDependencies.Add("$(PluginDir)/Content/*", StagedFileType.NonUFS);
    }
}
