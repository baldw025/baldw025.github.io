SWEP.Author					= "DarkShadow6"
SWEP.Contact				= "tehdarkshadow6@gmail.com"
SWEP.Purpose				= "Fall with style and finesse (probably)."
SWEP.Instructions			= "Use rimary attack to deploy your parachute. Forward to fly forward."

SWEP.ViewModel				= ""
SWEP.WorldModel				= ""
SWEP.AnimPrefix				= "melee"
SWEP.HoldType				= "melee"

SWEP.Category				= "RagMod"
SWEP.Spawnable				= true
SWEP.AdminSpawnable			= true

SWEP.Primary.ClipSize		= -1
SWEP.Primary.DefaultClip	= -1
SWEP.Primary.Automatic		= false
SWEP.Primary.Ammo			= "None"

SWEP.Secondary.ClipSize		= -1
SWEP.Secondary.DefaultClip	= -1
SWEP.Secondary.Automatic	= false
SWEP.Secondary.Ammo			= "None"

if SERVER then
	AddCSLuaFile("shared.lua")
	SWEP.Weight				= 4
	SWEP.AutoSwitchTo		= false
	SWEP.AutoSwitchFrom		= false
end

if CLIENT then
	SWEP.PrintName			= "Parachute"
	SWEP.Slot				= 5
	SWEP.SlotPos			= 0
	SWEP.DrawAmmo			= false
	SWEP.DrawCrosshair		= true
	SWEP.DrawWeaponInfoBox	= false
	SWEP.BounceWeaponIcon   = false
end

function SWEP:Initialize()
	self:SetWeaponHoldType(self.HoldType)
end

function SWEP:PrimaryAttack()
	local Ply = self.Owner
	if SERVER and IsValid(Ply) then
		rm.PlayerParachute(Ply)
	end
end

function SWEP:SecondaryAttack()
end

function SWEP:Reload()
end