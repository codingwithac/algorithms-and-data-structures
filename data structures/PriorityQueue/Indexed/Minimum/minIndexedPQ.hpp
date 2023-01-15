#include <vector>
#include <stdexcept>
#include <iostream>

using namespace std;

template <typename T>
class MinIndexedPQ
{
    // holds the current size of the heap
    int curSize;

    // holds the maximum size of the heap
    int maxSize;

    // a lookup table we maintain to tell us the
    // position of a key index in the heap
    // It answers the question:
    // "How do we go from knowing the index of a
    //  key to its position in the heap?"
    // key index -> its position in the heap
    vector<int> position{};

    // a lookup table we maintain to tell us
    // which key index is represented in the
    // heap at a certain position
    // It answers the question:
    // "How we do go from knowing the position
    //  of a key index in the heap to the key
    //  index ?"
    // position of key index in the heap -> key index at that position
    vector<int> indices{};

    // a lookup table that contains the priorities used to compare
    // key indices with each other
    // It is given to this class by the client
    // It answers the question:
    // "How do we go from knowing the index to its priority ?"
    // key index -> priority
    //T *priority{};
    vector<T> priorities{};

    // method that gives us the parent position in the heap
    int getParentPositionInHeap(int currentPos)
    {
        return (currentPos - 1) / 2;
    }

    // method that gives us the left child's position in the heap
    int getLeftChildPositionInHeap(int currentPos)
    {
        return 2 * currentPos + 1;
    }

    // method that gives us the right child's position in the heap
    int getRightChildPositionInHeap(int currentPos)
    {
        return 2 * currentPos + 2;
    }

    // method that implements the lessThan operation to compare two key indices
    bool lessThan(int pos1, int pos2)
    {
        // extract the key index at position pos1 in the heap
        // from the indices vector
        int ki1 = indices.at(pos1);

        // extract the key index at position pos2 in the heap
        // from the indices vector
        int ki2 = indices.at(pos2);

        // extract the priority of key index ki1 from the priority array
        auto pr1 = priorities[ki1];

        // extract the priority of key index ki2 from the priority array
        auto pr2 = priorities[ki2];

        // check whether priority of ki1 is smaller than priority of ki2
        return (pr1 < pr2) ? true : false;
    }

    // method to apply top-down heapify to restore the heap condition
    void topDownHeapify(int curPos)
    {
        while (true)
        {
            // get the left child's position
            int leftChildPos = getLeftChildPositionInHeap(curPos);

            // get the right child's position
            int rightChildPos = getRightChildPositionInHeap(curPos);

            // we have to determine the smaller child
            // initially select the left child as the smaller one
            int smallerChildPos = leftChildPos;

            // check if right child is smaller
            if (rightChildPos < curSize && lessThan(rightChildPos, leftChildPos))
                smallerChildPos = rightChildPos;

            // check if we have to end the loop
            if (leftChildPos >= curSize || lessThan(curPos, smallerChildPos))
                break;

            // swap key index at the current pos with its smallest child's position
            swap(curPos, smallerChildPos);

            // update the current position for the next iteration
            curPos = smallerChildPos;
        }
    }

    // method to apply bottom-up heapify to restore the heap condition
    void bottomUpHeapify(int curPos)
    {
        // get the parent position
        int parentPos = getParentPositionInHeap(curPos);

        // swap key indices at curPos and parentPos in the heap
        // as long as we don't have reached the beginning of the heap
        // and the key index at curPos has a smaller priority than the key
        // index at parentPos
        while (curPos > 0 && lessThan(curPos, parentPos))
        {
            // swap
            swap(curPos, parentPos);

            // update the current position for next iteration
            curPos = parentPos;

            // update the parent position for next iteration
            parentPos = getParentPositionInHeap(curPos);
        }
    }

    // method to exchange key indices in the heap
    void swap(int pos1, int pos2)
    {
        // extract the key indices at position 'pos1' and 'pos2' from the indices vector
        int ki1 = indices.at(pos1);
        int ki2 = indices.at(pos2);

        // swap the positions of these key indices in the position vector
        position[ki1] = pos2;
        position[ki2] = pos1;

        int tmp = indices.at(pos1);
        indices[pos1] = indices[pos2];
        indices[pos2] = tmp;
    }

public:
    MinIndexedPQ(int maxSize) : maxSize{maxSize}, curSize{0}
    {
        // Sanity checks
        if (maxSize <= 0)
            throw invalid_argument{"Invalid argument: Max size <= 0."};

        // initialize the lookup tables with default value -1
        position.assign(maxSize, -1);
        indices.assign(maxSize, -1);
        priorities.assign(maxSize, -1);
    }

    // method that performs insertion of a key index
    void insert(int keyIndex, T value)
    {
        // save the position of the given index in the position vector
        position[keyIndex] = curSize;

        // save the given key index in the indices vector
        indices[curSize] = keyIndex;

        // add value to the priority vector at given key index
        priorities[keyIndex] = value;

        // apply bottom-up heapify to restore the heap condition that might be violated
        bottomUpHeapify(curSize);

        // increment the current size by 1
        curSize++;
    }

    // method that applies removal of a key index
    void remove(int keyIndex)
    {
        // extract the position of given key index from the position vector
        int pos = position[keyIndex];

        // decrement the current size by 1
        curSize--;

        // exchange given key index and the last key index in the heap
        swap(pos, curSize);

        // apply top-down heapify to restore the heap condition
        topDownHeapify(pos);

        // apply bottom-up heapify to restore the heap condition
        bottomUpHeapify(pos);

        // delete the key index in the indices vector
        // note: after swapping the given key index is located at the end of the indices vector
        indices[curSize] = -1;

        // delete the position of the key index in the position vector
        position[keyIndex] = -1;

        // delete the priority at key index
        priorities[keyIndex] = -1;
    }

    // method that gives us the minimum key index
    int getMinKeyIndex()
    {
        // sanity check
        if (curSize == 0)
            throw runtime_error{"There no indices to return."};

        // the minimum key index is located at 0 in the indices vector
        int minKi = indices.at(0);

        // return
        return minKi;
    }

    // method that checks whether or not a key index exists
    bool contains(int keyIndex)
    {
        // sanity check
        if (keyIndex < 0 || keyIndex >= maxSize)
            throw invalid_argument{"Invalid argument: key index <=0 OR >= maxSize."};

        // if the key index has no position, it does not exist; otherwise, it exists.
        return (position[keyIndex] == -1) ? false : true;
    }

    // method that deletes and returns the minimum key index
    int deleteMinKeyIndex()
    {
        // get the minimum key index
        int minKi = getMinKeyIndex();

        // remove the key index
        remove(minKi);

        // return the minimum key index
        return minKi;
    }

    // method that changes the position of a key index (used after the priority of a key index is changed)
    void change(int keyIndex, T newPriority)
    {
        // get the position of a key index from the position vector
        const int pos = position[keyIndex];

        // update the priority at key index
        priorities[keyIndex] = newPriority;

        // apply bottom-up heapify to restore the heap condition
        bottomUpHeapify(pos);

        // apply top-down heapify to restore the heap condition
        topDownHeapify(pos);
    }

    // print the lookup tables (just for debugging purposes)
    void printTables()
    {
        cout << "Indices: ";
        for (const auto index : indices)
            cout << index << " ";

        cout << endl;

        cout << "Position: ";
        for (const auto pos : position)
            cout << pos << " ";
        cout << endl;

        cout << "Priority: ";
        for (const auto pos : priorities)
            cout << pos << " ";
        cout << endl;
    }
};