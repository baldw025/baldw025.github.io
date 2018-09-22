local CVarSwitches = {FCVAR_NOTIFY, FCVAR_REPLICATED}

_G.rm = rm or {}
rm.Version = "v6.1"

rm.Enabled = CreateConVar("rm_enabled", "1", CVarSwitches, "Enable RagMod 2 v" ..rm.Version.. ".")
rm.EnabledDelta = rm.Enabled:GetBool()

rm.HintEnabled = CreateConVar("rm_hint_enabled", "0", CVarSwitches, "Enable client hints.")

rm.SoundEnabled = CreateConVar("rm_sound_enabled", "1", CVarSwitches, "Enable sounds.")
rm.SoundVolume = CreateConVar("rm_sound_volume", "80", CVarSwitches, "The global volume of all RagMod sounds (0 to 100).")
rm.SoundDelay = CreateConVar("rm_sound_delay", "0.25", CVarSwitches, "The delay (in seconds) before sounds can be played again.")

rm.OxygenEnabled = CreateConVar("rm_oxygen_enabled", "0", CVarSwitches, "Enable oxygen while underwater.")
rm.OxygenValue = CreateConVar("rm_oxygen_value", "30", CVarSwitches, "The amount of oxygen a player has in seconds.")
rm.OxygenRegenerateValue = CreateConVar("rm_oxygen_regenerate_value", "2.5", CVarSwitches, "The multiplier a player will regenerate oxygen at (ex. a player can regenerate oxygen this number of times faster than the speed at which it is lost).")
rm.OxygenDrownDelay = CreateConVar("rm_oxygen_drown_delay", "1", CVarSwitches, "The delay players can take drown damage at in seconds.")
rm.OxygenDrownDamage = CreateConVar("rm_oxygen_drown_damage", "5", CVarSwitches, "The damage players take while drowning.")

rm.AfterdeathEnabled = CreateConVar("rm_afterdeath_enabled", "1", CVarSwitches, "Enable Afterdeath.")

rm.RespawnDelay = CreateConVar("rm_respawn_delay", "1", CVarSwitches, "The number of seconds a player must wait before respawning.")

rm.NinjaModeEnabled = CreateConVar("rm_ninjamode_enabled", "0", CVarSwitches, "This console variable has no use. I do not recommend modifying it in any way, shape, or form; doing so may void your warranty.")

rm.RagdollRecoveryEnabled = CreateConVar("rm_ragdoll_recovery_enabled", "1", CVarSwitches, "Enable recovery from ragdolization (to remove the timer, see rm_ragdoll_recovery_timer_enabled).")
rm.RagdollRecoverySmoothingEnabled = CreateConVar("rm_ragdoll_recovery_smoothing_enabled", "1", CVarSwitches, "Enable recovery smoothing.")
rm.RagdollRecoveryDelayEnabled = CreateConVar("rm_ragdoll_recovery_delay_enabled", "0", CVarSwitches, "Enable the recovery delay timer (if disabled, players can recover immediately).")
rm.RagdollRecoveryDelayOnExplosion = CreateConVar("rm_ragdoll_recovery_delay_onexplosion", "1", CVarSwitches, "The number of seconds a player must wait before getting back up when when ragdolzied by being caught in an explosion.")
rm.RagdollRecoveryDelayOnEject = CreateConVar("rm_ragdoll_recovery_delay_oneject", "1", CVarSwitches, "The number of seconds a player must wait before getting back up when ragdolzied by ejecting from a seat.")
rm.RagdollRecoveryDelayOnFall = CreateConVar("rm_ragdoll_recovery_delay_onfall", "1", CVarSwitches, "The number of seconds a player must wait before getting back up when ragdolzied by taking fall damage or when going faster than a certain value.")
rm.RagdollRecoveryDelayOnPlayer = CreateConVar("rm_ragdoll_recovery_delay_onplayer", "1", CVarSwitches, "The number of seconds a player must wait before getting back up when ragdolzied by taking damage from a player or NPC.")
rm.RagdollRecoveryDelayDefault = CreateConVar("rm_ragdoll_recovery_delay_default", "1", CVarSwitches, "The number of seconds a player must wait before getting back up when ragdolized from other sources.")
rm.RagdollRecoveryWeaponPreserveEnabled = CreateConVar("rm_ragdoll_recovery_weapon_preserve_enabled", "1", CVarSwitches, "Enable the preservation of weapons when recovering.")

rm.WeaponDropOnRagdollEnabled = CreateConVar("rm_weapon_drop_onragdoll_enabled", "0", CVarSwitches, "Enable equipped weapons dropping upon ragdolization.")
rm.WeaponDropOnDeathEnabled = CreateConVar("rm_weapon_drop_ondeath_enabled", "1", CVarSwitches, "Enable equipped weapons dropping upon death.")
rm.WeaponDropOnDrownEnabled = CreateConVar("rm_weapon_drop_ondrown_enabled", "1", CVarSwitches, "Enable equipped weapons dropping upon drowning.")
rm.WeaponDropOnSuicideEnabled = CreateConVar("rm_weapon_drop_onsuicide_enabled", "1", CVarSwitches, "Enable equipped weapons dropping upon suicide.")
rm.WeaponCrossbowWeldEnabled = CreateConVar("rm_weapon_crossbow_weld_enabled", "1", CVarSwitches, "Enable RagMod ragdolls being welded to objects when shot with the Crossbow.")

rm.RagdollResetEnabled = CreateConVar("rm_ragdoll_reset_enabled", "1", CVarSwitches, "Enable resetting while ragdolzied.")

rm.RagdollBloodEnabled = CreateConVar("rm_ragdoll_blood_enabled", "1", CVarSwitches, "Enable RagMod ragdoll blood.")

rm.RagdollDecapitationEnabled = CreateConVar("rm_ragdoll_decapitation_enabled", "0", CVarSwitches, "Enable RagMod ragdoll decapitation.")
rm.RagdollDecapitationValue = CreateConVar("rm_ragdoll_decapitation_value", "-1", CVarSwitches, "The damage required to decapitate.")
rm.RagdollGibEnabled = CreateConVar("rm_ragdoll_gib_enabled", "1", CVarSwitches, "Enable RagMod ragdoll gibbing.")
rm.RagdollGibValue = CreateConVar("rm_ragdoll_gib_value", "25", CVarSwitches, "The damage required to gib.")

