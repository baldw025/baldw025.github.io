include("autorun/sh_ragmod.lua")

rm.HintTime = CreateClientConVar("rm_hint_time", "3", false, false)

rm.OxygenHUDEnabled = CreateClientConVar("rm_oxygen_hud_enabled", "1", true, false)
rm.OxygenHUDTextEnabled = CreateClientConVar("rm_oxygen_hud_text_enabled", "1", true, false)
rm.OxygenHUDBarEnabled = CreateClientConVar("rm_oxygen_hud_bar_enabled", "1", true, false)

rm.AfterdeathClientEnabled = CreateClientConVar("rm_afterdeath_client_enabled", "1", true, false)
rm.AfterdeathHUDEnabled = CreateClientConVar("rm_afterdeath_hud_enabled", "1", true, false)
rm.AfterdeathHUDKillerEnabled = CreateClientConVar("rm_afterdeath_hud_killer_enabled", "1", true, false)
rm.AfterdeathHUDKillsEnabled = CreateClientConVar("rm_afterdeath_hud_kills_enabled", "1", true, false)
rm.AfterdeathHUDRespawnTimeEnabled = CreateClientConVar("rm_afterdeath_hud_respawntime_enabled", "1", true, false)
rm.AfterdeathCameraMode = CreateClientConVar("rm_afterdeath_camera_mode", "2", true, false)

rm.RagdollRecoveryHUDEnabled = CreateClientConVar("rm_ragdoll_recovery_hud_enabled", "1", true, false)

rm.RagdollBloodSpurtEnabled = CreateClientConVar("rm_ragdoll_blood_spurt_enabled", "1", true, false)
rm.RagdollBloodSpurtStyle = CreateClientConVar("rm_ragdoll_blood_spurt_style", "2", true, false)

rm.RagdollGibEffectEnabled = CreateClientConVar("rm_ragdoll_gib_effect_enabled", "1", true, false)
rm.RagdollGibEffectMultiplier = CreateClientConVar("rm_ragdoll_gib_effect_multiplier", "1", true, false)

rm.RagdollBurnDeflateEnabled = CreateClientConVar("rm_ragdoll_burn_deflate_enabled", "1", true, false)
rm.RagdollBurnDeflateData =
{
	"ValveBiped.Bip01_Head1",		0.95,
	"ValveBiped.Bip01_Spine4",		0.97,
	"ValveBiped.Bip01_Spine",		0.2,
	"ValveBiped.Bip01_L_UpperArm",	0.7,
	"ValveBiped.Bip01_R_UpperArm",	0.7,
	"ValveBiped.Bip01_Spine2",		0.8,
	"ValveBiped.Bip01_L_Forearm",	0.6,
	"ValveBiped.Bip01_R_Forearm",	0.6,
	"ValveBiped.Bip01_Pelvis",		0.9,
	"ValveBiped.Bip01_L_Hand",		0.8,
	"ValveBiped.Bip01_R_Hand",		0.8,
	"ValveBiped.Bip01_L_Thigh",		0.6,
	"ValveBiped.Bip01_R_Thigh",		0.6,
	"ValveBiped.Bip01_L_Calf",		0.6,
	"ValveBiped.Bip01_R_Calf",		0.6,
}

rm.RagdollCameraMode = CreateClientConVar("rm_ragdoll_camera_mode", "0", true, false)

rm.PPEnabled = CreateClientConVar("rm_pp_enabled", "1", true, false)
rm.PPRestrict = CreateClientConVar("rm_pp_restrict", "0", true, false)
rm.PPAddR = CreateClientConVar("rm_pp_addr", "0", true, false)
rm.PPAddG = CreateClientConVar("rm_pp_addg", "0", true, false)
rm.PPAddB = CreateClientConVar("rm_pp_addb", "0", true, false)
rm.PPBrightness = CreateClientConVar("rm_pp_brightness", "0.9", true, false)
rm.PPContrast = CreateClientConVar("rm_pp_contrast", "1.3", true, false)
rm.PPColor = CreateClientConVar("rm_pp_color", "0.4", true, false)
rm.PPMulR = CreateClientConVar("rm_pp_mulr", "1", true, false)
rm.PPMulG = CreateClientConVar("rm_pp_mulg", "1", true, false)
rm.PPMulB = CreateClientConVar("rm_pp_mulb", "1", true, false)
rm.PPBlurAlpha = CreateClientConVar("rm_pp_bluralpha", "0.7", true, false)

