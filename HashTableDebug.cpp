#include "HashTable.h"
#include <iostream>

int main() {
    HashTable ht;

    // Insert some key-value pairs
    std::cout << "Inserting values...\n";
    ht.insert("Alice", 1001);
    ht.insert("Bob", 1002);
    ht.insert("Charlie", 1003);
    ht.insert("David", 1004);
    ht.insert("Eve", 1005);

    // Print table
    std::cout << "\nInitial table:\n" << ht << "\n";

    // Test contains
    std::cout << "Contains 'Alice'? " << (ht.contains("Alice") ? "Yes" : "No") << "\n";
    std::cout << "Contains 'Zara'? " << (ht.contains("Zara") ? "Yes" : "No") << "\n";

    // Test get
    auto val = ht.get("Charlie");
    if (val) std::cout << "Value of 'Charlie': " << *val << "\n";

    // Test operator[]
    std::cout << "Bob before: " << ht["Bob"] << "\n";
    ht["Bob"] = 2022;
    std::cout << "Bob after: " << ht["Bob"] << "\n";

    // Test keys()
    std::cout << "Keys in table: ";
    for (auto k : ht.keys()) std::cout << k << " ";
    std::cout << "\n";

    // Test alpha(), size(), capacity()
    std::cout << "Load factor: " << ht.alpha() << "\n";
    std::cout << "Size: " << ht.size() << "\n";
    std::cout << "Capacity: " << ht.capacity() << "\n";

    // Remove a key
    std::cout << "\nRemoving 'David'...\n";
    ht.remove("David");
    std::cout << "Contains 'David'? " << (ht.contains("David") ? "Yes" : "No") << "\n";

    // Insert a new key to reuse EAR bucket
    ht.insert("Frank", 1006);

    // Print table after removal and new insertion
    std::cout << "\nTable after remove and insert:\n" << ht << "\n";

    // Test rehashBackwards
    std::cout << "Rehashing backwards...\n";
    ht.rehashBackwards();
    std::cout << "\nTable after rehashBackwards:\n" << ht << "\n";

    return 0;
}
