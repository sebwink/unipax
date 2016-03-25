#ifndef GRAPHMLGRAPHWRITER_H_
#define GRAPHMLGRAPHWRITER_H_

#include <iostream>
#include <fstream>
#include <sstream>

#include <algorithm>

#include <vector>
#include <functional>

#include <lemon/core.h>
#include <lemon/maps.h>

#include <lemon/concept_check.h>
#include <lemon/concepts/maps.h>

#include <lemon/lgf_writer.h>

#include <typeinfo>

namespace lemon
{

template <typename _Item>
class TypedMapStorageBase {
public:
	typedef _Item Item;

public:
	TypedMapStorageBase() {}
	virtual ~TypedMapStorageBase() {}

	virtual std::string get(const Item& item) = 0;
	virtual void sort(std::vector<Item>&) = 0;

	virtual std::string valueType() = 0;
};

template <typename _Item, typename _Map, typename _Converter = _writer_bits::DefaultConverter<typename _Map::Value> >
class TypedMapStorage : public TypedMapStorageBase<_Item> {
public:
	typedef _Map Map;
	typedef _Converter Converter;
	typedef _Item Item;
	typedef typename _Map::Value MapValueType;

private:
	const Map& _map;
	Converter _converter;
	std::string type;

public:
	TypedMapStorage(const Map& map, const Converter& converter = Converter())
	: _map(map), _converter(converter)
	{
		if (typeid(MapValueType) == typeid(int) || typeid(MapValueType) == typeid(unsigned int) )
			type = "int";
		else if (typeid(MapValueType) == typeid(long) || typeid(MapValueType) == typeid(long long) || typeid(MapValueType) == typeid(unsigned long) || typeid(MapValueType) == typeid(unsigned long long))
			type = "long";
		else if (typeid(MapValueType) == typeid(std::string) || typeid(MapValueType) == typeid(char*))
			type = "string";
		else if (typeid(MapValueType) == typeid(double))
			type = "double";
		else if (typeid(MapValueType) == typeid(float))
			type = "float";
		else
			type = "unknown";
	}

	virtual ~TypedMapStorage() {}

	virtual std::string get(const Item& item) {
		return _converter(_map[item]);
	}
	virtual void sort(std::vector<Item>& items) {
		_writer_bits::MapLess<Map> less(_map);
		std::sort(items.begin(), items.end(), less);
	}

	std::string valueType() {
		return type;
	}
};

template<typename GR>
class GraphMLGraphWriter {

public:

	typedef GR Graph;

	TEMPLATE_GRAPH_TYPEDEFS(GR);

private:

	std::ostream* _os;
	bool local_os;

	const GR& _graph;

	typedef std::map<Node, std::string> NodeIndex;
	NodeIndex _node_index;
	typedef std::map<Edge, std::string> EdgeIndex;
	EdgeIndex _edge_index;

	typedef std::vector<std::pair<std::string, TypedMapStorageBase<Node>* > > NodeMaps;
	NodeMaps _node_maps;

	typedef std::vector<std::pair<std::string, TypedMapStorageBase<Edge>*> > EdgeMaps;
	EdgeMaps _edge_maps;

	typedef std::vector<std::pair<std::string, _writer_bits::ValueStorageBase*> > Attributes;
	Attributes _attributes;

public:

	/// \brief Constructor
	///
	/// Construct a undirected graph writer, which writes to the given
	/// output stream.
	GraphMLGraphWriter(const GR& graph, std::ostream& os = std::cout) :
		_os(&os),
		local_os(false),
		_graph(graph)
	{
	}

	/// \brief Constructor
	///
	/// Construct a undirected graph writer, which writes to the given
	/// output file.
	GraphMLGraphWriter(const GR& graph, const std::string& fn) :
		_os(new std::ofstream(fn.c_str())),
		local_os(true),
		_graph(graph)
	{
		if (!(*_os)) {
			delete _os;
			throw IoError("Cannot write file", fn);
		}
	}

