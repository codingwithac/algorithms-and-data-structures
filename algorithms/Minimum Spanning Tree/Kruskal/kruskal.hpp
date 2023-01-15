#include "graph.hpp"
#include "union_find.hpp"
#include <queue>

using namespace std;

/**
 * A program implementing Kruskal's algorithm to find the minimum spanning tree (MST) of a graph.
 * 
*/

class Kruskal
{
    // a reference to our graph on which we are going to apply Kruskal's algorithm
    Graph &graph;

    // a queue that will hold the MST edges
    queue<Edge *> mstEdges;

    // a min PQ will be used so that edges can be taken out in order by weight (from smallest to largest)
    priority_queue<Edge *, vector<Edge *>, Edge> minPQ;

    // a UnionFind implementation used to identify vertices that cause cycles
    UnionFind *uf;

    // a variable holding the total cost of the MST
    double totalWeight;

public:
    // constructor
    Kruskal(Graph &graph) : graph{graph}, totalWeight{0}
    {
        // initialize UnionFind
        uf = new UnionFind(graph.getVertices());

        // populate the minPQ with all edges
        for (int v{}; v < graph.getVertices(); v++)
        {
            // get list of vertices adjacent to v
            auto adjList = graph.getAdjLists()[v];

            for (const auto adjVertex : adjList)
            {
                auto edgeToInsert = new Edge(new Vertex{v}, new Vertex{adjVertex->getAdjVertexId()}, adjVertex->getWeight());
                // build an edge & put it into the min PQ
                minPQ.emplace(edgeToInsert);
            }
        }
    }

    // method that applies Kruskal's MST
    void kruskal()
    {
        // loop as long we have edges & size of the queue holding the MST edges is under V-1
        while (!minPQ.empty() && mstEdges.size() < graph.getVertices() - 1)
        {
            // get the edge with the lowest weight
            auto minEdge = minPQ.top();
            minPQ.pop();

            // extract its vertices
            auto v = minEdge->getV()->getId();
            auto w = minEdge->getW()->getId();

            // if its vertices are not connected
            if (uf->connected(v, w))
                continue;

            // connect them, they are now vertices that belong to the MST
            uf->unify(v, w);

            // add this edge to the MST
            mstEdges.push(minEdge);

            // add weight to cost
            totalWeight += minEdge->getWeight();
        }
    }

    // method to print the result of Kruskal's MST algorithm
    void printResult()
    {
        while (!mstEdges.empty())
        {
            auto edge = mstEdges.front();
            mstEdges.pop();

            cout << "(" << edge->getV()->getId() << "," << edge->getW()->getId() << ") with weight " << edge->getWeight() << endl;
        }

        cout << "The total cost is of the MST is " << totalWeight << endl;
    }
};
