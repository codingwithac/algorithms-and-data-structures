
/**
 * The client that tests the functionalities of the SeparateChaining class.
*/

#include "separateChaining.hpp"
#include <string>

int main()
{
    SeparateChaining<string, int> *sp = new SeparateChaining<string, int>{100};
    sp->put("Abdullah", 33);
    sp->put("Arif", 28);
    cout << sp->getValue("Abdullah") << endl;

    auto keyToSearch = "Abdullah";
    cout << "Is " << keyToSearch << " in the hash table? Answer: " << boolalpha << sp->contains(keyToSearch) << endl;

    cout << "How many elements do we have? Answer: " << sp->getNrOfElements() << endl;

    cout << "Is the hash table empty? Answer: " << sp->isEmpty() << endl;

    sp->printHashTable();
    sp->removal("Abdullah");
    cout << "How many elements do we have? Answer: " << sp->getNrOfElements() << endl;

    sp->printHashTable();
}