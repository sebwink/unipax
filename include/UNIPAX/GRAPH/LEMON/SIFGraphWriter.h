#ifndef SIFGRAPHWRITER_H_
#define SIFGRAPHWRITER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <algorithm>

#include <vector>
#include <list>
#include <functional>

#include <lemon/core.h>
#include <lemon/maps.h>

#include <lemon/concept_check.h>
#include <lemon/concepts/maps.h>

#include <lemon/lgf_writer.h>

namespace lemon
{

template<typename GR>
class SIFGraphWriter {

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

	_writer_bits::MapStorageBase<Node>* _label_map;

	_writer_bits::MapStorageBase<Edge>* _relation_map;

	typedef std::vector<_writer_bits::MapStorageBase<Edge>* > EdgeMaps;
	EdgeMaps _edge_maps;

	struct NodeAttribute {
		NodeAttribute(std::ostream& strm, _writer_bits::MapStorageBase<Node>* map, const std::string& n)
			: output(strm),
			  node_map(map),
			  name(n)
		{
		}

		std::ostream& output;
		_writer_bits::MapStorageBase<Node>* node_map;
		std::string name;
	};

	std::list<NodeAttribute> _node_attributes;

public:

	/// \brief Constructor
	///
	/// Construct a undirected graph writer, which writes to the given
	/// output stream.
	SIFGraphWriter(const GR& graph, std::ostream& os = std::cout, std::string unknown_label_prefix = "unknown_label_") :
			_os(&os),
			local_os(false),
			_graph(graph),
			_label_map(0),
			_relation_map(0),
			_edge_maps(0),
			//_node_attributes(0),
			_unknown_label_prefix(unknown_label_prefix)
	{
	}

	/// \brief Constructor
	///
	/// Construct a undirected graph writer, which writes to the given
	/// output file.
	SIFGraphWriter(const GR& graph, const std::string& fn, std::string unknown_label_prefix = "unknown_label_") :
			_os(new std::ofstream(fn.c_str())),
			local_os(true),
			_graph(graph),
			_label_map(0),
			_relation_map(0),
			_edge_maps(0),
			_unknown_label_prefix(unknown_label_prefix)
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
	SIFGraphWriter(const GR& graph, const char* fn, std::string unknown_label_prefix = "unknown_label_") :
			_os(new std::ofstream(fn)),
			local_os(true),
			_graph(graph),
			_label_map(0),
			_relation_map(0),
			_edge_maps(0),
			_unknown_label_prefix(unknown_label_prefix)
	{
		if (!(*_os)) {
			delete _os;
			throw IoError("Cannot write file", fn);
		}
	}

	/// \brief Destructor
	~SIFGraphWriter()
	{
		delete _label_map;
		delete _relation_map;

		for (typename EdgeMaps::iterator it = _edge_maps.begin(); it != _edge_maps.end(); ++it) {
			delete *it;
		}

		if (local_os) {
			delete _os;
		}
	}


private:

	template<typename TGR>
	friend SIFGraphWriter<TGR> sifGraphWriter(const TGR& graph, std::ostream& os);

	template<typename TGR>
	friend SIFGraphWriter<TGR> sifGraphWriter(const TGR& graph, const std::string& fn);

	template<typename TGR>
	friend SIFGraphWriter<TGR> sifGraphWriter(const TGR& graph, const char *fn);


	SIFGraphWriter(SIFGraphWriter& other) :
			_os(other._os),
			local_os(other.local_os),
			_graph(other._graph)
	{

		other._os = 0;
		other.local_os = false;

		_node_index.swap(other._node_index);
		_edge_index.swap(other._edge_index);

		_label_map = other._label_map;
		_relation_map = other._relation_map;
		_edge_maps.swap(other._edge_maps);
	}

	SIFGraphWriter& operator=(const SIFGraphWriter&);

public:

	/// \name Writing Rules
	/// @{

	/// \brief Node map writing rule
	///
	/// Add a node map writing rule to the writer.
	template<typename Map>
	SIFGraphWriter& labelMap(const Map& map)
	{
		checkConcept<concepts::ReadMap<Node, typename Map::Value>, Map>();
		_label_map = new _writer_bits::MapStorage<Node, Map>(map);
		return *this;
	}

	/// \brief Edge map writing rule
	///
	/// Add an relation map writing rule to the writer.
	template<typename Map>
	SIFGraphWriter& relationMap(const Map& map)
	{
		checkConcept<concepts::ReadMap<Edge, typename Map::Value>, Map>();
		_relation_map = new _writer_bits::MapStorage<Edge, Map>(map);
		return *this;
	}

