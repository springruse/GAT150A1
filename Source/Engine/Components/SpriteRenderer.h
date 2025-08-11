#pragma once
#include "EngineGame/Component.h"
#include "Components/RendererComponent.h"

namespace piMath {
		class SpriteRenderer : public RendererComponent {
		public:
			std::string textureName;

		public:
			void Update(float deltatime) override;
			void Draw(Renderer& renderer) override;
		};
}