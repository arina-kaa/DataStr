/*
Каравайцева Арина, ИПС-2020

   1. Имеется массив элементов,  отсортированный по некоторому
полю. Методом бинарного поиска обеспечить:
   1) нахождение заданного элемента;
   2) вставку элемента;
   3) удаление элемента (8).
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <optional>

std::vector<int> values;

void Print()
{
    for (const int value : values) std::cout << value << " ";
    std::cout << std::endl;
}

std::pair<int, int> FindElement(int value)
{
    bool flag = false;
    int l = 0;
    int r = values.size() - 1;
    int mid;

    while ((l <= r) && (!flag)) {
        mid = (l + r) / 2;

        if (values[mid] == value) 
            flag = true;

        if (values[mid] > value) 
            r = mid - 1;
        else 
            l = mid + 1;
    }

    return std::make_pair((flag) ? mid : -1, l);
}

void AddElement(int value)
{
    values.insert(values.begin() + FindElement(value).second, value);
}

void DeleteElement(int value)
{
    int pos = FindElement(value).first;
    if (pos >= 0)
    {
        values.erase(values.begin() + pos);
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        exit;
    }
    const std::string fileName = argv[1];
    std::ifstream input(fileName);

    int value;
    while (input >> value)
    {
        values.push_back(value);
    }
    Print();

    int command;
    do
    {
        std::cout << "Select command:" << std::endl;
        std::cout << "1 - find element" << std::endl;
        std::cout << "2 - add element" << std::endl;
        std::cout << "3 - delete element" << std::endl;
        std::cout << "4 - exit" << std::endl;

        std::cin >> command;
        if (command != 4)
        {
            std::cin >> value;
            switch (command)
            {
            case 1:
                std::cout << FindElement(value).first << std::endl;
                break;
            case 2:
                AddElement(value);
                break;
            case 3:
                DeleteElement(value);
                break;
            default:
                break;
            }
            Print();
        }
    } while (command != 4);

    return 0;
}