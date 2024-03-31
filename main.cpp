#include "soll.hpp"

int main() {
    SOList<int> myList;

    std::cout << "Inserting elements...\n";
    myList.push_back(1);
    myList.push_front(2);
    myList.push_back(3);
    myList.push_front(4);
    myList.push_front(5);
    myList.push_front(6);

    std::cout << "Original list: ";
    myList.print();

    std::cout << "\nSorted list: ";
    myList.print_sorted();

    std::cout << "\nRemoving elements...\n";
    myList.pop_back();
    myList.pop_front();

    std::cout << "List after removal: ";
    myList.print();

    std::cout << "\nSorted list after removal: ";
    myList.print_sorted();

    std::cout << "\nInserting at position 1...\n";
    myList.insert(1, 4);

    std::cout << "List after insertion: ";
    myList.print();

    std::cout << "\nSorted list after insertion: ";
    myList.print_sorted();

    std::cout << "\nRemoving at position 1...\n";
    myList.remove(1);

    std::cout << "List after removal: ";
    myList.print();

    std::cout << "\nSorted list after removal: ";
    myList.print_sorted();

    return 0;
}
