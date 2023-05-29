#include "Forward_List.h"
#include <iostream>

int main()
{
    srand(time(NULL));
    Forward_List<int> List;

    for (int i = 0; i < 5; ++i)
    {
        List.Push_Back(rand() % 39 - 10);
    }
    List.Push_Front(1000);

    List.Print();
    std::cout << "\n";
    List.Insert(999, 3);
    List.Print();
    List.RemoveAt(3);
    std::cout << "\n";
    List.Print();
}
