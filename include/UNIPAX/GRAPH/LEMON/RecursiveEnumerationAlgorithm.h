#ifndef RECURSIVEENUMERATIONALGORITHM_H_
#define RECURSIVEENUMERATIONALGORITHM_H_

// Implemented following the publication of V. M. Jimenez & A. Marzal:
// Computing the K Shortest Paths: A New Algorithm and an Experimental Comparison,
// Springer-Verlag Berlin Heidelberg 1999

#include <lemon/concepts/digraph.h>
#include <lemon/bellman_ford.h>
#include <boost/shared_ptr.hpp>
#include <stdexcept>

namespace lemon {

namespace KShortestPath {

#ifdef DOXYGEN
template <typename GR, typename LEN, typename TR>
#else
template <typename GR=ListDigraph,
typename LEN=typename GR::template ArcMap<int>,
typename TR=BellmanFordDefaultTraits<GR,LEN> >
#endif
class ShortestPathLinks
{
public:
	///The type of the underlying digraph.
	typedef typename TR::Digraph Digraph;

	/// \brief The type of the arc lengths.
	typedef typename TR::LengthMap::Value Value;
	/// \brief The type of the map that stores the arc lengths.
	typedef typename TR::LengthMap LengthMap;
	/// \brief The type of the map that stores the last
	/// arcs of the shortest paths.
	typedef typename TR::PredMap PredMap;
	/// \brief The type of the map that stores the distances of the nodes.
	typedef typename TR::DistMap DistMap;
	/// The type of the paths.
	typedef PredMapPath<Digraph, PredMap> Path;
	/// The \ref BellmanFordDefaultTraits "traits class" of the algorithm.
	typedef TR Traits;

	typedef typename Digraph::Node Node;
	typedef typename Digraph::NodeIt NodeIt;
	typedef typename Digraph::Arc Arc;
	typedef typename Digraph::ArcIt ArcIt;
	typedef typename Digraph::template NodeMap<size_t> NodeIndexMap;

	/*ShortestPathLinks() //:
		//path_links(0),
		//path_lengths(0),
		//idx_node(0),
		//k_size(0)
	{}*/

	/**
	 * Creates a ShortestPathLinks object for the given Digraph, DistMap and number of shortest paths (k)
	 */
	ShortestPathLinks(const Digraph & g, const unsigned int k) :
		//path_links(0),
		//path_lengths(0),
		node_idx(g),
		node_end_idx(g),
		//idx_node(0, NodeIt(INVALID)),
		k_size(k),
		graph(&g)
	{
		init();
	}

	~ShortestPathLinks()
	{}

	/**
	 * Sets a link for arc (u, v) with weight val to u on the k-th shortest path
	 */
	void setLink(const Arc & a, const unsigned int k_pred, const Value val)
	{
		Node u = graph->source(a);
		Node v = graph->target(a);
		size_t idx = node_end_idx[v];
		if (idx > node_idx[v] + k_size -1)
		{
			throw std::out_of_range("ShortestPathLinks::setLink: More than k links can not be set.");
		}
		if (k_pred > k_size)
		{
			throw std::invalid_argument("ShortestPathLinks::setLink: k_pred is bigger than k_size.");
		}
		path_links.at(idx) = node_idx[u] + k_pred-1;
		path_lengths.at(idx) = val;
		arc_links.at(idx) = ArcIt(*graph, a);
		node_end_idx.set(v, idx+1);
	}

	/**
	 * Gets the predecessor of node v on the k-th shortest path
	 */
	Node getPredecessor(const Node v, const unsigned int k) const
	{
		size_t idx = node_idx[v] + k-1;
		if (idx >= node_end_idx[v])
		{
			throw std::out_of_range("ShortestPathLinks::getPredecessor: parameter k is to large.");
		}
		return idx_node.at(path_links.at(idx) / k_size);
	}

	/**
	 * Gets the path number of predecessor of node v on the k-th shortest path
	 */
	unsigned int getPredecessorK(const Node v, const unsigned int k) const
	{
		size_t idx = node_idx[v] + k-1;
		if (idx >= node_end_idx[v])
		{
			throw std::out_of_range("ShortestPathLinks::getPredecessorK: parameter k is to large.");
		}
		return 1 + (path_links.at(idx) % k_size);
	}

	/**
	 * Gets the distance of node v to the source on the k-th shortest path
	 */
	Value getDistance(const Node v, const unsigned int k) const
	{
		size_t idx = node_idx[v] + k-1;
		if (idx >= node_end_idx[v])
		{
			throw std::out_of_range("ShortestPathLinks::getDistance: parameter k is to large.");
		}
		return path_lengths.at(idx);
	}

	/**
	 * Gets the arc of node v to the predecessor on the k-th shortest path
	 */
	Arc getArc(const Node v, const unsigned int k) const
	{
		size_t idx = node_idx[v] + k-1;
		if (idx >= node_end_idx[v])
		{
			throw std::out_of_range("ShortestPathLinks::getArc: parameter k is to large.");
		}
		return arc_links.at(idx);
	}

