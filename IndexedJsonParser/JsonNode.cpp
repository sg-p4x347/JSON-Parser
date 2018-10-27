#include "pch.h"
#include "JsonNode.h"
#include "JSON.h"


JsonNode::JsonNode(JSON * index,uint32_t position) : Position(position), m_index(index)
{
}

std::vector<JsonNode> JsonNode::ToVector()
{
	std::vector<JsonNode> nodes;
	for (auto & child : Children) {
		nodes.push_back(m_index->LoadNode(child));
	}
	return nodes;
}

std::map<std::string, JsonNode> JsonNode::ToMap()
{
	std::map<std::string, JsonNode> nodes;
	for (auto & child : Children) {
		JsonNode && propertyNode = m_index->LoadNode(child);
		nodes.insert(std::make_pair(propertyNode.ToString(), m_index->LoadNode(propertyNode.Children[0])));
	}
	return nodes;
}

bool JsonNode::IsDefined(std::string property)
{
	for (auto & child : Children) {
		if (m_index->LoadNode(child).ToString() == property)
			return true;
	}
	return false;
}

JsonNode JsonNode::operator[](const unsigned int index)
{
	return m_index->LoadNode(Children[index]);
}

JsonNode JsonNode::operator[](std::string property)
{
	for (auto & child : Children) {
		auto && node = m_index->LoadNode(child);
		if (node.ToString() == property)
			return m_index->LoadNode(node.Children[0]);
	}
	throw std::out_of_range(property + " was not found in JsonNode");
}

std::string JsonNode::ToString()
{
	uint32_t position = Position;
	char ch = m_index->m_json[position];
	std::string value;
	if (ch == '"') {
		while (m_index->m_json[++position] != '"') {
			value += m_index->m_json[position];
		}
	}
	else if (std::isalnum(m_index->m_json[position])) {
		m_index->ParsePrimitive(position);
		value = m_index->m_json.substr(Position, (position+1) - Position);
	}
	return value;
}
