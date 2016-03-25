#ifndef GMLGRAPHWRITER_H_
#define GMLGRAPHWRITER_H_

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

namespace lemon
{

template<typename GR>
class GMLGraphWriter {

public:

	typedef GR Graph;

	TEMPLATE_GRAPH_TYPEDEFS(GR);

private:

	std::ostream* _os;
	bool local_os;
	std::string _unknown_label_prefix;

	const GR& _graph;

	typedef std::map<Node, std::string> NodeIndex;
	NodeIndex _node_index;
	typedef std::map<Edge, std::string> EdgeIndex;
	EdgeIndex _edge_index;

	typedef std::vector<std::pair<std::string, _writer_bits::MapStorageBase<Node>* > > NodeMaps;
	NodeMaps _node_maps;

	typedef std::vector<std::pair<std::string, _writer_bits::MapStorageBase<Edge>*> > EdgeMaps;
	EdgeMaps _edge_maps;

	typedef std::vector<std::pair<std::string, _writer_bits::ValueStorageBase*> > Attributes;
	Attributes _attributes;

public:

	/// \brief Constructor
	///
	/// Construct a undirected graph writer, which writes to the given
	/// output stream.
	GMLGraphWriter(const GR& graph, std::ostream& os = std::cout) :
			_os(&os),
			local_os(false),
			_graph(graph)
	{
	}

	/// \brief Constructor
	///
	/// Construct a undirected graph writer, which writes to the given
	/// output file.
	GMLGraphWriter(const GR& graph, const std::string& fn) :
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
	GMLGraphWriter(const GR& graph, const char* fn) :
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
	~GMLGraphWriter()
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
	friend GMLGraphWriter<TGR> gmlGraphWriter(const TGR& graph, std::ostream& os);

	template<typename TGR>
	friend GMLGraphWriter<TGR> gmlGraphWriter(const TGR& graph, const std::string& fn);

	template<typename TGR>
	friend GMLGraphWriter<TGR> gmlGraphWriter(const TGR& graph, const char *fn);


	GMLGraphWriter(GMLGraphWriter& other) :
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

	GMLGraphWriter& operator=(const GMLGraphWriter&);

public:

	/// \name Writing Rules
	/// @{

	/// \brief Node map writing rule
	///
	/// Add a node map writing rule to the writer.
	template<typename Map>
	GMLGraphWriter& nodeMap(const std::string& caption, const Map& map)
	{
		checkConcept<concepts::ReadMap<Node, typename Map::Value>, Map>();
		_writer_bits::MapStorageBase<Node>* storage = new _writer_bits::MapStorage<Node, Map>(map);
		_node_maps.push_back(std::make_pair(caption, storage));
		return *this;
	}

	/// \brief Node map writing rule
	///
	/// Add a node map writing rule with specialized converter to the
	/// writer.
	template<typename Map, typename Converter>
	GMLGraphWriter& nodeMap(const std::string& caption, const Map& map, const Converter& converter = Converter())
	{
		checkConcept<concepts::ReadMap<Node, typename Map::Value>, Map>();
		_writer_bits::MapStorageBase<Node>* storage = new _writer_bits::MapStorage<Node, Map, Converter>(map, converter);
		_node_maps.push_back(std::make_pair(caption, storage));
		return *this;
	}

	/// \brief Edge map writing rule
	///
	/// Add an edge map writing rule to the writer.
	template<typename Map>
	GMLGraphWriter& edgeMap(const std::string& caption, const Map& map)
	{
		checkConcept<concepts::ReadMap<Edge, typename Map::Value>, Map>();
		_writer_bits::MapStorageBase<Edge>* storage =
				new _writer_bits::MapStorage<Edge, Map>(map);
		_edge_maps.push_back(std::make_pair(caption, storage));
		return *this;
	}

	/// \brief Edge map writing rule
	///
	/// Add an edge map writing rule with specialized converter to the
	/// writer.
	template<typename Map, typename Converter>
	GMLGraphWriter& edgeMap(const std::string& caption, const Map& map, const Converter& converter = Converter())
	{
		checkConcept<concepts::ReadMap<Edge, typename Map::Value>, Map>();
		_writer_bits::MapStorageBase<Edge>* storage = new _writer_bits::MapStorage<Edge, Map, Converter>(map, converter);
		_edge_maps.push_back(std::make_pair(caption, storage));
		return *this;
	}

