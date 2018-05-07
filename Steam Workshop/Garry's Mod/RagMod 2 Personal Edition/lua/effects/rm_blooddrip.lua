function EFFECT:Init(Data)
	self.Particles = 0
	self.Pos = Data:GetOrigin()
	self.Emitter = ParticleEmitter(self.Pos)
	util.Decal("Blood", self.Pos, self.Pos + Data:GetNormal() * 2)
end

function EFFECT:Think()
	if self.Particles < math.random(50, 350) then
		if math.random(1, 15) == 1 then
			self.Particles = self.Particles + 1
			local ColorMultiplier = render.GetLightColor(self.Pos)
			local Particle = self.Emitter:Add("effects/blooddrop", self.Pos + Vector(math.Rand(-20, 20), math.Rand(-20, 20), -0.1))
			Particle:SetColor(127.5 * ColorMultiplier.r, 0, 0)
			Particle:SetStartAlpha(220)
			Particle:SetGravity(Vector(0, 0, math.Rand(-400, -100)))
			Particle:SetStartSize(math.Rand(1, 3))
			Particle:SetEndSize(0.5)
			Particle:SetDieTime(math.Rand(3, 20))
			Particle:SetCollide(true)
			Particle:SetCollideCallback(function()
				sound.Play("ambient/water/rain_drip" ..tostring(math.random(1, 4)).. ".wav", Particle:GetPos(), math.Rand(40, 75), math.Rand(150, 250), math.Rand(0.2, 0.6))
				if math.random(1, 20) == 1 then
					util.Decal("Blood", Particle:GetPos(), Particle:GetPos() + Vector(0, 0, -1))
				end
				Particle:SetDieTime(0)
			end)
		end
		return true
	else
		if self.Emitter then
			self.Emitter:Finish()
		end
		return false
	end
end

function EFFECT:Render()
end