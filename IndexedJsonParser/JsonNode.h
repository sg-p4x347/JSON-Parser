#pragma once
#include "pch.h"
class JSON;
class JsonNode
{
public:
	friend class JSON;
	JsonNode(JSON * index, uint32_t position);
	
	std::vector<JsonNode> ToVector();
	std::map<std::string, JsonNode> ToMap();
	template<typename Type>
	inline Type To() {
		std::stringstream ss(ToString());
		Type value = Type();
		ss >> std::boolalpha >> value;
		return value;
	}
	bool IsDefined(std::string property);
	JsonNode operator[](const unsigned int index);
	JsonNode operator[](std::string property);
	std::string ToString();
private:
	uint32_t Position;
	std::vector<uint32_t> Children;
	JSON * m_index;
	
};

