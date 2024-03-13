using UnrealBuildTool;

public class NeuralManagementEditor : ModuleRules
{
	public NeuralManagementEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Engine",
				"Slate",
				"UnrealEd",
				"InputCore",
				"SlateCore",
				"AssetTools",
				"DeveloperSettings",
				"NeuralManagement"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"WebOperator"
			}
		);
	}
}