	/// \brief Constructor
	///
	/// Construct a undirected graph writer, which writes to the given
	/// output file.
	GraphMLGraphWriter(const GR& graph, const char* fn) :
		_os(new std::ofstream(fn)),
		local_os(true),
		_graph(graph)
	{
		if (!(*_os)) {
			delete _os;
			throw IoError("Cannot write file", fn);
		}
	}

	/// \brief Destructor
	~GraphMLGraphWriter()
	{
		for (typename NodeMaps::iterator it = _node_maps.begin();
				it != _node_maps.end(); ++it) {
			delete it->second;
		}

		for (typename EdgeMaps::iterator it = _edge_maps.begin();
				it != _edge_maps.end(); ++it) {
			delete it->second;
		}

		for (typename Attributes::iterator it = _attributes.begin();
				it != _attributes.end(); ++it) {
			delete it->second;
		}

		if (local_os) {
			delete _os;
		}
	}


private:

	template<typename TGR>
	friend GraphMLGraphWriter<TGR> graphMLGraphWriter(const TGR& graph, std::ostream& os);

	template<typename TGR>
	friend GraphMLGraphWriter<TGR> graphMLGraphWriter(const TGR& graph, const std::string& fn);

	template<typename TGR>
	friend GraphMLGraphWriter<TGR> graphMLGraphWriter(const TGR& graph, const char *fn);


	GraphMLGraphWriter(GraphMLGraphWriter& other) :
		_os(other._os),
		local_os(other.local_os),
		_graph(other._graph)
	{

		other._os = 0;
		other.local_os = false;

		_node_index.swap(other._node_index);
		_edge_index.swap(other._edge_index);

		_node_maps.swap(other._node_maps);
		_edge_maps.swap(other._edge_maps);
		_attributes.swap(other._attributes);
	}

	GraphMLGraphWriter& operator=(const GraphMLGraphWriter&);

public:

	/// \name Writing Rules
	/// @{

	/// \brief Node map writing rule
	///
	/// Add a node map writing rule to the writer.
	template<typename Map>
	GraphMLGraphWriter& nodeMap(const std::string& caption, const Map& map)
	{
		checkConcept<concepts::ReadMap<Node, typename Map::Value>, Map>();
		TypedMapStorageBase<Node>* storage = new TypedMapStorage<Node, Map>(map);
		_node_maps.push_back(std::make_pair(caption, storage));
		return *this;
	}

	/// \brief Node map writing rule
	///
	/// Add a node map writing rule with specialized converter to the
	/// writer.
	template<typename Map, typename Converter>
	GraphMLGraphWriter& nodeMap(const std::string& caption, const Map& map, const Converter& converter = Converter())
	{
		checkConcept<concepts::ReadMap<Node, typename Map::Value>, Map>();
		TypedMapStorageBase<Node>* storage = new TypedMapStorage<Node, Map, Converter>(map, converter);
		_node_maps.push_back(std::make_pair(caption, storage));
		return *this;
	}

	/// \brief Edge map writing rule
	///
	/// Add an edge map writing rule to the writer.
	template<typename Map>
	GraphMLGraphWriter& edgeMap(const std::string& caption, const Map& map)
	{
		checkConcept<concepts::ReadMap<Edge, typename Map::Value>, Map>();
		TypedMapStorageBase<Edge>* storage =
				new TypedMapStorage<Edge, Map>(map);
		_edge_maps.push_back(std::make_pair(caption, storage));
		return *this;
	}

	/// \brief Edge map writing rule
	///
	/// Add an edge map writing rule with specialized converter to the
	/// writer.
	template<typename Map, typename Converter>
	GraphMLGraphWriter& edgeMap(const std::string& caption, const Map& map, const Converter& converter = Converter())
	{
		checkConcept<concepts::ReadMap<Edge, typename Map::Value>, Map>();
		TypedMapStorageBase<Edge>* storage = new TypedMapStorage<Edge, Map, Converter>(map, converter);
		_edge_maps.push_back(std::make_pair(caption, storage));
		return *this;
	}

