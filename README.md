This project is a custom game engine and game project built for educational purposes, featuring a modular engine architecture, a 2D platformer, and a legacy space game. This repository demonstrates engine design principles, component-based architecture, physics integration, rendering, and audio systems using third-party libraries like SDL3, Box2D, FMOD, and RapidJSON.

**📂 Project Structure**
Source/Engine

The core engine powering the games. Modular systems handle rendering, physics, input, audio, and more.

**Audio** 
---
Plays all audio in the game.

Handles audio sources and listeners for 2D/3D sound.

**Components** 
---
Contains reusable components for entities, such as:

Animator – manages animations

AudioSource – plays sounds tied to entities

Collider – defines collision shapes

MeshRenderer – renders 3D meshes

RigidBody – physics component

SpriteRenderer – draws 2D sprites

Tilemap – manages grid-based game worlds

**Core** 
---
Provides utility systems for the engine:

Factory – creates objects dynamically

File & Json – file I/O and JSON parsing

ErrorLogger – logs runtime errors

Random – random number generation

Serializable – serialization for saving/loading

Singleton – base class for singletons

StringHelper – string manipulation utilities

Time – timing and delta-time management

**EngineGame** 
---
Contains core game object management:

Actors – game entities

Object – base object class

Scene – handles scene management, loading, and updates

**Event** 
---
Implements an observer system:

Observers – subscribe to events

EventManager – dispatches events to listeners

**Input** 
---
Handles keyboard input and manages player actions.

**Math** 
---
Custom math utilities and classes:

Math – custom functions

Rect – rectangles for collision or UI

Transform – position, rotation, scale

Vec2 / Vec3 – 2D and 3D vector operations

**Physics** 
---
Handles physical simulation:

Collidable – objects that can collide

GamePhysics – physics world management

PhysicsBody – physics properties for entities

**Renderer** 
---
Manages on-screen rendering:

Mesh, Text, ParticleSystem

Texture, TextureAnimation

Any component that needs to be drawn

**Resource** 
---
Manages game resources:

ResourceManager – loads and stores assets (textures, sounds, meshes, etc.)

**Source/Game**
---
Contains the actual games built using the engine.

**Platformer** 
---
Core platformer gameplay:

PlayerController – handles player input and movement

EnemyController – AI logic for enemies

PickupSystem – manages collectible items

PlatformGame – main platformer game logic

Space Game (Outdated)

Legacy 2D space shooter, mostly included for reference.

**Source/ThirdParty** 
---
Third-party libraries used in the project:

SDL3 – windowing, input, and rendering

Box2D – physics simulation

FMOD/Core – audio playback

RapidJSON – JSON parsing

---

The build folder is all you need to run the game, as it has an EXE.

---

Want to setup and run?

**⚙️ Setup & Running**

Clone the repository:

git clone https://github.com/springruse/GAT150A1.git
cd GAT150A1


Open the project in your preferred IDE (Visual Studio, CLion, etc.).

Ensure dependencies in ThirdParty are correctly linked.

Build the Engine and Game projects.

Run the game executable located in the Build directory.
