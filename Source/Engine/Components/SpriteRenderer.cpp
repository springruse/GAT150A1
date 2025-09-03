#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"
#include "Engine.h"



namespace claw {

	FACTORY_REGISTER(SpriteRenderer)

	void SpriteRenderer::Update(float deltatime)
	{
		//
	}

	void SpriteRenderer::Draw(Renderer& renderer)
	{

		if (texture) {
			if (textureRect.w > 0 && textureRect.h > 0) {
				renderer.DrawTexture(*texture,
					textureRect,
					owner->m_transform.position.x,
					owner->m_transform.position.y,
					owner->m_transform.rotation,
					owner->m_transform.scale, 
					flipH);
			}
			else {
				renderer.DrawTexture(*texture,
					owner->m_transform.position.x,
					owner->m_transform.position.y,
					owner->m_transform.rotation,
					owner->m_transform.scale,
					flipH);
			}
		}
	}

	void SpriteRenderer::Start()
	{
		// get texture resource if texture doesn't exist and there's a texture name
		if (!texture && !textureName.empty()) {
			texture = Resources().Get<Texture>(textureName, GetEngine().GetRenderer());
		}
	}

	void SpriteRenderer::Read(const json::value_t& value)
	{
		Object::Read(value);
		JSON_READ_NAME(value, "texture_name", textureName);
		JSON_READ(value, flipH);
	}

}

