// Francis Ng 2017-2018

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectCHEditorTarget : TargetRules
{
	public ProjectCHEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "ProjectCH" } );
	}
}