	/**
	 * Returns true if node v has an link for the k-th shortest path
	 */
	bool exists(const Node v, const unsigned int k) const
	{
		size_t idx = node_idx[v] + k-1;
		if (idx < node_end_idx[v])
		{
			return true;
		}
		return false;
	}

	/**
	 * Returns the number of shortest Paths that are available ending at Node t
	 */
	size_t numPaths(const Node v) const
	{
		return node_end_idx[v] - node_idx[v];
	}

protected:

	/**
	 * Initializes the ShortestPathLinks object for the given Digraph, DistMap and number of shortest paths (k)
	 */
	void init()
	{
		int num = lemon::countNodes(*graph);
		path_links.assign(num * k_size, 0);
		path_lengths.assign(num * k_size, 0);
		arc_links.assign(num * k_size, INVALID);
		idx_node.assign(num, INVALID);

		size_t idx = 0;
		for (NodeIt nit(*graph); nit != INVALID; ++nit)
		{
			node_idx.set(nit, idx * k_size);
			node_end_idx.set(nit, idx * k_size);
			idx_node.at(idx) = nit;
			++ idx;
		}
	}

	// path_links and path_lengths are of size n*k
	// access in form: idx_base * k + (k-1)
	std::vector<size_t> path_links; // stores the index of the pred. node link on the k-th shortest path
	std::vector<Value> path_lengths; // stores the distance from node s to v on the k-th shortest path
	std::vector<ArcIt> arc_links; // stores a link to the actual arc in the graph (needed to distinguish arcs of equal length)

	NodeIndexMap node_idx; // stores the index base of each node in path_links and path_lengths
	NodeIndexMap node_end_idx; // stores the index after the last valid entry
	std::vector<NodeIt> idx_node; // stores the nodes to each index base
	unsigned int k_size; // number of paths to search

	const 	Digraph* graph;
};

#ifdef DOXYGEN
template <typename GR, typename LEN, typename TR>
#else
template <typename GR=ListDigraph,
typename LEN=typename GR::template ArcMap<int>,
typename TR=BellmanFordDefaultTraits<GR,LEN> >
#endif
class RecursiveEnumeration
{
public:

	///The type of the underlying digraph.
	typedef typename TR::Digraph Digraph;

	/// \brief The type of the arc lengths.
	typedef typename TR::LengthMap::Value Value;
	/// \brief The type of the map that stores the arc lengths.
	typedef typename TR::LengthMap LengthMap;
	/// \brief The type of the map that stores the last
	/// arcs of the shortest paths.
	typedef typename TR::PredMap PredMap;
	/// \brief The type of the map that stores the distances of the nodes.
	typedef typename TR::DistMap DistMap;
	/// The type of the paths.
	typedef Path<Digraph> KPath;
	/// The \ref BellmanFordDefaultTraits "traits class" of the algorithm.
	typedef TR Traits;

	typedef typename Digraph::Node Node;
	typedef typename Digraph::NodeIt NodeIt;
	typedef typename Digraph::Arc Arc;
	typedef typename Digraph::ArcIt ArcIt;
	typedef typename Digraph::OutArcIt OutArcIt;
	typedef typename Digraph::InArcIt InArcIt;

	RecursiveEnumeration(const Digraph &g, const LengthMap &length) :
		sp_algo(g, length),
		lengths(&length),
		nodes_candidateSets(g),
		done(false),
		graph(&g)
	{
		//lemon::digraphCopy(g, graph);
	}

	~RecursiveEnumeration()
	{}

	/**
	 * Executes the recursive enumeration of k shortest paths between nodes s and t.
	 */
	bool run(Node s, Node t, unsigned int k)
	{
		if (k == 0) return true;
		// execute the Bellman-Ford algorithm to compute 1-SP and all distances
		source = NodeIt(*graph, s);
		target = NodeIt(*graph, t);

		sp_algo.init(std::numeric_limits<Value>::max());

		sp_algo.addSource(source);
		if (!sp_algo.checkedStart()) return false; // iff negative cycle was found
		if (!sp_algo.reached(target)) return false; // iff t not reachable from s
		// initialize data structures
		{
			lemon::InDegMap<Digraph> indegree(*graph);
			for (NodeIt nit(*graph); nit != INVALID; ++nit)
			{
				CandidateSet c;
				c.reserve(indegree[nit]);
				nodes_candidateSets[nit] = c;
			}
		}
		nodes_pathLinks.reset(new ShortestPathLinks<GR, LEN, TR>(*graph, k));
		initPathLinks(source);

		// calculate k-shortest paths
		recursiveEnumeration(k);
		return true;
	}

	/**
	 * Returns a directed cycle with negative total length from the graph if any is found or an empty path.
	 */
	lemon::Path<Digraph> negativeCycle() const
			{
		return sp_algo.negativeCycle();
			}

