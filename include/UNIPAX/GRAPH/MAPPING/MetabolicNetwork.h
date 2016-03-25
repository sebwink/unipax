/*
 * MetabolicNetwork.h
 *
 *  Created on: Mar 8, 2012
 *      Author: gerasch
 */

#ifndef METABOLICNETWORK_H_
#define METABOLICNETWORK_H_

#include <UNIPAX/COMMON/common.h>
#include <UNIPAX/GRAPH/MAPPING/BiologicalNetwork.h>

#include <lemon/list_graph.h>
#include <lemon/maps.h>

#include <boost/shared_ptr.hpp>

#include <set>
#include <string>

namespace UniPAX
{
namespace GRAPH
{
class UNIPAX_EXPORT MetabolicNetwork : virtual public UniPAX::GRAPH::BiologicalNetwork
{

public:

	typedef lemon::ListDigraph Graph;
	typedef Graph::Arc Arc;
	typedef Graph::Node Node;
	typedef Graph::ArcIt ArcIt;
	typedef Graph::NodeIt NodeIt;

	Graph graph;
	Graph::ArcMap<std::string> relationMap;
	Graph::ArcMap<UnipaxId> arc_id_map;
	Graph::NodeMap<UnipaxId> node_id_map;

	std::map<UnipaxId, Graph::Node> id_node_map;

	std::multimap<UnipaxId, Graph::Arc> id_arcs_map;

	typedef std::pair<std::multimap<UnipaxId, Graph::Arc>::iterator, std::multimap<UnipaxId, Graph::Arc>::iterator> ArcMapEqualRange;

	MetabolicNetwork() : graph(), relationMap(graph), arc_id_map(graph), node_id_map(graph), id_node_map(), id_arcs_map() {}


	MetabolicNetwork(MetabolicNetwork & copy) : graph(), relationMap(graph), arc_id_map(graph), node_id_map(graph), id_node_map()
	{
		lemon::digraphCopy(copy.graph, graph).arcMap(copy.relationMap, relationMap).nodeMap(copy.node_id_map, node_id_map).run();

		for (Graph::NodeIt it(graph); it != lemon::INVALID; ++it)
		{
			id_node_map[node_id_map[it]] = it;
		}

		for (Graph::ArcIt it(graph); it != lemon::INVALID; ++it)
		{
			id_arcs_map.insert(std::make_pair(arc_id_map[it], it));
		}

	}

	Node createNode(UnipaxId id)
	{
		Node n = graph.addNode();

		id_node_map[id] = n;
		node_id_map[n] = id;

		return n;
	}

	Node getNode(UnipaxId id)
	{
		return id_node_map[id];
	}

	bool hasNode(UnipaxId id)
	{
		return id_node_map.find(id) != id_node_map.end();
	}

	Arc createArc(Node source, Node target, std::string relation)
	{
		Arc a = graph.addArc(source, target);

		relationMap[a] = relation;

		// fill the id_arcs_map
		if (relation == "leftEntity")
		{
			id_arcs_map.insert(std::make_pair(node_id_map[target], a));
			arc_id_map[a] = node_id_map[target];
		}
		else if (relation == "rightEntity")
		{
			id_arcs_map.insert(std::make_pair(node_id_map[source], a));
			arc_id_map[a] = node_id_map[source];
		}

		return a;
	}

	int hasArc(UnipaxId id)
	{
		return id_arcs_map.count(id);
	}

	std::vector<Arc> getArcs(UnipaxId id)
	{
		std::vector<Arc> edges;

		for (ArcMapEqualRange p = id_arcs_map.equal_range(id); p.first != p.second; ++p.first)
		{
			edges.push_back(p.first->second);
		}

		return edges;
	}

	MetabolicNetwork & retainNodes(std::set<UnipaxId> nodes)
	{
		for (std::map<UnipaxId, Graph::Node>::iterator it = id_node_map.begin(); it != id_node_map.end();)
		{
			if (nodes.find(it->first) == nodes.end())
			{
				Graph::Node n = it->second;

				if (graph.valid(n))
					graph.erase(n);
				id_node_map.erase(it++);
			}
			else
			{
				++it;
			}
		}

		return *this;
	}

