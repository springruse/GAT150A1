#pragma once

namespace claw {
	class ICollidable {
	public:
		virtual ~ICollidable() = default;
		virtual void OnCollision(class Actor* other) = 0;
	};
}
	