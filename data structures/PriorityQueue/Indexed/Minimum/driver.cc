#include "minIndexedPQ.hpp"
#include <array>

int main()
{
    MinIndexedPQ<double> *minIPQ = new MinIndexedPQ<double>(4);

    minIPQ->insert(0, 0.43);
    minIPQ->insert(2, 0.11);
    minIPQ->insert(1, 0.36);
    minIPQ->insert(3, 0.25);

    cout << "Min Key: " << minIPQ->getMinKeyIndex() << endl;

    minIPQ->printTables();
    cout << "--------------------------" << endl;

    auto minKeyIndex = minIPQ->deleteMinKeyIndex();
    cout << "Min Key: " << minIPQ->getMinKeyIndex() << endl;
    minIPQ->printTables();
    cout << "--------------------------" << endl;

    cout << "Does key index 2 exists? Answer: " << boolalpha << minIPQ->contains(2) << endl;
    cout << "Does key index 0 exists? Answer: " << boolalpha << minIPQ->contains(0) << endl;

    minIPQ->change(0, 0.08);
    cout << "Min Key: " << minIPQ->getMinKeyIndex() << endl;
    minIPQ->printTables();
}