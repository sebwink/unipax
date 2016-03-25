/*
 * RelationsGraph.h
 *
 *  Created on: Mar 8, 2012
 *      Author: gerasch
 */

#ifndef RELATIONSGRAPH_H_
#define RELATIONSGRAPH_H_

#include <UNIPAX/COMMON/common.h>

#include <lemon/list_graph.h>
#include <lemon/maps.h>

#include <boost/shared_ptr.hpp>

#include <set>
#include <string>

namespace UniPAX
{
namespace GRAPH
{
class UNIPAX_EXPORT RelationsGraph
{

public:

	typedef lemon::ListDigraph Graph;
	typedef Graph::Arc Edge;
	typedef Graph::Node Node;
	typedef Graph::ArcIt EdgeIt;
	typedef Graph::NodeIt NodeIt;

	Graph graph;
	Graph::ArcMap<std::string> relationMap;
	Graph::NodeMap<UnipaxId> idMap;

	std::map<UnipaxId, Node> nodeMap;

	RelationsGraph() : graph(), relationMap(graph), idMap(graph), nodeMap() {}


	RelationsGraph(RelationsGraph & copy) : graph(), relationMap(graph), idMap(graph), nodeMap()
	{
		lemon::digraphCopy(copy.graph, graph).arcMap(copy.relationMap, relationMap).nodeMap(copy.idMap, idMap).run();

		for (NodeIt it(graph); it != lemon::INVALID; ++it)
		{
			nodeMap[idMap[it]] = it;
		}
	}
};
}
}


#endif /* RELATIONSGRAPH_H_ */