	/// \brief Arc map writing rule
	///
	/// Add an arc map writing rule to the writer.
	template<typename Map>
	GMLGraphWriter& arcMap(const std::string& caption, const Map& map)
	{
		checkConcept<concepts::ReadMap<Arc, typename Map::Value>, Map>();
		_writer_bits::MapStorageBase<Edge>* forward_storage = new _writer_bits::GraphArcMapStorage<GR, true, Map>(_graph, map);
		_edge_maps.push_back(std::make_pair('+' + caption, forward_storage));
		_writer_bits::MapStorageBase<Edge>* backward_storage = new _writer_bits::GraphArcMapStorage<GR, false, Map>(_graph, map);
		_edge_maps.push_back(std::make_pair('-' + caption, backward_storage));
		return *this;
	}

	/// \brief Arc map writing rule
	///
	/// Add an arc map writing rule with specialized converter to the
	/// writer.
	template<typename Map, typename Converter>
	GMLGraphWriter& arcMap(const std::string& caption, const Map& map, const Converter& converter = Converter())
	{
		checkConcept<concepts::ReadMap<Arc, typename Map::Value>, Map>();
		_writer_bits::MapStorageBase<Edge>* forward_storage = new _writer_bits::GraphArcMapStorage<GR, true, Map, Converter>(_graph, map, converter);
		_edge_maps.push_back(std::make_pair('+' + caption, forward_storage));
		_writer_bits::MapStorageBase<Edge>* backward_storage = new _writer_bits::GraphArcMapStorage<GR, false, Map, Converter>(_graph, map, converter);
		_edge_maps.push_back(std::make_pair('-' + caption, backward_storage));
		return *this;
	}

	/// \brief Attribute writing rule
	///
	/// Add an attribute writing rule to the writer.
	template<typename Value>
	GMLGraphWriter& attribute(const std::string& caption, const Value& value)
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
	GMLGraphWriter& attribute(const std::string& caption, const Value& value, const Converter& converter = Converter())
	{
		_writer_bits::ValueStorageBase* storage = new _writer_bits::ValueStorage<Value, Converter>(value, converter);
		_attributes.push_back(std::make_pair(caption, storage));
		return *this;
	}

private:

    inline bool isWhiteSpace(char c) {
      return c == ' ' || c == '\t' || c == '\v' ||
        c == '\n' || c == '\r' || c == '\f';
    }

    inline bool isEscaped(char c) {
      return c == '\\' || c == '\"' || c == '\'' ||
        c == '\a' || c == '\b';
    }

    inline bool isDigit(char c) {
    	return c >= '0' && c <= '9';
    }

