local BloodMaterial = Material("effects/bloodstream")

function EFFECT:Init(Data)
	if not rm.RagdollBloodSpurtEnabled:GetBool() then
		self:Remove()
		return
	end
	self.Source = Data:GetEntity()
	self.SourceIsValid = IsValid(self.Source)
	self.Attachment = Data:GetAttachment()
	self.ParentAttachment = self.SourceIsValid and self.Source:TranslateBoneToPhysBone(self.Source:GetBoneParent(self.Source:TranslatePhysBoneToBone(self.Attachment))) or -1
	self.Pos = Data:GetOrigin()
	self.Velocity = Data:GetNormal()
	self.Magnitude = Data:GetMagnitude()
	self.Scale = Data:GetScale()
	self.Particles = {}
	self.ParticlesMax = self.SourceIsValid and math.random(2000, 3000) or self.Magnitude
	self.Emitter = ParticleEmitter(self.SourceIsValid and self.Source:GetPos() or self.Pos)
end

function EFFECT:Think()
	if #self.Particles < self.ParticlesMax then
		local Pos, Velocity = nil, nil
		if IsValid(self.Source) then
			local Bone = self.Source:GetPhysicsObjectNum(self.Attachment)
			if self.ParentAttachment ~= -1 and self.ParentAttachment ~= self.Attachment then
				local ParentBone = self.Source:GetPhysicsObjectNum(self.ParentAttachment)
				if IsValid(ParentBone) then
					Velocity = ParentBone:GetAngles():Forward()
					Pos = Bone:GetPos() + (ParentBone:GetAngles():Forward() * -2.5)
				else
					self.CanDestroy = true
				end
			elseif Bone then
				Velocity = Bone:GetAngles():Forward()
				Pos = Bone:GetPos() + (Bone:GetAngles():Forward() * -1.5)
			else
				self.CanDestroy = true
			end
		elseif not self.SourceIsValid then
			Pos = self.Pos
			Velocity = self.Velocity
		else
			self.CanDestroy = true
		end
		if Pos and Velocity then
			self:SetPos(Pos)
			local Percent = 1 - #self.Particles / self.ParticlesMax
			local ColorMultiplier = render.GetLightColor(Pos)
			for i = 1, math.random(20, 25) do
				local Particle = self.Emitter:Add("effects/blood_core", Pos + VectorRand())
				Particle:SetColor(math.Rand(110, 120) * ColorMultiplier.r, math.Rand(15, 20) * ColorMultiplier.g, math.Rand(15, 20) * ColorMultiplier.b)
				Particle:SetStartAlpha(50)
				Particle:SetVelocity(VectorRand() * self.Magnitude * math.Rand(0.2, 1) * Percent)
				Particle:SetGravity(Vector(0, 0, math.Rand(-150, -300)))
				Particle:SetStartSize(2 * Percent)
				Particle:SetEndSize(math.max(self.Scale + math.Rand(-1, 20), Particle:GetStartSize()) * Percent)
				Particle:SetRoll(math.Rand(0, 360))
				Particle:SetRollDelta(math.Rand(-0.5, 0.5))
				Particle:SetDieTime(math.Rand(0.3, 0.5))
			end
			local StartTime = CurTime()
			for i = 1, math.random(40, 80) do
				local Particle = self.Emitter:Add("particles/smokey", Pos + (VectorRand() * 0.5))
				Particle.OldPos = Particle:GetPos()
				Particle.StartTime = StartTime
				Particle:SetColor(math.Rand(80, 100) * ColorMultiplier.r, 0, 0)
				Particle:SetStartAlpha(math.Rand(150, 255))
				Particle:SetVelocity((IsValid(self.Source) and self.Source:GetVelocity() or Vector()) + (((Velocity * self.Magnitude * 2) + (VectorRand() * 20)) * Percent))
				Particle:SetGravity(Vector(0, 0, math.Rand(-400, -300)))
				Particle:SetStartSize((self.Scale / math.Rand(1.9, 10)) * Percent)
				Particle:SetEndSize((self.Scale + math.Rand(-0.75, 0.75)) * Percent)
				Particle:SetRoll(math.Rand(0, 360))
				Particle:SetRollDelta(math.Rand(-0.08, 0.08))
				Particle:SetDieTime(math.Rand(0.1, 5))
				Particle:SetCollide(true)
				Particle:SetCollideCallback(function()
					local Pos = Particle:GetPos()
					local Velocity = Particle:GetVelocity()
					if math.random(1, 200) == 1 then
						sound.Play("player/footsteps/wade" ..tostring(math.random(1, 8)).. ".wav", Particle:GetPos(), math.Rand(70, 85), math.Rand(170, 250), math.Rand(0.1, 0.2))
						local Blood = EffectData()
						Blood:SetOrigin(Pos)
						Blood:SetNormal(-Velocity:GetNormalized())
						if math.random(1, 3) == 1 then
							util.Effect("BloodImpact", Blood)
							util.Decal("Blood", Pos, Pos + (Velocity:Length() > 1 and (Velocity:GetNormalized() * 10) or Vector(0, 0, -2)))
						end
					elseif math.random(1, 25) == 1 then
						sound.Play("ambient/water/rain_drip" ..tostring(math.random(1, 4)).. ".wav", Particle:GetPos(), math.Rand(65, 70), math.Rand(210, 250), math.Rand(0.01, 0.1))
						Particle:SetDieTime(0)
					end
				end)
				Particle:SetBounce(math.Rand(0.1, 0.5))
				Particle.Created = true
				table.insert(self.Particles, Particle)
			end
		end
	end
	if self.CanDestroy then
		self.Emitter:Finish()
		return false
	end
	return true
end

function EFFECT:Render()
	local Time = 1 / GetConVar("host_timescale"):GetFloat()
	local Style = rm.RagdollBloodSpurtStyle:GetInt()
	if Style > 0 and #self.Particles > 0 then
		render.SetMaterial(BloodMaterial)
		local CanDestroy = true
		local Tick = CurTime()
		for _, Particle in pairs(self.Particles) do
			if Particle.Created and Particle.StartTime + Particle:GetDieTime() > Tick then
				CanDestroy = false
				local Pos1 = Particle:GetPos()
				local Pos2 = Particle.OldPos
				local Percent = (Tick - Particle.StartTime) / Particle:GetDieTime()
				local R, G, B = Particle:GetColor()
				render.DrawBeam(
					Pos1,
					Pos1 + ((Pos2 - Pos1) * 0.75) * Time,
					(Particle:GetStartSize() * (Style == 1 and 20 or (Style == 2 and 3)) * (1 - Percent)) + (Particle:GetEndSize() * 5 * Percent),
					1,
					(Style == 1 and 1 or (Style == 2 and 0)),
					Color(R, G, B, Particle:GetStartAlpha() * (1 - Percent))
					)
				Particle.OldPos = Pos1
			end
		end
		if CanDestroy then
			self.CanDestroy = true
		end
	end
end