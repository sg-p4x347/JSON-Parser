#pragma once
#include "JsonNode.h"

class JSON
{
public:
	friend class JsonNode;
	JSON(std::string json);
	~JSON();
	JsonNode Root();
private:
	std::string m_json;
	std::map<uint32_t, JsonNode> m_index;
private:
	void AddChild(JsonNode & parent, JsonNode && child);
	JsonNode AddNode(JsonNode && node);
	JsonNode AddNode(JsonNode & node);
	JsonNode ParseBlock(uint32_t & position, char closing);
	JsonNode ParseNode(uint32_t & position);
	JsonNode ParsePrimitive(uint32_t & position);
	JsonNode LoadNode(uint32_t & position);
	void SkipBlock(uint32_t & position, char opening, char closing);
};

