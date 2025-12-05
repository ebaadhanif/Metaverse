// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AFISEDrawingsLoader : ModuleRules
{
	public AFISEDrawingsLoader(ReadOnlyTargetRules Target) : base(Target)
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
				"Core", "ProceduralMeshComponent", "Json", "JsonUtilities", "XmlParser" , "CesiumRuntime"
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

		RuntimeDependencies.Add("$(PluginDir)/AFISEDrawingsLoader.uplugin", StagedFileType.NonUFS);

		if(Target.Platform == UnrealTargetPlatform.Win64)
        {
            RuntimeDependencies.Add("$(PluginDir)/Binaries/Wind64/*", StagedFileType.NonUFS);
        }
        RuntimeDependencies.Add("$(PluginDir)/Resources/**", StagedFileType.NonUFS);
        RuntimeDependencies.Add("$(PluginDir)/Config/**", StagedFileType.NonUFS);

    }
}
