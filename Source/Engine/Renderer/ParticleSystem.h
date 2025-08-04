#pragma once
#include "../Renderer/Renderer.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include <vector>


namespace piMath {
	struct Particle {
		bool active = false;

		vec2 previousPosition;
		vec2 position;
		vec2 velocity;
		vec3 color;

		float lifeSpan = 1.0f;
	};

	class ParticleSystem {
	public:
			ParticleSystem() = default;
			bool Initialize(int poolSize = 1000);
			void Shutdown();

			void Update(float dt);

			void Draw(class Renderer& renderer);

			void AddParticle(const Particle& particle);
	private:
		std::vector<Particle> m_particles;

	private:
		Particle* getFreeParticle();
	};
}