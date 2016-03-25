/*
 * test_RecuriveEnumerationAlgorithm.cpp
 *
 *  Created on: Nov 26, 2013
 *      Author: niermann
 */


#include <UNIPAX/GRAPH/LEMON/RecursiveEnumerationAlgorithm.h>
#include <lemon/list_graph.h>
#include <boost/shared_ptr.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <exception>
#include <iostream>

class TestREA : public ::testing::Test
{
	public:
		TestREA()
		{
		}

		virtual ~TestREA() {}

	protected:
		virtual void SetUp()
		{
			// create Graph

			s = graph.addNode();
			lemon::ListDigraph::NodeIt a(graph, graph.addNode());
			graph.addArc(s, a);
			lemon::ListDigraph::NodeIt a2(graph, a);
			for (int i=0; i!=3; ++i)
			{
				lemon::ListDigraph::NodeIt b(graph, graph.addNode());
				lemon::ListDigraph::NodeIt b2(graph, graph.addNode());
				graph.addArc(a, b);
				graph.addArc(a2, b2);
				a = b;
				a2 = b2;
			}
			t = graph.addNode();
			graph.addArc(a, t);
			graph.addArc(a2, t);
			graph.addArc(s, t);
		}

		virtual void TearDown()
		{
		}

		typedef boost::shared_ptr<lemon::KShortestPath::RecursiveEnumeration<lemon::ListDigraph> > REAPtr;
		//REAPtr rea;
		lemon::ListDigraph graph;
		lemon::ListDigraph::Node s, t;
};

TEST_F(TestREA, run)
{
	lemon::ListDigraph::ArcMap<int> lengths(graph, 1);
	REAPtr rea	(new lemon::KShortestPath::RecursiveEnumeration<lemon::ListDigraph>(graph, lengths));
	unsigned int num_paths = 3;

	ASSERT_TRUE(rea->run(s, t, num_paths)) << "k-shortest path search did not work out.";
	ASSERT_TRUE(rea->reached(t)) << "No path from s to t found.";
	ASSERT_TRUE(rea->negativeCycle().empty()) << "Negative cycle found.";

	size_t numOfPaths = rea->getKPaths(t).size();
	ASSERT_EQ(num_paths, numOfPaths) << "Found " << numOfPaths << " paths instead of " << num_paths << ".";
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