rm.RagdollKeepEnabled = CreateConVar("rm_ragdoll_keep_enabled", "1", CVarSwitches, "Enable the preservation of dead RagMod ragdolls. If disabled, NPC ragdolls will disappear after a minute.")
rm.RagdollKeepPlayerValue = CreateConVar("rm_ragdoll_keep_player_value", "0", CVarSwitches, "The number of ragdolls to keep per-player (0 is infinite).")
rm.RagdollKeepNPCValue = CreateConVar("rm_ragdoll_keep_npc_value", "0", CVarSwitches, "The number of ragdolls to keep for NPCs (0 is infinite).")

rm.RagdollDamageEnabled = CreateConVar("rm_ragdoll_damage_enabled", "1", CVarSwitches, "Enable the damaging of RagMod ragdolls (This does not influence other damage-related effects).")
rm.RagdollDamagePVPEnabled = CreateConVar("rm_ragdoll_damage_pvp_enabled", "1", CVarSwitches, "Enable players to damage other players' RagMod ragdolls")
rm.RagdollDamageMultiplier = CreateConVar("rm_ragdoll_damage_multiplier", "1", CVarSwitches, "The multiplier at which a player will take damage while ragdolized.")
rm.RagdollDamageFixInfoEnabled = CreateConVar("rm_ragdoll_damage_fixinfo_enabled", "1", CVarSwitches, [[Enable the repair of damage information:
    When a player dies as a RagMod ragdoll, it is technically commiting suicide; the killer and inflictor will be replaced accordingly.
    If the attacker is also the inflictor or the inflictor is not valid, the inflictor is replaced with the attacker's weapon, even if it is not used. If the inflictor is still not valid, the world will be used instead (as if the player was killed with a world prop).
	(Note: This is a feature in some cases and a bug in others; should the need arise, this may be removed)]])

rm.RagdollBounceEnabled = CreateConVar("rm_ragdoll_bounce_enabled", "0", CVarSwitches, "Enable an enhanced RagMod ragdoll bounce effect.")
rm.RagdollBounceMultiplier = CreateConVar("rm_ragdoll_bounce_multiplier", "1", CVarSwitches, "The force multiplier that RagMod ragdolls bounce at.")

rm.RagdollForceType = CreateConVar("rm_ragdoll_force_type", "2", CVarSwitches, "The way force to RagMod ragdolls is handled.\n1: Standard force from damage information.\n2: RagMod normalized damage-based force.")
rm.RagdollForceMultiplier = CreateConVar("rm_ragdoll_force_multiplier", "1", CVarSwitches, "The force multiplier that damage pushes RagMod ragdolls.")
rm.RagdollForceMultiplierExplosion = CreateConVar("rm_ragdoll_force_multiplier_explosion", "1", CVarSwitches, "The force multiplier that explosions push RagMod ragdolls.")

rm.RagdollBurnEnabled = CreateConVar("rm_ragdoll_burn_enabled", "1", CVarSwitches, "Enable burning effects on RagMod ragdolls.")
rm.RagdollBurnOnExplosionEnabled = CreateConVar("rm_ragdoll_burn_onexplosion_enabled", "1", CVarSwitches, "Enable the ability to catch a RagMod ragdoll on fire when caught in explosions.")
rm.RagdollBurnOnExplosionValue = CreateConVar("rm_ragdoll_burn_onexplosion_value", "10", CVarSwitches, "RagMod ragdolls will catch on fire when caught in explosions every one in this number of times.")

rm.RagdollMoveEnabled = CreateConVar("rm_ragdoll_move_enabled", "1", CVarSwitches, "Enable various RagMod ragdoll movements activated with the forward key: crawling, swimming, gliding, etc.")
rm.RagdollMoveSupermanModeEnabled = CreateConVar("rm_ragdoll_move_supermanmode_enabled", "0", CVarSwitches, "This console variable has no use. I do not recommend modifying it in any way, shape, or form; doing so may void your warranty.")

rm.RagdollTwitchEnabled = CreateConVar("rm_ragdoll_twitch_enabled", "1", CVarSwitches, "Enable RagMod ragdoll randomized twitching.")
rm.RagdollTwitchOnCommandEnabled = CreateConVar("rm_ragdoll_twitch_oncommand_enabled", "1", CVarSwitches, "Enable RagMod ragdoll twitching activated by holding the back key.")
rm.RagdollTwitchOnDamageEnabled = CreateConVar("rm_ragdoll_twitch_ondamage_enabled", "1", CVarSwitches, "Enable RagMod ragdoll twitching when damaged.")
rm.RagdollTwitchOnDamageMultiplier = CreateConVar("rm_ragdoll_twitch_ondamage_multiplier", "1", CVarSwitches, "The multiplier at which RagMod ragdolls will twitch based on the damage taken.")
rm.RagdollTwitchOnSpeedEnabled = CreateConVar("rm_ragdoll_twitch_onspeed_enabled", "1", CVarSwitches, "Enable RagMod ragdoll twitching based on their velocity.")
rm.RagdollTwitchOnSpeedMultiplier = CreateConVar("rm_ragdoll_twitch_onspeed_multiplier", "1", CVarSwitches, "The multiplier at which RagMod ragdolls will twitch based on their velocity.")
rm.RagdollTwitchOnDeathEnabled = CreateConVar("rm_ragdoll_twitch_ondeath_enabled", "1", CVarSwitches, "Enable RagMod ragdoll twitching while dead.")

rm.RagdollGrabEnabled = CreateConVar("rm_ragdoll_grab_enabled", "1", CVarSwitches, "Enable the ability to grab onto props.")
rm.RagdollGrabOnCommandEnabled = CreateConVar("rm_ragdoll_grab_oncommand_enabled", "1", CVarSwitches, "Enable the ability to grab onto props on command.")
rm.RagdollGrabStrength = CreateConVar("rm_ragdoll_grab_strength", "9500", CVarSwitches, "The strength at which the grabbing RagMod ragdoll holds on.")

rm.RagdollParachuteEnabled = CreateConVar("rm_ragdoll_parachute_enabled", "1", CVarSwitches, "Enable RagMod ragdoll parachutes.")
rm.RagdollParachuteOnCommandEnabled = CreateConVar("rm_ragdoll_parachute_oncommand_enabled", "1", CVarSwitches, "Enable RagMod ragdoll parachutes.")
rm.RagdollParachuteOnCommandUnlimitedEnabled = CreateConVar("rm_ragdoll_parachute_oncommand_unlimited_enabled", "0", CVarSwitches, "Enable unlimited RagMod ragdoll parachutes.")
rm.RagdollParachuteMultiplier = CreateConVar("rm_ragdoll_parachute_multiplier", "1", CVarSwitches, "The parachute damping multiplier.")

