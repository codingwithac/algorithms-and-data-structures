#include "boruvka.hpp"
#include <iostream>
#include <functional>

using namespace std;

int main()
{
    Vertex *v0 = new Vertex(0);
    Vertex *v1 = new Vertex(1);
    Vertex *v2 = new Vertex(2);
    Vertex *v3 = new Vertex(3);
    Vertex *v4 = new Vertex(4);
    Vertex *v5 = new Vertex(5);
    Vertex *v6 = new Vertex(6);
    Vertex *v7 = new Vertex(7);

    Edge *e1 = new Edge(v4, v5, 0.35);
    Edge *e2 = new Edge(v4, v7, 0.37);
    Edge *e3 = new Edge(v5, v7, 0.28);
    Edge *e4 = new Edge(v0, v7, 0.16);
    Edge *e5 = new Edge(v1, v5, 0.32);
    Edge *e6 = new Edge(v0, v4, 0.38);
    Edge *e7 = new Edge(v2, v3, 0.17);
    Edge *e8 = new Edge(v1, v7, 0.19);
    Edge *e9 = new Edge(v0, v2, 0.26);
    Edge *e10 = new Edge(v1, v2, 0.36);
    Edge *e11 = new Edge(v1, v3, 0.29);
    Edge *e12 = new Edge(v2, v7, 0.34);
    Edge *e13 = new Edge(v6, v2, 0.40);
    Edge *e14 = new Edge(v3, v6, 0.52);
    Edge *e15 = new Edge(v6, v0, 0.58);
    Edge *e16 = new Edge(v6, v4, 0.93);

    Graph graph{8};
    graph.insertEdge(e1);
    graph.insertEdge(e2);
    graph.insertEdge(e3);
    graph.insertEdge(e4);
    graph.insertEdge(e5);
    graph.insertEdge(e6);
    graph.insertEdge(e7);
    graph.insertEdge(e8);
    graph.insertEdge(e9);
    graph.insertEdge(e10);
    graph.insertEdge(e11);
    graph.insertEdge(e12);
    graph.insertEdge(e13);
    graph.insertEdge(e14);
    graph.insertEdge(e15);
    graph.insertEdge(e16);

    //graph.showGraph();

    vector<Edge *> edges{e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16};
    Boruvka *bor = new Boruvka(edges, 8);
    auto result = bor->boruvka();

    cout << "The edges belonging to the MST are: " << endl;
    for (const auto mstEdge : result.mst)
        cout << "(" << mstEdge->getV()->getId() << "," << mstEdge->getW()->getId() << "," << mstEdge->getWeight() << ")"
             << endl;
    cout << endl;

    cout << "Min cost: " << result.mstCost << endl;
}