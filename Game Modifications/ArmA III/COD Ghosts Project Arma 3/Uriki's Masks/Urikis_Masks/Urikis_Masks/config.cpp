class CfgPatches
{
	class STALKER
	{
		units[]={};
		weapons[]=
		requiredVersion=0.1;
		requiredAddons[]={};
	};
};
class CfgGlasses
{
	class G_Balaclava_lowprofile;
	class G_Bandanna_blk;
	class UR_G_Bandanna_Beast_Red: G_Bandanna_blk
	{
		author="GrandCannon";
		displayName="Ajax's Mask";
		hiddenSelectionsTextures[]=
		{
			"\WeAreGhosts\Data\Ajax_Mask.paa"
		};
	};
	class UR_G_Bandanna_Beast_Red_Avi: G_Bandanna_aviator
	{
		author="Uriki9";
		displayName="Bandanna (Beast Red - Aviators)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\Beast\Beast_Red.paa",
			"\a3\characters_f\heads\glasses\data\glass_ca.paa"
		};
		picture="\A3\Characters_F_Bootcamp\Data\UI\icon_G_BandMask_tan_ca.paa";
	};
	class UR_G_Bandanna_Beast_Grey: G_Bandanna_blk
	{
		author="Uriki9";
		displayName="Bandanna (Beast Grey)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\Beast\Beast_Grey.paa"
		};
		picture="\A3\Characters_F_Bootcamp\Data\UI\icon_G_BandMask_tan_ca.paa";
	};
	class UR_G_Bandanna_Beast_Grey_Avi: G_Bandanna_aviator
	{
		author="Uriki9";
		displayName="Bandanna (Beast Grey - Aviators)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\Beast\Beast_Grey.paa",
			"\a3\characters_f\heads\glasses\data\glass_ca.paa"
		};
		picture="\A3\Characters_F_Bootcamp\Data\UI\icon_G_BandMask_tan_ca.paa";
	};
	class UR_G_Bandanna_Tan_Avi: G_Bandanna_aviator
	{
		author="Uriki9";
		displayName="Bandanna (Tan - Aviators)";
		hiddenSelectionsTextures[]=
		{
			"\A3\Characters_F_Bootcamp\Guerrilla\Data\headgear_bandMask_tan_co.paa",
			"\a3\characters_f\heads\glasses\data\glass_ca.paa"
		};
		picture="\A3\Characters_F_Bootcamp\Data\UI\icon_G_BandMask_tan_ca.paa";
	};
	class UR_G_Bandanna_Oli_Avi: G_Bandanna_aviator
	{
		author="Uriki9";
		displayName="Bandanna (Olive - Aviators)";
		hiddenSelectionsTextures[]=
		{
			"\A3\Characters_F_Bootcamp\Guerrilla\Data\headgear_bandMask_grn_co.paa",
			"\a3\characters_f\heads\glasses\data\glass_ca.paa"
		};
		picture="\A3\Characters_F_Bootcamp\Data\UI\icon_G_BandMask_olive_ca.paa";
	};
	class UR_G_Bandanna_Kha_Avi: G_Bandanna_aviator
	{
		author="Uriki9";
		displayName="Bandanna (Khaki - Aviators)";
		hiddenSelectionsTextures[]=
		{
			"\A3\Characters_F_Bootcamp\Guerrilla\Data\headgear_bandMask_khk_co.paa",
			"\a3\characters_f\heads\glasses\data\glass_ca.paa"
		};
		picture="\A3\Characters_F_Bootcamp\Data\UI\icon_G_BandMask_khaki_ca.paa";
	};
	class UR_G_Bandanna_Beast_Avi: G_Bandanna_aviator
	{
		author="Uriki9";
		displayName="Bandanna (Beast - Aviators)";
		hiddenSelectionsTextures[]=
		{
			"\A3\Characters_F_Bootcamp\Guerrilla\Data\headgear_bandMask_beast_co.paa",
			"\a3\characters_f\heads\glasses\data\glass_ca.paa"
		};
		picture="\A3\Characters_F_Bootcamp\Data\UI\icon_G_BandMask_beast_ca.paa";
	};
	hiddenSelectionsTextures[]=
	{
		"\A3\Characters_F_Bootcamp\Guerrilla\Data\headgear_bandMask_beast_co.paa"
	};
	class UR_H_Bandanna_mouthDirty: G_Bandanna_blk
	{
		author="Uriki9";
		displayName="Uriki's Bandanna (Mouth Dirty - Black)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\mouths\Mouth_Dirty.paa"
		};
	};
	class UR_H_Bandanna_mouthSnarl: G_Bandanna_blk
	{
		author="Uriki9";
		displayName="Uriki's Bandanna (Mouth Snarl - Black)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\mouths\Mouth_Snarl.paa"
		};
	};
	class UR_H_Bandanna_clownColour: G_Bandanna_blk
	{
		author="Uriki9";
		displayName="Uriki's Bandanna (Colour Clown - Black)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\clowns\Colour_Clown.paa"
		};
	};
	class UR_H_Bandanna_clownCigar: G_Bandanna_blk
	{
		author="Uriki9";
		displayName="Uriki's Bandanna (Cigar Clown - Black)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\clowns\Cigar_Clown.paa"
		};
	};
	class UR_G_Balaclava_Deadpool: G_Balaclava_oli
	{
		author="Uriki9";
		displayName="Uriki's Balaclava (Deadpool)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\heros\Balaclava_Deadpool.paa"
		};
	};
	class UR_G_Balaclava_Deathstroke: G_Balaclava_oli
	{
		author="Uriki9";
		displayName="Uriki's Balaclava (Deathstroke)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\heros\Balaclava_Deathstroke.paa"
		};
	};
	class UR_G_Balaclava_Emile_Blk: G_Balaclava_oli
	{
		author="Uriki9";
		displayName="Uriki's Balaclava (Emile - Black)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\emile\Balaclava_Emile_Blk.paa"
		};
	};
	class UR_G_Balaclava_Emile_Lush: G_Balaclava_oli
	{
		author="Uriki9";
		displayName="Uriki's Balaclava (Emile - Lush)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\emile\Balaclava_Emile_Lsh.paa"
		};
	};
	class UR_G_Balaclava_Emile_Ard: G_Balaclava_oli
	{
		author="Uriki9";
		displayName="Uriki's Balaclava (Emile - Arid)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\emile\Balaclava_Emile_Ard.paa"
		};
	};
	class UR_H_Bandanna_GhostRecon_Khaki: G_Bandanna_blk
	{
		author="Uriki9";
		displayName="Uriki's Bandanna (Recon - Khaki)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\ghost_recon\Balaclava_GhostRecon_Khaki.paa"
		};
	};
	class UR_H_Bandanna_GhostRecon_Green: G_Bandanna_blk
	{
		author="Uriki9";
		displayName="Uriki's Bandanna (Recon - Green)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\ghost_recon\Balaclava_GhostRecon_Green.paa"
		};
	};
	class UR_H_Bandanna_GhostRecon_Black: G_Bandanna_blk
	{
		author="Uriki9";
		displayName="Uriki's Bandanna (Recon - Black)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\ghost_recon\Balaclava_GhostRecon_Black.paa"
		};
	};
	class UR_G_Balaclava_CodGhosts_01_Blk_LPG: G_Balaclava_lowprofile
	{
		author="Uriki9";
		displayName="Uriki's Balaclava (Ghosts 01 - Black, Goggles)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\cod_ghosts\Balaclava_CodGhosts_01_Blk.paa",
			"\a3\characters_f\heads\glasses\data\lowprofile_black_ca.paa"
		};
	};
	class UR_G_Balaclava_CodGhosts_01_Blk: G_Balaclava_oli
	{
		author="Uriki9";
		displayName="Uriki's Balaclava (Ghosts 01 - Black)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\cod_ghosts\Balaclava_CodGhosts_01_Blk.paa"
		};
	};
	class UR_G_Balaclava_CodGhosts_01_Lsh: G_Balaclava_oli
	{
		author="Uriki9";
		displayName="Uriki's Balaclava (Ghosts 01 - Lush)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\cod_ghosts\Balaclava_CodGhosts_01_Lsh.paa"
		};
	};
	class UR_G_Balaclava_CodGhosts_01_Ard: G_Balaclava_oli
	{
		author="Uriki9";
		displayName="Uriki's Balaclava (Ghosts 01 - Arid)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\cod_ghosts\Balaclava_CodGhosts_01_Ard.paa"
		};
	};
	class UR_G_Balaclava_CodGhosts_02_Blk_LPG: G_Balaclava_lowprofile
	{
		author="Uriki9";
		displayName="Uriki's Balaclava (Ghosts 02 - Black, Goggles)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\cod_ghosts\Balaclava_CodGhosts_02_Blk.paa",
			"\a3\characters_f\heads\glasses\data\lowprofile_black_ca.paa"
		};
	};
	class UR_G_Balaclava_CodGhosts_02_Blk: G_Balaclava_oli
	{
		author="Uriki9";
		displayName="Uriki's Balaclava (Ghosts 02 - Black)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\cod_ghosts\Balaclava_CodGhosts_02_Blk.paa"
		};
	};
	class UR_G_Balaclava_CodGhosts_02_Lsh: G_Balaclava_oli
	{
		author="Uriki9";
		displayName="Uriki's Balaclava (Ghosts 02 - Lush)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\cod_ghosts\Balaclava_CodGhosts_02_Lsh.paa"
		};
	};
	class UR_G_Balaclava_CodGhosts_02_Ard: G_Balaclava_oli
	{
		author="Uriki9";
		displayName="Uriki's Balaclava (Ghosts 02 - Arid)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\cod_ghosts\Balaclava_CodGhosts_02_Ard.paa"
		};
	};
	class UR_G_Balaclava_CodGhosts_03_Blk_LPG: G_Balaclava_lowprofile
	{
		author="Uriki9";
		displayName="Uriki's Balaclava (Ghosts 03 - Black, Goggles)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\cod_ghosts\Balaclava_CodGhosts_03_Blk.paa",
			"\a3\characters_f\heads\glasses\data\lowprofile_black_ca.paa"
		};
	};
	class UR_G_Balaclava_CodGhosts_03_Blk: G_Balaclava_oli
	{
		author="Uriki9";
		displayName="Uriki's Balaclava (Ghosts 03 - Black)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\cod_ghosts\Balaclava_CodGhosts_03_Blk.paa"
		};
	};
	class UR_G_Balaclava_CodGhosts_03_Lsh: G_Balaclava_oli
	{
		author="Uriki9";
		displayName="Uriki's Balaclava (Ghosts 03 - Lush)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\cod_ghosts\Balaclava_CodGhosts_03_Lsh.paa"
		};
	};
	class UR_G_Balaclava_CodGhosts_03_Ard: G_Balaclava_oli
	{
		author="Uriki9";
		displayName="Uriki's Balaclava (Ghosts 03 - Arid)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\cod_ghosts\Balaclava_CodGhosts_03_Ard.paa"
		};
	};
	class UR_G_Bandanna_CodGhosts_04_Blk: G_Bandanna_blk
	{
		author="Uriki9";
		displayName="Uriki's Bandanna (Ghosts 04 - Black)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\cod_ghosts\Bandanna_CodGhosts_04_Blk.paa"
		};
	};
	class UR_G_Bandanna_Skull_01_Black_Avi: G_Bandanna_aviator
	{
		author="Uriki9";
		displayName="Uriki's Bandanna (Skull 01  - Aviators Black)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\skulls\Skull_01_Black.paa",
			"\a3\characters_f\heads\glasses\data\glass_ca.paa"
		};
	};
	class UR_G_Bandanna_Skull_01_Black: G_Bandanna_blk
	{
		author="Uriki9";
		displayName="Uriki's Bandanna (Skull 01 - Black)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\skulls\Skull_01_Black.paa"
		};
	};
	class UR_G_Bandanna_Skull_01_Khaki: G_Bandanna_blk
	{
		author="Uriki9";
		displayName="Uriki's Bandanna (Skull 01 - Khaki)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\skulls\Skull_01_Khaki.paa"
		};
	};
	class UR_G_Bandanna_Skull_01_Green: G_Bandanna_blk
	{
		author="Uriki9";
		displayName="Uriki's Bandanna (Skull 01 - Green)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\skulls\Skull_01_Green.paa"
		};
	};
	class UR_G_Bandanna_Tribal_01_Blk: G_Bandanna_blk
	{
		author="Uriki9";
		displayName="Uriki's Bandanna (Tribal 01 - Black)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\tribal\Bandanna_Tribal_01_Blk.paa"
		};
	};
	class UR_G_Bandanna_Tribal_01_Grn: G_Bandanna_blk
	{
		author="Uriki9";
		displayName="Uriki's Bandanna (Tribal 01 - Green)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\tribal\Bandanna_Tribal_01_Grn.paa"
		};
	};
	class UR_G_Bandanna_Tribal_01_Khk: G_Bandanna_blk
	{
		author="Uriki9";
		displayName="Uriki's Bandanna (Tribal 01 - Khaki)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\tribal\Bandanna_Tribal_01_Khk.paa"
		};
	};
	class UR_G_Bandanna_Tribal_02_Blk: G_Bandanna_blk
	{
		author="Uriki9";
		displayName="Uriki's Bandanna (Tribal 02 - Black)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\tribal\Bandanna_Tribal_02_Blk.paa"
		};
	};
	class UR_G_Bandanna_Tribal_02_Grn: G_Bandanna_blk
	{
		author="Uriki9";
		displayName="Uriki's Bandanna (Tribal 02 - Green)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\tribal\Bandanna_Tribal_02_Grn.paa"
		};
	};
	class UR_G_Bandanna_Tribal_02_Khk: G_Bandanna_blk
	{
		author="Uriki9";
		displayName="Uriki's Bandanna (Tribal 02 - Khaki)";
		hiddenSelectionsTextures[]=
		{
			"\Urikis_Masks\Textures\tribal\Bandanna_Tribal_02_Khk.paa"
		};
	};
};
class cfgMods
{
	author="Uriki9";
	timepacked="1496722869";
};
