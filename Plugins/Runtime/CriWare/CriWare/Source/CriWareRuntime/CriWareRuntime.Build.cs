/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2013-2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Build Settings of CriWareRuntime Module
 * File     : CriWareRuntime.Build.cs
 *
 ****************************************************************************/
using System.IO;

namespace UnrealBuildTool.Rules
{
    public class CriWareRuntime : ModuleRules
    {
        public CriWareRuntime(ReadOnlyTargetRules Target) : base(Target)
        {
            /* 4.15 - remove PCH includes */
            PrivatePCHHeaderFile = "Private/CriWareRuntimePrivatePCH.h";

            PrivateIncludePaths.AddRange(new string[]
            {
                "CriWareRuntime/Private",
                "CriWareRuntime/Private/Sections",
                "CriWareRuntime/Private/Tracks",
            });

            PublicDependencyModuleNames.AddRange(
                new string[] {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "CriWare",
                    "RHI",
                    "RenderCore",
                    "SlateCore",
                    "MovieScene",
                    "HeadMountedDisplay",
                    //"InternationalizationSettings",
                }
            );

            /* backward compatibility with 4.21 */
            BuildVersion Version;
            if (BuildVersion.TryRead(BuildVersion.GetDefaultFileName(), out Version) &&
                Version.MinorVersion < 22)
            {
                PublicDependencyModuleNames.Add("ShaderCore");
            }

            string engine_path = System.IO.Path.GetFullPath(Target.RelativeEnginePath);

            PrivateIncludePaths.AddRange(
                new string[] {
                    engine_path + "Source/Runtime/Engine/Private",
                }
            );

            if ((Target.Platform == UnrealTargetPlatform.Win32)
                || (Target.Platform == UnrealTargetPlatform.Win64))
            {
                PublicAdditionalLibraries.Add("propsys.lib");
                if (Target.WindowsPlatform.bNeedsLegacyStdioDefinitionsLib)
                {
                    PublicAdditionalLibraries.Add("legacy_stdio_definitions.lib");
                }
            }

            /* Intel Media SDK */
            if (Target.Platform == UnrealTargetPlatform.Win64 ||
                Target.Platform == UnrealTargetPlatform.Win32)
            {
                string IntelDir = "/../../Binaries/ThirdParty/Intel/";
                string LibName = Target.Platform == UnrealTargetPlatform.Win64 ? "libmfxsw64.dll" : "libmfxsw32.dll";
                string LibPath = IntelDir + Target.Platform.ToString() + "/" + LibName;
                if (File.Exists(ModuleDirectory + LibPath))
                {
                    RuntimeDependencies.Add(ModuleDirectory + LibPath, StagedFileType.NonUFS);
                    AddPublicDefinition("CRIWARE_USE_INTEL_MEDIA=1");
                }
            }
            /* VP9 */
            if (Target.Platform == UnrealTargetPlatform.Win64 ||
                Target.Platform == UnrealTargetPlatform.Win32 ||
                Target.Platform == UnrealTargetPlatform.Mac ||
                Target.Platform == UnrealTargetPlatform.IOS ||
                Target.Platform == UnrealTargetPlatform.Android)
            {
                string CriNativeDir = "/../ThirdParty/CriWare/cri/";
                if (Target.Platform == UnrealTargetPlatform.Win64
                    ||
                    Target.Platform == UnrealTargetPlatform.Win32) {
                    CriNativeDir += "pc";
                }
                if (Target.Platform == UnrealTargetPlatform.Mac) {
                    CriNativeDir += "macosx";
                }
                if (Target.Platform == UnrealTargetPlatform.IOS) {
                    CriNativeDir += "ios";
                }
                if (Target.Platform == UnrealTargetPlatform.Android) {
                    CriNativeDir += "android";
                }

                string LibHeaderPath = CriNativeDir + "/include/" + "cri_mana_vp9.h";

                if (File.Exists(ModuleDirectory + LibHeaderPath))
                {
                    AddPublicDefinition("CRIWARE_USE_MANA_VP9=1");
                }
            }

            if (Target.bBuildEditor == true)
            {
                PublicDependencyModuleNames.Add("UnrealEd");
                PublicDependencyModuleNames.Add("Matinee");
                PrivateIncludePathModuleNames.Add("CriWareEditor");
                PublicIncludePathModuleNames.Add("CriWareEditor");
                DynamicallyLoadedModuleNames.Add("CriWareEditor");
            }

            UnrealTargetPlatform TargetPlatformValue;
            bool bSupported = ((Target.Platform == UnrealTargetPlatform.Win32)
                || (Target.Platform == UnrealTargetPlatform.Win64)
                || (Target.Platform == UnrealTargetPlatform.PS4)
                || (Target.Platform == UnrealTargetPlatform.XboxOne)
                || (Target.Platform == UnrealTargetPlatform.Switch)
                || (Target.Platform == UnrealTargetPlatform.Mac)
                || (Target.Platform == UnrealTargetPlatform.IOS)
                || (Target.Platform == UnrealTargetPlatform.Linux)
                || (Target.Platform == UnrealTargetPlatform.Android)
                /* MICROSOFT_UWP_UNREAL - UWP support */
                || (System.Enum.TryParse("UWP32", out TargetPlatformValue) && Target.Platform == TargetPlatformValue)
                || (System.Enum.TryParse("UWP64", out TargetPlatformValue) && Target.Platform == TargetPlatformValue));

            AddPublicDefinition(string.Format("WITH_CRIWARE={0}", bSupported ? 1 : 0));
        }

        public void AddPublicDefinition(string Definition)
        {
            string PublicDefinitionsPropertyName = "PublicDefinitions";

            /* backward compatibility with 4.18 */
            BuildVersion Version;
            if (BuildVersion.TryRead(BuildVersion.GetDefaultFileName(), out Version) &&
                Version.MinorVersion < 19) {
                PublicDefinitionsPropertyName = "Definitions";
            }
            // <PublicDefinitions>.Add(Definition)
            object PublicDefinitions = GetType().GetField(PublicDefinitionsPropertyName).GetValue(this);
            PublicDefinitions.GetType().GetMethod("Add").Invoke(PublicDefinitions, new object[] { Definition });
            Definitions.Add(string.Format("CRIWARE_UE4_LE=1"));
        }
    }
}
