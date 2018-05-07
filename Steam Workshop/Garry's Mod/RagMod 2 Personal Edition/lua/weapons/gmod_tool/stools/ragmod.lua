TOOL.Category		= "Poser"
TOOL.Name			= "#tool.ragmod.name"
TOOL.Command		= nil
TOOL.ConfigName		= nil

if CLIENT then
	language.Add("tool.ragmod.name", "RagMod Ragdolizer")
	language.Add("tool.ragmod.desc", "Modify RagMod ragdoll properties.")
	language.Add("tool.ragmod.0", "Left click on a ragdoll to enable RagMod effects, right click to remove them.")
end

function TOOL:LeftClick(Trace)
	if Trace.Hit then
		local Ent = Trace.Entity
		if IsValid(Ent) and Ent:GetClass() == "prop_ragdoll" and not Ent.rm_IsRagdoll then
			if CLIENT then
				return true
			elseif SERVER then
				Ent.rm_IsRagdoll = true
				Ent:SetNetworkedBool("rm_IsRagdoll", true)
				Ent.rm_Owner = Ent.rm_Owner or self.Owner
				return true
			end
		end
	end
end

function TOOL:RightClick(Trace)
	if Trace.Hit then
		local Ent = Trace.Entity
		if IsValid(Ent) and Ent:GetClass() == "prop_ragdoll" and Ent.rm_IsRagdoll and not Ent.rm_IsLimb and (not IsValid(Ent.rm_Owner) or (IsValid(Ent.rm_Owner) and not Ent.rm_Owner.rm_Ragdoll == Ent)) then
			if CLIENT then
				return true
			elseif SERVER then
				Ent.rm_IsRagdoll = false
				Ent:SetNetworkedBool("rm_IsRagdoll", false)
				return true
			end
		end
	end
end

function TOOL:Think()
end

function TOOL.BuildCPanel(Panel)
	Panel:AddControl("Header", {Text = "#Tool.RagMod.name", Description = "#Tool.RagMod.desc"})
	Panel:AddControl("Label", {Text = "#Tool.RagMod.0"})
end