	/// \brief Arc map writing rule
	///
	/// Add an arc map writing rule to the writer.
	template<typename Map>
	GraphMLGraphWriter& arcMap(const std::string& caption, const Map& map)
	{
		checkConcept<concepts::ReadMap<Arc, typename Map::Value>, Map>();
		TypedMapStorageBase<Edge>* forward_storage = new _writer_bits::GraphArcMapStorage<GR, true, Map>(_graph, map);
		_edge_maps.push_back(std::make_pair('+' + caption, forward_storage));
		TypedMapStorageBase<Edge>* backward_storage = new _writer_bits::GraphArcMapStorage<GR, false, Map>(_graph, map);
		_edge_maps.push_back(std::make_pair('-' + caption, backward_storage));
		return *this;
	}

	/// \brief Arc map writing rule
	///
	/// Add an arc map writing rule with specialized converter to the
	/// writer.
	template<typename Map, typename Converter>
	GraphMLGraphWriter& arcMap(const std::string& caption, const Map& map, const Converter& converter = Converter())
	{
		checkConcept<concepts::ReadMap<Arc, typename Map::Value>, Map>();
		TypedMapStorageBase<Edge>* forward_storage = new _writer_bits::GraphArcMapStorage<GR, true, Map, Converter>(_graph, map, converter);
		_edge_maps.push_back(std::make_pair('+' + caption, forward_storage));
		TypedMapStorageBase<Edge>* backward_storage = new _writer_bits::GraphArcMapStorage<GR, false, Map, Converter>(_graph, map, converter);
		_edge_maps.push_back(std::make_pair('-' + caption, backward_storage));
		return *this;
	}

	/// \brief Attribute writing rule
	///
	/// Add an attribute writing rule to the writer.
	template<typename Value>
	GraphMLGraphWriter& attribute(const std::string& caption, const Value& value)
	{
		_writer_bits::ValueStorageBase* storage = new _writer_bits::ValueStorage<Value>(value);
		_attributes.push_back(std::make_pair(caption, storage));
		return *this;
	}

	/// \brief Attribute writing rule
	///
	/// Add an attribute writing rule with specialized converter to the
	/// writer.
	template<typename Value, typename Converter>
	GraphMLGraphWriter& attribute(const std::string& caption, const Value& value, const Converter& converter = Converter())
	{
		_writer_bits::ValueStorageBase* storage = new _writer_bits::ValueStorage<Value, Converter>(value, converter);
		_attributes.push_back(std::make_pair(caption, storage));
		return *this;
	}

private:

	inline static void writeEscape(std::ostream& os, char c) {
		switch (c) {
		case '\"':
			os << "&quot;";
			return;
		case '\'':
			os << "&apos;";
			return;
		case '<':
			os << "&lt;";
			return;
		case '>':
			os << "&gt;";
			return;
		case '&':
			os << "&amp;";
			return;
		default:
			if (c < 0x20) {
				std::ios::fmtflags flags = os.flags();
				os << '\\' << std::oct << static_cast<int>(c);
				os.flags(flags);
			} else {
				os << c;
			}
			return;
		}
	}

	inline std::ostream& writeToken(std::ostream& os, const std::string& str) {
		for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
			writeEscape(os, *it);
		}

		return os;
	}

	inline bool isNumber(const std::string & str)
	{
		for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
			if ((*it >= '0' && *it <= '9') || *it == '.' || *it == ',')
				continue;
			else
				return false;
		}

