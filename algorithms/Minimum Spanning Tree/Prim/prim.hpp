/**
 * A program implementing Prim's algorithm to find the minimum spanning tree (MST) of a graph.
 * 
 * The Prim's algorithm works as follows: 
 * Attach a new edge to a single growing tree at step. Start with any vertex as a single-vertex
 * tree; then add V-1 edges to it, always taking next the minimum weight edge that connects a 
 * vertex on the tree to a vertex not yet on the tree (a crossing edge for the cut defined by 
 * tree vertices).
 * 
 * This implementation of the Prim's algorithm uses an index priority queue. The minimum index
 * priority queue helps us to take the minimum key on the priority queue which is the weight of 
 * the minimal-weigth crossing edge & its associated vertex 'v' is the next to add to the tree.
 * 
 * 
*/

#include "graph.hpp"
#include "minIndexedPQ.hpp"
#include <vector>
#include <limits>
#include <iostream>
using namespace std;

class Prim
{
    // a reference to our graph
    Graph &graph;

    // a vertex-indexed vector to hold the distance to the closest tree vertex for each non-tree vertex
    // for example: "closestDist[w] = distance" tells us the current shortest 'distance' (or smallest weight) connecting a non-vertex 'w' to a tree vertex
    vector<double> closestDist;

    // vertex-indexed vector to hold the index of the closest tree vertex for each non-tree vertex
    // for example: "closestVertex[w] = v" tells us that 'v' is the closest tree vertex for the non-tree vertex 'w'
    vector<int> closestVertex;

    // vertex-indexed vector to keep track of the vertices already in the MST
    // for example: marked[v] = true if 'v' is a tree vertex
    vector<bool> marked;

    // a reference to the min index PQ
    MinIndexedPQ<double> *ipq;

    // a vertex-indexed vector to keep track of the vertices that belong to the MST
    // for example: "mst[v] = w" tells us that we go to vertex 'v' from 'w'
    vector<int> mst;

    // holds the total weight (or cost) of the MST
    double totalWeight;

public:
    Prim(Graph &graph) : graph{graph}, totalWeight{0}
    {
        // initialize the closest distance vector
        closestDist.assign(graph.getVertices(), numeric_limits<double>::max());

        // initialize the closest edge to tree vector
        closestVertex.assign(graph.getVertices(), -1);

        // initialize the marked vector with false
        marked.assign(graph.getVertices(), false);

        // initialize the mst vector
        mst.assign(graph.getVertices(), -1);

        // initialize indexed PQ
        ipq = new MinIndexedPQ<double>(graph.getVertices());
    }

    // public method that finds the MST using Prim's algorithm
    void prim(int startingVertexId)
    {
        // closest distance to the starting vertex is 0.0
        closestDist[startingVertexId] = 0.0;

        // closest vertex id of the starting vertex
        closestVertex[startingVertexId] = startingVertexId;

        // insert starting vertex with priority 0.0 into ipq
        ipq->insert(startingVertexId, 0.0);

        // as long as the index PQ is not empty
        while (!ipq->isEmpty())
        {
            // get the id of the vertex with the highest priority (smallest weight)
            auto minVertexId = ipq->deleteMinKeyIndex();

            // add tree vertex
            mst[minVertexId] = closestVertex[minVertexId];

            // mark "minVertexId"; indicates that vertex with ID 'minVertexId' is now in the MST
            marked[minVertexId] = true;

            // add weight to total sum
            totalWeight += closestDist[minVertexId];

            // get the adjacency list of 'minVertexId'
            auto adjList = graph.getAdjLists()[minVertexId];

            // scan through the edges incident on minVertexId
            for (const auto edge : adjList)
            {
                // get its adjacent vertex id
                auto adjVertexId = edge->getAdjVertexId();
                // if "adjVertexId" already in the MST, we can skip it
                if (marked[adjVertexId])
                    continue;

                // get the weight on the edge to the adjacent vertex
                auto weight = edge->getWeight();

                // check if "minVertexId" brings "adjVertex" closer to the tree
                if (weight < closestDist[adjVertexId])
                {
                    // update the closest distance to the tree for "adjVertexId"
                    closestDist[adjVertexId] = weight;

                    // update the closest tree vertex of "adjVertexId"
                    closestVertex[adjVertexId] = minVertexId;

                    // if a vertex with id 'adjVertexId' is already in the index PQ
                    if (ipq->contains(adjVertexId))
                        // then we have to update its weight value
                        ipq->change(adjVertexId, closestDist[adjVertexId]);
                    else
                        // otherwise, insert it with its weight for the first time
                        ipq->insert(adjVertexId, closestDist[adjVertexId]);
                }
            }
        }
    }

    // public method to print the results to the console
    void getResults()
    {
        for (int vertexId{}; vertexId < mst.size(); vertexId++)
            cout << "We go to vertex " << vertexId << " from " << mst[vertexId] << " with weight " << closestDist[vertexId] << "." << endl;

        cout << endl;
        cout << "The total weight of the MST is: " << totalWeight << endl;
    }
};
