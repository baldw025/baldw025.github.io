function EFFECT:Init(Data)
	local Pos = Data:GetOrigin()
	local Velocity = Data:GetNormal()
	local Emitter = ParticleEmitter(Pos)
	local ColorMultiplier = render.GetLightColor(Pos)
	for i = -1, math.ceil(math.random(8, 12) * rm.RagdollGibEffectMultiplier:GetFloat()) do
		local Gib = EffectData()
		Gib:SetOrigin(Pos + VectorRand())
		Gib:SetScale(math.Rand(0.6, 0.8))
		Gib:SetNormal(((Pos - Gib:GetOrigin()):GetNormalized() + (Velocity * math.Rand(0.4, 0.9))):GetNormalized())
		util.Effect("rm_Gib", Gib)
	end
	for i = 1, math.random(5, 6) do
		local Particle = Emitter:Add("effects/blood_core", Pos)
		Particle:SetColor(math.Rand(100, 160) * ColorMultiplier.r, 0, 0)
		Particle:SetStartAlpha(math.Rand(180, 200))
		Particle:SetVelocity(VectorRand() * 50)
		Particle:SetStartSize(math.Rand(5, 8))
		Particle:SetEndSize(math.Rand(30, 45))
		Particle:SetRoll(math.Rand(0, 360))
		Particle:SetRollDelta(math.Rand(-0.25, 0.25))
		Particle:SetDieTime(math.Rand(0.4, 0.6))
	end
	for i = 1, math.random(50, 75) do
		local Particle = Emitter:Add("effects/blood", Pos)
		Particle:SetColor(math.Rand(120, 170) * ColorMultiplier.r, 10, 10)
		Particle:SetStartAlpha(math.Rand(175, 190))
		Particle:SetVelocity((Velocity * math.Rand(100, 200)) + (VectorRand() * 20))
		Particle:SetGravity(Vector(0, 0, math.Rand(-30, -120)))
		Particle:SetStartSize(math.Rand(3, 6))
		Particle:SetEndSize(math.Rand(15, 20))
		Particle:SetRoll(math.Rand(0, 360))
		Particle:SetRollDelta(math.Rand(-0.35, 0.35))
		Particle:SetDieTime(math.Rand(0.75, 1.5))
	end
	for i = 1, math.random(35, 50) do
		local Particle = Emitter:Add("effects/blood_puff", Pos)
		Particle:SetColor(math.Rand(150, 200) * ColorMultiplier.r, math.Rand(45, 50) * ColorMultiplier.g, math.Rand(45, 50) * ColorMultiplier.b)
		Particle:SetStartAlpha(math.Rand(50, 100))
		Particle:SetVelocity(Velocity * math.Rand(35, 50) + VectorRand() * 20)
		Particle:SetGravity(Vector(0, 0, math.Rand(-15, -25)))
		Particle:SetStartSize(math.Rand(1, 4))
		Particle:SetEndSize(math.Rand(12, 15))
		Particle:SetRoll(math.Rand(0, 360))
		Particle:SetRollDelta(math.Rand(-0.5, 0.5))
		Particle:SetDieTime(math.Rand(0.5, 2))
	end
	Emitter:Finish()
end

function EFFECT:Think()
	return false
end

function EFFECT:Render()
end