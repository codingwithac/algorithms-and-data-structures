#include <vector>
#include <iostream>
using namespace std;

/**
 * A program illustrating the interface of the UnionFind 
 * data structure. 
*/
class UnionFind
{

public:
    // constructor to initialize n elements with integer names
    UnionFind(int n) : count{n}
    {
        // initialize the component id structure
        for (int i{}; i < n; i++)
            id.push_back(i);
    }

    // a virtual destructor
    virtual ~UnionFind() = default;

    // method to add connection between p and q
    // so, it merges two components if the two elements p & q are in different components
    // after merge is done, it also decrements the number of components stored in
    // 'count' by 1
    virtual void unify(int p, int q) = 0;

    // method to find the component id of p
    // so, returns an integer component id for a given element p
    virtual int find(int p) = 0;

    // method to check if p & q are in the same component
    bool connected(int p, int q)
    {
        return find(p) == find(q);
    }

    // method to return the number of components
    int getCount()
    {
        return count;
    }

    // public member representing the components
    // e.g. id[i] = component id to which i belongs to
    vector<int> id;

    // public member holding the number of components
    int count;

    // public method to print the component id structure to the console
    // (for debugging purposes)
    void printId()
    {
        for (int i{}; i < id.size(); i++)
            cout << "Component id of " << i << " is: " << id[i] << endl;
    }
};