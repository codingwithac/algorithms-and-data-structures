#include <vector>
#include <iostream>
using namespace std;

/* A class implementing the node we add to the adjacency list */
class Node
{
    // represents the adjacent vertex
    int adjVertexId;

    // a double value representing the weight on the edge incident on this vertex
    double weight;

public:
    // constructor
    Node(int adjVertexId, double weight) : adjVertexId{adjVertexId}, weight{weight} {}

    // getter to obtain 'adjVertexId' value
    int getAdjVertexId() { return this->adjVertexId; }

    // getter to obtain 'weight' value
    double getWeight() { return this->weight; }
};

/* A class implementing the vertex used in a graph */
class Vertex
{
    // holds the id of this vertex
    int id;

public:
    // constructor
    Vertex(int id) : id{id} {}

    // getter to obtain the id of this vertex
    int getId() { return this->id; }
};

/**
 * A class implementing an edge used in undirected graphs. Such an edge consists of 
 * two vertices that we denote as v and w, respectively.
 * 
*/
class Edge
{
    // a pointer to the first vertex of this edge
    Vertex *v;
    // a pointer to the second vertex of this edge
    Vertex *w;
    // a double value representing the weight associated with the edge
    double weight;

public:
    // constructor
    Edge(Vertex *v, Vertex *w, double weight) : v{v}, w{w}, weight{weight} {}

    // a getter to obtain a pointer to the first vertex
    Vertex *getV() { return this->v; }

    // a getter to obtain a pointer to the second vertex
    Vertex *getW() { return this->w; }

    // a getter to obtain the weight associated with this edge
    double getWeight() { return this->weight; }
};

/**
 * A class implementing the graph for our graph-processing algorithms. Here, the graph is represented 
 * by an adjacency-lists. 
 * 
*/
class Graph
{
    // holds the number of vertices in the graph
    int vertices;

    // tells whether graph is (un)directed (by default: undirected)
    bool isDirected;

    // the adjacency-lists representation of this graph
    vector<vector<Node *>> adjLists;

    // holds the number of edges in this graph
    int edges;

    // private method to initialize the adjacency-lists representation of this graph
    void initAdjLists()
    {
        // initialize the adjacency-lists
        this->adjLists.assign(vertices, {});
    }

public:
    // constructor
    Graph(int vertices, bool isDirected = false) : vertices{vertices}, isDirected{isDirected}
    {
        // sanity check: we disallow empty graphs
        if (vertices == 0)
            throw invalid_argument{"Invalid vertex number. Empty graphs are not allowed."};

        // initialize the adjacency-list of each vertex
        initAdjLists();
    }

    // a getter to obtain the number of vertices in the graph
    int getVertices() { return this->vertices; }

    // a getter to obtain the number of edges in the graph
    int getEdges() { return this->edges; }

    // a getter to obtain the adjacency-lists
    vector<vector<Node *>> getAdjLists() { return this->adjLists; }

    // public method to insert an edge into the graph
    void insertEdge(Edge *edge)
    {
        // get the source vertex id
        // it tells us in which adjacency list its adjacent vertex (destination) will be placed
        int sourceId = edge->getV()->getId();

        // get the adjacent vertex to the source (which is the destination vertex)
        auto adjacentVertexToSource = edge->getW();

        // add it to the corresponding adjacency list
        this->adjLists[sourceId].push_back(new Node(adjacentVertexToSource->getId(), edge->getWeight()));

        // increment the number of edges by 1
        this->edges++;

        // do the opposite if the graph is undirected (default)
        if (!isDirected)
        {
            // get the destination vertex id
            // it tells us in which adjacency list its adjacent vertex (source) will be placed
            int destinationId = edge->getW()->getId();

            // get the adjacent vertex to the destination (which is the source vertex)
            auto adjacentVertexToDestination = edge->getV();

            // add it to the corresponding adjacency list
            this->adjLists[destinationId].push_back(new Node(adjacentVertexToDestination->getId(), edge->getWeight()));

            // increment the number of edges by 1
            this->edges++;
        }
    }
    // a public method to print the adjacency-lists representation of this graph
    void showGraph()
    {
        // scan through the adjacency-lists representation
        for (int vertexId = 0; vertexId < this->vertices; vertexId++)
        {
            cout << vertexId << ": ";
            for (const auto vertex : this->adjLists[vertexId])
                cout << "(" << vertex->getAdjVertexId() << " , " << vertex->getWeight() << ")"
                     << " ";

            cout << endl;
        }
    }
};
