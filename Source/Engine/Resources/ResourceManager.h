#pragma once
#include <string>
#include <map>
#include <memory>
#include <iostream>

#include "Core/StringHelper.h"
#include "Core/Singleton.h"
#include "Resource.h"
#include "Core/Logger.h"


namespace piMath {

	class ResourceManager : public Singleton<ResourceManager> {
	public:
		template <typename T, typename ...Args>
		res_t<T> Get(const std::string& name, Args&& ... args);

		template <typename T, typename ...Args>
		res_t<T> GetWithID(const std::string& id,const std::string& name, Args&& ... args);

		static inline ResourceManager& Instance() {
			static ResourceManager instance;
			return instance;
		}

	private:
		std::map<std::string, res_t<Resource>> m_resources;
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;

	};

	template<typename T, typename ... Args>
	inline res_t<T> ResourceManager::Get(const std::string& name, Args&& ... args)
	{
		return GetWithID<T>(name, name, std::forward<Args>(args)...);

	}

	template<typename T, typename ...Args>
	inline res_t<T> ResourceManager::GetWithID(const std::string& id, const std::string& name, Args && ...args)
	{

		std::string key = toLower(id);
		auto iter = m_resources.find(key);

		if (iter != m_resources.end()) {
			auto base = iter->second;

			auto derived = std::dynamic_pointer_cast<T>(base);

			if (derived == nullptr) {
				Logger::Warning("Resource Type Mismatch: " + key);
				return res_t<T>();
			}
			return derived;
		}
		// load resource
		res_t<T> resource = std::make_shared<T>();
		if (resource->Load(name, std::forward<Args>(args)...) == false) {
			Logger::Warning("Could not load resource: " + name);
			return res_t<T>();
		}
		// add resource to resource manager
		m_resources[key] = resource;

		return resource;
	}
	
	inline ResourceManager& Resources() {
		return ResourceManager::Instance();
	}



}