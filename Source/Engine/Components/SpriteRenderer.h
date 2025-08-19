#pragma once
#include "EngineGame/Component.h"
#include "Components/RendererComponent.h"
#include "Core/Serializable.h"

namespace claw {
		class SpriteRenderer : public RendererComponent {
		public:
			std::string textureName;
			void Read(const json::value_t& value);

		public:
			void Update(float deltatime) override;
			void Draw(Renderer& renderer) override;
		};

}