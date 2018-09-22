function EFFECT:Init(Data)
	local Pos = Data:GetOrigin()
	local Velocity = Data:GetNormal()
	local Emitter = ParticleEmitter(Pos)
	local ColorMultiplier = render.GetLightColor(Pos)
	for i = -1, math.ceil(math.random(20, 30) * rm.RagdollGibEffectMultiplier:GetFloat()) do
		local Gib = EffectData()
		Gib:SetOrigin(Pos + (VectorRand() * 4))
		Gib:SetScale(math.Rand(0.7, 1))
		Gib:SetNormal(((Pos - Gib:GetOrigin()):GetNormalized() + (Velocity * math.Rand(0.7, 1.2))):GetNormalized())
		util.Effect("rm_Gib", Gib)
	end
	for i = 1, math.random(300, 400) do
		local Particle = Emitter:Add("effects/blooddrop", Pos + (VectorRand() * 5))
		Particle:SetColor(math.Rand(200, 255) * ColorMultiplier.r, 0, 0)
		Particle:SetStartAlpha(math.Rand(150, 255))
		Particle:SetVelocity(VectorRand() * 150)
		Particle:SetGravity(Vector(0, 0, math.Rand(-400, -100)))
		Particle:SetStartSize(math.Rand(0.1, 2))
		Particle:SetEndSize(0)
		Particle:SetRoll(math.Rand(0, 360))
		Particle:SetRollDelta(math.Rand(-3, 3))
		Particle:SetDieTime(math.Rand(1, 12))
		Particle:SetCollide(true)
		Particle:SetCollideCallback(function() Particle:SetDieTime(0) end)
	end
	for i = 1, math.random(15, 20) do
		local Particle = Emitter:Add("effects/blood", Pos + (VectorRand() * 12))
		Particle:SetColor(math.Rand(200, 255) * ColorMultiplier.r, math.Rand(10, 30) * ColorMultiplier.g, math.Rand(10, 20) * ColorMultiplier.b)
		Particle:SetStartAlpha(math.Rand(100, 120))
		Particle:SetVelocity(VectorRand() * 50)
		Particle:SetGravity(Vector(0, 0, math.Rand(-60, -50)))
		Particle:SetStartSize(math.Rand(0, 10))
		Particle:SetEndSize(math.Rand(25, 75))
		Particle:SetRoll(math.Rand(0, 360))
		Particle:SetRollDelta(math.Rand(-0.75, 0.75))
		Particle:SetDieTime(math.Rand(0.1, 0.6))
	end
	for i = 1, math.random(175, 200) do
		local Particle = Emitter:Add("effects/blood", Pos)
		Particle:SetColor(math.Rand(200, 255) * ColorMultiplier.r, math.Rand(25, 30) * ColorMultiplier.g, math.Rand(25, 20) * ColorMultiplier.b)
		Particle:SetStartAlpha(200)
		Particle:SetVelocity((Velocity * math.Rand(20, 150)) + (VectorRand() * 25))
		Particle:SetGravity(Vector(0, 0, math.Rand(-65, -25)))
		Particle:SetStartSize(math.Rand(0, 5))
		Particle:SetEndSize(math.Rand(10, 15))
		Particle:SetRoll(math.Rand(0, 360))
		Particle:SetRollDelta(math.Rand(-0.6, 0.6))
		Particle:SetDieTime(math.Rand(1, 4))
		Particle:SetCollide(true)
		Particle:SetBounce(math.Rand(0.1, 0.3))
	end
	for i = 1, 3 do
		local Particle = Emitter:Add("particles/smokey", Pos + (VectorRand() * 5))
		Particle:SetColor(math.Rand(140, 170) * ColorMultiplier.r, math.Rand(0, 20) * ColorMultiplier.g, math.Rand(0, 20) * ColorMultiplier.b)
		Particle:SetStartAlpha(math.Rand(150, 200))
		Particle:SetVelocity((Velocity * math.Rand(1, 5)) + VectorRand())
		Particle:SetStartSize(math.Rand(5, 15))
		Particle:SetEndSize(math.Rand(50, 80))
		Particle:SetRoll(math.Rand(0, 360))
		Particle:SetRollDelta(math.Rand(-0.4, 0.4))
		Particle:SetDieTime(math.Rand(1, 5))
	end
	Emitter:Finish()
end

function EFFECT:Think()
	return false
end

function EFFECT:Render()
end