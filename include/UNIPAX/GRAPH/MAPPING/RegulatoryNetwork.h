/*
 * RegulatoryNetwork.h
 *
 *  Created on: Mar 8, 2012
 *      Author: gerasch
 */

#ifndef REGULATORYNETWORK_H_
#define REGULATORYNETWORK_H_

#include <UNIPAX/COMMON/common.h>
#include <UNIPAX/GRAPH/MAPPING/BiologicalNetwork.h>

#include <lemon/list_graph.h>
#include <lemon/maps.h>
#include <lemon/core.h>

#include <boost/shared_ptr.hpp>

#include <set>
#include <string>
#include <map>

namespace UniPAX
{
namespace GRAPH
{

class UNIPAX_EXPORT RegulatoryNetwork : virtual public UniPAX::GRAPH::BiologicalNetwork
{


public:

	typedef lemon::ListDigraph Graph;
	typedef Graph::Arc Edge;
	typedef Graph::Node Node;
	typedef Graph::ArcIt EdgeIt;
	typedef Graph::NodeIt NodeIt;



	Graph graph;
	Graph::ArcMap<UnipaxId> arc_id_map;
	Graph::NodeMap<UnipaxId> node_id_map;

	std::map<UnipaxId, Graph::Node> id_node_map;

	std::multimap<UnipaxId, Graph::Arc> id_arcs_map;

	typedef std::pair<std::multimap<UnipaxId, RegulatoryNetwork::Graph::Arc>::iterator, std::multimap<UnipaxId, RegulatoryNetwork::Graph::Arc>::iterator> ArcMapEqualRange;

	RegulatoryNetwork() : graph(), arc_id_map(graph), node_id_map(graph), id_node_map(), id_arcs_map() {}


