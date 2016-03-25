#ifndef GMXGRAPHWRITER_H_
#define GMXGRAPHWRITER_H_

#include <iostream>
#include <fstream>
#include <sstream>

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
class GMXGraphWriter {

public:

	typedef GR Graph;

	TEMPLATE_GRAPH_TYPEDEFS(GR);

private:

	std::ostream* _os;
	bool local_os;

	std::string _geneset_title;
	std::string _geneset_description;

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
	GMXGraphWriter(const GR& graph, std::ostream& os = std::cout) :
			_os(&os),
			local_os(false),
			_graph(graph),
			_label_map(0),
			_relation_map(0),
			_edge_maps(0),
			_node_attributes(0)
	{
	}

	/// \brief Constructor
	///
	/// Construct a undirected graph writer, which writes to the given
	/// output file.
	GMXGraphWriter(const GR& graph, const std::string& fn) :
			_os(new std::ofstream(fn.c_str())),
			local_os(true),
			_graph(graph),
			_label_map(0),
			_relation_map(0),
			_edge_maps(0)
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
	GMXGraphWriter(const GR& graph, const char* fn) :
			_os(new std::ofstream(fn)),
			local_os(true),
			_graph(graph),
			_label_map(0),
			_relation_map(0),
			_edge_maps(0)
	{
		if (!(*_os)) {
			delete _os;
			throw IoError("Cannot write file", fn);
		}
	}

	/// \brief Destructor
	~GMXGraphWriter()
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
	friend GMXGraphWriter<TGR> gmxGraphWriter(const TGR& graph, std::ostream& os);

	template<typename TGR>
	friend GMXGraphWriter<TGR> gmxGraphWriter(const TGR& graph, const std::string& fn);

	template<typename TGR>
	friend GMXGraphWriter<TGR> gmxGraphWriter(const TGR& graph, const char *fn);


	GMXGraphWriter(GMXGraphWriter& other) :
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

	GMXGraphWriter& operator=(const GMXGraphWriter&);

public:

	/// \name Writing Rules
	/// @{

	/// \brief Node map writing rule
	///
	/// Add a node map writing rule to the writer.
	template<typename Map>
	GMXGraphWriter& labelMap(const Map& map)
	{
		checkConcept<concepts::ReadMap<Node, typename Map::Value>, Map>();
		_label_map = new _writer_bits::MapStorage<Node, Map>(map);
		return *this;
	}

	/// \brief Edge map writing rule
	///
	/// Add an relation map writing rule to the writer.
	template<typename Map>
	GMXGraphWriter& relationMap(const Map& map)
	{
		checkConcept<concepts::ReadMap<Edge, typename Map::Value>, Map>();
		_relation_map = new _writer_bits::MapStorage<Edge, Map>(map);
		return *this;
	}

	/// \brief Edge map writing rule
	///
	/// Add an edge map writing rule to the writer.
	template<typename Map>
	GMXGraphWriter& dataMap(const Map& map)
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
	GMXGraphWriter& dataMap(const Map& map, const Converter& converter = Converter())
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
	GMXGraphWriter& nodeMap(const std::string& name, const Map& map, std::ostream& output)
	{
		checkConcept<concepts::ReadMap<Node, typename Map::Value>, Map>();
		_writer_bits::MapStorageBase<Node>* storage = new _writer_bits::MapStorage<Node, Map>(map);
		_node_attributes.push_back(NodeAttribute(output, storage, name));
		return *this;
	}

	/// \brief gene set title
	///
	/// Add an gene set title to the writer.
	GMXGraphWriter& genesetTitle(const std::string title)
	{
		_geneset_title = title;
		return *this;
	}

	/// \brief gene set description
	///
	/// Add an gene set description to the writer.
	GMXGraphWriter& genesetDescription(const std::string description)
	{
		_geneset_description = description;
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


		std::set<std::string> node_labels;
		for (int i = 0; i < static_cast<int>(nodes.size()); ++i)
		{
			Node n = nodes[i];
			if (_node_index.find(n)->second != "")
			{
				node_labels.insert(_node_index.find(n)->second);
			}
		}

		std::set<std::string>::iterator set_it;
		for (set_it = node_labels.begin(); set_it != node_labels.end(); set_it++)
		{
			*_os << *set_it;
			*_os << std::endl;
		}
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
				_node_index.insert(std::make_pair(n, value));
			}
		}
	}

