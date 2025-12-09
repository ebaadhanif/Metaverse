// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Metaverse : ModuleRules
{
	public Metaverse(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",
			"CesiumRuntime", "XmlParser","HeadMountedDisplay" , "UMG" , "Niagara", "XRBase" , "ModelingComponents", "GeometryCore", "MeshDescription", "StaticMeshDescription",
			"GeometryScriptingCore" ,"ProceduralMeshComponent",  "DynamicMesh" , "GeometryFramework",
           "AFISEDrawingsLoader" , "DISIntegerator"   ,"InputDevicesHandler","MetaverseXRSystem", "RuntimeModelsImporter" , "ShpFileReader", "Systems" , "TerrainSystemConfig" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
