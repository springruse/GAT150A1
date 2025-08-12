#include "Player.h"
#include "Engine.h"
#include "GameData.h"
#include "Rocket.h"
#include "SpaceGame.h"

void Player::Update(float dt)
{

	piMath::vec2 direction{ 1,0 };

    float rotate = 0;
	
	// rotation speed
    if (piMath::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_A))  rotate =  -1; 
    if(piMath::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_D))  rotate = +1; 

	m_transform.rotation += (rotate * rotationSpeed) * dt;

	//thrust speed
    float thrust = 0;
	if (piMath::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_W))  thrust = +1;
	if (piMath::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_S))  thrust = -1;
	// player bounds
	m_transform.position.x = piMath::Math::Wrap(m_transform.position.x, 0.0f, (float)piMath::GetEngine().GetRenderer().getWidth());
	m_transform.position.y = piMath::Math::Wrap(m_transform.position.y, 0.0f, (float)piMath::GetEngine().GetRenderer().getHeight());

	piMath::vec2 force = direction.Rotate(piMath::Math::degToRad(m_transform.rotation)) * thrust * speed;
	//velocity += force;

	auto* rb = GetComponent<piMath::RigidBody>();
	if (rb) {
		rb->velocity += force * dt;
	}

	if (force.Length() > 0) {
		piMath::Particle particle;
		particle.position = m_transform.position;
		particle.color = piMath::vec3{ 1,1,1 };
		particle.velocity = piMath::vec2{ piMath::Random::onUnitCircle() * piMath::Random::getReal(50.0f, 80.0f) };
		particle.lifeSpan = 1.0f;
		piMath::GetEngine().GetParticleSystem().AddParticle(particle);

	}
	
	// check if player fires
	fireTimer -= dt;
	if (piMath::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_E))
	{
		fireTimer = fireTime; // Reset fire timer

		piMath::GetEngine().GetAudio().playSound(*piMath::Resources().Get<piMath::AudioClip>("blaster", piMath::GetEngine().GetAudio()));

		piMath::GetEngine().GetAudio().playSound("blaster");
		piMath::Transform rocketTransform{ this->m_transform.position, this->m_transform.rotation, 1.0f };
		auto rocket = std::make_unique<Rocket>(rocketTransform); // , piMath::Resources().Get<piMath::Texture>("texture/blue_01.png", piMath::GetEngine().GetRenderer()));
		rocket->speed = 60.0f;
		rocket->lifeSpan = 1.5f;
		rocket->name = "rocket";
		rocket->tag = "player"; // Set rocket name for identification

		//components
		auto spriteRenderer = std::make_unique<piMath::SpriteRenderer>();
		spriteRenderer->textureName = "texture/missle.png"; // rocket texture
		rocket->AddComponent(std::move(spriteRenderer));

		auto rb = std::make_unique<piMath::RigidBody>();
		rocket->AddComponent(std::move(rb));

		auto collider = std::make_unique<piMath::CircleCollider2D>();
		collider->radius = 10.0f;
		rocket->AddComponent(std::move(collider));

		m_scene->AddActor(std::move(rocket));

	}

	Actor::Update(dt);

}


void Player::onCollision(Actor* other)
{

	
	if (tag != other->tag) {
		destroyed = true;
		piMath::GetEngine().GetAudio().playSound("death");
		dynamic_cast<SpaceGame*>(m_scene->GetGame())->OnPlayerDeath(); // Notify the game of player death
	}
	std::cout << other->tag << std::endl;
	
}
