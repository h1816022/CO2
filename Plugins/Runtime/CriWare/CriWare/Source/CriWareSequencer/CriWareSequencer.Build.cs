/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2017 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Build Settings of CriWareSequencer Module
 * File     : CriWareSequencer.Build.cs
 *
 ****************************************************************************/
namespace UnrealBuildTool.Rules
{
	public class CriWareSequencer : ModuleRules
	{
		public CriWareSequencer(ReadOnlyTargetRules Target) : base(Target)
        {
	        /* 4.15 - remove PCH includes */
	        PrivatePCHHeaderFile = "Private/CriWareSequencerPrivatePCH.h";
	
	        PublicDependencyModuleNames.AddRange(
				new string[] {
					"Core",
					"CoreUObject",
					"Engine",
					"UnrealEd",
					"EditorStyle",
					"SlateCore",
					"Slate",
					"AssetTools",
					"MovieScene",
					"MovieSceneTools",
					"MovieSceneTracks",
					"PropertyEditor",
					"Sequencer",
					"SharedSettingsWidgets",
					"DesktopWidgets",
					"CriWareRuntime",
					"RenderCore",
					"RHI",
				}
			);

			PrivateDependencyModuleNames.AddRange(
				new string[] {
					"Renderer",
				}
			);
		}
	}
}