rm.RagdollDeathEffectEnabled = CreateConVar("rm_ragdoll_death_effect_enabled", "1", CVarSwitches, "Enable a slowed fall when killing players and NPCs with low damage (note that the respective ragdolizing functionalities must be enabled).")
rm.RagdollDeathEffectMultiplier = CreateConVar("rm_ragdoll_death_effect_multiplier", "1", CVarSwitches, "The damping multiplier (note that there isn't much of a change with higher values because only one bone is affected).")
rm.RagdollDeathFacePoseEnabled = CreateConVar("rm_ragdoll_death_facepose_enabled", "1", CVarSwitches, "Pose the face flexes when dying.")

rm.RagdollToolGunEnabled = CreateConVar("rm_ragdoll_toolgun_enabled", "1", CVarSwitches, "Enable the ability to use the ToolGun on RagMod ragdolls (does not apply to non-player RagMod ragdolls).")
rm.RagdollPhysGunEnabled = CreateConVar("rm_ragdoll_physgun_enabled", "1", CVarSwitches, "Enable the ability to use the PhysGun on players and RagMod ragdolls (does not apply to non-player RagMod ragdolls).")

rm.RagdolizeOnCommandEnabled = CreateConVar("rm_ragdolize_oncommand_enabled", "1", CVarSwitches, "Enable the ability to ragdolize on command.")
rm.RagdolizeOnFallEnabled = CreateConVar("rm_ragdolize_onfall_enabled", "0", CVarSwitches, "Enable the ragdolizing of players when taking any fall damage.")
rm.RagdolizeOnDamageEnabled = CreateConVar("rm_ragdolize_ondamage_enabled", "0", CVarSwitches, "Enable the ragdolizing of players when taking an amount of damage.")
rm.RagdolizeOnDamageValue = CreateConVar("rm_ragdolize_ondamage_value", "35", CVarSwitches, "The amount of damage needed to ragdolize players.")
rm.RagdolizeOnDamageVehicleValue = CreateConVar("rm_ragdolize_ondamage_vehicle_value", "0", CVarSwitches, "The amount of damage needed to ragdolize players when inside vehicles.")
rm.RagdolizeOnSpeedEnabled = CreateConVar("rm_ragdolize_onspeed_enabled", "0", CVarSwitches, "Enable the ragdolizing of players when going faster than a certain value.")
rm.RagdolizeOnSpeedValue = CreateConVar("rm_ragdolize_onspeed_value", "0", CVarSwitches, "The amount of speed needed to ragdolize players.")
rm.RagdolizeOnEjectEnabled = CreateConVar("rm_ragdolize_oneject_enabled", "0", CVarSwitches, "Enable the ragdolizing of players when ejecting from a seat.")
rm.RagdolizeOnEjectValue = CreateConVar("rm_ragdolize_oneject_value", "100", CVarSwitches, "The amount of speed when ejecting players need to ragdolize.")
rm.RagdolizeOnDeathEnabled = CreateConVar("rm_ragdolize_ondeath_enabled", "1", CVarSwitches, "Enable the ragdolizing of players upon death.")

rm.NPCRagdolizeBlacklist = CreateConVar("rm_npc_ragdolize_blacklist", "C_AI_BaseNPC,crow,pigeon,seagull,cscanner,clawscanner,manhack,rollermine,turret,turret_floor,bigmomma,cockroach,gargantua,nihilanth,snark,tentacle,dog,antlionguard,barnacle,strider,fisherman", CVarSwitches, "Any NPC class names (\"npc_\" and \"monster_\" prefixes optional) in this list, separated by a comma, will not be ragdolized.")
rm.NPCRagdolizeOnDeathEnabled = CreateConVar("rm_npc_ragdolize_ondeath_enabled", "1", CVarSwitches, "Enable the ragdolizing of NPCs upon death. ai_serverragdolls will be set to 1 for compatibility reasons.")