		return true;
	}

	inline bool requireEscape(const std::string & str)
	{
		for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
			if ((*it >= '0' && *it <= '9') || *it == '.' || *it == ',' || (*it >= 'A' && *it <= 'Z') || (*it >= 'a' && *it <= 'z'))
				continue;
			else
				return true;
		}

		return false;
	}

	inline std::ostream& writeCData(std::ostream& os, const std::string& str) {
		if (requireEscape(str))
		{
			os << "<![CDATA[";
			os << str;
			os << "]]>";
		}
		else
			os << str;
		return os;
	}

	void writeNodes() {
		std::vector<Node> nodes;
		for (NodeIt n(_graph); n != INVALID; ++n)
		{
			nodes.push_back(n);
		}

		IdMap<GR, Node> id_map(_graph);
		_writer_bits::MapLess<IdMap<GR, Node> > id_less(id_map);
		std::sort(nodes.begin(), nodes.end(), id_less);


		for (int i = 0; i < static_cast<int>(nodes.size()); ++i)
		{
			Node n = nodes[i];

			std::ostringstream os;
			os << _graph.id(n);
			_node_index.insert(std::make_pair(n, os.str()));

			*_os << "\t\t<node id=\"";
			writeToken(*_os, os.str());

			if (_node_maps.empty())
			{
				*_os << "\"/>"  << std::endl;
			}
			else
			{
				*_os << "\">"  << std::endl;
				for (typename NodeMaps::iterator it = _node_maps.begin(); it != _node_maps.end(); ++it)
				{
					*_os << "\t\t\t<data key=";
					writeToken(*_os, it->first);
					*_os << ">";
					std::string value = it->second->get(n);
					writeCData(*_os, value);
					*_os << "</data>" << std::endl;
				}
				*_os << "\t\t</node>" << std::endl;
			}
		}
	}

	void writeEdges()
	{
		std::vector<Edge> edges;
		for (EdgeIt n(_graph); n != INVALID; ++n) {
			edges.push_back(n);
		}


		IdMap<GR, Edge> id_map(_graph);
		_writer_bits::MapLess<IdMap<GR, Edge> > id_less(id_map);
		std::sort(edges.begin(), edges.end(), id_less);

		for (int i = 0; i < static_cast<int>(edges.size()); ++i)
		{
			Edge e = edges[i];
			std::ostringstream os;
			os << _graph.id(e);
			_edge_index.insert(std::make_pair(e, os.str()));

			*_os << "\t\t<edge id=\"";
			writeToken(*_os, os.str());

			*_os << "\" source=\"";
			writeToken(*_os, _node_index.find(_graph.u(e))->second);

			*_os << "\" target=\"";
			writeToken(*_os, _node_index.find(_graph.v(e))->second);

			if (_edge_maps.empty())
			{
				*_os << "\"/>" << std::endl;
			}
			else
			{
				*_os << "\">" << std::endl;
				for (typename EdgeMaps::iterator it = _edge_maps.begin(); it != _edge_maps.end(); ++it)
				{
					*_os << "\t\t\t<data key=\"";
					writeToken(*_os, it->first);
					*_os << "\">";
					std::string value = it->second->get(e);
					writeCData(*_os, value);
					*_os << "</data>" << std::endl;
				}
				*_os << "\t\t</edge>" << std::endl;
			}
		}
	}

	void writeAttributes() {

		for (typename EdgeMaps::iterator it = _edge_maps.begin(); it != _edge_maps.end(); ++it)
		{

			std::string type = it->second->valueType();

			*_os << "\t<key id=\"";
			writeToken(*_os, it->first);
			*_os << "\" for=\"edge\" attr.name=\"";
			writeToken(*_os, it->first);
			*_os << "\" attr.type=\"";
			writeToken(*_os, type);
			*_os << "\"/>" << std::endl;
		}

		for (typename NodeMaps::iterator it = _node_maps.begin(); it != _node_maps.end(); ++it)
		{

			std::string type = it->second->valueType();

			*_os << "\t<key id=\"";
			writeToken(*_os, it->first);
			*_os << "\" for=\"node\" attr.name=\"";
			writeToken(*_os, it->first);
			*_os << "\" attr.type=\"";
			writeToken(*_os, type);
			*_os << "\"/>" << std::endl;
		}

		//
		//		*_os << "\t";
		//		writeToken(*_os, "directed") << ' ';
		//		writeToken(*_os, "0");
		//		*_os << std::endl;
		//
		//		if (_attributes.empty())
		//			return;
		////		if (!_attributes_caption.empty()) {
		////			writeToken(*_os << ' ', _attributes_caption);
		////		}
		////		*_os << std::endl;
		//		for (typename Attributes::iterator it = _attributes.begin(); it != _attributes.end(); ++it) {
		//			*_os << "\t";
		//			writeToken(*_os, it->first) << ' ';
		//			writeToken(*_os, it->second->get());
		//			*_os << std::endl;
		//		}
	}

