AddCSLuaFile("autorun/client/cl_ragmod.lua")
AddCSLuaFile("autorun/sh_ragmod.lua")

resource.AddFile("materials/hud/killicons/entityflame.vmt")
resource.AddFile("materials/hud/killicons/player.vmt")
resource.AddFile("materials/hud/killicons/prop_ragdoll.vmt")
resource.AddFile("materials/hud/killicons/weapon_physcannon.vmt")

include("autorun/sh_ragmod.lua")

rm.Ragdolls = rm.Ragdolls or {}

function rm.PlayerRagdolize(Ply, Override)
	local Team = Ply:Team()
	if (Ply.rm_Alive or Override) and Team ~= TEAM_CONNECTING and ((Team ~= TEAM_UNASSIGNED and Team ~= TEAM_SPECTATOR) or not GAMEMODE.TeamBased) and not Ply.rm_Ragdoll and Ply.rm_CanRagdolize then
		local Velocity = Ply:GetVelocity()
		if not Ply.rm_ExitingVehicle and Ply:InVehicle() then
			Velocity = Velocity + Ply:GetVehicle():GetVelocity()
			Ply.rm_ExitingVehicle = true
			Ply:ExitVehicle()
			Ply.rm_ExitingVehicle = false
		end
		if Ply.rm_Alive then
			local Keep = true
			if rm.WeaponDropOnRagdollEnabled:GetBool() then
				Keep = rm.PlayerDropActiveWeapon(Ply, true)
			end
			if rm.RagdollRecoveryWeaponPreserveEnabled:GetBool() then
				Ply.rm_WeaponClass = {}
				Ply.rm_WeaponClip1 = {}
				Ply.rm_WeaponClip2 = {}
				Ply.rm_WeaponAmmo = {}
				Ply.rm_WeaponAmmoType = {}
				local ActiveWeapon = Ply:GetActiveWeapon()
				for _, Item in pairs(Ply:GetWeapons()) do
					if Keep == true or Item ~= ActiveWeapon then
						table.insert(Ply.rm_WeaponClass, Item:GetClass())
						table.insert(Ply.rm_WeaponClip1, Item:Clip1())
						table.insert(Ply.rm_WeaponClip2, Item:Clip2())
						table.insert(Ply.rm_WeaponAmmo, Ply:GetAmmoCount(Item:GetPrimaryAmmoType()))
						table.insert(Ply.rm_WeaponAmmoType, Item:GetPrimaryAmmoType())
						table.insert(Ply.rm_WeaponAmmo, Ply:GetAmmoCount(Item:GetSecondaryAmmoType()))
						table.insert(Ply.rm_WeaponAmmoType, Item:GetSecondaryAmmoType())
					end
				end
				Ply.rm_WeaponSelected = IsValid(ActiveWeapon) and ActiveWeapon:GetClass() or Ply.rm_WeaponSelected or ""
				Ply.rm_WeaponPreserve = true
			end
			Ply:StripWeapons()
		end
		local Ragdoll = ents.Create("prop_ragdoll")
		Ragdoll:SetModel(Ply:GetModel())
		Ragdoll:SetPos(Ply:GetPos())
		Ragdoll:SetAngles(Ply:GetAngles())
		Ragdoll:SetSkin(Ply:GetSkin())
		Ragdoll:SetMaterial(Ply:GetMaterial())
		for i = 0, Ragdoll:GetNumBodyGroups() - 1 do
			Ragdoll:SetBodygroup(i, Ply:GetBodygroup(i) or 0)
		end
		Ragdoll:SetColor(Ply:GetColor())
		Ragdoll:SetPhysicsAttacker(Ply)
		Ragdoll.rm_Owner = Ply
		Ragdoll.rm_IsRagdoll = true
		Ragdoll:SetNetworkedEntity("rm_Owner", Ply)
		Ragdoll:SetNetworkedBool("rm_IsRagdoll", true)
		Ragdoll.rm_IsUnderwater = Ply.rm_IsUnderwater or false
		Ragdoll:Spawn()
		table.insert(rm.Ragdolls, Ragdoll)
		if Ply:IsOnFire() then
			Ragdoll:Ignite(math.Rand(0, 120))
			Ply:Extinguish()
		end
		rm.RagdollIterateBones(Ragdoll, function(Bone, i)
			local Pos, angles = Ply:GetBonePosition(Ragdoll:TranslatePhysBoneToBone(i))
			Bone:SetPos(Pos)
			Bone:SetAngles(angles)
			Bone:SetVelocity(Velocity)
		end)
		rm.RagdollTwitch(Ragdoll, 100)
		Ply:Spectate(OBS_MODE_CHASE)
		Ply:SpectateEntity(Ragdoll)
		Ply:SetVelocity(vector_origin)
		Ply:SetMoveType(MOVETYPE_OBSERVER)
		Ply.rm_Ragdoll = Ragdoll
		Ply:SetNetworkedEntity("rm_Ragdoll", Ragdoll)
		return Ragdoll
	end
end
function rm.PlayerRecover(Ply, Reset)
	if rm.RagdollRecoveryEnabled:GetBool() and Ply.rm_Alive and Ply.rm_Ragdoll and Ply.rm_CanRecover and (Ply.rm_RecoveryTimer <= 0 or not rm.RagdollRecoveryDelayEnabled:GetBool()) then
		local Ragdoll = Ply.rm_Ragdoll
		if rm.RagdollRecoverySmoothingEnabled:GetBool() and not Reset and not Ply.rm_Grab and not Ply.rm_UsingClimbRope and IsValid(Ragdoll) and Ply:WaterLevel() < 2 then
			Ply.rm_CanRecover = false
			local Head = Ragdoll:GetPhysicsObjectNum(10)
			local Multiplier = 0
			local function Move()
				local Tick = FrameTime()
				timer.Simple(Tick, function()
					if IsValid(Ply) and Ply.rm_Alive and IsValid(Ragdoll) then
						local HeightTrace = -(Ragdoll:OBBMaxs().z - Ragdoll:OBBMins().z + 5)
						if rm.RagdollIterateBones(Ragdoll, function(Bone)
							return util.TraceLine(
								{
									start = Bone:GetPos(),
									endpos = Bone:GetPos() + Vector(0, 0, HeightTrace),
									filter = Ragdoll
								}
							).Hit
						end) and Multiplier < 5 and (Multiplier > 0.5 or (Ply:KeyDown(IN_ATTACK) or Ply:KeyDown(IN_ATTACK2) or Ply:KeyDown(IN_JUMP))) then
							local Mass = 0
							rm.RagdollIterateBones(Ragdoll, function(Bone)
								Mass = Mass + Bone:GetMass()
							end)
							local Trace = util.TraceLine(
								{
									start = Head:GetPos(),
									endpos = Head:GetPos() + Vector(0, 0, HeightTrace + 5),
									filter = Ragdoll
								}
							)
							if Trace.Fraction < 0.85 then
								Head:SetVelocity(Vector(0, 0, Mass * 9.84 * (1 - Trace.Fraction) * Multiplier))
								Multiplier = Multiplier + Tick
								Move()
							else
								rm.PlayerRecoverSpawn(Ply, Reset)
							end
						else
							Ply.rm_CanRecover = true
							return
						end
					end
				end)
			end
			Move()
		else
			rm.PlayerRecoverSpawn(Ply, Reset)
		end
	end
end
function rm.PlayerRecoverSpawn(Ply, Reset, Force)
	local Ragdoll = Ply.rm_Ragdoll
	local Health = Ply:Health()
	local Armor = Ply:Armor()
	local angles = Ply:EyeAngles()
	Ply:Spawn()
	if IsValid(Ragdoll) then
		if Reset then
			if not Force and rm.NinjaModeEnabled:GetBool() then
				local Melon = ents.Create("prop_physics")
				Melon:SetModel("models/props_junk/watermelon01.mdl")
				Melon:SetPos(Ragdoll:GetPos())
				Melon:Spawn()
				Melon:GetPhysicsObject():AddAngleVelocity(Vector(0, 0, 50000))
				local Effect = EffectData()
				Effect:SetOrigin(Ragdoll:GetPos())
				util.Effect("Explosion", Effect)
				rm.PlayerHint(Ply, "You disappeared in a cloud of fiery smoke...")
			else
				rm.PlayerHint(Ply, "You have been" ..(Force and " forcefully " or " ").. "reset!")
			end
		else
			if Ragdoll:IsOnFire() then
				Ply:Ignite(math.Rand(0, 120))
			end
			Ply:StripWeapons()
			if rm.RagdollRecoveryWeaponPreserveEnabled:GetBool() then
				if Ply.rm_WeaponPreserve then
					Ply:SetSuppressPickupNotices(true)
					for _, Item in pairs(Ply.rm_WeaponClass) do
						Ply:Give(Item)
					end
					for i, Item in pairs(Ply:GetWeapons()) do
						Item:SetClip1(Ply.rm_WeaponClip1[i])
						Item:SetClip2(Ply.rm_WeaponClip2[i])
					end
					for i, Item in pairs(Ply.rm_WeaponAmmoType) do
						Ply:SetAmmo(Ply.rm_WeaponAmmo[i], Item)
					end
					Ply:SelectWeapon(Ply.rm_WeaponSelected)
					Ply:SetSuppressPickupNotices(false)
					Ply.rm_WeaponClass = nil
					Ply.rm_WeaponClip1 = nil
					Ply.rm_WeaponClip2 = nil
					Ply.rm_WeaponAmmo = nil
					Ply.rm_WeaponAmmoType = nil
					Ply.rm_WeaponSelected = ""
					Ply.rm_WeaponPreserve = false
				end
				timer.Simple(0.1, function() Ply.rm_CanRagdolize = true end)
			end
			Ply:SetSkin(Ragdoll:GetSkin())
			Ply:SetMaterial(Ragdoll:GetMaterial())
			for i = 0, Ply:GetNumBodyGroups() - 1 do
				Ply:SetBodygroup(i, Ragdoll:GetBodygroup(i) or 0)
			end
			Ply:SetColor(Ragdoll:GetColor())
			Ply:SetHealth(Health)
			Ply:SetArmor(Armor)
			Ply:SetPos(
				util.TraceLine(
					{
						start = Ragdoll:GetPos() + Vector(0, 0, 10),
						endpos = Ragdoll:GetPos() - Vector(0, 0, 10),
						filter = {Ply, Ragdoll}
					}
				).HitPos
			)
			Ply:SetEyeAngles(angles)
			Ply:SetVelocity(Ragdoll:GetVelocity())
			if Force then
				rm.PlayerHint(Ply, "You have been forcefully recovered!")
			end
		end
	else
		if Force then
			rm.PlayerHint(Ply, "You have been forcefully reset!")
		else
			rm.PlayerHint(Ply, "You have lost your body and have been reset!")
		end
	end
	rm.PlayerRemoveRagdoll(Ply)
	Ply.rm_CanRecover = true
