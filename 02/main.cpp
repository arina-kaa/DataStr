#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
#include "classes/tree.h"

using namespace std;

bool askContinue()
{
    bool result = false;
    cout << endl
         << "Do you want to continue?" << endl;
    string answer = "";
    getline(cin, answer);
    if (answer == "yes" || answer == "y" || answer == "true" || answer == "1")
    {
        result = true;
    }
    return result;
}

vector<string> parseStr(const string &str, char delimiter = ' ')
{
    vector<string> strParts;

    stringstream stream(str);
    string tmpStr;

    while (getline(stream, tmpStr, delimiter))
    {
        strParts.push_back(tmpStr);
    }

    return strParts;
}

void printTreeFromFile(string filePath)
{
    ifstream fileIn;
    Tree<string> tree;
    fileIn.open(filePath);
    if (fileIn.is_open())
    {
        cout << "File is opened!" << endl
             << endl;
        string str = "";
        while (!fileIn.eof())
        {
            getline(fileIn, str);
            if (str.length() == 0)
                continue;

            vector<string> strParts = parseStr(str);
            if (strParts.size() > 0)
            {
                auto level = strParts[0].length();
                auto value = strParts[1];
                auto type = (strParts.size() == 3)
                                ? ((strParts[2][0] == '&') ? NodeType::AND : NodeType::OR)
                                : NodeType::LIST;
                tree.insert(value, level, type);
            }
        }
        tree.print();
        tree.generate();
    }
    else
    {
        cout << "File not found!" << endl;
    }
    fileIn.close();
}

int main() // task 18
{
    bool shouldContinue = true;
    while (shouldContinue)
    {
        cout << "Enter file name:" << endl;
        string filePath = "";
        getline(cin, filePath);

        printTreeFromFile(filePath);
        shouldContinue = askContinue();
    }
    return 0;
}
