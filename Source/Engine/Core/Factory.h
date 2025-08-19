#pragma once
#include "EngineGame/Object.h"
#include "Core/Singleton.h"
#include "Core/StringHelper.h"
#include "Core/Logger.h"
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

	// next class

	class Factory : public Singleton<Factory> {
	public:
		template <typename T>
			requires std::derived_from<T, Object>
		void Register(const std::string& name);

		template <typename T = Object>
			requires std::derived_from<T, Object>
		std::unique_ptr<T> Create(const std::string& name);

	private:
		std::map<std::string, std::unique_ptr<CreatorBase>> m_registry;
	};

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


}