end
function rm.PlayerSpawn(Ply)
	if (not Ply.rm_Alive or not Ply.rm_Ready) then
		if not Ply.rm_Ready then
			rm.PlayerHint(Ply, "This server is running RagMod 2 " ..rm.Version.. ".", 20)
			if GAMEMODE.IsSandboxDerived then
				rm.PlayerHint(Ply, "See \"Spawn Menu > Options > RagMod 2\" for more information.", 20, 2.5)
			else
				rm.PlayerHint(Ply, "Use the console command rm_help for more information.", 20, 2.5)
			end
			Ply.rm_Ragdolls = {}
			rm.PlayerRemoveRagdollVariables(Ply)
		elseif not Ply.rm_Alive then
			Ply:SetMaterial(nil)
			Ply:SetColor(Color(255, 255, 255, 255))
			if not rm.RagdollKeepEnabled:GetBool() then
				rm.PlayerRemoveRagdoll(Ply)
			else
				rm.PlayerRemoveRagdollVariables(Ply)
			end
		end
		Ply.rm_CanRagdolize = true
		Ply.rm_CanRecover = true
		Ply.rm_SoundTimer = 0
		Ply.rm_Oxygen = 0
		Ply:SetNetworkedFloat("rm_Oxygen", 1)
		Ply.rm_Attacker = nil
		Ply.rm_Inflictor = nil
		Ply:SetNetworkedEntity("rm_Killer", NULL)
		Ply:SetNetworkedFloat("rm_DeathTime", 0)
		Ply:SetNetworkedFloat("rm_NextSpawnTime", 0)
		Ply.rm_WeaponClass = nil
		Ply.rm_WeaponClip1 = nil
		Ply.rm_WeaponClip2 = nil
		Ply.rm_WeaponAmmo = nil
		Ply.rm_WeaponSelected = ""
		Ply.rm_WeaponPreserve = false
		Ply.rm_WeaponLowered = false
		Ply.rm_RecoveryTimer = 0
		Ply.rm_Move = false
		Ply.rm_MoveTimer = 0
		Ply.rm_MoveSwitch = false
		Ply.rm_Twitch = false
		Ply.rm_Grab = false
		Ply.rm_Parachute = false
		Ply.rm_ParachuteEntity = nil
		Ply.rm_Kills = 0
		Ply:SetNetworkedInt("rm_Kills", 0)
		Ply.rm_Alive = true
		Ply.rm_Ready = true
	end
end
function rm.NPCRagdolize(NPC)
	for _, ClassName in pairs(string.Explode(",", rm.NPCRagdolizeBlacklist:GetString())) do
		if NPC:GetClass() == ClassName or NPC:GetClass() == "npc_" ..ClassName or NPC:GetClass() == "monster_" ..ClassName or NPC:GetClass() == "snpc_" ..ClassName then
			return
		end
	end
	local Ragdoll = ents.Create("prop_ragdoll")
	Ragdoll:SetModel(NPC:GetModel())
	Ragdoll:SetPos(NPC:GetPos())
	Ragdoll:SetAngles(NPC:GetAngles())
	Ragdoll:SetSkin(NPC:GetSkin())
	Ragdoll:SetMaterial(NPC:GetMaterial())
	for i = 0, Ragdoll:GetNumBodyGroups() - 1 do
		Ragdoll:SetBodygroup(i, NPC:GetBodygroup(i) or 0)
	end
	Ragdoll:SetColor(NPC:GetColor())
	Ragdoll:SetPhysicsAttacker(NPC)
	Ragdoll.rm_Owner = NPC
	Ragdoll.rm_IsRagdoll = true
	Ragdoll:SetNetworkedBool("rm_IsRagdoll", true)
	Ragdoll.rm_IsNPCRagdoll = true
	Ragdoll.rm_IsUnderwater = false
	Ragdoll:Spawn()
	table.insert(rm.Ragdolls, Ragdoll)
	if NPC:IsOnFire() then
		Ragdoll:Ignite(math.Rand(0, 120))
		NPC:Extinguish()
	end
	rm.RagdollIterateBones(Ragdoll, function(Bone, i)
		local Pos, angles = NPC:GetBonePosition(Ragdoll:TranslatePhysBoneToBone(i))
		Bone:SetPos(Pos)
		Bone:SetAngles(angles)
	end)
	if NPC.rm_DamageInfo then
		if NPC.rm_DamageInfo:GetDamageType() == DMG_FALL then
			local Velocity = NPC.rm_DamageInfo:GetDamageForce() * 10
			if Velocity == vector_origin then
				Velocity = vector_up * -150
			end
			rm.RagdollIterateBones(Ragdoll, function(Bone)
				Bone:SetVelocity(Velocity)
			end)
		else
			Ragdoll:TakeDamageInfo(NPC.rm_DamageInfo)
		end
	end
	rm.RagdollTwitch(Ragdoll, 100)
	NPC.rm_Ragdoll = Ragdoll
	NPC:SetNetworkedEntity("rm_Ragdoll", Ragdoll)
	local RagdollCount = 0
	local FirstRagdoll = nil
	if rm.RagdollKeepEnabled:GetBool() and rm.RagdollKeepNPCValue:GetInt() > 0 then
		for _, Ent in pairs(ents.FindByClass("prop_ragdoll")) do
			if Ent.rm_IsNPCRagdoll then
				FirstRagdoll = IsValid(FirstRagdoll) and FirstRagdoll or Ent
				RagdollCount = RagdollCount + 1
				if RagdollCount > rm.RagdollKeepNPCValue:GetInt() then
					rm.RagdollRemove(FirstRagdoll)
				end
			end
		end
	elseif not rm.RagdollKeepEnabled:GetBool() then
		timer.Simple(10, function() rm.RagdollRemove(Ragdoll) end)
	end
	return Ragdoll
end
function rm.PlayerHint(Ply, Text, Time, Delay)
	if rm.HintEnabled:GetBool() then
		local function ShowHint()
			if GAMEMODE.IsSandboxDerived then
				Ply:SendLua("GAMEMODE:AddNotify([[[RagMod] " ..Text.. "]], NOTIFY_GENERIC, " ..(Time or "rm.HintTime:GetFloat()").. ") surface.PlaySound(\"ambient/water/drip" ..math.random(1, 4).. ".wav\")")
			else
				Ply:ChatPrint("[RagMod] " ..Text)
			end
		end
		if Delay then
			timer.Simple(Delay, ShowHint)
		else
			ShowHint()
		end
	end
end
function rm.PlaySound(Ent, Mode)
	if rm.SoundEnabled:GetBool() then
		local Gender = nil
		local SoundTable = rm.Sounds[Mode]
		if not SoundTable then
			Gender = rm.GetPlayerModelGender(Ent:GetModel())
			SoundTable = rm.Sounds[Gender .. Mode]
		end
		if SoundTable and #SoundTable > 0 then
			local Sound = CreateSound(Ent, table.Random(SoundTable))
			Sound:PlayEx(rm.SoundVolume:GetFloat(), math.Rand(95, 105) * ((GetConVar("host_timescale"):GetFloat() + 1) / 2))
			return Sound
		end
	end
end
function rm.PlayerPlaySound(Ply, Mode, Override)
	if rm.SoundEnabled:GetBool() and (Ply.rm_SoundTimer >= rm.SoundDelay:GetFloat() or Override) then
		if Ply.rm_PlayerSound then
			Ply.rm_PlayerSound:Stop()
		end
		Ply.rm_PlayerSound = rm.PlaySound(IsValid(Ply.rm_Ragdoll) and Ply.rm_Ragdoll or Ply, Mode)
		Ply.rm_SoundTimer = 0
	end
end
function rm.RagdollIterateBones(Ragdoll, Action)
	for i = 0, Ragdoll:GetPhysicsObjectCount() - 1 do
		local Bone = Ragdoll:GetPhysicsObjectNum(i)
		if IsValid(Bone) then
			if Action(Bone, i, Ragdoll) == false then
				return false
			end
		end
	end
	return true
end
function rm.RagdollClosestBone(Ragdoll, Pos, Restrict)
	local Target, TargetIndex, TargetChild, TargetChildIndex, TargetParent, TargetParentIndex = nil, nil, nil, nil, nil, nil
	rm.RagdollIterateBones(Ragdoll, function(Bone, i)
		local ModelBone = Ragdoll:TranslatePhysBoneToBone(i)
		if i ~= 0 and (not Restrict or (Restrict and (not Ragdoll["rm_DecapitatedBone" ..i] and ModelBone ~= Ragdoll:LookupBone("ValveBiped.Bip01_Spine1") and ModelBone ~= Ragdoll:LookupBone("ValveBiped.Bip01_Spine2")))) and (not Target or (Target and Bone:GetPos():Distance(Pos) < Target:GetPos():Distance(Pos))) then
			Target = Bone
			TargetIndex = i
		end
	end)
	if Target then
		rm.RagdollIterateBones(Ragdoll, function(Bone, i)
			if Ragdoll:TranslateBoneToPhysBone(Ragdoll:GetBoneParent(Ragdoll:TranslatePhysBoneToBone(i))) == TargetIndex then
				TargetChild = Bone
				TargetChildIndex = i
			end
		end)
		TargetParentIndex = Ragdoll:TranslateBoneToPhysBone(Ragdoll:GetBoneParent(Ragdoll:TranslatePhysBoneToBone(TargetIndex)))
		if TargetParentIndex and TargetParentIndex ~= TargetIndex then
			rm.RagdollIterateBones(Ragdoll, function(Bone, i)
				if i == TargetParentIndex then
					TargetParent = Bone
				end
			end)
		end
	end
	return Target, TargetIndex, TargetChild, TargetChildIndex, TargetParent, TargetParentIndex
end
function rm.RagdollHideChildBones(Ragdoll, MasterBone)
	Ragdoll:ManipulateBoneScale(MasterBone, vector_origin)
	Ragdoll:ManipulateBonePosition(MasterBone, vector_origin)
	for _, Bone in pairs(Ragdoll:GetChildBones(MasterBone)) do
		Ragdoll:ManipulateBoneScale(Bone, vector_origin)
		Ragdoll:ManipulateBonePosition(Bone, Ragdoll:GetPhysicsObjectNum(Ragdoll:TranslateBoneToPhysBone(Bone)):WorldToLocal(Ragdoll:GetBonePosition(MasterBone)))
	end
end
function rm.RagdollTwitch(Ragdoll, Amount)
	rm.RagdollIterateBones(Ragdoll, function(Bone, i)
		if i ~= 0 then
			Bone:AddVelocity(VectorRand() * Amount)
		end
	end)
end
function rm.RagdollDeath(Ragdoll)
	if rm.RagdollDeathEffectEnabled:GetBool() then
		local Bone = Ragdoll:GetPhysicsObjectNum(Ragdoll:TranslateBoneToPhysBone(math.random(0, 1) == 1 and 0 or (Ragdoll:LookupBone("ValveBiped.Bip01_Head1") or Ragdoll:LookupBone("head") or 0)))
		Velocity = math.max(Bone:GetVelocity():Length() / 80, 1)
		local Multiplier = 1000 * (1 / Velocity) * rm.RagdollDeathEffectMultiplier:GetFloat()
		local Count = math.Rand(1, 5)
		local CountMax = Count
		local function Move()
			local Tick = FrameTime()
			timer.Simple(Tick, function()
				if IsValid(Ragdoll) then
					Bone:SetDamping(0, 0)
					if Count > 0 then
						local Height = Ragdoll:OBBMaxs().z - Ragdoll:OBBMins().z
						if rm.RagdollIterateBones(Ragdoll, function(Bone)
							Trace = util.TraceLine(
								{
									start = Bone:GetPos(),
									endpos = Bone:GetPos() + Vector(0, 0, -Height),
									filter = Ragdoll
								}
							)
							if not Trace.Hit then
								return false
							end
						end) then
							Bone:SetDamping(Multiplier * (Count / CountMax), 0)
							Count = Count - Tick
							Move()
						end
					end
				end
			end)
		end
		Move()
	end
	if rm.RagdollDeathFacePoseEnabled:GetBool() then
		local Count = math.Rand(2, 3)
		local CountMax = Count
		local function Pose()
			local Tick = FrameTime()
			timer.Simple(Tick, function()
				if IsValid(Ragdoll) and Count > 0 then
					local Value = 1 - math.cos((Count / CountMax) * (math.pi / 2))
					local FlexNum = Ragdoll:GetFlexNum() - 1
					if FlexNum <= 0 then
						return
					end
					for i = 0, FlexNum - 1 do
						local Name = Ragdoll:GetFlexName(i)
						if Name == "jaw_drop" or Name == "right_part" or Name == "left_part" or Name == "right_mouth_drop" or Name == "left_mouth_drop" then
							Ragdoll:SetFlexWeight(i, Value)
						end
					end
					Count = Count - Tick
					Pose()
				end
			end)
		end
		Pose()
	end
	if rm.RagdollTwitchEnabled:GetBool() and rm.RagdollTwitchOnDeathEnabled:GetBool() then
		local Count = math.Rand(12, 15)
		local CountMax = Count
		local function Move()
			local Tick = FrameTime()
			timer.Simple(Tick, function()
				if IsValid(Ragdoll) then
					Count = Count - Tick
					if Count <= 0 then
						return
					end
					local Multiplier = Count / CountMax
					if Ragdoll:IsOnFire() then
						rm.RagdollTwitch(Ragdoll, 50 * Multiplier)
					else
						rm.RagdollIterateBones(Ragdoll, function(Bone, i)
							if i ~= 0 and math.random(0, 1000 * (1 - Multiplier)) == 0 then
								Bone:AddVelocity(VectorRand() * 80 * Multiplier)
							end
						end)
					end
					Move()
				end
			end)
		end
		Move()
	end
