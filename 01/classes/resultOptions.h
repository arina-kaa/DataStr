#include <iostream>
#include <cstring>

using namespace std;

class resultOptions
{
  public:
    static const int validString = 0;
    static const int emptyString = 1;
    static const int invalidSymbol = 2;
    static const int notClosedBrackets = 3;
    static const int severalOperations = 4;

    static void printError(int resultCode)
    {
        switch (resultCode)
        {
        case emptyString:
            cout << "Empty infix string." << endl;
            break;
        case invalidSymbol:
            cout << "Invalid symbol." << endl;
            break;
        case notClosedBrackets:
            cout << "Not closed brackets." << endl;
            break;
        case severalOperations:
            cout << "Several operations detected in a row." << endl;
            break;
        }
    }
};