public:

	/// \name Execution of the Writer
	/// @{

	/// \brief Start the batch processing
	///
	/// This function starts the batch processing.
	void run() {
		*_os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
		*_os << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">" << std::endl;

		writeAttributes();

		*_os << "\t<graph id=\"G\" edgedefault=\"undirected\">" << std::endl;
		writeNodes();
		writeEdges();
		*_os << "\t</graph>" << std::endl;
		*_os << "</graphml>" << std::endl;
	}

	/// \brief Give back the stream of the writer
	///
	/// Give back the stream of the writer
	std::ostream& ostream() {
		return *_os;
	}

	/// @}
};


template<typename GR>
class GraphMLDigraphWriter {

public:

	typedef GR Graph;
	TEMPLATE_DIGRAPH_TYPEDEFS(GR);

private:

	std::ostream* _os;
	bool local_os;

	const GR& _graph;

	typedef std::map<Node, std::string> NodeIndex;
	NodeIndex _node_index;
	typedef std::map<Arc, std::string> ArcIndex;
	ArcIndex _arc_index;

	typedef std::vector<std::pair<std::string, TypedMapStorageBase<Node>* > > NodeMaps;
	NodeMaps _node_maps;

	typedef std::vector<std::pair<std::string, TypedMapStorageBase<Arc>*> > ArcMaps;
	ArcMaps _arc_maps;

	typedef std::vector<std::pair<std::string, _writer_bits::ValueStorageBase*> > Attributes;
	Attributes _attributes;

public:

	/// \brief Constructor
	///
	/// Construct a undirected graph writer, which writes to the given
	/// output stream.
	GraphMLDigraphWriter(const GR& graph, std::ostream& os = std::cout) :
		_os(&os),
		local_os(false),
		_graph(graph)
	{
	}

	/// \brief Constructor
	///
	/// Construct a undirected graph writer, which writes to the given
	/// output file.
	GraphMLDigraphWriter(const GR& graph, const std::string& fn) :
		_os(new std::ofstream(fn.c_str())),
		local_os(true),
		_graph(graph)
	{
		if (!(*_os)) {
			delete _os;
			throw IoError("Cannot write file", fn);
		}
	}

	/// \brief Constructor
	///
	/// Construct a undirected graph writer, which writes to the given
	/// output file.
	GraphMLDigraphWriter(const GR& graph, const char* fn) :
		_os(new std::ofstream(fn)),
		local_os(true),
		_graph(graph)
	{
		if (!(*_os)) {
			delete _os;
			throw IoError("Cannot write file", fn);
		}
	}

	/// \brief Destructor
	~GraphMLDigraphWriter()
	{
		for (typename NodeMaps::iterator it = _node_maps.begin();
				it != _node_maps.end(); ++it) {
			delete it->second;
		}

		for (typename ArcMaps::iterator it = _arc_maps.begin();
				it != _arc_maps.end(); ++it) {
			delete it->second;
		}

		for (typename Attributes::iterator it = _attributes.begin();
				it != _attributes.end(); ++it) {
			delete it->second;
		}

		if (local_os) {
			delete _os;
		}
	}

private:

	template<typename TGR>
	friend GraphMLDigraphWriter<TGR> graphMLDigraphWriter(const TGR& graph, std::ostream& os);

	template<typename TGR>
	friend GraphMLDigraphWriter<TGR> graphMLDigraphWriter(const TGR& graph, const std::string& fn);

	template<typename TGR>
	friend GraphMLDigraphWriter<TGR> graphMLDigraphWriter(const TGR& graph, const char *fn);



