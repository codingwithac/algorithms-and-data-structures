#include "graph.hpp"
#include "union_find.hpp"
#include <vector>
#include <stdexcept>
#include <limits>
using namespace std;

// a data type to hold the results of Boruvka's MST algorithm
struct Result
{
    vector<Edge *> mst;
    double mstCost;
};

/**
 * A class that implements the Boruvka algorithm to find a minimum spanning tree in a graph.
 * This implementation uses the UnionFind data structure to associate vertex indices with 
 * MST subtrees as they are built.
 * Each phase corresponds to checking all the remaining edges; those that connect vertices in
 * different components are kept for the next phase.

*/
class Boruvka
{
    // a vector that will contain edges not yet discarded & not yet in the MST
    vector<Edge *> edges;

    // a vector that will contain the MST edges
    vector<Edge *> mstEdges;

    // a vector that will save the nearest neighbor
    vector<Edge *> nearestNeighbor;

    // a pointer to an UnionFind object
    // we will use this data structure to know whether or not two given vertices are in the same MST subtree
    // and to unify them if they are not
    UnionFind *uf;

    // holds the number of graph vertices
    int vertices;

    // holds the total MST cost
    double mstCost;

public:
    // constructor: takes the vector of edges representing the graph & the number of vertices
    Boruvka(vector<Edge *> edges, int vertices) : edges{edges}, vertices{vertices}
    {
        // sanity check
        if (edges.size() == 0)
            throw invalid_argument{"Invalid argument: no edges in the graph."};

        if (vertices == 0)
            throw invalid_argument{"Invalid argument: no vertices in the graph."};

        // initialize UnionFind pointer
        uf = new UnionFind(vertices);
    }

    // apply Boruvka's algorithm to find the MST
    Result boruvka()
    {
        // store the number of edges
        int numberOfEdges = edges.size();

        // used to store the number of edges being saved for the next phase
        int edgesForNextPhase;

        // index e is used to access the next edge to be checked
        int e;

        // loop as long as we have edges that connect different MST subtrees
        while (numberOfEdges != 0)
        {
            // fill the nearest neighbor vector with a default edge
            // this vector identifies the nearest neighbor for each MST subtree
            nearestNeighbor.assign(vertices, new Edge(new Vertex(-1), new Vertex(-1), numeric_limits<double>::max()));

            // for each edge in the graph:
            //      - if current edge connects vertices in same MST, discard it
            //      - otherwise, check the nearest neighbor distances between the two MST subtrees
            //        that the current edge connects and update them if appropriate
            for (e = 0, edgesForNextPhase = 0; e < numberOfEdges; e++)
            {
                // get root of the first vertex incident on the current edge
                int rootV = uf->find(edges.at(e)->getV()->getId());
                // get root of the first vertex incident on the current edge
                int rootW = uf->find(edges.at(e)->getW()->getId());

                // check if their roots are the same, they belong to the same MST subtree
                if (rootV == rootW)
                    continue;

                // update the nearest neighbor of the MST subtree to which 'rootV' belongs to if we have to
                if (edges.at(e)->getWeight() < nearestNeighbor.at(rootV)->getWeight())
                    nearestNeighbor[rootV] = edges.at(e);

                // update the nearest neighbor of the MST subtree to which 'rootW' belongs to if we have to
                if (edges.at(e)->getWeight() < nearestNeighbor.at(rootW)->getWeight())
                    nearestNeighbor[rootW] = edges.at(e);

                // note: edges that connect vertices in different components are kept for the next phase
                edges[edgesForNextPhase++] = edges[e];
            }

            // unify MST subtrees & add edge to MST
            for (const auto edge : nearestNeighbor)
            {
                // get id of current edge's first vertex
                int v = edge->getV()->getId();
                // get id of current edge's second vertex
                int w = edge->getW()->getId();

                // if they do not belong to the same MST subtree
                if ((v != -1) && (!uf->connected(v, w)))
                {
                    // unify MST subtrees
                    uf->unify(v, w);
                    // add edge to mst
                    mstEdges.push_back(edge);

                    // add cost to mstCost
                    mstCost += edge->getWeight();
                }
            }

            // we reset the number of edges from edgesForNextPhase at the end of each phase
            numberOfEdges = edgesForNextPhase;
        }

        // return the result (mst edges & total cost) to the caller
        return Result{mstEdges, mstCost};
    }
};
