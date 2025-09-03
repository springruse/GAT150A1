#pragma once

// core
#include "Core/Random.h"
#include "Core/Logger.h"
#include "Core/StringHelper.h"
#include "Core/File.h"
#include "Core/Singleton.h"
#include "Core/Time.h"
#include "Core/Json.h"
#include "Core/Factory.h"

// framework
#include "EngineGame/Actor.h"
#include "EngineGame/Game.h"
#include "EngineGame/Scene.h"
#include "EngineGame/Object.h"

// math
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Math.h"
#include "Math/Transform.h"
#include "Math/Rect.h"

// physics
#include "Physics/Collidable.h"
#include "Physics/Physics.h"
#include "Physics/PhysicsBody.h"

// events
#include "Event/Event.h"
#include "Event/EventManager.h"
#include "Event/Observer.h"

// resources
#include "Resources/Resource.h"
#include "Resources/ResourceManager.h"

// Third Party
#include <fmod.hpp>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_error.h>
#include <box2d/box2d.h>

// standard library
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <memory>
#include <cstdlib>
#include <algorithm>
#include <filesystem>