	GraphMLDigraphWriter(GraphMLDigraphWriter& other) :
		_os(other._os),
		local_os(other.local_os),
		_graph(other._graph)
	{

		other._os = 0;
		other.local_os = false;

		_node_index.swap(other._node_index);
		_arc_index.swap(other._arc_index);

		_node_maps.swap(other._node_maps);
		_arc_maps.swap(other._arc_maps);
		_attributes.swap(other._attributes);
	}

	GraphMLDigraphWriter& operator=(const GraphMLDigraphWriter&);

public:

	/// \name Writing Rules
	/// @{

	/// \brief Node map writing rule
	///
	/// Add a node map writing rule to the writer.
	template<typename Map>
	GraphMLDigraphWriter& nodeMap(const std::string& caption, const Map& map)
	{
		checkConcept<concepts::ReadMap<Node, typename Map::Value>, Map>();
		TypedMapStorageBase<Node>* storage = new TypedMapStorage<Node, Map>(map);
		_node_maps.push_back(std::make_pair(caption, storage));
		return *this;
	}

	/// \brief Node map writing rule
	///
	/// Add a node map writing rule with specialized converter to the
	/// writer.
	template<typename Map, typename Converter>
	GraphMLDigraphWriter& nodeMap(const std::string& caption, const Map& map, const Converter& converter = Converter())
	{
		checkConcept<concepts::ReadMap<Node, typename Map::Value>, Map>();
		TypedMapStorageBase<Node>* storage = new TypedMapStorage<Node, Map, Converter>(map, converter);
		_node_maps.push_back(std::make_pair(caption, storage));
		return *this;
	}

	/// \brief Arc map writing rule
	///
	/// Add an arc map writing rule to the writer.
	template <typename Map>
	GraphMLDigraphWriter& arcMap(const std::string& caption, const Map& map) {
		checkConcept<concepts::ReadMap<Arc, typename Map::Value>, Map>();
		TypedMapStorageBase<Arc>* storage =
				new TypedMapStorage<Arc, Map>(map);
		_arc_maps.push_back(std::make_pair(caption, storage));
		return *this;
	}

	/// \brief Arc map writing rule
	///
	/// Add an arc map writing rule with specialized converter to the
	/// writer.
	template <typename Map, typename Converter>
	GraphMLDigraphWriter& arcMap(const std::string& caption, const Map& map,
			const Converter& converter = Converter()) {
		checkConcept<concepts::ReadMap<Arc, typename Map::Value>, Map>();
		TypedMapStorageBase<Arc>* storage =
				new TypedMapStorage<Arc, Map, Converter>(map, converter);
		_arc_maps.push_back(std::make_pair(caption, storage));
		return *this;
	}

	/// \brief Attribute writing rule
	///
	/// Add an attribute writing rule to the writer.
	template<typename Value>
	GraphMLDigraphWriter& attribute(const std::string& caption, const Value& value)
	{
		_writer_bits::ValueStorageBase* storage = new _writer_bits::ValueStorage<Value>(value);
		_attributes.push_back(std::make_pair(caption, storage));
		return *this;
	}

private:

	inline static void writeEscape(std::ostream& os, char c) {
		switch (c) {
		case '\"':
			os << "&quot;";
			return;
		case '\'':
			os << "&apos;";
			return;
		case '<':
			os << "&lt;";
			return;
		case '>':
			os << "&gt;";
			return;
		case '&':
			os << "&amp;";
			return;
		default:
			if (c < 0x20) {
				std::ios::fmtflags flags = os.flags();
				os << '\\' << std::oct << static_cast<int>(c);
				os.flags(flags);
			} else {
				os << c;
			}
			return;
		}
	}

	inline std::ostream& writeToken(std::ostream& os, const std::string& str) {
		for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
			writeEscape(os, *it);
		}

