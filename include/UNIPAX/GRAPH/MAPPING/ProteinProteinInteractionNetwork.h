/*
 * ProteinProteinInteractionNetwork.h
 *
 *  Created on: Mar 8, 2012
 *      Author: gerasch
 */

#ifndef PROTEINPROTEININTERACTIONNETWORK_H_
#define PROTEINPROTEININTERACTIONNETWORK_H_

#include <UNIPAX/COMMON/common.h>
#include <UNIPAX/GRAPH/MAPPING/BiologicalNetwork.h>

#include <lemon/list_graph.h>
#include <lemon/maps.h>

#include <boost/shared_ptr.hpp>

#include <set>
#include <string>
#include <map>

namespace UniPAX
{
namespace GRAPH
{

class UNIPAX_EXPORT ProteinProteinInteractionNetwork : virtual public UniPAX::GRAPH::BiologicalNetwork
{


public:

	typedef lemon::ListGraph Graph;
	typedef Graph::Edge Edge;
	typedef Graph::Node Node;
	typedef Graph::EdgeIt EdgeIt;
	typedef Graph::NodeIt NodeIt;

	Graph graph;
	Graph::EdgeMap<UnipaxId> edge_id_map;
	Graph::NodeMap<UnipaxId> node_id_map;

	std::map<UnipaxId, Graph::Node> id_node_map;

	std::multimap<UnipaxId, Graph::Edge> id_edges_map;

	typedef std::pair<std::multimap<UnipaxId, Graph::Edge>::iterator, std::multimap<UnipaxId, Graph::Edge>::iterator> EdgeMapEqualRange;

	ProteinProteinInteractionNetwork() : graph(), edge_id_map(graph), node_id_map(graph), id_node_map(), id_edges_map() {}


	ProteinProteinInteractionNetwork(ProteinProteinInteractionNetwork & copy) : graph(), edge_id_map(graph), node_id_map(graph), id_node_map(), id_edges_map()
	{
		lemon::graphCopy(copy.graph, graph).edgeMap(copy.edge_id_map, edge_id_map).nodeMap(copy.node_id_map, node_id_map).run();

		for (Graph::NodeIt it(graph); it != lemon::INVALID; ++it)
		{
			id_node_map[node_id_map[it]] = it;
		}

		for (Graph::EdgeIt it(graph); it != lemon::INVALID; ++it)
		{
			id_edges_map.insert(std::make_pair(edge_id_map[it], it));
		}
	}

	struct EquiDigraph
	{
		EquiDigraph(const Graph & ori) :
			graph(),
			oriNodeRef(graph),
			newNodeRef(ori)
		{}

		lemon::ListDigraph graph;
		lemon::ListDigraph::NodeMap<Graph::Node> oriNodeRef;
		Graph::NodeMap<lemon::ListDigraph::Node> newNodeRef;
	};

	typedef UnipaxPtr<EquiDigraph>::type EquiDigraphPtr;

	EquiDigraphPtr createEquivalent()
	{
		EquiDigraphPtr equi_digraph(new EquiDigraph(graph));
		for (NodeIt nit(graph); nit!=lemon::INVALID; ++nit)
		{
			lemon::ListDigraph::Node equi = equi_digraph->graph.addNode();
			equi_digraph->newNodeRef.set(nit, equi);
			equi_digraph->oriNodeRef.set(equi, nit);
		}
		for (EdgeIt eit(graph); eit != lemon::INVALID; ++eit)
		{
			lemon::ListDigraph::Node u(equi_digraph->newNodeRef[graph.u(eit)]);
			lemon::ListDigraph::Node v(equi_digraph->newNodeRef[graph.v(eit)]);
			equi_digraph->graph.addArc(u, v);
			equi_digraph->graph.addArc(v, u);
		}
		return equi_digraph;
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
		Edge e = graph.addEdge(source, target);

		edge_id_map[e] = id;
		id_edges_map.insert(std::make_pair(id, e));

		return e;
	}

	int hasEdge(UnipaxId id)
	{
		return id_edges_map.count(id);
	}

	std::vector<Edge> getEdges(UnipaxId id)
	{
		std::vector<Edge> edges;

		for (EdgeMapEqualRange p = id_edges_map.equal_range(id); p.first != p.second; ++p.first)
		{
			edges.push_back(p.first->second);
		}

		return edges;
	}


