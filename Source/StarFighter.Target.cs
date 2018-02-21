// Francis Ng 2017-2018

using UnrealBuildTool;
using System.Collections.Generic;

public class StarFighterTarget : TargetRules
{
	public StarFighterTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "StarFighter" } );
	}
}