	/// \brief Edge map writing rule
	///
	/// Add an edge map writing rule to the writer.
	template<typename Map>
	SIFGraphWriter& dataMap(const Map& map)
	{
		checkConcept<concepts::ReadMap<Edge, typename Map::Value>, Map>();
		_writer_bits::MapStorageBase<Edge>* storage = new _writer_bits::MapStorage<Edge, Map>(map);
		_edge_maps.push_back(storage);
		return *this;
	}

	/// \brief Edge map writing rule
	///
	/// Add an edge map writing rule with specialized converter to the
	/// writer.
	template<typename Map, typename Converter>
	SIFGraphWriter& dataMap(const Map& map, const Converter& converter = Converter())
	{
		checkConcept<concepts::ReadMap<Edge, typename Map::Value>, Map>();
		_writer_bits::MapStorageBase<Edge>* storage = new _writer_bits::MapStorage<Edge, Map, Converter>(map, converter);
		_edge_maps.push_back(storage);
		return *this;
	}

	/// \brief Additional node attributes
	///
	/// Add an additional output stream to write node attributes to.
	///
	/// \param name The name that should be written to the header of the node attributes.
	/// \param map The map containing the node attributes
	/// \param output A std::ostream to which the output should be written to.
	template<typename Map>
	SIFGraphWriter& nodeMap(const std::string& name, const Map& map, std::ostream& output)
	{
		checkConcept<concepts::ReadMap<Node, typename Map::Value>, Map>();
		_writer_bits::MapStorageBase<Node>* storage = new _writer_bits::MapStorage<Node, Map>(map);
		_node_attributes.push_back(NodeAttribute(output, storage, name));
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

	void createNodeIndex() {
		if (_label_map == 0) {
			for (NodeIt n(_graph); n != INVALID; ++n) {
				std::ostringstream os;
				os << _graph.id(n);
				_node_index.insert(std::make_pair(n, os.str()));
			}
		} else {
			for (NodeIt n(_graph); n != INVALID; ++n) {
				std::string value = _label_map->get(n);
				if (value != "")
					_node_index.insert(std::make_pair(n, value));
				else
				{
					std::ostringstream os;
					os << _unknown_label_prefix;
					os << _graph.id(n);
					_node_index.insert(std::make_pair(n, os.str()));
				}
			}
		}
	}

	void writeNodeAttributes()
	{
		for (typename std::list<NodeAttribute>::const_iterator at(_node_attributes.begin()); at != _node_attributes.end(); ++at)
		{
			at->output << at->name << std::endl;
			for(typename std::map<Node, std::string>::const_iterator it = _node_index.begin(); it != _node_index.end(); ++it)
			{
				writeToken(at->output, it->second);
				at->output << "\t=\t";
				writeToken(at->output, at->node_map->get(it->first));
				at->output << std::endl;
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

			writeToken(*_os, _node_index.find(_graph.u(e))->second);
			*_os << "\t";
			if (!_edge_maps.empty())
				*_os << "(";
			if (_relation_map->get(e) == "")
				writeToken(*_os, "pp");
			else
				writeToken(*_os, _relation_map->get(e));
			if (!_edge_maps.empty())
				*_os << ")";
			*_os << "\t";
			writeToken(*_os, _node_index.find(_graph.v(e))->second);

			if (!_edge_maps.empty())
			{
				*_os << "\t=";
				for (typename EdgeMaps::iterator it = _edge_maps.begin(); it != _edge_maps.end(); ++it)
				{
					*_os << "\t";
					writeToken(*_os, (*it)->get(e), true);
				}
			}
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
		createNodeIndex();
		writeEdges();
		writeNodeAttributes();
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
class SIFDigraphWriter {

public:

	typedef GR Graph;

	TEMPLATE_DIGRAPH_TYPEDEFS(GR);

private:

	std::ostream* _os;
	bool local_os;
	std::string _unknown_label_prefix;

	const GR& _graph;

	typedef std::map<Node, std::string> NodeIndex;
	NodeIndex _node_index;
	typedef std::map<Arc, std::string> EdgeIndex;
	EdgeIndex _edge_index;

	_writer_bits::MapStorageBase<Node>* _label_map;

	_writer_bits::MapStorageBase<Arc>* _relation_map;

	typedef std::vector<_writer_bits::MapStorageBase<Arc>* > EdgeMaps;
	EdgeMaps _edge_maps;

	struct NodeAttribute {
		NodeAttribute(std::ostream& strm, _writer_bits::MapStorageBase<Node>* map, const std::string& n)
			: output(strm),
			  node_map(map),
			  name(n)
		{
		}

		std::ostream& output;
		_writer_bits::MapStorageBase<Node>* node_map;
		std::string name;
	};

	std::list<NodeAttribute> _node_attributes;

public:

	/// \brief Constructor
	///
	/// Construct a undirected graph writer, which writes to the given
	/// output stream.
	SIFDigraphWriter(const GR& graph, std::ostream& os = std::cout, std::string unknown_label_prefix = "unknown_label_") :
			_os(&os),
			local_os(false),
			_graph(graph),
			_label_map(0),
			_relation_map(0),
			_edge_maps(0),
			_unknown_label_prefix(unknown_label_prefix)
	{
	}

	/// \brief Constructor
	///
	/// Construct a undirected graph writer, which writes to the given
	/// output file.
	SIFDigraphWriter(const GR& graph, const std::string& fn, std::string unknown_label_prefix = "unknown_label_") :
			_os(new std::ofstream(fn.c_str())),
			local_os(true),
			_graph(graph),
			_label_map(0),
			_relation_map(0),
			_edge_maps(0),
			_unknown_label_prefix(unknown_label_prefix)
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
	SIFDigraphWriter(const GR& graph, const char* fn, std::string unknown_label_prefix = "unknown_label_") :
			_os(new std::ofstream(fn)),
			local_os(true),
			_graph(graph),
			_label_map(0),
			_relation_map(0),
			_edge_maps(0),
			_unknown_label_prefix(unknown_label_prefix)
	{
		if (!(*_os)) {
			delete _os;
			throw IoError("Cannot write file", fn);
		}
	}

	/// \brief Destructor
	~SIFDigraphWriter()
	{
		delete _label_map;
		delete _relation_map;

		for (typename EdgeMaps::iterator it = _edge_maps.begin(); it != _edge_maps.end(); ++it) {
			delete *it;
		}

		if (local_os) {
			delete _os;
		}
	}


private:

	template<typename TGR>
	friend SIFDigraphWriter<TGR> sifDigraphWriter(const TGR& graph, std::ostream& os);

	template<typename TGR>
	friend SIFDigraphWriter<TGR> sifDigraphWriter(const TGR& graph, const std::string& fn);

	template<typename TGR>
	friend SIFDigraphWriter<TGR> sifDigraphWriter(const TGR& graph, const char *fn);


	SIFDigraphWriter(SIFDigraphWriter& other) :
			_os(other._os),
			local_os(other.local_os),
			_graph(other._graph)
	{

		other._os = 0;
		other.local_os = false;

		_node_index.swap(other._node_index);
		_edge_index.swap(other._edge_index);

		_label_map = other._label_map;
		_relation_map = other._relation_map;
		_edge_maps.swap(other._edge_maps);
	}

	SIFDigraphWriter& operator=(const SIFDigraphWriter&);

public:

	/// \name Writing Rules
	/// @{

	/// \brief Node map writing rule
	///
	/// Add a node map writing rule to the writer.
	template<typename Map>
	SIFDigraphWriter& labelMap(const Map& map)
	{
		checkConcept<concepts::ReadMap<Node, typename Map::Value>, Map>();
		_label_map = new _writer_bits::MapStorage<Node, Map>(map);
		return *this;
	}

	/// \brief Edge map writing rule
	///
	/// Add an relation map writing rule to the writer.
	template<typename Map>
	SIFDigraphWriter& relationMap(const Map& map)
	{
		checkConcept<concepts::ReadMap<Arc, typename Map::Value>, Map>();
		_relation_map = new _writer_bits::MapStorage<Arc, Map>(map);
		return *this;
	}

	/// \brief Edge map writing rule
	///
	/// Add an edge map writing rule to the writer.
	template<typename Map>
	SIFDigraphWriter& dataMap(const Map& map)
	{
		checkConcept<concepts::ReadMap<Arc, typename Map::Value>, Map>();
		_writer_bits::MapStorageBase<Arc>* storage = new _writer_bits::MapStorage<Arc, Map>(map);
		_edge_maps.push_back(storage);
		return *this;
	}

	/// \brief Edge map writing rule
	///
	/// Add an edge map writing rule with specialized converter to the
	/// writer.
	template<typename Map, typename Converter>
	SIFDigraphWriter& dataMap(const Map& map, const Converter& converter = Converter())
	{
		checkConcept<concepts::ReadMap<Arc, typename Map::Value>, Map>();
		_writer_bits::MapStorageBase<Arc>* storage = new _writer_bits::MapStorage<Arc, Map, Converter>(map, converter);
		_edge_maps.push_back(storage);
		return *this;
	}

	/// \brief Additional node attributes
	///
	/// Add an additional output stream to write node attributes to.
	///
	/// \param name The name that should be written to the header of the node attributes.
	/// \param map The map containing the node attributes
	/// \param output A std::ostream to which the output should be written to.
	template<typename Map>
	SIFDigraphWriter& nodeMap(const std::string& name, const Map& map, std::ostream& output)
	{
		checkConcept<concepts::ReadMap<Node, typename Map::Value>, Map>();
		_writer_bits::MapStorageBase<Node>* storage = new _writer_bits::MapStorage<Node, Map>(map);
		_node_attributes.push_back(NodeAttribute(output, storage, name));
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

	void createNodeIndex() {
		if (_label_map == 0) {
			for (NodeIt n(_graph); n != INVALID; ++n) {
				std::ostringstream os;
				os << _graph.id(n);
				_node_index.insert(std::make_pair(n, os.str()));
			}
		} else {
			for (NodeIt n(_graph); n != INVALID; ++n) {
				std::string value = _label_map->get(n);
				if (value != "")
					_node_index.insert(std::make_pair(n, value));
				else
				{
					std::ostringstream os;
					os << _unknown_label_prefix;
					os << _graph.id(n);
					_node_index.insert(std::make_pair(n, os.str()));
				}
			}
		}
	}

	void writeNodeAttributes()
	{
		for (typename std::list<NodeAttribute>::const_iterator at(_node_attributes.begin()); at != _node_attributes.end(); ++at)
		{
			at->output << at->name << std::endl;
			for(typename std::map<Node, std::string>::const_iterator it = _node_index.begin(); it != _node_index.end(); ++it)
			{
				writeToken(at->output, it->second);
				at->output << "\t=\t";
				writeToken(at->output, at->node_map->get(it->first));
				at->output << std::endl;
			}
		}
	}

	void writeEdges()
	{
		std::vector<Arc> edges;
		for (ArcIt n(_graph); n != INVALID; ++n) {
			edges.push_back(n);
		}

		IdMap<GR, Arc> id_map(_graph);
		_writer_bits::MapLess<IdMap<GR, Arc> > id_less(id_map);
		std::sort(edges.begin(), edges.end(), id_less);


		for (int i = 0; i < static_cast<int>(edges.size()); ++i)
		{
			Arc e = edges[i];

			writeToken(*_os, _node_index.find(_graph.source(e))->second);
			*_os << "\t";
			if (!_edge_maps.empty())
				*_os << "(";
			if (_relation_map->get(e) == "")
				writeToken(*_os, "pp");
			else
				writeToken(*_os, _relation_map->get(e));
			if (!_edge_maps.empty())
				*_os << ")";
			*_os << "\t";
			writeToken(*_os, _node_index.find(_graph.target(e))->second);

			if (!_edge_maps.empty())
			{
				*_os << "\t=";
				for (typename EdgeMaps::iterator it = _edge_maps.begin(); it != _edge_maps.end(); ++it)
				{
					*_os << "\t";
					writeToken(*_os, (*it)->get(e), true);
				}
			}
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
		createNodeIndex();
		writeEdges();
		writeNodeAttributes();
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
SIFGraphWriter<TGR> sifGraphWriter(const TGR& graph, std::ostream& os);

template<typename TGR>
SIFGraphWriter<TGR> sifGraphWriter(const TGR& graph, const std::string& fn);

template<typename TGR>
SIFGraphWriter<TGR> sifGraphWriter(const TGR& graph, const char *fn);

template<typename TGR>
SIFGraphWriter<TGR> sifGraphWriter(const TGR& graph, std::ostream& os)
{
	SIFGraphWriter<TGR> tmp(graph, os);
	return tmp;
}

template<typename TGR>
SIFGraphWriter<TGR> sifGraphWriter(const TGR& graph, const std::string& fn)
{
	SIFGraphWriter<TGR> tmp(graph, fn);
	return tmp;
}

template<typename TGR>
SIFGraphWriter<TGR> sifGraphWriter(const TGR& graph, const char *fn)
{
	SIFGraphWriter<TGR> tmp(graph, fn);
	return tmp;
}

template<typename TGR>
SIFDigraphWriter<TGR> sifDigraphWriter(const TGR& graph, std::ostream& os);

template<typename TGR>
SIFDigraphWriter<TGR> sifDigraphWriter(const TGR& graph, const std::string& fn);

template<typename TGR>
SIFDigraphWriter<TGR> sifDigraphWriter(const TGR& graph, const char *fn);

template<typename TGR>
SIFDigraphWriter<TGR> sifDigraphWriter(const TGR& graph, std::ostream& os)
{
	SIFDigraphWriter<TGR> tmp(graph, os);
	return tmp;
}

template<typename TGR>
SIFDigraphWriter<TGR> sifDigraphWriter(const TGR& graph, const std::string& fn)
{
	SIFDigraphWriter<TGR> tmp(graph, fn);
	return tmp;
}

template<typename TGR>
SIFDigraphWriter<TGR> sifDigraphWriter(const TGR& graph, const char *fn)
{
	SIFDigraphWriter<TGR> tmp(graph, fn);
	return tmp;
}

}

#endif /* SIFGRAPHWRITER_H_ */
