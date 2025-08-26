#pragma once
#include <variant>
namespace claw {
	class Event {
	public:
		using id_t = std::string;
		using data_t = std::variant<int, float, std::string, bool, vec2, vec3>;
		id_t id;
		data_t data;

		Event(const id_t& id, const data_t& data) : 
			id{ id }, 
			data{ data } 
		{}
	};
}