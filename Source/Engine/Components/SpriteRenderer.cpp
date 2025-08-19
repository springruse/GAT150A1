#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"



namespace claw {

	FACTORY_REGISTER(SpriteRenderer)

	void SpriteRenderer::Update(float deltatime)
	{
		//
	}

	void SpriteRenderer::Draw(Renderer& renderer)
	{
		auto texture = Resources().Get<Texture>(textureName, renderer);

		if (texture) {
				renderer.DrawTexture(*texture, 
				owner->m_transform.position.x, 
				owner->m_transform.position.y, 
				owner->m_transform.scale, 
				owner->m_transform.rotation);
		}
	}

	void SpriteRenderer::Read(const json::value_t& value)
	{
		Object::Read(value);
		JSON_READ(value, textureName);
	}

}

