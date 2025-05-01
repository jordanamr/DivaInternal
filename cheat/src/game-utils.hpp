#pragma once

#include "global.h"

inline app::Type* GetUnityType(std::string name)
{
	auto type = app::Type_GetType_3(string_to_il2cppi(name), nullptr);
	if (type != nullptr) return type;

	auto assemblyName = name.substr(0, name.find_first_of("."));
	auto assembly = app::Assembly_LoadWithPartialName(string_to_il2cppi(assemblyName), nullptr);
	if (assembly == nullptr) return nullptr;

	return app::Assembly_GetType(assembly, string_to_il2cppi(name), false, nullptr);
}

template<typename T>
std::string GetName(T obj)
{
	return il2cppi_to_string(app::Object_1_get_name(reinterpret_cast<app::Object_1*>(obj), nullptr));
}