public:

	/// \name Execution of the Writer
	/// @{

	/// \brief Start the batch processing
	///
	/// This function starts the batch processing.
	void run() {
		*_os << _geneset_title << std::endl;
		*_os << _geneset_description << std::endl;
		createNodeIndex();
		writeNodes();
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
class GMXDigraphWriter {

public:

	typedef GR Graph;

	TEMPLATE_DIGRAPH_TYPEDEFS(GR);

private:

	std::ostream* _os;
	bool local_os;

	std::string _geneset_title;
	std::string _geneset_description;

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
	GMXDigraphWriter(const GR& graph, std::ostream& os = std::cout) :
			_os(&os),
			local_os(false),
			_graph(graph),
			_label_map(0),
			_relation_map(0),
			_edge_maps(0)
	{
	}

	/// \brief Constructor
	///
	/// Construct a undirected graph writer, which writes to the given
	/// output file.
	GMXDigraphWriter(const GR& graph, const std::string& fn) :
			_os(new std::ofstream(fn.c_str())),
			local_os(true),
			_graph(graph),
			_label_map(0),
			_relation_map(0),
			_edge_maps(0)
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
	GMXDigraphWriter(const GR& graph, const char* fn) :
			_os(new std::ofstream(fn)),
			local_os(true),
			_graph(graph),
			_label_map(0),
			_relation_map(0),
			_edge_maps(0)
	{
		if (!(*_os)) {
			delete _os;
			throw IoError("Cannot write file", fn);
		}
	}

	/// \brief Destructor
	~GMXDigraphWriter()
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
	friend GMXDigraphWriter<TGR> gmxDigraphWriter(const TGR& graph, std::ostream& os);

	template<typename TGR>
	friend GMXDigraphWriter<TGR> gmxDigraphWriter(const TGR& graph, const std::string& fn);

	template<typename TGR>
	friend GMXDigraphWriter<TGR> gmxDigraphWriter(const TGR& graph, const char *fn);


	GMXDigraphWriter(GMXDigraphWriter& other) :
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

	GMXDigraphWriter& operator=(const GMXDigraphWriter&);

public:

	/// \name Writing Rules
	/// @{

	/// \brief Node map writing rule
	///
	/// Add a node map writing rule to the writer.
	template<typename Map>
	GMXDigraphWriter& labelMap(const Map& map)
	{
		checkConcept<concepts::ReadMap<Node, typename Map::Value>, Map>();
		_label_map = new _writer_bits::MapStorage<Node, Map>(map);
		return *this;
	}

	/// \brief Edge map writing rule
	///
	/// Add an relation map writing rule to the writer.
	template<typename Map>
	GMXDigraphWriter& relationMap(const Map& map)
	{
		checkConcept<concepts::ReadMap<Arc, typename Map::Value>, Map>();
		_relation_map = new _writer_bits::MapStorage<Arc, Map>(map);
		return *this;
	}

	/// \brief Edge map writing rule
	///
	/// Add an edge map writing rule to the writer.
	template<typename Map>
	GMXDigraphWriter& dataMap(const Map& map)
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
	GMXDigraphWriter& dataMap(const Map& map, const Converter& converter = Converter())
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
	GMXDigraphWriter& nodeMap(const std::string& name, const Map& map, std::ostream& output)
	{
		checkConcept<concepts::ReadMap<Node, typename Map::Value>, Map>();
		_writer_bits::MapStorageBase<Node>* storage = new _writer_bits::MapStorage<Node, Map>(map);
		_node_attributes.push_back(NodeAttribute(output, storage, name));
		return *this;
	}

	/// \brief gene set title
	///
	/// Add an gene set title to the writer.
	GMXDigraphWriter& genesetTitle(const std::string title)
	{
		_geneset_title = title;
		return *this;
	}

	/// \brief gene set description
	///
	/// Add an gene set description to the writer.
	GMXDigraphWriter& genesetDescription(const std::string description)
	{
		_geneset_description = description;
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

		std::set<std::string> node_labels;
		for (int i = 0; i < static_cast<int>(nodes.size()); ++i)
		{
			Node n = nodes[i];
			if (_node_index.find(n)->second != "")
			{
				node_labels.insert(_node_index.find(n)->second);
			}
		}

		std::set<std::string>::iterator set_it;
		for (set_it = node_labels.begin(); set_it != node_labels.end(); set_it++)
		{
			*_os << *set_it;
			*_os << std::endl;
		}
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
				_node_index.insert(std::make_pair(n, value));
			}
		}
	}

public:

	/// \name Execution of the Writer
	/// @{

	/// \brief Start the batch processing
	///
	/// This function starts the batch processing.
	void run() {
		*_os << _geneset_title << std::endl;
		*_os << _geneset_description << std::endl;
		createNodeIndex();
		writeNodes();
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
GMXGraphWriter<TGR> gmxGraphWriter(const TGR& graph, std::ostream& os);

template<typename TGR>
GMXGraphWriter<TGR> gmxGraphWriter(const TGR& graph, const std::string& fn);

template<typename TGR>
GMXGraphWriter<TGR> gmxGraphWriter(const TGR& graph, const char *fn);

template<typename TGR>
GMXGraphWriter<TGR> gmxGraphWriter(const TGR& graph, std::ostream& os)
{
	GMXGraphWriter<TGR> tmp(graph, os);
	return tmp;
}

template<typename TGR>
GMXGraphWriter<TGR> gmxGraphWriter(const TGR& graph, const std::string& fn)
{
	GMXGraphWriter<TGR> tmp(graph, fn);
	return tmp;
}

template<typename TGR>
GMXGraphWriter<TGR> gmxGraphWriter(const TGR& graph, const char *fn)
{
	GMXGraphWriter<TGR> tmp(graph, fn);
	return tmp;
}

template<typename TGR>
GMXDigraphWriter<TGR> gmxDigraphWriter(const TGR& graph, std::ostream& os);

template<typename TGR>
GMXDigraphWriter<TGR> gmxDigraphWriter(const TGR& graph, const std::string& fn);

template<typename TGR>
GMXDigraphWriter<TGR> gmxDigraphWriter(const TGR& graph, const char *fn);

template<typename TGR>
GMXDigraphWriter<TGR> gmxDigraphWriter(const TGR& graph, std::ostream& os)
{
	GMXDigraphWriter<TGR> tmp(graph, os);
	return tmp;
}

template<typename TGR>
GMXDigraphWriter<TGR> gmxDigraphWriter(const TGR& graph, const std::string& fn)
{
	GMXDigraphWriter<TGR> tmp(graph, fn);
	return tmp;
}

template<typename TGR>
GMXDigraphWriter<TGR> gmxDigraphWriter(const TGR& graph, const char *fn)
{
	GMXDigraphWriter<TGR> tmp(graph, fn);
	return tmp;
}





}

#endif /* GMXGRAPHWRITER_H_ */
