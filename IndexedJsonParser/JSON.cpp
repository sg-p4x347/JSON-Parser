#include "pch.h"
#include "JSON.h"


JSON::JSON(std::string json) : m_json(json)
{
	uint32_t position = 0;
	
	// create the index
	AddNode(ParseBlock(position, '}'));
}

JSON::~JSON()
{
}

JsonNode JSON::Root()
{
	return m_index.find(0)->second;
}


void JSON::AddChild(JsonNode & parent, JsonNode && child)
{
	parent.Children.push_back(child.Position);
	//m_index[parent.Position].Children.push_back(child.Position);
}

JsonNode JSON::AddNode(JsonNode && node)
{
	return AddNode(node);
}

JsonNode JSON::AddNode(JsonNode & node)
{
	m_index.emplace(std::make_pair(node.Position, node));
	return node;
}

JsonNode JSON::ParseBlock(uint32_t & position, char closing)
{
	// create a new node
	JsonNode blockNode(this,position);
	JsonNode * property = nullptr;
	while (++position != m_json.length()) {
		char ch = m_json[position];
		if (ch == closing) {
			if (property) AddNode(*property);
			break;
		}
		// while not in a string, try to parse recursively
		else if (closing != '"') {
			switch (ch) {
			case '{': AddChild(blockNode,AddNode(ParseBlock(position, '}'))); break;
			case '[': AddChild(blockNode,AddNode(ParseBlock(position, ']'))); break;
			case '"': 
				if (property) AddNode(*property);
				property = &ParseBlock(position, '"');
				AddChild(blockNode, std::move(*property));
				break;
			case ':':
				AddChild(*property,AddNode(ParseNode(position)));
				break;
			default:
				if (std::isalnum(ch)) {
					AddChild(blockNode,AddNode(ParsePrimitive(position)));
				}
			}
		}
	}
	return blockNode;
}

JsonNode JSON::ParseNode(uint32_t & position)
{
	while (++position != m_json.length()) {
		char ch = m_json[position];
		switch (ch) {
		case '{': return ParseBlock(position, '}');
		case '[': return ParseBlock(position, ']');
		case '"': return ParseBlock(position, '"');
		default : 
			if (std::isalnum(ch)) {
				return ParsePrimitive(position);
			}
		}
	}
}

JsonNode JSON::ParsePrimitive(uint32_t & position)
{
	JsonNode primitive(this,position);
	while (++position != m_json.length() && (std::isalnum(m_json[position]) || m_json[position] == '.'));
	--position;
	return primitive;
}

JsonNode JSON::LoadNode(uint32_t & position)
{
	auto it = m_index.find(position);
	if (it != m_index.end()) {
		return it->second;
	}
	else {
		// lazy load the node

	}
}

void JSON::SkipBlock(uint32_t & position, char opening, char closing)
{
}