end
function rm.PlayerDropActiveWeapon(Ply, Advanced)
	local Weapon = Ply:GetActiveWeapon()
	if IsValid(Weapon) and Weapon:GetClass() ~= "swep_parachute" and Weapon:GetClass() ~= "swep_climbrope" and Weapon:GetModel() ~= "" then
		local Keep = false
		local Class = Weapon:GetClass()
		if Advanced == true then
			if Weapon:GetPrimaryAmmoType() ~= -1 then
				local Count = 0
				if Class == "weapon_ar2" then
					Count = 30
				elseif Class == "weapon_crossbow" then
					if Weapon:Clip1() == 0 then
						Count = 5
					else
						Count = 4
					end
				elseif Class == "weapon_deagle" then
					Count = 40
				elseif Class == "weapon_frag" then
					Keep = true
					Count = 1
				elseif Class == "weapon_glock" then
					Count = 8
				elseif Class == "weapon_m4" then
					Count = 25
				elseif Class == "weapon_mac10" then
					Count = 50
				elseif Class == "weapon_para" then
					Count = 100
				elseif Class == "weapon_pumpshotgun" then
					Count = 8
				elseif Class == "weapon_rpg" then
					Count = 3
				elseif Class == "weapon_tmp" then
					Count = 25
				elseif Class == "weapon_slam" then
					Keep = true
					Count = 3
				elseif Weapon:Clip1() == -1 and Weapon:Clip2() == -1 then
					Count = 1
				end
				if Count > 0 then
					if Ply:GetAmmoCount(Weapon:GetPrimaryAmmoType()) >= Count then
						Ply:RemoveAmmo(Count, Weapon:GetPrimaryAmmoType())
						if Ply:GetAmmoCount(Weapon:GetPrimaryAmmoType()) == 0 then
							Keep = false
						end
					else
						return
					end
				end
			end
		end
		local NewWeapon = ents.Create(Weapon:GetClass())
		NewWeapon:SetKeyValue("spawnflags", "2")
		NewWeapon:Spawn()
		local Trace = util.TraceLine(
			{
				start = Ply:EyePos(),
				endpos = Ply:EyePos() + (Ply:GetAimVector() * 100),
				filter = Ply
			}
		)
		if Trace.Hit and Advanced then
			NewWeapon:SetPos(Trace.HitPos + Vector(0, 0, 10))
			NewWeapon:SetAngles(Ply:GetAngles() + Angle(0, 90 * (math.random(0, 1) == 1 and -1 or 1), math.random(0, 1) == 1 and (math.random(0, 1) == 1 and 90 or -90) or 0))
		else
			NewWeapon:SetPos(Ply:EyePos() + (Ply:GetAimVector() * 30))
			NewWeapon:SetAngles(Ply:EyeAngles())
			if IsValid(NewWeapon:GetPhysicsObject()) then
				if not Advanced then
					NewWeapon:GetPhysicsObject():AddAngleVelocity(Vector(math.Rand(-600, 600), math.Rand(-600, 600), math.Rand(-600, 600)))
				end
				NewWeapon:GetPhysicsObject():SetVelocity(Ply:GetVelocity() + (Ply:GetAimVector() * (Advanced and 500 or math.Rand(50, 150))))
			end
		end
		NewWeapon:SetClip1(Weapon:Clip1())
		NewWeapon:SetClip2(Weapon:Clip2())
		timer.Simple(2, function()
			if IsValid(NewWeapon) then
				NewWeapon:SetKeyValue("spawnflags", "0")
			end
		end)
		if not Keep then
			Weapon:Remove()
		end
		return Keep
	end
	return true
end
function rm.PlayerRemoveRagdollVariables(Ply)
	Ply.rm_Ragdoll = nil
	Ply:SetNetworkedEntity("rm_Ragdoll", NULL)
end
function rm.PlayerRemoveRagdoll(Ply)
	if IsValid(Ply.rm_Ragdoll) then
		Ply.rm_Ragdoll:Remove()
	end
	rm.PlayerRemoveRagdollVariables(Ply)
end
function rm.RagdollRemove(Ragdoll, Mode)
	Mode = Mode or 2
	if Mode == 1 then
		Ragdoll:Remove()
	elseif Mode == 2 or Mode == 3 then
		Ragdoll.rm_IsRagdoll = false
		Ragdoll:SetNetworkedBool("rm_IsRagdoll", false)
		Ragdoll.rm_IsNPCRagdoll = false
		Ragdoll:SetNetworkedBool("rm_IsNPCRagdoll", false)
		Ragdoll.rm_IsLimb = false
		Ragdoll:SetNetworkedBool("rm_IsLimb", false)
		if Mode == 2 then
			Ragdoll:SetMoveType(0)
			Ragdoll:SetSolid(0)
			Ragdoll:DrawShadow(false)
			Ragdoll:SetRenderMode(RENDERMODE_TRANSALPHA)
			local Alpha = 1
			local function Fade()
				local Tick = FrameTime()
				timer.Simple(Tick, function()
					Alpha = Alpha - Tick
					if IsValid(Ragdoll) then
						if Alpha <= 0 then
							Ragdoll:Remove()
						else
							local RagdollColor = Ragdoll:GetColor()
							Ragdoll:SetColor(Color(RagdollColor.r, RagdollColor.g, RagdollColor.b, Alpha * 255))
							Fade()
						end
					end
				end)
			end
			Fade()
		end
	end
end
function rm.PlayerGrab(Ply)
	if rm.RagdollGrabEnabled:GetBool() then
		if Ply.rm_Grab and IsValid(Ply.rm_Ragdoll) then
			if IsValid(Ply.rm_GrabLeftConstraint) then
				Ply.rm_GrabLeftConstraint:Remove()
			end
			if IsValid(Ply.rm_GrabRightConstraint) then
				Ply.rm_GrabRightConstraint:Remove()
			end
			Ply.rm_Grab = false
		elseif not Ply.rm_Grab then
			if not Ply.rm_Ragdoll then
				local Ent = Ply:GetGroundEntity()
				if IsValid(Ent) or Ent:EntIndex() == 0 then
					local Ragdoll = rm.PlayerRagdolize(Ply)
					if IsValid(Ragdoll) then
						Ply.rm_RecoveryTimer = rm.RagdollRecoveryDelayDefault:GetFloat()
						local Strength = rm.RagdollGrabStrength:GetFloat()
						local LeftHand = Ragdoll:GetPhysicsObjectNum(5)
						local RightHand = Ragdoll:GetPhysicsObjectNum(7)
						local LeftFoot = Ragdoll:GetPhysicsObjectNum(12)
						local RightFoot = Ragdoll:GetPhysicsObjectNum(9)
						local Head = Ragdoll:GetPhysicsObjectNum(10)
						local LeftConstraint = constraint.Weld(Ragdoll, Ent, 9, 0, Strength, false)
						Ply.rm_GrabLeftConstraint = LeftConstraint
						local RightConstraint = constraint.Weld(Ragdoll, Ent, 12, 0, Strength, false)
						Ply.rm_GrabRightConstraint = RightConstraint
						Ply.rm_Grab = true
						local function Balance()
							timer.Simple(FrameTime(), function()
								if IsValid(Ply) and Ply.rm_Alive and IsValid(Ragdoll) and (IsValid(LeftConstraint) or IsValid(RightConstraint)) then
									LeftHand:AddVelocity((Vector(0, 0, 30) + (Ply:GetAngles():Right() * -20)) * math.Rand(0.5, 1))
									RightHand:AddVelocity((Vector(0, 0, 30) + (Ply:GetAngles():Right() * 20)) * math.Rand(0.5, 1))
									Head:AddVelocity(Vector(0, 0, 140))
									if IsValid(LeftConstraint) then
										if not IsValid(RightConstraint) then
											Ply.rm_Twitch = true
											if math.random(1, 1000) == 1 then
												LeftConstraint:Remove()
											end
										end
										local Pos = LeftFoot:GetPos()
										local Trace = util.TraceLine({start = Pos, endpos = Pos - Vector(0, 0, 25), filter = {Ragdoll, Ply}, mask = MASK_SOLID})
										if Trace.Entity ~= Ent then
											LeftConstraint:Remove()
										end
									end
									if IsValid(RightConstraint) then
										if not IsValid(LeftConstraint) then
											Ply.rm_Twitch = true
											if math.random(1, 1000) == 1 then
												RightConstraint:Remove()
											end
										end
										local Pos = RightFoot:GetPos()
										local Trace = util.TraceLine({start = Pos, endpos = Pos - Vector(0, 0, 25), filter = {Ragdoll, Ply}, mask = MASK_SOLID})
										if Trace.Entity ~= Ent then
											RightConstraint:Remove()
										end
									end
									if Ply.rm_Twitch and math.random(1, 100) == 1 then
										rm.PlayerPlaySound(Ply, "FreeFall")
									end
									Balance()
								else
									if IsValid(LeftConstraint) then
										LeftConstraint:Remove()
									end
									if IsValid(RightConstraint) then
										RightConstraint:Remove()
									end
									Ply.rm_Twitch = false
									Ply.rm_Grab = false
								end
							end)
						end
						Balance()
					end
				end
			end
		end
	end
end
function rm.PlayerParachute(Ply)
	if rm.RagdollParachuteEnabled:GetBool() and Ply.rm_Alive and not Ply.rm_Parachute and not IsValid(Ply.rm_ParachuteEntity) then
		local Ragdoll = Ply.rm_Ragdoll
		if not Ragdoll then
			Ply.rm_RecoveryTimer = rm.RagdollRecoveryDelayDefault:GetFloat()
			Ragdoll = rm.PlayerRagdolize(Ply)
		end
		if IsValid(Ragdoll) then
			local Parachute = ents.Create("prop_physics")
			Parachute:SetModel("models/props_debris/metal_panel01a.mdl")
			Parachute:SetPos(Ragdoll:GetPos() + Vector(0, 0, 40))
			Parachute:SetAngles(Angle(90, -90, Ply:EyeAngles().yaw))
			Parachute:SetMaterial("models/props_c17/FurnitureFabric003a")
			Parachute:Spawn()
			Parachute:GetPhysicsObject():SetMass(40)
			Parachute:GetPhysicsObject():SetDamping(15 * rm.RagdollParachuteMultiplier:GetFloat(), math.Rand(1, 2))
			local LeftFrontConstraint, LeftFrontRope = constraint.Elastic(Ragdoll, Parachute, 1, 0, Vector(6, 5, 5), Vector(3, 22, -60), 200, 100, 0, "cable/cable", 1, true)
			local LeftBackConstraint, LeftFrontRope = constraint.Elastic(Ragdoll, Parachute, 1, 0, Vector(6, -3, 5), Vector(3, -22, -60), 200, 100, 0, "cable/cable", 1, true)
			local RightFrontConstraint, RightFrontRope = constraint.Elastic(Ragdoll, Parachute, 1, 0, Vector(6, 5, -5), Vector(3, 22, 60), 200, 100, 0, "cable/cable", 1, true)
			local RightBackConstraint, RightBackRope = constraint.Elastic(Ragdoll, Parachute, 1, 0, Vector(6, -3, -5), Vector(3, -22, 60), 200, 100, 0, "cable/cable", 1, true)
			local LeftHandConstraint, LeftHandRope = constraint.Elastic(Ragdoll, Parachute, 5, 0, Vector(5, -2, 0), Vector(3, 0, -50), 150, 100, 0, "cable/cable", 0.5, true)
			local RightHandConstraint, RightHandRope = constraint.Elastic(Ragdoll, Parachute, 7, 0, Vector(5, -2, 0), Vector(3, 0, 50), 150, 100, 0, "cable/cable", 0.5, true)
			Ply.rm_ParachuteEntity = Parachute
			Ply.rm_Parachute = true
			local function Check()
				timer.Simple(FrameTime(), function()
					if IsValid(Ragdoll) and IsValid(Parachute) and (not IsValid(Ply) or (Ply and (not Ply.rm_Ragdoll or (Ply.rm_Ragdoll == Ragdoll and Ply.rm_Parachute)))) then
						Check()
					else
						if IsValid(LeftFrontConstraint) then
							LeftFrontConstraint:Remove()
						end
						if IsValid(LeftBackConstraint) then
							LeftBackConstraint:Remove()
						end
						if IsValid(RightFrontConstraint) then
							RightFrontConstraint:Remove()
						end
						if IsValid(RightBackConstraint) then
							RightBackConstraint:Remove()
						end
						if IsValid(LeftHandConstraint) then
							LeftHandConstraint:Remove()
						end
						if IsValid(RightHandConstraint) then
							RightHandConstraint:Remove()
						end
						if IsValid(Parachute) then
							Parachute:Remove()
						end
						Ply.rm_ParachuteEntity = nil
						Ply.rm_Parachute = false
					end
				end)
			end
			Check()
		end
	end
