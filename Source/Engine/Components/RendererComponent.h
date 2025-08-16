#pragma once

#include "EngineGame/Component.h"

namespace claw {
	class RendererComponent : public Component {
	public:
		virtual void Draw(class Renderer& renderer) = 0;
	};
}