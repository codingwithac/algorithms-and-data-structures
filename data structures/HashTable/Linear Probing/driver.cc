
/**
 * The client that tests the functionalities of the LinearProbing class.
*/

#include "linearProbing.hpp"
#include <string>

int main()
{
    LinearProbing<string, int> lp{10};
    lp.put("Abdullah", 33);
    lp.put("Abdullah", 36);

    cout << "The value of key Abdullah is " << lp.getValue("Abdullah") << endl;

    auto keyToSearch = "Abdullah";
    cout << "Does the key " << keyToSearch << " exist? Answer: " << boolalpha << lp.contains(keyToSearch) << endl;

    cout << "How many elements do we have in the hash table? Answer: " << lp.getElements() << endl;

    cout << "Is the hash table empty? Answer: " << lp.isEmpty() << endl;

    lp.printHashTable();

    lp.put("Arif", 28);
    lp.put("Günther", 55);
    lp.put("Klaus", 48);
    lp.put("Linda", 39);
    lp.put("Jessica", 42);
    lp.put("James", 33);
    lp.put("Maria", 55);
    lp.put("Torben", 22);
    lp.put("Tim", 18);
    lp.put("Jaqueline", 44);
    lp.printHashTable();

    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    lp.removal("Abdullah");

    lp.printHashTable();
}