	ProteinProteinInteractionNetwork & eraseProtein(UnipaxId id)
	{
		if (id_node_map.find(id) != id_node_map.end())
		{
			Graph::Node n = id_node_map.find(id)->second;

			for (Graph::IncEdgeIt it(graph, n); it != lemon::INVALID; ++it)
			{
				UnipaxId _id = edge_id_map[it];

				for (EdgeMapEqualRange p = id_edges_map.equal_range(_id); p.first != p.second; )
				{
					if (p.first->second == it)
					{
						id_edges_map.erase(p.first++);
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

	ProteinProteinInteractionNetwork &  eraseInteraction(UnipaxId id)
	{
		if (id_edges_map.find(id) != id_edges_map.end())
		{
			if (graph.valid(id_edges_map.find(id)->second))
				graph.erase(id_edges_map.find(id)->second);
			id_edges_map.erase(id);
		}

		return *this;
	}

	ProteinProteinInteractionNetwork & retainNodes(std::set<UnipaxId> nodes)
	{
		for (std::map<UnipaxId, Graph::Node>::iterator it = id_node_map.begin(); it != id_node_map.end();)
		{
			if (nodes.find(it->first) == nodes.end())
			{
				Graph::Node n = it->second;

				for (Graph::IncEdgeIt it2(graph, n); it2 != lemon::INVALID; ++it2)
				{
					UnipaxId _id = edge_id_map[it2];

					for (EdgeMapEqualRange p = id_edges_map.equal_range(_id); p.first != p.second; )
					{
						if (p.first->second == it2)
						{
							id_edges_map.erase(p.first++);
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

	ProteinProteinInteractionNetwork & removeNodes(std::set<UnipaxId> nodes)
	{
		for (std::map<UnipaxId, Graph::Node>::iterator it = id_node_map.begin(); it != id_node_map.end();)
		{
			if (nodes.find(it->first) != nodes.end())
			{
				Graph::Node n = it->second;

				for (Graph::IncEdgeIt it2(graph, n); it2 != lemon::INVALID; ++it2)
				{
					UnipaxId _id = edge_id_map[it2];

					for (EdgeMapEqualRange p = id_edges_map.equal_range(_id); p.first != p.second; )
					{
						if (p.first->second == it2)
						{
							id_edges_map.erase(p.first++);
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

	ProteinProteinInteractionNetwork & retainNodes(std::set<Graph::Node> nodes)
	{
		for (std::map<UnipaxId, Graph::Node>::iterator it = id_node_map.begin(); it != id_node_map.end();)
		{
			if (nodes.find(it->second) == nodes.end())
			{
				Graph::Node n = it->second;

				for (Graph::IncEdgeIt it2(graph, n); it2 != lemon::INVALID; ++it2)
				{
					UnipaxId _id = edge_id_map[it2];

					for (EdgeMapEqualRange p = id_edges_map.equal_range(_id); p.first != p.second; )
					{
						if (p.first->second == it2)
						{
							id_edges_map.erase(p.first++);
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

	ProteinProteinInteractionNetwork & removeNodes(std::set<Graph::Node> nodes)
	{
		for (std::map<UnipaxId, Graph::Node>::iterator it = id_node_map.begin(); it != id_node_map.end();)
		{
			if (nodes.find(it->second) != nodes.end())
			{
				Graph::Node n = it->second;

				for (Graph::IncEdgeIt it2(graph, n); it2 != lemon::INVALID; ++it2)
				{
					UnipaxId _id = edge_id_map[it2];

					for (EdgeMapEqualRange p = id_edges_map.equal_range(_id); p.first != p.second; )
					{
						if (p.first->second == it2)
						{
							id_edges_map.erase(p.first++);
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

	ProteinProteinInteractionNetwork & retainArcs(std::set<UnipaxId> arcs)
	{
		return retainEdges(arcs);
	}

	ProteinProteinInteractionNetwork & retainEdges(std::set<UnipaxId> arcs)
	{
		for (std::map<UnipaxId, Graph::Edge>::iterator it = id_edges_map.begin(); it != id_edges_map.end();)
		{
			if (arcs.find(it->first) == arcs.end())
			{
				Graph::Edge e = it->second;

				if (graph.valid(e))
					graph.erase(e);
				id_edges_map.erase(it++);
			}
			else
			{
				++it;
			}
		}

		return *this;
	}

	ProteinProteinInteractionNetwork & retainEdges(std::set<Graph::Edge> arcs)
	{
		for (std::map<UnipaxId, Graph::Edge>::iterator it = id_edges_map.begin(); it != id_edges_map.end();)
		{
			if (arcs.find(it->second) == arcs.end())
			{
				Graph::Edge e = it->second;

				if (graph.valid(e))
					graph.erase(e);
				id_edges_map.erase(it++);
			}
			else
			{
				++it;
			}
		}

		return *this;
	}

	ProteinProteinInteractionNetwork & removeArcs(std::set<UnipaxId> arcs)
	{
		return removeEdges(arcs);
	}

	ProteinProteinInteractionNetwork & removeEdges(std::set<UnipaxId> arcs)
	{
		for (std::map<UnipaxId, Graph::Edge>::iterator it = id_edges_map.begin(); it != id_edges_map.end();)
		{
			if (arcs.find(it->first) != arcs.end())
			{
				Graph::Edge e = it->second;

				if (graph.valid(e))
					graph.erase(e);
				id_edges_map.erase(it++);
			}
			else
			{
				++it;
			}
		}

		return *this;
	}

	ProteinProteinInteractionNetwork & removeEdges(std::set<Graph::Edge> arcs)
	{
		for (std::map<UnipaxId, Graph::Edge>::iterator it = id_edges_map.begin(); it != id_edges_map.end();)
		{
			if (arcs.find(it->second) != arcs.end())
			{
				Graph::Edge e = it->second;

				if (graph.valid(e))
					graph.erase(e);
				id_edges_map.erase(it++);
			}
			else
			{
				++it;
			}
		}

		return *this;
	}

	ProteinProteinInteractionNetwork & eraseDisconnectedNodes()
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

	template <typename T> ProteinProteinInteractionNetwork & filterNodes(Graph::NodeMap<T> & map, T value, bool retain_match = true)
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

	template <typename T, typename F> ProteinProteinInteractionNetwork & filterNodes(Graph::NodeMap<T> & map, T value, F f = F(), bool retain_match = true)
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

	template <typename T> ProteinProteinInteractionNetwork & filterEdges(Graph::EdgeMap<T> & map, T value, bool retain_match = true)
	{
		std::set<Graph::Edge> edges;

		for (Graph::EdgeIt it(graph); it != lemon::INVALID; ++it)
		{
			if (std::equal_to<T>(map[it], value))
			{
				edges.insert(it);
			}
		}

		if (retain_match)
			retainEdges(edges);
		else
			removeEdges(edges);

		return *this;
	}


	template <typename T, typename F> ProteinProteinInteractionNetwork & filterEdges(Graph::EdgeMap<T> & map, T value, F f = F(), bool retain_match = true)
	{
		std::set<Graph::Edge> edges;

		for (Graph::EdgeIt it(graph); it != lemon::INVALID; ++it)
		{
			if (f(map[it], value))
			{
				edges.insert(it);
			}
		}

		if (retain_match)
			retainEdges(edges);
		else
			removeEdges(edges);

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


	template<typename TV, template<class, class, class> class F> void mapEdgeData(Graph::template EdgeMap<TV> & targetEdgeDataMap, const F<typename Graph::Edge, UnipaxId, TV> & f)
	{
		for (Graph::EdgeIt it(graph); it != lemon::INVALID; ++it)
		{
			targetEdgeDataMap[it] = f(it, edge_id_map[it]);
		}
	}

	template<typename TV, typename MV, template<class, class, class> class F> void mapEdgeData(Graph::template EdgeMap<TV> & targetEdgeDataMap, Graph::template EdgeMap<MV> & mappingEdgeDataMap, const F<Graph::Edge, MV, TV> & f)
	{
		for (Graph::EdgeIt it(graph); it != lemon::INVALID; ++it)
		{
			targetEdgeDataMap[it] = f(it, mappingEdgeDataMap[it]);
		}
	}

};

typedef UnipaxPtr<ProteinProteinInteractionNetwork>::type ProteinProteinInteractionNetworkPtr;

}
}


#endif /* PROTEINPROTEININTERACTIONNETWORK_H_ */
