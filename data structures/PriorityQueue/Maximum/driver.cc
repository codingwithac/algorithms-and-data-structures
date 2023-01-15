#include "maximumPQ.hpp"

int main()
{
    MaxPQ<int> *mPQ = new MaxPQ<int>(5);

    mPQ->insert(2);
    mPQ->insert(4);
    mPQ->insert(5);

    mPQ->printHeap();

    mPQ->remove(5);
    mPQ->printHeap();

    mPQ->insert(10);
    mPQ->printHeap();

    cout << "Max item: " << mPQ->getMaximumItem() << endl;
    mPQ->printHeap();

    int itemToSearch = 4;
    cout << "Is the item " << itemToSearch << " in the heap? Answer: " << boolalpha << mPQ->contains(itemToSearch) << endl;
}