    inline static void writeEscape(std::ostream& os, char c) {
      switch (c) {
      case '\\':
        os << "\\\\";
        return;
      case '\"':
        os << "\\\"";
        return;
      case '\a':
        os << "\\a";
        return;
      case '\b':
        os << "\\b";
        return;
      case '\f':
        os << "\\f";
        return;
      case '\r':
        os << "\\r";
        return;
      case '\n':
        os << "\\n";
        return;
      case '\t':
        os << "\\t";
        return;
      case '\v':
        os << "\\v";
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

    inline bool requireEscape(const std::string& str) {
      if (str.empty() || str[0] == '@') return true;
      std::istringstream is(str);
      char c;
      while (is.get(c)) {
        if (!isDigit(c)) {
          return true;
        }
      }
      return false;
    }

    inline std::ostream& writeToken(std::ostream& os, const std::string& str, bool checkEscape = false) {

      if (checkEscape && requireEscape(str))
      {
        os << '\"';
        for (std::string::const_iterator it = str.begin();
             it != str.end(); ++it) {
          writeEscape(os, *it);
        }
        os << '\"';
      } else {
        os << str;
      }
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

			*_os << "\tnode [" << std::endl;

			*_os << "\t\t" << "id" << '\t';
			std::ostringstream os;
			os << _graph.id(n);
			writeToken(*_os, os.str());
			*_os << std::endl;
			_node_index.insert(std::make_pair(n, os.str()));

			for (typename NodeMaps::iterator it = _node_maps.begin(); it != _node_maps.end(); ++it)
			{
				*_os << "\t\t";
				writeToken(*_os, it->first);
				*_os << " ";
				std::string value = it->second->get(n);
				writeToken(*_os, value, true);
				*_os << std::endl;
			}
			*_os << "\t]" << std::endl;
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

			*_os << "\tedge [" << std::endl;

			*_os << "\t\t";
			writeToken(*_os, "source");
			*_os << " ";
			writeToken(*_os, _node_index.find(_graph.u(e))->second);
			*_os << std::endl;

			*_os << "\t\t";
			writeToken(*_os, "target");
			*_os << " ";
			writeToken(*_os, _node_index.find(_graph.v(e))->second);
			*_os << std::endl;

			*_os << "\t\tid ";
			std::ostringstream os;
			os << _graph.id(e);
			writeToken(*_os, os.str());
			*_os << std::endl;
			_edge_index.insert(std::make_pair(e, os.str()));

			for (typename EdgeMaps::iterator it = _edge_maps.begin(); it != _edge_maps.end(); ++it)
			{
				*_os << "\t\t";
				writeToken(*_os, it->first);
				*_os << " ";
				std::string value = it->second->get(e);
				writeToken(*_os, value, true);
				*_os << std::endl;
			}
			*_os << "\t]" << std::endl;
		}
	}

	void writeAttributes() {
		*_os << "\t";
		writeToken(*_os, "directed") << ' ';
		writeToken(*_os, "0");
		*_os << std::endl;

		if (_attributes.empty())
			return;
//		if (!_attributes_caption.empty()) {
//			writeToken(*_os << ' ', _attributes_caption);
//		}
//		*_os << std::endl;
		for (typename Attributes::iterator it = _attributes.begin(); it != _attributes.end(); ++it) {
			*_os << "\t";
			writeToken(*_os, it->first) << ' ';
			writeToken(*_os, it->second->get());
			*_os << std::endl;
		}
	}

public:

	/// \name Execution of the Writer
	/// @{

	/// \brief Start the batch processing
	///
	/// This function starts the batch processing.
	void run() {
		*_os << "graph [" << std::endl;
		writeAttributes();
		writeNodes();
		writeEdges();
		*_os << "]" << std::endl;
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
class GMLDigraphWriter {

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

	typedef std::vector<std::pair<std::string, _writer_bits::MapStorageBase<Node>* > > NodeMaps;
	NodeMaps _node_maps;

	typedef std::vector<std::pair<std::string, _writer_bits::MapStorageBase<Arc>*> > ArcMaps;
	ArcMaps _arc_maps;

	typedef std::vector<std::pair<std::string, _writer_bits::ValueStorageBase*> > Attributes;
	Attributes _attributes;

public:

	/// \brief Constructor
	///
	/// Construct a undirected graph writer, which writes to the given
	/// output stream.
	GMLDigraphWriter(const GR& graph, std::ostream& os = std::cout) :
			_os(&os),
			local_os(false),
			_graph(graph)
	{
	}

	/// \brief Constructor
	///
	/// Construct a undirected graph writer, which writes to the given
	/// output file.
	GMLDigraphWriter(const GR& graph, const std::string& fn) :
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
	GMLDigraphWriter(const GR& graph, const char* fn) :
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
	~GMLDigraphWriter()
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
	friend GMLDigraphWriter<TGR> gmlDigraphWriter(const TGR& graph, std::ostream& os);

	template<typename TGR>
	friend GMLDigraphWriter<TGR> gmlDigraphWriter(const TGR& graph, const std::string& fn);

	template<typename TGR>
	friend GMLDigraphWriter<TGR> gmlDigraphWriter(const TGR& graph, const char *fn);



	GMLDigraphWriter(GMLDigraphWriter& other) :
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

	GMLDigraphWriter& operator=(const GMLDigraphWriter&);

public:

	/// \name Writing Rules
	/// @{

	/// \brief Node map writing rule
	///
	/// Add a node map writing rule to the writer.
	template<typename Map>
	GMLDigraphWriter& nodeMap(const std::string& caption, const Map& map)
	{
		checkConcept<concepts::ReadMap<Node, typename Map::Value>, Map>();
		_writer_bits::MapStorageBase<Node>* storage = new _writer_bits::MapStorage<Node, Map>(map);
		_node_maps.push_back(std::make_pair(caption, storage));
		return *this;
	}

	/// \brief Node map writing rule
	///
	/// Add a node map writing rule with specialized converter to the
	/// writer.
	template<typename Map, typename Converter>
	GMLDigraphWriter& nodeMap(const std::string& caption, const Map& map, const Converter& converter = Converter())
	{
		checkConcept<concepts::ReadMap<Node, typename Map::Value>, Map>();
		_writer_bits::MapStorageBase<Node>* storage = new _writer_bits::MapStorage<Node, Map, Converter>(map, converter);
		_node_maps.push_back(std::make_pair(caption, storage));
		return *this;
	}

    /// \brief Arc map writing rule
    ///
    /// Add an arc map writing rule to the writer.
    template <typename Map>
    GMLDigraphWriter& arcMap(const std::string& caption, const Map& map) {
      checkConcept<concepts::ReadMap<Arc, typename Map::Value>, Map>();
      _writer_bits::MapStorageBase<Arc>* storage =
        new _writer_bits::MapStorage<Arc, Map>(map);
      _arc_maps.push_back(std::make_pair(caption, storage));
      return *this;
    }

    /// \brief Arc map writing rule
    ///
    /// Add an arc map writing rule with specialized converter to the
    /// writer.
    template <typename Map, typename Converter>
    GMLDigraphWriter& arcMap(const std::string& caption, const Map& map,
                          const Converter& converter = Converter()) {
      checkConcept<concepts::ReadMap<Arc, typename Map::Value>, Map>();
      _writer_bits::MapStorageBase<Arc>* storage =
        new _writer_bits::MapStorage<Arc, Map, Converter>(map, converter);
      _arc_maps.push_back(std::make_pair(caption, storage));
      return *this;
    }

	/// \brief Attribute writing rule
	///
	/// Add an attribute writing rule to the writer.
	template<typename Value>
	GMLDigraphWriter& attribute(const std::string& caption, const Value& value)
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
	GMLDigraphWriter& attribute(const std::string& caption, const Value& value, const Converter& converter = Converter())
	{
		_writer_bits::ValueStorageBase* storage = new _writer_bits::ValueStorage<Value, Converter>(value, converter);
		_attributes.push_back(std::make_pair(caption, storage));
		return *this;
	}

private:

    inline bool isWhiteSpace(char c) {
      return c == ' ' || c == '\t' || c == '\v' ||
        c == '\n' || c == '\r' || c == '\f';
    }

    inline bool isEscaped(char c) {
      return c == '\\' || c == '\"' || c == '\'' ||
        c == '\a' || c == '\b';
    }

    inline bool isDigit(char c) {
    	return c >= '0' && c <= '9';
    }

    inline static void writeEscape(std::ostream& os, char c) {
      switch (c) {
      case '\\':
        os << "\\\\";
        return;
      case '\"':
        os << "\\\"";
        return;
      case '\a':
        os << "\\a";
        return;
      case '\b':
        os << "\\b";
        return;
      case '\f':
        os << "\\f";
        return;
      case '\r':
        os << "\\r";
        return;
      case '\n':
        os << "\\n";
        return;
      case '\t':
        os << "\\t";
        return;
      case '\v':
        os << "\\v";
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

    inline bool requireEscape(const std::string& str) {
      if (str.empty() || str[0] == '@') return true;
      std::istringstream is(str);
      char c;
      while (is.get(c)) {
        if (!isDigit(c)) {
          return true;
        }
      }
      return false;
    }

    inline std::ostream& writeToken(std::ostream& os, const std::string& str, bool checkEscape = false) {

      if (checkEscape && requireEscape(str))
      {
        os << '\"';
        for (std::string::const_iterator it = str.begin();
             it != str.end(); ++it) {
          writeEscape(os, *it);
        }
        os << '\"';
      } else {
        os << str;
      }
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

			*_os << "\tnode [" << std::endl;

			*_os << "\t\t" << "id" << '\t';
			std::ostringstream os;
			os << _graph.id(n);
			writeToken(*_os, os.str());
			*_os << std::endl;
			_node_index.insert(std::make_pair(n, os.str()));

			for (typename NodeMaps::iterator it = _node_maps.begin(); it != _node_maps.end(); ++it)
			{
				*_os << "\t\t";
				writeToken(*_os, it->first);
				*_os << " ";
				std::string value = it->second->get(n);
				writeToken(*_os, value, true);
				*_os << std::endl;
			}
			*_os << "\t]" << std::endl;
		}
	}

	void createNodeIndex() {
		for (NodeIt n(_graph); n != INVALID; ++n) {
			std::ostringstream os;
			os << _graph.id(n);
			_node_index.insert(std::make_pair(n, os.str()));
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

			*_os << "\tedge [" << std::endl;

			*_os << "\t\t";
			writeToken(*_os, "source");
			*_os << " ";
			writeToken(*_os, _node_index.find(_graph.source(e))->second);
			*_os << std::endl;

			*_os << "\t\t";
			writeToken(*_os, "target");
			*_os << " ";
			writeToken(*_os, _node_index.find(_graph.target(e))->second);
			*_os << std::endl;

			*_os << "\t\tid ";
			std::ostringstream os;
			os << _graph.id(e);
			writeToken(*_os, os.str());
			*_os << std::endl;
			_arc_index.insert(std::make_pair(e, os.str()));

			for (typename ArcMaps::iterator it = _arc_maps.begin(); it != _arc_maps.end(); ++it)
			{
				*_os << "\t\t";
				writeToken(*_os, it->first);
				*_os << " ";
				std::string value = it->second->get(e);
				writeToken(*_os, value, true);
				*_os << std::endl;
			}
			*_os << "\t]" << std::endl;
		}
	}

	void createArcIndex() {
		for (ArcIt e(_graph); e != INVALID; ++e) {
			std::ostringstream os;
			os << _graph.id(e);
			_arc_index.insert(std::make_pair(e, os.str()));
		}

	}

	void writeAttributes() {
		*_os << "\t";
		writeToken(*_os, "directed") << ' ';
		writeToken(*_os, "1");
		*_os << std::endl;

		if (_attributes.empty())
			return;
//		if (!_attributes_caption.empty()) {
//			writeToken(*_os << ' ', _attributes_caption);
//		}
//		*_os << std::endl;
		for (typename Attributes::iterator it = _attributes.begin(); it != _attributes.end(); ++it) {
			*_os << "\t";
			writeToken(*_os, it->first) << ' ';
			writeToken(*_os, it->second->get());
			*_os << std::endl;
		}
	}

public:

	/// \name Execution of the Writer
	/// @{

	/// \brief Start the batch processing
	///
	/// This function starts the batch processing.
	void run() {
		*_os << "graph [" << std::endl;
		writeAttributes();
		writeNodes();
		writeArcs();
		*_os << "]" << std::endl;
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
GMLGraphWriter<TGR> gmlGraphWriter(const TGR& graph, std::ostream& os);

template<typename TGR>
GMLGraphWriter<TGR> gmlGraphWriter(const TGR& graph, const std::string& fn);

template<typename TGR>
GMLGraphWriter<TGR> gmlGraphWriter(const TGR& graph, const char *fn);

template<typename TGR>
GMLGraphWriter<TGR> gmlGraphWriter(const TGR& graph, std::ostream& os)
{
	GMLGraphWriter<TGR> tmp(graph, os);
	return tmp;
}

template<typename TGR>
GMLGraphWriter<TGR> gmlGraphWriter(const TGR& graph, const std::string& fn)
{
	GMLGraphWriter<TGR> tmp(graph, fn);
	return tmp;
}

template<typename TGR>
GMLGraphWriter<TGR> gmlGraphWriter(const TGR& graph, const char *fn)
{
	GMLGraphWriter<TGR> tmp(graph, fn);
	return tmp;
}

template<typename TGR>
GMLDigraphWriter<TGR> gmlDigraphWriter(const TGR& graph, std::ostream& os);

template<typename TGR>
GMLDigraphWriter<TGR> gmlDigraphWriter(const TGR& graph, const std::string& fn);

template<typename TGR>
GMLDigraphWriter<TGR> gmlDigraphWriter(const TGR& graph, const char *fn);

template<typename TGR>
GMLDigraphWriter<TGR> gmlDigraphWriter(const TGR& graph, std::ostream& os)
{
	GMLDigraphWriter<TGR> tmp(graph, os);
	return tmp;
}

template<typename TGR>
GMLDigraphWriter<TGR> gmlDigraphWriter(const TGR& graph, const std::string& fn)
{
	GMLDigraphWriter<TGR> tmp(graph, fn);
	return tmp;
}

template<typename TGR>
GMLDigraphWriter<TGR> gmlDigraphWriter(const TGR& graph, const char *fn)
{
	GMLDigraphWriter<TGR> tmp(graph, fn);
	return tmp;
}





}

#endif /* GMLGRAPHWRITER_H_ */
