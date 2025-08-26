#include "Observer.h"

namespace claw {

	IObserver::~IObserver() {
		OBSERVER_REMOVE_SELF;
	};

}