	/**
	 * Returns true if the node t is reachable from s.
	 */
	bool reached(Node & t) const
	{
		return sp_algo.reached(t);
	}

	/**
	 * Returns the list of <= k calculated shortest paths between s and t.
	 */
	std::vector<KPath> getKPaths(Node v) const
	{
		unsigned int k_size = nodes_pathLinks->numPaths(v);
		std::vector<KPath> k_paths;
		k_paths.reserve(k_size);
		for (unsigned int k=1; k != k_size+1; ++k)
		{
			KPath p;
			Node u = v;
			unsigned int k_pos = k;
			unsigned int k_tmp;
			while (u != source)
			{
				p.addFront(nodes_pathLinks->getArc(u, k_pos));
				k_tmp = nodes_pathLinks->getPredecessorK(u, k_pos);
				u = nodes_pathLinks->getPredecessor(u, k_pos);
				k_pos = k_tmp;
			}
			k_paths.push_back(p);
		}
		return k_paths;
	}


protected:

	typedef std::vector<std::pair<ArcIt, size_t> > CandidateSet;

	void initPathLinks(NodeIt & v)
	{
		if (v != source)
		{
			nodes_pathLinks->setLink(sp_algo.predArc(v), 1, sp_algo.dist(v));
		}
		for (OutArcIt a(*graph, v); a!=INVALID; ++a)
		{
			NodeIt target(*graph, graph->runningNode(a));
			if (sp_algo.predArc(target) == a)
			{
				initPathLinks(target);
			}
		}
	}

	void recursiveEnumeration(unsigned int k)
	{
		if (k == 1) return; // first path is already calculated!
		unsigned int tmp_k = 2;
		done = false;
		while(!done)  // A.2
		{
			nextPath(target, tmp_k);
			if (tmp_k == k) done = true; // k paths iterated
			++tmp_k;
		}
	}

	void nextPath(const NodeIt v, unsigned int k)
	{
		if (k == 2) // init set of candidates (B.1)
		{
			for (InArcIt a(*graph, v); a!=INVALID; ++a)
			{
				if (sp_algo.predArc(v) != a)
				{
					nodes_candidateSets[v].push_back(std::pair<ArcIt, size_t>(ArcIt(*graph, a), 1)); // only path k==1 has been calculated
				}
			}
		}
		if (v != source || k != 2) //(B.2)
		{
			NodeIt u(*graph, nodes_pathLinks->getPredecessor(v, k-1)); // (B.3)
			unsigned int k_prime = nodes_pathLinks->getPredecessorK(v, k-1);
			if (!nodes_pathLinks->exists(u, k_prime + 1)) // (B.4)
			{
				nextPath(u, k_prime + 1);
			}
			if (nodes_pathLinks->exists(u, k_prime + 1)) // (B.5)
			{
				nodes_candidateSets[v].push_back(std::pair<ArcIt, size_t>(ArcIt(*graph, nodes_pathLinks->getArc(v, k-1)), k_prime + 1));
			}
		}
		// (B.6)
		// If existing delete min path from nodes_candidateSets[v] and insert it into pathLinks
		if (!nodes_candidateSets[v].empty())
		{
			CandidateSet* c = &nodes_candidateSets[v];
			size_t min_idx = 0;
			ArcIt min_a(*graph, c->at(min_idx).first);
			NodeIt tmp_u(*graph, graph->source(min_a));
			unsigned int tmp_k = c->at(min_idx).second;
			Value min_length = (*lengths)[min_a];
			if (tmp_u != source)
			{
				min_length += nodes_pathLinks->getDistance(tmp_u, tmp_k);
			}
			for (size_t idx = 0; idx != c->size(); ++idx)
			{
				ArcIt tmp_a(*graph, c->at(idx).first);
				tmp_u = NodeIt(*graph, graph->source(tmp_a));
				tmp_k = c->at(idx).second;
				Value tmp_length = (*lengths)[tmp_a];
				if (tmp_u != source)
				{
					tmp_length += nodes_pathLinks->getDistance(tmp_u, tmp_k);
				}
				if (tmp_length < min_length)
				{
					min_length = tmp_length;
					min_idx = idx;
					min_a = tmp_a;
				}
			}
			nodes_pathLinks->setLink(min_a, c->at(min_idx).second, min_length);
			c->erase(c->begin() + min_idx);
		}
	}

	const Digraph* graph;
	const LengthMap* lengths;
	NodeIt source;
	NodeIt target;
	typename Digraph::template NodeMap<CandidateSet> nodes_candidateSets;
	boost::shared_ptr<ShortestPathLinks<GR, LEN, TR> > nodes_pathLinks;

	BellmanFord<GR, LEN, TR> sp_algo;
	//NodeMap<std::vector<Path> > nodes_k_paths; // should be implicit!!!
	bool done;
};

} // end of namespace

} // end of namespace

//#include <UNIPAX/GRAPH/LEMON/RecursiveEnumerationAlgorithm.tpp>

#endif /* RECURSIVEENUMERATIONALGORITHM_H_ */
