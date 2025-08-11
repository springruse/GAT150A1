#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"
namespace piMath {
	void SpriteRenderer::Update(float deltatime)
	{
		//
	}

	void SpriteRenderer::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(Resources().Get<Texture>(textureName, renderer).get(), 
			owner->m_transform.position.x,
			owner->m_transform.position.y,
			owner->m_transform.scale,
			owner->m_transform.rotation
		);
	}
}

