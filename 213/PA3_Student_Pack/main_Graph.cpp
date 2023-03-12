#include "Graph.h"
#include "GraphExceptions.h"
#include <iostream>

int main()
{
    Graph g;
    std::vector<int> vector;
    g.InsertVertex("S");
    g.InsertVertex("T");
    g.InsertVertex("U");
    g.InsertVertex("V");
    g.InsertVertex("Y");
    g.InsertVertex("Z");


    g.ConnectVertices("S", "Y", 4);
    g.ConnectVertices("Y", "Z", 2);
    g.ConnectVertices("S", "Z", 7);
    g.ConnectVertices("S", "T", 10);
    g.ConnectVertices("T", "Y", 3);
    g.ConnectVertices("Y", "Z", 2);

    g.ShortestPath(vector,"S","Y");

    return 0;
}