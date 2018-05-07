function EFFECT:Init(Data)
	local Pos = Data:GetOrigin()
	local Velocity = Data:GetNormal()
	local Emitter = ParticleEmitter(Pos)
	local ColorMultiplier = render.GetLightColor(Pos)
	for i = -1, math.ceil(math.random(40, 50) * rm.RagdollGibEffectMultiplier:GetFloat()) do
		local Gib = EffectData()
		Gib:SetOrigin(Pos + (VectorRand() * 4))
		Gib:SetScale(math.Rand(0.1, 2))
		Gib:SetNormal(((Pos - Gib:GetOrigin()):GetNormalized() + (Velocity * math.Rand(3, 10)) + (VectorRand() * 3)):GetNormalized())
		util.Effect("rm_Gib", Gib)
	end
	for i = 1, math.random(25, 30) do
		local Particle = Emitter:Add("effects/blood_core", Pos + VectorRand() * 25)
		Particle:SetColor(math.Rand(100, 220) * ColorMultiplier.r, math.Rand(10, 30) * ColorMultiplier.g, math.Rand(10, 20) * ColorMultiplier.b)
		Particle:SetStartAlpha(math.Rand(180, 255))
		Particle:SetVelocity(VectorRand() * 100)
		Particle:SetStartSize(math.Rand(10, 15))
		Particle:SetEndSize(math.Rand(35, 50))
		Particle:SetRoll(math.Rand(0, 360))
		Particle:SetRollDelta(math.Rand(-0.75, 0.75))
		Particle:SetDieTime(math.Rand(0.8, 1.5))
	end
	for i = 1, math.random(75, 120) do
		local Particle = Emitter:Add("effects/blood", Pos)
		Particle:SetColor(math.Rand(190, 220) * ColorMultiplier.r, math.Rand(25, 30) * ColorMultiplier.g, math.Rand(25, 20) * ColorMultiplier.b)
		Particle:SetStartAlpha(200)
		Particle:SetVelocity(Velocity * math.Rand(50, 75) + VectorRand() * 80)
		Particle:SetGravity(Vector(0, 0, math.Rand(-35, -45)))
		Particle:SetStartSize(math.Rand(5, 9))
		Particle:SetEndSize(math.Rand(16, 20))
		Particle:SetRoll(math.Rand(0, 360))
		Particle:SetRollDelta(math.Rand(-0.5, 0.5))
		Particle:SetDieTime(math.Rand(8, 12))
		Particle:SetCollide(true)
	end
	for i = 1, math.random(100, 150) do
		local Particle = Emitter:Add("effects/blood_puff", Pos)
		Particle:SetColor(math.Rand(200, 230) * ColorMultiplier.r, math.Rand(45, 50) * ColorMultiplier.g, math.Rand(45, 50) * ColorMultiplier.b)
		Particle:SetStartAlpha(100)
		Particle:SetVelocity(Velocity * math.Rand(20, 25) + VectorRand() * 15)
		Particle:SetGravity(Vector(0, 0, math.Rand(-5, -10)))
		Particle:SetStartSize(math.Rand(1, 8))
		Particle:SetEndSize(math.Rand(15, 22))
		Particle:SetRoll(math.Rand(0, 360))
		Particle:SetRollDelta(math.Rand(-1, 1))
		Particle:SetDieTime(math.Rand(1, 4))
		Particle:SetCollide(true)
	end
	for i = 1, 8 do
		local Particle = Emitter:Add("particles/smokey", Pos + VectorRand() * 12)
		Particle:SetColor(math.Rand(120, 160) * ColorMultiplier.r, 20 * ColorMultiplier.g, 20 * ColorMultiplier.b)
		Particle:SetStartAlpha(math.Rand(100, 125))
		Particle:SetVelocity(Velocity * math.Rand(1, 5) + VectorRand() * 2)
		Particle:SetGravity(Vector(0, 0, math.Rand(-0.5, -2)))
		Particle:SetStartSize(math.Rand(5, 20))
		Particle:SetEndSize(math.Rand(50, 90))
		Particle:SetRoll(math.Rand(0, 360))
		Particle:SetRollDelta(math.Rand(-0.1, 0.1))
		Particle:SetDieTime(math.Rand(8, 21))
		Particle:SetCollide(true)
	end
	Emitter:Finish()
	for i = 1, 100 do
		util.Decal("Blood", Pos + (VectorRand() * 125), Pos + (VectorRand() * 125))
	end
end

function EFFECT:Think()
	return false
end

function EFFECT:Render()
end