		return os;
	}

	inline bool isNumber(const std::string & str)
	{
		for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
			if ((*it >= '0' && *it <= '9') || *it == '.' || *it == ',')
				continue;
			else
				return false;
		}

		return true;
	}

	inline bool requireEscape(const std::string & str)
	{
		for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
			if ((*it >= '0' && *it <= '9') || *it == '.' || *it == ',' || (*it >= 'A' && *it <= 'Z') || (*it >= 'a' && *it <= 'z'))
				continue;
			else
				return true;
		}

		return false;
	}

	inline std::ostream& writeCData(std::ostream& os, const std::string& str) {
		if (requireEscape(str))
		{
			os << "<![CDATA[";
			os << str;
			os << "]]>";
		}
		else
			os << str;
		return os;
	}

	void writeNodes() {
		std::vector<Node> nodes;
		for (NodeIt n(_graph); n != INVALID; ++n)
		{
			nodes.push_back(n);
		}

		IdMap<GR, Node> id_map(_graph);
		_writer_bits::MapLess<IdMap<GR, Node> > id_less(id_map);
		std::sort(nodes.begin(), nodes.end(), id_less);


		for (int i = 0; i < static_cast<int>(nodes.size()); ++i)
		{
			Node n = nodes[i];

			std::ostringstream os;
			os << _graph.id(n);
			_node_index.insert(std::make_pair(n, os.str()));

			*_os << "\t\t<node id=\"";
			writeToken(*_os, os.str());

			if (_node_maps.empty())
			{
				*_os << "\"/>"  << std::endl;
			}
			else
			{
				*_os << "\">"  << std::endl;
				for (typename NodeMaps::iterator it = _node_maps.begin(); it != _node_maps.end(); ++it)
				{
					std::string value = it->second->get(n);
					if (value == "")
						continue;

					*_os << "\t\t\t<data key=\"";
					writeToken(*_os, it->first);
					*_os << "\">";
					writeCData(*_os, value);
					*_os << "</data>" << std::endl;
				}
				*_os << "\t\t</node>" << std::endl;
			}
		}
	}
	void writeArcs()
	{
		std::vector<Arc> arcs;
		for (ArcIt n(_graph); n != INVALID; ++n) {
			arcs.push_back(n);
		}


		IdMap<GR, Arc> id_map(_graph);
		_writer_bits::MapLess<IdMap<GR, Arc> > id_less(id_map);
		std::sort(arcs.begin(), arcs.end(), id_less);


		for (int i = 0; i < static_cast<int>(arcs.size()); ++i)
		{
			Arc e = arcs[i];
			std::ostringstream os;
			os << _graph.id(e);
			_arc_index.insert(std::make_pair(e, os.str()));

			*_os << "\t\t<edge id=\"";
			writeToken(*_os, os.str());

			*_os << "\" source=\"";
			writeToken(*_os, _node_index.find(_graph.source(e))->second);
			*_os << "\" target=\"";
			writeToken(*_os, _node_index.find(_graph.target(e))->second);

			if (_arc_maps.empty())
			{
				*_os << "\"/>" << std::endl;
			}
			else
			{
				*_os << "\">" << std::endl;
				for (typename ArcMaps::iterator it = _arc_maps.begin(); it != _arc_maps.end(); ++it)
				{
					std::string value = it->second->get(e);
					if (value == "")
						continue;

					*_os << "\t\t\t<data key=\"";
					writeToken(*_os, it->first);
					*_os << "\">";
					writeCData(*_os, value);
					*_os << "</data>" << std::endl;
				}
				*_os << "\t\t</edge>" << std::endl;
			}


		}
	}

	void writeAttributes() {

		for (typename ArcMaps::iterator it = _arc_maps.begin(); it != _arc_maps.end(); ++it)
		{

			std::string type = it->second->valueType();

			*_os << "\t<key id=\"";
			writeToken(*_os, it->first);
			*_os << "\" for=\"edge\" attr.name=\"";
			writeToken(*_os, it->first);
			*_os << "\" attr.type=\"";
			writeToken(*_os, type);
			*_os << "\"/>" << std::endl;
		}

		for (typename NodeMaps::iterator it = _node_maps.begin(); it != _node_maps.end(); ++it)
		{

			std::string type = it->second->valueType();

			*_os << "\t<key id=\"";
			writeToken(*_os, it->first);
			*_os << "\" for=\"node\" attr.name=\"";
			writeToken(*_os, it->first);
			*_os << "\" attr.type=\"";
			writeToken(*_os, type);
			*_os << "\"/>" << std::endl;
		}
		//
		//		*_os << "\t";
		//		writeToken(*_os, "directed") << ' ';
		//		writeToken(*_os, "1");
		//		*_os << std::endl;
		//
		//		if (_attributes.empty())
		//			return;
		////		if (!_attributes_caption.empty()) {
		////			writeToken(*_os << ' ', _attributes_caption);
		////		}
		////		*_os << std::endl;
		//		for (typename Attributes::iterator it = _attributes.begin(); it != _attributes.end(); ++it) {
		//			*_os << "\t";
		//			writeToken(*_os, it->first) << ' ';
		//			writeToken(*_os, it->second->get());
		//			*_os << std::endl;
		//		}
	}