	MetabolicNetwork & retainNodes(std::set<Graph::Node> nodes)
	{
		std::set<UnipaxId> ids;
		for (std::map<UnipaxId, Graph::Node>::iterator it = id_node_map.begin(); it != id_node_map.end();)
		{
			if (nodes.find(it->second) != nodes.end())
				ids.insert(it->first);
		}
		return retainNodes(ids);
	}

	MetabolicNetwork & eraseDisconnectedNodes()
	{
		for (std::map<UnipaxId, Graph::Node>::iterator it = id_node_map.begin(); it != id_node_map.end();)
		{
			if (lemon::countInArcs(graph, it->second) + lemon::countOutArcs(graph, it->second) == 0)
			{
				if (graph.valid(it->second))
					graph.erase(it->second);
				id_node_map.erase(it++);
			}
			else
			{
				++it;
			}
		}

		return *this;
	}

	MetabolicNetwork & removeNodes(std::set<Graph::Node> nodes)
	{
		for (std::map<UnipaxId, Graph::Node>::iterator it = id_node_map.begin(); it != id_node_map.end();)
		{
			if (nodes.find(it->second) != nodes.end())
			{
				Graph::Node n = it->second;

				if (graph.valid(n))
					graph.erase(n);
				id_node_map.erase(it++);
			}
			else
			{
				++it;
			}
		}

		return *this;
	}

	MetabolicNetwork & retainArcs(std::set<UnipaxId> arcs)
	{
		for (std::map<UnipaxId, Graph::Arc>::iterator it = id_arcs_map.begin(); it != id_arcs_map.end();)
		{
			if (arcs.find(it->first) == arcs.end())
			{
				Graph::Arc a = it->second;

				if (graph.valid(a))
					graph.erase(a);
				id_arcs_map.erase(it++);
			}
			else
			{
				++it;
			}
		}

		return *this;
	}

	MetabolicNetwork & retainArcs(std::set<Graph::Arc> arcs)
	{
		for (std::map<UnipaxId, Graph::Arc>::iterator it = id_arcs_map.begin(); it != id_arcs_map.end();)
		{
			if (arcs.find(it->second) == arcs.end())
			{
				Graph::Arc a = it->second;

				if (graph.valid(a))
					graph.erase(a);
				id_arcs_map.erase(it++);
			}
			else
			{
				++it;
			}
		}

		return *this;
	}

	MetabolicNetwork & removeArcs(std::set<UnipaxId> arcs)
	{
		for (std::map<UnipaxId, Graph::Arc>::iterator it = id_arcs_map.begin(); it != id_arcs_map.end();)
		{
			if (arcs.find(it->first) != arcs.end())
			{
				Graph::Arc a = it->second;

				if (graph.valid(a))
					graph.erase(a);
				id_arcs_map.erase(it++);
			}
			else
			{
				++it;
			}
		}

		return *this;
	}

	MetabolicNetwork & removeArcs(std::set<Graph::Arc> arcs)
	{
		for (std::map<UnipaxId, Graph::Arc>::iterator it = id_arcs_map.begin(); it != id_arcs_map.end();)
		{
			if (arcs.find(it->second) != arcs.end())
			{
				Graph::Arc a = it->second;

				if (graph.valid(a))
					graph.erase(a);
				id_arcs_map.erase(it++);
			}
			else
			{
				++it;
			}
		}

		return *this;
	}



	template <typename T, typename F> MetabolicNetwork & filterNodes(Graph::NodeMap<T> & map, T value, bool retain_match = true)
	{
		std::set<Graph::Node> nodes;

		for (Graph::NodeIt it(graph); it != lemon::INVALID; ++it)
		{
			if (std::equal_to<T>(map[it], value))
			{
				nodes.insert(it);
			}
		}

		if (retain_match)
			retainNodes(nodes);
		else
			removeNodes(nodes);

		return *this;
	}

	template <typename T, typename F> MetabolicNetwork & filterNodes(Graph::NodeMap<T> & map, T value, F f = F(), bool retain_match = true)
	{
		std::set<Graph::Node> nodes;

		for (Graph::NodeIt it(graph); it != lemon::INVALID; ++it)
		{
			if (f(map[it], value))
			{
				nodes.insert(it);
			}
		}

		if (retain_match)
			retainNodes(nodes);
		else
			removeNodes(nodes);

		return *this;
	}

};

typedef UnipaxPtr<MetabolicNetwork>::type MetabolicNetworkPtr;

}
}


#endif /* METABOLICNETWORK_H_ */
