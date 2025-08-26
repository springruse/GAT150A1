#include "EnginePCH.h"
#include "MeshRenderer.h"
#include "Renderer/Mesh.h"

namespace claw {
	FACTORY_REGISTER(MeshRenderer);

	void MeshRenderer::Update(float dt) {
		//update stuff here
	}
	void MeshRenderer::Draw(class Renderer& renderer) {
		auto mesh = Resources().Get<Mesh>(meshName);
		if (mesh) {
			mesh->Draw(renderer, owner->m_transform);
		}
	}

}

