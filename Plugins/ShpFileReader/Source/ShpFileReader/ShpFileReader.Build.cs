// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class ShpFileReader : ModuleRules
{
	public ShpFileReader(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core","Projects"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

        PublicDefinitions.Add("NOMINMAX");

        string PluginRoot = Path.GetFullPath(Path.Combine(ModuleDirectory, "..", ".."));
        string GDALRoot = Path.Combine(PluginRoot, "ThirdParty", "GDAL");

        // Include GDAL headers
        PublicIncludePaths.Add(Path.Combine(GDALRoot, "include"));

        // Link GDAL static library
        PublicAdditionalLibraries.Add(Path.Combine(GDALRoot, "lib", "gdal_i.lib"));

        // Delay-load the main GDAL DLL
        PublicDelayLoadDLLs.Add("gdal.dll");

        // Recursively add ALL files in ThirdParty/GDAL/bin to Binaries/Win64
        string GdalBinSourceDir = Path.Combine(GDALRoot, "bin");
        string PluginBinTargetDir = "$(PluginDir)/Binaries/Win64";

        if (Directory.Exists(GdalBinSourceDir))
        {
            foreach (string SrcPath in Directory.GetFiles(GdalBinSourceDir, "*", SearchOption.AllDirectories))
            {
                string RelativePath = SrcPath.Substring(GdalBinSourceDir.Length + 1); // skip base path + slash
                string DestPath = Path.Combine(PluginBinTargetDir, RelativePath).Replace("\\", "/");

                RuntimeDependencies.Add(DestPath, SrcPath, StagedFileType.NonUFS);
            }
        }


    }
}
