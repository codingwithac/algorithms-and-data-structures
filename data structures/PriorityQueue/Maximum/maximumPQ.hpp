#include <iostream>
#include <stdexcept>

using namespace std;

template <typename Item>
class MaxPQ
{
    // pointer to the minimum PQ
    Item *pq;

    // holds the number of items
    int items;

    // holds the maximum size of elements
    int maxSize;

    // method that computes the index of the left child of item at 'idx'
    int getLeftChildIndex(int idx)
    {
        return 2 * idx + 1;
    }

    // method that computes the index of the right child of item at 'idx'
    int getRightChildIndex(int idx)
    {
        return 2 * idx + 2;
    }

    // method that computes the index of the parent of item at 'idx'
    int getParentIndex(int idx)
    {
        return (idx - 1) / 2;
    }

    // method to swap elements at idx1 & idx2
    void swap(int idx1, int idx2)
    {
        Item tmp = pq[idx1];
        pq[idx1] = pq[idx2];
        pq[idx2] = tmp;
    }

    // method to check if item at idx1 is greater than the item at idx2
    bool greaterThan(int idx1, int idx2) { return pq[idx1] > pq[idx2]; }

    // method that applies bottom-up heapify to restore the heap condition
    void bottomUpHeapify(int curIndex)
    {
        // determine the parent index of the element at 'curIndex'
        int parentIndex = getParentIndex(curIndex);

        // move up until current index > 0 AND item at current index is smaller than item at parent index
        while (curIndex > 0 && greaterThan(curIndex, parentIndex))
        {
            // swap item at current index with element at parent index
            swap(curIndex, parentIndex);

            // update the current index
            curIndex = parentIndex;

            // update the parent index
            parentIndex = getParentIndex(curIndex);
        }
    }

    // method that applies top-down heapify to restore the heap condition
    void topDownHeapify(int curIndex)
    {
        while (true)
        {
            // get the index of the left child of the element at 'curIndex'
            int leftChildIndex = getLeftChildIndex(curIndex);
            // get the index of the right child of the element at 'curIndex'
            int rightChildIndex = getRightChildIndex(curIndex);

            // we have to determine the smallerChild; initially, select the left child as the smaller one
            // note: that might change in the future
            int smallerChildIndex = leftChildIndex;

            // check if right child is smaller
            if (rightChildIndex < items && greaterThan(rightChildIndex, leftChildIndex))
                smallerChildIndex = rightChildIndex;

            // check whether or not the loop terminates
            if (leftChildIndex >= items || greaterThan(curIndex, smallerChildIndex))
                break;

            // swap the elements 'curIndex' with element at 'smallerChildIndex'
            swap(curIndex, smallerChildIndex);

            // after a swap, we have to update the current index
            curIndex = smallerChildIndex;
        }
    }

public:
    // constructor
    MaxPQ(int maxSize) : items{0}, maxSize{maxSize}
    {
        // initialize PQ
        pq = new Item[maxSize];
    }

    // method to print the heap (just for debugging purposes)
    void printHeap()
    {
        for (int i = 0; i < items; i++)
            cout << pq[i] << " ";

        cout << endl;
    }

    // method to insert an item into the PQ
    void insert(Item newItem)
    {
        if (items == maxSize)
            throw runtime_error{"Insert method failed. PQ is full."};

        // initially, insert the new item at the end of the heap
        pq[items] = newItem;

        // apply bottom-up heapify to restore the heap condition that might be destroyed after adding the new item
        bottomUpHeapify(items);

        // increment the items number by one
        items++;
    }

    // method to delete and return the minimum element in the PQ
    Item getMaximumItem()
    {
        // swap the first and last element
        swap(0, items - 1);

        // get the last item to return it later
        Item maxItem = pq[items - 1];

        // decrement the items number by 1
        items--;

        // apply top-down heapify to restore the heap condition
        topDownHeapify(0);

        // return minimum item
        return maxItem;
    }

    // method to remove an item from the PQ
    void remove(Item item)
    {
        if (items == 0)
            throw runtime_error{"Remove method failed. PQ is empty."};

        // apply linear search to find the item
        for (int i = 0; i < items; i++)
        {
            // item found; item to remove is at index -i
            if (item == pq[i])
            {
                // swap element at index i with last element
                swap(i, items - 1);

                // decrement the items number by 1
                items--;

                // apply top-down heapify to restore the heap condition
                topDownHeapify(i);
            }
        }
    }

    // method to check if a given item is in the PQ
    bool contains(Item item)
    {
        // apply linear search to find the item
        for (int i = 0; i < items; i++)
            // item found!
            if (pq[i] == item)
                return true;

        return false;
    }
};