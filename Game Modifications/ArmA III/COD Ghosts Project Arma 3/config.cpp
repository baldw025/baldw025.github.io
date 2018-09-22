class CfgPatches
{
	class SC_Custom_Faces
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"A3_Characters_F"
		};
	};
};
class CfgFaces
{
	class Default
	{
		class Custom;
	};
	class Man_A3: Default
	{
		class Default
		{
			displayname="$STR_CFG_FACES_Default";
			texture="\A3\Characters_F\Heads\Data\m_White_01_co.paa";
			head="DefaultHead_A3";
			identityTypes[]={};
			material="A3\Characters_F\Heads\Data\m_White_01.rvmat";
			textureHL="\A3\Characters_F\Heads\Data\hl_White_hairy_1_co.paa";
			materialHL="\A3\Characters_F\Heads\Data\hl_White_hairy_muscular.rvmat";
			textureHL2="\A3\Characters_F\Heads\Data\hl_White_hairy_1_co.paa";
			materialHL2="\A3\Characters_F\Heads\Data\hl_White_hairy_muscular.rvmat";
			disabled=0;
		};
		class SC_Face_Keegan: Default
		{
			displayname="K. Russ";
			texture="sc_custom_faces\data\face_keegan.paa";
			head="DefaultHead_A3";
			identityTypes[]={};
			material="sc_custom_faces\data\custom.rvmat";
			textureHL="\A3\Characters_F\Heads\Data\hl_White_hairy_1_co.paa";
			materialHL="\A3\Characters_F\Heads\Data\hl_White_hairy_muscular.rvmat";
			textureHL2="\A3\Characters_F\Heads\Data\hl_White_hairy_1_co.paa";
			materialHL2="\A3\Characters_F\Heads\Data\hl_White_hairy_muscular.rvmat";
			disabled=0;
		};
		class SC_Face_Logan: SC_Face_Keegan
		{
			displayname="L. Walker";
			texture="sc_custom_faces\data\face_logan.paa";
		};
		class SC_Face_Merrick: SC_Face_Keegan
		{
			displayname="T. Merrick";
			texture="sc_custom_faces\data\face_merrick.paa";
		};
		class SC_Face_Hesh: SC_Face_Keegan
		{
			displayname="D. Walker";
			texture="sc_custom_faces\Data\face_hesh.paa";
		};
	};
};
