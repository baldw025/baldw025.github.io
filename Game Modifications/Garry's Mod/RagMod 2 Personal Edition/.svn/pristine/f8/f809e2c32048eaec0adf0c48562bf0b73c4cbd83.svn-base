function EFFECT:Init(Data)
	if not rm.RagdollGibEffectEnabled:GetBool() then
		self:Remove()
		return
	end
	local Scale = Data:GetScale()
	local Ent = self.Entity
	Ent:SetModel(rm.GibModels[math.random(1, #rm.GibModels)])
	Ent:PhysicsInit(SOLID_VPHYSICS)
	Ent:SetSolid(SOLID_VPHYSICS)
	Ent:SetMoveType(MOVETYPE_VPHYSICS)
	local PhysObj = Ent:GetPhysicsObject()
	if IsValid(PhysObj) then
		PhysObj:Wake()
		PhysObj[(PhysObj.SetAngle and "SetAngle" or "SetAngles")](PhysObj, Angle(math.Rand(0, 360), math.Rand(0, 360), math.Rand(0, 360))) -- Hotfix
		PhysObj:SetVelocity(Data:GetNormal() * math.Rand(0, 500))
		PhysObj:AddAngleVelocity(Vector(math.random(-250, 250), math.random(-250, 250), math.random(-250, 250)))
	else
		Msg("[RagMod 2] Invalid gib model \"" ..self:GetModel().. "\"!\nNote: All RagMod gib models (by default) use standard HL2 props; is HL2 installed correctly?\n")
		self:Remove()
	end
	local ScaleMatrix = Matrix()
	ScaleMatrix:Scale(VectorRand() * Scale)
	Ent:EnableMatrix("RenderMultiply", ScaleMatrix)
	Ent:SetCollisionGroup(COLLISION_GROUP_DEBRIS)
	Ent:SetCollisionBounds(Vector(-20, -20 -20) * Scale, Vector(20, 20, 20) * Scale)
	Ent:SetMaterial("models/flesh")
	PhysObj:SetMaterial("bloodyflesh")
	Ent.Emitter = ParticleEmitter(Ent:GetPos())
	self.DieTime = CurTime() + math.Rand(5, 20)
	self.FadeTimer = math.pi / 2
	self.Ready = true
end

function EFFECT:Think()
	if IsValid(self) and self.Ready then
		if not IsValid(self.Entity) or not IsValid(self.Entity:GetPhysicsObject()) or self:GetPos() == Vector() then
			return false
		end
		local Pos = self:GetPos()
		local Velocity = self:GetVelocity()
		if Velocity:Length() > math.Rand(30, 100) and math.Rand(1, 3) == 1 then
			local Blood = EffectData()
			Blood:SetOrigin(Pos)
			Blood:SetNormal(-Velocity:GetNormalized())
			util.Effect("BloodImpact", Blood)
			util.Decal("Blood", Pos, Pos + Velocity)
		end
		if self.DieTime < CurTime() then
			self.FadeTimer = self.FadeTimer - 0.05
			self:SetModelScale(math.sin(self.FadeTimer), 0)
			if self.FadeTimer <= 0 then
				return false
			end
		end
	end
	return true
end

function EFFECT:Render()
	self.Entity:DrawModel()
end