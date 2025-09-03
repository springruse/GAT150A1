#pragma once

namespace claw {
	template <typename t>
	struct Rect {
		t x;
		t y;
		t w;
		t h;
		
		Rect() {
			x = 0;
			y = 0;
			w = 0;
			h = 0;
		}

		Rect(t x, t y, t w, t h) {
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}

	};
	using rect = Rect<float>;
	using irect = Rect<int>;

}