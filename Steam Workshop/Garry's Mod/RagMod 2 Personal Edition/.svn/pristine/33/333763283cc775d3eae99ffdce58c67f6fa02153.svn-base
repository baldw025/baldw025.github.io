function EFFECT:Init(Data)
	local Pos = Data:GetOrigin()
	local Velocity = Data:GetNormal()
	local Emitter = ParticleEmitter(Pos)
	local ColorMultiplier = render.GetLightColor(Pos)
	for i = 1, math.random(2, 4) do
		local Particle = Emitter:Add("effects/blood_core", Pos)
		Particle:SetColor(math.Rand(90, 150) * ColorMultiplier.r, 0, 0)
		Particle:SetStartAlpha(math.Rand(200, 240))
		Particle:SetVelocity(VectorRand() * 30)
		Particle:SetStartSize(math.Rand(4, 6))
		Particle:SetEndSize(math.Rand(15, 25))
		Particle:SetRoll(math.Rand(0, 360))
		Particle:SetRollDelta(math.Rand(-0.2, 0.2))
		Particle:SetDieTime(math.Rand(0.2, 0.4))
	end
	for i = 1, math.random(15, 25) do
		local Particle = Emitter:Add("effects/blood", Pos)
		Particle:SetColor(math.Rand(100, 160) * ColorMultiplier.r, 0, 0)
		Particle:SetStartAlpha(math.Rand(190, 210))
		Particle:SetVelocity((Velocity * math.Rand(50, 150)) + (VectorRand() * 15))
		Particle:SetGravity(Vector(0, 0, math.Rand(-50, -100)))
		Particle:SetStartSize(math.Rand(1, 5))
		Particle:SetEndSize(math.Rand(10, 15))
		Particle:SetRoll(math.Rand(0, 360))
		Particle:SetRollDelta(math.Rand(-0.3, 0.3))
		Particle:SetDieTime(math.Rand(0.5, 1))
	end
	for i = 1, math.random(25, 30) do
		local Particle = Emitter:Add("effects/blood_puff", Pos)
		Particle:SetColor(math.Rand(130, 190) * ColorMultiplier.r, math.Rand(25, 30) * ColorMultiplier.g, math.Rand(25, 30) * ColorMultiplier.b)
		Particle:SetStartAlpha(math.Rand(80, 150))
		Particle:SetVelocity((Velocity * math.Rand(25, 30)) + (VectorRand() * 15))
		Particle:SetGravity(Vector(0, 0, math.Rand(-20, -35)))
		Particle:SetStartSize(math.Rand(1, 2))
		Particle:SetEndSize(math.Rand(5, 12))
		Particle:SetRoll(math.Rand(0, 360))
		Particle:SetRollDelta(math.Rand(-0.4, 0.4))
		Particle:SetDieTime(math.Rand(0.25, 1.25))
	end
	Emitter:Finish()
end

function EFFECT:Think()
	return false
end

function EFFECT:Render()
end