end
hook.Add("Tick", "rm_sv_Tick", function()
	local Enabled = rm.Enabled:GetBool()
	if rm.EnabledDelta ~= Enabled then
		rm.EnabledDelta = Enabled
		for _, Ply in pairs(player.GetAll()) do
			rm.PlayerHint(Ply, "RagMod 2 is now " ..(rm.EnabledDelta and "en" or "dis").. "abled.", 5)
			if IsValid(Ply.rm_Ragdoll) then
				Ply:Spawn()
			end
		end
	end
	if Enabled then
		local rm_Tick = FrameTime()
		if rm.NPCRagdolizeOnDeathEnabled:GetBool() then
			if not GetConVar("ai_serverragdolls"):GetBool() then
				RunConsoleCommand("ai_serverragdolls", "1")
				for _, Ply in pairs(player.GetAll()) do
					rm.PlayerHint(Ply, "ai_serverragdolls needs to be enabled for NPC death ragdolization compatibility.", 10, 1)
				end
			end
		end
		local i = 1
		while i <= #rm.Ragdolls do
			local Item = rm.Ragdolls[i]
			if not Item then
				break
			elseif not IsValid(Item) then
				table.remove(rm.Ragdolls, i)
			else
				if rm.RagdollTwitchEnabled:GetBool() and rm.RagdollTwitchOnSpeedEnabled:GetBool() then
					rm.RagdollTwitch(Item, Item:GetVelocity():Length() * 0.015 * rm.RagdollTwitchOnSpeedMultiplier:GetFloat())
				end
				if Item:WaterLevel() == 3 then
					if Item:IsOnFire() and math.random(1, 15) == 1 then
						Item:Extinguish()
					end
					if Item.rm_IsUnderwater ~= true then
						Item.rm_IsUnderwater = true
						if Item:GetVelocity():Length() > math.Rand(150, 250) then
							local Water = EffectData()
							Water:SetOrigin(Item:GetPos())
							Water:SetScale(Item:GetVelocity():Length() / 10)
							util.Effect("WaterSplash", Water)
						end
					end
				else
					Item.rm_IsUnderwater = false
				end
				i = i + 1
			end
		end
		for _, Ply in pairs(player.GetAll()) do
			if Ply:WaterLevel() == 3 then
				Ply.rm_IsUnderwater = true
				Ply:Extinguish()
				if rm.OxygenEnabled:GetBool() then
					Ply.rm_Oxygen = math.min(Ply.rm_Oxygen + rm_Tick, rm.OxygenValue:GetFloat())
				end
			else
				Ply.rm_IsUnderwater = false
				if rm.OxygenEnabled:GetBool() then
					Ply.rm_Oxygen = math.max(Ply.rm_Oxygen - rm_Tick * rm.OxygenRegenerateValue:GetFloat(), 0)
				end
			end
			if Ply.rm_Alive then
				if rm.OxygenEnabled:GetBool() and Ply.rm_Oxygen >= rm.OxygenValue:GetFloat() then
					if CurTime() > (Ply.rm_NextDrown or 0) then
						local Damage = rm.OxygenDrownDamage:GetFloat()
						if Ply.rm_Ragdoll then
							Ply:SetHealth(math.max(Ply:Health() - Damage, 0))
							if Ply:Health() - Damage <= 0 then
								if rm.WeaponDropOnDrownEnabled:GetBool() then
									rm.PlayerDropActiveWeapon(Ply, false)
								end
								Ply:Kill()
							end
						else
							if Ply:Health() - Damage <= 0 then
								if rm.WeaponDropOnDrownEnabled:GetBool() then
									rm.PlayerDropActiveWeapon(Ply, false)
								end
							end
							local Info = DamageInfo()
							Info:SetDamageType(DMG_DROWN)
							Info:SetDamagePosition(Ply:GetPos())
							Info:SetDamageForce(Vector(VectorRand() * 3, VectorRand() * 3, VectorRand() * 3))
							Info:SetDamage(Damage)
							Info:SetAttacker(Ply)
							Ply:TakeDamageInfo(Info)
						end
						rm.PlayerPlaySound(Ply, "PlayerDrown")
						Ply.rm_NextDrown = CurTime() + rm.OxygenDrownDelay:GetFloat()
					end
				end
			else
				Ply.rm_Move = false
				Ply.rm_Twitch = false
				Ply.rm_Grab = false
			end
			local Ragdoll = Ply.rm_Ragdoll
			if IsValid(Ragdoll) then
				if Ply:FlashlightIsOn() then
					Ply:Flashlight(false)
				end
				Ply:SetPos(Ragdoll:GetPos() + Vector(0, 0, 9.5))
				if Ply.rm_Alive then
					if not Ply.rm_Move and math.random(1, 150) == 1 and Ragdoll:GetVelocity():Length() >= rm.RagdolizeOnSpeedValue:GetFloat() / 3 then
						rm.PlayerPlaySound(Ply, "FreeFall")
					end
					if rm.RagdollTwitchEnabled:GetBool() and ((Ply.rm_Twitch and rm.RagdollTwitchOnCommandEnabled:GetBool()) or Ply.rm_Oxygen >= rm.OxygenValue:GetFloat()) then
						rm.RagdollIterateBones(Ragdoll, function(Bone, i)
							if math.random(1, 5) == 1 and (i == 10 or i == 5 or i == 7 or i == 13 or i == 14) then
								Bone:AddVelocity(VectorRand() * 325)
							end
						end)
						if math.random(1, 400) == 1 then
							Ragdoll:Extinguish()
						end
						if Ragdoll.rm_IsUnderwater and math.random(1, 50) == 1 then
							local Water = EffectData()
							Water:SetOrigin(Ragdoll:GetPos() + VectorRand() * 20)
							Water:SetScale(math.Rand(2, 6))
							util.Effect("WaterSplash", Water)
						end
					end
					if rm.RagdollMoveEnabled:GetBool() and Ply.rm_Move then
						local Velocity = Ragdoll:GetVelocity()
						if Ply.rm_Parachute then
							local Force = Ply:GetAimVector() * math.Clamp(Ragdoll:GetVelocity():Length() / 8, 15, 1000)
							local ForceRight = Ply:EyeAngles():Right() * 100

							Ply.rm_ParachuteEntity:GetPhysicsObject():SetVelocity(Velocity + Force)

							local Bone = Ragdoll:GetPhysicsObjectNum(1)
							Bone:SetVelocity(Velocity + Force / 7)

							Bone = Ragdoll:GetPhysicsObjectNum(10)
							Bone:SetVelocity(Velocity + Force / 15)

							Bone = Ragdoll:GetPhysicsObjectNum(5)
							Bone:SetVelocity(Velocity - ForceRight)

							Bone = Ragdoll:GetPhysicsObjectNum(7)
							Bone:SetVelocity(Velocity + ForceRight)
						else
							local Superman = rm.RagdollMoveSupermanModeEnabled:GetBool()
							if Velocity:Length() < 200 then
								if Ply.rm_MoveTimer >= 0.5 then
									Ply.rm_MoveTimer = 0
									Ply.rm_MoveSwitch = not Ply.rm_MoveSwitch
								end
								local Force = (Ragdoll.rm_IsUnderwater and Ply:GetAimVector() or Ply:GetAngles():Forward()) * (Ply.rm_MoveTimer / 0.5) * 900

								local Bone = Ragdoll:GetPhysicsObjectNum(1)
								if not Ply.rm_Grab then
									Bone:ApplyForceOffset(-Bone:GetAngles():Right(), Vector(0, 0, 10000))
								end
								Bone:SetVelocity(Velocity + Force / 35)

								Bone = Ragdoll:GetPhysicsObjectNum(10)
								Bone:SetVelocity(Velocity + Force / 10)

								Bone = Ragdoll:GetPhysicsObjectNum(Ply.rm_MoveSwitch and 5 or 7)
								Bone:SetVelocity(Velocity + Force)
								Bone = Ragdoll:GetPhysicsObjectNum(Ply.rm_MoveSwitch and 4 or 6)
								Bone:SetVelocity(Velocity + Force / 1.5)

								Bone = Ragdoll:GetPhysicsObjectNum(Ply.rm_MoveSwitch and 7 or 5)
								Bone:SetVelocity(Velocity + Force / 3)
								Bone = Ragdoll:GetPhysicsObjectNum(Ply.rm_MoveSwitch and 6 or 4)
								Bone:SetVelocity(Velocity - Force / 2)
							elseif Superman or Velocity.z < -300 then
								local Multiplier = Superman and 1 or (1 - (1 / ((-(Velocity.z + 300) / 1000) + 1)))
								if Ply:GetAimVector().z <= -0.99 then
									local ForceForward = Ply:EyeAngles():Forward() * 100 * Multiplier
									local ForceUp = Vector(0, 0, Multiplier * 200)
									local ForceDown = -ForceUp * 2

									local Bone = Ragdoll:GetPhysicsObjectNum(1)
									Bone:SetVelocity(Velocity + ForceDown * 0.3)

									Bone = Ragdoll:GetPhysicsObjectNum(10)
									Bone:SetVelocity(Velocity + ForceForward + ForceDown)

									Bone = Ragdoll:GetPhysicsObjectNum(5)
									Bone:SetVelocity(Velocity + ForceUp - (ForceForward / 2))

									Bone = Ragdoll:GetPhysicsObjectNum(7)
									Bone:SetVelocity(Velocity + ForceUp - (ForceForward / 2))

									Bone = Ragdoll:GetPhysicsObjectNum(12)
									Bone:SetVelocity(Velocity + ForceUp - (ForceForward / 2))

									Bone = Ragdoll:GetPhysicsObjectNum(9)
									Bone:SetVelocity(Velocity + ForceUp - (ForceForward / 2))
								else
									local ForceForward = (Superman and (Ply:GetAimVector() * 250) or (Ply:EyeAngles():Forward() * 150)) * Multiplier
									local ForceRight = Ply:EyeAngles():Right() * 100 * Multiplier
									local ForceUp = Vector(0, 0, 70) * Multiplier

									local Bone = Ragdoll:GetPhysicsObjectNum(1)
									Bone:ApplyForceOffset(-Bone:GetAngles():Right(), Vector(0, 0, 10000 * Multiplier))
									Bone:SetVelocity(Velocity + (ForceUp / 10) + (ForceForward / 25))

									Bone = Ragdoll:GetPhysicsObjectNum(5)
									Bone:SetVelocity(Velocity + (ForceUp / 2) + ForceForward - (Superman and vector_origin or ForceRight))
									Bone = Ragdoll:GetPhysicsObjectNum(4)
									Bone:SetVelocity(Velocity + (ForceUp / 2) + (ForceForward / 2) - (Superman and vector_origin or ForceRight))
									Bone = Ragdoll:GetPhysicsObjectNum(7)
									Bone:SetVelocity(Velocity + (ForceUp / 2) + ForceForward + (Superman and vector_origin or ForceRight))
									Bone = Ragdoll:GetPhysicsObjectNum(6)
									Bone:SetVelocity(Velocity + (ForceUp / 2) + (ForceForward / 2) + (Superman and vector_origin or ForceRight))

									Bone = Ragdoll:GetPhysicsObjectNum(12)
									Bone:SetVelocity(Velocity + (ForceUp / 2) - (ForceForward / 5) - (ForceRight / 5))
									Bone = Ragdoll:GetPhysicsObjectNum(9)
									Bone:SetVelocity(Velocity + (ForceUp / 2) - (ForceForward / 5) + (ForceRight / 5))
								end
							end
						end
					end
				end
			else
				if rm.RagdolizeOnSpeedEnabled:GetBool() and Ply:GetVelocity():Length() >= rm.RagdolizeOnSpeedValue:GetFloat() then
					rm.PlayerPlaySound(Ply, "FreeFall")
					Ply.rm_RecoveryTimer = rm.RagdollRecoveryDelayOnFall:GetFloat()
					Ragdoll = rm.PlayerRagdolize(Ply)
					if IsValid(Ragdoll) then
						rm.RagdollTwitch(Ragdoll, 900)
					end
				end
			end
			if rm.SoundEnabled:GetBool() then
				Ply.rm_SoundTimer = Ply.rm_SoundTimer + rm_Tick
			end
			if rm.RagdollMoveEnabled:GetBool() then
				Ply.rm_MoveTimer = Ply.rm_MoveTimer + (rm_Tick / 2)
			end
			if rm.RagdollRecoveryEnabled:GetBool() and rm.RagdollRecoveryDelayEnabled:GetBool() then
				Ply.rm_RecoveryTimer = Ply.rm_RecoveryTimer - rm_Tick
				Ply:SetNetworkedInt("rm_RecoveryTimer", Ply.rm_RecoveryTimer)
			else
				Ply:SetNetworkedInt("rm_RecoveryTimer", 0)
			end
			if rm.OxygenEnabled:GetBool() then
				Ply:SetNetworkedFloat("rm_Oxygen", 1 - (Ply.rm_Oxygen / rm.OxygenValue:GetFloat()))
			else
				Ply:SetNetworkedFloat("rm_Oxygen", 1)
			end
		end
	end
end)
hook.Add("CreateEntityRagdoll", "rm_sv_BlockNPCRagdolls", function(Ent, Ragdoll)
	if rm.Enabled:GetBool() then
		if IsValid(Ent) and Ent:IsNPC() and rm.NPCRagdolizeOnDeathEnabled:GetBool() then
			Ragdoll:Remove()
		end
	end
end)
hook.Add("EntityTakeDamage", "rm_sv_Damage", function(Ent, Info)
	if rm.Enabled:GetBool() then
		if rm.NPCRagdolizeOnDeathEnabled:GetBool() and Ent:IsNPC() then
			Ent.rm_DamageInfo = Info
		else
			local Ply = nil
			local Vehicle = nil
			local Ragdoll = nil
			local IsLimb = false
			if Info:GetAmmoType() == 18 then
				Info:SetDamage(GetConVarNumber("sk_jeep_gauss_damage"))
			end
			if Info:GetAmmoType() == 20 then
				Info:SetDamage(GetConVarNumber("sk_plr_dmg_airboat"))
			end
			local Attacker = Info:GetAttacker()
			local Inflictor = Info:GetInflictor()
			local Amount = Info:GetDamage()
			if Ent:IsPlayer() then
				Ply = Ent
			elseif Ent:IsVehicle() then
				Vehicle = Ent
				Ply = Vehicle:GetDriver()
			elseif Ent:GetClass() == "prop_ragdoll" then
				if Ent.rm_IsRagdoll then
					Ragdoll = Ent
					IsLimb = Ent.rm_IsLimb or false
					if not IsLimb then
						local Owner = Ent.rm_Owner
						if IsValid(Owner) and Owner:IsPlayer() then
							if Owner.rm_Ragdoll == Ent then
								Ply = Owner
							end
						end
					end
				end
			end
			Ply = IsValid(Ply) and Ply or nil
			Vehicle = IsValid(Vehicle) and Vehicle or nil
			Ragdoll = IsValid(Ragdoll) and Ragdoll or nil
			if Ply ~= nil or Ragdoll ~= nil then
				if Info:GetDamagePosition() == vector_origin then
					Info:SetDamagePosition((IsLimb and Ragdoll:GetPhysicsObjectNum(Ragdoll.rm_LimbIndex):GetPos() or (Ragdoll or Ply):GetPos()) + (VectorRand() * (IsLimb and 5 or 20)))
				end
				if not IsValid(Attacker) then
					Attacker = game.GetWorld()
					if IsValid(Inflictor) then
						if Inflictor:IsPlayer() or Inflictor:IsNPC() then
							Attacker = Inflictor
						elseif Inflictor:IsVehicle() then
							Attacker = Inflictor:GetDriver()
						elseif IsValid(Inflictor:GetOwner()) then
							Attacker = Inflictor:GetOwner()
						elseif IsValid(Inflictor.rm_Owner) then
							Attacker = Inflictor.rm_Owner
						elseif IsValid(Inflictor.Owner) then
							Attacker = Inflictor.Owner
						end
					end
				end
				if not IsValid(Inflictor) or (Inflictor == Attacker and (Attacker:IsPlayer() or Attacker:IsNPC())) then
					Inflictor = game.GetWorld()
					if Attacker:IsPlayer() or Attacker:IsNPC() then
						local Weapon = Attacker:GetActiveWeapon()
						if IsValid(Weapon) then
							Inflictor = Weapon
						end
					end
				end
				if Ply then
					if IsValid(Attacker) or not IsValid(Ply.rm_Attacker) then
						Ply.rm_Attacker = Attacker
					end
					if IsValid(Inflictor) or not IsValid(Ply.rm_Inflictor) then
						Ply.rm_Inflictor = Inflictor
					end
				end
				local DamageMultiplier = rm.RagdollDamageMultiplier:GetFloat()
				if Ragdoll then
					if not IsValid(Attacker) then
						DamageMultiplier = DamageMultiplier / math.Rand(7.5, 25)
					elseif Inflictor:IsPlayer() or Inflictor.rm_IsRagdoll then
						DamageMultiplier = DamageMultiplier / math.Rand(75, 250)
					end
				end
				if Ply then
					if GetConVar("sbox_godmode"):GetBool() or (Attacker:IsPlayer() and Attacker ~= Ply and (not rm.RagdollDamagePVPEnabled:GetBool() or not GetConVar("sbox_playershurtplayers"):GetBool())) then
						DamageMultiplier = 0
					elseif not Ragdoll then
						DamageMultiplier = 1
						if (rm.RagdolizeOnDamageEnabled:GetBool() and Amount >= rm.RagdolizeOnDamageValue:GetFloat()) or (rm.RagdolizeOnFallEnabled:GetBool() and Info:IsFallDamage()) then
							if Info:IsExplosionDamage() then
								Ply.rm_RecoveryTimer = rm.RagdollRecoveryDelayOnExplosion:GetFloat()
							elseif Attacker:IsPlayer() or Attacker:IsNPC() then
								Ply.rm_RecoveryTimer = rm.RagdollRecoveryDelayOnPlayer:GetFloat()
							else
								Ply.rm_RecoveryTimer = rm.RagdollRecoveryDelayDefault:GetFloat()
							end
							Ragdoll = rm.PlayerRagdolize(Ply)
						end
					end
				end
				Amount = Amount * DamageMultiplier
				if Ply and Ply.rm_Alive then
					if rm.RagdollDamageEnabled:GetBool() and ((not Vehicle and Ragdoll) or (Vehicle and Vehicle:GetClass() == "prop_vehicle_prisoner_pod")) then
						Ply:SetHealth(math.max(Ply:Health() - Amount, 0))
					end
					if Ply:Health() <= 0 then
						local _, TargetIndex = nil, nil
						if Ragdoll then
							_, TargetIndex = rm.RagdollClosestBone(Ragdoll, Info:GetDamagePosition())
						else
							TargetIndex = rm.ModelClosestBone(Ply, Info:GetDamagePosition())
							TargetIndex = Ent:TranslateBoneToPhysBone(TargetIndex)
						end
						if rm.WeaponDropOnDeathEnabled:GetBool() then
							rm.PlayerDropActiveWeapon(Ply, false)
						end
						Ply:Kill()
						if not Ragdoll then
							Ragdoll = IsValid(Ply.rm_Ragdoll) and Ply.rm_Ragdoll or nil
						end
						if Ragdoll then
							if Inflictor:GetClass() == "entityflame" then
								Ragdoll:Ignite(math.Rand(120, 240))
							end
						end
					elseif not Ply.rm_IsUnderwater and Amount > math.Rand(0.5, 5) then
						rm.PlayerPlaySound(Ply, "Pain")
					end
				end
				if Inflictor:GetClass() == "entityflame" then
					if Ragdoll and Ply and Ply.rm_Alive then
						rm.PlayerPlaySound(Ply, "PlayerBurn")
						rm.RagdollTwitch(Ragdoll, 125)
					end
					if not (Ragdoll or Ply):IsOnFire() and math.random(1, 10) == 1 then
						(Ragdoll or Ply):Ignite(math.Rand(30, 60))
					end
				end
				if Ragdoll and Amount > 0 then
					if Info:IsExplosionDamage() and rm.RagdollBurnOnExplosionEnabled:GetBool() and math.random(1, math.max(rm.RagdollBurnOnExplosionValue:GetFloat(), 1)) == 1 then
						Ragdoll:Ignite(math.Rand(30, 120))
					end
					if rm.RagdollBloodEnabled:GetBool() and Amount > math.Rand(0, 3) then
						local Pos = Info:GetDamagePosition()
						local Normal = Info:GetDamageForce():GetNormalized()
						if Amount >= math.Rand(8, 35) then
							rm.PlaySound(Ragdoll, "FleshSquish")
							util.Decal("Blood", Pos - (Normal * 2), Pos + (Normal * 4))
							util.Decal("Blood", Pos + (Normal * 10), Pos - (Normal * 20))
						end
						local Blood = EffectData()
						Blood:SetOrigin(Pos + Normal * -3)
						Blood:SetNormal(Normal)
						util.Effect("BloodImpact", Blood)
						if Amount >= math.Rand(5, 50) then
							local Blood = EffectData()
							Blood:SetOrigin(Pos + Normal * 13)
							Blood:SetNormal(-Normal)
							util.Effect("BloodImpact", Blood)
						end
						if math.random(1, 3) == 1 or Amount >= math.Rand(50, 75) then
							local Bone = rm.RagdollClosestBone(Ragdoll, Info:GetDamagePosition())
							local Offset = Bone:GetPos() - Pos
							for i = 1, math.max(math.floor(math.Rand(1, 3) * Amount / 10), 1) do
								timer.Simple(i * math.Rand(0.3, 0.5), function()
									if IsValid(Bone) then
										local Blood = EffectData()
										Blood:SetOrigin(Bone:LocalToWorld(Offset))
										Blood:SetNormal(VectorRand())
										util.Effect("BloodImpact", Blood)
									end
								end)
							end
						end
						if math.random(1, 15) == 1 then
							local Trace = util.TraceLine(
								{
									start = Pos,
									endpos = Pos + Vector(0, 0, 50),
									filter = {Ragdoll, Ply},
									mask = MASK_SOLID
								}
							)
							if Trace.HitWorld and Trace.HitNormal.z < -0.8 then
								local BloodDrip = EffectData()
								BloodDrip:SetOrigin(Trace.HitPos)
								util.Effect("rm_BloodDrip", BloodDrip)
							end
						end
						if rm.WeaponCrossbowWeldEnabled:GetBool() and Inflictor:GetClass() == "crossbow_bolt" and (not Ply or (Ply and not Ply.rm_Alive)) then
							local Trace = util.TraceLine(
								{
									start = Pos,
									endpos = Pos + (Normal * 50),
									filter = {Ragdoll, Inflictor, Ragdoll.rm_Owner},
									mask = MASK_SOLID
								}
							)
							if Trace.Hit and (IsValid(Trace.Entity) or Trace.Entity:IsWorld()) then
								local Target, TargetIndex = rm.RagdollClosestBone(Ragdoll, Info:GetDamagePosition())
								if Target then
									Ragdoll:EmitSound("weapons/crossbow/bolt_skewer1.wav", 100, math.Rand(90, 110) * ((GetConVar("host_timescale"):GetFloat() + 1) / 2))
									local TracePos = Trace.HitPos + (Target:GetPos() - Info:GetDamagePosition()) + (Trace.HitNormal * 8)
									if Target:GetPos():Distance(TracePos) > 8 then
										Target:SetPos(TracePos)
									end
									if Trace.HitWorld and Target:IsMotionEnabled() then
										Target:EnableMotion(false)
									else
										constraint.Weld(Trace.Entity, Ragdoll, Trace.PhysicsBone, TargetIndex, 10000, false)
									end
								end
							end
						end
					end
					if rm.RagdollTwitchEnabled:GetBool() and rm.RagdollTwitchOnDamageEnabled:GetBool() then
						if Inflictor.rm_IsRagdoll then
							rm.RagdollTwitch(Ragdoll, math.min(Amount / math.Rand(5, 25), 100))
						else
							if Ply and Ply.rm_Alive then
								rm.RagdollTwitch(Ragdoll, math.min(Amount * 25 * rm.RagdollTwitchOnDamageMultiplier:GetFloat(), 200))
							else
								rm.RagdollTwitch(Ragdoll, math.min(Amount / math.Rand(2, 5), 100))
							end
							local Target, TargetIndex = rm.RagdollClosestBone(Ragdoll, Info:GetDamagePosition())
							if not Inflictor:IsWorld() then
								local Force = vector_origin
								local Type = rm.RagdollForceType:GetInt()
								if Type == 1 then
									Force = Info:GetDamageForce() * (Info:IsExplosionDamage() and rm.RagdollForceMultiplierExplosion:GetFloat() or rm.RagdollForceMultiplier:GetFloat())
								elseif Type == 2 then
									Force = Info:GetDamageForce():GetNormalized() * (Info:IsExplosionDamage() and (math.Rand(5, 10) * rm.RagdollForceMultiplierExplosion:GetFloat()) or (math.Rand(40, 60) * rm.RagdollForceMultiplier:GetFloat())) * math.min(Amount / 3, 500)
								end
								if Info:IsExplosionDamage() and not IsLimb and Type == 1 then
									Ragdoll:GetPhysicsObject(0):AddVelocity(Force)
								elseif Target and not Info:IsExplosionDamage() then
									Target:AddVelocity(Force)
								elseif not IsLimb then
									rm.RagdollIterateBones(Ragdoll, function(Bone)
										Bone:AddVelocity(Force)
									end)
								end
							elseif not IsLimb and Target and rm.RagdollBounceEnabled:GetBool() and TargetIndex ~= 0 and TargetIndex ~= 1 then
								local Velocity = Target:GetVelocity()
								Target:AddVelocity((Vector(-Velocity.x, -Velocity.y, -Velocity.z / math.Rand(1.5, 3)) / math.Rand(25, 40) + (Vector(0, 0, Target:GetVelocity():Length() * math.Rand(1, 1.5) * math.min(Amount / math.Rand(3, 5), 40)))) * rm.RagdollBounceMultiplier:GetFloat())
							end
						end
					end
					if not Ply and Ragdoll:IsOnFire() and rm.RagdollBurnEnabled:GetBool() then
						local RagdollColor = Ragdoll:GetColor()
						local r, g, b = RagdollColor.r, RagdollColor.g, RagdollColor.b
						if r <= 40 then
							r = 40
						else
							r = r - 2
						end
						if g <= 40 then
							g = 40
						else
							g = g - 2
						end
						if b <= 40 then
							b = 40
						else
							b = b - 2
						end
						Ragdoll:SetColor(Color(r, g, b))
					end
					if (not Ply or (Ply and not Ply.rm_Alive)) then
						if Inflictor:GetClass() == "env_entity_dissolver" or Inflictor:GetClass() == "prop_combine_ball" or Inflictor:GetClass() == "hunter_flechette" then
							if Ply then
								Ply:Extinguish()
								rm.PlayerRemoveRagdollVariables(Ply)
							end
							rm.RagdollRemove(Ragdoll, 3)
							Ragdoll:SetGravity(0)
							rm.RagdollIterateBones(Ragdoll, function(Bone)
								Bone:SetVelocity((Info:GetDamageForce() * math.Rand(0, 0.01)) + Vector(0, 0, math.Rand(0, 50)))
								Bone:EnableGravity(false)
								Bone:EnableCollisions(false)
								Bone:EnableDrag(false)
								Bone:SetMass(1)
							end)
							if Inflictor:GetClass() ~= "env_entity_dissolver" then
								local Dissolver = ents.Create("env_entity_dissolver")
								Dissolver.Target = "rm_Dissolver" ..Dissolver:EntIndex()
								Dissolver:SetKeyValue("DissolveType", 0)
								Dissolver:SetKeyValue("Magnitude", 100)
								Dissolver:SetPos(Ragdoll:GetPos())
								Dissolver:Spawn()
								Ragdoll:SetName(Dissolver.Target)
								Dissolver:Fire("Dissolve", Dissolver.Target)
								Dissolver:Remove()
							end
						end
						if not IsLimb and Inflictor:GetClass() ~= "crossbow_bolt" and Inflictor:GetClass() ~= "weapon_pistol" then
							if (Amount >= rm.RagdollDecapitationValue:GetFloat() and rm.RagdollDecapitationEnabled:GetBool()) or (Amount >= rm.RagdollGibValue:GetFloat() and rm.RagdollGibEnabled:GetBool()) then
								local Gib = Amount >= rm.RagdollGibValue:GetFloat()
								for x = 1, (Info:IsExplosionDamage() and math.ceil(Amount / (Gib and math.Rand(5, 15) or math.Rand(3, 9))) or 1) do
									if not IsValid(Ragdoll) or not Ragdoll.rm_IsRagdoll then
										break
									end
									local Target, TargetIndex, TargetChild, TargetChildIndex = rm.RagdollClosestBone(Ragdoll, Info:GetDamagePosition(), true)
									local ForceDecapitation = true
									for i = 1, Ragdoll:GetPhysicsObjectCount() do
										if not Ragdoll["rm_DecapitatedBone" ..i] then
											ForceDecapitation = false
											break
										end
									end
									if not Target or ForceDecapitation then
										rm.PlaySound(Ragdoll, "FleshBreak")
										if Gib then
											if rm.RagdollBloodEnabled:GetBool() then
												local Effect = EffectData()
												Effect:SetOrigin(Ragdoll:GetPos())
												Effect:SetNormal(Info:GetDamageForce():GetNormalized())
												util.Effect("rm_TorsoGib", Effect)
												for i = 1, math.random(6, 8) do
													local Spurt = EffectData()
													Spurt:SetOrigin(Ragdoll:GetPos() + (VectorRand() * 15))
													Spurt:SetScale(math.Rand(8, 10))
													Spurt:SetNormal(Info:GetDamageForce():GetNormalized() + (VectorRand():GetNormalized() / 10))
													Spurt:SetMagnitude(math.Rand(75, 250))
													util.Effect("rm_BloodSpurt", Spurt)
												end
											end
											Ragdoll:Remove()
											break
										end
									elseif not Ragdoll["rm_DecapitatedBone" ..TargetIndex] and (not IsValid(TargetChild) or Ragdoll["rm_DecapitatedBone" ..TargetChildIndex]) and Target:GetPos():Distance(Info:GetDamagePosition()) < (Info:IsExplosionDamage() and math.Rand(100, 300) or math.Rand(20, 30)) then
										rm.PlaySound(Ragdoll, "FleshBreak")
										Ragdoll["rm_DecapitatedBone" ..TargetIndex] = true
										Ragdoll:SetNetworkedBool("rm_DecapitatedBone" ..TargetIndex, true)
										rm.RagdollHideChildBones(Ragdoll, Ragdoll:TranslatePhysBoneToBone(TargetIndex))
										Target:EnableMotion(true)
										Target:EnableGravity(false)
										Target:EnableCollisions(false)
										Target:EnableDrag(false)
										Target:SetMass(1)
										if rm.RagdollBloodEnabled:GetBool() then
											local ModelBone = Ragdoll:TranslatePhysBoneToBone(TargetIndex)
											local Effect = EffectData()
											Effect:SetOrigin(Target:GetPos() + Target:GetMassCenter())
											Effect:SetNormal(Info:GetDamageForce():GetNormalized())
											if Gib then
												if ModelBone == Ragdoll:LookupBone("ValveBiped.Bip01_Head1") or ModelBone == Ragdoll:LookupBone("head") or ModelBone == Ragdoll:LookupBone("eyes") then
													util.Effect("rm_HeadGib", Effect)
												else
													util.Effect("rm_LimbGib", Effect)
												end
											else
												util.Effect("rm_LimbDecapitation", Effect)
											end
											local Spurt = EffectData()
											Spurt:SetEntity(Ragdoll)
											Spurt:SetAttachment(TargetIndex)
											if ModelBone == Ragdoll:LookupBone("ValveBiped.Bip01_Head1") or ModelBone == Ragdoll:LookupBone("head") or ModelBone == Ragdoll:LookupBone("eyes") then
												Spurt:SetScale(Gib and 5 or 3)
												Spurt:SetMagnitude(Gib and math.Rand(110, 130) or math.Rand(75, 90))
											else
												Spurt:SetScale(Gib and 3 or 2)
												Spurt:SetMagnitude(math.Rand(50, 90) or math.Rand(25, 50))
											end
											util.Effect("rm_BloodSpurt", Spurt)
										end
										if not Gib then
											local Limb = ents.Create("prop_ragdoll")
											Limb:SetModel(Ragdoll:GetModel())
											Limb:SetPos(Ragdoll:GetPos())
											Limb:SetAngles(Ragdoll:GetAngles())
											Limb:SetSkin(Ragdoll:GetSkin())
											Limb:SetMaterial(Ragdoll:GetMaterial())
											Limb:SetColor(Ragdoll:GetColor())
											Limb:SetPhysicsAttacker(Ply)
											Limb.rm_Owner = Ply
											Limb.rm_IsRagdoll = true
											Limb:SetNetworkedBool("rm_IsRagdoll", true)
											Limb.rm_IsLimb = true
											Limb:SetNetworkedBool("rm_IsLimb", true)
											Limb.rm_LimbIndex = TargetIndex
											Limb:SetNetworkedInt("rm_LimbIndex", TargetIndex)
											Limb.rm_IsUnderwater = Ragdoll.rm_IsUnderwater or false
											Limb:Spawn()
											table.insert(rm.Ragdolls, Limb)
											rm.RagdollIterateBones(Limb, function(Bone, i)
												local RagdollBone = Ragdoll:GetPhysicsObjectNum(i)
												Bone:SetPos(RagdollBone:GetPos())
												Bone:SetAngles(RagdollBone:GetAngles())
												Bone:SetVelocity(RagdollBone:GetVelocity())
												if i ~= TargetIndex then
													Bone:EnableGravity(false)
													Bone:EnableCollisions(false)
													Bone:EnableDrag(false)
													Bone:SetMass(Bone:GetMass() / 10)
												else
													Bone:SetMass(Bone:GetMass() * 5)
												end
											end)
											if Ragdoll:IsOnFire() then
												Limb:Ignite(math.Rand(0, 30))
											end
											rm.ModelIterateBones(Limb, function(i)
												local BoneIndex = Limb:TranslateBoneToPhysBone(i)
												if BoneIndex ~= TargetIndex then
													Limb:ManipulateBoneScale(i, vector_origin)
													Limb:ManipulateBonePosition(i, vector_origin)
												end
											end)
											timer.Simple(math.Rand(30, 60), function()
												if IsValid(Limb) then
													rm.RagdollRemove(Limb)
												end
											end)
										end
									end
								end
							end
						elseif IsLimb and rm.RagdollGibEnabled:GetBool() and Amount >= rm.RagdollGibValue:GetFloat() then
							rm.PlaySound(Ragdoll, "FleshBreak")
							if rm.RagdollBloodEnabled:GetBool() then
								local Effect = EffectData()
								Effect:SetOrigin(Info:GetDamagePosition())
								Effect:SetNormal(Info:GetDamageForce():GetNormalized())
								util.Effect("rm_LimbGib", Effect)
							end
							Ragdoll:Remove()
						end
					end
				elseif Amount == 0 and Inflictor:GetClass() == "prop_combine_ball" then
					Inflictor:Fire("Explode")
				end
			end
		end
	end
end)
hook.Add("PlayerSpawn", "rm_sv_PlayerSpawn", rm.PlayerSpawn)
hook.Add("CanPlayerSuicide", "rm_sv_PlayerSuicide", function(Ply)
	if rm.Enabled:GetBool() and rm.WeaponDropOnSuicideEnabled:GetBool() then
		rm.PlayerDropActiveWeapon(Ply, false)
	end
end)
hook.Add("PlayerDeathSound", "rm_sv_PlayerDeathSound", function()
	return rm.Enabled:GetBool() and true or nil
end)
hook.Add("PlayerDeath", "rm_sv_PlayerDeath", function(Ply, Inflictor, Attacker)
	if rm.Enabled:GetBool() and Ply.rm_Alive then
		Ply.rm_Alive = false
		Ply.rm_WeaponPreserve = false
		Ply.DeathTime = CurTime()
		Ply.NextSpawnTime = Ply.DeathTime + rm.RespawnDelay:GetFloat()
		Ply:SetNetworkedFloat("rm_DeathTime", Ply.DeathTime)
		Ply:SetNetworkedFloat("rm_NextSpawnTime", Ply.NextSpawnTime)
		rm.PlayerPlaySound(Ply, "Death", true)
		if rm.RagdollDamageFixInfoEnabled:GetBool() then
			if not IsValid(Ply.rm_Attacker) and (Ply.rm_Attacker and not Ply.rm_Attacker:IsWorld()) then
				Ply.rm_Attacker = game.GetWorld()
				if IsValid(Attacker) then
					Ply.rm_Attacker = Attacker
				end
			end
			if not IsValid(Ply.rm_Inflictor) and (Ply.rm_Inflictor and not Ply.rm_Inflictor:IsWorld()) then
				Ply.rm_Inflictor = game.GetWorld()
				if IsValid(Inflictor) then
					Ply.rm_Inflictor = Inflictor
				end
			end
			if IsValid(Ply.rm_Attacker) then
				if Ply.rm_Attacker:IsPlayer() then
					if Ply.rm_Attacker == Ply then
						umsg.Start("PlayerKilledSelf")
						umsg.Entity(Ply)
						umsg.End()
						MsgAll(Ply:Nick().. " suicided!\n")
					else
						umsg.Start("PlayerKilledByPlayer")
						umsg.Entity(Ply)
						umsg.String(Ply.rm_Inflictor:GetClass())
						umsg.Entity(Ply.rm_Attacker)
						umsg.End()
						if IsValid(Ply.rm_Inflictor) and Ply.rm_Inflictor ~= Ply then
							MsgAll(Ply.rm_Attacker:Nick().. " killed " ..Ply:Nick().. " with " ..Ply.rm_Inflictor:GetClass().. "\n")
						else
							MsgAll(Ply.rm_Attacker:Nick().. " killed " ..Ply:Nick().. "\n")
						end
						Ply.rm_Attacker.rm_Kills = Ply.rm_Attacker.rm_Kills + 1
						Ply.rm_Attacker:SetNetworkedInt("rm_Kills", Ply.rm_Attacker.rm_Kills)
					end
				elseif Ply.rm_Attacker:IsNPC() then
					umsg.Start("PlayerKilled")
					umsg.Entity(Ply)
					umsg.String(Ply.rm_Inflictor:GetClass())
					umsg.String(Ply.rm_Attacker:GetClass())
					umsg.End()
					if IsValid(Ply.rm_Inflictor) and Ply.rm_Inflictor ~= Ply then
						MsgAll(Ply.rm_Attacker:GetClass().. " killed " ..Ply:Nick().. " with " ..Ply.rm_Inflictor:GetClass().. "\n")
					else
						MsgAll(Ply.rm_Attacker:GetClass().. " killed " ..Ply:Nick().. "\n")
					end
				else
					umsg.Start("PlayerKilled")
					umsg.Entity(Ply)
					umsg.String(Ply.rm_Inflictor:GetClass())
					umsg.String(Ply.rm_Attacker:GetClass())
					umsg.End()
					MsgAll(Ply:Nick().. " was killed by " ..Ply.rm_Attacker:GetClass().. "\n")
				end
			else
				umsg.Start("PlayerKilledSelf")
				umsg.Entity(Ply)
				umsg.End()
				Ply:AddFrags(1)
				MsgAll(Ply:Nick() .. " died!\n")
			end
		end
		if IsValid(Ply.rm_Attacker) and (Ply.rm_Attacker:IsPlayer() or Ply.rm_Attacker:IsNPC()) and Ply.rm_Attacker ~= Ply then
			Ply:SetNetworkedEntity("rm_Killer", Ply.rm_Attacker)
		end
		if rm.RagdolizeOnDeathEnabled:GetBool() then
			local Ragdoll = Ply:GetRagdollEntity()
			if IsValid(Ragdoll) then
				Ragdoll:Remove()
			end
			Ragdoll = Ply.rm_Ragdoll or rm.PlayerRagdolize(Ply, true)
			if IsValid(Ragdoll) then
				rm.RagdollDeath(Ragdoll)
			end
			for i, Item in pairs(Ply.rm_Ragdolls) do
				if not IsValid(Item) then
					table.remove(Ply.rm_Ragdolls, i)
				end
			end
			table.insert(Ply.rm_Ragdolls, Ply.rm_Ragdoll)
			if rm.RagdollKeepEnabled:GetBool() then
				if rm.RagdollKeepPlayerValue:GetInt() > 0 then
					if #Ply.rm_Ragdolls > rm.RagdollKeepPlayerValue:GetInt() then
						rm.RagdollRemove(Ply.rm_Ragdolls[1])
						table.remove(Ply.rm_Ragdolls, 1)
					end
				end
			end
		else
			rm.PlayerRemoveRagdoll(Ply)
			Ply:SetNetworkedEntity("rm_Ragdoll", Ply:GetRagdollEntity())
		end
		return rm.RagdollDamageFixInfoEnabled:GetBool() or nil
	end
end)
hook.Add("OnNPCKilled", "rm_sv_NPCDeath", function(NPC, Ent)
	if rm.Enabled:GetBool() then
		if IsValid(Ent) then
			if Ent:IsPlayer() then
				Ent.rm_Kills = Ent.rm_Kills + 1
				Ent:SetNetworkedInt("rm_Kills", Ent.rm_Kills)
				Ent:AddFrags(1)
				MsgAll(Ent:Nick().. " killed " ..NPC:GetClass() .. (IsValid(Ent:GetActiveWeapon()) and " with " ..Ent:GetActiveWeapon():GetClass() or "").. "\n")
			elseif Ent:IsNPC() then
				MsgAll(Ent:GetClass().. " killed " ..NPC:GetClass() .. (IsValid(Ent:GetActiveWeapon()) and " with " ..Ent:GetActiveWeapon():GetClass() or "").. "\n")
			else
				MsgAll(NPC:GetClass().. " was killed by " ..Ent:GetClass().. "\n")
			end
		else
			MsgAll(NPC:GetClass().. " died!\n")
		end
		if GetConVar("ai_serverragdolls"):GetBool() and rm.NPCRagdolizeOnDeathEnabled:GetBool() then
			local Ragdoll = rm.NPCRagdolize(NPC)
			if IsValid(Ragdoll) then
				rm.RagdollDeath(Ragdoll)
			end
		end
	end
end)
hook.Add("CanPlayerEnterVehicle", "rm_sv_VehicleBlock", function(Ply, Ent)
	if rm.Enabled:GetBool() and Ply.rm_Ragdoll then
		return false
	end
end)
hook.Add("PlayerLeaveVehicle", "rm_sv_PlayerLeaveVehicle", function(Ply, Ent)
	if rm.Enabled:GetBool() and rm.RagdolizeOnEjectEnabled:GetBool() and not Ply.rm_Ragdoll and not Ply.rm_ExitingVehicle then
		if Ent:GetVelocity():Length() >= rm.RagdolizeOnEjectValue:GetInt() then
			Ply.rm_RecoveryTimer = rm.RagdollRecoveryDelayOnEject:GetFloat()
			Ply.rm_ExitingVehicle = true
			local Ragdoll = rm.PlayerRagdolize(Ply)
			Ply.rm_ExitingVehicle = false
			if IsValid(Ragdoll) then
				rm.RagdollIterateBones(Ragdoll, function(Bone)
					Bone:SetVelocity((Ent:GetVelocity() * 1.2) + (VectorRand() * 10))
				end)
				rm.PlayerPlaySound(Ply, "FreeFall")
			end
		end
	end
end)
hook.Add("PlayerDisconnected", "rm_sv_PlayerDisconnected", function(Ply)
	if rm.Enabled:GetBool() then
		rm.PlayerRemoveRagdoll(Ply)
		for _, Item in pairs(ents.GetAll()) do
			if IsValid(Item) and Item.rm_IsRagdoll and Item.rm_Owner == Ply then
				rm.RagdollRemove(Item)
			end
		end
	end
end)
hook.Add("KeyPress", "rm_sv_KeyPress", function(Ply, Key)
	if rm.Enabled:GetBool() and Ply.rm_Alive then
		if Key == IN_JUMP or Key == IN_ATTACK or Key == IN_ATTACK2 then
			Ply.rm_Parachute = false
			rm.PlayerRecover(Ply)
		elseif Key == IN_FORWARD then
			Ply.rm_Move = true
		elseif Key == IN_BACK then
			Ply.rm_Twitch = true
		elseif Key == IN_RELOAD then
			Ply.rm_WeaponLowered = false
			rm.PlayerRecover(Ply, true)
		end
	end
end)
hook.Add("KeyRelease", "rm_sv_KeyRelease", function(Ply, Key)
	if rm.Enabled:GetBool() and Ply.rm_Alive then
		if Key == IN_FORWARD then
			Ply.rm_Move = false
		elseif Key == IN_BACK then
			Ply.rm_Twitch = false
		end
	end
end)
hook.Add("CanTool", "rm_sv_BlockToolGun", function(Ply, Trace, Mode)
	local Ent = Trace.Entity
	if rm.Enabled:GetBool() and IsValid(Ent) and Ent.rm_IsRagdoll then
		local Owner = Ent.rm_Owner
		if IsValid(Owner) and Owner:IsPlayer() and Owner.rm_Ragdoll == Ent then
			if not rm.RagdollToolGunEnabled:GetBool() or Mode == "remover" then
				return false
			end
			Ent.rm_Attacker = Ply
			Ent.rm_Inflictor = Ply:GetActiveWeapon()
		end
	end
end)
hook.Add("PhysgunPickup", "rm_sv_BlockPhysGun", function(Ply, Ent)
	if rm.Enabled:GetBool() and IsValid(Ent) and Ent.rm_IsRagdoll then
		local Owner = Ent.rm_Owner
		if IsValid(Owner) and Owner:IsPlayer() and Owner.rm_Ragdoll == Ent then
			if rm.RagdollPhysGunEnabled:GetBool() then
				return false
			end
			Ent.rm_Attacker = Ply
			Ent.rm_Inflictor = Ply:GetActiveWeapon()
		end
	end
end)
concommand.Add("rm_version", function(Ply, Command, Args)
	Ply:PrintMessage(HUD_PRINTCONSOLE, "RagMod 2 version " ..rm.Version.. "\n")
end)
concommand.Add("rm_ragdolize", function(Ply, Command, Args)
	if rm.Enabled:GetBool() and rm.RagdolizeOnCommandEnabled:GetBool() and IsValid(Ply) and Ply:IsPlayer() and not IsValid(Ply.rm_Ragdoll) then
		Ply.rm_RecoveryTimer = rm.RagdollRecoveryDelayDefault:GetFloat()
		rm.PlayerRagdolize(Ply)
	end
end)
concommand.Add("rm_ragdolize_target", function(Ply, Command, Args)
	if rm.Enabled:GetBool() and IsValid(Ply) and Ply:IsPlayer() and Ply:IsAdmin() then
		for _, Arg in pairs(Args) do
			if Arg ~= nil then
				for _, Ply in pairs(player.GetAll()) do
					if string.find(string.lower(Ply:Nick()), string.lower(Arg)) then
						MsgAll("[RagMod] " ..Ply:Nick().. " ragdolized " ..Ply:Nick().. ".\n")
						if IsValid(Ply.rm_Ragdoll) then
							rm.PlayerRecoverSpawn(Ply)
						else
							Ply.rm_RecoveryTimer = rm.RagdollRecoveryDelayDefault:GetFloat()
							rm.PlayerRagdolize(Ply)
						end
					end
				end
			end
		end
	end
end)
concommand.Add("rm_recover_target", function(Ply, Command, Args)
	if rm.Enabled:GetBool() and IsValid(Ply) and Ply:IsPlayer() and Ply:IsAdmin() then
		for _, Arg in pairs(Args) do
			if Arg ~= nil then
				for _, Ply in pairs(player.GetAll()) do
					if string.find(string.lower(Ply:Nick()), string.lower(Arg)) and Ply.rm_Ragdoll then
						MsgAll("[RagMod] " ..Ply:Nick().. " reset " ..Ply:Nick().. ".\n")
						rm.PlayerRecoverSpawn(Ply, false, true)
					end
				end
			end
		end
	end
end)
concommand.Add("rm_reset", function(Ply, Command, Args)
	if rm.Enabled:GetBool() and IsValid(Ply) and Ply:IsPlayer() then
		rm.PlayerRecover(Ply, true)
	end
end)
concommand.Add("rm_reset_target", function(Ply, Command, Args)
	if rm.Enabled:GetBool() and IsValid(Ply) and Ply:IsPlayer() and Ply:IsAdmin() then
		for _, Arg in pairs(Args) do
			if Arg ~= nil then
				for _, Ply in pairs(player.GetAll()) do
					if string.find(string.lower(Ply:Nick()), string.lower(Arg)) then
						MsgAll("[RagMod] " ..Ply:Nick().. " reset " ..Ply:Nick().. ".\n")
						rm.PlayerRecoverSpawn(Ply, true, true)
					end
				end
			end
		end
	end
end)
concommand.Add("rm_grab", function(Ply, Command, Args)
	if rm.Enabled:GetBool() and rm.RagdollGrabOnCommandEnabled:GetBool() and IsValid(Ply) and Ply:IsPlayer() then
		rm.PlayerGrab(Ply)
	end
end)
concommand.Add("rm_grab_target", function(Ply, Command, Args)
	if rm.Enabled:GetBool() and IsValid(Ply) and Ply:IsPlayer() and Ply:IsAdmin() then
		for _, Arg in pairs(Args) do
			if Arg ~= nil then
				for _, Ply in pairs(player.GetAll()) do
					if string.find(string.lower(Ply:Nick()), string.lower(Arg)) then
						MsgAll("[RagMod] " ..Ply:Nick().. " grabbed " ..Ply:Nick().. ".\n")
						rm.PlayerGrab(Ply)
					end
				end
			end
		end
	end
end)
concommand.Add("rm_parachute", function(Ply, Command, Args)
	if rm.Enabled:GetBool() and rm.RagdollParachuteOnCommandEnabled:GetBool() and IsValid(Ply) and Ply:IsPlayer() and Ply.rm_Alive then
		if Ply.rm_Parachute then
			Ply.rm_Parachute = false
		else
			if (function()
				if rm.RagdollParachuteOnCommandUnlimitedEnabled:GetBool() then
					return true
				elseif Ply:HasWeapon("swep_parachute") then
					return true
				elseif Ply.rm_Ragdoll then
					for _, Weapon in pairs(Ply.rm_WeaponClass) do
						if Weapon == "swep_parachute" then
							return true
						end
					end
				end
				return false
			end)() then
				rm.PlayerParachute(Ply)
			end
		end
	end
end)
concommand.Add("rm_parachute_target", function(Ply, Command, Args)
	if rm.Enabled:GetBool() and IsValid(Ply) and Ply:IsPlayer() and Ply:IsAdmin() then
		for _, Arg in pairs(Args) do
			if Arg ~= nil then
				for _, Ply in pairs(player.GetAll()) do
					if string.find(string.lower(Ply:Nick()), string.lower(Arg)) then
						MsgAll("[RagMod] " ..Ply:Nick().. " parachuted " ..Ply:Nick().. ".\n")
						if Ply.rm_Parachute then
							Ply.rm_Parachute = false
						else
							rm.PlayerParachute(Ply)
						end
					end
				end
			end
		end
	end
end)
concommand.Add("rm_lowerweapon", function(Ply, Command, Args)
	local Weapon = Ply:GetActiveWeapon()
	if rm.Enabled:GetBool() and Ply.rm_Alive and not Ply.rm_Ragdoll and IsValid(Weapon) then
		if Ply.rm_WeaponLowered then
			Ply.rm_WeaponLowered = false
		else
			Ply.rm_WeaponLowered = true
			Weapon:SetNextPrimaryFire(1000000)
			Weapon:SetNextSecondaryFire(1000000)
			umsg.Start("rm_lowerweapon")
			umsg.Entity(Weapon)
			umsg.Bool(true)
			umsg.End()
			local function Check()
				timer.Simple(FrameTime(), function()
					if IsValid(Ply) then
						if Ply.rm_Ragdoll or not Ply.rm_WeaponLowered or not IsValid(Ply:GetActiveWeapon()) or not IsValid(Weapon) or Ply:GetActiveWeapon() ~= Weapon then
							if IsValid(Weapon) then
								Weapon:SetNextPrimaryFire(0)
								Weapon:SetNextSecondaryFire(0)
								umsg.Start("rm_lowerweapon")
								umsg.Entity(Weapon)
								umsg.Bool(false)
								umsg.Bool(not (Ply:GetActiveWeapon() == Weapon))
								umsg.End()
							end
							Ply.rm_WeaponLowered = false
							return
						end
					end
					Check()
				end)
			end
			Check()
		end
	end
end)
concommand.Add("rm_holsterweapon", function(Ply, Command, Args)
	if rm.Enabled:GetBool() and Ply.rm_Alive and not Ply.rm_Ragdoll then
		local Weapon = Ply:GetActiveWeapon()
		if Ply.rm_WeaponSelected ~= "" and not IsValid(Weapon) then
			Ply:SelectWeapon(Ply.rm_WeaponSelected)
			Ply.rm_WeaponSelected = ""
			Weapon = Ply:GetActiveWeapon()
			Weapon:SendWeaponAnim(ACT_VM_DRAW)
			timer.Simple(1, function()
				if Ply:GetActiveWeapon() == Weapon then
					Weapon:SendWeaponAnim(ACT_VM_IDLE)
					Weapon:SetNextPrimaryFire(CurTime())
					Weapon:SetNextSecondaryFire(CurTime())
				end
			end)
		elseif IsValid(Weapon) then
			Weapon:SendWeaponAnim(ACT_VM_HOLSTER)
			timer.Simple(FrameTime(), function()
				if IsValid(Weapon) and Ply:GetActiveWeapon() == Weapon then
					Ply.rm_WeaponSelected = Weapon:GetClass()
					Ply:SetActiveWeapon(NULL)
					Ply:DrawViewModel(false)
				end
			end)
		end
	end
end)
concommand.Add("rm_dropammo", function(Ply, Command, Args)
	local Weapon = Ply:GetActiveWeapon()
	if rm.Enabled:GetBool() and Ply.rm_Alive and not Ply.rm_Ragdoll and IsValid(Weapon) then
		local Class = nil
		if Args[1] == "1" then
			local Primary = Weapon:GetPrimaryAmmoType()
			local Count = 0
			if Primary == 1 then
				if Ply:GetAmmoCount(Weapon:GetPrimaryAmmoType()) >= 100 then
					Count = 100
					Class = "item_ammo_ar2_large" --item_large_box_lrounds
				else
					Count = 20
					Class = "item_ammo_ar2" --item_box_lrounds
				end
			elseif Primary == 3 then
				if Ply:GetAmmoCount(Weapon:GetPrimaryAmmoType()) >= 100 then
					Count = 100
					Class = "item_ammo_pistol_large" --item_large_box_srounds
				else
					Count = 20
					Class = "item_ammo_pistol" --item_box_srounds
				end
			elseif Primary == 4 then
				if Ply:GetAmmoCount(Weapon:GetPrimaryAmmoType()) >= 225 then
					Count = 225
					Class = "item_ammo_smg1_large" --item_large_box_mrounds
				else
					Count = 45
					Class = "item_ammo_smg1" --item_box_mrounds
				end
			elseif Primary == 5 then
				if Ply:GetAmmoCount(Weapon:GetPrimaryAmmoType()) >= 20 then
					Count = 20
					Class = "item_ammo_357_large"
				else
					Count = 6
					Class = "item_ammo_357"
				end
			elseif Primary == 6 then
				Count = 6
				Class = "item_ammo_crossbow"
			elseif Primary == 7 then
				Count = 20
				Class = "item_box_buckshot"
			elseif Primary == 8 then
				Count = 1
				Class = "item_rpg_round" --item_ml_grenade
			elseif Primary == 10 then
				Count = 1
				Class = "weapon_frag"
			else
				return
			end
			if Ply:GetAmmoCount(Weapon:GetPrimaryAmmoType()) >= Count then
				Ply:RemoveAmmo(Count, Weapon:GetPrimaryAmmoType())
			else
				return
			end
		elseif Args[1] == "2" then
			local Secondary = Weapon:GetSecondaryAmmoType()
			local Count = 0
			if Secondary == 2 then
				Count = 1
				Class = "item_ammo_ar2_altfire"
			elseif Secondary == 9 then
				Count = 1
				Class = "item_ammo_smg1_grenade" --item_ar2_grenade
			else
				return
			end
			if Ply:GetAmmoCount(Weapon:GetSecondaryAmmoType()) >= Count then
				Ply:RemoveAmmo(Count, Weapon:GetSecondaryAmmoType())
			else
				return
			end
		else
			return
		end
		local Ammo = ents.Create(Class)
		Ammo:Spawn()
		local Trace = util.TraceLine(
			{
				start = Ply:EyePos(),
				endpos = Ply:EyePos() + (Ply:GetAimVector() * 150),
				filter = Ply
			}
		)
		if Trace.Hit then
			Ammo:SetPos(Trace.HitPos + Vector(0, 0, 12))
			Ammo:SetAngles(Ply:GetAngles() + Angle(0, 180, 0))
		else
			Ammo:SetPos(Ply:EyePos() + (Ply:GetAimVector() * 100))
			Ammo:SetAngles(Ply:EyeAngles())
			Ammo:GetPhysicsObject():SetVelocity(Ply:GetVelocity() + (Ply:GetAimVector() * 500))
		end
	end
end)
concommand.Add("rm_dropweapon", function(Ply, Command, Args)
	if rm.Enabled:GetBool() then
		rm.PlayerDropActiveWeapon(Ply, true)
	end
end)
for _, Ply in pairs(player.GetAll()) do
	Ply.rm_Ready = false
	rm.PlayerSpawn(Ply)
end

MsgAll("RagMod 2 " ..rm.Version.. " loaded!\n")