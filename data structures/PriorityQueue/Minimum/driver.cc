#include "minimumPQ.hpp"

int main()
{
    MinPQ<int> *mPQ = new MinPQ<int>(5);
    mPQ->insert(5);
    mPQ->insert(4);
    mPQ->insert(2);
    mPQ->insert(0);

    mPQ->printHeap();

    cout << "Min item: " << mPQ->getMinimumItem() << endl;
    mPQ->printHeap();

    mPQ->insert(-1);
    mPQ->printHeap();

    mPQ->remove(2);
    mPQ->printHeap();

    int itemToSearch = 4;
    cout << "Is the item " << itemToSearch << " in the heap? Answer: " << boolalpha << mPQ->contains(itemToSearch) << endl;
}