// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CustomPCG : ModuleRules
{
	public CustomPCG(ReadOnlyTargetRules Target) : base(Target)
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
				"Core","PCG" , "CesiumRuntime", "Engine", "InputCore", "Projects" , "ShpFileReader",   "SQLiteSupport",  "SQLiteCore"  /* "Landscape", // ?? ADD THIS LINE*/,
                "Json", "JsonUtilities", "XmlParser" 

				// ... add other public dependencies that you statically link with here ...
			}
            );
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore", "CesiumRuntime"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...

            }
			);

        RuntimeDependencies.Add("$(PluginDir)/CustomPCG.uplugin", StagedFileType.NonUFS);

        RuntimeDependencies.Add("$(PluginDir)/Resources/**", StagedFileType.NonUFS);
        RuntimeDependencies.Add("$(PluginDir)/Config/**", StagedFileType.NonUFS);
        RuntimeDependencies.Add("$(PluginDir)/Content/**", StagedFileType.NonUFS);


    }
}
