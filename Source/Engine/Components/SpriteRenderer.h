#pragma once
#include "EngineGame/Component.h"
#include "Components/RendererComponent.h"
#include "Core/Serializable.h"

namespace claw {
		class SpriteRenderer : public RendererComponent {
		public:
			CLASS_PROTOTYPE(SpriteRenderer)
			std::string textureName;
			rect textureRect;
			res_t<Texture> texture;
			

		public:
			void Start() override;
			void Read(const json::value_t& value);
			void Update(float deltatime) override;
			void Draw(Renderer& renderer) override;
		};

}