	RegulatoryNetwork(RegulatoryNetwork & copy) : graph(), arc_id_map(graph), node_id_map(graph), id_node_map()
	{
		lemon::digraphCopy(copy.graph, graph).arcMap(copy.arc_id_map, arc_id_map).nodeMap(copy.node_id_map, node_id_map).run();

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

	Edge createEdge(Node source, Node target, UnipaxId id)
	{
		Edge e = graph.addArc(source, target);

		arc_id_map[e] = id;
		id_arcs_map.insert(std::make_pair(id, e));

		return e;
	}

	int hasEdge(UnipaxId id)
	{
		return id_arcs_map.count(id);
	}

	std::vector<Edge> getEdges(UnipaxId id)
	{
		std::vector<Edge> edges;

		for (ArcMapEqualRange p = id_arcs_map.equal_range(id); p.first != p.second; ++p.first)
		{
			edges.push_back(p.first->second);
		}

		return edges;
	}


	RegulatoryNetwork & eraseNode(UnipaxId id)
	{
		if (id_node_map.find(id) != id_node_map.end())
		{
			Graph::Node n = id_node_map.find(id)->second;

			for (Graph::InArcIt it(graph, n); it != lemon::INVALID; ++it)
			{
				UnipaxId _id = arc_id_map[it];

				for (ArcMapEqualRange p = id_arcs_map.equal_range(_id); p.first != p.second; )
				{
					if (p.first->second == it)
					{
						id_arcs_map.erase(p.first++);
					}
					else
					{
						++p.first;
					}
				}
			}

			for (Graph::OutArcIt it(graph, n); it != lemon::INVALID; ++it)
			{
				UnipaxId _id = arc_id_map[it];

				for (ArcMapEqualRange p = id_arcs_map.equal_range(_id); p.first != p.second; )
				{
					if (p.first->second == it)
					{
						id_arcs_map.erase(p.first++);
					}
					else
					{
						++p.first;
					}
				}
			}

			if (graph.valid(id_node_map.find(id)->second))
				graph.erase(id_node_map.find(id)->second);
			id_node_map.erase(id);
		}

		return *this;
	}

	RegulatoryNetwork & eraseRegulation(UnipaxId id)
	{
		if (id_arcs_map.find(id) != id_arcs_map.end())
		{
			for (ArcMapEqualRange p = id_arcs_map.equal_range(id); p.first != p.second; ++p.first)
			{
				if (graph.valid(p.first->second))
					graph.erase(p.first->second);
			}
			id_arcs_map.erase(id);
		}

		return *this;
	}

	RegulatoryNetwork & retainNodes(std::set<UnipaxId> nodes)
	{
		for (std::map<UnipaxId, Graph::Node>::iterator it = id_node_map.begin(); it != id_node_map.end();)
		{
			if (nodes.find(it->first) == nodes.end())
			{
				Graph::Node n = it->second;

				for (Graph::InArcIt it2(graph, n); it2 != lemon::INVALID; ++it2)
				{
					UnipaxId _id = arc_id_map[it2];

					for (ArcMapEqualRange p = id_arcs_map.equal_range(_id); p.first != p.second; )
					{
						if (p.first->second == it2)
						{
							id_arcs_map.erase(p.first++);
						}
						else
						{
							++p.first;
						}
					}
				}

				for (Graph::OutArcIt it2(graph, n); it2 != lemon::INVALID; ++it2)
				{
					UnipaxId _id = arc_id_map[it2];

					for (ArcMapEqualRange p = id_arcs_map.equal_range(_id); p.first != p.second; )
					{
						if (p.first->second == it2)
						{
							id_arcs_map.erase(p.first++);
						}
						else
						{
							++p.first;
						}
					}
				}

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

	RegulatoryNetwork & removeNodes(std::set<UnipaxId> nodes)
	{
		for (std::map<UnipaxId, Graph::Node>::iterator it = id_node_map.begin(); it != id_node_map.end();)
		{
			if (nodes.find(it->first) != nodes.end())
			{
				Graph::Node n = it->second;

				for (Graph::InArcIt it2(graph, n); it2 != lemon::INVALID; ++it2)
				{
					UnipaxId _id = arc_id_map[it2];

					for (ArcMapEqualRange p = id_arcs_map.equal_range(_id); p.first != p.second; )
					{
						if (p.first->second == it2)
						{
							id_arcs_map.erase(p.first++);
						}
						else
						{
							++p.first;
						}
					}
				}

				for (Graph::OutArcIt it2(graph, n); it2 != lemon::INVALID; ++it2)
				{
					UnipaxId _id = arc_id_map[it2];

					for (ArcMapEqualRange p = id_arcs_map.equal_range(_id); p.first != p.second; )
					{
						if (p.first->second == it2)
						{
							id_arcs_map.erase(p.first++);
						}
						else
						{
							++p.first;
						}
					}
				}

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

	RegulatoryNetwork & retainNodes(std::set<Graph::Node> nodes)
	{
		for (std::map<UnipaxId, Graph::Node>::iterator it = id_node_map.begin(); it != id_node_map.end();)
		{
			if (nodes.find(it->second) == nodes.end())
			{
				Graph::Node n = it->second;

				for (Graph::InArcIt it2(graph, n); it2 != lemon::INVALID; ++it2)
				{
					UnipaxId _id = arc_id_map[it2];

					for (ArcMapEqualRange p = id_arcs_map.equal_range(_id); p.first != p.second; )
					{
						if (p.first->second == it2)
						{
							id_arcs_map.erase(p.first++);
						}
						else
						{
							++p.first;
						}
					}
				}

				for (Graph::OutArcIt it2(graph, n); it2 != lemon::INVALID; ++it2)
				{
					UnipaxId _id = arc_id_map[it2];

					for (ArcMapEqualRange p = id_arcs_map.equal_range(_id); p.first != p.second; )
					{
						if (p.first->second == it2)
						{
							id_arcs_map.erase(p.first++);
						}
						else
						{
							++p.first;
						}
					}
				}

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

	RegulatoryNetwork & removeNodes(std::set<Graph::Node> nodes)
	{
		for (std::map<UnipaxId, Graph::Node>::iterator it = id_node_map.begin(); it != id_node_map.end();)
		{
			if (nodes.find(it->second) != nodes.end())
			{
				Graph::Node n = it->second;

				for (Graph::InArcIt it2(graph, n); it2 != lemon::INVALID; ++it2)
				{
					UnipaxId _id = arc_id_map[it2];

					for (ArcMapEqualRange p = id_arcs_map.equal_range(_id); p.first != p.second; )
					{
						if (p.first->second == it2)
						{
							id_arcs_map.erase(p.first++);
						}
						else
						{
							++p.first;
						}
					}
				}

				for (Graph::OutArcIt it2(graph, n); it2 != lemon::INVALID; ++it2)
				{
					UnipaxId _id = arc_id_map[it2];

					for (ArcMapEqualRange p = id_arcs_map.equal_range(_id); p.first != p.second; )
					{
						if (p.first->second == it2)
						{
							id_arcs_map.erase(p.first++);
						}
						else
						{
							++p.first;
						}
					}
				}

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

	RegulatoryNetwork & retainArcs(std::set<UnipaxId> arcs)
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

	RegulatoryNetwork & retainArcs(std::set<Graph::Arc> arcs)
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

	RegulatoryNetwork & removeArcs(std::set<UnipaxId> arcs)
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

	RegulatoryNetwork & removeArcs(std::set<Graph::Arc> arcs)
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


	RegulatoryNetwork & eraseDisconnectedNodes()
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

	template <typename T> RegulatoryNetwork & filterNodes(Graph::NodeMap<T> & map, T value, bool retain_match = true)
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


	template <typename T, typename F> RegulatoryNetwork & filterNodes(Graph::NodeMap<T> & map, T value, const F & f = F(), bool retain_match = true)
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

	template <typename T> RegulatoryNetwork & filterArcs(Graph::ArcMap<T> & map, T value, bool retain_match = true)
	{
		std::set<Graph::Arc> arcs;

		for (Graph::ArcIt it(graph); it != lemon::INVALID; ++it)
		{
			if (std::equal_to<T>(map[it], value))
			{
				arcs.insert(it);
			}
		}

		if (retain_match)
			retainArcs(arcs);
		else
			removeArcs(arcs);

		return *this;
	}

	template <typename T, typename F> RegulatoryNetwork & filterArcs(Graph::ArcMap<T> & map, T value, const F & f = F(), bool retain_match = true)
	{
		std::set<Graph::Arc> arcs;

		for (Graph::ArcIt it(graph); it != lemon::INVALID; ++it)
		{
			if (f(map[it], value))
			{
				arcs.insert(it);
			}
		}

		if (retain_match)
			retainArcs(arcs);
		else
			removeArcs(arcs);

		return *this;
	}

	template<typename TV, template<class, class, class> class F> void mapNodeData(Graph::template NodeMap<TV> & targetNodeDataMap, const F<Graph::Node, UnipaxId, TV> & f)
	{
		for (Graph::NodeIt it(graph); it != lemon::INVALID; ++it)
		{
			targetNodeDataMap[it] = f(it, node_id_map[it]);
		}
	}

	template<typename TV, typename MV, template<class, class, class> class F> void mapNodeData(Graph::template NodeMap<TV> & targetNodeDataMap, Graph::template NodeMap<MV> & mappingNodeDataMap, const F<Graph::Node, MV, TV> & f)
	{
		for (Graph::NodeIt it(graph); it != lemon::INVALID; ++it)
		{
			targetNodeDataMap[it] = f(it, mappingNodeDataMap[it]);
		}
	}


	template<typename TV, template<class, class, class> class F> void mapArcData(Graph::template ArcMap<TV> & targetArcDataMap, const F<typename Graph::Arc, UnipaxId, TV> & f)
	{
		for (Graph::ArcIt it(graph); it != lemon::INVALID; ++it)
		{
			targetArcDataMap[it] = f(it, arc_id_map[it]);
		}
	}

	template<typename TV, typename MV, template<class, class, class> class F> void mapArcData(Graph::template ArcMap<TV> & targetArcDataMap, Graph::template ArcMap<MV> & mappingArcDataMap, const F<Graph::Arc, MV, TV> & f)
	{
		for (Graph::ArcIt it(graph); it != lemon::INVALID; ++it)
		{
			targetArcDataMap[it] = f(it, mappingArcDataMap[it]);
		}
	}
};

typedef UnipaxPtr<RegulatoryNetwork>::type RegulatoryNetworkPtr;

}
}


#endif /* REGULATORYNETWORK_H_ */
