#pragma once
#include "EngineGame/Component.h"
#include "Components/RendererComponent.h"
#include "Core/Serializable.h"


namespace claw {
	class MeshRenderer : public RendererComponent {
	public:
		std::string meshName;

	public:
		CLASS_PROTOTYPE(MeshRenderer)

		void Update(float dt);
		void Draw(class Renderer& renderer);
	};
}