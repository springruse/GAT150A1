#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"
namespace claw {
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
}