rm.Genders =
{
	Alyx = {"player/alyx%.mdl"},
	Breen = {"player/breen%.mdl"},
	Barney = {"player/barney%.mdl"},
	GMan = {"player/gman_high%.mdl"},
	Kleiner = {"player/kleiner%.mdl"},
	Mossman = {"player/mossman%.mdl"},
	Odessa = {"player/odessa%.mdl"},

	CombineMetropolice =
	{
		"player/police%.mdl",
		"gasmask",
		"gas_mask"
	},
	CombineSoldier =
	{
		"combine",
		"soldier_stripped"
	},
	Female =
	{
		"female",
		"girl",
		"woman"
	},
	Zombie =
	{
		"charple",
		"corpse",
		"player/classic%.mdl",
		"zombie"
	}
}
rm.Sounds =
{
	FleshSquish =
	{
		Sound("ambient/levels/canals/toxic_slime_gurgle2.wav"),
		Sound("ambient/levels/canals/toxic_slime_gurgle4.wav"),
		Sound("ambient/levels/canals/toxic_slime_gurgle8.wav"),
		Sound("physics/flesh/flesh_bloody_impact_hard1.wav"),
		Sound("physics/flesh/flesh_squishy_impact_hard2.wav"),
		Sound("physics/flesh/flesh_squishy_impact_hard3.wav"),
		Sound("physics/flesh/flesh_squishy_impact_hard4.wav")
	},
	FleshBreak =
	{
		Sound("npc/barnacle/barnacle_crunch2.wav"),
		Sound("npc/barnacle/barnacle_crunch3.wav"),
		Sound("npc/barnacle/neck_snap1.wav"),
		Sound("npc/barnacle/neck_snap2.wav"),
		Sound("physics/flesh/flesh_bloody_break.wav"),
		Sound("physics/flesh/flesh_squishy_impact_hard1.wav")
	},
	PlayerDrown =
	{
		Sound("player/pl_drown1.wav"),
		Sound("player/pl_drown2.wav"),
		Sound("player/pl_drown3.wav")
	},
	PlayerBurn =
	{
		Sound("player/pl_burnpain1.wav"),
		Sound("player/pl_burnpain2.wav"),
		Sound("player/pl_burnpain3.wav")
	},
	AlyxFreeFall =
	{
		Sound("vo/NovaProspekt/al_uhoh_np.wav"),
		Sound("vo/npc/Alyx/lookout01.wav"),
		Sound("vo/npc/Alyx/lookout03.wav"),
		Sound("vo/npc/Alyx/ohno_startle01.wav"),
		Sound("vo/npc/Alyx/ohno_startle03.wav"),
		Sound("vo/npc/Alyx/watchout01.wav"),
		Sound("vo/npc/Alyx/watchout02.wav"),
		Sound("vo/Streetwar/Alyx_gate/al_ahno.wav")
	},
	AlyxPain =
	{
		Sound("vo/Citadel/al_dienow.wav"),
		Sound("vo/Citadel/al_struggle07.wav"),
		Sound("vo/Citadel/al_struggle08.wav"),
		Sound("vo/eli_lab/al_dogairlock01.wav"),
		Sound("vo/NovaProspekt/al_combinespy01.wav"),
		Sound("vo/NovaProspekt/al_gasp01.wav"),
		Sound("vo/npc/Alyx/gasp02.wav"),
		Sound("vo/npc/Alyx/gasp03.wav"),
		Sound("vo/npc/Alyx/hurt04.wav"),
		Sound("vo/npc/Alyx/hurt05.wav"),
		Sound("vo/npc/Alyx/hurt06.wav"),
		Sound("vo/npc/Alyx/hurt08.wav"),
		Sound("vo/npc/Alyx/uggh01.wav"),
		Sound("vo/npc/Alyx/uggh02.wav"),
		Sound("vo/Streetwar/Alyx_gate/al_ah.wav")
	},
	AlyxDeath =
	{
		Sound("vo/Citadel/al_dadgordonno_c.wav"),
		Sound("vo/Citadel/al_dadsorry.wav"),
		Sound("vo/Citadel/al_struggle01.wav"),
		Sound("vo/Citadel/al_struggle02.wav"),
		Sound("vo/Citadel/al_struggle03.wav"),
		Sound("vo/Citadel/al_struggle05.wav"),
		Sound("vo/NovaProspekt/al_gordon01.wav"),
		Sound("vo/NovaProspekt/al_horrible01.wav"),
		Sound("vo/NovaProspekt/al_ohmygod.wav"),
		Sound("vo/npc/Alyx/gordon_dist01.wav"),
		Sound("vo/npc/Alyx/no01.wav"),
		Sound("vo/npc/Alyx/no02.wav"),
		Sound("vo/npc/Alyx/no03.wav"),
		Sound("vo/npc/Alyx/ohgod01.wav"),
		Sound("vo/Streetwar/Alyx_gate/al_no.wav")
	},
	BreenFreeFall =
	{
		Sound("vo/Citadel/br_failing11.wav"),
		Sound("vo/Citadel/br_no.wav"),
		Sound("vo/Citadel/br_ohshit.wav"),
		Sound("vo/npc/male01/pain01.wav"),
		Sound("vo/npc/male01/startle01.wav"),
		Sound("vo/npc/male01/startle02.wav")
	},
	BreenPain =
	{
		Sound("vo/Citadel/br_failing11.wav"),
		Sound("vo/Citadel/br_no.wav"),
		Sound("vo/Citadel/br_ohshit.wav"),
		Sound("vo/npc/male01/pain01.wav"),
		Sound("vo/npc/male01/startle01.wav"),
		Sound("vo/npc/male01/startle02.wav")
	},
	BreenDeath =
	{
		Sound("vo/Citadel/br_failing11.wav"),
		Sound("vo/Citadel/br_laugh01.wav"),
		Sound("vo/Citadel/br_no.wav"),
		Sound("vo/Citadel/br_ohshit.wav"),
		Sound("vo/Citadel/br_youfool.wav"),
		Sound("vo/Citadel/br_youneedme.wav"),
		Sound("vo/npc/male01/pain01.wav"),
		Sound("vo/npc/male01/startle01.wav"),
		Sound("vo/npc/male01/startle02.wav")
	},
	BarneyFreeFall =
	{
		Sound("vo/k_lab/ba_cantlook.wav"),
		Sound("vo/k_lab/ba_whatthehell.wav"),
		Sound("vo/k_lab2/ba_incoming.wav"),
		Sound("vo/npc/Barney/ba_damnit.wav"),
		Sound("vo/npc/Barney/ba_duck.wav"),
		Sound("vo/npc/Barney/ba_getdown.wav"),
		Sound("vo/npc/Barney/ba_getoutofway.wav"),
		Sound("vo/npc/Barney/ba_hereitcomes.wav"),
		Sound("vo/npc/Barney/ba_lookout.wav")
	},
	BarneyPain =
	{
		Sound("vo/k_lab/ba_getitoff01.wav"),
		Sound("vo/k_lab/ba_thingaway02.wav"),
		Sound("vo/npc/Barney/ba_pain01.wav"),
		Sound("vo/npc/Barney/ba_pain02.wav"),
		Sound("vo/npc/Barney/ba_pain03.wav"),
		Sound("vo/npc/Barney/ba_pain04.wav"),
		Sound("vo/npc/Barney/ba_pain05.wav"),
		Sound("vo/npc/Barney/ba_pain06.wav"),
		Sound("vo/npc/Barney/ba_pain07.wav"),
		Sound("vo/npc/Barney/ba_pain08.wav"),
		Sound("vo/npc/Barney/ba_pain09.wav"),
		Sound("vo/npc/Barney/ba_pain10.wav")
	},
	BarneyDeath =
	{
		Sound("vo/k_lab/ba_guh.wav"),
		Sound("vo/k_lab/ba_thingaway02.wav"),
		Sound("vo/npc/Barney/ba_no01.wav"),
		Sound("vo/npc/Barney/ba_no02.wav"),
		Sound("vo/npc/Barney/ba_ohshit03.wav"),
		Sound("vo/Streetwar/rubble/ba_damnitall.wav")
	},
	GManFreeFall =
	{
		Sound("vo/npc/male01/startle01.wav")
	},
	GManDeath =
	{
		Sound("vo/Citadel/gman_exit01.wav"),
		Sound("vo/Citadel/gman_exit02.wav"),
		Sound("vo/Citadel/gman_exit10.wav")
	},
	KleinerFreeFall =
	{
		Sound("vo/k_lab/kl_ahhhh.wav"),
		Sound("vo/k_lab/kl_dearme.wav"),
		Sound("vo/k_lab/kl_fiddlesticks.wav"),
		Sound("vo/k_lab/kl_getoutrun02.wav"),
		Sound("vo/k_lab/kl_getoutrun03.wav"),
		Sound("vo/k_lab/kl_hedyno03.wav"),
		Sound("vo/k_lab/kl_ohdear.wav"),
		Sound("vo/k_lab2/kl_notallhopeless_b.wav"),
		Sound("vo/trainyard/kl_morewarn01.wav")
	},
	KleinerPain =
	{
		Sound("vo/k_lab/kl_ahhhh.wav"),
		Sound("vo/k_lab/kl_hedyno03.wav"),
		Sound("vo/npc/male01/pain01.wav"),
		Sound("vo/npc/male01/startle01.wav"),
		Sound("vo/npc/male01/startle02.wav")
	},
	KleinerDeath =
	{
		Sound("vo/k_lab/kl_ahhhh.wav"),
		Sound("vo/k_lab/kl_dearme.wav"),
		Sound("vo/k_lab/kl_hedyno03.wav"),
		Sound("vo/k_lab/kl_ohdear.wav"),
		Sound("vo/k_lab2/kl_greatscott.wav"),
		Sound("vo/trainyard/kl_morewarn01.wav")
	},
	MossmanFreeFall =
	{
		Sound("vo/eli_lab/mo_hereseli01.wav"),
		Sound("vo/npc/female01/pain02.wav"),
		Sound("vo/npc/female01/startle01.wav"),
		Sound("vo/npc/female01/startle02.wav")
	},
	MossmanPain =
	{
		Sound("vo/eli_lab/mo_hereseli01.wav"),
		Sound("vo/npc/female01/pain02.wav"),
		Sound("vo/npc/female01/startle01.wav"),
		Sound("vo/npc/female01/startle02.wav")
	},
	MossmanDeath =
	{
		Sound("vo/Citadel/mo_sorrygordon.wav"),
		Sound("vo/eli_lab/mo_hereseli01.wav"),
		Sound("vo/npc/female01/moan01.wav"),
		Sound("vo/npc/female01/moan02.wav"),
		Sound("vo/npc/female01/moan03.wav"),
		Sound("vo/npc/female01/moan04.wav"),
		Sound("vo/npc/female01/moan05.wav"),
		Sound("vo/npc/female01/pain02.wav"),
		Sound("vo/npc/female01/startle01.wav"),
		Sound("vo/npc/female01/startle02.wav")
	},
	OdessaFreeFall =
	{
		Sound("vo/npc/male01/pain01.wav")
	},
	OdessaPain =
	{
		Sound("vo/npc/male01/pain02.wav"),
		Sound("vo/npc/male01/pain03.wav"),
		Sound("vo/npc/male01/pain04.wav"),
		Sound("vo/npc/male01/pain05.wav"),
		Sound("vo/npc/male01/pain06.wav")
	},
	OdessaDeath =
	{
		Sound("vo/coast/odessa/nlo_cub_thatsthat.wav"),
		Sound("vo/npc/male01/moan01.wav"),
		Sound("vo/npc/male01/moan02.wav"),
		Sound("vo/npc/male01/moan03.wav"),
		Sound("vo/npc/male01/moan04.wav"),
		Sound("vo/npc/male01/moan05.wav")
	},

	CombineMetropoliceFreeFall =
	{
		Sound("npc/metropolice/vo/help.wav"),
		Sound("npc/metropolice/vo/lookout.wav"),
		Sound("npc/metropolice/vo/moveit.wav"),
		Sound("npc/metropolice/vo/shit.wav"),
		Sound("npc/metropolice/vo/takecover.wav"),
		Sound("npc/metropolice/vo/watchit.wav")
	},
	CombineMetropolicePain =
	{
		Sound("npc/metropolice/pain1.wav"),
		Sound("npc/metropolice/pain2.wav"),
		Sound("npc/metropolice/pain3.wav"),
		Sound("npc/metropolice/pain4.wav"),
		Sound("npc/metropolice/vo/chuckle.wav"),
		Sound("npc/metropolice/vo/shit.wav")
	},
	CombineMetropoliceDeath =
	{
		Sound("npc/metropolice/die1.wav"),
		Sound("npc/metropolice/die2.wav"),
		Sound("npc/metropolice/die3.wav")
	},
	CombineSoldierFreeFall =
	{
		Sound("npc/combine_soldier/vo/inbound.wav"),
		Sound("npc/combine_soldier/vo/coverhurt.wav")
	},
	CombineSoldierPain =
	{
		Sound("npc/combine_soldier/pain1.wav"),
		Sound("npc/combine_soldier/pain2.wav"),
		Sound("npc/combine_soldier/pain3.wav"),
	},
	CombineSoldierDeath =
	{
		Sound("npc/combine_soldier/die1.wav"),
		Sound("npc/combine_soldier/die2.wav"),
		Sound("npc/combine_soldier/die3.wav")
	},
	FemaleFreeFall =
	{
		Sound("vo/canals/female01/stn6_incoming.wav"),
		Sound("vo/npc/female01/headsup02.wav"),
		Sound("vo/npc/female01/help01.wav"),
		Sound("vo/npc/female01/incoming02.wav"),
		Sound("vo/npc/female01/runforyourlife01.wav"),
		Sound("vo/npc/female01/runforyourlife02.wav"),
		Sound("vo/npc/female01/uhoh.wav"),
		Sound("vo/npc/female01/watchout.wav")
	},
	FemalePain =
	{
		Sound("vo/npc/female01/imhurt01.wav"),
		Sound("vo/npc/female01/imhurt02.wav"),
		Sound("vo/npc/female01/ow01.wav"),
		Sound("vo/npc/female01/ow02.wav"),
		Sound("vo/npc/female01/pain01.wav"),
		Sound("vo/npc/female01/pain02.wav"),
		Sound("vo/npc/female01/pain03.wav"),
		Sound("vo/npc/female01/pain04.wav"),
		Sound("vo/npc/female01/pain05.wav"),
		Sound("vo/npc/female01/pain06.wav"),
		Sound("vo/npc/female01/pain07.wav"),
		Sound("vo/npc/female01/pain08.wav"),
		Sound("vo/npc/female01/pain09.wav"),
		Sound("vo/npc/female01/startle01.wav"),
		Sound("vo/npc/female01/startle02.wav")
	},
	FemaleDeath =
	{
		Sound("vo/canals/arrest_helpme.wav"),
		Sound("vo/coast/odessa/female01/nlo_cubdeath01.wav"),
		Sound("vo/coast/odessa/female01/nlo_cubdeath02.wav"),
		Sound("vo/npc/female01/gordead_ans04.wav"),
		Sound("vo/npc/female01/gordead_ans05.wav"),
		Sound("vo/npc/female01/gordead_ans06.wav"),
		Sound("vo/npc/female01/gordead_ans19.wav"),
		Sound("vo/npc/female01/gordead_ques02.wav"),
		Sound("vo/npc/female01/gordead_ques06.wav"),
		Sound("vo/npc/female01/gordead_ques10.wav"),
		Sound("vo/npc/female01/gordead_ques14.wav"),
		Sound("vo/npc/female01/moan01.wav"),
		Sound("vo/npc/female01/moan02.wav"),
		Sound("vo/npc/female01/moan03.wav"),
		Sound("vo/npc/female01/moan04.wav"),
		Sound("vo/npc/female01/moan05.wav"),
		Sound("vo/npc/female01/no01.wav"),
		Sound("vo/npc/female01/no02.wav")
	},
	MaleFreeFall =
	{
		Sound("vo/canals/male01/stn6_incoming.wav"),
		Sound("vo/npc/male01/headsup02.wav"),
		Sound("vo/npc/male01/help01.wav"),
		Sound("vo/npc/male01/incoming02.wav"),
		Sound("vo/npc/male01/pain01.wav"),
		Sound("vo/npc/male01/runforyourlife01.wav"),
		Sound("vo/npc/male01/runforyourlife02.wav"),
		Sound("vo/npc/male01/runforyourlife03.wav"),
		Sound("vo/npc/male01/strider_run.wav"),
		Sound("vo/npc/male01/uhoh.wav"),
		Sound("vo/npc/male01/watchout.wav"),
		Sound("vo/Streetwar/sniper/male01/c17_09_help01.wav"),
		Sound("vo/Streetwar/sniper/male01/c17_09_help02.wav")
	},
	MalePain =
	{
		Sound("vo/npc/male01/imhurt01.wav"),
		Sound("vo/npc/male01/imhurt02.wav"),
		Sound("vo/npc/male01/ow01.wav"),
		Sound("vo/npc/male01/ow02.wav"),
		Sound("vo/npc/male01/pain02.wav"),
		Sound("vo/npc/male01/pain03.wav"),
		Sound("vo/npc/male01/pain04.wav"),
		Sound("vo/npc/male01/pain05.wav"),
		Sound("vo/npc/male01/pain06.wav"),
		Sound("vo/npc/male01/pain07.wav"),
		Sound("vo/npc/male01/pain08.wav"),
		Sound("vo/npc/male01/pain09.wav"),
		Sound("vo/npc/male01/startle01.wav"),
		Sound("vo/npc/male01/startle02.wav")
	},
	MaleDeath =
	{
		Sound("vo/coast/odessa/male01/nlo_cubdeath01.wav"),
		Sound("vo/coast/odessa/male01/nlo_cubdeath02.wav"),
		Sound("vo/npc/male01/gordead_ans04.wav"),
		Sound("vo/npc/male01/gordead_ans05.wav"),
		Sound("vo/npc/male01/gordead_ans06.wav"),
		Sound("vo/npc/male01/gordead_ans19.wav"),
		Sound("vo/npc/male01/gordead_ques02.wav"),
		Sound("vo/npc/male01/gordead_ques06.wav"),
		Sound("vo/npc/male01/gordead_ques10.wav"),
		Sound("vo/npc/male01/gordead_ques14.wav"),
		Sound("vo/npc/male01/moan01.wav"),
		Sound("vo/npc/male01/moan02.wav"),
		Sound("vo/npc/male01/moan03.wav"),
		Sound("vo/npc/male01/moan04.wav"),
		Sound("vo/npc/male01/moan05.wav"),
		Sound("vo/npc/male01/no01.wav"),
		Sound("vo/npc/male01/no02.wav"),
		Sound("vo/trainyard/male01/cit_window_use01.wav")
	},
	ZombieFreeFall =
	{
		Sound("npc/zombie/zombie_voice_idle1.wav"),
		Sound("npc/zombie/zombie_voice_idle2.wav"),
		Sound("npc/zombie/zombie_voice_idle3.wav"),
		Sound("npc/zombie/zombie_voice_idle4.wav"),
		Sound("npc/zombie/zombie_voice_idle5.wav"),
		Sound("npc/zombie/zombie_voice_idle6.wav"),
		Sound("npc/zombie/zombie_voice_idle7.wav"),
		Sound("npc/zombie/zombie_voice_idle8.wav"),
		Sound("npc/zombie/zombie_voice_idle9.wav"),
		Sound("npc/zombie/zombie_voice_idle10.wav"),
		Sound("npc/zombie/zombie_voice_idle11.wav"),
		Sound("npc/zombie/zombie_voice_idle12.wav"),
		Sound("npc/zombie/zombie_voice_idle13.wav"),
		Sound("npc/zombie/zombie_voice_idle14.wav")
	},
	ZombiePain =
	{
		Sound("npc/zombie/zombie_pain1.wav"),
		Sound("npc/zombie/zombie_pain2.wav"),
		Sound("npc/zombie/zombie_pain3.wav"),
		Sound("npc/zombie/zombie_pain4.wav"),
		Sound("npc/zombie/zombie_pain5.wav"),
		Sound("npc/zombie/zombie_pain6.wav")
	},
	ZombieDeath =
	{
		Sound("npc/zombie/zombie_die1.wav"),
		Sound("npc/zombie/zombie_die2.wav"),
		Sound("npc/zombie/zombie_die3.wav"),
		Sound("npc/zombie/zombie_alert1.wav"),
		Sound("npc/zombie/zombie_alert2.wav"),
		Sound("npc/zombie/zombie_alert3.wav")
	}
}

