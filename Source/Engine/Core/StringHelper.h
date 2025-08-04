#pragma once
#include <string>

namespace piMath {
	inline std::string toLower(const std::string& str) {
		std::string result = str;

		for (char& c : result) {
			c = std::tolower(c);
		}

		return result;
	}

	inline std::string toUpper(const std::string& str) {
		std::string result = str;
		for (char& c : result) {
			c = std::toupper(c);
		}
		return result;
	}
}