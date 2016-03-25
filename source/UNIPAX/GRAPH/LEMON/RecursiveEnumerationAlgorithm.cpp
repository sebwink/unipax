#include <UNIPAX/GRAPH/LEMON/RecursiveEnumerationAlgorithm.h>

void lemon::KShortestPath::ShortestPathLinks::init(Digraph g, unsigned int k)
{
	int num = lemon::countNodes(g);
	path_links.assign(num * k, 0);
	path_lengths.assign(num * k, 0);
	arc_links.assign(num * k, INVALID);
	if (idx_node.size() != 0) // re-initialization
	{
		node_idx = NodeMap<size_t>(g);
		node_end_idx = NodeMap<size_t>(g);
		k_size = k;
		graph = g;
	}
	idx_node.assign(num, INVALID);

	size_t idx = 0;
	for (Digraph::NodeIt nit(g); nit != INVALID; ++nit)
	{
		node_idx.set(*nit, idx * k);
		node_end_idx.set(*nit, idx * k);
		++ idx;
	}
}

void lemon::KShortestPath::ShortestPathLinks::setLink(Arc a, unsigned int k, Value val)
{
	Node u = graph.source(a);
	Node v = graph.target(a);
	size_t idx = node_idx[v] * k_size + k-1;
	if (idx > node_end_idx[v])
	{
		throw std::invalid_argument("k = " + k);
	}
	path_links.insert(idx , node_idx[u] * k_size + k-1);
	path_lengths.insert(idx, val);
	arc_links.insert(Digraph::ArcIt(a));
	if (idx == node_end_idx[v])
	{
		node_end_idx.set(v, node_end_idx[v] = idx+1);
	}
}



lemon::KShortestPath::RecursiveEnumeration::RecursiveEnumeration(const Digraph &g, const LengthMap &length) :
	graph(g),
	sp_algo(g, length),
	nodes_candidateSets(g),
	done(false)
{
}

lemon::KShortestPath::RecursiveEnumeration::~RecursiveEnumeration()
{
}

bool lemon::KShortestPath::RecursiveEnumeration::run(Node s, Node t, unsigned int k)
{
		if (k == 0) return true;
		// execute the Bellman-Ford algorithm to compute 1-SP and all distances
		source = s;
		target = t;
		sp_algo.init();
		sp_algo.addSource(source);
		if (!sp_algo.checkedStart()) return false; // iff negative cycle was found
		if (!reached(target)) return false; // iff t not reachable from s
		// initialize data structures
		{
			lemon::InDegMap<Digraph> indegree(graph);
			for (NodeIt nit(graph); nit != INVALID; ++nit)
			{
				nodes_candidateSets[*nit] = CandidateSet(indegree[*nit]);
			}
		}
		nodes_pathLinks.init(graph, k);
		initPathLinks(source);

		// calculate k-shortest paths
		recursiveEnumeration(k);
		return true;
}

void lemon::KShortestPath::RecursiveEnumeration::initPathLinks(NodeIt v)
{
	if (v != source)
	{
		nodes_pathLinks.setLink(sp_algo.predArc(v), 1, sp_algo.dist(v));
	}
	for (Digraph::OutArcIt a(graph, v); a!=INVALID; ++a)
	{
			if (sp_algo.predNode(graph.runningNode(a)) == v)
			{
					initPathLinks(graph.baseNode(a));
			}
	}
}


std::vector<lemon::KShortestPath::RecursiveEnumeration::Path> lemon::KShortestPath::RecursiveEnumeration::getKPaths(Node v) const
{
	unsigned int k_size = nodes_pathLinks.numPaths(v);
	std::vector<Path> k_paths(k_size);
	for (unsigned int k=1; k != k_size+1; ++k)
	{
		Path p;
		Node u = v;
		while (u != source)
		{
			p.addFront(nodes_pathLinks.getArc(u, k));
			u = nodes_pathLinks.getPredecessor(u, k);
		}
		k_paths.push_back(p);
	}
	return k_paths;
}

void lemon::KShortestPath::RecursiveEnumeration::recursiveEnumeration(unsigned int k_size)
{
	if (k_size == 1) return; // first path is already calculated!
	unsigned int k = 2;
	done = false;
	while(!done)  // A.2
	{
			nextPath(target, k);
			if (k == k_size) done = true; // k paths iterated
			++k;
	}
}

void lemon::KShortestPath::RecursiveEnumeration::nextPath(const Node v, unsigned int k)
{
	if (k == 2) // init set of candidates (B.1)
	{
		for (Digraph::InArcIt a(graph, v); a!=INVALID; ++a)
		{
			Node u = graph.baseNode(*a);
			if (sp_algo.predNode(v) != u)
			{
				nodes_candidateSets[v].push_back(std::pair<ArcIt, size_t>(a, 1)); // only path k==1 has been calculated
			}
		}
	}
	if (v != source || k != 2) //(B.2)
	{
			Node u = nodes_pathLinks.getPredecessor(v, k-1); // (B.3)
			unsigned int k_prime = nodes_pathLinks.getPredecessorK(v, k-1);
			if (!nodes_pathLinks.exists(u, k_prime + 1)) // (B.4)
			{
				nextPath(u, k_prime + 1);
			}
			if (nodes_pathLinks.exists(u, k_prime + 1)) // (B.5)
			{
				nodes_candidateSets[v].push_back(std::pair<ArcIt, size_t>(nodes_pathLinks.getArc(v, k-1), k_prime + 1));
			}
	}
	// (B.6)
	// If existing delete min path from nodes_candidateSets[v] and insert it into pathLinks
	if (!nodes_candidateSets[v].empty())
	{
		CandidateSet c = nodes_candidateSets[v];
		size_t min_idx = 0;
		Arc min_a = *c.at(min_idx).first;
		Node tmp_u = graph.source(min_a);
		unsigned int tmp_k = c.at(min_idx).second;
		Value min_length = sp_algo.lengthMap[min_a] + nodes_pathLinks.getDistance(tmp_u, tmp_k);
		for (size_t idx = 1; idx < c.size(); ++idx)
		{
				Arc tmp_a = *c.at(idx).first;
				tmp_u = graph.source(tmp_a);
				tmp_k = c.at(idx).second;
				Value tmp_length = sp_algo.lengthMap[tmp_a] + nodes_pathLinks.getDistance(tmp_u, tmp_k);
				if (tmp_length < min_length)
				{
					min_length = tmp_length;
					min_idx = idx;
					min_a = tmp_a;
				}
		}
		nodes_pathLinks.setLink(min_a, min_idx, min_length);
		c.erase(c.begin() + min_idx);
	}
}
