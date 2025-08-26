#pragma once
#include "EngineGame/Object.h"
#include "Core/Singleton.h"
#include "Core/StringHelper.h"
#include "Core/Logger.h"
#include "EngineGame/Actor.h"
#include <map>
#include <memory>
#include <string>

#define FACTORY_REGISTER(classname) \
class Register##classname { \
    public: \
        Register##classname() { \
        claw::Factory::Instance().Register<classname>(#classname); \
    } \
}; \
Register##classname register_instance;

namespace claw {

	class CreatorBase {
	public:
		virtual ~CreatorBase() = default;
		virtual std::unique_ptr<Object> Create() = 0;
	
	};

	template <typename T>
		requires std::derived_from<T, Object>
	class Creator : public CreatorBase{
	public:
		std::unique_ptr<Object> Create() override {
			return std::make_unique<T>();
		}
	};

	template <typename T>
		requires std::derived_from<T, Object>
	class PrototypeCreator : public CreatorBase {
	public:
		PrototypeCreator(std::unique_ptr<T> prototype) :
			m_prototype{ std::move(prototype) }
		{
		}
		std::unique_ptr<Object> Create() override {
			return m_prototype->Clone();
		}

	private:
	std::unique_ptr<T> m_prototype;
	};

	// next class

	class Factory : public Singleton<Factory> {
	public:
		template<typename T>
			requires std::derived_from<T, Object>
		void Register(const std::string& name);

		template<typename T>
			requires std::derived_from<T, Object>
		void RegisterPrototype(const std::string& name, std::unique_ptr<T> prototype);

		template<typename T = Object>
			requires std::derived_from<T, Object>
		std::unique_ptr<T> Create(const std::string& name);

		void RemoveAll() { m_registry.clear(); }

	private:
		std::map<std::string, std::unique_ptr<CreatorBase>> m_registry;
	};

	template<typename T>
		requires std::derived_from<T, Object>
	inline std::unique_ptr<T> Factory::Create(const std::string& name)
	{
		//make case insensitive
		std::string key = toLower(name);

		auto iter = m_registry.find(key);
		if (iter != m_registry.end()) {
			auto object = iter->second->Create();
			T* derived = dynamic_cast<T*>(object.get());
			if (derived) {
				object.release();
				return std::unique_ptr<T>(derived);
			}
			Logger::Error("Type mismatch factory object: {}", name);
		}
		else {
			Logger::Error("Couldn't create factory object: {}", name);

		}
		return nullptr;
	}

	template<typename T>
		requires std::derived_from<T, Object>
	inline void Factory::Register(const std::string& name)
	{
		//make case insensitive
		std::string key = toLower(name);
		//add creator to registry
		m_registry[key] = std::make_unique<Creator<T>>();

		Logger::Info("Registered factory object: {}", name);
	}

	template<typename T>
		requires std::derived_from<T, Object>
	inline void Factory::RegisterPrototype(const std::string& name, std::unique_ptr<T> prototype)
	{
		// make case-insensitive (lowercase)
		std::string key = toLower(name);

		// add prototype creator to registry
		m_registry[key] = std::make_unique<PrototypeCreator<T>>(std::move(prototype));

		Logger::Info("{} prototype added to factory.", name);
	}

	//instantiate with name
	template<typename T = Actor>
		requires std::derived_from<T, Actor>
	std::unique_ptr<T> Instantiate(const std::string& name) {
		return Factory::Instance().Create<T>(name);
	}

	//instantiate with name and transform info
	template<typename T = Actor>
		requires std::derived_from<T, Actor>
	std::unique_ptr<T> Instantiate(const std::string& name, const vec2& position, float rotation, float scale) {
		auto instance = Factory::Instance().Create<T>(name);
		instance->m_transform = Transform{ position, rotation, scale };
		return instance;
	}

	//instantiate with name and transform
	template<typename T = Actor>
		requires std::derived_from<T, Actor>
	std::unique_ptr<T> Instantiate(const std::string& name, const Transform& transform) {
		auto instance = Factory::Instance().Create<T>(name);
		instance->m_transform = transform;
		return instance;
	}
}
