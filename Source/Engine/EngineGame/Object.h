#pragma once

namespace claw {
	class Object {
	public:
		std::string name;
		bool active = true;

	public:
		Object() = default;
		virtual ~Object() = default;

	private:

	};

}