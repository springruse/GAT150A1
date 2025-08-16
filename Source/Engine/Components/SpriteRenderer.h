#pragma once
#include "EngineGame/Component.h"
#include "Components/RendererComponent.h"

namespace claw {
		class SpriteRenderer : public RendererComponent {
		public:
			std::string textureName;

		public:
			void Update(float deltatime) override;
			void Draw(Renderer& renderer) override;
		};
}