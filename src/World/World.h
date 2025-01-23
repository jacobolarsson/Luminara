#pragma once

#include "../Object/Object.h"	

#include <unordered_set>
#include <memory>

class World 
{
public:
	World() = delete;

	static void Initialize();
	static void Update();

private:
	static void AddObject(std::shared_ptr<Object> obj);
	static void RemoveObject(std::shared_ptr<Object> obj);

	static std::unordered_set<std::shared_ptr<Object>> m_objects;
};