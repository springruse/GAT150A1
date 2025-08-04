#include "ParticleSystem.h"


namespace piMath {

	bool ParticleSystem::Initialize(int poolSize)
	{
		//reserve the initial size of the particle vector
		m_particles.resize(poolSize);
		return true;
	}

	void ParticleSystem::Update(float deltaTime)
	{
		for (auto& particle : m_particles) {
			if (particle.active) {
				particle.lifeSpan -= deltaTime; // Decrease the lifespan of the particle
				particle.position += particle.velocity * deltaTime; // Update the position based on velocity
				particle.previousPosition = particle.position;
				particle.active = (particle.lifeSpan > 0.0f); // Mark the particle as inactive if its lifespan is over
				
			}
		}
	}

	void ParticleSystem::Shutdown()
	{
		m_particles.clear();
		// Cleanup resources if needed
	}

	void ParticleSystem::Draw(Renderer& renderer)
	{
		for (auto& particle : m_particles) {
			if (particle.active) {
				renderer.SetColor(particle.color.r, particle.color.g, particle.color.b);
				renderer.DrawPoint(particle.position.x, particle.position.y);
			}
		}
	}

	void ParticleSystem::AddParticle(const Particle& particle)
	{
		Particle* pointerParticle = getFreeParticle();
		if (pointerParticle) {
			*pointerParticle = particle; // Copy the particle data into the free particle slot
			pointerParticle->active = true; 
		}
	}

	Particle* ParticleSystem::getFreeParticle()
	{
		for (auto& particle : m_particles) {
			if (!particle.active) {
				particle.active = true; // Mark the particle as active
				return &particle; // Return a pointer to the free particle
			}
		}
		return nullptr;
	}

}