rm.PPMotionBlurEnabled = CreateClientConVar("rm_pp_motionblur_enabled", "1", true, false)
rm.PPMotionBlurRestrict = CreateClientConVar("rm_pp_motionblur_restrict", "0", true, false)
rm.PPMotionBlurScale = CreateClientConVar("rm_pp_motionblur_scale", "1", true, false)

local Incursion = 0
local function LoadClientLua()
	if not IsValid(LocalPlayer()) then
		Incursion = Incursion + 1
		Msg("[RagMod] Client load check #" ..Incursion.. ", returned " ..tostring(LocalPlayer()).. ".\n")
		timer.Simple(FrameTime(), LoadClientLua)
	else
		local EntityMetaTable = FindMetaTable("Entity")
		if EntityMetaTable then
			function EntityMetaTable:GetRagdollOwner()
				if self:GetNetworkedBool("rm_IsRagdoll") then
					local Owner = self:GetNetworkedEntity("rm_Owner")
					if IsValid(Owner) then
						return Owner
					end
				else
					return self:GetOwner()
				end
			end
		end
		surface.CreateFont("rm_UI",
			{
				font = "Coolvetica",
				size = 24,
				weight = 300,
				blursize = 0,
				scanlines = 0,
				antialias = 1,
				underline = false,
				italic = false,
				strikeout = false,
				symbol = false,
				rotary = false,
				shadow = false,
				additive = false,
				outline = true
			}
		)
		for Class, Name in pairs(
			{
				combine_mine = "Combine Mine",
				entityflame = "Fire",
				env_explosion = "Explosion",
				func_button = "Button",
				func_train = "Vehicle",
				func_tracktrain = "Vehicle",
				func_tank = "Turret",
				gmod_balloon = "Balloon",
				grenade_hand = "Assassain",
				HL2_Annabelle = "Annabelle",
				item_ammo_crate = "Ammunition Crate",
				nihilanth_energy_ball = "Nihilanth",
				npc_clawscanner = "Claw Scanner",
				npc_helicopter = "Combine Helicopter",
				prop_dynamic = "Prop",
				trigger_hurt = "Terrain",
				weapon_357 = "Revolver",
				weapon_annabelle = "Annabelle",
				weapon_ar2 = "AR2",
				weapon_crowbar = "Crowbar",
				weapon_crossbow = "Crossbow",
				weapon_frag = "Grenade",
				weapon_physcannon = "Gravity Gun",
				weapon_physgun = "Physics Gun",
				weapon_pistol = "Pistol",
				weapon_rpg = "RPG",
				weapon_shotgun = "Shotgun",
				weapon_smg1 = "SMG",
				weapon_striderbuster = "Magnusson Device",
				World = "Terrain",
				worldspawn = "Terrain"
			}
		) do
			language.Add(Class, Name)
		end
		if killicon then
			killicon.Add("entityflame", "HUD/killicons/entityflame", Color(255, 80, 0, 255))
			killicon.Add("player", "HUD/killicons/player", Color(255, 80, 0, 255))
			killicon.Add("prop_ragdoll", "HUD/killicons/prop_ragdoll", Color(255, 80, 0, 255))
			killicon.Add("weapon_physcannon", "HUD/killicons/weapon_physcannon", Color(255, 80, 0, 255))
			killicon.AddAlias("gmod_turret", "weapon_smg1")
			killicon.AddAlias("grenade_hand", "weapon_grenade")
			killicon.AddAlias("prop_dynamic", "prop_physics")
			killicon.AddAlias("weapon_crossbow", "crossbow_bolt")
			killicon.AddAlias("weapon_rpg", "rpg_missile")
			killicon.AddAlias("weapon_physgun", "weapon_physcannon")
		end
		usermessage.Hook("rm_lowerweapon", function(Data)
			local Weapon = Data:ReadEntity()
			if IsValid(Weapon) then
				local Holster = Data:ReadBool()
				local CancelAnimations = Data:ReadBool()
				if Holster then
					if not CancelAnimations then
						Weapon:SendWeaponAnim(ACT_VM_IDLE_LOWERED)
					end
					if Weapon.SetWeaponHoldType then
						Weapon:SetWeaponHoldType("passive")
						Weapon.HoldType = Weapon.HoldType or Weapon:GetHoldType()
					end
				else
					if not CancelAnimations then
						Weapon:SendWeaponAnim(ACT_VM_IDLE)
					end
					if Weapon.SetWeaponHoldType then
						Weapon:SetWeaponHoldType(
							(function()
								if Weapon:GetClass() == "gmod_tool" then
									return "pistol"
								elseif Weapon:GetClass() == "gmod_camera" then
									return "camera"
								elseif Weapon.HoldType then
									return Weapon.HoldType
								else
									return "normal"
								end
							end)()
						)
					end
				end
			end
		end)
		concommand.Add("rm_help", function(Ply, Command, Args)
			local Help = [[

/// Welcome, to... /////////////////////////////////////////
//                                                        //
//                                                        //
//  ======    =====    ======   =====    =====   ======   //
//  ==   ==  ==   ==  ==       == = ==  ==   ==  ==   ==  //
//  ======   =======  ==  ===  == = ==  ==   ==  ==   ==  //
//  == ==    ==   ==  ==   ==  == = ==  ==   ==  ==   ==  //
//  ==   ==  ==   ==  ======   == = ==   =====   ======   //
//                                                        //
//    ======       ==   ==  =======  ======    =======    //
//         ==      ==   ==  ==       ==   ==   ==         //
//       ==         == ==   =====    ======    ======     //
//     ==            ===    ==       == ==          ==    //
//    =======         =     =======  ==   ==   ======     //
//                                                        //
//                                                        //
/// About: RagMod 2 ////////////////////////////////////////
//                                                        //
//                                                        //
// Thank you for choosing RagMod 2 version 5!             //
//                                                        //
// This version includes cleaned-up console variables,    //
//     many fixes, and new features! The addon is also    //
//     faster, with less redundancy in the ragdolization  //
//     generation functions and other code.               //
//                                                        //
// This version is the next iteration of RagMod 2 version //
//     4.x, which was an unofficial edit of version 3b,   //
//     which, in itself, was an unofficial edit of        //
//     version 3. RagMod was originally created by        //
//     DayStranger3, better known as ds3. You can find    //
//     the original release thread for version 3 here:    //
//     http://facepunch.com/threads/718151                //
//                                                        //
// Please contact DarkShadow6 if you have any questions.  //
//     Steam: dark_shadow_6                               //
//                                                        //
// P.S.: DayStranger3 released a public beta for a newer  //
//     edition of RagMod, 3, which included many of the   //
//     features you see here. I, however, started off     //
//     using RagMod 2 v3b as a base instead. RagMod 3 was //
//     built much differently than 2 v3b, and as a direct //
//     result, was slower and buggier. If you know of a   //
//     feature that RagMod 3 (or any other addon, for     //
//     that matter) has that this version doesn't, don't  //
//     hesitate to say so; I'll try my best to impliment  //
//     it in a later version!                             //
//                                                        //
// Enjoy!                                                 //
//                                                        //
//                                                        //
/// About: What is RagMod 2? ///////////////////////////////
//                                                        //
//                                                        //
// RagMod 2 is a quickly-growing addon for Garry's Mod    //
//     that morphs your player into a ragdoll when you    //
//     take a lot of damage, fall a height, go too fast,  //
//     etc. All of these values can also be customized    //
//     with the many console variables that exist; it     //
//     supports NPC ragdolization upon them being         //
//     killed, and it even works in multiplayer!          //
// RagMod 2 also features a few neat SWEPs as a bonus,    //
//     including a rope used for climbing while           //
//     ragdolized, and a small usable parachute!          //
// RagMod 2 has a large array of console commands related //
//     to ragdolizing, recovery, and weapons, along with  //
//     other miscellaneous commands.                      //
//                                                        //
//                                                        //
/// Instructions: What do I do? ////////////////////////////
//                                                        //
//                                                        //
// To become a ragdoll, just use the rm_ragdolize console //
//     command. RagMod 2 also automatically ragdolizes    //
//     you upon reaching certain prerequisites (such as   //
//     damage, falling and speed, as stated above). All   //
//     of these values can be changed via console, listed //
//     under the heading "rm_" for proper orginization.   //
//                                                        //
// For those unaccustomed to using the console, all of    //
//     the console commands RagMod 2 uses are also        //
//     activatable via button in the RagMod 2 menu. If    //
//     you would like to use the console instead, all     //
//     commands are also listed below.                    //
//                                                        //
// Console commands:                                      //
//  ////////////////////////////////////////////////////  //
//  // Command                                 Action //  //
//  ////////////////////////////////////////////////////  //
//  // rm_ragdolize                  Become a ragdoll //  //
//  // rm_reset                Reset while ragdolized //  //
//  // rm_grab                       See grab section //  //
//  // rm_parachute             See parachute section //  //
//  // rm_lowerweapon               Lower your weapon //  //
//  // rm_holsterweapon           Holster your weapon //  //
//  // rm_dropammo 1                Drop primary ammo //  //
//  // rm_dropammo 2              Drop secondary ammo //  //
//  // rm_dropweapon                 Drop your weapon //  //
//  ////////////////////////////////////////////////////  //
//                                                        //
//                                                        //
/// Instructions: Controlling your body ////////////////////
//                                                        //
//                                                        //
// RagMod 2 features an intuitive control system that     //
//     gives you full control over your RagMod ragdoll.   //
//                                                        //
// Basic controls:                                        //
//  ////////////////////////////////////////////////////  //
//  // Key                  Ground action  Air action //  //
//  ////////////////////////////////////////////////////  //
//  // Attack 1 / 2, Jump         Recover   No action //  //
//  // Forwards                Crawl/Swim  Glide/Dive //  //
//  // Backwards                   Twitch   No change //  //
//  // Reload      Reset while ragdolized   No change //  //
//  ////////////////////////////////////////////////////  //
//                                                        //
//                                                        //
/// Instructions: Recovery /////////////////////////////////
//                                                        //
//                                                        //
// To recover (by default), press and hold any of the     //
//     listed recovery buttons. Let go of them early      //
//     to cancel recovery; however, after a set time, you //
//     will recover whether or not you are holding any    //
//     recovery button.                                   //
// If rm_ragdoll_recovery_smoothing is set to 0, you      //
//     don't need to hold recovery buttons to recover,    //
//     and will instantly recover upon pressing one, just //
//     like in older versions of RagMod.                  //
//                                                        //
//                                                        //
/// Instructions: Grab /////////////////////////////////////
//                                                        //
//                                                        //
// Upon using the grab command, you will be ragdolized    //
//     with your feet welded to the ground. You will hold //
//     your arms out, attempting to remain steady. This   //
//     tactic is very useful in situations where staying  //
//     attached to one place without much effort is a     //
//     must. If you are grabbing something and use grab   //
//     again, you will be unwelded. You can instantly     //
//     recover while grabbing an object.                  //
//                                                        //
//                                                        //
/// Instructions: Parachute ////////////////////////////////
//                                                        //
//                                                        //
// Use the parachute command if you have a parachute in   //
//     your inventory to use it whenever you like, not    //
//     just with the SWep. You can also use the parachute //
//     command again to unhook yourself from your         //
//     parachute at any time it is deployed.              //
//                                                        //
// Parachute-specific controls:                           //
//  ////////////////////////////////////////////////////  //
//  // Title / Key                             Action //  //
//  ////////////////////////////////////////////////////  //
//  // Attack 1 / 2, Jump           Release parachute //  //
//  // Forwards                          Fly forwards //  //
//  ////////////////////////////////////////////////////  //
//                                                        //
//                                                        //
/// Tips ///////////////////////////////////////////////////
//                                                        //
//                                                        //
// If you don't want to open the console to ragdolize or  //
//     change settings, remember that there is a RagMod 2 //
//     menu under the "Options" tab of the Sandbox menu.  //
//     But you knew that already, right?                  //
//                                                        //
// Try binding a key to rm_ragdolize to ragdolize         //
//     whenever you press the bound button:               //
//         bind <key> rm_ragdolize                        //
//     This works for all the other commands, too.        //
//                                                        //
// You can use the Climb Rope to rope yourself to objects //
//     to keep yourself from falling off. Surprisingly,   //
//     it's not really that good for climbing... Grab can //
//     be used as an alternative, though it's harder to   //
//     stay upright. You also don't move around as much.  //
//     Use grab for low-speed situations, and the Climb   //
//     Rope for higher speeds.                            //
//                                                        //
// When swimming, movement isn't restricted to left and   //
//     right. You can swim up and down, too! Use this to  //
//     your advantage. You can also instantly recover     //
//     while swimming.                                    //
//                                                        //
// When gliding, look all the way down while holding      //
//     forward to dive. It makes you fall at top speed in //
//     a nosedive! Just make to level out before it's too //
//     late to change your mind...                        //
//                                                        //
//                                                        //
/// Thanks /////////////////////////////////////////////////
//                                                        //
//                                                        //
// I want to thank Hentie for their help getting me past  //
//     a few roadblocks in the decapitation code and for  //
//     helping me impliment the Climb Rope SWep more      //
//     efficiently. Couldn't have done it without you.    //
//                                                        //
// I also want to thank the nice portion of the Facepunch //
//     community in general for helping me out with my    //
//     addmittedly shoddy Garry's Mod Lua skills,         //
//     reporting bugs, and otherwise being good people.   //
//     (Well, usually.)                                   //
//                                                        //
// I would also like to thank Kirk for helping out with   //
//     beta testing and some Lua help. Thanks, buddy.     //
//                                                        //
// Finally, I would like to thank some of my Steam and    //
//     real-life friends for giving some (mostly) useful  //
//     tips on what I could do to make RagMod 2 better.   //
//                                                        //
//                                                        //
////////////////////////////////////////////////////////////

]]
			local i = 1
			local function ShowHelp()
				Msg(string.sub(Help, i, i + 60))
				i = i + 61
				if i > string.len(Help) then
					return
				end
				ShowHelp()
			end
			ShowHelp()
		end)
		-- [[ Old BBP code, kept just in case Garry brings it back.
		hook.Add("OnEntityCreated", "rm_cl_DecapitationHandler", function(Ent)
			if IsValid(Ent) and Ent:GetClass() == "prop_ragdoll" then
				local Old = Ent.BuildBonePositions
				local function New(Ent, Bones, PhysBones)
					print("shit workd")
					if Ent:GetNetworkedBool("rm_IsLimb") then
						local LimbIndex = Ent:GetNetworkedInt("rm_LimbIndex")
						local LimbMatrix = Ent:GetBoneMatrix(Ent:TranslatePhysBoneToBone(LimbIndex))
						if LimbMatrix then
							rm.ModelIterateBones(Ent, function(i)
								local BoneIndex = Ent:TranslateBoneToPhysBone(i)
								if BoneIndex ~= LimbIndex then
									local BoneMatrix = Ent:GetBoneMatrix(i)
									if BoneMatrix then
										BoneMatrix:Translate(Ent:GetPhysicsObjectNum(BoneIndex):WorldToLocal(LimbMatrix:GetTranslation()))
										BoneMatrix:Scale(vector_origin)
										BoneMatrix:Rotate(vector_origin)
										Ent:SetBoneMatrix(i, BoneMatrix)
									end
								end
							end)
						end
					else
						rm.ModelIterateBones(Ent, function(i)
							if Ent:GetNetworkedBool("rm_DecapitatedBone" ..Ent:TranslateBoneToPhysBone(i)) then
								local BoneMatrix = Ent:GetBoneMatrix(i)
								if BoneMatrix then
									BoneMatrix:Translate(vector_origin)
									BoneMatrix:Scale(vector_origin)
									BoneMatrix:Rotate(Angle(0, 0, 0))
									Ent:SetBoneMatrix(i, BoneMatrix)
								end
							end
						end)
					end
				end
				if Old then
					function Ent.BuildBonePositions(...)
						Old(...)
						New(...)
					end
				else
					Ent.BuildBonePositions = New
				end
			end
		end)
		--]]
		hook.Add("PlayerFootstep", "rm_cl_PlayerFootstep", function(Ply, Pos, Foot, SoundPath, Volume, Filter)
			if rm.Enabled:GetBool() and IsValid(Ply:GetNetworkedEntity("rm_Ragdoll")) then
				return true
			end
		end)
		hook.Add("CalcView", "rm_cl_CalcView", function(Ply, origin, angles, fov, znear, zfar, vm_origin, vm_angles)
			if GetViewEntity() == Ply and rm.Enabled:GetBool() then
				local Mode = rm.AfterdeathCameraMode:GetInt()
				local Killer = Ply:GetNetworkedEntity("rm_Killer")
				if Mode > 0 and Mode < 4 and IsValid(Killer) and rm.AfterdeathEnabled:GetBool() and rm.AfterdeathClientEnabled:GetBool() then
					Killer = IsValid(Killer:GetNetworkedEntity("rm_Ragdoll")) and Killer:GetNetworkedEntity("rm_Ragdoll") or Killer
					local KillerPos = IsValid(Killer:GetPhysicsObject()) and (Killer:GetPhysicsObject():GetMassCenter() + Vector(0, 0, 5)) or (Killer:GetPos() + Vector(0, 0, 50))
					local PlyPos = (IsValid(Ply:GetNetworkedEntity("rm_Ragdoll")) and Ply:GetNetworkedEntity("rm_Ragdoll") or Ply):GetPos() + Vector(0, 0, 30)
					if Mode == 1 and (Killer:IsPlayer() or Killer:IsNPC()) then
						local Eyes = Killer:GetAttachment(Killer:LookupAttachment("eyes")) or Killer:GetAttachment(Killer:LookupAttachment("anim_attachment_head")) or Killer:GetAttachment(Killer:LookupAttachment("head"))
						local origin = nil
						local angles = nil
						if Eyes then
							origin = Eyes.Pos
							angles = Eyes.Ang
						else
							if Killer:GetClass() == "npc_barnacle" then
								origin = Killer:LocalToWorld(Vector(100, 0, 0))
								angles = Killer:GetAngles() + Angle(-90, 0, 0)
							else
								origin = Killer:LocalToWorld(Vector(-150, 0, 100))
								angles = Killer:GetAngles()
							end
						end
						return {origin = origin, angles = angles, fov = fov}
					elseif Mode == 2 then
						return {origin = PlyPos, angles = (KillerPos - PlyPos):Angle(), fov = fov}
					elseif Mode == 3 then
						return {origin = KillerPos, angles = (PlyPos - KillerPos):Angle(), fov = fov}
					end
				else
					local Ragdoll = Ply:GetNetworkedEntity("rm_Ragdoll")
					if IsValid(Ragdoll) then
						local Mode = rm.RagdollCameraMode:GetInt()
						if Mode == 1 or Mode == 2 then
							local Eyes = Ragdoll:GetAttachment(Ragdoll:LookupAttachment("eyes"))
							return {origin = Eyes.Pos + Vector(0, 0, 2), angles = (function()
								if Mode == 1 then
									return Ply:EyeAngles()
								elseif Mode == 2 then
									return Eyes.Ang
								end
							end)(), fov = fov}
						end
					end
				end
			end
		end)
		hook.Add("RenderScreenspaceEffects", "rm_cl_Effects", function()
			local PlyLocal = LocalPlayer()
			local Ragdoll = PlyLocal:GetNetworkedEntity("rm_Ragdoll")
			Ragdoll = IsValid(Ragdoll) and Ragdoll
			if rm.Enabled:GetBool() and GetViewEntity() == PlyLocal then
				local Multiplier = math.cos(math.cos(math.Clamp(1 - (PlyLocal:Health() / 100), 0, 1) * (math.pi / 2)) * (math.pi / 2))
				if rm.PPEnabled:GetBool() then
					if rm.PPRestrict:GetBool() then
						Multiplier = PlyLocal:Alive() and 0 or 1
					end
					if Multiplier > 0 then
						DrawColorModify(
							{
								["$pp_colour_addr"] = rm.PPAddR:GetFloat() * Multiplier,
								["$pp_colour_addg"] = rm.PPAddG:GetFloat() * Multiplier,
								["$pp_colour_addb"] = rm.PPAddB:GetFloat() * Multiplier,
								["$pp_colour_brightness"] = (rm.PPBrightness:GetFloat() - 1) * Multiplier,
								["$pp_colour_contrast"] = (1 - Multiplier) + (rm.PPContrast:GetFloat() * Multiplier),
								["$pp_colour_colour"] = (1 - Multiplier) + (rm.PPColor:GetFloat() * Multiplier),
								["$pp_colour_mulr"] = (rm.PPMulR:GetFloat() - 1) * Multiplier,
								["$pp_colour_mulg"] = (rm.PPMulG:GetFloat() - 1) * Multiplier,
								["$pp_colour_mulb"] = (rm.PPMulB:GetFloat() - 1) * Multiplier
							}
						)
						DrawMotionBlur((1 - Multiplier) + (rm.PPBlurAlpha:GetFloat() * Multiplier), 0.99, 0)
					end
				end
			end
		end)
		hook.Add("GetMotionBlurValues", "rm_cl_MotionBlur", function(x, y, Forward, Spin, ...)
			local PlyLocal = LocalPlayer()
			if rm.Enabled:GetBool() and GetViewEntity() == PlyLocal and rm.PPEnabled:GetBool() and rm.PPMotionBlurEnabled:GetBool() and ((rm.PPMotionBlurRestrict:GetBool() and Ragdoll) or not Ragdoll) then
				local Ragdoll = PlyLocal:GetNetworkedEntity("rm_Ragdoll")
				Ragdoll = IsValid(Ragdoll) and Ragdoll
				local Velocity = (Ragdoll or PlyLocal):GetVelocity():Angle()
				local angles = (Ragdoll or PlyLocal):GetAngles()
				local Speed = math.min((Ragdoll or PlyLocal):GetVelocity():Length() / 80000, 1)
				local x2 = math.sin(math.AngleDifference(Velocity.y, angles.y) / 360) * 4
				local y2 = math.sin(math.AngleDifference(Velocity.p, angles.p) / 360) * 4
				if x2 > 1 then
					x2 = 1 - (x2 - 1)
				elseif x2 < -1 then
					x2 = -1 - (x2 + 1)
				end
				if y2 > 1 then
					y2 = 1 - (y2 - 1)
				elseif y2 < -1 then
					y2 = -1 - (y2 + 1)
				end
				local Multiplier = rm.PPMotionBlurScale:GetFloat()
				x = x + x2 * Speed * Multiplier
				y = y + y2 * Speed * Multiplier
				Forward = Forward + Speed * Multiplier
				return x, y, Forward, Spin
			end
		end)
		hook.Add("HUDPaint", "rm_cl_HUDPaint", function()
			if rm.Enabled:GetBool() then
				local PlyLocal = LocalPlayer()
				if PlyLocal:Alive() then
					local PosX, PosY, SizeX, SizeY = ScrW() / 2, ScrH() - 70, 400, 25
					local RecoveryTimer = math.ceil(PlyLocal:GetNetworkedInt("rm_RecoveryTimer"))
					if RecoveryTimer > 0 and rm.RagdollRecoveryHUDEnabled:GetBool() and IsValid(PlyLocal:GetNetworkedEntity("rm_Ragdoll")) then
						surface.SetDrawColor(0, 0, 0, 127.5)
						surface.DrawRect(PosX - SizeX / 2, PosY, SizeX, SizeY)
						draw.DrawText("You have to wait " ..tostring(RecoveryTimer).. " " ..(RecoveryTimer == 1 and "second" or "seconds").. " to recover", "rm_UI", PosX, PosY, Color(255, 255, 255, 255), 1)
						PosY = PosY + SizeY
					end
					local Oxygen = PlyLocal:GetNetworkedFloat("rm_Oxygen")
					if Oxygen < 1 and rm.OxygenHUDEnabled:GetBool() then
						surface.SetDrawColor(0, 0, 0, 127.5)
						surface.DrawRect(PosX - SizeX / 2, PosY, SizeX, SizeY)
						if rm.OxygenHUDBarEnabled:GetBool() then
							surface.SetDrawColor(255, 255 * Oxygen, 255 * Oxygen, 127.5)
							surface.DrawRect(PosX - SizeX / 2 + 5, PosY + 5, SizeX * Oxygen - 10, SizeY - 10)
						end
						if rm.OxygenHUDTextEnabled:GetBool() then
							draw.DrawText(Oxygen <= 0 and "Drowning!" or "Oxygen", "rm_UI", PosX, PosY, Color(255, 255 * Oxygen, 255 * Oxygen, 255), 1)
						end
						PosY = PosY + SizeY
					end
				else
					if rm.AfterdeathEnabled:GetBool() and rm.AfterdeathClientEnabled:GetBool() and rm.AfterdeathHUDEnabled:GetBool() then
						local Width = ScrW()
						local Height = ScrH()
						local Size = 0
						local Text = nil
						surface.SetDrawColor(0, 0, 0, 255)
						if rm.AfterdeathHUDRespawnTimeEnabled:GetBool() then
							Size = Size + 20
							surface.DrawRect(0, Height - Size, Width, 20)
							Text = "Respawn in: "
							if not surface.GetTextSize(Text) then
								return
							end
							draw.DrawText(Text, "rm_UI", (Width - surface.GetTextSize(Text)) / 2, Height - Size, Color(255, 255, 255), 1)
							local Time = CurTime()
							local SpawnTime = PlyLocal:GetNetworkedFloat("rm_NextSpawnTime")
							local DeathTime = PlyLocal:GetNetworkedFloat("rm_DeathTime")
							Text = string.sub(tostring(math.max(SpawnTime - Time, 0)), 1, 5)
							if Text == "0" then
								Text = "0 seconds"
							else
								Text = Text .. string.rep("0", math.max(0, 4 - string.len(Text))) .. " seconds"
							end
							draw.DrawText(Text, "rm_UI", (Width + surface.GetTextSize(Text)) / 2, Height - Size, Color(255, 0, 0), 1)
						end
						if rm.AfterdeathHUDKillsEnabled:GetBool() then
							Size = Size + 20
							surface.DrawRect(0, Height - Size, Width, 20)
							Text = "Total kills: "
							draw.DrawText(Text, "rm_UI", (Width - surface.GetTextSize(Text)) / 2, Height - Size, Color(255, 255, 255), 1)
							Text = tostring(PlyLocal:GetNetworkedInt("rm_Kills"))
							draw.DrawText(Text, "rm_UI", (Width + surface.GetTextSize(Text)) / 2, Height - Size, Color(255, 0, 0), 1)
						end
						local Killer = PlyLocal:GetNetworkedEntity("rm_Killer")
						if IsValid(Killer) and rm.AfterdeathHUDKillerEnabled:GetBool() then
							Size = Size + 20
							surface.DrawRect(0, Height - Size, Width, 20)
							Text = "Killed by: "
							draw.DrawText(Text, "rm_UI", (Width - surface.GetTextSize(Text)) / 2, Height - Size, Color(255, 255, 255), 1)
							if Killer:IsPlayer() then
								Text = Killer:Nick()
							else
								Text = "#" ..Killer:GetClass():lower()
							end
							draw.DrawText(Text, "rm_UI", (Width + surface.GetTextSize(Text)) / 2, Height - Size, Color(255, 0, 0), 1)
						end
						if Size == 0 then
							Size = 20
							surface.DrawRect(0, Height - Size, Width, 20)
						end
						surface.DrawRect(0, 0, Width, Size)
						draw.DrawText("Afterdeath", "rm_UI", Width / 2, (Size - 20) / 2, Color(255, 255, 255), 1)
					end
				end
			end
		end)
		hook.Add("PhysgunPickup", "rm_cl_BlockPhysGun", function(Ply, Ent)
			if rm.Enabled:GetBool() and IsValid(Ent) and Ent:GetNetworkedBool("rm_IsRagdoll") then
				for _, Ply in pairs(player.GetAll()) do
					if Ply:GetNetworkedEntity("rm_Ragdoll") == Ent then
						if rm.RagdollPhysGunEnabled:GetBool() then
							return false
						end
					end
				end
			end
		end)
		hook.Add("Tick", "rm_cl_Tick", function()
			if rm.Enabled:GetBool() then
				if rm.RagdollBurnDeflateEnabled:GetBool() then
					for _, Ragdoll in pairs(ents.FindByClass("prop_ragdoll")) do
						if Ragdoll:IsOnFire() then
							for i = 1, #rm.RagdollBurnDeflateData, 2 do
								if math.random(1, 25) == 1 then
									local Bone = Ragdoll:LookupBone(rm.RagdollBurnDeflateData[i])
									if Bone then
										local Size = Ragdoll:GetManipulateBoneScale(Bone)
										local x, y, z = Size.x, Size.y, Size.z
										if x > 0 and y > 0 and z > 0 then
											x = x - 0.001
											y = y - 0.001
											z = z - 0.001
											local MaxSize = rm.RagdollBurnDeflateData[i + 1]
											if x < MaxSize then
												x = MaxSize
											end
											if y < MaxSize then
												y = MaxSize
											end
											if z < MaxSize then
												z = MaxSize
											end
											Ragdoll:ManipulateBoneScale(Bone, Vector(x, y, z))
										end
									end
								end
							end
						end
					end
				end
			end
		end)
	end
end
LoadClientLua()