public:

	/// \name Execution of the Writer
	/// @{

	/// \brief Start the batch processing
	///
	/// This function starts the batch processing.
	void run() {
		*_os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
		*_os << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">" << std::endl;

		writeAttributes();

		*_os << "\t<graph id=\"G\" edgedefault=\"directed\">" << std::endl;
		writeNodes();
		writeArcs();
		*_os << "\t</graph>" << std::endl;
		*_os << "</graphml>" << std::endl;
	}

	/// \brief Give back the stream of the writer
	///
	/// Give back the stream of the writer
	std::ostream& ostream() {
		return *_os;
	}

	/// @}
};


template<typename TGR>
GraphMLGraphWriter<TGR> graphMLGraphWriter(const TGR& graph, std::ostream& os);

template<typename TGR>
GraphMLGraphWriter<TGR> graphMLGraphWriter(const TGR& graph, const std::string& fn);

template<typename TGR>
GraphMLGraphWriter<TGR> graphMLGraphWriter(const TGR& graph, const char *fn);

template<typename TGR>
GraphMLGraphWriter<TGR> graphMLGraphWriter(const TGR& graph, std::ostream& os)
{
	GraphMLGraphWriter<TGR> tmp(graph, os);
	return tmp;
}

template<typename TGR>
GraphMLGraphWriter<TGR> graphMLGraphWriter(const TGR& graph, const std::string& fn)
{
	GraphMLGraphWriter<TGR> tmp(graph, fn);
	return tmp;
}

template<typename TGR>
GraphMLGraphWriter<TGR> graphMLGraphWriter(const TGR& graph, const char *fn)
{
	GraphMLGraphWriter<TGR> tmp(graph, fn);
	return tmp;
}

template<typename TGR>
GraphMLDigraphWriter<TGR> graphMLDigraphWriter(const TGR& graph, std::ostream& os);

template<typename TGR>
GraphMLDigraphWriter<TGR> graphMLDigraphWriter(const TGR& graph, const std::string& fn);

template<typename TGR>
GraphMLDigraphWriter<TGR> graphMLDigraphWriter(const TGR& graph, const char *fn);

template<typename TGR>
GraphMLDigraphWriter<TGR> graphMLDigraphWriter(const TGR& graph, std::ostream& os)
{
	GraphMLDigraphWriter<TGR> tmp(graph, os);
	return tmp;
}

template<typename TGR>
GraphMLDigraphWriter<TGR> graphMLDigraphWriter(const TGR& graph, const std::string& fn)
{
	GraphMLDigraphWriter<TGR> tmp(graph, fn);
	return tmp;
}

template<typename TGR>
GraphMLDigraphWriter<TGR> graphMLDigraphWriter(const TGR& graph, const char *fn)
{
	GraphMLDigraphWriter<TGR> tmp(graph, fn);
	return tmp;
}





}

#endif /* GRAPHMLGRAPHWRITER_H_ */
