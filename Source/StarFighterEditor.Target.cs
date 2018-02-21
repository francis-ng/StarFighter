// Francis Ng 2017-2018

using UnrealBuildTool;
using System.Collections.Generic;

public class StarFighterEditorTarget : TargetRules
{
	public StarFighterEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "StarFighter" } );
	}
}