rm.GibModels =
{
	"models/gibs/antlion_gib_medium_1.mdl",
	"models/gibs/antlion_gib_small_1.mdl",
	"models/gibs/antlion_gib_small_2.mdl",
	"models/gibs/antlion_gib_small_3.mdl",
	"models/props_combine/breenbust_Chunk02.mdl",
	"models/props_combine/breenbust_Chunk03.mdl",
	"models/props_combine/breenbust_Chunk04.mdl",
	"models/props_combine/breenbust_Chunk05.mdl",
	"models/props_combine/breenbust_Chunk06.mdl",
	"models/props_combine/breenbust_Chunk07.mdl",
	"models/props_junk/watermelon01_chunk02a.mdl",
	"models/props_junk/watermelon01_chunk02b.mdl",
	"models/props_junk/watermelon01_chunk02c.mdl",
	"models/props_phx/misc/potato.mdl",
	"models/props_wasteland/prison_toiletchunk01f.mdl",
	"models/props_wasteland/prison_toiletchunk01i.mdl",
	"models/props_wasteland/prison_toiletchunk01j.mdl"
}
for _, Gib in pairs(rm.GibModels) do
	util.PrecacheModel(Gib)
end

for HookType, Hook in pairs(hook.GetTable()) do
	for HookName, HookAction in pairs(Hook) do
		if string.sub(tostring(HookName), 1, 3) == "rm_" then
			hook.Remove(HookType, HookName)
			Msg("[RagMod] Removed " ..(CLIENT and "client" or (SERVER and "server" or "?")).. " hook " ..tostring(HookName).. ".\n")
		end
	end
