/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2013-2017 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Build Settings of CriWare Module
 * File     : CriWare.Build.cs
 *
 ****************************************************************************/
using System.IO;
namespace UnrealBuildTool.Rules
{
	public class CriWare : ModuleRules
	{
		public CriWare(ReadOnlyTargetRules Target) : base(Target)
        {
			Type = ModuleType.External;

            string CriWarePath = Path.Combine(ModuleDirectory, "cri/");
	
	        if (Target.Platform == UnrealTargetPlatform.Win64) {
				PublicIncludePaths.Add(CriWarePath + "pc/include");
				PublicLibraryPaths.Add(CriWarePath + "pc/libs/x64");
                PublicAdditionalLibraries.AddRange(
                    new string[] {
                            CriWarePath + "pc/libs/x64/cri_ware_pcx64_le_import.lib"
                    }
                );
                PublicDelayLoadDLLs.Add("cri_ware_pcx64_le.dll");
                PrivateDependencyModuleNames.AddRange(new string[] { "CriWareRuntime" });
                RuntimeDependencies.Add(new RuntimeDependency(CriWarePath + "pc/libs/x64/cri_ware_pcx64_le.dll"));

			}
            else if (Target.Platform == UnrealTargetPlatform.Mac) {
				PublicFrameworks.AddRange(new string[] { "CoreAudio", "AudioToolbox", "AudioUnit" });
				PublicIncludePaths.Add(CriWarePath + "macosx/include");
				PublicLibraryPaths.Add(CriWarePath + "macosx/libs");
                PublicAdditionalLibraries.AddRange(
                    new string[] {
                            CriWarePath + "macosx/libs/libcri_ware_macosx_le.a"
                    }
                );
            } 
        }
	}
}
