#pragma once
#include <string>

namespace claw {
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

	inline bool EqualsIgnoreCase(const std::string& str1, const std::string& str2) {
		if (str1.length() != str2.length()) {
			return false;
		}

		return std::equal(str1.begin(), str1.end(), str2.begin(), [](char a, char b) {
			return (std::tolower(a) == std::tolower(b));
		});
	}
}