end

function rm.GetPlayerModelGender(ModelName)
	for GenderName, GenderIndex in pairs(rm.Genders) do
		for _, Match in pairs(GenderIndex) do
			if string.find(string.lower(ModelName), string.lower(Match)) then
				return GenderName
			end
		end
	end
	return "Male"
end

function rm.ModelIterateBones(Ent, Action)
	for i = 0, Ent:GetBoneCount() - 1 do
		if Action(i, Ent) == false then
			return false
		end
	end
	return true
end

function rm.ModelClosestBone(Ent, Pos, Restrict)
	local TargetIndex, TargetChildIndex, TargetParentIndex = nil, nil, nil
	rm.ModelIterateBones(Ent, function(i)
		if not TargetIndex or (TargetIndex and Ent:GetBonePosition(i):Distance(Pos) < Ent:GetBonePosition(TargetIndex):Distance(Pos)) then
			TargetIndex = i
		end
	end)
	if Target then
		rm.ModelIterateBones(Ent, function(i)
			if Ent:GetBoneParent(i) == TargetIndex then
				TargetChildIndex = i
			end
		end)
		TargetParentIndex = Ragdoll:GetBoneParent(TargetIndex)
	end
	return TargetIndex, TargetChildIndex, TargetParentIndex
end

hook.Add("PopulateToolMenu", "rm_PopulateToolMenu", function()
	spawnmenu.AddToolMenuOption("Options", "RagMod 2 " ..rm.Version, "RagModSettings", "Settings", "", "", function(CPanel)
		CPanel:AddControl("Label", {Text = "RagMod 2 " ..rm.Version.. " client commands and settings"})
		CPanel:AddControl("Label", {Text = "\n\nCommands\n"})
		CPanel:AddControl("Button", {Label = "Ragdolize (rm_ragdolize)", Command = "rm_ragdolize"})
		CPanel:AddControl("Button", {Label = "Grab (rm_grab)", Command = "rm_grab"})
		CPanel:AddControl("Button", {Label = "Parachute (rm_parachute)", Command = "rm_parachute"})
		CPanel:AddControl("Button", {Label = "Reset (rm_reset)", Command = "rm_reset"})
		CPanel:AddControl("Label", {Text = ""})
		CPanel:AddControl("Button", {Label = "Lower weapon (rm_lowerweapon)", Command = "rm_lowerweapon"})
		CPanel:AddControl("Button", {Label = "Holster weapon (rm_holsterweapon)", Command = "rm_holsterweapon"})
		CPanel:AddControl("Button", {Label = "Drop ammo (rm_dropammo 1)", Command = "rm_dropammo 1"})
		CPanel:AddControl("Button", {Label = "Drop secondary ammo (rm_dropammo 2)", Command = "rm_dropammo 2"})
		CPanel:AddControl("Button", {Label = "Drop weapon (rm_dropweapon)", Command = "rm_dropweapon"})
		CPanel:AddControl("Label", {Text = ""})
		CPanel:AddControl("Button", {Label = "Help (rm_help, opens in console)", Command = "showconsole;rm_help"})
		CPanel:AddControl("Label", {Text = "\n\nCamera\n"})
		CPanel:AddControl("ComboBox",
			{
				Label = "          Mode:",
				Options =
				{
					["Third-person"] = {rm_ragdoll_camera_mode = 0},
					["First-person"] = {rm_ragdoll_camera_mode = 1},
					["First-person (camera oriented to ragdoll)"] = {rm_ragdoll_camera_mode = 2}
				},
				CVars =
				{
					"rm_ragdoll_camera_mode"
				},
				MenuButton = "0",
				Folder = ""
			}
		)
		CPanel:AddControl("Label", {Text = "\n\nPost-processing\n"})
		CPanel:AddControl("CheckBox", {Label = "Enabled", Command = "rm_pp_enabled"})
		CPanel:AddControl("CheckBox", {Label = "Restrict to death", Command = "rm_pp_restrict"})
		CPanel:AddControl("ComboBox",
			{
				Label = "          Presets:",
				Options =
				{
					["Default"] =
					{
						rm_pp_addr = "0",
						rm_pp_addg = "0",
						rm_pp_addb = "0",
						rm_pp_brightness = "0.9",
						rm_pp_contrast = "1.3",
						rm_pp_color = "0.4",
						rm_pp_mulr = "1",
						rm_pp_mulg = "1",
						rm_pp_mulb = "1",
						rm_pp_bluralpha = "0.7"
					},
					["Minimal"] =
					{
						rm_pp_addr = "0",
						rm_pp_addg = "0",
						rm_pp_addb = "0",
						rm_pp_brightness = "1",
						rm_pp_contrast = "1.3",
						rm_pp_color = "0.8",
						rm_pp_mulr = "1",
						rm_pp_mulg = "1",
						rm_pp_mulb = "1",
						rm_pp_bluralpha = "0.8"
					},
					["Bright"] =
					{
						rm_pp_addr = "0",
						rm_pp_addg = "0",
						rm_pp_addb = "0",
						rm_pp_brightness = "1.5",
						rm_pp_contrast = "1.2",
						rm_pp_color = "0.9",
						rm_pp_mulr = "1",
						rm_pp_mulg = "1",
						rm_pp_mulb = "1",
						rm_pp_bluralpha = "0.8"
					},
					["Black and White"] =
					{
						rm_pp_addr = "0",
						rm_pp_addg = "0",
						rm_pp_addb = "0",
						rm_pp_brightness = "1.2",
						rm_pp_contrast = "1",
						rm_pp_color = "0",
						rm_pp_mulr = "1",
						rm_pp_mulg = "1",
						rm_pp_mulb = "1",
						rm_pp_bluralpha = "0.4"
					},
					["High-Contrast Black and White"] =
					{
						rm_pp_addr = "0",
						rm_pp_addg = "0",
						rm_pp_addb = "0",
						rm_pp_brightness = "0.5",
						rm_pp_contrast = "8",
						rm_pp_color = "0",
						rm_pp_mulr = "1",
						rm_pp_mulg = "1",
						rm_pp_mulb = "1",
						rm_pp_bluralpha = "0.25"
					},
					["Blurry"] =
					{
						rm_pp_addr = "0",
						rm_pp_addg = "0",
						rm_pp_addb = "0",
						rm_pp_brightness = "1.25",
						rm_pp_contrast = "0.8",
						rm_pp_color = "0.9",
						rm_pp_mulr = "1.1",
						rm_pp_mulg = "1.1",
						rm_pp_mulb = "1",
						rm_pp_bluralpha = "0.2"
					},
					["Gritty"] =
					{
						rm_pp_addr = "0",
						rm_pp_addg = "0",
						rm_pp_addb = "0",
						rm_pp_brightness = "0.7",
						rm_pp_contrast = "3",
						rm_pp_color = "0.3",
						rm_pp_mulr = "1",
						rm_pp_mulg = "1",
						rm_pp_mulb = "1",
						rm_pp_bluralpha = "0.65"
					},
					["Half-Life Red"] =
					{
						rm_pp_addr = "0.4",
						rm_pp_addg = "0",
						rm_pp_addb = "0",
						rm_pp_brightness = "1",
						rm_pp_contrast = "1.2",
						rm_pp_color = "0.95",
						rm_pp_mulr = "1.1",
						rm_pp_mulg = "0.9",
						rm_pp_mulb = "0.9",
						rm_pp_bluralpha = "0.9"
					}
				},
				CVars =
				{
					"rm_pp_addr",
					"rm_pp_addg",
					"rm_pp_addb",
					"rm_pp_brightness",
					"rm_pp_contrast",
					"rm_pp_color",
					"rm_pp_mulr",
					"rm_pp_mulg",
					"rm_pp_mulb",
					"rm_pp_bluralpha"
				},
				MenuButton = "0",
				Folder = ""
			}
		)
		CPanel:AddControl("CheckBox", {Label = "Motion blur", Command = "rm_pp_motionblur_enabled"})
		CPanel:AddControl("CheckBox", {Label = " - Restrict to ragdoll", Command = "rm_pp_motionblur_restrict"})
		CPanel:AddControl("Label", {Text = "\n\nHUD\n"})
		CPanel:AddControl("CheckBox", {Label = "Recovery", Command = "rm_ragdoll_recovery_hud_enabled"})
		CPanel:AddControl("CheckBox", {Label = "Oxygen", Command = "rm_oxygen_hud_enabled"})
		CPanel:AddControl("CheckBox", {Label = " - Text", Command = "rm_oxygen_hud_text_enabled"})
		CPanel:AddControl("CheckBox", {Label = " - Bar", Command = "rm_oxygen_hud_bar_enabled"})
		CPanel:AddControl("CheckBox", {Label = "Afterdeath", Command = "rm_afterdeath_hud_enabled"})
		CPanel:AddControl("CheckBox", {Label = " - Killer", Command = "rm_afterdeath_hud_killer_enabled"})
		CPanel:AddControl("CheckBox", {Label = " - Kills", Command = "rm_afterdeath_hud_kills_enabled"})
		CPanel:AddControl("CheckBox", {Label = " - Respawn time", Command = "rm_afterdeath_hud_respawntime_enabled"})
		CPanel:AddControl("Label", {Text = "\n\nSounds\n"})
		CPanel:AddControl("Label", {Text = "\n\nAfterdeath\n"})
		CPanel:AddControl("CheckBox", {Label = "Enabled", Command = "rm_afterdeath_client_enabled"})
		CPanel:AddControl("ComboBox",
			{
				Label = "          Camera mode:",
				Options =
				{
					["None"] = {rm_afterdeath_camera_mode = 0},
					["Killer's view"] = {rm_afterdeath_camera_mode = 1},
					["Killer from corpse"] = {rm_afterdeath_camera_mode = 2},
					["Corpse from killer"] = {rm_afterdeath_camera_mode = 3}
				},
				CVars =
				{
					"rm_afterdeath_camera_mode"
				},
				MenuButton = "0",
				Folder = ""
			}
		)
		CPanel:AddControl("Label", {Text = "(Note: Afterdeath also needs to be enabled on the server)"})
		CPanel:AddControl("Label", {Text = "\n\nEffects\n"})
		CPanel:AddControl("CheckBox", {Label = "Blood spurts", Command = "rm_ragdoll_blood_spurt_enabled"})
		CPanel:AddControl("ComboBox",
			{
				Label = "          - Style:",
				Options =
				{
					["Point"] = {rm_ragdoll_blood_spurt_style = 0},
					["Line"] = {rm_ragdoll_blood_spurt_style = 1},
					["Textured line"] = {rm_ragdoll_blood_spurt_style = 2}
				},
				CVars =
				{
					"rm_ragdoll_blood_spurt_style"
				},
				MenuButton = "0",
				Folder = ""
			}
		)
		CPanel:AddControl("CheckBox", {Label = "Gib chunks", Command = "rm_ragdoll_gib_effect_enabled"})
		CPanel:AddControl("Slider", {Label = "          - Multiplier:", Command = "rm_ragdoll_gib_effect_multiplier", Type = "float", Min = 1, Max = 3})
		CPanel:AddControl("Label", {Text = "\n\n\n\nIf you're having trouble, try reading the help!"})
	end)
end)